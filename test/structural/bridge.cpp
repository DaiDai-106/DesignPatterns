#include "structural/bridge/bridge.h"
#include <iostream>
#include <memory>

int main()
{
  using namespace DesignPatterns::Bridge;
  std::cout << "=== Bridge Pattern Test ===\n" << std::endl;

  // 1. 创建不同的实现 (Renderers)
  auto vector_renderer = std::make_shared<VectorRenderer>();
  auto raster_renderer = std::make_shared<RasterRenderer>();

  // 2. 创建抽象对象 (Shapes)，并注入具体的实现 (Bridge connection)
  // 圆形使用矢量渲染
  std::shared_ptr<Shape> circle = std::make_shared<Circle>( vector_renderer, 5.0f );

  // 3. 运行测试
  std::cout << "--- Drawing Circle with Vector Renderer ---" << std::endl;
  circle->draw();

  // 4. 动态改变实现 (如果我们要演示桥接的灵活性：可以在运行时换实现 - 这里我们新建一个对象演示)
  std::cout << "\n--- Switching Implementation: Circle with Raster Renderer ---" << std::endl;
  auto circle_raster = std::make_shared<Circle>( raster_renderer, 5.0f );
  circle_raster->draw();

  // 5. 改变抽象部分的属性，不影响实现部分
  std::cout << "\n--- Resizing Circle ---" << std::endl;
  circle_raster->resize( 2.0f );  // 半径变为 10.0
  circle_raster->draw();

  return 0;
}
