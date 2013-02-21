#include <iostream>

#include "GameManager.h"
#include "Entity.h"

using namespace std;

int main()
{
  GameManager gm;
  Entity player = gm.createEntity("player");
  cout << "player: " << player.name << " " << player.getId() << endl;
}
