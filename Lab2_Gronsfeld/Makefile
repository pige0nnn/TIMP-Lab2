TARGET = lab2_gronsfeld
CC = g++
CFLAGS = -Wall -std=c++17

all: $(TARGET)

$(TARGET): main.o modAlphaCipher.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o modAlphaCipher.o

main.o: main.cpp modAlphaCipher.h cipher_error.h
	$(CC) $(CFLAGS) -c main.cpp

modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h cipher_error.h
	$(CC) $(CFLAGS) -c modAlphaCipher.cpp

clean:
	rm -f *.o $(TARGET)
