#ifndef DESIGN_PATTERNS_STRUCTURAL_BRIDGE_H
#define DESIGN_PATTERNS_STRUCTURAL_BRIDGE_H

#include <iostream>
#include <memory>
#include <string>

namespace DesignPatterns::Bridge
{

// 1. 实现接口 (Implementor): 渲染器
class Renderer
{
 public:
  virtual ~Renderer()                           = default;
  virtual void render_circle( float radius )    = 0;
  virtual std::string get_renderer_name() const = 0;
};

// 具体实现 A: 矢量渲染器 (模拟)
class VectorRenderer : public Renderer
{
 public:
  void render_circle( float radius ) override
  {
    std::cout << "[Vector] Drawing a circle using mathematical curves, radius=" << radius << std::endl;
  }

  std::string get_renderer_name() const override { return "VectorRenderer"; }
};

// 具体实现 B: 栅格渲染器 (模拟)
class RasterRenderer : public Renderer
{
 public:
  void render_circle( float radius ) override
  {
    std::cout << "[Raster] Drawing circle pixels, radius=" << radius << std::endl;
  }

  std::string get_renderer_name() const override { return "RasterRenderer"; }
};

// 2. 抽象接口 (Abstraction): 形状
// 它持有一个对实现部分 (Renderer) 的引用
class Shape
{
 protected:
  std::shared_ptr<Renderer> renderer_;

 public:
  explicit Shape( std::shared_ptr<Renderer> renderer ) : renderer_( std::move( renderer ) ) {}
  virtual ~Shape()                    = default;
  virtual void draw()                 = 0;
  virtual void resize( float factor ) = 0;
};

// 扩展抽象接口 (RefinedAbstraction)
class Circle : public Shape
{
 private:
  float radius_;

 public:
  Circle( std::shared_ptr<Renderer> renderer, float radius ) : Shape( std::move( renderer ) ), radius_( radius ) {}

  void draw() override
  {
    std::cout << "Circle (Abstraction) is asking renderer to draw:" << std::endl;
    renderer_->render_circle( radius_ );
  }

  void resize( float factor ) override { radius_ *= factor; }
};

}  // namespace DesignPatterns::Bridge

#endif  // DESIGN_PATTERNS_STRUCTURAL_BRIDGE_H
