CC=gcc
CFLAGS=-g -Wall -c -D_DEBUG

EXEC=graf

CFILES:=$(wildcard src/*.c)
CPPFILES:=$(wildcard src/*.cpp)
COBJ:=$(addprefix obj/,$(notdir $(CFILES:.c=_c.o)))
CLIBS:=$(wildcard include/*.a)

all: $(COBJ) $(CLIBS)
	$(CC) $^ -o bin/$(EXEC) $(CLIBS)
	
obj/%_c.o: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

include/lib.a: obj/libliste_c.o obj/libgraphe_c.o
	ar -cq include/lib.a obj/libliste_c.o obj/libgraphe_c.o

clean:
	rm obj/*.o;

mrproper: clean
	rm bin/$(EXEC)
	rm $(CLIBS)
