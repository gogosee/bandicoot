CC	= g++


FILECPP := main.cpp
FILEOBJ := $(subst .cpp,.o,${FILECPP})


TARGET = prototype
all: ${TARGET}


${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 


${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  

clean:
	@-$(RM) ${TARGET} *.o core	
