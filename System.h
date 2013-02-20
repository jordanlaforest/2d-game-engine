#ifndef SYSTEM_H
#define SYSTEM_H
class System
{
  protected:
    list<Entity*> entities; //List of relevant entities for the system
    vector<ComponentType> neededComponents; //Defines what components are used
  public:
    void update()=0;
    void entityChanged(const Entity*, const list<Component*>&);

};
#endif
