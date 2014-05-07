#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    gps
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror
LIBS = -lgps

SOURCES = GPSReader.cpp
HEADERS = GPSReader.h
FILE = GPSReader.o



all : $(FILE)
$(FILE) : $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(FLAGS) $(LIBS) -c -o $(FILE)

example : $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) example.cpp $(FLAGS) $(LIBS) -o example

