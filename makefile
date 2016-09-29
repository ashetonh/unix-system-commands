CC = g++
DEBUG = -g -O0 -pedantic-errors
CFLAGS = -Wall -std=c++11 -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: chmod ls cat cp mv mkdir pwd penv ln rm stat kill getuid
chmod: chmod.o
	$(CC) $(LFLAGS) -o chmod chmod.o
chmod.o: chmod.cpp
	$(CC) $(CFLAGS) chmod.cpp

ls: ls.o
	$(CC) $(LFLAGS) -o ls ls.o
ls.o: ls.cpp
	$(CC) $(CFLAGS) ls.cpp

cat: cat.o
	$(CC) $(LFLAGS) -o cat cat.o
cat.o: cat.cpp
	$(CC) $(CFLAGS) cat.cpp

cp: cp.o
	$(CC) $(LFLAGS) -o cp cp.o
cp.o: cp.cpp
	$(CC) $(CFLAGS) cp.cpp

getuid: getuid.o
	$(CC) $(LFLAGS) -o getuid getuid.o
getuid.o: getuid.cpp
	$(CC) $(CFLAGS) getuid.cpp
stat: stat.o
	$(CC) $(LFLAGS) -o stat stat.o
stat.o: stat.cpp
	$(CC) $(CFLAGS) stat.cpp

rm: rm.o
	$(CC) $(LFLAGS) -o rm rm.o
rm.o: rm.cpp
	$(CC) $(CFLAGS) rm.cpp		

ln: ln.o
	$(CC) $(LFLAGS) -o ln ln.o
ln.o: ln.cpp
	$(CC) $(CFLAGS) ln.cpp	

mv: mv.o
	$(CC) $(LFLAGS) -o mv mv.o
mv.o: mv.cpp
	$(CC) $(CFLAGS) mv.cpp

mkdir: mkdir.o
	$(CC) $(LFLAGS) -o mkdir mkdir.o
mkdir.o: mkdir.cpp
	$(CC) $(CFLAGS) mkdir.cpp	

pwd: pwd.o
	$(CC) $(LFLAGS) -o pwd pwd.o
pwd.o: pwd.cpp
	$(CC) $(CFLAGS) pwd.cpp

penv: penv.o
	$(CC) $(LFLAGS) -o penv penv.o
penv.o: penv.cpp
	$(CC) $(CFLAGS) penv.cpp

kill: kill.o
	$(CC) $(LFLAGS) -o kill kill.o
kill.o: kill.cpp
	$(CC) $(CFLAGS) kill.cpp
.PHONY: clean

clean: 
	rm -rf getuid
	rm -rf kill
	rm -rf rm
	rm -rf stat
	rm -rf ln
	rm -rf penv
	rm -rf mkdir
	rm -rf pwd
	rm -rf chmod
	rm -rf cp
	rm -rf mv
	rm -rf ls
	rm -rf cat
	rm -rf *.o