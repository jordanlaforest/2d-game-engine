#ifndef PRINT_TRANSFORM_SYSTEM
#define PRINT_TRANSFORM_SYSTEM

#include "System.h"

//A test system that will just print out the position of each entity
//and its name
class PrintTransformSystem : public System
{
  public:
    PrintTransformSystem(GameManager&);
    void update();
};
#endif