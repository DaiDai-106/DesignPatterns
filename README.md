# C++20 设计模式 (Design Patterns)

本项目旨在通过 C++20 标准来实现和演示各种经典的设计模式。仓库结构清晰，代码与文档结合，方便学习和查阅。

## 📂 项目结构

- **`src/`**: 包含设计模式的核心实现代码 (`.cpp`)。
- **`include/`**: 包含头文件 (`.h`) 以及对应的模式详解文档 (`.md`)。
- **`test/`**: 包含针对各个设计模式的测试用例 (`test_*.cpp`)。

## 🛠️ 如何构建与运行

本项目使用 CMake 进行构建。

1. **基本构建命令**:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```

2. **构建选项**:
   - `-DRUN_CREATIONAL=ON`: 启用创建型模式的编译（默认开启）。
   - `-DSHARED_LIB=ON`: 编译为动态库（默认开启）。

3. **运行测试**:
   构建完成后，可执行文件位于 `build/` 目录下，例如：
   ```bash
   ./build/test_factory
   ./build/test_builder
   ```

## 📚 设计模式目录

### 创建型模式 (Creational Patterns)

| 模式名称 | 描述 | 文档与代码 |
| :--- | :--- | :--- |
| **建造者模式 (Builder)** |  将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。| [查看文档](./include/creational/builder/builder.md) |
| **工厂模式 (Factory)** | 定义一个创建对象的接口，让其子类自己决定实例化哪一个工厂类。囊括了简单工厂、工厂方法及抽象工厂。 | [查看文档](./include/creational/factory/factory.md) |
| **原型模式 (Prototype)** | 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。 | [查看文档](./include/creational/prototype/prototype.md) |
| **单例模式 (Singleton)** | 确保一个类只有一个实例，并提供一个全局访问点。同时保证线程安全。 | [查看文档](./include/creational/singleton/singleton.md) |

---

### 结构型模式 (Structural Patterns)
| | | |
| :--- | :--- | :--- |
| **适配器模式 (Adapter)** | 将一个类的接口转换成客户端所期望的另一个接口。适配器模式让原本由于接口不兼容而不能一起工作的那些类可以一起工作。 | [查看文档](./include/structural/adapter/adapter.md) |
| **桥接模式 (Bridge)** | 将抽象部分与实现部分分离，使它们可以独立变化。 | [查看文档](./include/structural/bridge/bridge.md) |
| **组合模式 (Composite)** | 将对象组合成树形结构以表示"部分-整体"的层次结构。 | [查看文档](./include/structural/composite/composite.md) |
| **装饰器模式 (Decorator)** | 动态地给一个对象添加一些额外的职责。就增加功能来说，装饰器模式比生成子类更为灵活。 | [查看文档](./include/structural/decorator/decorator.md) |
| **外观模式 (Facade)** | 为子系统中的一组接口提供一个一致的界面。外观模式定义了一个高层接口，使得子系统更易使用。 | [查看文档](./include/structural/facade/facade.md) |
| **享元模式 (Flyweight)** | 通过共享技术避免因创建大量相似对象导致的内存开销。 | [查看文档](./include/structural/flyweight/flyweight.md) |
| **代理模式 (Proxy)** | 为其他对象提供一种代理以控制对这个对象的访问。代理模式在客户端和目标对象之间起到中介作用。 | [查看文档](./include/structural/proxy/proxy.md) |

---

### 行为型设计模式 (Behavioral Patterns)

| 模式名称 | 描述 | 文档与代码 |
| :--- | :--- | :--- |
| **责任链模式 (Chain of Responsibility)** | 使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。 | [查看文档](./include/behavioral/responsibility_chain/responsibility_chain.md) |
| **命令模式 (Command)** | 将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化。。 | [查看文档](./include/behavioral/command/command.md) |