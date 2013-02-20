#include <list>
#include "System.h"
#include "Component.h"
#include "Entity.h"

void System::entityChanged(const Entity* e, const list<Component*>& list)
{
  //Loop through list
  //Check that for each entry in neededComponents there is a
  //matching  Component in that list
  //update the entities list accordingly
}
