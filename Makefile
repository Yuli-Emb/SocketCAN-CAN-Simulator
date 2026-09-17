CC := gcc
CFLAGS := -std=gnu11 -Wall -Wextra -g
SRCS := main.c can_socket.c frame_gen.c logger.c update.c
OBJS := $(SRCS:.c=.o)
TARGET := can_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean