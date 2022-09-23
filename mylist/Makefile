CXX = gcc
OBJECTS = myls.o
EXEC = myls

${EXEC}: myls.o
	${CXX} ${OBJECTS} -o ${EXEC}

myls.o: myls.c

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC}
