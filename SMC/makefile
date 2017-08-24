#
# Author: Pavlo
# Date: 8/23/17
# 

all: SMCreator.exe

SMCreator.exe: SMCreator.o
	gcc -o SMCreator.exe SMCreator.o

SMCreator.o: SMCreator.c
	gcc -c SMCreator.c
	 
clean:
	rm SMCreator.o SMCreator.exe
	 
test: all
	./SMCreator.exe SMCreatorCorrect.txt