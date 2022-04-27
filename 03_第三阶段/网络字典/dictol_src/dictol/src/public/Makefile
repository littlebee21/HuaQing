TARGET = dictolpublic
INC=../../inc
LIB=../../lib
CC = gcc
CFLAGS = -fPIC

OBJS= dictolpublic.o  dictolprotocol.o

INCLUDES= -I$(INC)

%.o:%.c
	$(CC) -c $(INCLUDES) $(CFLAGS) $< -o $@

install:$(OBJS)
	$(CC) -fPIC -shared -o lib$(TARGET).so $(OBJS) -L$(LIB) 
	cp lib$(TARGET).so $(LIB)

clean:
	-rm $(OBJS) ./*.so *.o $(LIB)/lib$(TARGET).so -f
