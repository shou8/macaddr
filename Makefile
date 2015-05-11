CC=gcc
PWD=$(shell pwd)
PREFIX=/opt/bin

CFLAGS=-Wall -O2
LDLIBS=

OBJS1=macutil.o genCode.o
SRCS1=$(OBJS1:%.o=%.c)
TARGET1=genCode

OBJS2=mac.o
SRCS2=mac.c

OBJS3=macutil.o macaddr.o
SRCS3=$(OBJS3:%.o=%.c)
TARGET3=macaddr



.PHONY: all db clean

all: db $(TARGET1) $(TARGET3)

oui.txt:
	wget http://standards.ieee.org/develop/regauth/oui/oui.txt

mac.db: oui.txt
	/bin/bash $(PWD)/genMACdb.sh

$(TARGET1): $(OBJS1)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET1) $(SRCS1) $(LDLIBS)

$(OBJS2): mac.db $(TARGET1)
	$(PWD)/$(TARGET1)
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $(OBJS2) $(SRCS2) $(LDLIBS)

$(TARGET3): $(OBJS2) $(OBJS3)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET3) $(OBJS2) $(OBJS3) $(LDLIBS)

install:
	cp $(PWD)/$(TARGET3) $(PREFIX)

clean:
	@rm -f $(TARGET1) $(TARGET3) $(OBJS1) $(OBJS2) $(OBJS3) oui.txt mac.db

