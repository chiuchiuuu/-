# C++: 多态与虚函数

## 多态和虚函数的基本概念

### 虚函数

在类的定义中，前面有 `virtual` 关键字的成员函数就是虚函数。 `virtual` 关键字只用在类定义里的函数声明中， 写函数体时不用。构造函数与静态成员函数不能是多态。
### 多态的表现形式
多态的实现主要通过两种形式：指针多态和引用多态。
#### 指针多态

派生类的指针可以赋给基类指针。

通过基类指针调用基类和派生类中的同名虚函数时:：

- 若该指针指向一个基类的对象，那么被调用是基类的虚函数
- 若该指针指向一个派生类的对象，那么被调用的是派生类的虚函数。

这种机制就叫做“多态”。 
```cpp
class CBase{
	public:
	virtual void SomeFunction() {}
};
class CDerived:public CBase{
	public:
	virtual void SomeFunction() {}
};
int main() {
	CDerived ODerived;
	CBase *p = &ODerived; //基类的指针指向了派生类的对象
	p->SomeFunction(); //调用哪个基函数取决于p指向哪种类型的对象
	return 0;
}
```

#### 引用多态

派生类的对象可以赋给基类引用 

通过基类引用调用基类和派生类中的同名虚函数时：

- 若该引用引用的是一个基类的对象，那么被调用是基类的虚函数
- 若该引用引用的是一个派生类的对象，那么 被调用的是派生类的虚函数。          

这种机制也叫做“多态”。 
```cpp
class CBase {
	public:
	virtual void SomeFunction() {}
};

class CDeruved: public CBase{
	public:
	virtual void SomeFunction() {}
};

int main() {
	CDerived ODerived;
	CBase &r = ODerived;//基类的引用 引用派生类的对象
	r.SomeVirtualFunction();//调用哪个虚函数取决于r引用对象的类型
	return 0;
}

```
### 多态的作用

在面向对象的程序设计中使用多态，能够增强 程序的**可扩充**性，即程序需要修改或增加功能的时候，需要改动和增加的代码较少。

## 多态实例： 几何形体处理程序

几何形体处理程序: 输入若干个几何形体的参数， 要求按面积排序输出。输出时要指明形状。 

Input: 

第一行是几何形体数目n（不超过100).下面有n行，每行以一个字母c开头. 

若 c 是 ‘R’，则代表一个矩形，本行后面跟着两个整数，分别是矩形的宽和高； 

若 c 是 ‘C’，则代表一个圆，本行后面跟着一个整数代表其半径 

若 c 是 ‘T’，则代表一个三角形，本行后面跟着三个整数，代表三条边的长度 

Output: 

按面积从小到大依次输出每个几何形体的种类及面积。每行一个几何形体，输 出格式为： 

形体名称：面积 

```c++
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Shape
{
public:
	virtual double Area() = 0; // 纯虚函数！！
	virtual void PrintInfo() = 0;
};

class Rectangle : public Shape
{
public:
	int w, h;
	virtual double Area() { return w*h; }
	virtual void PrintInfo()
	{
		cout << "Rectangle: " << Area() << endl;
	}
};

class Circle :public Shape
{
public:
	int r;
	virtual double Area() { return 3.14*r*r; }
	virtual void PrintInfo()
	{
		cout << "Circle: " << Area() << endl;
	}
};

class Triangle :public Shape
{
public:
	int a, b, c;
	virtual double Area()
	{
		double p = (a + b + c) / 2.0;
		return sqrt(p*(p - a)*(p - b)*(p - c));
	}
	virtual void PrintInfo()
	{
		cout << "Triangle: " << Area() << endl;
	}
};

int MyCompare(const void *s1, const void *s2)
{
	Shape **p1 = (Shape**)s1;
	Shape **p2 = (Shape**)s2;

	double a1 = (*p1)->Area();
	double a2 = (*p2)->Area();

	if (a1 < a2)
	{
		return -1;
	}
	else if (a1 > a2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	Shape *pShape[100];
	int n = 0;
	cin >> n;
	Rectangle *pr;
	Circle *pc;
	Triangle *pt;
	for (int i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		switch (c)
		{
		case 'R':
			pr = new Rectangle();
			cin >> pr->w >> pr->h;
			pShape[i] = pr;
			break;
		case 'C':
			pc = new Circle();
			cin >> pc->r;
			pShape[i] = pc;
			break;
		case 'T':
			pt = new Triangle();
			cin >> pt->a >> pt->b >> pt->c;
			pShape[i] = pt;
			break;
		}
	}
	qsort(pShape, n, sizeof(Shape*), MyCompare);
	for (int i = 0; i < n; i++)
	{
		pShape[i]->PrintInfo();
	}
	return 0;
}
```
**小Tipps**
用基类指针数组存放指向各种派生类对象的指针，然后遍历该数组，就能对各个派生类对象做各种操作，是很常用的做法。

### 构造函数和析构函数中调用虚函数

在构造函数和析构函数中调用虚函数，不是多态。编译时即可确定，调用的函数是自己的类或基类中定义的函数，不会等到运行时才决定调用自己的还是派生类的函数。 

派生类中和基类中虚函数同名同参数表的函数，不加`virtual`也自动成为虚函数。



## 多态的实现原理
“多态”的关键在于通过基类指针或引用调用一个虚函数时，编译时不确定到底调用的是基类还是派生类的函数，运行时才确定，即为“**动态联编**”。我们来看下面的程序：
```c++
class Base {
    public:
        int i;
        virtual void Print() {cout<<"Base print"<<endl;}
};
class CDeriverd: public Base {
    public:
        int n;
        void Print() {cout<<"Derived Print"<<endl;}
};
int main() {
    CDerived d;
    cout<<sizeof(Base)<<","<<sizeof(CDerived)<<endl;
    return 0;
}
```
该小程序的输出结果为：
```cpp
8,12
```
按照我们之前对`class`的学习，一个`class`的大小应该为其内部成员变量所占据空间的大小。那么这多出来的4个字节来自哪里？其实这是由于虚函数的虚函数表。
### 虚函数表

每一个有虚函数的类（或有虚函数的类的派生类）都有一个虚函数表，该类的任何对象中都放着虚函数表的指针。虚函数表中列出了该类的虚函数地址。多出来的4个字节就是用来放虚函数表的地址的。 

多态的函数调用语句被编译成一系列根据基类指针所指向的（或基类引用所引用的）对象中存放的虚函数表的地址，在虚函数表中查找虚函数地址， 并调用虚函数的指令。 

### 缺点

时间开销：查虚函数表

空间开销：每个对象多四个字节存放虚函数表的地址



## 虚析构函数

虚析构函数的提出源于实际问题，本质上是多态。考虑下面场景，通过基类的指针删除派生类对象时，只调用了基类的析构函数，也就意味着派生类的内存没有被释放，在大型程序中可能会造成内存碎片和内存浪费。

```c++
class son 
{
public:
	~son() { cout << "bye from son" << endl; };
};
class grandson : public son
{
public:
	~grandson() { cout << "bye from grandson" << endl; }
};

int main()
{
	son *pson;
	pson = new grandson;
	delete pson;
	return 0;
}

// 输出：bye from son
// 没有执行 grandson::~grandson()!
```

解决办法：

把基类的析构函数声明为`virtual`

此时通过基类指针删除派生类对象时

- 先调用派生类的析构函数
- 在调用基类的析构函数

一般来说，如果类定义了虚函数, 则最好将析构函数也定义成虚函数

注：构造函数不可声明为虚函数！



## 纯虚函数和抽象类

纯虚函数：没有函数体的虚函数

```c++
virtual void Print() = 0;
```

抽象类：包含纯虚函数的类

- 只能作为基类来派生新类使用
- 不能创建抽象类的对象
- 可以有抽象类的指针和引用->由抽象类派生出来的类的对象 

抽象类中：

- 在成员函数内可以调用纯虚函数
- 在构造函数/析构函数内部不能调用纯虚函数 

如果一个类从抽象类派生而来,只有它实现了基类中的所有纯虚函数，才能成为非抽象类
## 混合类型
在一个程序中，派生类与基类可能存在多种情况的同名成员函数，参见下面程序：
```cpp
#include <iostream>
using namespace std;
class A {
    private:
        int nVal;
    public:
        void Fun()
        { cout << "A::Fun" << endl; }
        virtual void Do()
        { cout << "A::Do" << endl; }
};
class B:public A {
    public:
        virtual void Do()
        { cout << "B::Do" << endl; }
};
class C:public B {
    public:
        void Do( )
        { cout << "C::Do" << endl; }
        void Fun()
        { cout << "C::Fun" << endl; }
};
void Call(  A *p
// 在此处补充你的代码
         )  {
    p->Fun();  p->Do();
}
int main()  {
    Call( new A() );
    Call( new C() );
    return 0;
}
```
该程序的输出结果为：
```cpp
A::Fun
A::Do
A::Fun
C::Do
```
在调用`Call(new C())`时，由于基类中的`Fun()`函数不是虚函数，不构成多态，而`Call()`函数中，`p`的类型为`A * {C}`,即指向派生类`C`的基类`A`指针，故而调用基类A下的`Fun()`函数。

## References
- [1] https://github.com/chiuchiuuu/programming-and-algorithm
- [2] https://www.coursera.org/learn/cpp-chengxu-sheji/lecture