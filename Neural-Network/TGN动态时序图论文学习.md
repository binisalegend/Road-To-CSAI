# 背景
---
## 静态图中的深度学习
在一个静态图$G=(\mathcal{v}, \mathcal{e})$中，包含节点$\mathcal v=1,2,\dots,n$，和边$e\subseteq\mathcal{V}\times\mathcal{V}$，其中经典图神经网络GNN（通过学习局部聚合规则）创建节点的嵌入$z_{i}$：$$\begin{aligned}\mathrm{z_i=\sum_{j\in n_i}h(m_{ij},v_i)}\\\mathrm{m_{ij}=msg(v_i,v_j,e_{ij})}\end{aligned}$$可以理解为节点$i$的邻接节点$j$对它的信息传递，其中$n_{i}=\{j:(i, j)\in e\}$表示节点$i$的邻域，$msg$和$h$为可学习函数

## 动态时序图结构表示
> [!NOTE] 动态图分类
> 离散时间动态图(Discrete-time Dynamic Graph): 按照时间间隔拍摄的静态图快照
>
> 连续时间动态图(Continuos-time Dynamic Graph): 按照时间排列的事件，包括边、节点的添加、移动和删除，以及边权重的改变

1. 模型：
   动态图被建模为带时间戳(time-stamped)的时间序列: $$\mathcal G = \{x(t_{1}), x(t_{2}), \cdots\}$$
2. 事件表示：
   表示节点或节点交互作用(个人理解就是边权重和连接操作)的更改发生在$t_{1}, t_{2}, \cdots$中，事件$x(t_{i})$可以表示为以下两种类型
   1. 节点操作事件(node-wise event): 节点操作表示为$v_{i}(t)$，其中$i$是节点索引，$v$是事件相关的向量特性。节点一旦出现就假定之后一直存在，且在后续事件中其索引保持不变
   2. 节点交互事件(interaction event): 交互操作表示为$e_{ij}$，使用有向时序边表示(理论上两节点间在不同时间段可能具有多条平行边)

> [!INFO] 集合表示
> $\mathcal V(T) = \{i:\exists v_{i}(t)\in (G), t\in T\}$：表示点集合
>
> $\mathcal \varepsilon(T) = \{(i, j):\exists e_{ij}(t)\in G, t\in T\}$：表示边集
> 
> $\mathcal n_{i}(T)=\{j:(i, j)\in \varepsilon(T)\}$：表示节点$i$在时间间隔$T$间的邻接节点
> 
> $n_{i}^{k}(T)$：表示k跳邻接节点集，即从某个顶点出发，所有与节点$i$最短路径为K跳（或K步）的顶点的集合(BFS)
> 
> $\mathcal G(t)=(\mathcal V[0, t], \varepsilon[0, t])$：表示在时间$t$时对时序图$\mathcal G$的快照，包含$n(t)$个节点

- 动态图的神经网络模型可以看作一个`encoder-decoder`架构，`encoder`模块将动态图映射为节点嵌入，`decoder`模块接收一个或多个节点嵌入作为输入并进行节点分类或边预测

# 动态时序图核心模块
---

## 内存(memory)
内存（状态）储存了一个包含时间$t$之前所有出现过的节点$i$的向量$s_{i}(t)$，当节点参与某个节点或者边事件时，更新节点的内存，从而以一个压缩格式保存节点的历史连接情况，因此TGNs可以保存节点的长期连接状况

## 信息函数(message function)
- 信息传递函数是更新内存的重要机制。

1. 节点交互事件($e_{ij}(t),i, j, t)$：向两节点$i, j$发送message更新内存$$\begin{aligned}\mathbf{m}_i(t)&=\mathrm{msg}_{s}\left(\mathbf{s}_i(t^-),\mathbf{s}_j(t^-),t,\mathbf{e}_{ij}(t)\right)\\\mathbf{m}_j(t)&=\mathrm{msg}_{d}\left(\mathbf{s}_j(t^-),\mathbf{s}_i(t^-),t,\mathbf{e}_{ij}(t)\right)\end{aligned}$$
2. 节点操作事件($v_{i}(t), i, t$)：向被操作节点$i$发送message更新内存$$\mathbf{m}_{i}(t)=\mathrm{msg}_{\mathrm{n}}(\mathbf{s}_{i}(t^{-}),t,\mathbf{v}_{i}(t))$$其中，$s_{i}(t^{-})$指节点$i$在时间$t$之前的内存，$msg_{s},msg_{d},msg_{n}$为诸如`MLPs`的可学习消息函数，本文选用`identity`函数，仅对输入做简单拼接
![](Pasted%20image%2020240123213424.png)

## 信息聚合器(message aggregator)
- 为提高消息处理效率进行批处理操作，导致同一批次(batch)中包含同一节点$i$的多个事件，用于每个事件都会产生一个message，我们采用了一种机制来聚合同一个节点$i$在时间$t_{1},\cdots, t_{b}\leq t$中的message $m_{i}(t_{1}), \cdots, m_{i}(t_{b})$: $$\bar{\mathrm{m}}_i(t)=\mathrm{agg}\left(\mathrm{m}_i(t_1),\ldots,\mathrm{m}_i(t_b)\right)$$其中，$agg$为聚合函数，可以采用`RNNs`或是对节点内存采用注意力机制等方式，本文中仅采用保留最近消息(most recent message)和平均消息(mean message)两种(不可学习型)方式进行操作
![](Pasted%20image%2020240123215306.png)

## 内存更新器(memory updater)
- 根据新的message更新节点内存$$\mathbf{s}_{i}(t)=\operatorname*{mem}\left(\bar{\mathbf{m}}_{i}(t),\mathbf{s}_{i}(t^{-})\right)$$其中，$mem$是一个可学习型的记忆更新函数，可以采用`RNN`, `LSTM`(长短期记忆递归神经网络), `GRU`(门控循环单元)等实现，以解决长期记忆和反向传播中的梯度等问题
![](Pasted%20image%2020240123215326.png)

## 图嵌入(embedding)
- 考虑到节点的内存本身就是一个随时间更新的向量，最直接方式是直接使用内存作为节点的嵌入(Embedding)，但是在长期记忆中可能会产生陈旧性问题(staleness problem)，因此选取其他方式计算嵌入
- 一种解决方案是参考节点的邻居。为了解决陈旧性问题，嵌入模块通过对节点的时空邻接节点(spatiotemporal neighbours)进行图形聚合(graph aggregation)来计算该节点的时间嵌入(temporal embedding)。即使一个节点已经不活动一段时间，它的一些邻居可能已经活动，并且通过聚集他们的内存，TGN可以计算一个节点最新的嵌入(up-to-date embedding)。在我们的例子中，即使用户离开Twitter，他们的朋友仍然活跃，所以当用户返回时，朋友最近的活动可能比用户自己的历史活动更相关。  
![](Pasted%20image%2020240123220606.png)
- 图形嵌入模块通过在目标节点的时间邻域(temporal neighbourhood)上执行聚合来计算目标节点的嵌入。在上面的图中，当计算节点 1 在时间$t$（$t$比$t_{2},t_{3},t_{4}$大，比$t_{5}$少）的Embedding的时候，节点的时间邻域只包含时间$t$之前出现的边。因此，节点5的边不参与计算，因为它是在将来发生的。相反，嵌入模块从相邻节点2、3和4的`features(v)`和`memory(s)`以及边的特征进行聚合，以计算节点1的表示。实验中表现最好的图形嵌入模块是图注意力机制(temporal graph attention)，它可以根据邻居的内存、特征和交互时间(time of interaction)来判断哪些邻居是最重要的。  

- **简言之：**: 如果直接用memory来表示节点的信息，如果这个节点长时间不活动，会出现内存过时的问题，所以聚合一下邻居的信息，来生成这个节点的embedding。

> [!IMPORTANT] Embedding模块用来生成节点$i$在时间$t$的时间嵌入$z_{i}(t)$
> $$\mathbf{z}_i(t)=\mathrm{emb}(i,t)=\sum_{j\in\mathcal{N}_i^k([0,t])}h\left(\mathbf{s}_i(t),\mathbf{s}_j(t),\mathbf{e}_{ij},\mathbf{v}_i(t),\mathbf{v}_j(t)\right)$$
> 
> 其中，$h$是一个可学习函数，可以以多种方式实现

1. `Identity(id)`: 直接用内存作为节点嵌入$$emb(i, t)=s_{i}(t)$$
2. `Time projection(time)`: $$\operatorname{emb}(i,t)=(1+\Delta t\mathbf{w})\circ\mathbf{s}_i(t)$$其中$w$是可学习参数，$\Delta t$是与上一次交互间隔时间，$\circ$表示向量点乘
3. `Temporal Graph Attention(attn)`
   
4. `Temporal Graph Sum(sum)`
   