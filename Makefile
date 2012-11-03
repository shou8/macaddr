CC=gcc
PWD=$(shell pwd)
PREFIX=/opt/bin

CFLAGS=-Wall -O2
LDLIBS=

OBJS1=macutil.o
SRCS1=$(OBJS1:%.o=%.c)
TARGET1=genCode

OBJS2=genCode
SRCS2=mac.c
TARGET2=mac

OBJS3=macutil.o mac.o macaddr.o
SRCS3=$(OBJS3:%.o=%.c)
TARGET3=macaddr


all: db $(TARGET1) $(TARGET2) $(TARGET3)

db: mac.db
	wget http://standards.ieee.org/develop/regauth/oui/oui.txt
	/bin/bash $(PWD)/genMACdb.sh

$(TARGET1): $(OBJS1)
		$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET1) $(SRCS1) $(LDLIBS)

$(TARGET2): $(OBJS2)
		$(PWD)/genCode
		$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRCS2) $(LDLIBS)

$(TARGET3): $(OBJS3)
		$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET3) $(OBJS3) $(LDLIBS)

install:
		mv $(PWD)/$(TARGET3) $(PREFIX)

clean:
		@rm -f $(OBJS2) $(OBJS3)
