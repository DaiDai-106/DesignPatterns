# Chain of Responsibility Pattern (责任链模式)
从本章节开始，进入到行为设计模式的介绍模块了，行为设计模块主要是针对一些具体特定的问题的合适的设计方案。

## 1.介绍
什么情况下应该考虑这样的设计模式呢，这里有一些判断标准
1. 有一串规则，校验，处理步骤如下面的代码所示：
```cpp
if (!checkA(x)) return false;
if (!checkB(x)) return false;
if (!checkC(x)) return false;
```
2. 规则会不会增加，删除或者重新排序时
3. 规则处理有一些先后顺序的约束时
4. 用户并不清楚该如何调用具体的规则时

根据上面的描述，其实有一个具体的工程明确其实可以使用这种设计模式，那就是针对规则， 约束的校验系统，这其实在真是的工程中是基本必要的。针对规划约束，输入参数的合法性，安全检查和前置条件验证等。

## 2. 指针链
这里以大部分的书籍中都会使用的例子，假设有一个游戏角色 Creature: 它会受到一次攻击，然后攻击会被如下方式处理，护盾，护甲。同时还要维护该游戏角色的生命值。
这里的伤害会按顺序春地，同时每个防御只能处理一部分，剩余的伤害会向下传递。
1. 首先定义伤害类
```cpp
struct Attack
{
    int damage;
}
```
2. 抽象处理者
```cpp
struct CreatureModifier {
  CreatureModifier* next = nullptr;

  virtual void handle(Attack& attack) {
    if (next) next->handle(attack);
  }
};
```
3. 对没一个处理者进行具体设计
```cpp
struct ShieldModifier : CreatureModifier {
  void handle(Attack& attack) override {
    int absorbed = std::min(5, attack.damage);
    attack.damage -= absorbed;
    std::cout << "Shield absorbed " << absorbed << "\n";
    CreatureModifier::handle(attack);
  }
};

struct ArmorModifier : CreatureModifier {
  void handle(Attack& attack) override {
    attack.damage /= 2;
    std::cout << "Armor reduced damage to " << attack.damage << "\n";
    CreatureModifier::handle(attack);
  }
};
// 做后是生命承受
struct HealthModifier : CreatureModifier {
  int& hp;

  HealthModifier(int& hp_) : hp(hp_) {}

  void handle(Attack& attack) override {
    hp -= attack.damage;
    std::cout << "Health took " << attack.damage
              << ", HP left: " << hp << "\n";
  }
};
```
4. 接下来就是组装指针链了
```cpp
int main() {
  int hp = 100;
  Attack attack{ 20 };

  ShieldModifier shield;
  ArmorModifier armor;
  HealthModifier health(hp);

  // 关键：手动串指针
  shield.next = &armor;
  armor.next  = &health;

  shield.handle(attack);
}
```
通过上面的方式，便是一个简单的责任链的实现。

## 3.思考
在实现这个链的代码里，很明显能看出组合设计模式的影子，这让我思考了这两个的区别。组合模式更像是一颗树，用户会对整个树做一样的事情，而责任链更像是一条流水线，让请求沿着一条路往前走。
之所以我觉得一样，是因为他们的设计思想都是对象的递归组合并多态转发。两者都满足递归 + 同一接口。

单看上面责任链的例子，好像也不必if/else好，但是想一个情况，如果我不同的怪兽不同的链条呢，不同的关卡不同的链条呢，如果我想运行时动态组装链条呢。就像下面的代码解释的那样。
```cpp
std::vector<CreatureModifier*> chain;

if (hasShield) chain.push_back(&shield);
if (hasArmor)  chain.push_back(&armor);
chain.push_back(&health);

// Boss
chain = { &magic, &shield, &armor, &health };

// Slime
chain = { &health };
```
上面这个情况如果是if/else的话就很有可能演化成下面这个样子，我想你撇一眼都想拒绝这样的写法。
```cpp
if (type == BOSS) {
  applyMagic();
  applyShield();
  applyArmor();
  applyHealth();
}
else if (type == SLIME) {
  applyHealth();
}
else if (type == TANK) {
  applyShield();
  applyShield();
  applyArmor();
  applyHealth();
}
```
