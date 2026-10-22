TARGET = lab2_route
CC = g++
CFLAGS = -Wall -std=c++17

all: $(TARGET)

$(TARGET): main.o RouteCipher.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o RouteCipher.o

main.o: main.cpp RouteCipher.h cipher_error.h
	$(CC) $(CFLAGS) -c main.cpp

RouteCipher.o: RouteCipher.cpp RouteCipher.h cipher_error.h
	$(CC) $(CFLAGS) -c RouteCipher.cpp

clean:
	rm -f *.o $(TARGET)
