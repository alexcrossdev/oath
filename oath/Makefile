CC := gcc

CFLAGS := -g -Wall -Wextra

TARGET := oath

LIBS := \
	../parser/libparser.a \
	../scanner/libscanner.a \
	../codegen/libcodegen.a	\
	../ast/libast.a

INCLUDES := \
	-I../codegen \
	-I../ast

SRC := main.c

.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -lfl -o $(TARGET) $(INCLUDES)

clean:
	rm -f $(TARGET)
