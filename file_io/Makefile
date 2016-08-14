.PHONY: all clean

CC=gcc
OBJ_DIR=./obj
HEADERS=-I.
DEBUG=-g -ggdb
WALL=-Wall -W
CFLAGS=$(WALL) $(DEBUG)
L_CC=$(CC) $(CFLAGS) $(HEADERS)

OBJ_DIR=./obj
C_SRC=${wildcard *.c}
C_OBJ=$(patsubst %.c, $(OBJ_DIR)/%.o, $(C_SRC)) #目标文件
C_EXE=$(patsubst %.c, %.exe, $(C_SRC)) #可执行文件

all:prepare $(C_EXE)

prepare:
	@if [ ! -d $(OBJ_DIR)  ];then mkdir $(OBJ_DIR); fi

# 下面这句不能省略，否则obj文件会被删除 
$(C_EXE):$(C_OBJ)

%.exe:$(OBJ_DIR)/%.o 
	$(L_CC)  $< -o $@

$(OBJ_DIR)/%.o:%.c 
	$(L_CC) -c $< -o $@

clean:
	@-rm -f *.exe
	@-rm -rf $(OBJ_DIR)
