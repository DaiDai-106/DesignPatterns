#include "creational/builder/combine_builder.h"
#include <iostream>
int test_builder()
{
  DesignPatterns::Builder::Person p = DesignPatterns::Builder::Person::Create()
                                          .lives()
                                          .at( "123 London Road" )
                                          .with_postcode( "SW1 1GB" )
                                          .in( "London" )
                                          .works()
                                          .at( "PragmaSoft" )
                                          .earning( 10e5 );

  std::cout << p << std::endl;
  return 0;
}
