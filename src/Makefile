CC = gcc   # This variable is which compiler to use, we will use the variable later by $(CC)
CFLAGS = -Wall  # this variable is command line arguments
CFILES =  user_prompt.c GraphReader.c debug.c adjList.c dijkstra.c

# SHARED_SRCS = GraphReader.c debug.c

# USER_PROMPT_TARGET = matrixTest.out
# USER_PROMPT_SRCS = user_prompt.c 

all: map  #runs target myprogram is nothing is passed into make

map: # it needs to compile out to >>>map.out<<<!
	$(CC) $(CFLAGS) -o map.out $(CFILES)  
	

$(ADJ_MATRIX_TARGET): $(ADJ_MATRIX_SRCS)
	$(CC) $(CFLAGS) -o $(ADJ_MATRIX_TARGET) $(ADJ_MATRIX_SRCS) $(SHARED_SRCS)



clean: #this is a clean target, it removes all the .out files, called via > make clean
	rm  *.out