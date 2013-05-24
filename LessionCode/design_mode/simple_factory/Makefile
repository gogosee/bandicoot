CC	= g++


FILECPP := main.cpp
FILEOBJ := $(subst .cpp,.o,${FILECPP})


TARGET = simple_factory
all: ${TARGET}


${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 
	${CC} -o simple_factory2 main2.cpp


${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  

clean:
	@-$(RM) ${TARGET} factory2 *.o core	
