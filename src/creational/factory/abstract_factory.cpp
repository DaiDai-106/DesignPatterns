#include "creational/factory/abstract_factory.h"

namespace DesignPatterns::Factory
{

std::unique_ptr<Drink> Factory::create_drink( const std::string &type )
{
  if ( factories.find( type ) == factories.end() ) { throw std::runtime_error( "Unknown drink type" ); }
  return factories[ type ]->make_drink();
}

}  // namespace DesignPatterns::Factory