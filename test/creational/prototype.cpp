#include "creational/prototype/prototype.h"

int main()
{
  DesignPatterns::Factory::Address *a = new DesignPatterns::Factory::ExtendedAddress( "Suite 456" );
  a->show();

  auto b = a->clone();
  b->show();

  delete a;
  delete b;

  return 0;
}