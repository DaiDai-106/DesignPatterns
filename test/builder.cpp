#include "builder/combine_builder.h"
#include <iostream>

int main()
{
  DesignPatterns::Builder::Person p = DesignPatterns::Builder::Person::Create()
                                          .lives()
                                          .at( "123 London Road" )
                                          .with_postcode( "SW1 1GB" )
                                          .in( "London" )
                                          .works()
                                          .at( "PragmaSoft" )
                                          .earning( 100.32 );

  std::cout << p << std::endl;
  return 0;
}
