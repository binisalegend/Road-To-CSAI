本篇文章是BIT人工智能专业的限选课Java语言程序设计，可以和[[CS61B学习笔记]]结合一起学习（后者是使用Java语言讲授的数据结构课程）
# Class 1
如果一个类被声明为 `public` 那么当前文件名必须与其相同，这并不是说java程序中只能包含一个类，只是只能包含一个共有类 `public class`
Java程序从 `main` 开始执行，且 `main` 方法声明必须是共有且静态的 `public static`
`System(类名).out(类字段).println(标准输出对象方法)()` 可以直接打印一个空行  ^c9ae49

|转义字符| 字符 |转义字符| 字符 |
|---|---|---|---|
| `\\` |反斜杠| `\f` |换页|
| `\b` |退格| `\t` |跳出一个Tab|
| `\r` |回车| `\n` |换行|
| `\"` |双引号| `\'` |单引号|

Java类中的核心包以 `java` 开头（无需引用即可直接使用，如 `System`），扩展包以 `javax` 开头，第三方包以反写网址开头(如 `com.example`表示 `www.example.com` 的包)
- 以下是一个包含多个类的程序，以此演示调用静态和实例类型类的不同
~~~java
/** MultipleClassesJavaProgram.java */
class Class1
{
    public int outputInt(int x)
    {
        return 1024 + x;
    }
}

class Class2
{
    public static void printInfo()
    {
        System.out.println("调用Class2的printInfo方法");
    }
}

public class MultipleClassesJavaProgram
{
    public static void main(String[] args)
    {
        Class1 c1 = new Class1();
        Class2.printInfo();
        int v1 = c1.outputInt(6);
        System.out.println("调用了Class1的main方法");
        System.out.printf("%d\n", v1);
        System.exit(0);
    }
}
~~~
即静态类可以直接调用类函数，而实例类需要先实例化一个变量，再对变量进行赋值操作（可以看一下[[CS61B学习笔记#^9a36d4]]
# Class2
## *Lesson3: Java程序设计语法基础*
---
- 利用关键词 `final` 声明常量相当于 `public` 一个 `const` 类型变量，如果常量仅在本类使用就要定义为 `private` 类型
- `enum` 为枚举类型，具体调用方法有 `<枚举变量>.<变量名> = <枚举变量>.枚举元素 (如Size s = Size.SMALL)` 或 `Size t = Size.valueOf("SMALL")` ，也可以通过类似 `MyEnum <变量名> : MyEnum.values()` 来遍历枚举中的元素
- `JOptionPane.showInputDialog` 可以在显示的输入框中显示我们想显示的内容，同时可以使用 `JOptionPane.showMessageDialog(Component parentComponent, Object message, String title, int messageType)` 来控制输出形式，具体的可以看看官方文档
- 数据类型转化中精度问题：![[Pasted image 20230920191440.png]]
- `Integer.parseInt()` 可以将字符串类型变量转化为整型变量，而 `String.valueOf(variable)` 则可以将变量转化为字符串类型，结合 `write` 方法可以将内容输出到终端
- Java中可以直接将 `String + 其他类型变量` ，最终输出的是一个 `String` 类型变量
## *Lesson4: Java中的方法*
---
- 在调用类似 `Math` 库时可以使用 `import static java.lang.Math.*;` 命令，使得在代码中只写静态方法名而省略函数名
- 对于较大数的运算可以考虑用 `BigInteger` 变量，相比于 `double BigDecimal` 能避免精度丢失问题
  注意 `BigInteger` 的运算方式要调用 `.add .multiply` 等方法来进行
- 在Java中将一个方法放入类中，相当于C语言中定义一个函数，具体的语法格式为
~~~Java
访问权限 [static] 返回值类型 方法名(参数列表)
{

	return 表达式
}
~~~
- 生成随机数的一个惯用语句：`Random ran = new Random(System.currentTimeMills());`,这个语句使用当前时间作为“种子”来生成随机数
- 从JDK5.0开始，Java支持可变参数，基本代码如 `<variables class>... <variables name>`,注意当函数具有多个参数时，可变参数只能放在所有参数的最后（放前面识别不出来结束）
  在调用可变参数方法时系统自动为可变参数创造一个数组，在函数中以数组形式调用可变参数
- 对于 `System.out.println()` 可以输出不同类型参数，实际上调用了 `write(String.valueOf(<variable>))` 来将不同变量转化为String类型，再由write方法输出到终端
- 看PPT突然发现读取输入的另一种方式 `int x = Integer.parseInt(args[0]);` 可以直接读取第一行的数据（尤其是对于只有一个数输入的情况很好用）
- 在这里就已经能发现引用类内方法的迹象了 `Class ClassName = new Class()` ,具体的解释在[[#^bea8b9]]
- 计算机不能精确的比较浮点数，因此在执行 `0.00001 == 0.00000000000001` 时会返回true，因此应该比较其差的绝对值是否在某个范围之内 `Math.Abs(i-j) < 1e-10`
# Class3
## *Lesson5: Java中的类和对象*
---
Java中的类和对象可以理解成每个类都是为了某些特定对象而服务的方法集，在一个类中封装了面向一类对象的处理方法，而面向用户只开放特定的简单接口
1. 编写类的方法如下：
~~~Java
public/private class class_name{
	public/private <variable class> variable_name;
	public/private <return value variable class> function_name(parameter List)
}
~~~
2. 调用一个自定义类可以使用 `Class class_name = new Class()` 的语法，在调用类中的具体方法或者变量时使用 `class_name.<variable_name>()`  ^bea8b9
3. 我们在定义一个原始类型的变量时Java会要求立刻显式初始化变量，并且JDK会直接为该变量分配内存，如 `int value = 100;` ,而当我们声明一个对象类型的变量时系统不会立刻为变量分配内存，而是会让这个对象类型变量初始化为null，即 `Class obj = null;` ，如果一个对象变量不引用一个真实存在的已定义对象，就必须初始化为null
4. 在对象类型变量的赋值上，对于像如下这种类型的赋值，相当于把`other`类的指针也指向了`obj`类型的地址，因此当我们更改other类中的方法或者变量时，会导致obj类型中的变量同时发生改变，这个可以和[[CS61B学习笔记#^14da37]]类比着看
~~~Java
public class test{
    public static void main(String[] args)
    {
       MyClass obj = new MyClass(); 
       MyClass other = obj;
       other.x = 19;
       System.out.println(obj.x);
    }
}
class MyClass
{
    public int x = 0;
    private int y = 19;
}
>>> 19
~~~
5. 相似的，在判断两个对象类型变量是否相等时尽量不要用 `==` ,这样比较的是两个对象的地址是否相同（对于上面那个情况是可以的，但是如果是重新`new`了一个对象变量就不行了），尽量使用 `.equals()` 方式来比较(代码在这里[ObjectEquals](D:\大学资料\Road-To-CSAI\Java-Programming-for-Scientific-Problems\Class3Lesson5Code\ObjectEquals.java))
   - [ ] 对于这个 `.equals()` 的调用有点没看懂，讲义里写道有重写(override)和重载(overload)两种方式: 重写方式在方法前要加上 `@Override` 表示此方法是重写 `Object` 基类的的同名方法（这种以“@”打头的标记被称为“Annotation”），在方法中的对象类型参数为 `Object` 类型；而如果直接重载 `.equals()` 方法就不需要附加 `@Override` 标记，同时由于重载中 `.equals()` 的父类已经是最顶层的 `Object` 类，所以参数类型为当前方法所处的类名
   在代码的这一部分：
   ~~~Java
   public MyTestClass (int initValue){
	   Value = initValue;
	}
   ~~~
	以上位于类中的定义被称作类的构造方法（也被称作构造函数），构造方法的名称与类相同，没有返回值；同一个类可以有很多个构造函数，具体的构造函数由参数来区分，并且可以通过 `this` 来进行相互调用
6. 可以在类中直接使用 `{}` 将一个字段包裹起来，直接作为这个类的一个字段，作为类的“初始化块”，前面加上 `static` 就是静态初始化字段
7. 在类中可以定义静态字段 `static int total_employee_id`，在调用时需要以类名为前缀进行调用（用对象变量也行但不推荐）
8. 代码在这里[TestStaticInitializeBlock](D:\大学资料\Road-To-CSAI\Java-Programming-for-Scientific-Problems\Class3Lesson5Code\TestStaticInitializeBlock.java)
   - `extends` 表示继承，在定义一个类 `class <class_name> extends <father_class_name>` 表示一个类继承了一个父类的属性，在执行当前新定义类之前一定会先执行父类的初始化；同时，静态初始优先于所有的初始，因此静态初始化模块会优先执行
   - `super` 关键字代表当前对象的父类型特征，可以和 `this` 类比来看，当子类构造方法第一行中没有 `super` 定义时系统会自动加上无参数的 `super()` 方法，详细的解释可以看这个帖子[Java中super关键字及super()的使用](https://blog.csdn.net/pipizhen_/article/details/107165618) ^1f05af
9. 类的静态方法只能访问类的静态成员，静态初始化块只执行一次，同时创建子类型的对象时，父类型中的静态初始化块也会被执行
10. Java中提供了一系列的包装类（引用类型，可以创建相应对象），简单来说就是把基本变量类型首字母大写，具体作用是为基本数据类型提供了一些方法和字段，可以使用 `import package.class` 来引用一个包，也可以在文件前使用 `package <包的路径(把/换成.)>` 语句来将类加入到指定的包中
    在对上述这种进行将类放入自定义包中操作的文件进行编译时，使用 `javac -d 文件相对路径 文件名.java` 命令，系统会自动按照 `package` 语句中的路径创建文件夹并将 `.class` 文件放在文件夹中，但注意执行可执行文件时需要在根目录执行类似这样 `java Try.test.Hello` 的命令才能够正确运行
11. 学到了一个新的类：`StringBuffer / StringBuilder` 可以直接用 `.append() .insert() .delete()` 来对字符串进行一系列操作
# Class4
## *Lesson6: Java程序设计中的字符串*
---
1. 上来就是老生常谈好吧：`String` 类型比较相同不能使用 `==` ,用string自带的判定方式 `.equals()` 来进行判断（Java自带的内存压缩机制导致相同的变量可能被指向同一个地址，而如果 `new` 一个变量会导致指向一个全新分配的地址，`==` 比较的不是元素值而是地址，所以会返回 `false`）
2. `compareTo` :使用字典法进行比较,返回0表两字串相等,小于返回负值,大于返回正值
3. 这些方法记录在这，用的时候自己查吧(bushi): 
   1. `regionMatches`: 比较两字串的某一部分是否相等
   2. `startsWith`和`endsWith`: 查询字符串是否以某字符串开始或结尾
   3. `indexOf`和`lastIndexOf`: 在字串中查找字符或子串
   4. 操作函数

|功能函数|功能描述|
|---|---|
|`.substring(StartIndex, EndIndex)`|查找字符串中某一段的内容(经典含前不含后)|
|`str1.concat(str2)`|将str2接到str1后|
|`.replace(OldChar, NewChar)`|将旧字符替换为新字符|
|`.trim()`|去除头尾空格|
|`.toUpperCase() .toLowerCase()`|大小写转换|
|`.getChars(srcstart, srcend, string, strIndex)`|获取从指定位置起的子串复制到字符数组中|
4. `StringBuffer/StringBuilder`类的常用使用方法：`StringBuilder` 相较 `StringBuffer` 有速度优势
   1. 构造方法：`StringBuffer string = new StringBuffer(String str)`
   2. 操作函数
      
|功能函数|功能描述|
|---|---|
|`.capacity()`|不另外分配内存情况下 `StringBuffer` 还能存放的字符个数|
|`.ensureCapacity(int capacity)`|明确 `StringBuffer` 的最小容量|
|`.setLength(int length)`|指定 `StringBuffer` 变量的长度|
|`.charAt(int index)`|返回 `StringBuffer` 中位于 `index` 位的字符|
|`.setCharAt(int index, char ch)`|替换 `StringBuffer` 中位于 `index` 位的字符为 `ch` |
|`.getChars(int IndexOfPrevious, int length, char[] str, IndexOfNew)`|将 `StringBufffer` 中的字符片段拷贝到字符数组中|
|`.reverse()`|倒转 `StringBuffer`|
|`.append(char[]/String str)`|在 `StringBuffer` 后加上一段字符串|
|`.insert(int index, string/char[] str)`|从第 `index` 位开始插入字符串|
|`.deleteCharAt(int index)` & `delete(int StartIndex, int EndIndex)`|删除 `StringBuffer` 中的某一个(段)字符|
## *Lesson7: Java中的正则表达式*
^b2609e
---
- PS：当初听[[Missing-Semester学习笔记#^cd331a]]数据整理这一节的时候一点都没听懂，倒是没想到现在还是得学hhh
正则表达式：对字符串本身具有特性的形式化表达，用来描述字符串“模式”
**正则表达式主要由普通字符和元字符(meta character)组成**
1. 字串字面量匹配(literal)
   `/abc/`匹配“abc”字符串(但不会匹配到像`"a bc"`的字符串，空格会影响到字串匹配)，但是这样的方式只会匹配到文档中最前面的那个匹配字符串，在命令中选择global模式 `/abc/g` 可以匹配文档中全部匹配字串
2. “元字符”匹配
   1. 元字符指正则表达式中具有一些特殊含义的字符，主要有 `\ . * + - {} [] ^ $ | ? () : ! =` 等，例如 `.` 代表任意一个单个字符，`*` 代表任意一段字串
   2. 当我们想把元字符当作普通字符使用时，就需要使用 `'\' + 元字符` 来对元字符进行转义
   3. 其他的特殊字符
   
  |要匹配的字符|在正则表达式中应该写...|
  |---|---|
  |Tab|`\t`|
  |回车，换行|`\r`(代表回车)，`\n`(代表换行)，`\r\n`(代表回车换行)|
  |ESC|`\e`|
  |ASCII码字符|如`0xA9`要写作:`\xA9`|
  |Unicode字符|如`4e00`要写作：`\u4e00`|
3. 定义可选字符集合
   - 使用 `[` 和 `]` 定义字符串中某个位置（注意是单个位置）的“候选字符集合”
   - 例如 `[aeiou]` 表示搜索这五个字符; `gr[ea]t` 表示搜索 `gret` 和 `grat`，即在第四位是e或a的字符
   - 同时使用 `-` 可以定义一个字符区间，如 `[0-9]` 可以表示10个数字，`[A-Z]` 表示26个大写字母
   - 特例：`[50-99]` 真实的意义并不表示50-99这个数字区间，而是相当于 `[5][0-9][9]` 实际上就是0-9的区间；如果要表示50-99则应该分位进行搜索，即 `[5-9][0-9]`
4. 定义例外字符集合
   - 使用 `^` 定义在某文档中排除的字符，如 `see[^mn]` 表示排除掉以mn结尾的单词，`[^a-z]` 表示排除掉所有小写字母
5. 处理特殊的字符
   对于 `] - ^ \` 包围在 `[]` 中有时候需要进行转义，如 `/var [[(] [0-9] [\])]/` 表示数字由 `[]` 或 `()` 包围（后边的 `]` 为了不与可选字符集合边界混淆需要进行转义）
6. 字符集合的缩写![[Pasted image 20231026235908.png]]
   - 浅总结一下：小写 `d w s` 分别表示数字、数字和大小写、空白(包括空格、Tab、回车（\r）和换行（\n）)，大写的 `D W S` 就表示非前面说的字符
7. 处理重复的“贪婪量词”
   - `*` 表示指定字符重复0次或n词，`+` 表示指定字符出现1次或n次，`?` 表示指定字符出现0次或一次。(注意：如果不加括号的话贪婪量词都只作用于紧跟着的前一个字符)
8. 指定次数的重复
   使用 `{min, max}` 来指定重复次数，其中min必填且最小为0，而max可选
   - 如 `\d{4,}` 表示最小四位的的数字字串，`\d{4}` 表示4位数字字串 
   - 注意默认情况下系统会自动匹配尽可能多的字符，而可以使用一种叫“Lazy Expression”的表达方式使其匹配尽可能少的字符---`*? {min, max}? +? ??`(其实就是重复量词后面加个？)
9. 分组
   `()` 把若干个字符当作一个整体进行处理
10. 多选一
    - 使用 `|` 从多个选项中选择一个进行匹配，左边的选项具有高优先级。如 `w(ie|ei)rd` 匹配weird和wierd
11. 字符串的开头与结尾
    - 使用 `^` 来指定起始字符，如 `^\d+[a-z]*` 表示以至少一个数字开头，后面接任意个数的小写字母
    - 使用 `$` 来指定结束字符，如 `^\d\-[a-z]+$` 表示至少以一个小写字母为结尾的字符串，如 `5-adfjk`
	!!要注意的是正则表达式默认引擎都是singleline，即对于所行文本只会匹配最开头和最结尾的字符；想要匹配多行首尾字符则需要切换Multline anchors模式!!![[Pasted image 20231027085858.png]]
12. 处理单词的边界
    - 使用 `\b` 和 `\B` 来代表单词的边界和非单词的边界，如匹配段落中的所有单词可以使用 `\b\w+\b`
13. 反向引用
    1. 可以使用 `\1 \2 ...` 来引用前面出现过的已经被 `()` 分组的字符组
    2. 由于一般正则表达式引擎都只能处理9个反向引用，我们使用 `?:` 来指定某字符组不参与反向引用；如 `(?:orange) and (peach) to \1` 会匹配到 `orange and peach to peach` 而不是 `orange and peach to orange`
14. 断言
    - 可以使用 `?=` 给字符串加上条件判断以影响匹配进程，要注意的点是，`?=` 后的正则表达式并不会出现在匹配字符串中，他们只用来影响匹配进程
    - 同时，使用判断后能够回到起点的断言，可以对一个字符串根据多个标准进行判断
    - 可以使用 `?!` 表示一个“否”断言，如 `?!.*4321` 表示不包含4321的字串
    - 使用 `?<=` 和 `?<!` 可以明确告知正则引擎进行断言回退，如 `/(?<=base)ball/` 表示如果发现了ball，就应回退检查其前面是不是base，若是则匹配
15. Java中对正则表达式的编译(pattern)和匹配(matcher)方法
    1. 在 `String` 类中，`matches()` 方法可以验证字符串是否符合指定的正则表达式，`replaceAll()` 方法可以将符合正则表达式的字符串替换为指定的字符串，`split()` 可以以正则表达式进行分割
    2. 如果某正则表达式需要用很多次，则可以先调用java.util.regex包中的 `Pattern` 类的 `compile` 方法得到一个“编译后”的 `Pattern` 对象，再调用其 `matcher` 方法得到一个 `Matcher` 对象，对 `Matcher` 对象调用它的 `matches()` 方法进行正则表达式验证，模板如下
       ~~~Java
       Pattern expression = Pattern.compile("...");

	   String str1 = "..."

	   Matcher matcher = expression.matcher(str1);

	   while (matcher.find())
		   System.out.println(matcher.group());
	   ~~~
# Class5
## *Lesson8: Java中的继承、抽象类与接口*
---
- 继承
	**指既具有父类的一切特性，同时又具有自己的独有特性，通常称为 `IS_A` 关系**
	1. 继承的语法：`class <child class> extends <parent class> {}`，其中parent class和super class通常指某一类的直接上级，而base class通常指公共的基类
	2. 子类自动拥有父类声明为 `public` 和 `protected` 的成员，这也是继承特性的体现之一（下附继承条件下类的访问权限表）
	3. 使用继承类时，其实系统都会默认在第一行有一个 `super()`,而我们可以在第一行使用 `super(variables)` 来调用父类中参数匹配的其他功能；但无论如何，**子类的构造方法在运行之前，必须调用父类的构造方法。** 具体可以康康这个[[#^1f05af]]
	4. 以 `final` 声明的类不允许覆盖和更改，可以更加方便的用于多线程环境中
	5. 父类与子类之间的关系可以有以下三种：
	   1. `Extends`(扩充): 子类中定义的方法在父类中没有同名方法
	   2. `Override`(覆盖/重写): 子类和父类定义了完全一样的方法
	      在“+”运算中，当一个变量和String类型变量执行操作时，系统会自动隐式调用其 `toString()` 方法将其转化为字符串类型变量；默认情况下该方法返回 `<class name> + hashnode`，而如果需要其输出其他有意义信息则可以在当前类中重写该 `toString()` 方法 **注意一定要和父类方法一模一样！！否则就是重载(overload)了**
	   3. `Overload`(重载): 子类和父类的方法名相同，但两者的参数类型或数不一样
	
|声明|访问权限规则|
|---|---|
|`public`|外界自由访问|
|`private`|外界不可访问|
|`protected`|同一包中的子类、派生于同一父类的包的子类都可以访问|
|`default`|如果不指明任何权限，默认同一包中的类可以访问|
	
- 抽象类
	**有abstract修饰的类称为抽象类;在方法前加上abstract就形成了抽象方法**
	1. 抽象类只定义了什么方法应该存在，不能创建对象，必须派生出一个子类，并在子类中实现其未实现的方法之后，才能使用new关键字创建对象；抽象方法只有方法声明，没有实现代码。例：
	~~~Java
	abstract class person
	{
		public abstract String getDesCription();
	}
	~~~
	抽象类中可以包含非抽象方法和静态变量，即包含抽象方法的类一定是抽象类，但是抽象类中的方法不一定都是抽象方法
	2. 抽象类的三种类型
	   1. 直接定义抽象方法
	   2. 继承一个抽象父类，但没有包含所有父类中的抽象方法（如果包含了所有抽象方法就可以作为一个子类创建对象了，不再是抽象类）
	   3. 实现了一个接口，但没有完全包含该接口所包含的抽象方法
	3. 抽象类的使用
	   抽象类不能直接创建对象，通常用来引用子类对象，语法格式如下：`<abstract class> <abstract class variable> = new <child class from abstract class>`
	4. 抽象类的作用
	   在我们进行程序设计时，可以先思考项目需要实现什么功能，这些功能步骤就相当于是抽象的行为，即抽象类；然后我们可以再通过继承方法，实现对应更为细致功能的类，以此实现模块化的程序设计
- 接口
  1. 定义一个接口使用关键字 `interface`，实现一个接口采用关键字 `implements`;接口的成员函数自动成为public的，数据成员自动成为static和final的。
  2. 接口使用语法：`接口类型 接口类型的变量 = new 实现了接口的具体类型();`
  3. 接口的扩充：使用 `extends` 继承来扩充已有接口并实现一个新的接口；需要注意的是，实现子接口的类，必须实现“父”“子”接口所定义的所有方法，才能被实例化（即new出一个对象）
  4. 接口中定义常量：
     ~~~Java
     public interface ArrayBound{
	     public static final int lower_bound = 0;
	     public static final int upper_bound = 0;
     }
     ~~~
	 以这种方式定义的接口常量，只要被一个类声明实现，就可以直接使用这些常量(**变量必须被初始化**)
  5. 接口可以理解为，面向符合该接口设定类的一组需求
> **接口与抽象类的区别**：
> 1. 抽象类是一个不完全的类；接口则只表明类有哪些外部特征但不涉及具体实现细节
> 2. 接口不具备继承特点，只是承诺了外部可调用的方法
> 3. 一个类可以包含多个接口，但是只能继承一个父类

# Class6
## *Lesson9: Java程序设计之多态*
---
**多态(polymorphism)：指相同的一条语句在不同的类中进行不同的解释，在不同的运行环境中能够运行出不同的结果**
1. 多态的最本质特征即父类（或接口）变量可以引用子类对象（或实现了接口的类），即将子类对象当作基类对象来使用，可以让更一般的对象容纳更具体化的对象：
   ~~~Java
   Parent p = new child();
   ~~~
2. 基类变量与子类变量之间的赋值
   1. 子类对象可以直接赋给基类对象变量
   2. 基类对象赋给子类对象变量需要进行变量类型转换，语法为 `<child class variable> = (child class)<base class>`；可以使用 `classA instanceof classB` 来判断一个对象是否能转换成指定的类型，转换失败会抛出 `ClassCastException` 异常
3. 当子类和父类具有同名方法，并且让一个父类变量引用一个子类变量时，具体调用哪个方法取决于对象本身的类型是父类还是子类
4. 如果父类和子类中具有相同的字段，子类中访问方法会访问子类本身的方法，父类中的方法会被隐藏（如果确实需要访问使用 `super` 关键字）；而如果子类被当作父类使用时则会调用父类中的方法
5. 当多个类实现同一接口中的方法时，针对这些类所创建的对象调用接口所定义的方法时，会分别调用相应的类的具体实现代码。同时，编译器在编译上述代码时采取“滞后绑定”(late bind)方法，即编译器在编译时并不知道调用了哪个方法
   如果没有进行强制转换，编译器会将所有都识别为父类的方法和字段值，因此在TestPolymorphism示例中输出的 `value` 值都是父类的100，而当我们进行强制转换后，经反编译我们可以看出编译器会进行 `checkcast` 操作识别出字符串值的具体归属
6. 使用多态最大的好处即修改程序或是扩充系统时修改代码较少，且对其他代码部分的影响较小
**面向对象编程的思想就是，先构思过程，再细化每个过程涉及的相关数据，最后再针对具体数据完善对应的操作**
## 小专题之快速幂和矩阵快速算法
---
1. 快速幂算法基本步骤：
   1. 将指数n表示为其二进制形式。例如，将n表示为二进制数 $n = b_k * 2^k + b_{k-1} * 2^{k-1} + ... + b_1 * 2 + b_0$，其中 $b_i$ 表示二进制位的值（0或1），k 是二进制位数。
   2. 初始化一个变量 result 为 1，用于存储最终的计算结果。 
   3. 从最高位开始，从左向右遍历二进制位。对于每一位 $b_i$，进行以下操作：     
    - 如果 $b_i$ = 1，将 result 乘以底数（要求的数的幂），即 result = result * base。
    - 将底数 base 自乘一次，即 base = base * base。
   4. 继续遍历下一位，重复步骤3，直到遍历完所有二进制位。  
   5. 当遍历完所有位后，result 就包含了底数的n次幂的值。
   6. 快速幂代码示例
      ~~~Java
      private static int FastNthRoot(int num, int sqrt)
      {
	      int base = num;
          int result = 1;
          while (sqrt > 0) 
          {
              if ((sqrt&1) == 1)
              {
                  result *= base;
              }
              base *= base;
              sqrt = sqrt >> 1;
          }
          return result;
      }
      ~~~
2. 矩阵快速乘法(斐波那契数列)：
- 使用矩阵来表示斐波那契数列关系式 `F(n) = F(n-1) + F(n-2)` 如下：$$\begin{bmatrix}F(n) \\F(n-1)\end{bmatrix}=\begin{bmatrix}1 & 1 \\1 & 0\end{bmatrix}\times\begin{bmatrix}F(n-1) \\F(n-2)\end{bmatrix}$$  利用快速幂算法计算矩阵 $\begin{bmatrix}1 & 1 \\1 & 0\end{bmatrix}$ 的n-1次幂，结果矩阵的第`[0][0]`项就是斐波那契数列的第n项
## 小专题之位运算相关
---
1. 位运算符号概览

|符号|描述|运算规则|
|---|---|---|
| & | 与(且)运算 | 两位都为1时才返回1 |
| \| | 或运算 | 两位都为0时才返回0 |
| ^ | 异或运算 | 两位相同为0，不同为1 |
| ~ | 取反运算 | 0变1，1变0 |
| << | 左移运算 | 各二进位全部左移若干位，高位丢弃，低位补0 |
| >> | 右移运算 | 各二进位全部右移若干位，对无符号数，高位补0，有符号数，各编译器处理方法不一样，有的补符号位（算术右移），有的补0（逻辑右移）|
2. 按位与 `&` 运算符
   1. 例如：`3 & 5 = 0011 & 0101 = 0001`, 故 3&5 返回1
   2. 用途
      1. 清零：将各位与0进行相与操作，均返回为0
      2. 判断奇偶：只需根据二进制末位是0还是1来判断，即 `if((a&1)==0)` 来判断是不是偶数(1的前几位都是0只有最后一位能产生效果)
3. 按位或 `|` 运算符
   1. 例如：`3 | 5 = 0011 | 0101 = 0111`, 故 3|5 返回7
4. 异或 `^` 运算符
   1. 交换律、结合律、自反性均成立
   2. 用途
      1. 与0相异或值不变
      2. 交换两个数(代码示例如下)
         ~~~C++
         void Swap(int &a, int &b)
         {
	         if (a != b)
	         {
		         a ^= b;
		         b ^= a;
		         a ^= b;
	         }
         }
         ~~~
5. 左移 `<<` 右移 `>>` 运算符
   1. 左移相当于各二进制位全部左移若干位，左边的位丢弃，右边补0；如 `a = 10101110; a = a << 2` 执行操作后相当于 `a = 10111000`
      **若舍弃的高位不含1，则每左移一位都相当于该数乘2**
   2. 将一个数的各二进制位全部右移若干位，正数左补0，负数左补1，右边丢弃；如 `a = a >> 2` 执行操作后相当于 `a = 00101011(a > 0)` 或 `a = 11101011(a < 0)`
      **操作数每右移一位相当于该数除二**
# Class7
## *Lesson10: 泛型程序设计*
---
### 泛型类
1. 使用泛型的目的：限制集合能接收的数据类型，并且避免了类型转换的需要。语法一般为如 
   - [x] `ArrayList<String> strList = new ArrayList<String>();`
2. 相关术语
   1. `ArrayList<E>` 定义了一个泛型类型，`E` 称为“类型变量”或“类型参数”
   2. `ArrayList<Integer>` 称为“参数化的类型”，`Integer` 称为“实际类型参数”。
   3. `ArrayList` 称为泛型类型 `ArrayList<E>` 的“原始类型(raw type)”
3. 使用泛型可以减少类的数目，同时能在编译中检查代码中的类型错误
4. 注意：Java7后语法变为：`ArrayList<String> strList = new ArrayList<>();`
5. 泛型对象具有自动装箱特性，即如 `ArrayList<Integer> IntList = new ArrayList<>();  IntList.add(3);` 实际上是按照 `IntList.add(Integer.valueOf(3));` 来进行的；`int n = IntList.get(0)` 将被按照 `int n = IntList.get(0).intValue()` 来执行。因此在使用泛型类时应尽可能明确数据类型，防止在循环中过多出现装拆箱现象
6. 泛型使用须知：
   1. 泛型参数必须是引用类型而不能是基本数据类型，即只能为 `Double String Integer` 等
   2. 不能定义泛型化数组
       - [x] 像 `Pair<String>[] strPair = new Pair<String>[10]` 是不可接受的
       正确的方法应该是这样：
       ~~~Java
       public class GenericArray<T> {
		   T[] items;
		   int size;
		   @SuppressWarnings("unchecked")
		   public GenericArray(int size) 
		   {
			   items = (T[]) new Object[size];
			   this.size = size;
		   }
		   
		   public GenericArray(T[] items) 
		   {
		       this.items = items;
			   this.size = items.length;
		   }
	   }
       ~~~
   3. 泛型类型不能直接创建实例
   4. 泛型类不能继承自 `Throwable` 类(Java中所有错误或异常的超类)，所以我们也不能直接捕获或抛出泛型类型的异常对象
   5. 不能定义静态 `static` 泛型成员
7. 从泛型类中派生子类
   1. 不允许基类中具有泛型参数，即 `class MyChild extends MyClass<String>` 可以编译但
      - [x] `class MyChild extends MyClass<T>` 是错误的
   2. 如果继承自泛型类的子类不指定实际类型参数，则泛型参数类型默认为 `Object`
### 泛型方法
1. 泛型方法的定义
   ~~~Java
   class ArrayAlg {
         public static <T> T getMiddle(T[ ] a) {
                   return a[a.length / 2];
           }
    }
    String[] names = ...
	/*下面的两句代码等价，编译器能自动推断传入参数的实际类型*/
    String middle = ArrayAlg.<String>getMiddle(names);
    String middle = ArrayAlg.getMiddle(names);
    ~~~
2. 泛型类同样可以接收 `...` 定义的可变参数类型 
### 泛型的多态特性
1. 泛型多态特性实例
   ~~~Java
   public class GenericPolymorphism {
		public static void main(String[] args) {
			List<Number> nums = new ArrayList<Number>();
			nums.add(2);
			nums.add(3.14);
			for (Number number : nums) {
				System.out.println(number.getClass());
			}
		}
	}
	~~~
	1. 一个值得注意的点是，`ArrayList<Number>` 对象可以直接赋值给 `List<Number>` 变量
	2. `add()` 方法奏效的原因是因为 `Integer` 和 `Double` 类都是 `Number` 类的子类
	3. `List<Number>` 不是 `List<Integer>` 的基类型，所以 `nums` 变量不能引用一个 `List<Integer>` 对象
### 泛型约束
- 我们可以指定泛型参数具有某些特性，例如是某个类的子类、是某个接口等，这时就需要我们引入泛型约束这一概念
1. 首先，在泛型方法中指定泛型方法的泛型参数类型必须实现Comparable接口，例子如下：
   ~~~Java
   public static <T extends Comparable> T min(T[] a)
   {
	// 可以有多个约束条件，但只有第一个可以是一个类
   }
   ~~~  
   在进行泛型约束限定类后，泛型参数就只能是限定类的子类，例如如果限定了 `<T extends Number>` 则允许以 `Integer` 和 `Double` 等类型作为泛型参数，但 `String` 就不能作为这个类中的泛型参数
2. 类型通配符 `?` 
   使用类型通配符可以解决父类集合变量引用子类集合对象的问题
   1. 在不适用类型通配符的情况下，假如 `Child` 类派生自 `Parent` 类，当我们定义了 `List<Child> ChildList = new ChildList<>()` 时，这个列表中只能添加子类 `Child` 类型对象，而像 `ChildList.add(new Parent())` 的操作是不合法的
   2. 我们为了让某个泛型同时引用父类和子类集合，可以使用这样的定义方式 `<? extents Parent>` 表示泛型参数必须是 `Parent` 的子类；相似的，`<? super T>` 表示泛型参数必须是 `T` 的基类
   3. 泛型参数可以有多个约束，如 `<T extends Comparable & Serializable> T mtd()`
### 泛型“擦除”原理
受限于Java虚拟机本身不支持泛型，所以在JVM进行编译时会产生泛型擦除现象，示例如下
~~~Java
public class Pair<T> --> Pair<Object>  //没有泛型约束的直接擦除为Object
public static <T extends Comparable> T min() --> public static Comparable min()  //有泛型约束擦除泛型参数
public static <T extends Comparable & Serializable> T mtd() --> public static Comparable mtd()  //多个泛型约束只保留第一个约束，剩下全部擦除
a instanceof Pair<String> --> a instanceof Pair  //instanceof 应用于泛型时，擦除泛型参数只保留原始类型
~~~
泛型擦除可能会导致很多“奇怪”的编译现象，如下实例中，由于擦除现象会导致程序返回 `true`
~~~java
List<String> strList = new ArrayList<String>();
List<Integer> intList = new ArrayList<Integer>();

System.out.println(strList.getClass() == intList.getClass());
~~~
## *Lesson11：Java中的内部类*
---
1. 内部类 (Inner Class) 的定义直接包容在另一个类内部，形象化来说就是一个类中的好多方法有比较紧密的联系，所以把他们再包装一下放在一起
2. 内部类与外部类中的成员具有相同的地位，因此内部类中可以自由访问外部类中包括私有的方法成员
3. 内部类在编译后通常会产生一个名为 `<OutClass name>$<InnerClass name>.class` 的文件
4. 内部类有以下几种类型：
   1. 静态内部类`static class`:
      - 特性：不能访问其外部类的对象的实例数据，但可以访问其静态成员（包容字段与方法）
      - 使用场景：当需要编写许多静态方法及静态字段时，将逻辑上密切相关的代码组织成静态内部类
   2. 成员内部类 `class`:
      - 特性：不带有 `static` 关键字，可以访问外部类中的任何成员，同时外部类也可以访问内部类的所有成员
        在能够调用内部类的方法，以及为其数据字段赋值之前，外部类必须首先创建内部类的实例
      - 实例化成员内部类语法有所不同：`<OuterClass>.<PublicInnerClass> PublicInnerClass_name = OuterClass_name.new <PublicInnerClass>()`
      - 使用场景：注意一般成员内部类应设置为 `private` 以不允许外部类直接访问，这是面向对象的封装特性的应用实例
   3. 静态内部类 & 成员内部类：
      - 静态内部类: 适合于封装那些与特定类型相关的公用代码，这些代码不依赖于外部的状态，也不依赖于具体的对象；最典型的就像数学公式函数
      - 成员内部类: 主要用于分割代码并进行打包，在类内部实现代码重用；成员内部类的代码通常会直接访问外部实例对象，会与特定对象进行绑定
   4. 本地内部类(在一个方法中定义的类)
      - 特性：方法体和本地内部类可以访问彼此的局部变量和成员
      - 需要注意的是本地内部类也需要实例化后才能够使用，这个是正常的实例化方式，new就行
      - 主要优势在于是便于在一个方法内部重用代码
   5. 匿名内部类：
      - 特性：**没有名字**，可以省去为那些“仅用一次”的代码定义单独的类的麻烦，简化代码，避免出现“类”数目过多的弊端
      - 使用方式：在方法调用语句中直接声明一个实现指定接口的“没有名字”的内部类，并立即使用new关键字创建一个它的实例，示例如下：
        ~~~java
        private int outerField = 100;
        public void InnerVisitOuterField()
        {
	        var innerObj = new MyInnerFace // 不用再单独建一个InnerFace类了
	        {  
		        @Override
		        public void func()
		        {
			        // 访问外部类的私有字段
			        AnoymousInnerClassTest.this.outerField++;
			        System.out.println(outerField);
		        }
	        };
	        innerObj.func();
        }
        ~~~
      - 拥有基类的匿名内部类：不使用接口，而是使用Java最顶层的基类Object，我们可以随意定义并获得一个匿名内部类的实例并立即调用它的方法
      - 使用场景：某个对象**仅在**这个地方使用，具有可视化界面的GUI界面中，以及下一讲中的lambda表达式
      - 匿名内部类本身展示了“把代码本身当作数据”的思想(因为整个此部分代码变成了另一个方法的参数)
# Class8
## *Lesson12：Java中的lambda表达式*
---
- 只定义有一个抽象方法的接口，成为单一抽象方法--SAM；在开发中可以通过顶层类、内部类和匿名类三种方式来实现SAM，示例如下：
~~~Java
// 定义SAM接口MyInterface
interface MyInterface {
	void func();
}

// 定义静态调用接口定义方法
public static void doWithMyInterface(MyInterface obj) {
	obj.func();
}

// 1.使用传统实现方式
class MyClass implements MyInterface {  // 外部定义一个类实现接口
	@Override
	public void func() {
		System.out.println("traditional method")
	}
}

MyClass myclass = new MyClass();
doWithMyInterface(myclass);

// 2.使用本地内部类方式
class MyInnerClass implements MyInterface {  // 在方法内定义一个类实现接口
	@Override
	public void func() {
		System.out.println("Inner class method")
	}
}

doWithMyInterface(new MyInnerClass())

// 3.使用匿名内部类方式
doWithMyInterface() {
	@Override
	public void func(){
		System.out.println("Anonymous-Inner Class method")
	}
}
~~~
在以上的三种方法中，都需要分步骤调用相关静态方法来使用接口，而使用lambda特性则如下：
~~~Java
// 定义一个lambda表达式并将其引用保存到变量中，节省新建一个类的工作任务
MyInterface lambdaObj = () -> {
	System.out.println("Explicit Define Lambda object's func()");
}
doWithMyInterface(lambdaObbj);

// 直接将lambda表达式作为方法参数，甚至不需要重新定义一个新的变量
doWithMyInterface(() -> {
	System.out.println("Inline lambda object's func()");
})
~~~
1. 我们可以将一个lambda表达式看作是一个整体，例如上述方法中lambda表达式其实就作为 `doWithMyInterface` 方法调用时的一个实参；同时，lambda表达式具有 **延迟执行(deferred execution)** 特性，即定义变量时并不会执行，只有在显式调用它的时候才会执行
2. lambda表达式语法如下：
   ~~~Java
   ( ) -> { }  
   ():传入参数，如果只有一个参数可以省略括号
   { }:lambda执行语句，如果只有一条语句可以省略括号 
   ~~~
3. lambda表达式可以应用于赋值给一个SAM接口变量，或者作为一个方法调用的实参(参数类型为SAM接口)。SAM接口有另一个更常用的名字，叫作“函数式接口（Functional Interface），具体的解释详见第六条
4. lambda表达式在Java中的短板：由于没有引入真正的“函数类型”，Java的Lambda特性必须依托于特定的函数式接口，这使得在调用时必须使用函数式接口中所定义的抽象方法 去调用一个接收了lambda表达式的变量，才能执行这个Lambda表达式中的代码
5. 以下是另一个按照字符串长度对字符串数组进行排序的lambda表达式应用实例：
   ~~~Java
   // 不使用lambda表达式
   class LengthCompator implements Comparator<String> {
	   public int compare(String str1, String str2) {
		   return str1.length() - str2.length();
	   }
   }
   Arrays.sort(str, new LengthCompator());
   
   // 使用lambda表达式
   Arrays.sort(str, (String str1, String str2) -> str1.length() - str2.length());
   // 相当于lambda表达式已经定义了一个Comparator的泛型类作为比较器
   ~~~
- 函数式接口(functional intersface)
   1. Java8中用 `@FunctionalInterface` 来标识一个函数式接口，Java8之前就是我们之前提到的SAM：Single Abstract Method。这个注解不是必须的，但是当加入此注解并且接口并不符合函数式接口要求时，Java编译器会提出报错
   2. 函数式接口的抽象方法的签名称为“函数描述符”，例如 `void run()` 的 `void`；实际开发中编译器会根据描述符对lambda表达式进行推断以确定lambda表达式是否符合此函数式接口的要求
   3. 在统计某接口的抽象方法个数时，以下类不计算在内：
      1. 默认方法 (Default methods，Java8+新增特性)
         ~~~Java
         // 定义方法
         @FunctionalInterface
         interface Printer {
	         // 唯一的抽象方法
	         void print(String msg);
	         // 默认方法
	         default void welcome(){
		         System.out.println("hello");
	         }
         }
         
         // 调用方法
         public static void main(String[] args) {
	         Printer printer = (msg) -> System.out.println(msg);
	         printer.welcome();
         }
         ~~~
         - 实现某接口的类自动拥有默认方法，无需重写
      2. 静态方法 (Static methods，Java8+新增特性)
         定义和实现方法同上，关键字为 `static`，实现接口的所有类同样自动拥有接口中的静态方法
      2. Object类定义的公有方法
   4. 函数式接口的可包容成员类型
      1. `final` 类型接口常量
      2. `<function method significance> <method name>()` 唯一抽象公有方法
      3. `<function method significance> <Object method name>()` ：如 `toString()` 等，作为 `Object` 类的共有方法
      4. `private (static) <f-m-s> name()` 接口中私有实例和静态方法
      5. `default & static` 接口中默认和静态方法
   5. 实现函数式接口中，定义函数式接口具体类型后自动具有接口中定义的默认和静态方法
   6. 函数行接口的简单应用演示
      ~~~Java
      Comparator.comparing((String s) -> s.length())
      .thenComparing((String s) -> s,
				     (String s1, String s2) -> s1.compareTo(s2));
      // 更加简化版的
      Comparator.comparing(s -> s.length())
      .thenComparing(s -> s, (s1, s2) -> s1.compareTo(s2));
      
      // 学完以后的超进化
      Comparator.comparing(String::length)
      .thenComparing(String::compareTo)
      ~~~
   7. 泛型函数式接口
      1. 示例源码以及应用(以Function泛型接口为例)
         ~~~Java
         // Function函数接口的源码实现
         @FunctionalInterface
         public interface Function<T, R> {
	         R apply(T t);
         }
         
         // 使用示例
         // (1)接受一个String类型的字符串参数
         // (2)返回一个Integer类型结果
         Function<String, Integer> stringLength = str -> str.length();
         // 通过apply()方法调用
         System.out.println(stringLength.apply("hello"));  // 5
         ~~~
      2. Java开发中非常常用的函数式结构类型
      
|接口名|函数签名|
|---|---|
| `Consumer<T>` | `void accept(T t)` |
| `Supplier<T>` | `T get()` |
| `Function<T, R>` | `R apply(T t)` |
| `Predicate<T>` | `boolean test(T t)` |
- Lambda表达式的基础语法
  1. 函数型接口的定义与实例化示例
     - 相当于使用lambda表达式将类调用的接口中的抽象方法 `doSomething()` 赋予了具体效果为函数无需参数，直接打印语句
     ~~~Java
     @FunctionalInterface
     public interface SimpleInterface {
	     void doSomething();
     }
     
     // 实例化
     SimpleInterface obj = () -> System.out.println("this is a lambda example");
     obj.doSomething();
     ~~~
     - 如果lambda表达式有多条语句是可以使用 `{ }` 包围语句
  2. 闭包
     - lambda表达式可以访问表达式外部的变量，Lambda+外部变量构成一个“闭包 `Closure`”，相当于lambda表达式运行的总体环境(注意：lambda表达式并不定义一个新的变量作用域，因此如果在表达式内定义一个与外部变量相同的变量名是无法通过编译的)
     - lambda表达式访问的外部变量必须是effectively final的，即要么使用 `final` 定义的直接常量，要么没有使用 `final` 定义但是只被初始化了一次
- 方法引用
  1. 对于像如下代码：
     ~~~Java
     // 创建一个含有五个元素的集合
     var nums = List.of(1, 2, 3, 4, 5);
     // 使用lambda表达式遍历输出集合的全部数字
     nums.forEach(num -> System.out.println(num));
     ~~~
     lambda语句仅有一句，即传入参数并输出；在这种情况下，编译器只需要知道需要调用的函数即可推断出其余信息，因此上述语句可以简化为仅包含方法名的下述形式：
     ~~~Java
     nums.forEach(System.out::println);
     ~~~
  2. 使用方法引用的前提：lambda表达式只有一句，且为方法调用语句
  3. 使用方法引用简化lambda代码示例如下：
     1. 以 `sort` 函数为例
     ~~~Java
     // 对于sort函数的源码声明
     public static <T> void sort(List<T> list, Comparator<? super T> c)
     
     // 原始版本
     Collections.sort(people, (p1, p2) -> this.compareAge(p1, p2));
     // 简化为：
     Collections.sort(people, this::compareAge);
     // 进一步简化为：
     people.sort(this::compareAge);
     
     // 对于静态方法引用：
     people.sort(Person::compareAge);
     ~~~
     2. 以 `Supplier<T>` 和 `Math.random()` 为例
     ~~~Java
     // Supplier<T> 接受一个无参函数并返回一个类型T
     Supplier<ExampleClass> supplier = () -> new ExampleClass();
     // 简化为
     Supplier<ExampleClass> supplier = ExampleClass::new;
     
     // 原始版本
     Stream.generate(() -> Math.random())
	     .limit(10)
	     .forRach(System.out::println);
	 // 简化为
	 Stream.generate(Math::random)
		 .limit(10)
		 .forEach(System.out::println);
     ~~~
     3. 以 `CompareTo()` 方法为例
     ~~~Java
     // 原始版本
     List<String> strings = Arrays.asList("this", "is", "a", "list", "of", "strings");
     strings.stream()
	     .sorted((s1, s2) -> s1.compareTo(s2));
	 // 简化为
	 strings.stream()
		 .sorted(String::compareTo);
     ~~~
  4. IntelliJ会对可以转化为方法引用的语句提示，相应代码会自动地简化为使用“方法引用”，所以，方法引用这个语法特性，其实是不需要死记语法规则的。
## *Lesson13：Java中的Stream API*
---
- Stream API概述
  1. 定义：“流（Stream）” ：从支持数据处理操作的源生成的元素序列。
     - 元素序列：流包容的一组数目不限的数据
     - 源：流从 “源（通常是集合）” 中 “抽取” 数据
     - 操作：代表对数据的具体处理工作
  2. Stream API的示例
     - 传统编程方式：
     ~~~Java
     int count = 0;
     List<String> students = Student.getStudents();
     for (Student stu: students) 
     {
	     if (stu.getFrom().equals("北京")) count++;
     }
     System.out.println("来自于北京有学生有：" + count + "名");  
     ~~~
     使用传统编程方式，在搜索条件改变条件下，就必须重新编写代码；希望并行处理的时候也必须重写每个循环
     - 使用Stream API
     ~~~Java
     static void filterWithStreamAPI() {  
		 //集合对象有一个stream()方法，用于生成流  
		 long count = Student.getStudents().stream()  
			 //filter是一个Stream API函数，它可以接收一个Lambda表达式  
			 .filter(stu -> stu.getFrom().equals("北京"))  
			 //count是另一个Stream API函数，它接收前一个函数的结果并进行计数  
			 .count();  
		 
		 System.out.println("来自于北京有学生有：" + count + "名");  
	 }
     ~~~
     上述代码中，stream()方法返回一个“流”，`filter` 和 `count`都是对这个流所施加的“操作”，这种操作可以级联，最后一个才是负责真正启动执行这一连串处理工作的操作（称为“Terminal Operation”，本例中是count），中间的称为“Intermediate Opearation”，它们是被动的，不会引发操作的执行。
  3. 可以使用 `.parallelStream()` 来生成并行处理的流，使用 `.peak()` 来取出处理的每个元素，使用`Thread.currentThread().threadId()` 可以获取当前进行操作的线程编号
  4. Stream API的优点
     1. 声明式编程风格，代码简短易读
     2. 各种流处理方法进行动态组合，使用灵活方便
     3. 因为无需将所有数据调入内存，多操作可以一起运行，只遍历一次数据，对内存的占用减少；同时还支持并行运行
- 了解Stream的特性
  1. Stream的特性
     1. 普通的集合关注的是数据的存储方式；Stream关注的是施加于这些集合元素的处理操作
     2. Stream只“抽取”数据，它从不会修改底层的数据源。简言之：Stream Operation是只读操作！
     3. Stream API采用 “即抽取、即使用、即丢弃”的方式处理数据，因此能处理不受限制的数据集
     4. Stream只能使用一次，再次执行统一操作必须重新创建一个Stream
        ~~~Java
        private static void StreamMustBeRecreated() 
        {  
			List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5);  
			Stream<Integer> stream = numbers.stream();  
			System.out.println("numbers集合中有元素" + stream.count() + "个");  
			//必须重建一个流对象，否则，尝试重用流，会抛出IllegalStateException异常  
			// Exception in thread "main" java.lang.IllegalStateException: 
			// stream has already been operated upon or closed
			stream = numbers.stream();  
			System.out.println("平均值为："  
				+ stream.mapToInt(Integer::intValue)  
				.average().getAsDouble());  
		}
        ~~~
     5. 当需要反复执行特定流的不同操作系列时，可以构建一个Supplier对象，通过它获取新的流实例
        ~~~Java
        Supplier<IntStream> streamSupplier = () -> numbers.stream().mapToInt(Integer::intValue);
        streamSupplier.get().count()
        streamSupplier.get().average()        
        ~~~
  2. 组合Stream API完成复杂的处理工作
     - 可以选择定义多个流分别储存数据处理管线的不同操作，也可以采取如下的级联调用方式：
       ~~~Java
       // 求集合中奇数平方和
       int sum = numbers.stream()
	       .filter(n -> !(n & 1))
	       .map(n -> n * n)
	       .reduce(0, Integer::sum);
       ~~~
     - 流处理管线由 “中间操作” 和 “终结(终端、终止)操作” 所构成，终止后流对象被销毁
- 流的创建
  1. 为了支持上述进行的级联调用，所有进行的流中间操作都返回一个流对象，所以我们只需要构建一个初始流对象，基于它来构建一个流处理管线
  2. 流的分类：
     - 顺序执行流(Stream)和并行执行流(ParallelStream)
     - 对象流(`Stream<T>`)和原始数值流(`IntStream`等)
       使用数值流可以避免装箱带来的性能损失
  3. 创建流的几种方式
     1. 基于集合创建Stream
        - 所有集合对象都通过公有 `Collection` 接口定义了 `Stream()` 或 `ParallelStream()` 方法
        ~~~Java
        //创建一个集合对象  
		Set<String> names = new HashSet<>();  
		names.add("Tom");  
		names.add("Jacket");  
		//基于集合对象创建并行流（ parallel stream）  
		Stream<String> parallelStream = names.parallelStream(); 
		//基于数组创建流  
		int[] numbers = {2, 3, 5, 7, 11, 13};  
		var arrayStream = Arrays.stream(numbers);
        ~~~
     2. 使用 `Stream.of()` 创建流
        ~~~Java
        //使用可变参数创建流  
		var strStream = Stream.of("Java", "Kotlin", "C#");  
		//基于数组创建流 
		String[] names = {"Ken", "Jeff", "Chris", "Ellen"}; 
		Stream<String> nameStream = Stream.of(names);
        ~~~
     3. 使用 `Stream.<T>builder()` 泛型类方法
        - 可以直接使用类似级联方法添加元素，使用 `.build()` 方法终结(实际上是构建)Stream
        ~~~Java
        Stream<String> stream = Stream.<String>builder() 
	        .add("ken")
	        .add("jeff")
	        .build();
	    ~~~
     4. 构建一个空的流
        - 使用 `Stream.empty()` 方法
        ~~~Java
        Stream<String> stream = Stream.empty();
        IntStream numbers = IntStream.empty();
        ~~~
     5. 构建无限流
        - 使用 `.generate()` 和 `.iterate()` 方法构建的流可以拥有无穷个元素，被称为无穷流(infinite stream)
        ~~~Java
        // 基于工厂函数(直接构建)
        Supplier<Integer> intFactory = () -> (int)(Math.random() * 100);
        Stream<Integer> stream = Stream.generate(intFactory).limit(10);
        
        // 基于迭代函数(流元素依据前一个元素确定)
        // a[n]=a[n-1]+2
        UnaryOperator<Integer> intFactory = n -> n + 2;  
		Stream<Integer> stream = Stream.iterate(seed, intFactory).limit(10);
        ~~~
        - Attention：这种方式会产生数目无线的无限流，通常要使用 `limit()` 方法来限定要生成的元素个数
        - 我们可以使用 `.generate()` 方法结合 `Math.random()` 方法生成随机数值流；同时在Java8+之后，`Random` 类中添加了 `ints() doubles() longs()` 方法创建相应的数值流
          ~~~Java
          // 使用generate方法
          Stream.generate(Math::random)  
			  .limit(5)  
			  .map(doubleNum -> (int) (doubleNum * (to - from + 1)) + 1)  
			  .forEach(System.out::println);
		  // 使用Random类中方法
		  new Random()  
			  .ints(0, 100)  
			  .limit(5)  
			  .forEach(System.out::println);
          ~~~
     6. 构建一定范围内的数值流
        ~~~Java
        // 生成的流包容 [0,100) 区间的所有整数
        IntStream zeroToNinetyNine = IntStream.range(0, 100);
        //生成的流包容 [0,100]区间的所有整数  
		IntStream zeroToHundred = IntStream.rangeClosed(0, 100);
        ~~~
     7. 使用装箱流
        - 对于常用的一些流操作可能无法应用于数值流，这是我们可以使用 `boxed()` 或者 `mapToObj` 方法将数值流转换为对象流
        ~~~Java
        // boxed()装箱
        List<Integer> ints = IntStream.of(3, 1, 4, 1, 5, 9)  
		.boxed()  
		.toList();
		// mapToObj装箱
		List<Integer> ints2 = IntStream.of(3, 1, 4, 1, 5, 9)  
		.mapToObj(Integer::valueOf)  
		.tolist();
        ~~~
     8. 基于文件和文件夹创建流
        ~~~Java
        // 将每一行作为一个字符串流
        try (Stream<String> lines = Files.lines(Paths.get("data.txt")))  // 按行转化为流
        {  
			lines.forEach(System.out::println);  
		} 
		catch (IOException ex) 
		{  
			System.out.println(ex.getMessage());  
		}
		
		// 列出文件夹下的所有文件
		Path dir = Paths.get("");  
		System.out.printf(" %s contains：\n", dir.toAbsolutePath());  // 将dir转化为绝对路径输出
		//walk方法返回一个Stream  
		try (Stream<Path> fileTree = Files.walk(dir)) // 遍历路径下的每一个文件并输出文件名
		{  
			fileTree.forEach(System.out::println);  
		} 
		catch (IOException e) 
		{  
			e.printStackTrace();  
		}
        ~~~
- Stream API基础语法
 
|方法名|调用作用备注|操作类型|
|---|---|---|
|`.forEach(method)`|遍历流中的元素并施加 `method` 方法特定处理|终结操作|
|`.peek(method)`|检查、提取流中的元素，可以级联其他操作|中间操作|
|`.limit(long n)` 和 `.skip(long n)`|取出或忽略前n个元素|中间操作|
  - `.limit()` 和 `.skip()` 方法常用于对大数据集进行分页提取
- 流中数据的过滤与查找
  1. `.filter()`: 接受一个Predicate,从流中排除某些元素，保留流中符合筛选条件的元素
     ~~~Java
     Perdon.persons().stream()
	     // 过滤出所有女员工
	     .filter(Person::isFemale)
	     // 级联filter，过滤出男性收入大于5000的员工
	     .filter(Person::isMale)
	     .filter(p -> p.getIncome() > 5000)
	     // 应用一下复合表达式
	     .filter(p -> p.isMale() && p.getIncome() > 5000)
     ~~~
  2. `.distinct()`: 消除重复项
     - 还可以将List元素放到Set中利用 `toSet()` 收集器消除重复项
     ~~~Java
     // 直接使用distinct方法
     .distinct()
     // 使用toSet方法
     .collect(Collections.toSet())
     // IDEA教的直接哈希表
     new HashSet<>(numbers)
     ~~~
  3. `.sorted()`: 排序
     ~~~Java
     Stream<String> sortedWords = words.stream().sorted(Comparator.comparing(String::length));
     ~~~
  4. `.findAny()` 和 `.findFirst()`: 查找符合条件的单个元素(短路操作，找到一个结果立刻停止)
     - 对于有序集合 `.findFirst()` 的结果是确定的
  5. `.allMatch()` 和 `.noneMatch()`: 检查集合中元素是否都满足或不满足特定条件; `.anyMatch()`: 流中是否有至少一个元素匹配给定的条件
     ~~~Java
     var result = words.stream().allMatch(word -> word.length() >= 3);
     ~~~
  6. `.takeWhile()` 和 `.dropWhile()`: 切片操作(短路操作)
     ~~~Java
     // takeWhile(): 遇到第一个判定为false的就结束，返回流中所有true的值
     .takeWhile(num -> num < 6 && (num&1) == 1)
     // dropWhile(): 遇到第一个判定为true的就结束，返回流中所有剩余的值，判定为false的都删掉
     .dropWhile(num -> num < 3)
     ~~~
- 流数据转换
  - 使用Stream API往往需要对原始数据进行特定的加工处理之后在转换为另一种类型的数据；这种转换工作如果位于数据管线中间就称为Map，Stream API提供了 `map` 和 `flatmap` 两方法完成任务
  - Map的实际应用场景：在实际开发中，经常需要将数据库中的数据记录，抽取部分字段值，传给客户端，这种封装了发给客户端信息的对象，通常称为“DTO（数据传输对象）”。而使用map方法可以很轻松完成DTO转换工作
    ~~~Java
    // 定义转换函数
    Function<Client, ClientDTO> toDTO = client -> new ClientDTO(client.getId(), client.getName());
    // 完成转换工作
    List<ClientDTO> dtos = clients.stream()
	    .map(toDTO)
	    .toList()
    ~~~
  - 在使用map转换对象类型时，使用的就是原始的数据对象，以减少对象复制对内存的占用
  - 如果生成的结果是元素流的流(stream of stream)，则需要使用 `.flatMap()` 将形成嵌套关系的两个流合成为一个
    ~~~Java
    var words = List.of("Hello", "World");  
	words.stream()  
		.map(word -> word.split(""))  
		//将每个String[]转换为Stream<String>，再展平  
		//得到Stream<String>  
		.flatMap(Arrays::stream)  
		.distinct() //消除重复元素  
		.forEach(System.out::println);
    ~~~
  - `reduce()` 归约方法能够将流中所有元素反复组合起来，得到一个单一的值。
    1. `reduce` 方法的第一个参数是被称为 `seed` 的初始值，第二个参数是实现 `BinaryOperator<T>` 的lambda表达式；方法以 `seed` 作为接收的第一个元素，顺次接收流中的每一个元素并生成一个中间结果，将其与流中的下一个元素相加直到遇到最后一个元素
    ~~~Java
    // 使用传统循环方式求和
    int sum = 0;
    for (var num: nums)
    {
	    sum += num;
    }
    
    // 使用归约方法
    var sum = nums.stream.reduce(0, (a, b) -> a + b);
    // 简化版
    var sum = nums.stream.reduce(0, Integer::sum);
    ~~~
- 收集器
  - collect顺次收集流中的所有元素，进行某种处理之后得到一个结果，它是一个终结操作。完成收集操作的对象称为收集器
  - 常用的四种收集器
     1. 如 `Collectors.toList()`: 将流转换为某种集合
     2. 如 `Collectors.counting()`: 将流元素归约和汇总为一个值
     3. 如 `Collectors.groupingBy()`: 将流元素分组
     4. 如 `Collectors.partitioningBy()`: 将元素分区
  - 集合类型收集器 `.toList()` 和 `toSet()`
    ~~~Java
    Set<integer> distinctNums = nums.stream().collect(Collectors.toSet());
    // 也可以用HashMap
    Set<integer> distinctNums = new HashSet<>(nums);
    ~~~
  - 字符串收集器
    ~~~Java
    var numString = numbers.stream()
		    .map(String::valueOf)
		    .collect(Collections.joining(","));
    ~~~
  - `mapping` 收集器: 先转换、再收集
    1. `mapping` 收集器接收两个参数，源码如下
       ~~~java
       public static <T, U, A, R> Collector<T, ?, R> mapping(
	       Function<? super T, extends U> mapper,
	       Collector<? super U, A, R> downstream)
       ~~~
    2. 示例：
       ~~~Java
       //用于提取Student对象的name字段值  
	   Function<Student, String> getStudentName = Student::getName;  
	   //将每个Student对象先转换为字符串，再收集到List中  
	   List<String> nameList = students  
		   .stream()  
		   .collect(Collectors.mapping(getStudentName, Collectors.toList()));
		   // 也可以写成，相当于先用map进行映射转化，再收集到List中
		   // .map(getStudentName)
		   // .collect(Collectors.toList());
       ~~~
  - 统计相关的收集器
    - `minBy` 和 `maxBy` 收集器：获取流中方法最小和最大的值，接收一个函数式接口
    - `summingInt()`、`averagingInt()` 和 `summarizingInt()` 收集器：
    ~~~Java
    static void useStatisticsCollectors() {  
		var numbers = List.of(1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1);  
		long count = numbers.stream().collect(Collectors.counting());  
		System.out.println(count);  // 11
  
		var max = numbers.stream().collect(Collectors.maxBy(Integer::compareTo));  
		System.out.println(max);  // Optional[6]
  
		int sum = numbers.stream().collect(Collectors.summingInt(Integer::intValue));  
		System.out.println(sum);  // 36
  
		double avg = numbers.stream().collect(Collectors.averagingInt(Integer::intValue));  
		System.out.println(avg);  // 3.272727272727273
  
		var statistics = numbers.stream().collect(Collectors.summarizingInt(Integer::intValue));  
		System.out.println(statistics);  // IntSummaryStatistics{count=11, sum=36, min=1, average=3.272727, max=6}
	}
    ~~~
  - 分组相关
    1. 简单分组格式
       ~~~Java
       var groupResult = numbers.stream().collect(Collectors.groupingBy(num -> {
	       if ((num&1) == 0) return "even";
	       return "odd";
       }));
       ~~~
    2. 分组后过滤或统计
       ~~~Java
       var groupResult = IntStream.rangeClosed(1, 100)
	       .boxed()
	       .collect(Collectors.groupingBy(num -> {
		       if ((num&1) == 0) return "even";
		       return "odd";
	       }, 
	       Collectors.filtering(  // 若为统计则为 Collectors.counting()
		       num -> num.intValue() >= 50,
		       Collectors.toList())));
       ~~~
  - 分区相关
    - 分区其实是分组的一种特殊情况，由一个返回布尔值的函数作为分类函数，因此得到的分组Map键类型是 `Boolean`,因此最多可以分为true和false两组
    - 简单分区（注意：分区针对引用类型，因此要先使用 `boxed()` 方法装箱
      ~~~Java
      //依据考试成绩，分为“及格”与“不及格”两组  
	  var doYouPassed = IntStream.rangeClosed(1, 100)  
		  .boxed()  
		  .collect(Collectors.partitioningBy(score -> score >= 60));  
	  System.out.println(doYouPassed);
      ~~~
    - 先分区再分组
      ~~~Java
      var doYouPassed2 = IntStream.rangeClosed(1, 100)
	      .boxed()  
		  .collect(Collectors.partitioningBy(  
			  score -> score >= 60,  
			  Collectors.groupingBy(score -> {  
				  int temp = score / 10;  
				  return switch (temp) {  
					  case 0, 1, 2, 3, 4, 5 -> "不及格";  
					  case 6 -> "及格";  
					  case 7 -> "中";  
					  case 8 -> "良";  
					  case 9, 10 -> "优";  
					  default -> "无效成绩";  
				  };  
			})));
      ~~~
  - 区分 `Reduce()` 和 `Collect()`
    1. `numbers.stream().reduce(...)`: Reduce的结果类型由Stream的类型决定
    2. `numbers.stream().collect(...)`: Collect则可以根据调用方法返回任意类型结果
# Class9
## *Lesson14：Java程序设计之并发导论*
---

## *Lesson15：Java程序设计之GUI编程导论*
---

# Class10
## *Lesson16：SQLite基础*
---

## *Lesson17：JDBC基础*
---
