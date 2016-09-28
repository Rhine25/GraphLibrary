CC=gcc
CCC=g++
CFLAGS=-g -c -D_DEBUG
CCFLAGS=-g -c -D_DEBUG
CLINK=-lsfml-graphics -lsfml-window -lsfml-system -lpthread

EXEC=Pong

CFILES:=$(wildcard src/*.c)
CPPFILES:=$(wildcard src/*.cpp)
COBJ:=$(addprefix obj/,$(notdir $(CFILES:.c=_c.o)))
CPPOBJ:=$(addprefix obj/,$(notdir $(CPPFILES:.cpp=_cpp.o)))

all: $(COBJ) $(CPPOBJ)
	
	$(CCC) $^ -o bin/$(EXEC) $(CLINK)
	
obj/%_c.o: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

obj/%_cpp.o: src/%.cpp
	$(CCC) $(CCFLAGS) $^ -o $@

clean:
	rm obj/*.o;

mrproper: clean
	rm bin/$(EXEC)
