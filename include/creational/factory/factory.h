#ifndef DESIGN_PATTERNS_FACTORY_FACTORY_H
#define DESIGN_PATTERNS_FACTORY_FACTORY_H

#include <iostream>
#include <memory>
#include <vector>

namespace DesignPatterns::Factory
{

class Wall
{
 public:
  virtual void draw() = 0;
  virtual ~Wall()     = default;
};

class SolidWall : public Wall
{
 protected:
  SolidWall() {}

 public:
  virtual void draw() override;
  friend class WallFactory;  // 工厂可以访问构造函数
};

class WallFactory
{
 public:
  static std::vector<std::weak_ptr<Wall>> walls;

  static std::shared_ptr<Wall> create_partition()
  {
    auto ptr = std::shared_ptr<SolidWall>( new SolidWall() );
    // auto ptr = std::make_shared<SolidWall>();  // 这样会编译报错
    walls.push_back( ptr );
    return ptr;
  }
};

}  // namespace DesignPatterns::Factory
#endif
