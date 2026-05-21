CFLAGS  := -g -Wall -Wextra

MODULE  := scanner
LIBRARY := lib$(MODULE).a

DEPENDS := parser

INCLUDES := $(addprefix -I../,$(DEPENDS))

LEX_SRC := scanner.l
LEX_GEN := scanner.c

SRC := $(filter-out $(LEX_GEN),$(wildcard *.c))

OBJ := $(SRC:.c=.o) scanner.o

.PHONY: all clean

all: $(LIBRARY)

$(LEX_GEN): $(LEX_SRC)
	$(FLEX) -o $@ $<

scanner.o: $(LEX_GEN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY): $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -f *.o *.a $(LEX_GEN)
