#ifndef DESIGN_PATTERNS_BUILDER_COMBINE_BUILDER_H
#define DESIGN_PATTERNS_BUILDER_COMBINE_BUILDER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace DesignPatterns::Builder
{

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

// 1.这里主要的目的是尝试组合建造者模式
/**
 * @brief 简单记录某一个人的基本信息
 */
class Person
{
 public:
  // 主要目的是让下面这些能访问
  friend class PersonBuilder;
  friend class PersonAddressBuilder;
  friend class PersonJobBuilder;
  friend class PersonBuilderBase;

  static PersonBuilder Create();

  friend std::ostream &operator<<( std::ostream &os, const Person &person )
  {
    return os << "Address: " << person.address_ << ", " << person.post_code_ << ", " << person.city_
              << " | Work: " << person.company_name_ << ", " << person.salary_;
  }

 private:
  Person() {};

  // 个人住址信息
  std::string address_;
  std::string post_code_;
  std::string city_;

  // 企业信息
  std::string company_name_;
  double salary_{ 0.0 };
};

class PersonBuilderBase
{
 protected:
  Person &person_;
  PersonBuilderBase( Person &person ) : person_( person ) {}

 public:
  PersonAddressBuilder lives() const;
  PersonJobBuilder works() const;

  operator Person() { return std::move( person_ ); }
};

class PersonBuilder : public PersonBuilderBase
{
  Person p_;

 public:
  PersonBuilder();
};

class PersonAddressBuilder : public PersonBuilderBase
{
  using self = PersonAddressBuilder;

 public:
  explicit PersonAddressBuilder( Person &person ) : PersonBuilderBase( person ) {}

  self &at( std::string street_address )
  {
    person_.address_ = street_address;
    return *this;
  }

  self &with_postcode( std::string post_code )
  {
    person_.post_code_ = post_code;
    return *this;
  }

  self &in( std::string city )
  {
    person_.city_ = city;
    return *this;
  }
};

class PersonJobBuilder : public PersonBuilderBase
{
  using self = PersonJobBuilder;

 public:
  explicit PersonJobBuilder( Person &person ) : PersonBuilderBase( person ) {}

  self &at( std::string company_name )
  {
    person_.company_name_ = company_name;
    return *this;
  }

  self &earning( double annual_income )
  {
    person_.salary_ = annual_income;
    return *this;
  }
};

}  // namespace DesignPatterns::Builder

#endif  // DESIGN_PATTERNS_BUILDER_COMBINE_BUILDER_H
