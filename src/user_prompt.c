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

/**
 * @brief Gets input from the user
 * @return a string
 */
char* getInput() {
    char* str = malloc(MAX_INPUT_LIMIT * sizeof(char));
    scanf("%[^\n]%*c", str);
    return str;
}

/**
 * @brief Prints the help menu of commands
 */
void printHelp() {
    printf("Commands:\n");
    printf("\t\tlist - list all cities\n");
    printf("\t\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\t\thelp - print this help message\n");
    printf("\t\texit - exit the program\n");
}


/**
 * @brief Prints the list of cities
 * @param graph pointer to the AdjListGraph
 */
void printCityList(AdjListGraph* graph) {
    printCityVertices(graph);
}

/**
 * @brief Validates that both cities are in the vertices
 * @param graph pointer to the AdjListGraph
 * @param city1 name of a city
 * @param city2 name of a city
 * @return 1 if true, else 0
 */
int validateCities(AdjListGraph* graph, char* city1, char* city2) {
    if (findCityIndex(graph, city1) != -1 && findCityIndex(graph, city2) != -1) {
        return 1;
    } 
    return 0;
}

/**
 * @brief Gets and prints the shortest path from city1 to city2
 * @param graph pointer to the AdjListGraph
 * @param city1 name of a city
 * @param city2 name of a city
 * @return a string
 */
void findShortestPath(AdjListGraph* graph, char* city1, char* city2) {
    int dist[graph->numVertices];
    int prev[graph->numVertices];
    int srcIndex = findCityIndex(graph, city1);
    int destIndex = findCityIndex(graph, city2);
    dijkstra(graph, srcIndex, dist, prev); // run algo for all from src
    printPathFound(graph, destIndex, dist, prev, graph->numVertices);
}

/**
 * @brief Prompts the user and controls flow
 * @param graph pointer to the AdjListGraph
 */
void promptUser(AdjListGraph* graph) {
    printf("*** Welcome to the Shortest Path City Finder! ***\n"); 
    printHelp();
    char* menuChoice = NULL;

    while(menuChoice == NULL || strcmp(menuChoice, "exit") != 0) {
        printf("Where do you want to go today? ");
        menuChoice = getInput();

        char* city1 = strtok(menuChoice, " ");
        char* city2 = strtok(NULL, " ");

        if (city1 != NULL && city2 != NULL && validateCities(graph, city1, city2) == 1) {
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


int main(int argc, char const *argv[]) {
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

    promptUser(graph);
    freeGraph(graph);

    return EXIT_SUCCESS;
}