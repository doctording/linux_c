.PHONY: all clean

CC=gcc
HEADERS=-I.
DEBUG=-g -ggdb
WALL=-Wall -W
CFLAGS=$(WALL) $(DEBUG)
L_CC=$(CC) $(CFLAGS) $(HEADERS)

C_SRC=${wildcard *.c}
C_EXE=$(patsubst %.c, %.exe, $(C_SRC)) #可执行文件

all:$(C_EXE)

$(C_EXE):$(C_SRC)

%.exe:%.c 
	$(L_CC)  $< -o $@ -lpthread

clean:
	@-rm -f *.exe
