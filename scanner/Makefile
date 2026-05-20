CFLAGS  := -g -Wall -Wextra

TARGET  := scanner

LEX_SRC := scanner.l
LEX_GEN := scanner.c

SRC := $(filter-out $(LEX_GEN),$(wildcard *.c))

OBJ := $(SRC:.c=.o) scanner.o

.PHONY: all clean

all: $(TARGET)

$(LEX_GEN): $(LEX_SRC)
	$(FLEX) -o $@ $<

scanner.o: $(LEX_GEN)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lfl -o $@

clean:
	rm -f $(TARGET) *.o $(LEX_GEN)
