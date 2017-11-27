#BenC make file
CC := g++
CFLAGS := 
TARGET := a.out

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp /src/*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
	make clean
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf *.o
	
.PHONY: all clean
