CC = g++
CFLAGS = -Wall -g -std=c++11 

#EXT = .cpp
SRC = linkedList
#SRC = combination

all: d

d: $(SRC)$(EXT)
	$(CC) $(CFLAGS) $< -o $@

# valgrind check memory leaks
v:
	valgrind --leak-check=full ./d

clean:
	@rm -f *.o d *.out; rm -rf d.*
