CFLAGS  := -g -Wall -Wextra

MODULE  := parser
LIBRARY := lib$(MODULE).a

DEPENDS := ast

INCLUDES := $(addprefix -I../,$(DEPENDS))

YACC_SRC := parser.y

YACC_GEN_C := parser.tab.c
YACC_GEN_H := parser.tab.h

SRC := $(filter-out $(YACC_GEN_C),$(wildcard *.c))

OBJ := $(SRC:.c=.o) parser.tab.o

.PHONY: all clean

all: $(LIBRARY)

$(YACC_GEN_C) $(YACC_GEN_H): $(YACC_SRC)
	$(BISON) -d $<

parser.tab.o: $(YACC_GEN_C)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY): $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -f *.o *.a parser.tab.c parser.tab.h
