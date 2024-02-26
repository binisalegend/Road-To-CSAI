# 1. Introduction to Java
## *1.1 Essentials*
- 所有的代码都必须有一个类（class）,详见[[Java程序设计笔记#^c9ae49]]
- 在终端中运行Java程序时，需要先执行 `javac *.java` ，这时文件所在的目录中就会自动生成一个 `*.class` 文件，此时再执行命令 `java *` 即可输出程序运行的结果，即先使用 `javac` 进行编译，再使用 `java` 进行运行
- `System.out.print` 可以直接输出，而 `System.out.println` 则包含了换行，如果需要空格输出则可以使用 `System.out.print(x + " ")` （注意好像只能用双引号，单引号会输出乱码，应该是把空格识别成字符串类型了）
- 在Java中定义函数也要在 `public class` 里定义，同时对函数的定义也是 `public static <函数返回类型> <函数名> (参数类型 + 参数名)` ，和C语言很相近的是Java函数的返回也只能是一个类型
- `java` 在建立变量类型数组时，可以通过（以Dog举例）`Dog dogs[] = new Dog[2]` ，然后再分别通过 `dogs[0] = new Dog()` 来对每个变量进行引用和调用
## *1.2 Objects*
- 静态类型 `static` 与实例类型 `instantiated` 区别在于，`static` 不能访问实例类型变量， 例如 `public static void makenoise()` 中不能使用 `System.out.println()` 来访问外部定义的 `weightpounds` 变量；然而，静态类型变量在为一些没有被实例化的变量直接赋值时会变得非常方便，例如 `x = Math.round(5.6)` 就比先实例化一个变量 `Math m = new Math()` 再执行舍入操作 `x = m.round(x)` 要简洁的多 ^9a36d4
- 在Dog示例中，我们既可以设置静态函数 `maxdog` ，并且在DogLauncher函数中直接调用；也可以设置一个实例类函数，相当于用自身来和传入参数 `d2` 进行比较（ `this` 可以直接表示当前所处的变量），在DogLauncher进行调用时则使用 `Dog bigger = d.maxDog(d2);` 进行调用
- 在类中直接定义静态变量相当于直接赋给某个变量一个固有特性，个人理解类似于C语言中的 `const` 类型或者是 `#define <variable> count` 的初始化，在调用时直接用类名称 `Dog.binomen` 调用而不是某个特定的实例
- 对 `public static void main(String[] args)` 的一些解释
   `string[] args` 类似于对命令行输入建立一个字符数组，例如 `args[0]` 就会输出命令行输入的第一行，所以为了能使Java文件正常编译运行。这一部分不能省略
- `Integer.parseInt(String *a)` 可以将一个字符类型的数字输入转化为 `int` 类型的数字，这个在结合命令行 `args[0]` 使用时很有用，因为默认是字符数组，所以输入进来的数字如果需要进行计算都需要进行转化才能进行运算
- 建立数组的语法：`int num[] = new int[]{1, 6, 8, 7};`
- 在Java中可以使用这样的循环for语句 `for (String i: a)` ，其中 `a` 是一个字符数组，这样可以让字符串变量 `i` 遍历 `a` 中的每一个字符串并执行相应的操作。可以类比一下C++中的 `auto(int i: a)` 操作
# 2. Lists
## *2.1 Mystery of the Walrus*
### GoRE
- 对于 `PollQuestions` 实例，在x、y变量的赋值、取等操作中，系统所执行的操作相当于把一个变量所包含的数据复制给另一个变量，这被称作 The Golden Rule of Equals(GRoE)，所以当我们再对原来的变量做更改时，复制后的变量就不会被修改；而当我们 `new` 一个任意类型的引用变量时，Java会分配一个64bits的空间，但是类所需要的存储空间可能超过这个大小，因此我们就需要在这个空间中存储内存中引用变量的地址，即当我们在做 `b = a` 操作的时候相当于把`a` 的地址复制给 `b` ，这时a与b就具有了相同的地址，在 `box-pointer Notation` 模型中，相当于 `b` 复制了 `a` 变量指向实例化对象的指针，即这两个类同时指向了同一块地址内存 ^14da37
  - 注意在 java初始化中，如果一个变量的地址全为0，就会用 `null` 来表示；而一旦一个变量地址不为0，就会有一个指针指向一个实例化对象来记录该变量的具体信息
  同时，在Java语言中，我们无法访问一个变量的储存地址，这与C等语言不同，因为Java中确切的内存地址低于我们在Java中所能访问的抽象级别
- Java中的基本数据类型也是类似的 `int float double byte long boolean String short` 八大数据类型，其余任何由这八大数据类型构成的类、数组等都被称作引用类型 `reference type` 
### Instantiation of Arrays
- 对数组声明的解释：`int[] a = new int[]{0, 1, 2, 32, 4};` 
  - `int[] a` :相当于我们在对创建一个数组做一个声明，系统会建立一个存放64位地址的空间来存放我们即将要存放数组的位置，但是此时并没有对象被实例化
  - `new int[]{0, 1, 2, 32, 4}`: 将会创建五个元素并存放到数组中，将数组地址返回到声明处的64位地址处，注意：声明的对象是匿名的，也就是说如果我们不进行 `int[] a` 这样一个分配变量名的操作，输入进的元素会立刻消失（因为没有变量名可以调用他们）
  - 由于匿名化的特性，这也说明如果我们在上例中把 `a` new一个新的地址，我们将无法再找到当前的变量，因此在重置之前记得转存变量
### IntLists
听完Introducing感觉好像是链表？（
- 芜湖！感觉好像学到了一个判断链表长度的方法,一种用递归，另一种定义计数器用迭代（虽然之前可能学过但是我链表实在是啥也不会）
~~~Java
/**Return the size of the list using recusion */
public int size()
{
    if (rest == null)
    {
        return 1;
    }
    return 1 + this.rest.size();
}

/**Return the size of the list using interation */
public int InterativeSize()
{
    IntList p = this;
    int totalSize = 0;
    while (p != null)
    {
        totalSize += 1;
        p = p.rest;
    }
    return totalSize;
}
~~~
 主要感觉就是递归可以应用在好多地方叭，甚至对于提取到链表中的某个特定元素也可以通过递归的 `return rest.get(i-1)` 来实现
### SLLists
 - 在前面的 `Intlist` 方法实现链表及其相关操作的方式通常被称作“裸露的”方式，而在 `SLList` 方式中我们不仅可以通过 `L.addFirst()` 这样相对更加符合我们感官的方式来进行操作，同时也通过封装实现了功能的独立
   在 `SLList` 方法中，我们为了避免在其他文件中调用链表体系对结构进行一些错误的修改（例如将 `first` 指针指向自己从而导致无限循环），可以采用 `private` 方式定义结构变量，这样只有在 `SLList` 类中可以对 `first` 进行修改而在其它类中不能使用和修改这个变量，从而有效保证了代码的安全性，这也是面向对象编程中的重要思想，即使用我们方法的用户无需知道我们 `first` 变量的存在，只要程序员知道即可；与之相对应的 `public` 方法则在某种意义上代表着我们将永远不会删除这个变量或者方法
- 对于嵌套类的使用，很有用的一种情况是某一个类只在另一个类中使用，例如本例中的 `IntNode` 只在 `SLList` 类中使用，所以可以考虑直接嵌套在 `SLlist` 类中来使用；而当嵌套类从不使用嵌套它的类中的信息，我们还可以在 `public/private` 后加上 `static`(还没讲为什么讲了再说)
- 在 `SLList` 方法中，当我们要编写 `size()` 函数时，会遇到 SLList 变量本身并不具有 `item next` 等特性，而这时我们需要以一个静态类型，以 `IntNode` 作为参数的方法来返回，具体如下：
~~~Java
/**Return the size of the list that starts at IntNode p. */
public static int size(IntNode p)
{
    if (p.next == null)
    {
        return 1;
    }
    return 1 + size(p.next);
}

public int size()
{
	return size(first);
}
~~~
- (虽然在自己尝试过程我发现其实只用上面的静态方法，调用时候 `size(L.first)` 似乎也行)
  另外一个体现用内存换时间思想的方式是始终设置一个 `size` 变量，在增删元素的时候改变其大小，最后在 `size()` 函数中直接返回size大小即可
- 这一节还讲了头节点(sentinel Nodes), 引入的思路来自在使用 `addLast` 方法时，如果本身是一个空链表，就没有所谓的 `first.next` 即null没有地址，更没有next，所以需要建立一个头节点，让所有链表的第一个实际元素是 `sentinel.next` ,这样就解决了刚刚的问题，即只需要在 `sentinel.next` 添加新元素
### DLList
