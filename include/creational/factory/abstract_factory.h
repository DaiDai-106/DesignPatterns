#ifndef DESIGN_PATTERNS_FACTORY_ABSTRACT_FACTORY_H
#define DESIGN_PATTERNS_FACTORY_ABSTRACT_FACTORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>

namespace DesignPatterns::Factory
{

class Drink
{
 public:
  virtual void prepare( int volume ) = 0;
};

class Tea : public Drink
{
 public:
  void prepare( int volume ) override { std::cout << "Tea " << volume << "ml\n" << std::endl; }
};

class Coffee : public Drink
{
 public:
  void prepare( int volume ) override { std::cout << "Coffee " << volume << "ml\n" << std::endl; }
};

/// 定义抽象工厂类
class DrinkFactory
{
 public:
  virtual std::unique_ptr<Drink> make_drink() = 0;
};

class TeaFactory : public DrinkFactory
{
 public:
  std::unique_ptr<Drink> make_drink() override { return std::make_unique<Tea>(); }
};

class CoffeeFactory : public DrinkFactory
{
 public:
  std::unique_ptr<Drink> make_drink() override { return std::make_unique<Coffee>(); }
};

class Factory
{
  std::map<std::string, std::unique_ptr<DrinkFactory>> factories;

 public:
  Factory()
  {
    factories[ "tea" ]    = std::make_unique<TeaFactory>();
    factories[ "coffee" ] = std::make_unique<CoffeeFactory>();
  }

  std::unique_ptr<Drink> create_drink( const std::string &type );
};

}  // namespace DesignPatterns::Factory

#endif  // DESIGN_PATTERNS_FACTORY_ABSTRACT_FACTORY_H