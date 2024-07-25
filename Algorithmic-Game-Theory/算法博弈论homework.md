## 1. Prove that Rock-Paper-Scissors game has a unique Nash equilibrium, which is uniform over these three actions.

**Step 1: Define the Strategies**

Assume both players use mixed strategies, where each player chooses Rock, Paper, or Scissors with probabilities $p$, $q$, and $1−p−q$, respectively.

**Step 2: Calculate Expected Payoffs**

For Player A, let the probabilities of choosing Rock, Paper, and Scissors be $p_1$, $p_2$, and $p_3$ (where $p_1 + p_2 + p_3 = 1$). Similarly, let Player B's probabilities be $q_1$, $q_2$, and $q_3$ (where $q_1 + q_2 + q_3 = 1$).

The expected payoff for Player A choosing Rock is:
$$E_A(R) = R \cdot q_1 + S \cdot q_2 + P \cdot q_3$$

Since the game is zero-sum, Player A’s expected payoffs for choosing Paper and Scissors can be similarly calculated.

**Step 3: Equilibrium Condition**

For a mixed strategy to be a Nash equilibrium, the expected payoffs for Player A’s choices must be equal:
$$R \cdot q_1 + S \cdot q_2 + P \cdot q_3 = S \cdot q_1 + P \cdot q_2 + R \cdot q_3 = P \cdot q_1 + R \cdot q_2 + S \cdot q_3$$

Simplifying these equations, we get:
$$q_1 = q_2 = q_3$$

**Step 4: Uniform Strategy**

Since $q_1 + q_2 + q_3 = 1$ and $q_1 = q_2 = q_3$, we find:
$$3q_1 = 1$$
$$q_1 = \frac{1}{3}$$

Thus, the uniform strategy for each player is to choose Rock, Paper, and Scissors each with a probability of $\frac{1}{3}$.

From the above proof, we conclude that in the Rock-Paper-Scissors game, the unique Nash equilibrium is for each player to randomly choose Rock, Paper, and Scissors with equal probabilities of $\frac{1}{3}$. This strategy ensures that no player has an incentive to unilaterally change their strategy, resulting in an equilibrium.

## 2. Prove that if a finite game admits a potential function then it has at least one pure equilibrium.

Let $\Phi$ be the potential function of the game. Since the game has a finite number of states, there exists a state $s$ for which $\Phi$ is minimized.
Let $s^\prime$ be any other state of the game that differs from $s$ only in the strategy of a single player $i$. We have that $\Phi(s^\prime) \geq \Phi(s)$.
By the definition of the potential function, we obtain $\mathrm{cost}_i(\mathbf{s}^\prime) \geq \mathrm{cost}_i(\mathbf{s})$.
Since this holds for every player, $s$ must be an equilibrium.

## 3. Please give the statement of Myerson’s Lemma and prove it.

1. An allocation rule $\mathbf{x}$ is implementable if and only if it is monotone.
2. For every allocation rule $\mathbf{x}$, there exists a unique payment rule $\mathbf{p}$ such that $(\mathbf{x}, \mathbf{p})$ is a truthful auction.

Fix a bidder $i$, and the bids $\boldsymbol{b}_{-i}$ of the other bidders. Given that these quantities are now fixed, we simplify our notation:
$$\begin{aligned}
&- x(z) = x_i(z,\boldsymbol{b}_{-i}) \\
&- p(z) = p_i(z,\boldsymbol{b}_{-i}) \\
&- u(z) = u_i(z,\boldsymbol{b}_{-i})
\end{aligned}$$

### The Proof of 1:

Consider two bids $0 \leq z < y$ and assume $x$ is implementable by $p$.

True value $= z$, deviating bid $= y$:
$$u(z) \geq u(y) \Leftrightarrow z \cdot x(z) - p(z) \geq z \cdot x(y) - p(y)$$
$$\Leftrightarrow p(y) - p(z) \geq z \cdot (x(y) - x(z))$$

True value $= y$, deviating bid $= z$:
$$u(y) \geq u(z) \Leftrightarrow y \cdot x(y) - p(y) \geq y \cdot x(z) - p(z)$$
$$\Leftrightarrow p(y) - p(z) \leq y \cdot (x(y) - x(z))$$

Combining these two, we get:
$$z \cdot (x(y) - x(z)) \leq p(y) - p(z) \leq y \cdot (x(y) - x(z))$$

This also implies that:
$$(y - z) \cdot (x(y) - x(z)) \geq 0$$

Since $0 \leq z < y$, this is possible if and only if $x$ is monotone so that $y - z \leq 0$ and $x(y) - x(z) \leq 0$.

1 is now proved.

### The Proof of 2:

We can now assume that $\mathbf{x}$ is monotone.

Assume $\mathbf{x}$ is piecewise constant, like in sponsored search auctions.

The break points are defined by the highest bids of the other bidders:
$$z \cdot (x(y) - x(z)) \leq p(y) - p(z) \leq y \cdot (x(y) - x(z))$$

By fixing $z$ and taking the limit as $y$ tends to $z$, we have that the jump of $p$ at $z$ is $z \cdot$ (jump of $x$ at $z$).

Therefore, we can define the payment of the bidder as:
$$p(b) = \sum_{y \in [0,b]} y \cdot (\text{jump of } x \text{ at } y)$$

where $y$ enumerates all break points of $x$ in $[0,b]$.

## 4. Please give a complete proof of the $1/\sqrt{m}$-approximate mechanism of the single-minded auction.

#### Problem Definition

In a single-minded auction, we have:
- $m$ items.
- $n$ bidders.
- Each bidder $i$ has a value $v_i$ for a specific subset of items $S_i \subseteq \{1, 2, \ldots, m\}$.
- The goal is to allocate items to maximize the total value, i.e., $\sum_{i \in W} v_i$ where $W$ is a set of winning bidders such that their demanded subsets do not overlap.

#### Mechanism Outline

The mechanism is a greedy algorithm that sorts bidders by their value-to-size ratio $v_i / \sqrt{|S_i|}$ and then iteratively allocates items to the highest-ranked bidder whose subset is still available.

### Proof:

1. **Optimal Social Welfare $OPT$**:
   - Let $OPT$ be the optimal social welfare, i.e., the maximum sum of values from a feasible allocation of items.
   - Let $W^*$ be the set of winning bidders in the optimal solution.

2. **Greedy Algorithm**:
   - Sort the bidders $i$ by $v_i / \sqrt{|S_i|}$ in decreasing order.
   - Initialize an empty set $W$ for the winners.
   - Iterate through the sorted list of bidders:
     - For each bidder $i$, if $S_i$ does not overlap with any subset $S_j$ for $j \in W$, add $i$ to $W$.

3. **Analysis**:
   - Let $W_G$ be the set of winners chosen by the greedy algorithm.
   - For each bidder $i \in W_G$, we have that $v_i / \sqrt{|S_i|}$ is at least as large as $v_j / \sqrt{|S_j|}$ for any $j$ considered after $i$ in the greedy order.

4. **Comparing Greedy to Optimal**:
   - Consider the social welfare obtained by the greedy algorithm, $SW_G = \sum_{i \in W_G} v_i$.
   - Consider the social welfare of the optimal solution, $SW_{OPT} = \sum_{i \in W^*} v_i$.

5. **Bounding the Approximation Ratio**:
   - Let $|S_i|$ denote the size of the subset of items requested by bidder $i$.
   - The value-to-size ratio used by the greedy algorithm ensures that for any $i \in W_G$, the following holds:
     $$
     v_i \geq \frac{v_j \cdot \sqrt{|S_i|}}{\sqrt{|S_j|}}
    

 $$
     for any $j \in W^*$.
   - Sum this inequality over all $i \in W_G$ and $j \in W^*$:
     $$
     \sum_{i \in W_G} v_i \geq \sum_{j \in W^*} v_j \cdot \sum_{i \in W_G} \frac{\sqrt{|S_i|}}{\sqrt{|S_j|}}
     $$

6. **Bounding the Sum of Ratios**:
   - Notice that the number of items allocated to any subset $S_i$ is at most $m$, hence $\sum_{i \in W_G} |S_i| \leq m$.
   - Using Cauchy-Schwarz inequality:
     $$
     \sum_{i \in W_G} \sqrt{|S_i|} \leq \sqrt{|W_G| \cdot \sum_{i \in W_G} |S_i|} \leq \sqrt{|W_G| \cdot m}
     $$

7. **Final Approximation Bound**:
   - Combine these results:
     $$
     SW_G \geq \sum_{j \in W^*} v_j \cdot \frac{\sum_{i \in W_G} \sqrt{|S_i|}}{\sqrt{m}} \geq \frac{SW_{OPT} \cdot \sqrt{|W_G|}}{\sqrt{m}}
     $$
   - Since $|W_G| \leq m$ we get:
     $$
     SW_G \geq \frac{SW_{OPT}}{\sqrt{m}}
     $$

Thus, the greedy algorithm provides a $1/\sqrt{m}$-approximation to the optimal social welfare in a single-minded auction. This completes the proof.

## 5. Please give a complete proof of Arrow’s Impossibility Theorem.

We will assume that $W$ is both PE and IIA, and show that $W$ must be dictatorial. Our assumption that $|O| \geq 3$ is necessary for this proof. The argument proceeds in four steps.

### Step 1: If every voter puts an outcome $b$ at either the very top or the very bottom of his preference list, $b$ must be at either the very top or very bottom of $\succ_W$ as well.

Consider an arbitrary preference profile $[\succ]$ in which every voter ranks some $b \in O$ at either the very bottom or very top, and assume for contradiction that the above claim is not true. Then, there must exist some pair of distinct outcomes $a, c \in O$ for which $a \succ_W b$ and $b \succ_W c$.

Now let's modify $[\succ]$ so that every voter moves $c$ just above $a$ in his preference ranking, and otherwise leaves the ranking unchanged; let's call this new preference profile $[\succ^\prime]$. We know from IIA that for $a \succ_W b$ and $b \succ_W c$ to change, the pairwise relationship between $a$ and $b$ and/or the pairwise relationship between $b$ and $c$ would have to change. However, since $b$ occupies an extremal position for all voters, $c$ can be moved above $a$ without changing either of these pairwise relationships. Thus, in profile $[\succ^\prime]$, it is also the case that $a \succ_W b$ and $b \succ_W c$. From this fact and from transitivity, we have that $a \succ_W c$. However, in $[\succ^\prime]$, every voter ranks $c$ above $a$ and so PE requires that $c \succ_W a$. We have a contradiction.

### Step 2: There is some voter $n^*$ who is extremely pivotal in the sense that by changing his vote at some profile, he can move a given outcome $b$ from the bottom of the social ranking to the top.

Consider a preference profile $[\succ]$ in which every voter ranks $b$ last, and in which preferences are otherwise arbitrary. By PE, $W$ must also rank $b$ last. Now let voters from 1 to $n$ successively modify $[\succ]$ by moving $b$ from the bottom of their rankings to the top, preserving all other relative rankings. Denote as $n^*$ the first voter whose change causes the social ranking of $b$ to change. There clearly must be some such voter: when the voter $n$ moves $b$ to the top of his ranking, PE will require that $b$ be ranked at the top of the social ranking.

Denote by $[\succ^1]$ the preference profile just before $n^*$ moves $b$, and denote by $[\succ^2]$ the preference profile just after $n^*$ has moved $b$ to the top of his ranking. In $[\succ^1]$, $b$ is at the bottom in $\succ_W$. In $[\succ^2]$, $b$ has changed its position in $\succ_W$, and every voter ranks $b$ at either the top or the bottom. By the argument from Step 1, in $[\succ^2]$, $b$ must be ranked at the top of $\succ_W$.

### Step 3: $n^*$ (the agent who is extremely pivotal on outcome $b$) is a dictator over any pair $ac$ not involving $b$.

We begin by choosing one element from the pair $ac$; without loss of generality, let's choose $a$. We'll construct a new preference profile $[\succ^3]$ from $[\succ^2]$ by making two changes. First, we move $a$ to the top of $n^*$'s preference ordering, leaving it otherwise unchanged; thus $a \succ_{n^*} b \succ_{n^*} c$. Second, we arbitrarily rearrange the relative rankings of $a$ and $c$ for all voters other than $n^*$, while leaving $b$ in its extremal position.

In $[\succ^1]$, we had $a \succ_W b$, as $b$ was at the very bottom of $\succ_W$. When we compare $[\succ^1]$ to $[\succ^3]$, relative rankings between $a$ and $b$ are the same for all voters. Thus, by IIA, we must have $a \succ_W b$ in $[\succ^3]$ as well. In $[\succ^2]$, we had $b \succ_W c$, as $b$ was at the very top of $\succ_W$. Relative rankings between $b$ and $c$ are the same in $[\succ^2]$ and $[\succ^3]$. Thus, in $[\succ^3]$, $b \succ_W c$. Using the two above facts about $[\succ^3]$ and transitivity, we can conclude that $a \succ_W c$ in $[\succ^3]$.

Now construct one more preference profile, $[\succ^4]$, by changing $[\succ^3]$ in two ways. First, arbitrarily change the position of $b$ in each voter's ordering while keeping all other relative preferences the same. Second, move $a$ to an arbitrary position in $n^*$'s preference ordering, with the constraint that $a$ remains ranked higher than $c$. Observe that all voters other than $n^*$ have entirely arbitrary preferences in $[\succ^4]$, while $n^*$'s preferences are arbitrary except that $a \succ_{n^*} c$.

In $[\succ^3]$ and $[\succ^4]$, all agents have the same relative preferences between $a$ and $c$; thus, since $a \succ_W c$ in $[\succ^3]$ and by IIA, $a \succ_W c$ in $[\succ^4]$. Thus, we have determined the social preference between $a$ and $c$ without assuming anything except that $a \succ_{n^*} c$.

### Step 4: $n^*$ is a dictator over all pairs $ab$.

Consider some third outcome $c$. By the argument in Step 2, there is a voter $n^{**}$ who is extremely pivotal for $c$. By the argument in Step 3, $n^{**}$ is a dictator over any pair $\alpha\beta$ not involving $c$. Of course, $ab$ is such a pair $\alpha\beta$. We have already observed that $n^*$ is able to affect $W$'s $ab$ ranking—for example, when $n^*$ was able to change $a \succ_W b$ in profile $[\succ^1]$ into $b \succ_W a$ in profile $[\succ^2]$. Hence, $n^{**}$ and $n^*$ must be the same agent.

## 6. Prove the correctness of the LMM Algorithm.

#### Theorem

1.  (Liption et al.) For any $\epsilon \in (0,1)$, there exists an $\epsilon$-ANE where each player plays only $k = O(\log n / \epsilon^2)$ actions with positive probability.
2. (Chernoff Bound) Let $X_1, \ldots, X_m$ be $m$ random variables over $[0,1]$. For any $\epsilon > 0$ and $

X$ be the mean of $\{X_i\}_{i \in [m]}$, we have $\Pr[|X - \mathbb{E}[X]| \geq \epsilon] \leq 2\exp(-2m\epsilon^2)$.
3. (The Union Bound) $\Pr[A_1 \cup A_2] \leq \Pr[A_1] + \Pr[A_2]$

### Proof:

Let $(\mathbf{x}, \mathbf{y})$ be any NE of our instance.

Take $k$ i.i.d. samples (actions) $(r_1, \ldots, r_k)$ from the distribution $x$.

Let $\tilde{\mathbf{x}}$ be the “empirical” strategy which plays $r_i$ uniformly at random. Similarly with $\tilde{\mathbf{y}}.$

We will show, when $k$ is large enough, below could happen:

$$|\mathbf{e}_i^T R \mathbf{y} - \mathbf{e}_i^T R \mathbf{\tilde{y}}| \leq \epsilon / 2 \quad \text{and} \quad |\mathbf{x}^T C \mathbf{e}_j - \tilde{\mathbf{x}}^T C \mathbf{e}_j| \leq \epsilon / 2$$

where $i, j \in [n].$

If so, we have
$$\mathbf{e}_i^T R \tilde{\mathbf{y}} \leq \mathbf{e}_i^T R \mathbf{y} + \epsilon / 2 \leq \frac{1}{k} \sum_{i=1}^k \mathbf{e}_{r_j}^T R \mathbf{y} + \epsilon / 2 \leq \frac{1}{k} \sum_i \mathbf{e}_{r_j}^T R \tilde{\mathbf{y}} + \epsilon = \tilde{\mathbf{x}}^T R \tilde{\mathbf{y}} + \epsilon$$

We focus on a bad case that $|\mathbf{e}_i^T R \mathbf{y} - \mathbf{e}_i^T R \mathbf{\tilde{y}}| > \epsilon / 2$ for fixed $i$.

By Chernoff bound, we have (by setting $X_j = \mathbf{e}_i^T R \mathbf{e}_{r_j})$

$$\Pr[|\mathbf{e}_i^T R \mathbf{y} - \mathbf{e}_i^T R \mathbf{\tilde{y}}| > \epsilon / 2] \leq 2 \exp(-k \epsilon^2 / 2).$$

By the union bound, we have $2n$ bad cases, so the probability that any of the bad cases happens is at most $4n \exp(-k \epsilon^2 / 2)$. For $k > 2 \log(4n) / \epsilon^2$, the probability above is less than 1.

## 7. Prove the correctness of Lemke-Howson algorithm.

### 1. Definitions and Non-degeneracy

We start with definitions, considering a two-player game with payoff matrices $A_{m \times n}$ and $B_{m \times n}$. A strategy pair $(x, y)$ is a Nash equilibrium of the game $(A, B)$ if the following conditions hold:

$$\forall \: 1 \leq i \leq m, \: x_i > 0 \Rightarrow (A \boldsymbol{y})_i = \max_k (A \boldsymbol{y})_k$$
$$\forall \: m + 1 \leq j \leq m + n, \: y_j > 0 \Rightarrow (\boldsymbol{x}^T B)_j = \max_k (\boldsymbol{x}^T B)_k$$

To facilitate handling, we define non-degeneracy: a game $(A, B)$ is non-degenerate if, for any strategy $x$ and $y$, the size of the support sets meets specific conditions.

### 2. Polyhedral Representation

Next, we define two polyhedra $P$ and $Q$ that represent the strategy spaces for the two players:
$$P = \{(u, \boldsymbol{x}) \mid x_i \geq 0, \sum x_i = 1, \: \boldsymbol{x}^T B \leq u \cdot \mathbf{1}\}$$
$$Q = \{(v, \boldsymbol{y}) \mid y_j \geq 0, \sum y_j = 1, \: A \boldsymbol{y} \leq v \cdot \mathbf{1}\}$$

This can be simplified to:
$$\overline{P} = \{\boldsymbol{x} \mid x_i \geq 0, \: \boldsymbol{x}^T B \leq \mathbf{1}\}$$
$$\overline{Q} = \{\boldsymbol{y} \mid y_j \geq 0, \: A \boldsymbol{y} \leq \mathbf{1}\}$$

### 3. Vertices and Labels

We define the vertices (i.e., extreme points) of $P$ and $Q$ and introduce label sets $L(x)$ and $L(y)$ indicating the binding constraints for the corresponding strategies:
$$L(x) = \{i \mid x_i = 0\} \cup \{j \mid (x^T B)_j = 1\}$$
$$L(y) = \{j \mid y_j = 0\} \cup \{i \mid (A y)_i = 1\}$$

### 4. Graph Representation of Nash Equilibria

We define two graphs $G_1$ and $G_2$, with vertices representing the extreme points of the polyhedra $P$ and $Q$. Each vertex's label set $L(x)$ and $L(y)$ satisfies the following property:

**Theorem 3**: A strategy pair $(x, y)$ is a Nash equilibrium if and only if its label set satisfies $L(x) \cup L(y) = M \cup N$.

### 5. Lemke-Howson Algorithm

The algorithm steps are as follows:
1. Select a label $k \in M \cup N$.
2. Start from the initial state $(0, 0)$ and drop label $k$.
3. Check the current vertex's label set. If it satisfies the fully labeled condition (i.e., $L(x) \cup L(y) = M \cup N$), output the current vertex pair as the Nash equilibrium; otherwise, continue pivoting in the other polyhedron.

### 6. Proof of Correctness

The proof of the Lemke-Howson algorithm's correctness is based on two key theorems:

**Theorem 4**: For any label $k \in M \cup N$, every vertex in the graph $G$ (representing a strategy pair) has a degree of 1 (initial state and Nash equilibrium point) or 2 (other cases), meaning that every path's two endpoints are the initial state and a Nash equilibrium point.

**Proof**:
1. The initial state $(0, 0)$ and all Nash equilibrium points belong to the set $U_k$ and have a degree of 1 in the graph $G$.
2. Other vertices have a degree of 2.

Based on these theorems, we can demonstrate that the algorithm will always find a Nash equilibrium after traversing the path, and due to the existence and uniqueness of the path, the algorithm will terminate in a finite number of steps and output a Nash equilibrium.

### Conclusion

The Lemke-Howson algorithm alternates pivoting operations in the polyhedra $P$ and $Q$ to find fully labeled vertex pairs, thus finding a Nash equilibrium in a finite number of steps for non-degenerate two-player games. This proves the correctness of the Lemke-Howson algorithm.