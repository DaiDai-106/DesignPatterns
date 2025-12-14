#include "behavioral/responsibility_chain/responsibility_chain.h"
#include <iostream>

int test_responsibility_chain()
{
  std::cout << "=== 责任链示例 ===" << std::endl;

  DesignPatterns::ResponsibilityChain::Planner planner;
  DesignPatterns::ResponsibilityChain::JointPath path;
  path.points.push_back( {
      { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
      10.0
  } );
  path.points.push_back( {
      { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
      20.0
  } );
  path.points.push_back( {
      { 2.0, 2.0, 2.0, 2.0, 0.0 },
      30.0
  } );
  if ( planner.validateJoint( path ) ) {
    std::cout << "验证通过" << std::endl;
  } else {
    std::cout << "验证失败" << std::endl;
  }

  return 0;
}