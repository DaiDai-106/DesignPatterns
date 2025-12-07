# Prototype Pattern (原型模式)

## 1. 简介
该设计模式主要用于在预先构建好的对象或其拷贝或者基于此进行的一些自定义的设计。原型模式是一种 创建型设计模式，通过复制已有对象（原型）来创建新对象，而不是通过 new 关键字重新创建。

这里的简单想法就是：一个原型指一个模型对象，我们对其进行拷贝，自定义拷贝，然后使用他们。原型模式的挑战实际上是拷贝部分，其他都比较简单。

## 2. 对象构建
首先，这里抛出一个问题，如果已经有一个完整配置的对象，为什么不简单的拷贝该对象而非重新创建一个新的对象呢？
这里假设游戏里有一个对象，该对象有名称和等级
```cpp
shared_ptr<Character> w1 = make_shared<Warrior>("Aragorn", 10);
```
如果这个时候，我不使用拷贝的方式，那么就会有如下的代码
```cpp
shared_ptr<Character> w2 = make_shared<Warrior>("Aragorn", 10);
```
那么这在部分情况下可能会有一些问题：
1. 重复代码
2. 需要重复提供所有初始化参数。
3. 如果对象构造复杂，这会变得很麻烦。
4. 不够灵活
5. 运行时你可能只有 w1 对象，而不知道具体类型和参数（比如多态对象时）。你无法直接生成 w1 的副本，因为客户端不知道它是 Warrior 还是 Mage。

因此，原型模式的初衷就是为了解决这些问题。我们可以通过下面的代码快速实现
```cpp
shared_ptr<Character> w2 = w1->clone();
```
当然这个时候你可能依然会有疑惑，为什么不能使用拷贝构造的方式呢，像下面的代码
```cpp
shared_ptr<Character> w2 = make_shared<Warrior>(*dynamic_cast<Warrior*>(w1.get()));
```
显而易见有这么几个问题：
1. 破坏封装
2. 必须知道具体类型 Warrior。
3. 类型不安全
4. 如果对象是多态基类指针，你必须进行类型转换。
5. 代码臃肿，每次克隆对象都需要动态判断类型，特别是对象很多或类型复杂时。
## 3. 普通拷贝
还是刚才的例子，如果下面这个类中成员都是通过值的方式来存储的对象，使用 w1 = w2这样的赋值运算符是没问题的。
```cpp
class Warrior : public Character {
private:
    string name;
    int level;
}
```
但是，如果成员是通过引用或者指针来存储的，那么可能出现每一个原型拷贝共享同一个地址，这肯定不是我们想要的结果。
## 4. 拷贝构造函数
下面的例子是一个深拷贝的拷贝构造函数的例子
```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Warrior {
private:
    string name;
    int level;
    string* weapon; // 动态分配资源
public:
    // 构造函数
    Warrior(const string& n, int l, const string& w) 
        : name(n), level(l), weapon(new string(w)) {}

    // 拷贝构造函数（深拷贝）
    Warrior(const Warrior& other)
        : name(other.name), level(other.level), weapon(new string(*other.weapon)) {}

    // 析构函数
    ~Warrior() { delete weapon; }

    void show() const {
        cout << "Warrior: " << name << ", level: " << level
             << ", weapon: " << *weapon << endl;
    }

    void setWeapon(const string& w) { *weapon = w; }
};
```
当然上面是拷贝构造函数，你也可以实现对应的拷贝赋值函数，从上面的实现看其实还不错，不过也有些不足，比如如果类的成员复杂，似乎我们对每个成员都要实现一下相对应的拷贝构造和拷贝赋值函数。
## 5. “虚”构造函数
这里延续上面拷贝构造函数的局限，这里举个例子，假设 ExtendedAdress 继承自 Adress，即如果我们要拷贝一个存在多态性质的变量？
```cpp
ExtendedAddress* ea = new ExtendedAddress("123 Main St", "Suite 456");
Address* a = ea;  // 请问这里拷贝会发生什么呢？
```
显然上述的做法会存在问题，因为我们并不知道变量a的最终派生类型是什么。为了解决派生类带来的问题，以及拷贝构造函数不能是虚函数的问题，这里提出了“虚”构造函数。也就是引入一个虚函数 clone()。 当然在下面的实现中，clone的重载调用了其默认拷贝构造函数。通过下面的方式，我们就可以解决派生类带来的问题。并且可以得到一个深拷贝的对象了。
```cpp
class Address
{
 public:
  virtual ~Address()             = default;
  virtual void show() const      = 0;
  virtual Address *clone() const = 0;  // 原型接口
};

class ExtendedAddress : public Address
{
 private:
  std::string suite;

 public:
  ExtendedAddress( const std::string &s ) : suite( s ) {}
  void show() const override { std::cout << suite << std::endl; }
  Address *clone() const override { return new ExtendedAddress( *this ); }
};
```
当然，如果我不想显式写每个成员的深拷贝逻辑同时当前对象比较复杂，比如包含（比如嵌套指针、容器、图结构）时，可以使用序列化的方式来实现。当然对于一些非c++的语言，或者没有直接深拷贝方式的语言，这个方法是更友好的一种拷贝方式。
```cpp
ExtendedAddress* clone() const override {
    std::string data = serialize(*this);      // 序列化
    return deserialize<ExtendedAddress>(data); // 反序列化得到副本
}
```
## 6. 总结
如果不想每次对对象进行完全的初始化，那么，原型模式提供了一种很好的方式。同时为了兼容工厂模式，也可以通过原型对象对部分未初始化的成员进行初始化。