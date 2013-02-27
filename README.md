This game engine uses a Component/Entity/System design meaning that Entities do not do any processing themselves. They have components associated with them that that also do not do any processing but instead define certain attributes needed by the systems that do.

It uses OpenGL for rendering (with GLFW, GLEW, and GLM), I will probably also use GLFW for input, Lua (using LuaBind) for scripting, and Box2D for physics. Those are not decided for sure though.

Currently the engine will draw each entity (with a TransformComponent) to the screen as a white square. Next I plan on making a texture loading/managing class and then a RenderComponent that will define what texture to draw for an entity.
