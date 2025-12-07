#include "creational/builder/combine_builder.h"

namespace DesignPatterns::Builder
{

PersonBuilder Person::Create() { return PersonBuilder{}; }

PersonBuilder::PersonBuilder() : PersonBuilderBase( p_ ) {}

PersonAddressBuilder PersonBuilderBase::lives() const { return PersonAddressBuilder{ person_ }; }

PersonJobBuilder PersonBuilderBase::works() const { return PersonJobBuilder{ person_ }; }

}  // namespace DesignPatterns::Builder