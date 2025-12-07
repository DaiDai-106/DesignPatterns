#include "creational/factory/factory.h"
#include "creational/factory/abstract_factory.h"
#include <iostream>

int test_factory()
{
  auto wall = DesignPatterns::Factory::WallFactory::create_partition();
  wall->draw();

  DesignPatterns::Factory::Factory factory;
  auto my_drink = factory.create_drink( "coffee" );
  my_drink->prepare( 100 );

  return 0;
}