# Proxy Pattern (代理模式)

## 智能指针
智能指针是代理模式最简单且最直接的展示，智能指针（如 C++ 的 std::shared_ptr / std::unique_ptr）就是一个代理对象，它控制对真实对象的访问和生命周期管理。换句话说：用户访问智能指针 → 实际操作的是托管的真实对象，智能指针在中间做了一些额外的逻辑（引用计数、延迟释放、线程安全），用户完全不知道它访问的不是裸指针，而是代理。

## 1. 属性代理
这是一个非常简单的代理行为，考虑到C++没有类似python getter setter的语法糖，所以最常见的方法是创建一对和成员名称一样的 set/get 函数。
但是如果我们想使用属性成员的访问语法呢？
我们设计这样的一个属性代理，同时还为其提供特定的访问器和修改器。
```cpp
template <typename T>
class Property {
    T value;
    std::function<void(const T&)> setter_hook;
    std::function<void()> getter_hook;

public:
    Property(T init,
             std::function<void(const T&)> s = nullptr,
             std::function<void()> g = nullptr)
        : value(init), setter_hook(s), getter_hook(g) {}

    // 重载赋值运算符
    Property<T>& operator=(const T& v) {
        if (setter_hook) setter_hook(v);
        value = v;
        return *this;
    }

    // 隐式类型转换，访问时触发 getter
    operator T() const {
        if (getter_hook) getter_hook();
        return value;
    }
};
```
那么在后续的调用时，就可以像如下的方式进行调用了：
```cpp
class Person {
public:
    Property<std::string> name;

    Person() : name(
        "", 
        [](const std::string& v){ 
            if(v.empty()) throw std::invalid_argument("名字不能为空"); 
            std::cout << "setter: name 被修改为 " << v << "\n";
        },
        [](){ std::cout << "getter: 访问 name\n"; }
    ) {}
};

int main() {
    Person p;
    p.name = "Alice";       // 修改属性 → setter_hook
    std::cout << p.name << "\n"; // 访问属性 → getter_hook
}
```
## 2. 虚拟代理
这个代理模式的主要目的是为了对一些对象进行延迟加载，比如在某些情况下，我们只希望在访问对象时在实例化对象，那么在未使用之前，该对象会保持 nullptr的状态。这种情况叫做惰性加载。对于不知道后续会哪里进行延迟的话，这里可以选择一种代理的方式，即虚拟代理。

这里有一个例子，假设有一个大图片类 RealImage，加载非常耗费资源。我们希望，用户访问 Image 时，只有在第一次调用 display() 时才真正加载图片，这就是虚拟代理：延迟加载真实对象。

```cpp
class RealImage : public Image {
private:
    std::string filename;

    void loadFromDisk() {
        std::cout << "加载图片 " << filename << " 从磁盘...\n";
    }

public:
    RealImage(const std::string& fname) : filename(fname) {
        loadFromDisk();
    }

    void display() override {
        std::cout << "显示图片: " << filename << "\n";
    }
};
```
那么我们需要设计一个代理，即只有第一次display的时候才从磁盘加载，后续就不用加载了：
```cpp
class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;

public:
    ProxyImage(const std::string& fname) : filename(fname), realImage(nullptr) {}

    void display() override {
        if (!realImage) {
            // 延迟创建真实对象
            realImage = std::make_unique<RealImage>(filename);
        }
        realImage->display();
    }
};
```
通过上述的方式，就实现了一个简单的延迟代理（ 虚拟代理 ）。

## 3. 通信代理
这里的例子太多了，比如GRPC服务通信， ROS等都使用了通信代理。这里就不过多讲解了。

比如 grpc调用服务时， Stub就是客户端的“通信代理”，把本地函数调用封装成网络 RPC 调用。在 gRPC 中，我写的是 本地函数调用：
```cpp
client.Add(a, b);
```
但是实际上的流程是， Client → Stub → 网络传输 → Server。 那么在这个过程中，代理发挥了哪些作用呢？ 有如下的作用
| 作用            | 说明                    |
| ------------- | --------------------- |
| **序列化参数**     | 把 a、b 转成 protobuf 二进制 |
| **发送 RPC 请求** | 通过 HTTP/2 发给服务器       |
| **等待响应**      | 接收服务器返回的数据            |
| **反序列化结果**    | 把 protobuf 数据解码成返回值   |
| **返回给用户**     | 像本地函数一样返回 int         |
这样的好处是啥呢，首先用户不知道对象是远程的，Stub代理代表远程对象，负责请求/响应，用户只管写本地代码。
## 4. 值代理
顾名思义，就是值的代理，是一种以“对象”来代表“一个值”的代理方式。它让用户以对象的方式使用一个值，但在访问或修改时插入额外逻辑。
值代理（Value Proxy）满足以下条件：
1.它看起来像一个值,（支持隐式转换、比较、赋值……）
2. 但它不是值（内部保存的是引用、指针、句柄等间接访问方式）
3. 访问时可以走额外逻辑,比如：写回实际存储,延迟加载等
下面例子里的X就是标准的值代理。
```cpp
class ValueProxy {
    int& ref;  // 它不存值，它代理一个值
public:
    ValueProxy(int& r) : ref(r) {}

    operator int() const {
        std::cout << "读取 x\n";
        return ref;
    }

    ValueProxy& operator=(int v) {
        std::cout << "写入 x = " << v << "\n";
        ref = v;
        return *this;
    }
};

class A {
    int _x;
public:
    ValueProxy x{_x};
};  
``