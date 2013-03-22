CC	=	g++
LDFLAGS = -g -O0 -Wno-write-strings
CXXFLAGS = -g -O0 -Wno-write-strings

OBJS	=	ImagenES.o CalculoDWT.o DWT.o Pixel.o
BIN	=	DWT

$(BIN): $(OBJS)

clean:
			rm -f $(BIN) $(OBJS)

