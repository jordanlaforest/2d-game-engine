#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include "System.h"

class RenderSystem : public System
{
  public:
    RenderSystem(GameManager&);
    ~RenderSystem();
    void update();
};
#endif
