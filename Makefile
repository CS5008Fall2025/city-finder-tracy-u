CC = gcc   # This variable is which compiler to use, we will use the variable later by $(CC)
CFLAGS = -Wall  # this variable is command line arguments
CFILES =  src/user_prompt.c src/GraphReader.c src/debug.c src/adjList.c src/dijkstra.c

all: myprogram  #runs target myprogram is nothing is passed into make

myprogram: # it needs to compile out to >>>map.out<<<!
	$(CC) $(CFLAGS) -o map.out $(CFILES)  
	
clean: #this is a clean target, it removes all the .out files, called via > make clean
	rm  *.out