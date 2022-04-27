TARGET = dictolclient
INC=../../inc
CLIENT_INC=./inc
LIB=../../lib
CC = gcc

OBJS= cmain.o  view.o queryhistory.o  queryword.o  userlogin.o  userregister.o

INCLUDES=-I$(INC) -I$(CLIENT_INC)
CFLAGS= -g -Wall 
LDFLAGS= -L$(LIB) -ldictolpublic

all:$(TARGET)

%.o:%.c
	$(CC) -c $(INCLUDES) $(CFLAGS) $< -o $@

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	-rm ./$(TARGET) $(OBJS) -f
