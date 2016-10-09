.PHONY: build clean

CC=g++
HEADERS=-I.
DEBUG=-g -ggdb  
WALL=-Wall -W  
CFLAGS=$(WALL) $(DEBUG)  
L_CC=$(CC) $(CFLAGS) $(HEADERS)     


test:test.o semaphore.o
	$(L_CC) $^ -o $@ -lpthread

%.o:%.cpp 
	$(L_CC) -c $<

clean:
	@-rm *.o 
	@-rm test 
