# Singleton Pattern (单例模式)

## 1. 简介
单例模式是很间的意思，即整个应用程序中只能有一个特定组件的实例，并提供全局访问点。它适合用于那些全局共享、状态唯一、或资源管理类的组件。你肯定有个疑问，那就是什么时候适合使用该模式，那这里进行一些说明，具备以下特点的组件适合使用单例模式：
1. 全局唯一性：系统中只需要一个实例。
2. 全局访问性：多个模块都需要访问同一个实例。
3. 资源集中管理：需要统一管理某种资源（配置、日志、连接、硬件等）。
4. 生命周期长：通常贯穿整个程序生命周期。

## 2. 单例模式的实现
因为使用单例模式，所以需要保证该对象的实例化不能超过一次。并且我们需要防止其能被多次构造，所以下面代码变的合理了起来
```cpp
class ConfigManager {
public:
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }

    std::string getValue(const std::string& key) const { /*...*/ }
    void setValue(const std::string& key, const std::string& value) { /*...*/ }

private:
    ConfigManager() { /* load config */ }
    ~ConfigManager() = default;
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
};
```
这里使用了局部静态变量，所以变量全局存在，并且只会初始化一次，同时也无法通过任何其他方式对该对象进行构造因为都delete和私有化了。因为返回值是引用，所以全局拿到的都是一个对象，修改也都会共享。

当然也可以使用静态成员变量（和局部静态变量是两个概念），静态成员变量分配在堆上，并且在创建时未必线程安全，如下所示：
```cpp
class ConfigManager {
public:
    static ConfigManager* getInstance() {
        if (!instance_) {
            instance_ = std::unique_ptr<ConfigManager>(new ConfigManager());
        }
        return instance_.get();
    }

private:
    ConfigManager() {}
    ~ConfigManager() {}
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    static std::unique_ptr<ConfigManager> instance_;
};

std::unique_ptr<ConfigManager> ConfigManager::instance_ = nullptr;
```
## 3. 单例模式存在的问题
1. 在单元测试时，单例模式会带来很大的困扰，因为无法轻易的创建多个实例，也无法轻易的替换实例。同时还要依赖这样的单例，如果是数据库，显然不希望用真实的数据库进行单元测试，这时候只能摒弃单例，写一个DummyDataBase。
2. 如果出现多线程中每一个线程都需要一个单独的单例时，那么单例需要和线程号进行绑定了。