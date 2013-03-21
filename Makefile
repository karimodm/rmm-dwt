CC	=	g++

OBJS	=	ImagenES.o CalculoDWT.o DWT.o
BIN	=	DWT

all:			$(OBJS)
			$(CC) -Wall -o DWT $(OBJS)

clean:
			rm -f $(BIN) $(OBJS)

%.o: %.cpp
			$(CC) -c $(CFLAGS) $< -o $@
