CXX=g++
INCLUDEFLAGS=-Ihelper/rendering -Ihelper/library -Isystems -Icomponents -I./
CXXFLAGS= -MMD -Wall -Wextra -pedantic -std=c++11 -g $(INCLUDEFLAGS)
LDLIBS= -lGL -lglfw -lGLEW -lIL
EXECUTABLE=test
#objects
SYSTEMS=systems/System.o systems/PrintTransformSystem.o systems/RenderSystem.o
COMPONENTS=components/Component.o components/TransformComponent.o components/SpriteComponent.o
HELPERS= helper/rendering/ShaderProgram.o helper/rendering/Sprite.o helper/rendering/SpriteManager.o helper/rendering/Texture.o helper/rendering/SpriteBatch.o
OBJECTS= main.o GameManager.o Entity.o $(SYSTEMS) $(COMPONENTS) $(HELPERS) $(LIBRARYINIT)
DEPENDENCIES= $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

-include $(DEPENDENCIES)

.PHONY: clean, run

clean:
	rm -rf $(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE)

#My machine needs primusrun to run this
run: $(EXECUTABLE)
	primusrun ./$(EXECUTABLE)

#Otherwise framerate is limited at 60 fps
perftest: $(EXECUTABLE)
	vblank_mode=0 primusrun ./$(EXECUTABLE)
