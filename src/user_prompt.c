/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * 
 * References: 
 * Guessing Game Code Alongs. 
 * whitespace input: https://www.geeksforgeeks.org/c/taking-string-input-space-c-3-different-methods/
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "GraphReader.h"
#include "debug.h"
#include "adjList.h"
#include "dijkstra.h"


#define MAX_INPUT_LIMIT 50


char* getInput() {
    char* str = malloc(MAX_INPUT_LIMIT * sizeof(char));
    scanf("%[^\n]%*c", str);
    
    // TODO: string handling?
    return str;
}

void printHelp() {
    printf("Commands:\n");
    printf("\t\tlist - list all cities\n");
    printf("\t\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\t\thelp - print this help message\n");
    printf("\t\texit - exit the program\n");
}

// TODO documentation
void printCityList(AdjListGraph* graph) {
    printCityVertices(graph);
}

// TODO add documentation
int validateCities(AdjListGraph* graph, char* city1, char* city2) {
    printf("validating cities\n");
    if (findCityIndex(graph, city1) < 0 || findCityIndex(graph, city1) < 0) {
        return -1;
    }
    return 1;

    // confirm cities are in list before proceeding
    // TODO
}

void setUp(char const* verticesFile, char const* distancesFile) {
    // TODO
    return;
}

// TODO
void findShortestPath(AdjListGraph* graph, char* city1, char* city2) {
    if (findCityIndex(graph, city1) != -1 && findCityIndex(graph, city2) != -1) {
        int dist[graph->numVertices];
        int prev[graph->numVertices];
        int srcIndex = findCityIndex(graph, city1);
        int destIndex = findCityIndex(graph, city2);
        dijkstra(graph, srcIndex, dist, prev);
        printPathFound(graph, destIndex, dist, prev, graph->numVertices);
    } else {
        printf("Invalid Command\n");
        printHelp();
    }
    

}

void promptUser(AdjListGraph* graph) {
    // TODO
    printf("Welcome ...\n"); // UPDATE
    printHelp();
    char* menuChoice = NULL;

    while(menuChoice == NULL || strcmp(menuChoice, "exit") != 0) {
        printf("Where do you want to go today? ");
        menuChoice = getInput();

        char* city1 = strtok(menuChoice, " ");
        char* city2 = strtok(NULL, " ");

        if (city1 != NULL && city2 != NULL) {
            findShortestPath(graph, city1, city2);
        } else if (strcasecmp(menuChoice, "list") == 0) {
            printCityList(graph);
        } else if (strcasecmp(menuChoice, "help") == 0) {
            printHelp();
        } else if (strcasecmp(menuChoice, "exit") == 0) {
            printf("Byyyyeeeee!\n");
        } else {
            printf("Invalid Command\n");
            printHelp();
        }
    }
    free(menuChoice);
 
}



/* TODO : update to parse arguments
* The client will provide a list of cities/vertices and a list of distances between cities as a command line argument. 
* `Usage: ./map.out <vertices> <distances>`
*/ 
int main(int argc, char const *argv[]) {
    // if args < 3 then raise error
    // https://www.geeksforgeeks.org/c/error-handling-in-c/
    
    if (argc > 3) {
        set_debug_level(atoi(argv[3]));
    }
    
    if (argc < 3) {
        fprintf(stderr, "Error: Must enter filename for vertices and distances.\n");
        exit(EXIT_FAILURE);
    } else {}


    char const* verticesFile = argv[1];
    char const* distancesFile = argv[2];

    AdjListGraph* graph = createGraph(50, false);
    loadFromFile(graph, verticesFile, distancesFile);
    
    // MOVE ALL THIS TO SET UP function when done
    // read vertices file
    // create graph based on # vertices
    // read distances file
    // add edges based on distances file
    // find shortest path

    promptUser(graph);
    freeGraph(graph);

    return EXIT_SUCCESS;
}





/* EXPECTED OUTPUT


*****Welcome to the shortest path finder!******
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
*******************************************************
Where do you want to go today? what do i do?
Invalid Command
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
Where do you want to go today? list
a
b
c
d
e
f
g
x
Where do you want to go today? a f
Path Found...
        a
        c
        e
        f
Total Distance: 10
Where do you want to go today? f a
Path Found...
        f
        e
        c
        a
Total Distance: 10
Where do you want to go today? a x
Path Not Found...
Where do you want to go today? boston maine
Invalid Command
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
Where do you want to go today? help
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
Where do you want to go today? exit
Goodbye!

*/
