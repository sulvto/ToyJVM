#
# Makefile of ToyJVM
#

CC			= gcc
LD			= ld
SOURCES     = bytecode.c interpreter.c rtda.c classreader.c instruction.c \
                class.c map.c main.c
OBJECTS     = bytecode.o interpreter.o instruction.o \
			    classreader.o rtda.o class.o map.o main.o\

CFLAGS      = -std=c99

.PHONY : clean

everything : $(OBJECTS)
build : clean everything
link :
		$(CC) -o main $(OBJECTS)
clean :
		rm -f $(OBJECTS)

sinclude $(SOURCES:.c=.d)

%.d: %.c
		@echo "Creating $@ ..." \
		@set -e; \
		rm -f $@.$$$$; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
		rm -f $@.$$$$

$(OBJECTS): %.o: %.c
		$(CC) -c $(CFLAGS) $< -o $@
