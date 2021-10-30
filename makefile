
CC = g++


TARGET = scheduler

$(TARGET): main.cpp scheduler.cpp process.h
		$(CC) -o $(TARGET) main.cpp scheduler.cpp
main.o: main.cpp process.h
		$(CC) -I. -c main.cpp
