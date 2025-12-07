# Factory Pattern (工厂模式)

## 1. 简介
工厂设计模式（Factory Pattern）主要解决的是“对象创建与使用解耦”的问题。用简单的话描述， 就是：把“怎么创建对象”的决定权，从使用者手里拿走。
即允许用户创建特定类型而非任意类型的对象。这里举一个例子：
```cpp
void foo() {
    Car* car = new BMW();
    car->run();
}
```
上面的代码并不友好，foo 必须知道具体类 BMW， 如果以后要换成 Audi，Tesla，则需要在这里改代码,重新编译。这样的方法显然也违法了开闭原则（对修改关闭）

## 2. 简单工厂
还是上面的例子，如果我想使用工厂方法应该如何设计呢？
```cpp
class Car {
public:
    static Car* createBMW() {
        return new BMW();
    }

    virtual void run() = 0;
};
```
这样在调用的时候，用下面的方式即可，这样的好处是，使用者不知道 BMW 存不存在，也不关心构造细节，只依赖 Car 接口。
```cpp
void foo() {
    Car* car = Car::createBMW();
    car->run();
}
```
上面这样已经算是简单工厂了，但是依然还没有到工厂设计模式的层面，原因是依然还没有满足OCP原则，因为如果我要新增一个car，我都必须“修改 Car 类本身”。就像下面这样，所以需要继续进行优化
```cpp
class Car {
public:
    static Car* createBMW() {
        return new BMW();
    }

    static Car* createAudi() {
        return new Audi();   // 👈 修改 Car
    }
};
```
## 3. 抽象工厂
在我的代码中实现了简单工厂和抽象工厂，那么什么是抽象工厂呢？下面这里罗列出了一些对比：
### 核心概念对比：简单工厂 vs 抽象工厂

| 特性 | 简单工厂模式 | 抽象工厂模式 |
|------|--------------|--------------|
| 目的 | 封装单个产品的创建逻辑 | 封装一组相关或依赖对象的创建逻辑（产品族） |
| 工厂层级 | 单一工厂类 | 抽象工厂接口 + 多个具体工厂 |
| 客户端依赖 | 可以依赖具体工厂，也可以依赖抽象产品 | 只依赖抽象工厂接口和抽象产品 |
| 产品数量 | 通常单个产品或产品的不同具体实现 | 多个相关产品（产品族） |
| 扩展方式 | 修改工厂类 → 不满足 OCP | 增加新的具体工厂或产品族 → 满足 OCP |
| UML 结构 | 只有 Factory + Product | AbstractFactory + ConcreteFactory + AbstractProduct + ConcreteProduct |

基于上面的描述，代码仓库内对抽象工厂也进行了实现，这里的例子是这样的，假设我在咖啡馆工作，咖啡管可以供应茶和咖啡。
所以，针对咖啡和茶，这里就可以有两个具体的工厂，同时继承一个抽象的工厂：
```cpp

/// 定义抽象工厂类
class DrinkFactory
{
 public:
  virtual std::unique_ptr<Drink> make_drink() = 0;
};

class TeaFactory : public DrinkFactory
{
 public:
  std::unique_ptr<Drink> make_drink() override { return std::make_unique<Tea>(); }
};

class CoffeeFactory : public DrinkFactory
{
 public:
  std::unique_ptr<Drink> make_drink() override { return std::make_unique<Coffee>(); }
};
```
当有了继承抽象工厂后的两个具体工厂时，再封装一个具体的工厂类，就可以实现生产想要的饮品了，下面的代码展示了当调用create_drink时，会根据传入的类型返回不同的饮品。这样当有新的饮品比如说果汁时，只需要添加新的具体工厂即可，不需要修改其他具体类的实现了。做到了可拓展，开闭原则。
```cpp
class Factory
{
  std::map<std::string, std::unique_ptr<DrinkFactory>> factories;

 public:
  Factory()
  {
    factories[ "tea" ]    = std::make_unique<TeaFactory>();
    factories[ "coffee" ] = std::make_unique<CoffeeFactory>();
  }

  std::unique_ptr<Drink> create_drink( const std::string &type );
};
```
### 函数式工厂
当然，具体工厂的实现，比如类似下面的代码，其实未必一定要写成一个具体的类，也可以通过函数申明的方式实现，这样代码更简单, 这样的代替方式称作函数式工厂。
```cpp
public:
  std::unique_ptr<Drink> make_drink() override { return std::make_unique<Tea>(); }

---->可以简化为

factories[ "tea" ] = []{
    auto tea = std::make_unique<Tea>();
    return tea;
}
```

## 4.总结
与上一章的构造器方式相比，工厂模式可以一次创建一个完整的对象，而使用构造器，需要分布提供对象的部分信息才能逐步完成一个对象的创建。这里也举个生动形象的例子：

想象你去餐厅点汉堡：你说：我要一个 CheeseBurger
厨师直接做一个完整的 CheeseBurger 给你 → 一次完成， 你不需要关心里面的面包、芝士、蔬菜如何组合
```cpp
auto burger = BurgerFactory::createCheeseBurger();
```
但是，同样点汉堡，但是你想自己配置：先选择面包 → 再选择芝士 → 再选择蔬菜 → 最后组合成汉堡每一步都是单独操作，最后 build() 才生成完整对象
```cpp
BurgerBuilder builder;
builder.setBread("Wheat");
builder.setCheese("Cheddar");
builder.setVegetables({"Lettuce", "Tomato"});
auto burger = builder.build();
```
从上面的对比中，我大概能得到一个结论，那就是固定对象结构时，使用工厂模式会更方便，但是当对象复杂、多属性可选、需要定制时，使用建造者模式会更合适。
