CC=g++
CFLAGS=-std=c++11 -Wall -Wpedantic
LDFLAGS=

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SRCS))
TARGET=edlin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
