#include "structural/facade/facade.h"
#include <iostream>

int test_facade()
{
  using namespace DesignPatterns::Facade;
  HomeTheaterFacade homeTheater;
  homeTheater.watchMovie( "The Dark Knight" );
  homeTheater.endMovie();
  homeTheater.listenToMusic();
  return 0;
}