# Flyweight Pattern (享元模式)

## 1. 介绍
享元设计模式（Flyweight Pattern）是一种结构型设计模式，它的主要目的避免因创建大量相似对象导致的内存开销。主要在如下的场景中是适合的：
- 系统中有大量相似对象，造成内存开销过大
- 对象的大部分状态可以外部化（可以分为内部状态和外部状态）
- 这些对象可以按照内蕴状态分为很多组，当把外蕴对象从对象中剔除出来时，每一组对象都可以用一个对象来代替
- 系统不依赖于这些对象的身份，这些对象是不可分辨的

## 2. 结构组成

享元模式主要包含以下角色：

1. **抽象享元（Flyweight）**：定义对象的接口，通过这个接口可以接受并作用于外部状态
2. **具体享元（ConcreteFlyweight）**：实现抽象享元接口，并为内部状态增加存储空间
3. **享元工厂（FlyweightFactory）**：创建并管理享元对象，确保合理地共享享元
4. **客户端（Client）**：维持对享元对象的引用，计算或存储外部状态

## 3. 用户名共享系统示例
假设有一个游戏，里面需要有用户名，如果出现大量用户是同样的名称，如果每个名称都存储，那肯定是存储爆炸的事情。我们设计只存储一次该名字，然后通过享元模式共享相同名称的用户。
这里举一个例子:
享元工厂的核心实现：

```cpp
class User
{
 public:
  virtual ~User()                                          = default;
  virtual void display( const std::string &context ) const = 0;
};

// 具体享元类 - 共享的用户名
class SharedUser : public User
{
 private:
  std::string firstName;
  std::string lastName;

 public:
  SharedUser( const std::string &first, const std::string &last ) : firstName( first ), lastName( last ) {}

  void display( const std::string &context ) const override
  {
    std::cout << "用户: " << firstName << " " << lastName << " (上下文: " << context << ")" << std::endl;
  }

  const std::string &getFirstName() const { return firstName; }
  const std::string &getLastName() const { return lastName; }
};
```
在上述的基础上，通过构建一个享元工厂，对同样的User进行缓存，这里有如下的细节实现：
```cpp
class UserFactory
{
 private:
  // 共享池，存储已经创建的用户名对象
  std::map<std::string, std::shared_ptr<SharedUser>> users;

  // 生成唯一键
  std::string getKey( const std::string &first, const std::string &last ) const { return first + "_" + last; }

 public:
  // 获取或创建共享用户对象
  std::shared_ptr<SharedUser> getUser( const std::string &first, const std::string &last )
  {
    std::string key = getKey( first, last );

    // 如果对象已存在，直接返回
    if ( users.find( key ) != users.end() ) { return users[ key ]; }

    // 否则创建新对象并放入共享池
    std::cout << "创建新用户: " << first << " " << last << std::endl;
    auto newUser = std::make_shared<SharedUser>( first, last );
    users[ key ] = newUser;
    return newUser;
  }
};
```
这里也简单设计了一个用户端的使用例子，主要目的是为了说明这种内部相似对象保存，外部状态无关的情况：
```cpp
// 客户端上下文 - 存储外部状态
class UserContext
{
 private:
  std::shared_ptr<SharedUser> user;
  std::string sessionInfo;  // 外部状态1：会话信息
  std::string ipAddress;    // 外部状态2：IP地址

 public:
  UserContext( std::shared_ptr<SharedUser> u, const std::string &session, const std::string &ip )
      : user( u ), sessionInfo( session ), ipAddress( ip )
  {
  }

  void display() const
  {
    std::cout << "会话: " << sessionInfo << ", IP: " << ipAddress << " - ";
    user->display( "活跃用户" );
  }
};
```
那么最终外部调用过程如下，你会发现同名的用户共用了一个User
```cpp
  std::vector<UserContext> users;

  // 添加多个用户，注意有重复的用户名
  users.emplace_back( userFactory.getUser( "张", "三" ), "session_123", "192.168.1.1" );
  users.emplace_back( userFactory.getUser( "李", "四" ), "session_124", "192.168.1.2" );
  users.emplace_back( userFactory.getUser( "张", "三" ), "session_125", "192.168.1.3" );  // 重复用户名
  users.emplace_back( userFactory.getUser( "王", "五" ), "session_126", "192.168.1.4" );
  users.emplace_back( userFactory.getUser( "李", "四" ), "session_127", "192.168.1.5" );  // 重复用户名
  for ( const auto &user : users ) { user.display(); }
```



## 4. 与其他模式的区别
- **与单例模式的区别**：享元模式可以有多个实例，但每个实例代表不同的共享对象；单例模式只有一个实例
- **与原型模式的区别**：享元模式关注共享以节省内存；原型模式关注复制以创建新对象
- **与装饰器模式的区别**：享元模式关注对象共享；装饰器模式关注给对象添加功能