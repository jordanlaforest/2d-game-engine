CC=g++
#CFLAGS=-Wall -Wextra -pedantic -std=c++0x
CFLAGS=-std=c++11
EXECUTABLE=test

$(EXECUTABLE): main.o GameManager.o Entity.o systems/System.o components/Component.o components/TransformComponent.o
	$(CC) main.o GameManager.o Entity.o System.o Component.o TransformComponent.o -o $(EXECUTABLE)

main.o: main.cpp GameManager.h Entity.h components/Component.h systems/System.h
	$(CC) -c $(CFLAGS) main.cpp
GameManager.o: GameManager.cpp GameManager.h Entity.h components/Component.h systems/System.h
	$(CC) -c $(CFLAGS) GameManager.cpp
Entity.o: Entity.cpp GameManager.h Entity.h components/Component.h systems/System.h
	$(CC) -c $(CFLAGS) Entity.cpp
components/Component.o: components/Component.cpp components/Component.h
	$(CC) -c $(CFLAGS) components/Component.cpp
components/TransformComponent.o: components/TransformComponent.cpp components/TransformComponent.h components/Component.h
	$(CC) -c $(CFLAGS) components/TransformComponent.cpp
systems/System.o: systems/System.cpp systems/System.h components/Component.h Entity.h
	$(CC) -c $(CFLAGS) systems/System.cpp

.PHONY: clean

clean:
	rm -rf *.o $(EXECUTABLE)
