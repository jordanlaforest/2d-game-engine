CXX=g++
#CXXFLAGS=-Wall -Wextra -pedantic
CXXFLAGS= -MMD -std=c++11
EXECUTABLE=test
OBJECTS= main.o GameManager.o Entity.o systems/System.o components/Component.o components/TransformComponent.o
DEPENDENCIES= $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

-include $(DEPENDENCIES)

.PHONY: clean

clean:
	rm -rf $(OBJECTS) $(DEPENDENCIES) $(EXECUTABLE)
