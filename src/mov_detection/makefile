CC = g++

DEBUG =-g
CFLAGS = -Wall -pedantic -pthread -std=c++14 -c $(DEBUG)
LFLAGS = -Wall -pthread $(DEBUG)
LIBS = $(shell pkg-config --cflags --libs opencv)
OBJDIR = ../obj

EXEC=mov

.DEFAULT_GOAL := $(EXEC)

$(EXEC) : $(OBJDIR)/main.o
	$(CC) $(LFLAGS) $(LIBS) $(OBJDIR)/*.o -o $(EXEC)

$(OBJDIR)/main.o : main.cpp
	$(CC) $(CFLAGS) $< -o $@

