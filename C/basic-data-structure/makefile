#获取.c文件
SrcFiles=$(wildcard *.c)
#使用替换函数获取.o文件
ObjFiles=$(patsubst %.c,%.o,$(SrcFiles))
TargetFiles=$(patsubst %.c,%.exe,$(SrcFiles))
CC=gcc
#-I,添加包含路径，此处是头文件，-Wall 使gcc产生尽可能多的警告信息
# CFLAGS= -Wall
CFLAGS=-I ./include -Wall
.PRECIOUS: %.o

all:$(TargetFiles)

%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.exe: %.o
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean

#由于win10没有rm命令,可以使用del, 参数百度
clean:
	del *.exe /q /s
	del *.o /q /s