
> Rongze Tang
> Beijing Institute of Technology


# 1 Abstract

In mathematical economics, the **Arrow–Debreu model**[^1] is a theoretical general equilibrium  model. It posits that under certain economic assumptions (convex preferences,perfact and demand independence) there must be a set of prices such that aggregate supplies will equal aggregate demands for every commodity in the economy.Kamal Jain and others[^2] provide the first polynomial time exact algorithm for computing an Arrow-Debreu market equilibrium for the case of linear utilities.Here, we first outline the general background of the study, then explain and analyse in depth the specific algorithms proposed by Kamal Jain and others and their effects, and finally summarise the work done by them and its significance.

# 2 Introduction

A French economists, Leon Walras, in 1874  formulated one model for an unresolved issue, every person in an entire population has an initial endowment of divisible goods. Furthermore, every person in the population has a utility function for consuming goods. Every person sells the initial endowment and then buys an optimal bundle of goods with the entire revenue i.e., the market clears. Walras wondered whether a price can be assigned to every good so that this is possible. Such a price vector, if exist, is called general market equilibrium. An answer was given by two Nobel Laureates Kenneth Arrow and Gerard Debreu in 1954 . They showed that when the utility functions are concave then under some mild conditions a general market equilibrium always exist. Their proof is non-constructive and does not suggest any polynomial time algorithm to find a general market equilibrium.
在过去的很多年里，一些学者对Walras的模型进行了研究，他们提出了一些建设性方案，利用Lemke 法、牛顿法、初等二元法、凸编程和其他各种数值优化技术开发了许多启发式算法。同时，有的学者也提出了一些在复杂约束下的多项式时间算法。突破性的，Kamal Jain and others propose a mathematical program for the Walras model for the case of linear utilities,they show that the program is valid for non-linear utilities too. What's more, the program is simple and does not have complicated constraints like “optimality of the bundles purchased” and “money spent equals to money earned”. Instead these constraints follow from the feasibility of the program.At the same time, they show that all the general market equilibria are feasible points of this convex program and viceversa, hence, a general market equilibria can be obtained using ellipsoid method and simultaneous diophantine approximation.这引出了两条定理，我们将在xxxx中详细说明。
在第三节中，我们首先将给出上文所提到模型的具体定义，
*TODO*

# 3 Description of the model

There are n individuals in the system. Each of them has an initial endowment of some divisible good. In the case of linear utility, we can assume that each individual possesses only one item that is different from the items possessed by the others. Furthermore, we can assume that each individual has only one unit of the item.Each person also has a **linear utility function**. For $i-th$ person we denote this utility function by $\sum_ju_{ij}x_{ij}$, where $x_{ij}$ is the amount of item $j$ consumed by $i$. To be able to keep full precision in digital computers we assume that each $u_{ij}$ is an integer. Each person maximizes her utility by buy-ing an optimal bundle of items with the revenue made by selling her own endowment. 

The classical Arrow-Debreu [^1] theorem says that there is a price vector$(p_1, p_2, ··· , p_n)$, not all equal to zero,such that the buying and selling can be done at the prices in $(p_1, p_2, ··· , p_n)$ in such a way that the market clears. This price vector is called **general market equilibrium**.

Here we have a few more assumptions that are no less general-ity,we assume that everybody likes something, that is for every $i$ there is a $j$ such that $u_{ij} > 0$. If somebody does not like anything then the price of his good can be anything and he can be given any bundle. Again without loss of generality we assume that every item is liked by somebody, that is for every $j$ there is a $i$ such that $u_{ij} > 0$. If some good is not liked by any body then its price must be **zero**. 

# 4 Presentation and Solution of Non-Convex Programs

We begin this section by giving an assumption, called **Assumption 1**. 

 **Assumption 1** We assume that for every subset S that is neither empty nor contains everyone, there is a person i other than S who likes some item owned by S, i.e., for some $i ∈ S$ and some $j ∈ S$, $u_{ij} > 0$ (implying that everyone likes something). This assumption implies that **all equilibrium prices are non-zero**. If not, then think of S as the set of people who own zero-price goods. Then, someone other than S will make an infinite demand for the good owned by S.We will give a proof of this assumption after the account of the Convex Programs.
 **Non-Convex Programs**:Kamal Jain and others gives Non-Convex Programs as follow:
 $$\begin{aligned}
&\forall j: \sum_{i}x_{ij}=1 \\
&\forall i,j: x_{ij}\geq0 \\
&\forall i,j: \frac{u_{ij}}{p_j}\leq\frac{\sum_ku_{ik}x_{ik}}{p_i} \\
&\forall i: p_{i}>0& \text{(1)} 
\end{aligned}$$


The first two lines of the programme indicate that $x_{ij}$ is a feasible allocation (the sum is one and none of the elements is less than zero). The third line indicates that i has the highest utility of the good purchased by spending pi (which is his income). The fourth line indicates that the price is not zero. The Arrow-Debreu theorem only guarantees that at least one price is non-zero, but our *Assumption1* earlier in this section make all prices non-zero.

Immediately after, Kamal Jain and others presented the first theorem on the programs(In the section of non-linear utility case, we will show that the theorem 1 still holds at section 6):

**Theorem 1** The feasible region of non-convex program 1 has all and only general market equilibria.
**Proof** It is clear that all the market equilibria satisfy the program. So we only need to show that any feasible point is a market equilibrium. Line 3 of the program, when multiplied with $x_{ij}p_j$ add these inequalities for all $j$ gives:
 $$\forall i:\:\sum_ju_{ij}x_{ij}\leq\frac{\sum_ku_{ik}x_{ik}}{p_i}\sum_jx_{ij}p_j$$
Note that our assumption that everybody likes something implies that $\sum_ku_{ik}x_{ik}$ is not zero. So the inequality above after a simplification gives:
$$\forall i:\:p_i\leq\sum_jx_{ij}p_j$$
When we add these inequalities for all $i$ and interchange the order of summation on the right
hand side we get:
$$\sum_ip_i\leq\sum_jp_j\sum_ix_{ij}$$
Note that the second summation on the right hand side is 1(*Line1*),
so we get:
$$\sum_ip_i\leq\sum_jp_j$$
This should have been an equality. Which means that **all the inequalities added to obtain this must have been equalities**. This implies two facts, which we are writing as lemmas 

**Lemma 2** Every feasible point of the non-convex program1 satisfies the constraint of money earned equals to money spend for every user.

**Lemma 3** Every feasible point of the non-convex program1 satisfies that the money of every person is spent optimally. In other words whenever $x_{ij} >$, the corresponding constraint on the third line of the program is tight.

Now, we will solve the above Non-Convex Program 1.Note that the third line of non-convex program 1 is useful only when uij > 0. So we can rewrite the third line as:
$$\forall i,j\text{ such that }u_{ij}>0: \frac{p_i}{p_j}\leq\frac{\sum_ku_{ik}x_{ik}}{u_{ij}}$$

Next up is what I think is the best part of this proof, Kamal Jain and others construct a directed graph$G$, with the $n$ persons as the set of vertices. Then we draw an edge from $i$ to $j$ when  $u_{ij}>0\left(i\text{ and }j\text{ may be the same vertex in that case}\right.$ the edge is a loop). We assign two kinds of weight to each edge, $ij.$ The first is denoted by $w$ and the second is denoted by $LOGw.$ For an edge from $i$ to $j,w(ij)=\frac{\sum_ku_{ik}x_{ik}}{u_{ij}}$ and $LOGw( ij)$ = $\log ( w( ij) ) .$ By Farkas lemma, non- convex program 1 is feasible if and only if the product of $w_{ij}$ is at least one over any cycle of the graph, $G.$ In other words we have the following theorem:

**Theorem 4** Non-convex program1 is feasible if and only if there is no negative cycle in G with respect to the weight function, $LOGw$.

It tells us when an assignment is an equilibrium assignment. A flow is minimum cost if there is no neg
ative cycle. Similarly, an assignment of goods is an equilibrium solution if there is no negative cycle.
The theorem also gives the following convex program for the general equilibrium problem, which again makes it a functional theorem for computation.
$$\begin{aligned}
&\forall j: \sum_{i}x_{ij}=1 \\
&\forall i,j: x_{ij}\geq0 \\
&\text{For every cycle, }C,\text{ of }G : \prod_{ij\in C}w(ij)\geq1& \text{(2)} 
\end{aligned}$$
Using the usual inequality of the arithmetic mean is at least the geometric mean, the last set of inequalities can also be converted into an infinite number of linear equalities as follows.
$$\begin{aligned}
&\forall j: \sum_ix_{ij}=1 \\
&\forall i,j: x_{ij}\geq0 \\
&\text{For every cycle, }C,\text{of }G\text{ and for every }\alpha: \\
&\frac{1}{|C|}\sum_{ij\in C}\frac{w(ij)}{\alpha_{ij}}\geq(\frac{1}{\prod_{ij\in C}\alpha_{ij}})^{\frac{1}{|C|}}& \text{(3)} 
\end{aligned}$$
,where we denote by α a vector of non-negative real numbers. A subscripted α will denote a coordinate of α.From this we can derive the following lemma:

**Lemma 5** Convex program 2 is equivalent to linear program 3.

And tow important corollaries are able to be provided,detailed proofs will be given at **xxx**

**Corollary 6** Ellipsoid algorithm finds a market equilibrium in polynomial time.
**Corollary 7** The set of all possible assignments of goods to people ($x_{ij}$  variables) at equilibria is convex

In terms of using elliptic algorithms, the linear program 3 has no advantage over the convex program 2. However, linear programs are useful for designing primal-dual algorithms. When designing elementary-binary algorithms, one should not worry about the infinite size of linear programs. In the past, linear programs of exponential size have been used to design elementary-binary algorithms. An ingenious primal-dual algorithm uses only a polynomial number of binary variables. Convex Program 2 is exponentially large and would be infinite in size if it were converted to a linear program
Therefore, Convex Program 2 is not suitable for developing more efficient interior point methods. Kamal Jain and others will give us hope for developing interior point methods by developing a new polynomial size convex program in the next section.

# 5 Equivalent Convex Program for Non-convex Program 1

We just need to write the third line in the nonconvex program 1 for only those $i$ and $j$'s for which $u_{ij}>$ 0. Further note that this implies that$\sum_ku_{ik}x_{ik}>0.$ We already have that $p_i,p_j>0.$ So we can take the $\log$ of the whole inequalities to get:

$$\forall i,j \text{ such that } u_{ij}>0:\log(p_i)-\log(p_j)\leq\log(\frac{\sum_ku_{ik}x_{ik}}{u_{ij}})$$

We substitute every $\log(p_i)$ with a new variable $LOGp_i.$,then get:
$$\forall i,j \text{ such that } $u_{ij}>0:LOGp_{i}-LOGp_{j}\leq\log(\frac{\sum_{k}u_{ik}x_{ik}}{u_{ij}})$$
Note that $\log$ is a concave function i.e., $\log(\frac{x+y}2)$ $\geq$ $\frac{\log(x)+\log(y)}{2}.$ This means that if two feasible point satisfy the above inequality then their average will also satisfy the inequality. So the equivalent convex program4 we get for the non-convex program 1 is:
$$\begin{aligned}
&\forall j:\:\sum_{i}x_{ij}=1\\
&\forall i,j:\:x_{ij}\geq0\\
&\forall i,j\text{ such that }u_{ij}>0\\
&LOGp_i-LOGp_j\leq\log(\frac{\sum_ku_{ik}x_{ik}}{u_{ij}})\quad(4)\\
\end{aligned}$$
From the above discussion, we can easily get the following two points:
**Theorem 8** Non-convex program 1 is equivalent to convex program 4.

**Corollary 9** The set of all possible equilibria prices,on a logarithmic scale ($LOG_{pi}$) is convex.

So far, we have illustrated the Convex Program and Non-convex Program of Kamal Jain and others along with their solutions and some theorems,lemmas and so on. Next, we will go beyond the assumptions mentioned in section4 and give a more general case(i.e.Non-linear utilities).

# 6. Applicability of the programs in the general case

In section4 we have metioned the *Assumption 1* that for every proper subset, S, of persons there is a 
$i ∈ S$ and $j ∈ S$ such that $u_{ij} > 0$.We first prove the correctness of this assumption and show that even without it, there exists an equilibrium that contains only nonzero prices. Thus, the convex program4 remains valid and gives all such equilibria.

We draw the non-zero liking graph of the problem. This graph has a node for every person in the economy. There is a directed edge from $i$ to $j$ whenever $u_{ij}>0.$ If $i$ and $j$ are the same then we put a loop on $i.$ If this graph is disconnected, i.e., there is a proper subset $S$, such that there is no edge between $S$ and $\bar{S}$(S complement), then $S$ and $\bar{S}$ can be considered separate economies. One can write the convex programs of two separate economies together and call it a convex program for the joint economy. So we assume that the graph is connected.

If the graph is strongly connected then it satisfies the assumption and we finish the proof. Else we compute the strongly connected component decomposition of the graph. First, write the convex program for the equilibria of each component. For each component we know that equilibria prices are all non-zero. Now consider the underline acyclic structure on the strongly connected components. We say that a component, $S_{1}$, is lower than another component, $S_{2}$, if there is an edge from $S_1$ to $S_2.$ Take the transitive closure of this lower relation. This will be a partial order. Again denote it by lower. Note that if $S_{1}$ is lower than $S_{2}$ then $S_{2}$ is not lower than $S_1.$ Hence if the goods in $S_1$ are non-zero priced then they can't move from $S_1$ to $S_2.$ On the other hand if goods are heavily priced in $S_2$ then they can't move from $S_2$ to $S_{1}$ either. So we find non-zero equilibria for each component. If $S_1$ is lower than $S_2$ then we scale up the prices in $S_{2}$ by a huge number so that every person in $S_1$ likes something in $S_{1}$ in comparison with anything in $S_{2}.$ Hence all the prices are non-zero. For all such equilibria vectors we can write the convex program 4. In case one wants to allow zero-prices then note that only a lower ideal can have zero prices. So take any lower ideal put the zero prices for these. For rest of the economy write the convex-program 4.

Next, Kamal Jain and others explore the case when the utility functions are **non-linear but concave**. We assume that the utility functions are differentiable Let $u_i(x_i)$ be the utility function of $i$,where $x_i$ is her consumption vector.We assume that $u_i$ is concave, i.e.,
$$\frac{u_i(x_i)+u_i(y_i)}2\leq u_i(\frac{x_i+y_i}2),$$
for every consumption vectors $x_i$ and $y_i.$ Let $u_{ij}(x_i)$ be the partial derivative of $u_i$ at point $x_i$ with respect to the consumption of $j^\mathrm{th}$ good (consumption of $j^\mathrm{th}$ good by $i^\mathrm{th}$ person is denoted by $x_ij.).$ Now replace the $u_ij$ in the non-convex program 1 by $u_{ij}(x_i)$ (where $x_i=$ $(x_{i1},x_{i2},\cdots,x_{in}).$ For brevity, $u_ij(x_i)$ is written as $u_ij$, . Now we claim that the non-convex program l is valid for the nonlinear utility's case too.The proof given is as follow:

**Theorem 10** The feasible region of non-convex program 1has all and only general market equilibria even if utilities are general differentiable concave functions.

**Proof** First, determine a price vector. At this price, anything a person might buy is a convex set. However, this person will buy the set of goods that maximizes his or her utility. Since the utility function is concave, any local minimum will also be a global minimum. The condition for a local minimum is simply that the marginal utility per unit of additional money is the same for all consumer goods, and no other good has a greater marginal utility.

In the linear case, the constraints in the third line are obvious and represent the optimal case. This time, we need to make use of the additional fact that in equilibrium "money earned equals money spent". We know that the marginal utility per unit of money is the same for every $i$ as long as $x_{ij}$ > 0, that is, the quantity $\frac{u_{ij}}{P_j}$ is the same for every $i$ as long as $x_{ij} > 0$.Since $x_{ij} > 0$, we can say that $\frac{x_{ij}u_{ij}}{x_{ij}p_{j}}$ is the same. Add all the numerator and denominator together and note that the denominator is pi by “money earned equal to money spent” constraint,this shows that the non-convex program 1 remains valid.

# 7 Portfolio Characterization and Positive Characterization of Equilibrium in the Fisher Model

We note that the algorithms in this paper are neither combinatorial nor strongly polynomial. But convex programming reveals the basic structure of the problem and helps us understand it. As in convex programming4 , it leads to efficient practical algorithms using the interior point method [^3]. As shown in Theorem 4, the convex programming in this paper also brings a combinatorial characterization of equilibrium points. This combinatorial characterization, while revealing the structure of the problem, does not tell us how to fix the negative loop when it is found, whereas in the least-cost flow problem, the negative loop will tell us how to reduce the cost of the flow.

The combinatorial characterization of the Fisher model can be obtained using the linear programming model of Eisenberg-Gale [^4], and this characterization may help in the development of combinatorial algorithms that are strongly polynomial or strongly polynomial-time algorithms. The following theorem is an active characterization of equilibrium in the Fisher model, providing a specific way to determine whether an allocation is in equilibrium and indicating how to fix allocations that are not. This is in contrast to the passive characterization discussed previously; the theorem gives an active approach that not only tells us when an allocation is not in equilibrium, but also provides a way to fix it.

**Theorem 11** Consider an assignment $x_ij$'s from goods to buyers. $x_{ij}$ is an equilibrium if and only if there does not $existagoodjandtwobuyersiandi^{\prime}suchthatihasa$ non-zero quantity of good j and when i gives a sufficiently small but non-zero quantity of good j to i' then the prod- $uct\textit{of}U_{i}^{m_{i}}U_{i^{\prime }}^{m_{i^{\prime }}}$ increases, where $U_i$ and $U_i^{\prime}$ are the utili- $tiesofiandi'andm_{i}andm_{i'}aretheirinitialendowments$ $ofmoney.$

**Forward proof**

Assuming that $x_{ij}$ is an equilibrium allocation, it follows immediately from the Eisenberg-Gale linear programming model that there exists no good $j$ and two buyers $i$ and $i^{\prime}$, such that $i$ owns a nonzero quantity of $j$ and that the product of utilities  when $i$ gives some nonzero but very small amount of $j$ to $i^{\prime}$ is $\frac{\dot{U}_i}{m_i}\frac{U_{i^{\prime}}}{m_{i^{\prime}}}$ increases.

**Reverse proof**

Assuming that the allocation $x$ is not an equilibrium, and letting $x^*$ be an equilibrium allocation, Eisenberg-Gale's objective function has a higher value at $x^*$ than at $x$. Consider a straight line segment from $x$ to $x^*$, where the value of the Eisenberg-Gale objective function is strictly higher at any point on the line than at 0, and hence the derivative at 0 is positive. Writing this as a bipartite graph with weights and proving it by construction yields that there exists a bipartite graph with at least one positive weight placement, which implies that the aspects can be adjusted to achieve equilibrium.

In summary, the theorem is proved。

# 8.Generalized convex feasibility testing algorithm via ellipsoid and simultaneous diophantine approximation

在这部分，Kamal Jain and others推广了Grotschel、Lovasz和Schrijver的《几何算法与组合优化》[^5]中的定理6.4.1。原定理解决了通过强分离Oracle检测良好描述的多面体的非空问题，表明其可在Oracle-多项式时间内解决。然而，这一假设对某些凸规划（如Eisenberg-Gale的凸规划）不适用。


[^1]:Arrow, K.J., & Debreu, G. (1954). EXISTENCE OF AN EQUILIBRIUM FOR A COMPETITIVE ECONOMY. _Econometrica, 22_, 265.
[^2]: K. Jain, "A polynomial time algorithm for computing an Arrow-Debreu market equilibrium for linear utilities," 45th Annual IEEE Symposium on Foundations of Computer Science, Rome, Italy, 2004, pp. 
[^3]:Y. Ye. A Path to the Arrow-Debreu Competitive Market Equilibrium. Manuscript made public in 2004.
[^4]:E. Eisenberg and D. Gale. Consesus of subjective probabilities: The pari-mutuel method. Annals of Mathematical Statistics, 30:165-168, 1959.
[^5]:M. Grotschel, L. Lovasz, and A. Schrijver. Geometric Algorithms and Combinatorial Optimization, Second corrected edition, Springer Verlag Berlin Heidelberg, 1993.