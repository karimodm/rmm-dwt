CC=g++
CFLAGS=-c -Wall
SOURCES=RGBYCbCr.cpp ImagenES.cpp conversor.cpp
OBJS=$(SOURCES:.cpp=.o)
BIN=conversor

all: $(SOURCES) $(BIN)
$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

clean:
		rm -f $(BIN) $(OBJS)

