CC=gcc
CCC=g++
CFLAGS=-g -Wall -c -D_DEBUG
CCFLAGS=-g -c -D_DEBUG
CLINK=

EXEC=graf

CFILES:=$(wildcard src/*.c)
CPPFILES:=$(wildcard src/*.cpp)
COBJ:=$(addprefix obj/,$(notdir $(CFILES:.c=_c.o)))
CPPOBJ:=$(addprefix obj/,$(notdir $(CPPFILES:.cpp=_cpp.o)))

all: $(COBJ) $(CPPOBJ)
	
	$(CC) $^ -o bin/$(EXEC) $(CLINK)
	
obj/%_c.o: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

obj/%_cpp.o: src/%.cpp
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm obj/*.o;

mrproper: clean
	rm bin/$(EXEC)
