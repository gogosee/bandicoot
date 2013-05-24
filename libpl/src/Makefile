

INCLUDE	= -I../include
SRCS	= file.c io.c


TARGET	= libal.so


all:
	gcc ${SRCS} ${INCLUDE} -fPIC -shared -o ${TARGET}

clean:
	rm -rf *.o ${TARGET}
