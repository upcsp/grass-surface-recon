CC = g++

DEBUG =-g
CFLAGS = -Wall -pedantic -pthread -std=c++14 -c $(DEBUG)
LFLAGS = -Wall -pthread $(DEBUG) -L/usr/local/lib
LIBS = $(shell pkg-config --cflags --libs opencv)
OBJDIR = ../obj

EXEC=mov


.DEFAULT_GOAL := $(EXEC)

$(EXEC) : $(OBJDIR)/main.o $(OBJDIR)/funcs.o
	$(CC) $(LFLAGS) $(LIBS) $(OBJDIR)/*.o -o $(EXEC)

$(OBJDIR)/main.o : main.cpp disp.hpp
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/funcs.o : disp.cpp disp.hpp
	$(CC) $(CFLAGS) $< -o $@

