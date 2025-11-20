/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * 
 * Reference: based on code-along for Adjacency List Representation of Graph
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "adjList.h"
#include "debug.h"
#include "GraphReader.h"

#define BUFFER_SIZE 255


/**
 * Creates a new adjacency list graph with the given capacity.
 * @param capacity The initial capacity (number of vertices) of the graph.
 * @param directed Whether the graph is directed (true) or undirected (false).
 * @return A pointer to the newly created AdjListGraph.
 */
AdjListGraph* createGraph(int capacity, bool directed) {
    DEBUG_PRINT(DEBUG_INFO, "Creating graph with capacity %d\n", capacity);
    AdjListGraph* graph = (AdjListGraph*)malloc(sizeof(AdjListGraph));
    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed for graph.\n");
        exit(EXIT_FAILURE);
    }
    graph->numVertices = 0;
    graph->capacity = capacity;
    graph->directed = directed;
    graph->adjList = (AdjListNode**)malloc(capacity * sizeof(AdjListNode*));
    if (graph->adjList == NULL) {
        fprintf(stderr, "Memory allocation failed for adjacency list.\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < capacity; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

/**
 * Frees the memory allocated for the adjacency list graph.
 * @param graph A pointer to the AdjListGraph to free.
 */
void freeGraph(AdjListGraph* graph) {
    if (graph == NULL) {
        return;
    }
    for (int i = 0; i < graph->numVertices; i++) {
        AdjListNode* current = graph->adjList[i];
        while (current != NULL) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
}

/**
 * Doubles the capacity of the graph's adjacency list.
 * @param graph A pointer to the AdjListGraph.
 */
void __resizeGraph(AdjListGraph* graph) {
     DEBUG_PRINT(DEBUG_INFO, "Resizing graph from %d to %d\n", graph->capacity, graph->capacity * SCALE_FACTOR);
    int newCapacity = graph->capacity * SCALE_FACTOR;
    AdjListNode** newAdjList = (AdjListNode**)malloc(newCapacity * sizeof(AdjListNode*));
    if (newAdjList == NULL) {
        fprintf(stderr, "Memory allocation failed while doubling capacity.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < newCapacity; i++) {
        newAdjList[i] = NULL;
    }
    for (int i = 0; i < graph->capacity; i++) {
        newAdjList[i] = graph->adjList[i];
    }
    free(graph->adjList);
    graph->adjList = newAdjList;
    graph->capacity = newCapacity;
}

AdjListNode* createNewNode(char* city, int distance) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    // allocate memory for city
    newNode->city = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (newNode->city == NULL) {
        fprintf(stderr, "Memory allocation failed for city.\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->city, city);
    newNode->distance = distance;
    newNode->next = NULL;
    return newNode;
}

int addCityVertex(AdjListGraph* graph, char* city) {
    // check if city exists
    int index = findCityIndex(graph, city);
    if (index > -1) {
        return index;
    }
    
    if (graph->numVertices >= graph->capacity) {
        __resizeGraph(graph);
    }
    
    // Add new city at the next available index
    index = graph->numVertices;
    graph->adjList[index] = createNewNode(city, 0); // for first node (head), distance = 0
    graph->numVertices++;
    DEBUG_PRINT(DEBUG_INFO, "Added city %s at index %d\n", city, index);
    
    return index;
}

/**
 * Adds an edge to the graph from src to dest with the given distance.
 * @param graph A pointer to the AdjListGraph.
 * @param src The source city.
 * @param dest The destination city.
 * @param distance The distance of the edge.
 */
void addEdge(AdjListGraph* graph, char* src, char* dest, int distance) {
    // check if they exists; if not, add
    int srcIndex = addCityVertex(graph, src);
    int destIndex = addCityVertex(graph, dest);

    //check if edge already exists
    AdjListNode* curr = graph->adjList[srcIndex]->next;
    while (curr != NULL) {
        if (strcasecmp(curr->city, dest) == 0) {
            return;
        } 
        curr = curr->next;
    }

    AdjListNode* newNode = createNewNode(dest, distance);
    newNode->next = graph->adjList[srcIndex]->next;
    graph->adjList[srcIndex]->next = newNode;
    
    if (!graph->directed) {
        AdjListNode* reverseNode = createNewNode(src, distance);
        reverseNode->next = graph->adjList[destIndex]->next;
        graph->adjList[destIndex]->next = reverseNode;
    }
}

/**
 * Prints the adjacency list of the graph.
 * Prints in the format of "city: [(neighbor1, distance1), (neighbor2, distance2), ...]"
 * @param graph A pointer to the AdjListGraph.
 */
void printGraph(AdjListGraph* graph) {
    DEBUG_PRINT(DEBUG_INFO
        , "Graph: numVertices %d, capacity: %d, directed: %d\n"
        , graph->numVertices
        , graph->capacity
        , graph->directed
    );
   for(int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        printf("[");
        AdjListNode* current = graph->adjList[i];
        while (current != NULL) {
            printf("(%s, %d)", current->city, current->distance);
            current = current->next;
            if (current != NULL) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

/**
 * Loads a graph from a file.
 * @param graph A pointer to the AdjListGraph.
 * @param filename The name of the file to load from.
 */
void loadFromFile(AdjListGraph* graph, const char* verticesFilename, const char* distanceFilename) {
    // read in all vertices
    GraphReader* verticesReader = reader_open(verticesFilename);
    if (verticesReader == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", verticesFilename);
        return;
    }
    edge_t* line;

    while ((line = reader_next_vertices(verticesReader)) != NULL) {
        addCityVertex(graph, line->src);
    }
    reader_close(verticesReader);

    // read in all distances
    GraphReader* distanceReader = reader_open(distanceFilename);
    if (distanceReader == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", distanceFilename);
        return;
    }
    while ((line = reader_next(distanceReader)) != NULL) {
        char* src = line->src;
        char* dest = line->dest;
        int distance = line->distance;
        addEdge(graph, src, dest, distance);
    }
    reader_close(distanceReader);
}


/**
 * Finds the index for a city name.
 * @param graph A pointer to the AdjListGraph.
 * @param city The name of the city
 */int findCityIndex(AdjListGraph* graph, char* city) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjList[i] != NULL && 
            strcasecmp(graph->adjList[i]->city, city) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Prints the city names from the graph
 * @param graph A pointer to the AdjListGraph.
 */
void printCityVertices(AdjListGraph* graph) {
   for (int i = 0; i < graph->numVertices; i++) {
        printf("%s\n", graph->adjList[i]->city);
    }
}