#include "creational/factory/factory.h"

namespace DesignPatterns::Factory
{

std::vector<std::weak_ptr<Wall>> WallFactory::walls;
void SolidWall::draw() { std::cout << "SolidWall draw\n" << std::endl; }

}  // namespace DesignPatterns::Factory