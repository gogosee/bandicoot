CC	= g++


FILECPP := main.cpp
FILEOBJ := $(subst .cpp,.o,${FILECPP})


TARGET = factory_method
all: ${TARGET}


${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 


${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  

clean:
	@-$(RM) ${TARGET} singleton2 *.o core	
