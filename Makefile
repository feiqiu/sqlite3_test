CC		=$(ARCH)gcc
AR		=$(ARCH)ar
RANLIB	=$(ARCH)ranlib

all:libsqlite.a sqlite test

libsqlite.a:sqlite3.o
	$(AR) -r $@ $^

sqlite3.o:sqlite3.c

sqlite:shell.o sqlite3.o
	$(CC) -o $@ $^ -lpthread -ldl

shell.o:shell.c

lxt_db.o:lxt_db.c  lxt_check.h lxt_comm.h lxt_log.h

lxt_log.o:lxt_log.c  lxt_check.h lxt_comm.h lxt_log.h

main.o:main.c  lxt_check.h lxt_comm.h lxt_log.h

test:lxt_db.o lxt_log.o sqlite3.o main.o lxt_check.h lxt_comm.h lxt_log.h
	$(CC) -o $@ $^ -lpthread -ldl
	
install:libsqlite.a 
	$(RANLIB) $^

clean:
	rm *.o *.a -rf sqlite
