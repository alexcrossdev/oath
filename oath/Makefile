CC := gcc

CFLAGS := -g -Wall -Wextra

TARGET := oath

LIBS := \
	../parser/libparser.a \
	../scanner/libscanner.a

SRC := main.c

.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -lfl -o $(TARGET)

clean:
	rm -f $(TARGET)
