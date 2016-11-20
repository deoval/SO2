CC=gcc -Wall
OUTPUT_BUILD=build
UTILS=utils.h utils.o

all: rm cp touch cat

rm: rm.o $(UTILS)
	$(CC) rm.o utils.o -o $(OUTPUT_BUILD)/rm
	
cp: cp.o $(UTILS)
	$(CC) cp.o utils.o -o $(OUTPUT_BUILD)/cp
	
touch: touch.o $(UTILS)
	$(CC) touch.o utils.o -o $(OUTPUT_BUILD)/touch
	
cat: cat.o $(UTILS)
	$(CC) cat.o utils.o -o $(OUTPUT_BUILD)/cat