# Builder Pattern (建造者模式)

## 1. 简介
该模式主要关注复杂对象的创建过程。
这里的复杂对象指的难以通过单行构造函数来创建的对象。

## 2. 流式构造器
通过“链式调用（method chaining）”的方式一步一步配置对象，让代码读起来像一段“自然语言”。 下面的代码可以直观理解这样的构造方式

```cpp
auto robot = RobotBuilder{}
    .setName("UR5e")
    .setPayload(5.0)
    .setReach(850)
    .enableVision()
    .build();
```
通过将构造接口返回值修改为Builder本身的引用或者指针，就可以形成链式调用。当然你肯定有个疑问，为什么要这样，下面有个列子：
```cpp
Robot r("UR5e", 5.0, 850, true, false, true /* ... */);
```
```cpp
RobotBuilder b;
b.setName("UR5e");
b.setPayload(5.0);
// ...
Robot r = b.build();
```
从上面的两个例子中，一个是可读性差，还要保证顺序，也很容易传错参数。另一个虽然可控，但是又有些代码冗余。

## 3. 组合构造器 (Combined Builder) -->
<!-- 当一个对象非常复杂，包含多个维度的信息（例如：个人信息、地址信息、工作信息）时，如果全塞在一个 Builder 里会非常臃肿。此时可以使用组合建造者模式，利用多个专用的 Builder 协同工作。

1. 基类：定义一个基类 Builder，它持有对象的引用，并提供“切换跑道”的接口（如 `lives()` 返回地址建造者，`works()` 返回工作建造者）。
2. 子类：不同的子 Builder（如 `AddressBuilder`, `JobBuilder`）继承自基类，分别负责构建不同的属性。
3. 继承与复用：因为子类继承了基类，所以在任何一个子 Builder 状态下，都可以直接调用基类的切换接口，跳转到另一个 Builder。

<!-- ```cpp -->
// 1. 前向声明：解决循环依赖
class PersonAddressBuilder;
class PersonJobBuilder;

// 2. 基类：持有对象引用的“路由器”
class PersonBuilderBase {
protected:
    Person& person;
public:
    PersonBuilderBase(Person& p) : person(p) {}

    // 关键点：在这里定义切换接口
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

    // 技巧：利用类型转换运算符代替显式的 .build()
    operator Person() { return std::move(person); }
};

// 3. 子类：继承基类，拥有切换能力
class PersonAddressBuilder : public PersonBuilderBase {
public:
    explicit PersonAddressBuilder(Person& p) : PersonBuilderBase(p) {}
    
    PersonAddressBuilder& at(std::string street) {
        person.address = street;
        return *this; // 返回自己，支持当前维度的链式调用
    }
    // 注意：因为继承了 PersonBuilderBase，这里也能直接调用 .works()
};

// 4. 使用：像自然语言一样流畅
Person p = Person::Create()
    .lives().at("123 London Road").in("London") // 填写地址
    .works().at("Tech Corp").as_a("Developer"); // 填写工作，无缝切换
```
