CC	= g++


FILECPP := main.cpp
FILEOBJ := $(subst .cpp,.o,${FILECPP})


TARGET = bridge
all: ${TARGET}


${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 
	${CC} -o bridge2 main2.cpp


${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  

clean:
	@-$(RM) ${TARGET} *.o core	
