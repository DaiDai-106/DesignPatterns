# Bridge Pattern (桥接模式)

## 1. 简介
桥接模式其实很简单，它可以将两个不相关的组建链接起来。同时抽象接口也允许组建之间在不了解具体实现的情况下进行交互。（注意，比起后面的中介者模式，参与者在这里其实是互相知道的，接口也是有一些相关性的）  

## 2.回顾
Pimpl模式，通过把实现细节移到 .cpp 中，用指针隐藏实现，从而降低编译依赖、稳定 ABI、隐藏实现细节。
接下来是一个传统的写法，这样的写法问题是如果我一旦改动了 data或者table的定义，那就是重新编译。
```cpp
#include <vector>
#include <string>
#include <map>

class Widget {
public:
    void draw();
private:
    std::vector<int> data_;
    std::map<std::string, int> table_;
};
```
所以通过 Pimpl模式，在头文件中只用定义，不用包含任何的细节， 可以看到下面的代码中连 #include <vector> 都不需要了。
```cpp
// widget.h 文件

class Widget {
public:
    void draw();
private:
    class Impl;
    Impl* pImpl_;
};


// widget.cpp 文件
#include "widget.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

struct Widget::Impl {
    std::vector<int> data;
    std::map<std::string, int> table;

    void draw() {
        std::cout << "draw widget\n";
    }
};

Widget::Widget()
    : impl_(std::make_unique<Impl>()) {}

Widget::~Widget() = default;

Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;

void Widget::draw() {
    impl_->draw();
}
```
通过这样的设计，可以让头文件变的相当的简介。同时会降低编译时间。
## 3. 桥接模式
相比较Pimpl的私有桥的设计，下面的例子是个更通用的实现方式：
```cpp
class Shape {
public:
    virtual void draw() = 0;
protected:
    std::shared_ptr<Color> color_;
};

class Circle : public Shape {
    void draw() override {
        std::cout << "Draw circle in " << color_->name() << "\n";
    }
};
```
在运行时，可以用不同的color进行替换，同时Shape 和 Color 都可以独立的扩展。更像是一种公共的桥。
## 4. 一些想法
看上去，比如我设计的规划器交互软件，有很多SHAPE格式可以是OCC的格式，也可以是别的格式，同时渲染器也有多样性，比如OCC自带的GUI渲染，或者使用VTK进行渲染, 或者直接使用OpenGL进行渲染。这里感觉就非常适合使用这样的桥接模式进行设计了。