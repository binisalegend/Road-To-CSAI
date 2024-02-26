论文原文：IJCAI'19 DHGNN(Dynamic Hypergraph Neural Networks)
# 动态超图构建过程
---
> [!TITLE] Algorithm 1: Hypergraph Construction
> Input: 输入图嵌入$\mathcal{X}$；边大小$k$; 相邻超边集大小$S$
> 
> Output: 构建出的超边集$G$
>
> Function: k-Means聚类; knn近邻算法; dis计算两点闵可夫斯基距离; $S−1$小距离topK
~~~C
// Algorithm 1
1: C = kMeans(X) // 得到聚类中心集C
2: for u in range(len(X)) do
3:     eb = knn(X[u], X, k)  // 得到超边
4:     G[u].insert(eb)
5:     D = dis(C.center, u)
6:     D = sort(D)
7:     ind = topK(D, S − 1)
8:     for i in ind do
9:         G[u].insert(C[i])  // 将节点u连接到距离其最近的S-1个聚类中心
10:     end for
11: end for
~~~

- 设$Con(e)$为超边$e$包含的顶点集，$Adj(u)$为顶点$u$所相连的超边集
- $k_u,k_e$分别为包含顶点$u$的超边数和超边$e$所包含的顶点数，同时定义顶点$u$为超边集$Adj(u)$的质心顶点

# 超图卷积
---
## 顶点卷积模块

> [!TITLE] vertex convolution submodule
> 顶点卷积将顶点特征聚合到包含此顶点的超边上![](Pasted%20image%2020240117170142.png)

- 对于$k$个顶点，通过卷积计算出一个$k\times k$的变换矩阵，将变换矩阵与输入的顶点特征矩阵相乘，得到置换加权的顶点特征矩阵，然后对一维超边缘特征进行一维卷积。
- 在实现中，我们利用多层感知(MLP)来生成变换矩阵$T$，并使用$1-d$卷积来压缩变换后的特征
$$\begin{aligned}\mathbf{T}&=MLP(\mathbf{X}_u)\\\mathbf{x}_e&=conv(\mathbf{T}\cdot MLP(\mathbf{X}_u))\end{aligned}$$

## 超边卷积模块
> [!TITLE] hyperedge convolution submodule
> 超边卷积将相邻的超边特征聚合到质心顶点![](Pasted%20image%2020240117171822.png)

- 在超边卷积中采取注意力机制，利用多层感知(MLP)生成每个超边的权值输出的质心顶点特征即为输入的超边特征的加权和，即$$\begin{aligned}w&=softmax(\mathbf{x}_e\mathbf{W}+\mathbf{b})\\\mathbf{x}_u&=\sum_{i=0}^{|Adj(u)|}w^i\mathbf{x}_e^i\end{aligned}$$其中，$|Adj(u)|$是相邻超边集的大小，$X_e,X_u$分别表示相邻超边和质心顶点的特征，$W,b$为训练参数权重和偏置

# 动态超图神经网络
---
> [!TITLE] Algorithm 2 Hypergraph Convolution
> Input: Input sample $X_u$; hypergraph structure $G$
>
> Output: Output sample $Y_u$
~~~C
1: xlist = Φ
2: for e in Adj(u) do
3:     X_v = VertexSample(X, G)
4:     X_e = VertexConv(X_v)
5:     xlist.insert(X_e)
6: end for
7: X_e = stack(xlist)
8: X_u = EdgeConv(X_e)
9: Y_u = σ(X_u W + b)
~~~
- 通过结合定点卷积和超边卷积，我们将超图卷积层描述为算法二。对于$Adj(u)$中的每条超边$e$，首先对$e$中的$k$个顶点进行采样，得到$\mathbf{X}_{u}\in\mathbb{R}^{k\times d}$，其中$d$为特征输入维数。顶点卷积`vertexConv`将顶点特征$X_u$转换为超边特征$\mathbf{x}_{e}\in\mathbb{R}^{d}$。在进行$|Adj(u)|$次顶点卷积后，将$|Adj(u)|$超边特征堆叠，得到相邻特征矩阵$\mathbf{X}_e\in\mathbb{R}^{|Adj(u)|\times d}$。然后超边卷积`EdgeConv`将相邻的超边特征聚合到质心顶点$u$的特征$\mathbf{x}_{u}$上，最后$\mathbf{x}_{u}$通过线性层中的非线性激活函数$\sigma$转化为$y_u$
- 一个`DHGNN`模型由数层超图构建模块和超图卷积模块堆叠而成，一个超图卷积层更新定点特征以进行新的特征输入，基于此特征进行新的超图结构构建，如下：![](Pasted%20image%2020240117211651.png)

# 代码分析
---
## edge_to_hyperedge
> [!TITLE] `edge_to_hyperedge` 
> 函数主要目的是将图的边转换为超图的超边。

- 函数接收一个参数 `edges`，这是一个包含图的边的列表。
- 函数首先创建一个名为 `edge_list` 的列表，其长度为 `edges` 中的最大值加一。这个列表的每个元素都是一个空列表，用于存储与每个节点相连的其他节点。
- 然后，函数遍历 `edges` 中的每个边。对于每个边，它将边的两个节点添加到对方的列表中。这样，`edge_list` 的每个元素都将包含与该节点相连的所有其他节点。
- 最后，函数返回 `node_list` 和 `edge_list`。`node_list` 是 `edge_list` 的别名，它们都是相同的对象。这两个列表都表示了图的结构，其中每个节点都与其相连的其他节点相关联。

## construct_H_with_KNN
> [!TITLE] `construct_H_with_KNN`
> 函数的主要目的是从原始节点特征矩阵初始化多尺度超图顶点-边矩阵。

- 函数接收四个参数：`X`，`K_neigs`，`is_probH` 和 `m_prob`。`X` 是一个形状为 `N_object x feature_number` 的矩阵，表示原始节点特征。`K_neigs` 是一个整数或整数列表，表示邻居扩展的数量。`is_probH` 是一个布尔值，表示是否使用概率顶点-边矩阵或二进制。`m_prob` 是一个概率值。
- 首先，函数检查 `X` 的形状。如果 `X` 不是二维的，那么它将被重塑为二维，其中第二个维度是特征数量。
- 然后，函数检查 `K_neigs` 的类型。如果 `K_neigs` 是一个整数，那么它将被转换为一个只包含该整数的列表。
- 接下来，函数计算 `X` 的余弦距离矩阵 `dis_mat`。
- 然后，函数初始化一个名为 `H` 的变量，用于存储超图邻接矩阵。
- 接着，函数遍历 `K_neigs` 中的每个元素 `k_neig`。对于每个 `k_neig`，函数调用 `construct_H_with_KNN_from_distance` 函数，使用 `dis_mat`、`k_neig`、`is_probH` 和 `m_prob` 作为参数，生成一个临时的超图邻接矩阵 `H_tmp`。然后，使用 `hyperedge_concat` 函数将 `H_tmp` 附加到 `H` 上。
- 最后，函数返回超图邻接矩阵 `H`。

## construct_H_with_KNN_from_distance
> [!TITLE] `construct_H_with_KNN_from_distance` 
> 函数的主要目的是从超图节点距离矩阵构建超图邻接矩阵。

- 函数接收四个参数：`dis_mat`，`k_neig`，`is_probH` 和 `m_prob`。`dis_mat` 是节点距离矩阵。`k_neig` 是最近邻居的数量。`is_probH` 是一个布尔值，表示是否使用概率顶点-边矩阵或二进制。`m_prob` 是一个概率值。
- 首先，函数获取 `dis_mat` 的形状，确定节点数量 `n_obj` 和边数量 `n_edge`。然后，函数初始化一个形状为 `n_obj x n_edge` 的零矩阵 `H`。
- 接着，函数遍历每个节点，对于每个节点，函数将其距离矩阵的对角线元素设置为0，然后获取该节点的距离向量 `dis_vec`。函数使用 `np.argsort` 函数对 `dis_vec` 进行排序，获取最近的 `k_neig` 个节点的索引 `nearest_idx`。如果中心节点不在 `nearest_idx` 中，函数将最后一个元素设置为中心节点的索引。
- 然后，函数遍历 `nearest_idx` 中的每个节点索引 `node_idx`。如果 `is_probH` 为 `True`，函数将 `H[node_idx, center_idx]` 设置为基于 `dis_vec[0, node_idx]` 和平均距离 `avg_dis` 的概率值。否则，函数将 `H[node_idx, center_idx]` 设置为1。
- 最后，函数返回超图邻接矩阵 `H`。

## \_generate_G_from_H
> [!TITLE] `_generate_G_from_H` 
> 函数的主要目的是从超图邻接矩阵 `H` 计算图 `G`。

- 函数接收两个参数：`H` 和 `variable_weight`。`H` 是超图邻接矩阵。`variable_weight` 是一个布尔值，表示超边的权重是否可变。
- 首先，函数将 `H` 转换为 numpy 数组，并获取其列数 `n_edge`，这表示超边的数量。然后，函数创建一个长度为 `n_edge` 的全1数组 `W`，表示超边的权重。
- 接着，函数计算节点的度 `DV` 和超边的度 `DE`。节点的度 `DV` 是 `H` 和 `W` 的点积沿轴1(列)的和。超边的度 `DE` 是 `H` 沿轴0(行)的和。
- 然后，函数计算 `DE` 的逆 `invDE` 和 `DV` 的平方根的逆 `DV2`。这两个值都是对角矩阵。
- 接下来，函数将 `H` 转换为矩阵，并计算其转置 `HT`。
- 最后，如果 `variable_weight` 为 `True`，函数返回 `DV2 * H`，`W` 和 `invDE * HT * DV2`，即拉普拉斯矩阵的三部分。否则，函数返回 `DV2 * H * W * invDE * HT * DV2`，即$D_{v}^{-\frac{1}{2}}HWD_{e}^{-1}H^{T}D_{v}^{-\frac{1}{2}}$为超图中拉普拉斯矩阵的标准化结果，这是图 `G` 的计算结果。

## construct_G_from_fts
> [!TITLE] `construct_G_from_fts` 
> 函数的主要目的是从特征列表生成图`G`，通过连接超图关联矩阵`H`。

- 函数接收两个参数：`Xs` 和 `k_neighbors`。`Xs` 是特征列表，`k_neighbors` 是一个整数列表，表示每个特征的邻居数量。
- 首先，函数初始化一个空列表 `Hs`。然后，它遍历 `Xs` 的长度，对于每个特征，它调用 `construct_H_with_KNN` 函数，将特征和 `k_neighbors` 中的相应邻居数量作为参数。`construct_H_with_KNN` 函数返回每个特征的超图邻接矩阵 `H`，然后将其添加到 `Hs` 列表中。
  ```python
  Hs = [construct_H_with_KNN(Xs[i], [k_neighbors[i]]) for i in range(len(Xs))]
  ```
- 处理所有特征后，函数沿第二轴（列）连接 `Hs` 中的所有超图关联矩阵，形成一个单独的矩阵 `H`。
  ```python
  H = np.concatenate(Hs, axis=1)
  ```
- 最后，函数调用 `generate_G_from_H` 函数，将 `H` 作为参数生成图 `G`。`generate_G_from_H` 函数将超图关联矩阵转换为图表示。然后，函数返回这个图 `G`。
  ```python
  G = generate_G_from_H(H)
  return G
  ```
- 总的来说，`construct_G_from_fts` 函数将特征列表转换为图表示，首先将每个特征转换为超图关联矩阵，然后连接这些矩阵，最后将结果矩阵转换为图。

## \_construct_edge_list_from_distance
> [!TITLE] `_construct_edge_list_from_distance()` 和 `construct_edge_list_from_knn()` 
> 函数目的是从给定的特征集合中构建边列表。

- `_construct_edge_list_from_distance()` 函数接收一个特征矩阵 `X` 和一个整数 `k_neigh` 作为输入。这个函数首先计算特征矩阵 `X` 中每个点之间的余弦距离，然后将距离矩阵转换为 PyTorch 张量。接着，它使用 PyTorch 的 `topk()` 函数找出每个点的 `k_neigh` 个最近邻居的索引。最后，它将这些索引转换为 numpy 数组并返回。

- `construct_edge_list_from_knn()` 函数接收一个特征列表 `Xs` 和一个整数列表 `k_neighs` 作为输入。这个函数遍历 `Xs` 中的每个特征矩阵，并对每个特征矩阵调用 `_construct_edge_list_from_distance()` 函数，得到每个特征矩阵的边列表。然后，它使用 numpy 的 `concatenate()` 函数将所有的边列表拼接在一起，并返回结果。

## \_construct_edge_list_from_cluster
> [!TITLE] `_construct_edge_list_from_cluster()` 
> 函数目的是从单一模态的特征中构建边列表。它接收一个特征矩阵 `X`，一个整数 `clusters` 表示 K-means 的簇数，一个整数 `adjacent_clusters` 表示一个节点的相邻簇数，以及一个整数 `k_neighbors` 表示一个节点的邻居数。

- 首先，函数使用 K-means 算法对特征矩阵 `X` 进行聚类，得到每个簇的中心 `centers`。然后，它计算 `X` 中的每个点到 `centers` 的欧氏距离 `dis`，并找出每个点的 `adjacent_clusters` 个最近的簇中心的索引 `cluster_center_dict`。
- 接着，函数获取每个点的簇标签 `point_labels`，并创建一个列表 `point_in_which_cluster`，其中 `point_in_which_cluster[i]` 包含了所有在第 `i` 个簇中的点的索引。
- 然后，函数创建一个字典 `cluster_neighbor_dict`，其中 `cluster_neighbor_dict[point]` 包含了点 `point` 的所有相邻簇中的点的索引。这个字典是通过将 `point_in_which_cluster[cluster_center_dict[point][i]]` 中的所有列表拼接在一起得到的。
- 最后，函数遍历 `cluster_neighbor_dict` 中的每个条目，对于每个点 `point`，它从 `cluster_neighbor_dict[point]` 中随机选择 `k_neighbors` 个邻居的索引，然后将这些索引返回。
