# Facade Pattern (外观模式)

# 1. 介绍
这里先打个简单的比方，当我们买房子的时候，我们通常关心的是房子的外观，相比之下，我们可能不太会关注内部系统，比如下水道设施等。所以，这里诞生出来了一种想法，有的时候需要一种简单的方式和复杂的系统交互，这里的系统可以是一组或单个复杂组件。

# 2. 外观模式使用场景
1. 当需要为复杂的子系统提供一个简单的接口时
2. 当子系统有很多相互依赖的类时
3. 当想要将子系统分层时

简单来说，外观模式 = 给复杂系统套一层“傻瓜式操作面板”

# 3. 电脑系统
一个电脑有Disk， 有Memory，有CPU。
```cpp
class CPU {
public:
  void freeze() { std::cout << "CPU freeze\n"; }
  void execute() { std::cout << "CPU execute\n"; }
};

class Memory {
public:
  void load() { std::cout << "Memory load\n"; }
};

class Disk {
public:
  void read() { std::cout << "Disk read\n"; }
};
```
如果不是外观设计模式，我会用如下的方式执行这几个组建：
```cpp
CPU cpu;
Memory mem;
Disk disk;
cpu.freeze();
mem.load();
disk.read();
cpu.execute();
```
我想看到上面的调用，你肯定不想这么写，所以下面就是简单的外观系统的设计了：
```cpp
class Computer {
public:
  void start() {
    cpu_.freeze();
    memory_.load();
    disk_.read();
    cpu_.execute();
  }

private:
  CPU cpu_;
  Memory memory_;
  Disk disk_;
};
```
在这样的设计下，完成刚才的调用就只有两行代码了
```cpp
Computer computer;
computer.start();
```
# 4.总结
类似机械臂规划库的规划接口，其实也是非常简单的调用模式，一个plan就解决了所有。