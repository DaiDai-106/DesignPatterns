#include "structural/flyweight/flyweight.h"
#include <iostream>

int test_flyweight()
{
  std::cout << "=== 享元模式演示 ===" << std::endl;
  auto treeFactory = std::make_shared<DesignPatterns::Flyweight::TreeFactory>();
  DesignPatterns::Flyweight::Forest forest( treeFactory );

  // 在森林中种植大量树木，但只有少数几种类型
  forest.plantTree( 10, 20, "橡树", "绿色" );
  forest.plantTree( 15, 30, "松树", "深绿" );
  forest.plantTree( 25, 40, "橡树", "绿色" );  // 重复类型
  forest.plantTree( 35, 50, "枫树", "红色" );
  forest.plantTree( 45, 60, "松树", "深绿" );  // 重复类型
  forest.plantTree( 55, 70, "橡树", "绿色" );  // 重复类型
  forest.plantTree( 65, 80, "桦树", "白色" );
  forest.plantTree( 75, 90, "枫树", "红色" );   // 重复类型
  forest.plantTree( 85, 100, "松树", "深绿" );  // 重复类型

  forest.render();
  return 0;
}