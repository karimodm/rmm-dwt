CC	=	g++
CXXFLAGS = -g -O0 -Wno-write-strings

OBJS	=	ImagenES.o CalculoDWT.o DWT.o Pixel.o
BIN	=	DWT

$(BIN): $(OBJS)

clean:
			rm -f $(BIN) $(OBJS)

