#Ethan Roppel, 41753979
CC=gcc
CFLAGS=-Wall -g
TARGET=SJF_inital

all:	$(TARGET)

$(TARGET):	$(TARGET).c
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(TARGET).c