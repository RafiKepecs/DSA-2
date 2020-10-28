dij.exe: dij.o heap.o hash.o
	g++ -o dij.exe dij.o heap.o hash.o

dij.o: dij.cpp dij.h
	g++ -c dij.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp



debug:
	g++ -g -o dij.exe dij.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
