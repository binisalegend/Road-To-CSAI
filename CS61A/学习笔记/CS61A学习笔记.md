# Lecture 3 : Control（函数控制）
## *HW01 : Variables & Functions, Control*
- 可以给函数重新命名，或者理解为将一个函数的功能赋给另一个函数
~~~python
from operator import add, sub  
  
def a_plus_abs_b(a, b):  
    """Return a+abs(b), but without calling abs."""
    if b >= 0:  
        h = add  
    else:  
        h = sub  
    return h(a, b)
~~~
- [ ] 这个理解不了一点，不知道那个with_if_statement干啥用的
~~~python
def if_function(condition, true_result, false_result):  
    """Return true_result if condition is a true value, and  
    false_result otherwise. 
    
    >>> if_function(True, 2, 3)
    2
    >>> if_function(False, 2, 3)
	3
	>>> if_function(3==2, 3+2, 3-2)
	1
	>>> if_function(3>2, 3+2, 3-2)    
	5
	"""    
	if condition:  
        return true_result  
    else:  
        return false_result  
  
  
def with_if_statement():  
    """  
    >>> result = with_if_statement()    
    47
    >>> print(result) 
    None
    """
    if cond():  
        return true_func()  
    else:  
        return false_func()  
  
def with_if_function():  
    """  
    >>> result = with_if_function()
	42
	47
	>>> print(result)    
	None    
	"""    
	return if_function(cond(), true_func(), false_func())  
  
def cond():  
    "*** YOUR CODE HERE ***"  
    return False  
def true_func():  
    "*** YOUR CODE HERE ***"  
    print(42)  
def false_func():  
    "*** YOUR CODE HERE ***"  
    print(47)
~~~
- def定义一个函数，如果给这个函数调用赋予变量名，系统只会打印定义该变量过程中的print，而不会返回return值，需要再次调用变量才会打印return；而如果不给函数调用赋予变量名，则视为直接计算函数值也会打印return值
~~~python
def hailstone(x):  
    print(x)  
    cnt = 1  
    while x != 1:  
        cnt += 1  
        if x % 2 == 0:  
            x = x // 2  
            print(x)  
        else:  
            x = x * 3 + 1  
            print(x)  
    return cnt
~~~
![[Pasted image 20230710114432.png]]
## *Lab01: Variables & Functions, Control*
- 一些OK常用语句：
	1. 在输出行前打“DEBUG:"可以避免误识别print内容
	2. `python3 ok -q sum_digits -i `和  `python3 ok -q sum_digits -trace`没弄清楚啥意思，再摸索摸索（bushi
	3. `python3 -q doctest <文件名>` 可以运行程序中的测试
- `for i in range n:` 语句表示从i到n-1，意思是包含i，但不包含n。字面意思，区分一下
# Lecture 4:Higher-Order Functions（高阶函数）
## *function example: sound*
- 利用python进行三角波的形成和输出、整合，验证高级函数实用性
~~~python
from wave import open  
from struct import Struct  
from math import floor  
  
frame_rate = 11025  
  
def encode(x):  
    """Encode float x between -1 and 1 as two bytes.  
	(See https://docs.python.org/3/library/struct.html)"""
	i = int(16384 * x)  
    return Struct('h').pack(i)  
  
def play(sampler, name='song.wav', seconds=2):  
    """Write the output of a sampler function as a wav file.  
    (See https://docs.python.org/3/library/wave.html) """ 
	out = open(name, 'wb')  
    out.setnchannels(1)  
    out.setsampwidth(2)  
    out.setframerate(frame_rate)  
    t = 0  
    while t < seconds * frame_rate:  
        sample = sampler(t)  
        out.writeframes(encode(sample))  
        t = t + 1  
    out.close()  
  
def tri(frequency, amplitude=0.3):  
    """A continuous triangle wave."""  
    period = frame_rate // frequency  
    def sampler(t):  
        saw_wave = t / period - floor(t / period + 0.5)  
        tri_wave = 2 * abs(2 * saw_wave) - 1  
        return amplitude * tri_wave  
    return sampler  
  
c_freq, e_freq, g_freq = 261.63, 329.63, 392.00  
  
def both(f,g):  
    return lambda t: f(t) + g(t)  
  
def note(f,start,end,fade=0.1):  
    def sampler(t):  
        seconds = t / frame_rate  
        if seconds < start:  
            return 0  
        elif seconds > end:  
            return 0  
        elif seconds < start + fade:  
            return (seconds - start) / fade * f(t)  
        elif seconds > end - fade:  
            return (end - seconds) / fade * f(t)  
        else:  
            return f(t)  
    return sampler  

def mario_at(octave):  
    c = tri(octave * c_freq)  
    e = tri(octave * e_freq)  
    g = tri(octave * g_freq)  
    low_g = tri(octave * g_freq / 2)  
    return mario(c, e, g, low_g)  
    
# c,e = tri(c_freq),tri(e_freq)  
# g,low_g = tri(g_freq),tri(g_freq/2)  
  
def mario(c, e, g, low_g):  
    z = 0  
    song = note(e, z, z + 1/8)  
    z += 1/8  
    song = both(song, note(e, z, z + 1/8))  
    z += 1/4  
    song = both(song, note(e, z, z + 1/8))  
    z += 1/4  
    song = both(song, note(c, z, z + 1/8))  
    z += 1/8  
    song = both(song, note(e, z, z + 1/8))  
    z += 1/4  
    song = both(song, note(g, z, z + 1/4))  
    z += 1/2  
    song = both(song, note(low_g, z, z + 1/4))  
    return song  
  
# play(both(note(c,0,1/4),note(e,1/2,1)))  
play(both(mario_at(1),mario_at(1/2)))  
  
  
# play(both(mario_at(1), mario_at(1/2)))
~~~
## *Function Composition*
~~~python
def make_adder(n):  
    def adder(k):  
        return k + n  
    return adder  
  
def square(x):  
    return x * x  
  
def triple(x):  
    return 3 * x  
  
def compose1(f,g):  
    def h(x):  
        return f(g(x))  
    return h
~~~
## *Function Currying*
[[#^2f1599]]  [[#^ecfc38]]
- 柯里化是一种将接受多个参数的函数转换为接受单个参数的函数序列的技术。
~~~python
#应用def函数进行currying
def curry2(f):  
    def g(x):  
        def h(y):  
            return f(x,y)  
        return h  
    return g
~~~
~~~python
#应用lambda函数进行currying
def curry1(f):
	return lambda x : lambda y : f(x,y)
~~~
## *HW02 : Higher-Order Functions*
- base和term()应用combiner算法进行计算时受到计算顺序的影响，不能任意调换顺序
- ！记得考虑特殊情况
~~~python
def accumulate(combiner, base, n, term):  
    """Return the result of combining the first n terms in a sequence and base. The terms to be combined are term(1), term(2), ..., term(n).combiner is a two-argument commutative function.
      
    >>> accumulate(add, 0, 5, identity)  # 0 + 1 + 2 + 3 + 4 + 5
	15    
	>>> accumulate(add, 11, 5, identity) # 11 + 1 + 2 + 3 + 4 + 5
	26    
	>>> accumulate(add, 11, 0, identity) # 11
	11    
	>>> accumulate(add, 11, 3, square)   # 11 + 1^2 + 2^2 + 3^2
	25    
	>>> accumulate(mul, 2, 3, square)    # 2 * 1^2 * 2^2 * 3^2
	72    
	>>> accumulate(lambda x, y: x + y + 1, 2, 3, square)
	19    
	>>> accumulate(lambda x, y: 2 * (x + y), 2, 3, square)
	58    
	>>> accumulate(lambda x, y: (x + y) % 17, 19, 20, square)
	16    
	"""    
	"*** YOUR CODE HERE ***"  
    if n != 0:  
        x, loc = 2, combiner(base,term(1))  
        while x <= n:  
            loc = combiner(loc, term(x))  
            x += 1  
        print(loc)  
    else:  
        print(base)
~~~
- [ ] 应用accumulate函数用print函数会多打印一个None，用return就没问题
~~~python
def summation_using_accumulate(n, term):  
    y = accumulate(add,0,n,term)  
    return y
	"""print(y)"""
~~~
- sub是减，mul是乘...
- 返回值可以是函数，在compose1函数中的f(x)调用可以不指明
- for循环中可以自动赋给未定义变量值为0，while循环不行
~~~python
def compose1(func1, func2):  
    """Return a function f, such that f(x) = func1(func2(x))."""  
    def f(x):  
        return func1(func2(x))  
    return f  
  
def make_repeater(func, n):  
    """Return the function that computes the nth application of func.  
  
    >>> add_three = make_repeater(increment, 3)    
    >>> add_three(5)    
    8    
    >>> make_repeater(triple, 5)(1) # 3 * 3 * 3 * 3 * 3 * 1
	243    
	>>> make_repeater(square, 2)(5) # square(square(5))
	625    
	>>> make_repeater(square, 4)(5) # square(square(square(square(5))))       152587890625    
	>>> make_repeater(square, 0)(5) # Yes, it makes sense to apply the function zero times!
	5    
	"""    
	"*** YOUR CODE HERE ***"  
    f = func  
    if n == 0:  
        return identity  
    for i in range(n-1):  
        f = compose1(func, f)  
    return f
~~~

# Lecture 5:Environment Diagrams（程序环境示意图）
## *Environments for Higher-Order Functions*
~~~python
def apply_twice(f,x):  
    return f(f(x))  
  
def square(x):  
    return x * x
~~~
## *Higher-Order Function Example:Repeat*
~~~python
def repeat(f,x):  
    while f(x) != x:  
        x = f(x)  
    return x  
  
def g(y):  
    return (y + 5) // 3
~~~
![[Pasted image 20230708150326.png]]
## *Environments for Nested Definitions*
![[Pasted image 20230708151420.png]]![[Pasted image 20230708151721.png]]
~~~python
def make_adder(n):  
    def adder(k):  
        return k + n  
    return adder
~~~
- 每一个创建的函数，它自身在哪个框架中创建，他的母函数就是那个框架的函数，在寻找变量值时，沿母函数层层向上搜寻知道全局框架，最先搜索到的值便是函数调用的值[[#^a02dcd]]
## *Local Names*
![[Pasted image 20230708214014.png]]
- 在嵌套定义中，母函数的形参可以在子函数中使用；而在相对独立的函数定义中一个函数无法找到和调用在另一个函数中定义的形参。
## *Lambda Expressions*
### 1. lambda表达式相关
![[Pasted image 20230708215032.png]]
- lambda表达式是一个计算结果可以用某种方式解释的函数的表达式，当square被定义为“x * x”时，square仅仅作为一个数值存在；而当square被定义为一个关于x的lambda函数，它变成了一个具有具体调用地址的函数（甚至可以不定义lambda返回函数的名称而直接赋予形参具体值）
- lambda：A function with formal parameter x that returns the value of "x * x"
- <font color = red><big>**No Return!!!**</big></font>
- 只能将单个表达式作为lambda函数的主体
### 2. lambda与def定义函数的区别
- 使用lambda定义时函数名为”lambda“形式的函数，而def语句定义函数名则为编程者赋予的函数名称，如下：
![[Pasted image 20230708220818.png]]
![[Pasted image 20230708220836.png]]
![[Pasted image 20230708221101.png]]
## *Self-Reference*
~~~python
def print_sums(x):  
    print(x)  
    def next_sum(y):  
        return print_sums(x + y)  
    return next_sum
~~~
![[Pasted image 20230709005548.png]]
![[Pasted image 20230709005813.png]]
- (好难解释md)第一次调用的参数是1->n,打印1，定义next_sum函数，调用3->k，这时第一次调用的print_sums函数返回next_sum函数，而next_sum函数返回print_sums(n+k-->1+3)，即返回print_sums(4)，然后先打印4...
## *Lab02: Higher-Order Functions, Lambda Expressions, Self Reference*
### Q1: WWPD Lambda the Free
- [ ] 这个是真整体不咋理解，感觉没明白函数定义和返回，让我们过会来求助一波chatGPT老师（bushi）
~~~python
>>> def cake():
...     print('beets') 
...     def pie():
...         print('sweets') 
...         return 'cake' 
...     return pie 
>>> chocolate = cake()
beets
>>> chocolate
Function
>>> chocolate()
sweets
'cake'
>>> more_chocolate, more_cake = chocolate(), cake
sweets
>>> more_chocolate
'cake'
>>> def snake(x, y): 
...     if cake == more_cake: 
...         return chocolate 
...     else: 
...         return x + y 
>>> snake(10, 20)
Function
>>> snake(10, 20)()
sweets
'cake'
>>> cake = 'cake' 
>>> snake(10, 20)
30
~~~
![[Pasted image 20230711220439.png]]
- 感觉这个和上面那个例子有点异曲同工，就是定义变量名并且调用函数就会返回return值，但变量名没任何用好像（）（啊看不懂看不懂学不明白烦死了）
~~~python
>>> onethousand = print_lambda(1000)
1000
>>> onethousand
>>>
>>> print_lambda
<function <lambda> at 0x000001752468AE60>
~~~
### Q3: Lambdas and Currying
- 哇！感觉头一次发现到lambda到底是干嘛用的（一直觉得是个摆设），暂时的理解是用来调用未定义的参数（def和lambda如下）
	1. 应用def调用：
	~~~python
		def lambda_curry2(func):  
			def function1(x):  
			    def function2(y):  
			        return func(x,y)  
			    return function2  
			return function1
	~~~
	2. 应用lambda调用：
	~~~python
		def lambda_curry2(func): 
		   return lambda x : lambda y : func(x , y)
	~~~ 
	^2f1599
### Q4: Count van Count
- 单纯觉得这个求质数的方法很有启发性，算是第一次让我对函数封装有了相对具体的认识吧...
	 就是先用count_factors函数计算出某个数的公约数，然后调用count_primes函数计算在n之内的所有质数的个数，其中调用is_prime函数利用count_factors函数判定是否符合质数条件（只有两个公约数）
~~~python
def count_factors(n): 
"""Return the number of positive factors that n has. 
>>> count_factors(6) 
4    # 1, 2, 3, 6 
>>> count_factors(4) 
3    # 1, 2, 4 
""" 
	i, count = 1, 0 
	while i <= n: 
		if n % i == 0: 
			count += 1 
		i += 1 
	return count 

def count_primes(n): 
"""Return the number of prime numbers up to and including n. 
>>> count_primes(6) 
3    # 2, 3, 5 
>>> count_primes(13) 
6    # 2, 3, 5, 7, 11, 13 
""" 
	i, count = 1, 0 
	while i <= n: 
		if is_prime(i): 
			count += 1
		i += 1 
	return count 

def is_prime(n): 
	return count_factors(n) == 2 # only factors are 1 and n
~~~
- 暂时粗浅理解一下函数式编程吧，就是主函数的返回值尽可能都是一个函数，而调用一个主函数定义中没有显示的参数就要应用def或者lambda语句调用
~~~python
    """Returns a function with one parameter N that counts all the numbers from 1 to N that satisfy the two-argument predicate function Condition, where the first argument for Condition is N and the second argument is the number from 1 to N.

    >>> count_factors = count_cond(lambda n, i: n % i == 0)
    >>> count_factors(2)   # 1, 2
    2
    >>> count_factors(4)   # 1, 2, 4
    3
    >>> count_factors(12)  # 1, 2, 3, 4, 6, 12
    6

    >>> is_prime = lambda n, i: count_factors(i) == 2
    >>> count_primes = count_cond(is_prime)
    >>> count_primes(2)    # 2
    1
    >>> count_primes(3)    # 2, 3
    2
    >>> count_primes(4)    # 2, 3
    2
    >>> count_primes(5)    # 2, 3, 5
    3
    >>> count_primes(20)   # 2, 3, 5, 7, 11, 13, 17, 19
    8
    """
def count_cond(condition):
    return lambda x: sum(1 for y in range(1, x+1) if condition(x, y))
#这种方式用lambda函数，将condition(x,y)作为参数传给lambda，lambda函数接收一个参数x，然后使用range(1, x+1)生成从1到x的数字，对于每个数字y，如果满足条件condition(x, y)，则计数加1。最后，返回计数结果的总和。

def count_cond(condition):
	def count_f(x):
		i,count = 1,0
		while i < x:
			if condition(x,i):
				count += 1
			i += 1
		return count
	return count_f
#这种方式用def定义函数(个人认为更好理解一点)，注意返回值还是要一个函数而不是直接count（报错：NoneType那个）
~~~
^ecfc38
### Q5: Both Paths
- 关于局部变量(```nonlocal```)和全局变量(```global```)
  1. 全局变量和局部变量（global和nonlocal）
~~~python
g = 0  
def global_test(): 
	#global g
    g += 1  
    print(g)
>>> global_test
>>> UnboundLocalError: local variable 'gcount' referenced before assignment
~~~
  ```global```关键字用来在函数或其他局部作用域中使用全局变量。如果要修改全局变量就要声明```global```,如果不修改（只调用）就没事
~~~python
def make_counter():
    count = 0
    def counter():
        nonlocal count
        count += 1
        return count
    return counter
        
def make_counter_test():
	mc = make_counter()
	print(mc())
	print(mc())
	print(mc())
  
make_counter_test()
~~~
  ```nonlocal```声明的变量不是局部变量,也不是全局变量,而是外部嵌套函数内的变量。
- python可以设定给一个参数默认值，当该参数调用时没有值则按默认值计算，若有值输入则按输入值，例：
~~~python
def root(x, degree=2): 
	"""For example
	>>> root(64) 
	8 
	>>> root(64, 3) 
	4
	"""
	return x ** (1 / degree)
~~~
- [ ] 这个...真不知道该说啥，就是说一整个没看懂好吧，最后感觉上是emmmm就是往S后面加U&D？
~~~python
def both_paths(sofar="S"):  
    """  
    >>> up, down = both_paths()    
    S    
    >>> upup, updown = up()
	SU    
	>>> downup, downdown = down()
	SD    
	>>> _ = upup()    
	SUU    
	"""    
	"*** YOUR CODE HERE ***"  
    upsofar = sofar  
    downsofar = sofar  
  
    def up():  
        nonlocal upsofar  
        upsofar += 'U'  
        print(upsofar)  
        return up, up  
      
    def down():  
        nonlocal downsofar  
        downsofar += 'D'  
        print(downsofar)  
        return down , down  
  
    print(sofar)  
    return up,down
~~~
### Q7: Lambda the Environment Diagram
- [ ] 这个也理解不了一点呢~真好呢（精神状态逐渐扭曲xie），就从f3 21就看不懂了哭...
~~~python
a = lambda x: 2 * x + 1
def b(b,x):
	return b(x + a(x))
>>> x = 3
>>> b(a,x)
>>> 21
~~~
![[Pasted image 20230712213717.png]]

### Q8: Composite Identity Function
- 这个函数名已经足够反映我此时的心理状态了好吧...就是要调用函数调用函数，不能直接返回个值，不管是什么类型，都要先定义个函数和他的返回值，再返回那个函数
~~~python
def composite_identity(f, g):  
    def xiande(y):  
        if compose1(f,g)(y) == compose1(g,f)(y):
            return True  
        else:  
            return False  
    return xiande
~~~
### Q9: I Heard You Liked Functions...
- 好帅的递归，但不会(注意最后总函数的返回值缩进)
  小小总结一下：就是这种1.2.3.1.2.3...类型的循环好像都可以用这种类型的递归，即定义一个函数（如本题的conmpose1），然后函数参数分别为当前值和下一个函数值，即```compose1(f2,cycle_f(n-1))```这种形式，之后再试试呐~
~~~python
def cycle(f1, f2, f3):  
    def cycle_f(n):  
        if n == 0:  
            return lambda x : x  
        elif n % 3 == 1:  
            return compose1(f1,cycle_f(n-1))  
        elif n % 3 == 2:  
            return compose1(f2,cycle_f(n-1))  
        else:  
            return compose1(f3,cycle_f(n-1))  
    return cycle_f
~~~
## *Midterm1 Review*
- ```print```函数始终返回```None```，在它被当作函数调用时同时输出他的参数（以空格分开）![[Pasted image 20230713091350.png]]
- 一个验证函数在调用参数时总是沿母函数层层相上搜索的例子，如下：我觉得最重要的一步理解就是```pirate```函数里调用的```arggg```是3，而真正应用于返回函数```plunder```的参数实际上是已经定义的```square```函数，因此本质上```add```的第一项就是4的平方![[Pasted image 20230713100856.png]] ^a02dcd
~~~python
from operator import add,mul
def square(x):
    return mul(x,x)
    
def pirate(arggg):
    print('matey')
    def plunder(arggg):
        return arggg
    return plunder
    
add(pirate(3)(square)(4),1)
~~~
## *Decorations*
- 好像就是一个可以追踪高级函数运行过程的小玩意，但我的ucb不知道为什么运行不了（好像没装上这个库）
~~~python
def trace(fn):  
    def traced(x):  
        print('Calling',fn,'on argument',x)  
        return fn(x)  
    return traced  
  
@trace  
def square(x):  
    return x * x  
@trace  
def sum_squares_up_to(n):  
    k = 1  
    total = 0  
    while k <= n:  
        total,k = total + square(k),k + 1  
    return total
"""
>>> square(2)
Calling <function square at 0x0000015003B8ADD0> on argument 2
4
>>> sum_squares_up_to(5)
Calling <function sum_squares_up_to at 0x0000015003B8AE60> on argument 5
Calling <function square at 0x0000015003B8ADD0> on argument 1
Calling <function square at 0x0000015003B8ADD0> on argument 2
Calling <function square at 0x0000015003B8ADD0> on argument 3
Calling <function square at 0x0000015003B8ADD0> on argument 4
Calling <function square at 0x0000015003B8ADD0> on argument 5
55
"""
~~~

# Lecture 6: Recursion（递归）
## *Recursive functions*
- 递归的基本思路：首先具备一个```基本情况(basic case)```，然后在更复杂的函数求解过程中应用自身函数不断简化所求，使其更接近```基本情况(basic case)```
~~~python #求各位之和（用递归）
def split(n):  
    return n // 10, n % 10  
  
def sum_digits(n):  #basic case
    if n < 10:  
        return n  
    else:  
        all_but_last, last = split(n)  
        return sum_digits(all_but_last) + last
~~~
## *Recursion in Environment Diagrams*
- 对比来看，应用```while```循环需要定义参数来进行跟踪统计，而运用递归则只需要计算机分不同框架来自动区分递归的步骤（参数少） ^5ca33e
~~~python
def fact_iter(n):
	total, k = 1, 1
	while k <= n:
		total, k = total * k, k + 1
	return total

def fact(n):
	if n == 0:
		return 1
	else:
		return n * fact(n-1)
~~~
## Verifying Recursive Functions
<small>老师管做递归叫信仰之跃(The Recursive Leap of Faith)笑死我了哈哈哈哈哈</small>
- 验证递归是否符合要求的步骤：[[#^5ca33e]]
  1. Verify the base case. 验证基本情况（确定有一个情况是正确的）
  2. Treat``` fact``` as a functional abstraction. 将函数看作一个函数抽象功能，不考虑这个函数如何实施，只考虑它会做什么（好抽象...）
  3. Assume that ```fact(n-1)``` is correct. 假设```fact(n)```递归返回的第一个值```fact(n-1)```是正确的
  4. Verify that ```fact(n)``` is correct, assuming that ```fact(n-1)``` correct
  5. 代代特值（bushi）
## *Mutual Recursion*
### <small>Example: The Luhn algorithm</small>
- 感觉需要先给未来1000%看不懂这个例子是啥的我解释一下，就是一个现在国际上很通用的验证一些卡号的方法，具体如下：
  1. 从右向左，从最右面第一个数字开始乘一，右起第二个数乘二，第三个数乘三...以此类推
  2. 如果经过乘法运算后所得小于十则直接保留，如果大于十就返回其所得值的每位数字之和（如2 * 8 = 16则返回1 + 6 = 7）
  3. 将整个号码每位返回值相加并且取10的余数即被称为判定位
  ![[Pasted image 20230714014717.png]]
- 所以这个例子应用交互递归的点就在于一位数✖1另一位数✖2，因此需要两个分别为乘一乘二的函数的返回值都是彼此以达到变换效果
^756591
~~~python
def split(n):  #求前几位和末位
    return n // 10, n % 10  
  
def sum_digits(n):  #求各位之和，在此示例中用来求*2后超过10的各位之和
    if n < 10:  
        return n  
    else:  
        all_but_last, last = split(n)  
        return sum_digits(all_but_last) + last    
      
def luhn_sum(n):  #乘一的返回值，交互到乘二的函数
    if n < 10:  
        return n  
    else:  
        all_but_last,last = split(n)  
        return luhn_sum_double(all_but_last) + last  
  
def luhn_sum_double(n):  #乘二的返回值，交互到乘一的函数
    all_but_last,last = split(n)  
    luhn_digit = sum_digits(2 * last)  #超过十各位相加
    if n < 10:  
        return luhn_digit  
    else:  
        return luhn_sum(all_but_last) + luhn_digit
~~~
## *Recursion and Iteration*
- 从迭代```while```到递归，由于迭代是一种特殊的递归形式，所以只需要找到在不同迭代步骤中始终维护和保持的状态```n```并将其作为参数 
^afb04a
~~~python
def sum_digits_iter(n):  
    digit_sum = 0  
    while n > 0:  
        n, last = split(n)  
        digit_sum += last  
    return digit_sum  
  
def sum_digits_rec(n,digit_sum):  
    if n == 0:  
        return digit_sum  
    else:  
        n, last = split(n)  
        return sum_digits_rec(n,digit_sum)
~~~
## *Order of Recursive Calls*
- Cascade Function: (级联函数)
  这个例子为了证明即在任何一次函数递归中，直到执行其```return```值之前，这个函数递归都不会完成（例如本例中先执行```cascade(n//10)```再```print```）；同时，任何调用都能出现在递归调用之前或者之后；最后，在完成每个递归调用时，从最后一个递归调用逐级向上返回，直到返回第一次函数调用
~~~python
def cascade(n):  
    if n < 10:  
        print(n)  
    else:  
        print(n)  
        cascade(n//10)  
        print(n)  
  
def cascade(n):  
    print(n)  
    if n > 10:  
        cascade(n//10)  
        print(n)
~~~
## *Example: Inverse Cascade*
- 打印逆向级联
~~~python
def f_then_g(f,g,n):  
    if n:  
        f(n)  
        g(n)  
  
def inverse_cascade(n):  
    grow(n)  
    print(n)  
    shrink(n)

grow = lambda n: f_then_g(grow,print,n//10)  
shrink = lambda n: f_then_g(print,shrink,n//10)  
~~~
# Lecture 7: Tree Recursion（树递归）
<big>树递归即指在某函数内有不止一次的函数递归调用，每个值都能转化为树状的基本结构直接返回对应的值</big>
## *Tree Recursion*
~~~python
def fib(n):  #计算斐波那契数列
    if n === 0:  
        return 0  
    elif n == 1:  
        return 1  
    else:  
        return fib(n-1) +fib(n-2)
~~~
<small>（由于计算了很多重复值导致运行速度会慢）</small>
## *Example: Paths*
<small>判断从一个m行n列的表格一角走向另一个对角有多少种可能的路径</small>
- Thinking: 在每一个格子时都有向上和向右两种走法，而不管往哪个方向走一格，问题都可以转化为剩余```m-1```或```n-1```个格子所具有的路径数量
~~~python
def paths(m,n):
	if m == 1 or n == 1:
		return 1
	else:
		return path(m-1,n) + path(m,n-1)
~~~
## *Example: Knapsack*
<small>判断n的各位数字组合能否等于k，可能等于返回True，反之返回False</small>
- u1s1这个是有点没看懂的，自己的理解大概是如果n有0位不影响加减所以直接返回```True```，然后```with_last```函数每次去掉最后一位后查看包含此步骤中n的最后一位能否满足条件，而```without_last```则表示不包含此步骤中的最后一位能否满足。
  综上，这个函数主题应用树递归就是在n的每一位数都提供加上这位数字和不加上这位数字两种选择，以此来包含所有可能
~~~python
def knap(n,k):
	if n == 0:
		return k == 0
	else:
		with_last = knap(n // 10, k - n % 10)
		without_last = knap(n // 10,k)
		return with_last or without_last
~~~
## *Example: Counting Partitions*
- 计数分区：即定义一个函数```count_partitions(n,m)```，求出在单一分区最大为```m```的情况下，在```n```中能有多少种分区的组合。例如```count_partitions(6,4)```即有如下要求和9种解：
  ![[Pasted image 20230714145032.png]]
- Thinking：要应用树递归的基本思路，即将所有情况分成两种情况，逐渐简化为基本情况，并且简化后的情况可以用原情况表示。本例中，可以先分为分区中有4的情况和分区中最大为3的情况。而对于第一种情况而言，可以视作求2的分区，即```n-m```的可能分区情况。如此，本例转化为的递归即为```count_partitions(n-m,m)```和```count_partitions(n,m-1)```的递归数总和，代码如下
~~~python
def count_partitions(n,m):  
    if m == 0:  
        return 0  
    elif n == 0:  
        return 1  
    elif n < 0:  
        return 0  
    else:  
        with_m = count_partitions(n-m, m)  
        without_m = count_partitions(n, m-1)  
        return with_m + without_m
~~~

## *Example: Binary Print*
- [ ] （这节没听懂一点就是说）改日再会吧...
## *Implementing Functions*
- 这颗主要讲了一个程序填空题的解题思路吧，大概就是先理解框架，然后代入具体示例思考在每一步应该完成怎样的操作。
~~~python
def remove(n,digit):  #删除n中为digit的数字
    kept, digits = 0, 0  #digits常做计数器
    while n > 0 :  
        n, last = n // 10, n % 10  
        if last != digit :  
            kept = kept + last * 10 ** digits  #利用digits实现位数转换
            digits += 1  
    return kept
#另一种思路
def remove(n,digit):  
    kept, digits = 0, 0  
    while n > 0 :  
        n, last = n // 10, n % 10  
        if last != digit :  
            kept = kept / 10 + last  
            digits += 1  
    return round(kept * 10 ** (digits - 1))
~~~
## *Lab03: Recursion, Tree Recursion*
### Q2: WWPD: Journey to the Center of the Earth
- [ ] 这个还是有点似懂非懂，就是单纯凭理解感觉是```70km 2900km 5300km 2900km 5300km 2900km```，但是实际上好像涉及函数调用嵌套，最后还有个函数定义（？
~~~python
def crust():  
    print("70km")  
    def mantle():  
        print("2900km")  
        def core():  
            print("5300km")  
            return mantle()  
        return core  
    return mantle  
  
drill = crust  
drill = drill()  # 70km
drill = drill()  # 2900km
drill = drill()  #5300km
				 #2900km
drill()          #5300km
				 #2900km
				 #Function
~~~
![[Pasted image 20230715221249.png]]
### Q4: Repeated, repeated
- 这个算是记一下自己的解题思路吧，就是先自然用```while```循环写了，然后想办法用递归替换迭代循环吧（让我们一起高呼：这就是GPT!）
  在递归执行中因为直接返回```repeated(f,n-1)```所以就不需要```repeated_g```来作为"中转"（其实是不知道怎么能在全局变量里定义```repeated_g```的初始值且让这个语句就在递归里执行一次），所以就相当于直接赋给初始值```f(x)```
~~~python
#迭代while版
def compose1(f, g):  
    """"Return a function h, such that h(x) = f(g(x))."""  
    def h(x):  
        return f(g(x))  
    return h  
  
def repeated(f,n):  
    def repeated_f(x):  
        if n == 0:  
            return x  
        elif n == 1:  
            return f(x)  
        else:  
            i, repeated_g = 1, f  
            while i < n:  
                repeated_g = compose1(f,repeated_g)  
                i += 1  
            return repeated_g(x)  
    return repeated_f

#递归版
def repeated(f,n):  
    def repeated_f(x):  
        if n == 0:  
            return x  
        else:  
            return repeated(f, n-1)(f(x))  
    return repeated_f
~~~
### Q5: Num eights
- 这个的抽象程度远超我想象...本来还想用就是先定义函数做出来然后再改，但最后咋也改不出来，借鉴了一下网上的: 就是我的理解是用一个```return 0```来表示所有位数都已经判断完毕并且初始化计数器为0，然后层层向上，如果该位数是8就返回值+1
~~~python
def num_eights(x):
	if x == 0:
		return 0
	if x % 10 == 8:
		return num_eights(x // 10) + 1
	return num_eights(x // 10)
~~~
### Q6: Ping-pong
- 这题说真的是一点思路没有，看了网上大佬的代码后也用tutor理解了好久才勉强理解，我自己的理解大概是：
  引入一个判定正负方向的判定值```flag```初始值为1，把所求的第```n```个```pingpong```数转化为上一个```pingpong```数和上一个```flag```的和，而根据```flag(x)```函数的定义，```flag```最终不是1就是-1（如果满足被8整除或者含8的条件，```flag(x)```等于```-flag(x-1)```，即前一个增减方向的相反，这样起到了改变增减方向的作用）
~~~python
def pingpong(n):
	def flag(x):  
	    if x == 1:  
	        return 1  
	    if num_eights(x) or x % 8 == 0:  
	        return -flag(x-1)  
	    return flag(x-1)  
	if n == 1:  
	    return 1  
	return pingpong(n-1) + flag(n-1)
~~~
## *HW03: Higher-Order Functions, Self Reference, Recursion, Tree Recursion*
### Q1: Compose
- [ ] 主打一个一个都不会做...我是真没办法透彻理解这个咋过来的，充其量能说服自己的一种理解是：(读题 认清```func```是所有嵌套 可能会想明白一点)
      ```composer(func)```函数直接收了一个参数```func()```，表示已有的全部函数嵌套；最终```func_adder(g)```实际上要返回一个```func(g(x))```的新函数，并把它作为参数```func()```传回给```composer()```函数，也就是添加了一个新函数进入所有函数的嵌套；最终返回```func```（已有嵌套函数）和```func_adder```（添加新函数工具函数）
	      对于这种两参数可以借鉴一下这个例子 [[#^afb04a]]
~~~python
def composer(func = lambda x: x):
    def func_adder(g):
        h = lambda x: func(g(x))
        return composer(h)
    return func, func_adder
~~~
### Q2: G Function
- 哦莫，终于做出来一个，记录一下递归和迭代的不同思路
  需要注意的就是返回分清是返回函数还是具体值（即```g_iter_f```和```g_iter_f()```的区别）
~~~python
def g(n):   #递归
	if n <= 3:  
	    return n  
	else:  
	    return g(n-1) + 2 * g(n-2) + 3 * g(n-3)

def g_iter(n):    #迭代
	def g_iter_f():  
	    if n <= 3:  
	        return n  
	    else:  
	        i, loc = 1, 0  
	        while i <= 3:  
	            loc += i * g(n - i)  
	            i += 1  
	        return loc  
	return g_iter_f()
~~~
### Q3: Missing Digits
- 感觉很有必要先来记录以下这个在面对跟数字位数有关的问题是```all_but_last = n // 10```和```last = n % 10```的思路（每次看到恍然大悟自己想都想不到这个点）
- 先读题读明白，```missing_digits(n)```提取的参数本身就是一个各位数字逐渐增大的参数，所以思路是从最后一位```last```和前一位```last_last```比较，如果相差小于等于1说明这两位数字之间没缺失，大于1说明缺失了```last - last_last - 1```个数字，然后用递归继续判定前```all_but_last```位数字；注意在```return```值中可以加上每次缺失的数字个数，这种返回方式可以类比一下这个[[#^756591]]
	  还有就是别忘了基本条件```basic case```，否则会一直递归（报错```RecursionError: maximum recursion depth exceeded in comparison```)
~~~python
def missing_digits(n):
	all_but_last, last = n // 10, n % 10  
	if all_but_last == 0:  
	    return 0  
	last_last = all_but_last % 10  
	if last - last_last <= 1:  
	    miss = 0  
	else:  
	    miss = last - last_last - 1  
	return missing_digits(all_but_last) + miss
~~~
### Q4: Count Change
- 类比类比and类比！这个整体思路就是应用上面计数分区[[#*Example Counting Partitions*]]的思路，分先用含最大的和不含最大的m进行分类
	  过程中遇到了一点小问题，就是在不应用```while```循环的情况下怎么求出小于```total```的最大m（也就是2的n次幂），求助了一下chatGPT老师给出的解决方案是转化为位运算（因为2的幂总是在二进制表示中只有一位是1，其他位都是0）。例如：7的二进制是111，共3位；所以将1向左移动2位得到100，转换为十进制就是4，是小于7最大的2的n次幂
~~~python
def count_change(total):  
    def find_largest_power_of_two(x):  
        # 将total转换为二进制字符串并得到其长度  
        binary_length = len(bin(x)) - 2  
        # 将1左移(binary_length - 1)位得到结果  
        n = 1 << (binary_length - 1)  
        return n  
    m = find_largest_power_of_two(total)  
    def count_change_f(total, m):  
        if m == 1:  
            return 1  
        elif total < 0:  
            return 0  
        else:  
            with_m = count_change_f(total - m, m)  
            without_m = count_change_f(total, m // 2)  
            return with_m + without_m  
    return count_change_f(total, m)
~~~
### Q5: Towers of Hanoi
- 过年咯！感觉还是类比计数分区那个思路[[#*Example Counting Partitions*]]好吧，太有用了！这回变成```all_but_bottom```和```bottom```了，借助```print_move```函数来打印步骤，把每一个递归都理解成两个的思路，即```all_but_bottom: start->middle bottom: start->end all_but_bottom: middle->end```就搞定！
	  中间就怎么定义这个```middle```又去寻求一下老师帮助，方法类似于定义数组，定义了一个包含所有可能数值的集合```all_numbers```，然后使用集合的差集操作```all_numbers - {start, end}```来找到除了```start```和```end```之外的那个元素。由于集合是无序的，我们可以使用``pop()``方法随机获取其中的一个元素，这样```middle```就会等于剩下的那个值。
	  虽然但是最后觉得自己像个傻子因为发现了：```middle = 6 - start - end```...
~~~python
def print_move(origin,destination):  
    print("Move the top disk from rod", origin, "to rod", destination)  
  
def move_stack(n, start, end):  
    assert 1 <= start <= 3 and 1 <= end <= 3 and start != end, "Bad start/end"  
  
    def find_middle(start, end):  
        all_numbers = {1, 2, 3}  
        x = (all_numbers - {start, end}).pop()  
        return x  
  
    middle = find_middle(start, end)  
  
    if n == 1:  
        return print_move(start, end)  
    else:  
        all_but_bottom = move_stack(n-1, start, middle)  
        bottom = move_stack(1, start, end)  
        all_but_bottom = move_stack(n-1, middle, end)
~~~
### Q6: Anonymous factorial
- OK一朝回到解放前，又一道抽象题目...直接引用一下网上博主的解释
	  这道题要点，把函数当做参数传入，构造call, 在call里用lambda构造这个函数的behavior，这样就解决了迭代时需要函数名的问题。主要分为两部分: 
	  1. 第一个括号： (lambda f: lambda k: f(f, k)) 
	  构造一个需要f函数作为参数的函数，返回值是需要k为参数的函数，返回f函数的值，并且规定了f是一个需要2个参数的函数，f自身和k 
	  2. 第二个括号：(lambda f , k: k if k == 1 else k * f(f, k-1) ) 
	  这部分作为第一个括号的第一个call，构造f函数的行为，需要2个参数：f, k. 返回值为k或else后的值，if给出最简式，else给出，k和k-1的关系  
	  3. 注意环境变量的变化，写成相同的名字便于理解，实际并不相同。
~~~python
def make_anonymous_factorial():  
	return (lambda f: lambda n: f(f,n))(lambda f, n: n if n == 1 else n * f(f, n-1))
~~~
# Lecture 8: Sequences & Data Abstraction（序列与数据抽象）
## *Lists*
- 整体感觉就是C的数组，大括号```{1，2，3，4}```变成中括号```[1,2,3,4]```，另外还有些小tips和示例：
  ~~~python
  digits = [1, 2, 3, 4]
  len(digits) = 4  #判断数组长度

  from operater import getitem
  digits[3] <--> getitem(digits, 3)   #提取列表中第三个数
  
  >>> [2, 7] + digits * 2  <--> add([2, 7], mul(digits, 2))
  [2, 7, 1, 2, 3, 4, 1, 2, 3, 4]
  
  >>> pairs = [[10, 20], [30, 40]]
  >>> pairs[1]
  [30, 40]
  >>> pairs[1][0]
  30
  ~~~
## *For Statements*
- ```for```循环和```while```循环的用法功能对比：
~~~python
  def count(s, value):  
    total, index = 0, 0   #需要定义追踪变量index
    while index < len(s):  
        element = s[index]  
        if element == value:  
            total += 1  
        index += 1  
    return total  
  
def count(s, value):  
    total = 0  
    for element in s:     #不需要定义追踪变量，element初始化即为0且自增
        if element == value:  
            total += 1  
    return total

>>> pairs = [[1, 2], [2, 2], [3, 2], [4, 4]]
>>> same_count = 0
>>> for x, y in pairs:    #固定长度序列中每个元素的名称
...     if x == y:
...			same_count += 1

>>> same_count
2
~~~
- `for ... in ...`循环用法解释：

~~~python
'''
in表达式从（字符串、序列等）中依次取值，又称为遍历
for-in遍历的对象必须是可迭代对象
'''
 
'''
for-in的语法结构
for 自定义变量 in 可迭代对象:
    循环体
'''
 
# 字符串中取值
for item in 'python':
	print(item)
 
# range产生一个整数序列，也是一个可迭代对象
for i in range(10):
	print(i)

# 如果在循环体中不需要用到自定义变量，可将自定义变量写为‘_’
for _ in range(5):
	print('人生苦短，我用python')
~~~
## *Ranges*
~~~python
>>> list[range(-2, 2)]
list[range(-2, 2)]
>>> list(range(-2, 2))
[-2, -1, 0, 1]

>>> list[range(4)]
list[range(0, 4)]
>>> list(range(4))
[0, 1, 2, 3]

def cheer():
	for _ in range(3):  #无用用空格或者下划线代替
		print('Go bears!')
>>> cheer()
Go bears!
Go bears!
Go bears!
~~~
## *List Comprehensions*
~~~python
odds = [1, 3, 5, 7, 9]
>>> [x+1 for x in odds]
[2, 4, 6, 8, 10]
>>> [x for x in odds if 25 % x == 0]
[1, 5]

def divisors(n):
    """Return the integers that evenly divide n.

    >>> divisors(1)
    [1]
    >>> divisors(4)
    [1, 2]
    >>> divisors(12)
    [1, 2, 3, 4, 6]
    >>> [n for n in range(1, 1000) if sum(divisors(n)) == n]
    [1, 6, 28, 496]
    """
    return [1] + [x for x in range(2, n) if n % x == 0]
~~~
## *Strings*
- 对数组来说，一次只能查找一个元素；而对字符串序列来说可查找多个连续字符，如下：
~~~python
>>> 'here' in "Where is Waldo?"
True
>>> 234 in [1, 2, 3, 4, 5]
False
>>> [2, 3, 4] in [1, 2, 3, 4, 5]
False
~~~
## *Data Abstraction*
<small>Defination: A methodology by which functions enforce an abstraction barrier between representation and use</small>
- ```wishful thinking```通过保留有理数的分子分母来输出分数的准确值
~~~python
def mul_rational(x, y):  
    return rational(numer(x) * numer(y), denom(x) * decom(y))  
  
def add_rational(x, y):  
    nx, dx = numer(x), denom(x)  
    ny, dy = numer(y), denom(y)  
    return rational(nx * dy + ny * dx, dx * dy)  
  
def equal_rational(x, y):  
    return numer(x) * decom(y) == numer(y) * decom(x)
~~~
## *Representing Rational Numbers*
- 在定义一个列表如```pair = [1, 2]```后，可以通过解包```x, y = pair```或者运用元素运算选择符```x = pair[0]```来调用列表内容，再或者用```getitem(pair, 0)```
~~~python
from fractions import gcd   #Greatest common divisor  
  
def mul_rational(x, y):  
    return rational(numer(x) * numer(y), denom(x) * denom(y))  
  
def add_rational(x, y):  
    nx, dx = numer(x), denom(x)  
    ny, dy = numer(y), denom(y)  
    return rational(nx * dy + ny * dx, dx * dy)  
  
def equal_rational(x, y):  
    return numer(x) * denom(y) == numer(y) * denom(x)  
  
def rational(n, d):  
    """Construct a rational number that represents N/D"""  
    g = gcd(n, d)  
    return [n//g, d//g]  
  
def numer(x):  
    """Return the numerator of rational number x."""  
    return x[0]  
  
def denom(x):  
    """Return the denominator of rational number x."""  
    return x[1]
~~~
## *Abstraction Barriers*
- [x] 没咋看懂 放段教材（bushi

哦看懂了好像...感觉就是在函数内也尽量引用高层函数，例如```square_rational```引用```mul_rational```，确定了这两个函数的对应关系，即使在更改了选择构造器签名或者更改有理数实现的情况下，因为平方(```square```)等于两原数相乘这个关系始终不变，就不需要修改这个程序

在继续更多复合数据和数据抽象的示例之前，让我们考虑一下有理数示例引发的一些问题。我们根据构造函数 `rational` 和选择器函数 `numer` 和 `denom` 来定义操作。一般来说，数据抽象的基本思想是确定一组基本操作，根据这些操作可以表达对某种值的所有操作，然后仅使用这些操作来操作数据。通过以这种方式限制操作的使用，在不改变程序行为的情况下改变抽象数据的表示会容易得多。

对于有理数，程序的不同部分使用不同的操作来处理有理数，如此表中所述。

|该程序的一部分...|把有理数当作...|仅使用...|
|---|---|---|
|使用有理数进行计算|整个数据值|`add_rational, mul_rational, rationals_are_equal, print_rational`|
|创建有理数或操作有理数|分子和分母|`rational, numer, denom`|
|为有理数实现选择器和构造器|二元列表|列表字面量和元素选择|

在上面的每一层中，最后一列中的函数强制实施抽象障碍。这些功能会由更高层次调用，并使用较低层次的抽象实现。

每当程序的一部分可以使用更高级别的函数而不是使用较低级别的函数时，就会违反抽象障碍。例如，计算有理数平方的函数最好用 `mul_rational` 实现，它不对有理数的实现做任何假设。
```python
>>> def square_rational(x):
        return mul_rational(x, x)
```
直接引用分子和分母会违反一个抽象障碍。
```python
>>> def square_rational_violating_once(x):
        return rational(numer(x) * numer(x), denom(x) * denom(x))
```
假设有理数会表示为双元素列表将违反两个抽象障碍。
```python
>>> def square_rational_violating_twice(x):
        return [x[0] * x[0], x[1] * x[1]]
```
 抽象障碍使程序更易于维护和修改。依赖于特定表示的函数越少，想要更改该表示时所需的更改就越少。 计算有理数平方的所有这些实现都具有正确的行为，但只有第一个函数对未来的更改是健壮的。即使我们修改了有理数的表示，`square_rational` 函数也不需要更新。相比之下，当选择器函数或构造函数签名发生变化后，`square_rational_violating_once` 就需要更改，而只要有理数的实现发生变化，`square_rational_violating_twice` 就需要更新。
## *Data Representations*
<font color = orange>维护抽象障碍的目的是为了可以更改数据表示，而不用重写整个程序</font>
- 数据抽象的关键思想在于通过数据的行为来判断数据类型，而不是通过如何构造它，以下是一个示例，展示了通过修改程序内容而不修改程序表达的一个例子：
~~~python
#在这种定义里应用列表，x作为数组列表
def rational(n, d):  
    """Construct a rational number that represents N/D"""  
    g = gcd(n, d)  
    return [n//g, d//g]  
  
def numer(x):  
    """Return the numerator of rational number x."""  
    return x[0]  
  
def denom(x):  
    """Return the denominator of rational number x."""  
    return x[1]

#在这种定义里应用高阶函数，x作为函数
def rational(n, d):
	def select(name):
		if name == 'n':
			return n
		elif name == 'd':
			return d
	return select

def numer(x):   #这里x作为一个接收有理数（即rational函数）的函数参数
	return x('n')

def denom(x):
	return x('d')

#结果都是如下
>>> x, y = rational(1, 2), rational(3, 8)
>>> print_rational(mul_rational(x, y))
3 / 16
~~~
- 对于第二种定义方式可以这样理解：
  ~~~python
  x = rational(3, 8)
  numer(x)
#对于numer函数相当于：
  return rational('n')  #即返回3
  ~~~

## *61A Fall Lecture12 Video 6(Dictionary)*
- Dictionary: 把键位```key```和值```value```联系起来，没有顺序，例如：
  ~~~python
  >>> numerals = {'I': 1, 'V': 5, 'X': 10}
  >>> numerals
  {'I': 1, 'V': 5, 'X': 10}  #这个换不换顺序都有可能，但都无所谓
  >>> numerals['X'] # {dictionary}['Key']用来在dictionary中搜索
  10
  ~~~
- 其中有键位```keys```，值```values```，和项目```items```三个变量，如下调用：
  ~~~python
  >>> numerals.keys()
  dict_keys(['I', 'V', 'X'])
  >>> numerals.values()
  dict_values([1, 5, 10])
  >>> numerals.items()
  dict_items([('I', 1), ('V', 5), ('X', 10)])
  #如果不调用具体值则会类似显示函数地址或者结构变量，具体如下：
  >>> numerals.keys
  <built-in method keys of dict object at 0x0000014567D5FFC0>
  ~~~
- 还可以应用```dict```构造函数来创建一个```dictionary```，例如：
  ~~~python
  >>> items = [('I', 1), ('V', 5), ('X', 10)]
  >>> items
  [('I', 1), ('V', 5), ('X', 10)]
  >>> dict(items)
  {'I': 1, 'V': 5, 'X': 10}
  >>> dict(items)['X']
  10
  ~~~
- 可以判定一个```key```是否在```dictionary```中，应用语句```'X in numerals```，系统返回```True```或者```False```；与此同时，如果不确定一个```key```是否在```dictionary```中，可以应用```numerals.get(key, 默认值)```函数，赋给想判断的```key```一个默认值，如果在```dictionary```中则返回```dictionary```中对应的值，如果不在```dictionary```中则返回```get```函数中所赋的默认值
- <big>一些特殊的以及一些限制</big>
  - 可以有如下定义：
    ~~~python
    >>> squares = {x: x * x for x in range(10)}
    >>> squares
    {0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81}
    >>> squares[7]
    49
    ~~~
    - 一个```key```只能对应一个值```value```，这个值不局限于数字，也可以是列表等，但是```key```不能是列表```list```、目录```dictionary```或者任何可变的类型
## *Examples: Lists(List Functions)*
- 这节东西好多好多，包含了很多就是列表```list```改变的函数
  <small>首先要记住的一个小tips</small>: 
	  切片```slice [a, b]```包含第a个元素但不包含第b个元素，`[a:]`同理包含a

 - [x] 我先截几张图，之后把这个做个列表在shell里试一下（好多...好烦...）
- 关于```slice notation```的一些解释：
  总结下来，```a[-1]```表示列表的最后一个值，```a[:-1]```表示列表除最后一个值以外的所有元素，```a[::-1]```表示从倒着输出列表元素
~~~python
>>> a = ['a','b','c','d','e','f','g','h','g','k','l','m']

>>> b = a[:] # 列表切片，表示把列表a[]的值全部正序复制到列表b[]中
>>> print(b)
['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'g', 'k', 'l', 'm']

# b = a[n:m]表示列表切片，复制列表a[n]到a[m-1]的内容到新的列表对象b[]
# 当n缺省时，默认为0，即a[:m]
# 当m缺省时，默认到最后，即a[n:]
>>> b1 = a[1:4]
>>> print(b1)
['b', 'c', 'd']

>>> b2 = a[:3]
>>> print(b2)
['a', 'b', 'c']

>>> b3 = a[1:] #表示除第一个元素（编号为0）以后的全部元素
>>> print(b3)
['b', 'c', 'd', 'e', 'f', 'g', 'h', 'g', 'k', 'l', 'm']

# b = a[i:j:s]这种格式呢，i,j与上面的一样，但s表示步进，缺省为1，s可以取任何数字.
# 所以a[i:j:1]相当于a[i:j]

>>> b4 = a[1:5:2]
>>> print(b4)
['b', 'd']

>>> b5 = a[:5:-1]  # 从末尾倒数取值
>>> print(b5)
['m', 'l', 'k', 'g', 'h', 'g']

>>> b6 = a[5::-2]
>>> print(b6)  # 从a[n]处倒数取值
['f', 'd', 'b']

>>> b7 = a[::-1]  # 倒着取值
>>> print(b7)
['m', 'l', 'k', 'g', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a']

>>> b8 = a[-1]   #最后一个值
>>> print(b8)
'm'

>>> b9 = a[:-1]   #除最后一个值以外的元素
>>> print(b9)
['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'g', 'k', 'l']
~~~

 **以下表格所有条件均为：`s = [2, 3]`  `t = [5, 6]`**

|Operation(指令释义)|Example(示例操作)|Result(所得结果)|
|---|---|---|
|<div style="width: 180pt">***append***: adds one element to a list<br>NOTES: 首先注意和extend的区别：是增加一个元素，即是把t作为列表加到s；如果t作为列表被函数调用，那么对t中元素的更改会影响调用t的s</div>|`s.append(t)`<br>`t = 0`|`s = [2, 3, [5, 6]]`<br>`t = 0`|
|<div style="width: 190pt">***extend***: adds all elements in one list to another list<br>NOTES: 首先注意和append的区别：是增加全部元素，即要把t里的全部元素加到s上；同样的t之后的改变也不影响s</div>|`s.extend(t)`<br>`t[1] = 0`|`s = [2, 3, 5, 6]`<br>`t = [5, 0]`|
|<div style="width: 190pt">***addition*** & ***slicing***: creating new lists containing existing elements<br>NOTES: 首先，类似于b = a[1:]这种slice操作，所得首先是一个列表！！！(这个有坑在下面）；其次，用于a是将t作为列表与s相加，故对b[1][1]修改实际上是在对t中元素的修改，故既会影响a也会影响t</div>|`a = s + [t]`<br>`b = a[1:]`<br>`a[1] = 9`<br>`b[1][1] = 0`|`s = [2, 3]`<br>`t = [5, 0]`<br>`a = [2, 9, [5, 0]]`<br>`b = [3, [5, 0]]`|
|<div style="width: 180pt">***list*** function: creating new lists containing existing elements</div>|`t = list(s)`<br>`s[1] = 0`|`s = [2, 0]`<br>`t = [2, 3]`|
|<div style="width: 180pt">***slice assignment***: replaces a slice with new values<br>NOTES: 理解c[a:a] = b就是把b变成c的第a位，其他的全部按上边的tips(含前不含后)考虑</div>|`s[0: 0] = t`<br>`s[3:] = t`<br>`t[1] = 0`|`s = [5, 6, 2, 5, 6]`<br>`t = [5, 0]`|
|<div style="width: 190pt">***pop***: removes & returns the last element<br>NOTES: 既移除s的最后一位元素，同时将元素赋给t（注意是元素不是列表）</div>|`t = s.pop()`|`s = [2]`<br>`t = 3`|
|<div style="width: 180pt">***remove***: removes the first element equal to the argument</div>|`t.extend(t)`<br>`t.remove(5)`|`s = [2, 3]`<br>`t = [6, 5, 6]`|
|<div style="width: 180pt">***slice assignment***: remove elements to a list by assigning [] to a slice</div>|`s[:1] = []`<br>`t[0: 2] = []`|`s = [3]`<br>`t = []`|

- 对下面的
![[Pasted image 20230722005339.png]]
## *Lab 4: Python Lists, Data Abstraction*
### Q2: Reverse (iteratively)
- 类比一下C语言里面数组指针的特殊性
- <small>上面这个是自己写的，有个很明显的缺陷就是定义数组只有4位（这个相当于占了知道示例的便宜</small>
  ~~~python
  def reverse_iter(lst):  
    n, i = len(lst), 0
    # a = lst
    # 如果这里这样定义，在更改a中元素的同时lst的元素也会被更改  
    a = [0, 0, 0, 0]  
    while i < n:  
        a[i] = lst[n - i - 1]  
        i += 1  
    return a
  ~~~
- <small>之后这个是大佬的代码，借助了for循环的迭代用法和列表的加法顺序性质</small>
~~~python
def reverse_iter(lst):
	ans = []
	for x in lst:
		ans = [x] + ans
	return ans
~~~
  （关于```for-in```循环的用法详见[[#*For Statements*]]）
### Q3: Reverse (recursively)
- 具体思路请详见上一个[[#*Examples Lists(List Functions)*]]中有关```list[-1]```和```list[:-1]```的解释
  <big>把握住递归的basecase+recursion的结构</big>[[#*Recursive functions*]]
~~~python
def reverse_recursion(lst):
	if not lst:
		return []
	return [lst[-1]] + reverse_recursion(lst[:-1])
~~~
### Q5: Closer city
- 学一个选择返回的语句
~~~python
if distance_a < distance_b:  
    return get_name(city_a)  
else:  
    return get_name(city_b)
#等效于
return get_name(city_a) if distance_a < distance_b else get_name(city_b)
~~~
### Q7: Add Characters
- 就告诉自己一句话：别怕递归！按思路走[[#*Recursive functions*]]，对于字符串的基本情况记得考虑一下```len(list) == 0```
~~~python
def add_chars(w1, w2): 
    if len(w1) == 0:  
        return "" 
#OK犯病不知道为什么这里新建空字符串和返回空字符串都不行，就要我返回w1或者w2 
    if w1[0] == w2[0]:  
        return add_chars(w1[1:], w2[1:])  
    return w2[0] + add_chars(w1, w2[1:])
~~~
# Lecture 9: Functional Decomposition & Debugging（功能分解与调试）
## *Assertions*
- `assert`函数为断言函数，用来检查代码是否符合已有的理解。如果函数表达式的结果为真则没有任何效果产生，如果之后的表达式结果为假则返回预先设置好的报错信息，可以去看一下之前汉诺塔那个事例中用过[[#Q5 Towers of Hanoi]]
- `isinstance(数据, 数据类型)`函数则是一个判断所给数据是否为指定数据类型的函数，是则返回`True`，反之返回`False`具体的代码实现如下：
~~~python
def fact(x):
    assert isinstance(x, int)
    assert x >= 0
    if x == 0:
        return 1
    else:
        return x * fact(x-1)

def half_fact(x):
    return fact(x / 2)

>>> half_fact(5)
None  #调用fact函数时变量2.5不符合int整数类型
~~~
## *Testing*
- 调试程序能够发现程序中的错误，同时让我们能够保证某一个程序小组块的正确性，进而缩小未来可能需要的调试范围，也能够记录下程序的运行过程
- Python所提供的具体的调试方案即`doctest`函数，具体的执行方式为`python3 -m doctest filename.py`，实现测试的代码模板如下：
~~~python
def f(n):
	"""对函数功能的解释
	>>> f(1) #第一个函数验证测试示例
	1   #第一个函数期待返回的结果值
	>>> f(2)
	2
	"""
	#...具体函数代码
~~~
## *Print Debugging*
- 即应用打印过程值的方式来观察代码运行步骤，以起到检测调试代码的效果
~~~python
def fact(x):
    # assert isinstance(x, int)
    # assert x >= 0
    print("Debug x = ", x)
    if x == 0:
        return 1
    else:
        return x * fact(x-1)

def half_fact(x):
    return fact(x / 2)

>>> fact(2)
x = 2
x = 1
x = 0
2
~~~
## *Interative Debugging*
- 交互调试（Interative Debugging）再python中通常被等同于是一种叫做`REPL: Read-Eval-Print-Loop(读取-求值-打印-循环)`的工具，可以近似认为是python的命令行窗口，这种方式可以不用在PyCharm中不断的修改代码并运行，而是直接在命令行窗口中执行命令，具体指令为`python3 -i filename.py`。
## *Error Types*
- 本节介绍一些常见的Python报错，用来判断自己的程序出现了什么问题
1. SyntaxError(语法错误)
	 - 出现此类错误表示您运行的文件中有不是有效的Python标准语法，程序中有错误语法或者错别字等
	 - 应该试图搜索缺失或多余的括号、`if while`等语句末尾缺失的冒号，或是开始的声明中却没有包含内容
2. IndentationError(缩进错误)
	- 出现此类错误表示由于缩进不一致导致语法不正确，或者是因为用错了程序文本编辑器
	- 应该试图搜索一下是否出现混淆空格和Tab的情况、错位情况，或者将自己的程序在一个程序编辑器中打开，还有可能是用错了空格类型（有不止一种空格类型）
3. TypeError: 'X' object is not callable...(对象类型不可调用错误)
	- [ ] 出现此类错误表示数据X的类型不能被看作函数，在函数过程中调用了一个非函数变量
	- [ ] 应该被分配给函数的变量被分配给了非函数，或者局部变量中不包含全局变量里的同名函数
4. TypeError: ... NoneType ...(类型错误)
	- 出现此类错误表示在程序不该使用的某处运用了`None`
	- 事实上表示函数没有返回`return`语句
5. NameError or UnboundLocalError(命名错误&非绑定本地错误)
	- 出现此类错误表示Python寻找一个变量名但没找到
	- [ ] 检查名称拼写错误，另一种不太常见的情况是在局部框架中对一个全局框架中的变量做了阴影处理（没理解，代码如下）
~~~python
def f(x):
	return x ** 2

def g(x):
	y = f(x)
	def f():
		return y + x
	return f
~~~
## *Tracebacks*
- 程序返回的报错包括报错本身，返回错误的行数和每行都在进行着什么进程，最近的调用和错误返回将会显示在最底部
- 牢记基本的报错含义，依次浏览各行检查可能出错的位置。
## *Exceptions*
- 编程语言中的一种内置机制用于声明和反映异常的地方（这节没听懂）
## *Rasing Exceptions(引发异常)*
1. **Assert**: 最简单常见的引发报错的方式便是断言语句`assert`，语法为```assert<表达式>, <string>```，例如：`assert False, 'Error'`会返回`AssertionError: Error`. 同时由于`assert`语句会减慢程序运行速度，可以使用`python3 -O`语句来忽略程序中的所有`assert`语句（相当于屏蔽了`__debug__`语句(会返回False)
2. **Raise**: 感官上就是引发异常并抛出一个报错，格式大概是`raise <错误类型(如NameError, TypeError, KeyError(在dictionary中找不到对应的key), RuntimeError(超出运行时间), Exceptions等)> ('报错内容')`
## *Try Statements*
- `try`语句用来处理异常，具体语法如下:
~~~python
try:
	<try suite>
except <出现异常类型> as <命名>:
	<except suite>
~~~
`try`语句的执行规则：
1. 首先执行`<try suite>`，如果运行一切正常，就不执行异常语句`except suite`；
2. 如果在执行`<try suite>`的过程中产生了某种异常，则执行`except`语句中对应异常类型的`except suite`语句；
3. `try`语句的执行不会导致解释器停止工作，只会在特定出现异常情况下执行`except`操作
以下是一个示例：
~~~python
#一种很常见的做法，当我们试图把一个名称绑定到一个值上但没有成功，就把名称绑定到特定值
>>> try:
... 	x = 1 / 0
... except ZeroDivisionError as e:
... 	print('handling a', type(e))
...     x = 0
...
handling a <class 'ZeroDivisionError'>
>>> x
0
~~~
- 下面这个示例是为了对比以显示出`try`语句不会使程序停止运行的特性
~~~python
def invert(x):  
    y = 1 / x  
    print('Never print if x is zero.')  
    return y  
  
def invert_safe(x):  
    try:  
        return invert(x)  
    except ZeroDivisionError as e:  
        print('handled', e)  
        return 0

>>> invert_safe(0)
handled division by zero #这里的division by zero是原本1/0的报错
0
~~~
- 当输入指令`invert_safe(1/0)`时，程序不会运行，因为操作数`1/0`本身遍已经产生了`ZeroDivisionError`异常
- 运算符在操作数之前计算，即当`>>> inverrrrt_safe(1/0)`时，会优先出现`NameError: name 'inverrrrt_safe' is not defined`
- 当遇到如下嵌套`try`语句时，经过内部`try`语句执行后的部分便已经变成了一个没有异常运行良好的程序，所以外层的`except suite`永远不会被执行(代码如下)
~~~python
>>> try:
...     invert_safe(0)
... except ZeroDivisionError as e:
...     print('handled!')
...
handled division by zero  #不会执行外部循环的handled！语句
0
~~~
## *Example: Reduce*
对`reduce`函数的解释如下：
![[Pasted image 20230808143852.png]]
~~~python
from operator import add, mul, truediv  
  
def divide_all(n, ds):  
    try:  
        return reduce(truediv, ds, n)  
    except ZeroDivisionError as e:  
        return float('inf')  
  
def reduce(f, s, initial):   #循环
    """Combine elements of s using f starting with initial  
  
    >>> reduce(mul, [2, 4, 8], 1)    
    64    
    >>> reduce(add, [1, 2, 3, 4], 0)
	10    
	"""    
	for x in s:  
        initial = f(initial, x)  
    return initial  
  
def reduce(f, s, initial):  #递归
	"""Combine elements of s using f starting with initial  
  
    >>> reduce(mul, [2, 4, 8], 1)    
    64    
    >>> reduce(add, [1, 2, 3, 4], 0)
	10    
	""" 
	if not s:  
        return initial  
    else:  
        first, rest = s[0], s[1:]  
        return reduce(f, rest, f(initial, first))

>>> divide_all(1024, [2,4,8,0])
inf
>>> divide_all(1024, [2,4,8])
16.0
~~~
# Lecture 10: Trees
## *Box-and-Pointer Notation*
- 讲了一种指针表示列表元素的方法，有个闭包属性没咋听懂
![[Pasted image 20230809134011.png]]
## *Slicing*
- 一种对已有列表进行“切片”的操作
  具体操作请看上面的[[#*Examples Lists(List Functions)*]]
## *Processing Containing Values*
- 一些遍历列表和目录的内置函数(稍后制表)
![[Pasted image 20230809140009.png]]


|函数名|函数用途|示例|
|------|--------|---|
|**sum**函数|`sum(iterable[, start]) -> value`<br>将所给的可迭代变量（如列表）中的数字与`start`初始值相加（没有默认为0）|`>>> sum([2, 3, 4])` <br> `9`<br> `>>> sum([2, 3, 4], 5)`<br> `14` <br> `>>> sum([[2, 3], [4]], [])` <br> `[2, 3, 4]`|
|**max**函数|`max(iterable[, key = func]) -> value`<br>`max(a, b, c, ...[, key = func]) -> value`<br>输出所给的可迭代变量（如列表）中最大的数字，当给出`key function`时，调用这个函数来计算最大值|`>>> max(range(5))`<br> `4`<br> `>>> max(0, 1, 2, 3, 4)`<br>`4`<br>`>>> max(range(10), lambda x: 7 - (x-2) * (x-4))`<br>`3`|
|**all**函数|`all(iterable) -> bool`<br>当所提供的可迭代对象（如列表）中所有元素都为`True`值或列表为空时返回`True`|`>>> [x < 5 for x in range(5)]`<br> `[True, True, True, True, True]`<br> `>>> all([x < 5 for x in range(5)])`<br>`True`<br>`>>> all(range(5))`<br>`False`|
## *Trees*
本质上来说，`Tree`实际上是一种列表嵌套的表示，即将列表作为其他列表中的元素，称之为数据类型的闭包属性(`closure property`)
![[Pasted image 20230809201405.png]]
- 首先介绍了Tree的两种理解方式吧~
  1. 第一种是递归描述(recursive description -> wooden trees): 即每一个树结构都有一个根标签(root label)和若干个枝干(branches)，同时每一个枝干都可以视作为一个子树结构，一个没有枝干的树结构便称之为叶(leaf)
  2. 第二种则是亲缘描述(relative description -> family trees): 即树结构上的每一个位置都可以视作一个节点(node)，每个节点所对应的标签(label)都可以是任何值，而每一个节点同时也作为其他节点的父节点或者子节点(parent/child)
- 接下来，是如何让python定义出一个树结构，如果仅用概念抽象表示的话，树应该是这样的
~~~python
>>> tree(3, [tree(1), 
...     tree(2, [tree(1), 
...        tree(1)])])
[3, [1], [2, [1], [1]]]
~~~
- 紧接着，我们来实际在python下通过编写函数来实现构建Tree的过程
  1. 首先我们从构造函数`Tree`， 选择器函数`label`和 `branches` 组成。
~~~python
def tree(label, branches = []):  
    for branch in branches:   #引入branch遍历branches列表中的元素
        assert is_tree(branch), 'Branches must be trees'   #运用断言函数判断branches中的每一个元素是否也为Tree
    return [label] + list(branches)   #返回时将label值转化为列表，并重新构建一个列表递归除label以外的branches
  
def label(tree):   #返回Tree的第一个值，即root label
    return tree[0]  
  
def branches(tree):    #返回Tree除第一个以外的值，即branches
    return tree[1:]
~~~
  2. 由上方Tree的定义知，只有当树有一个根标签并且所有分支也是树时，树才是结构良好的。`is_tree` 函数应用于构造函数`tree`以验证所有分支是否结构良好。
~~~python
def is_tree(tree):  
    if type(tree) != list or len(tree) < 1:   #验证一个tree是否不是列表或者是否没有root label
        return False  
    for branch in branches(tree):    
        if not is_tree(branch):    #借助branch遍历branches的每一个元素（枝干）是否为Tree
            return False  
    return True
~~~
  3. 同时用`is_leaf`函数验证Tree是否有分支
~~~python
def is_tree(tree):
	return not branches(tree)
~~~
  4. 具体运行情况如下：
~~~python
>>> t = tree(3, [tree(1), tree(2, [tree(1), tree(1)])])
>>> t
[3, [1], [2, [1], [1]]]
>>> label(t)
3
>>> branches(t)
[[1], [2, [1], [1]]]
>>> label(branches(t)[1])
2
>>> is_leaf(t)
False
>>> is_leaf(branches(t)[0])
True
~~~
## *Tree Processing*

## *Example: Printing Trees*