CXX=g++
CXXFLAGS= -MMD -Wall -Wextra -pedantic -Werror -std=c++11 -g
LDLIBS= -lGL -lglfw -lGLEW
EXECUTABLE=test
OBJECTS= main.o GameManager.o Entity.o systems/System.o systems/PrintTransformSystem.o systems/RenderSystem.o components/Component.o components/TransformComponent.o helper/ShaderProgram.o
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
