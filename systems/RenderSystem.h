#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include <string>
#include "System.h"

class RenderSystem : public System
{
  public:
    RenderSystem(GameManager&, const std::string& title="Game Window");
    ~RenderSystem();
    void update();
};
#endif
