CC	=	g++
LDFLAGS = -g -O0 -Wno-write-strings
CXXFLAGS = -g -O0 -Wno-write-strings

OBJS	=	ImagenES.o CalculoDWT.o DWT.o
BIN	=	DWT

all: $(BIN)

$(BIN): $(OBJS)

clean:
			rm -f $(BIN) $(OBJS)

