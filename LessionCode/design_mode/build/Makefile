CC	= g++


FILECPP := main.cpp	
FILEOBJ := $(subst .cpp,.o,${FILECPP})

FILECPP2 := main2.cpp	
FILEOBJ2 := $(subst .cpp,.o,${FILECPP2})



TARGET = build
TARGET2 = build2

all: ${TARGET} ${TARGET2}


${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 

${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  



${TARGET2}: ${FILEOBJ2}
	${CC} -o $@ ${FILEOBJ2} 

${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  



clean:
	@-$(RM) ${TARGET} ${TARGET2} *.o core	
