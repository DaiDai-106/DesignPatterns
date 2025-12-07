# Composite Pattern (组合模式)

# 1. 简介
组合模式为单个对象和容器对象提供了相同的接口。 

# 2. 数组形式
首先， 这里举的例子是如何在类的属性上使用组合模式。

```cpp
class Creature
{
    int strenght, agility, intelligence;
public:
    int getStrenght() { return strenght; }
    int getAgility() { return agility; }
    int getIntelligence() { return intelligence; }

    int set_strenght(int strenght) { this->strenght = strenght; }
    int set_agility(int agility) { this->agility = agility; }
    int set_intelligence(int intelligence) { this->intelligence = intelligence; }
};
```
接下来，如果我想计算该类的相关统计数据时，比如总和，均值，最高值时，因为上面的分开实现，这里还要进行单独的接口设计如下：
```cpp
class Creature
{
    int sum();
    double average();
    int max();
}
```
这样的设计的问题是：总和计算容易遗漏属性，平均值如果多一个属性，平均值的计算公式需要修改。，计算max需要嵌套的使用。那么如何修改呢，一个简单的尝试是使用枚举，如下代码所示：
```cpp
enum Abilites
{
    str, agl, intl, count
};

class Creature
{ 
    std::array<int, count> abilites;
public:
    int getAbilites(Abilites abilites) { return abilites; }
    int setAbilites(Abilites abilites, int value) {this->abilites[abilites] = value; }
};

// 此时在计算平均数就变得相当的容易了
int sum() const
{
    return std::accumulate(abilites.begin(), abilites.end(), 0);
}

double average() const
{
    return sum() / count;
}

int max() const
{
    return *std::max_element(abilites.begin(), abilites.end());
}
```
通过上述的实现，可以看到通过enum的方式，不管是单个数值还是多个不同的数值，都统一进行了处理。

## 3. 组合模式
通俗的来说：组合模式有三个角色：
1. Component（抽象组件） 定义所有对象的公共接口（如操作方法 operation()）。
可以包含子节点的增删方法（可选）。
2. Leaf（叶子节点） 叶子对象，没有子节点。实现 Component 接口的具体方法。
3. Composite（组合节点） 有子节点的对象。存储子节点，并实现 Component 接口的方法，一般会把操作委托给子节点。

所以从上述的描述来看，类似树形结构的数据，比较适合此设计模式。、
```cpp
#include <iostream>
#include <vector>
#include <memory>

struct Component {
    virtual ~Component() = default;
    virtual void operation() = 0;
};

struct Leaf : public Component {
    void operation() override { std::cout << "Leaf operation\n"; }
};

struct Composite : public Component {
    std::vector<std::shared_ptr<Component>> children;

    void add(const std::shared_ptr<Component>& c) { children.push_back(c); }
    void remove(const std::shared_ptr<Component>& c) {
        children.erase(std::remove(children.begin(), children.end(), c), children.end());
    }

    void operation() override {
        std::cout << "Composite operation\n";
        for (auto& child : children) child->operation();
    }
};

int main() {
    auto leaf1 = std::make_shared<Leaf>();
    auto leaf2 = std::make_shared<Leaf>();
    auto comp = std::make_shared<Composite>();

    comp->add(leaf1);
    comp->add(leaf2);

    comp->operation();  // 对组合和叶子操作统一调用
}
```