TARGET = dictolserver
INC=../../inc
SERVER_INC=./inc
LIB=../../lib
CC = gcc

OBJS= handleclient.o  historyhelper.o  main.o  userhelper.o  wraprunsql.o

INCLUDES=-I$(INC) -I$(SERVER_INC)
CFLAGS= -g -Wall 
LDFLAGS= -L$(LIB) -ldictolpublic -lsqlite3

all:$(TARGET)

%.o:%.c
	$(CC) -c $(INCLUDES) $(CFLAGS) $< -o $@

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	-rm ./$(TARGET) $(OBJS) -f
