CFLAGS  := -g -Wall -Wextra

MODULE  := codegen
LIBRARY := lib$(MODULE).a

DEPENDS :=

INCLUDES := $(addprefix -I../,$(DEPENDS))

SRC := $(wildcard *.c)

OBJ := $(SRC:.c=.o)

.PHONY: all clean

all: $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBRARY): $(OBJ)
	$(AR) rcs $@ $(OBJ)

clean:
	rm -f *.o *.a

