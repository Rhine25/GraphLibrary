CC=gcc
CFLAGS=-g -Wall -c -static -L./include -lgraf
CLINK=

EXEC=graf

CFILES:=$(wildcard src/*.c)
COBJ:=$(addprefix obj/,$(notdir $(CFILES:.c=_c.o)))
COBJLIB:= obj/libliste_c.o obj/libgraphe_c.o
CLIBS:=$(wildcard include/libgraf.a)

all: $(COBJ) include/libgraf.a
	$(CC) $^ -o bin/$(EXEC) $(CLIBS) $(CLINK)

obj/%_c.o: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

include/libgraf.a: $(COBJLIB)
	ar -cq $@ $^

clean:
	rm obj/*.o;

cleanlibs:
	rm include/*.a

mrproper: clean cleanlibs
	rm bin/$(EXEC)
