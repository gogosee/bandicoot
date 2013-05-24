CC	= g++


FILECPP := main.cpp
FILEOBJ := $(subst .cpp,.o,${FILECPP})


FILECPP2 := main2.cpp
FILEOBJ2 := $(subst .cpp,.o,${FILECPP2})


TARGET = iterator
TARGET2 = iterator2
all: ${TARGET} ${TARGET2} 


${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 


${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  




${TARGET2}: ${FILEOBJ2}
	${CC} -o $@ ${FILEOBJ2} 


${FILEOBJ2}: %.o: ./%.cpp
	${CC} -c ./${FILECPP2}  


clean:
	@-$(RM) ${TARGET} ${TARGET2} *.o core	
