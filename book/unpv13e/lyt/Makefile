include ../Make.defines

PROGS =	01-signal-wait

all:	${PROGS}

dbg:	
	echo${CC} ${CFLAGS} -o $@ xxx ${LIBS}

01-signal-wait:	01-signal-wait.o
		${CC} ${CFLAGS} -o $@ 01-signal-wait.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
