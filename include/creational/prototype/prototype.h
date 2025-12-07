#ifndef DESIGN_PATTERNS_FACTORY_PROTOTYPE_H
#define DESIGN_PATTERNS_FACTORY_PROTOTYPE_H

#include <iostream>
#include <string>

namespace DesignPatterns::Factory
{

class Address
{
 public:
  virtual ~Address()             = default;
  virtual void show() const      = 0;
  virtual Address *clone() const = 0;  // 原型接口
};

class ExtendedAddress : public Address
{
 private:
  std::string suite;

 public:
  ExtendedAddress( const std::string &s ) : suite( s ) {}
  void show() const override { std::cout << suite << std::endl; }
  Address *clone() const override { return new ExtendedAddress( *this ); }
};

}  // namespace DesignPatterns::Factory

#endif  // DESIGN_PATTERNS_FACTORY_PROTOTYPE_H