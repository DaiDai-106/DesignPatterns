# Adapter Pattern (适配器模式)

## 1. 简介
从这一设计模式开始，从原本的创建型设计模式，转变为结构型设计模式。适配器的作用是将一个接口转换成另一个接口，适配器模式让原本接口不兼容的类可以协同工作。

## 2. 适配器
假设有如下定义好的类：
```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};
```
同时在这之前实现了一个画矩形的实现：
```cpp
class LegacyRectangle {
public:
    void drawRectangle(int x1, int y1, int x2, int y2) {
        // 旧绘制逻辑
    }
};
```
我们很容易发现接口是不兼容的，那有什么方法可以兼容呢，有如下适配器的实现：
```cpp
class RectangleAdapter : public Shape {
public:
    RectangleAdapter(LegacyRectangle& legacyRectangle) : legacyRectangle(legacyRectangle) {}
    void draw() const override {
        legacyRectangle.drawRectangle(0, 0, 10, 10);
    }
private:
    LegacyRectangle& legacyRectangle;
};
```
通过上面的实现，在调用时，新的接口可以调用旧的接口，从而实现接口的兼容。
```cpp
int main() {
    LegacyRectangle legacyRectangle;
    Shape* shape = new RectangleAdapter(legacyRectangle);
    shape->draw();
    delete shape;
    return 0;
}
```


## 3. 双向转换器
这其实是对适配器模式的扩展，适配器模式只适配一个方向，而双向转换器则适配两个方向。



## 4.总结
当看完这个文档时， 你肯定会有个疑问什么时候应该使用适配器，这里有一个流程：
我们可以用一个简单的决策树来判定是否需要使用适配器模式：

```mermaid
graph TD
    Start[我想复用现有的类 A 吗?] -->|No| NoAdapter[不需要适配器]
    Start -->|Yes| CheckInterface[A 的接口符合当前系统的期望吗?]
    
    CheckInterface -->|Yes| DirectUse[直接使用 A]
    CheckInterface -->|No| CanModify[我能修改 A 的源码吗?]
    
    CanModify -->|Yes & Should| Modify[直接修改 A (重构)]
    CanModify -->|No / Shouldn't| CheckGoal[是否只需要转换接口而不改变行为?]
    
    CheckGoal -->|Yes| Adapter[✅ 适配器模式]
    CheckGoal -->|No| CheckFunction[具体需求是什么?]
    
    CheckFunction -->|增加功能| Decorator[装饰器模式]
    CheckFunction -->|控制访问| Proxy[代理模式]
    CheckFunction -->|结构重塑| Bridge[桥接模式]
```

当然一般在接入第三方库，老旧接口迁移时会尝试使用该设计模式。