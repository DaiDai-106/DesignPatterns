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
*持续更新中...*
