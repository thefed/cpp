CC = g++
CFLAGS = -Wall -g -std=c++11 

SRC = linkedList

all: d

d: $(SRC)
	$(CC) $(CFLAGS) $< -o $@

# valgrind check memory leaks
v:
	valgrind --leak-check=full ./d

clean:
	@rm -f *.o d; rm -rf d.*
