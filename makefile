CC = gcc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lm

SOURCES = my_mastermind.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_mastermind

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core