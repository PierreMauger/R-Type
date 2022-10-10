CC = clang++
CFLAGS = -std=c++20

all: clean client server

client:
	$(CC) $(CFLAGS) -o client Client.cpp Connection.cpp testCli.cpp

server:
	$(CC) $(CFLAGS) -o server Server.cpp Connection.cpp testServ.cpp

clean:
	rm -f server client