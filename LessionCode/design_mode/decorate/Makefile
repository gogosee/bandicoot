CC	= g++


FILECPP := main.cpp
FILEOBJ := $(subst .cpp,.o,${FILECPP})

FILECPP2 := main2.cpp
FILEOBJ2 := $(subst .cpp,.o,${FILECPP2})


TARGET = decorate
TARGET2 = decorate2
all: ${TARGET} ${TARGET2}

# 1
${TARGET}: ${FILEOBJ}
	${CC} -o $@ ${FILEOBJ} 

${FILEOBJ}: %.o: ./%.cpp
	${CC} -c ./${FILECPP}  

# 2
${TARGET2}: ${FILEOBJ2}
	${CC} -o $@ ${FILEOBJ2} 

${FILEOBJ2}: %.o: ./%.cpp
	${CC} -c ./${FILECPP2}  



clean:
	@-$(RM) ${TARGET} ${TARGET2} *.o core	
