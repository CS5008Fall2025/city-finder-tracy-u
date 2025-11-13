/**
 * Reference: based on code-along
* Solution Code for Adjacency List Representation of Graph Code Along
* @author Albert Lionelle
* @date 2025-05-20
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "adjList.h"
#include "debug.h"
#include "GraphReader.h"




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

/**
 * Adds an edge to the graph from src to dest with the given weight.
 * @param graph A pointer to the AdjListGraph.
 * @param src The source vertex.
 * @param dest The destination vertex.
 * @param distance The distance of the edge.
 */
void addEdge(AdjListGraph* graph, int src, int dest, int distance) {
    if (src < 0  ||  dest < 0 ) {
        fprintf(stderr, "Vertex index out of bounds.\n");
        return;
    }
    graph->numVertices = (src >= graph->numVertices) ? src + 1 : graph->numVertices;
    graph->numVertices = (dest >= graph->numVertices) ? dest + 1 : graph->numVertices;

    if (graph->numVertices >= graph->capacity) {
        __resizeGraph(graph);
    }
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = dest;
    newNode->distance = distance;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if (!graph->directed) {
        // Add the edge in the opposite direction for undirected graphs
        AdjListNode* reverseNode = (AdjListNode*)malloc(sizeof(AdjListNode));
        if (reverseNode == NULL) {
            fprintf(stderr, "Memory allocation failed for reverse node.\n");
            exit(EXIT_FAILURE);
        }
        reverseNode->vertex = src;
        reverseNode->distance = distance;
        reverseNode->next = graph->adjList[dest];
        graph->adjList[dest] = reverseNode;
    }
}

/**
 * Gets the degree (number of neighbors) of a vertex.
 * @param graph A pointer to the AdjListGraph.
 * @param vertex The vertex to get the degree of.
 * @return The degree of the vertex.
 */
int getDegree(AdjListGraph* graph, int vertex) {
    if (vertex < 0 || vertex >= graph->numVertices) {
        fprintf(stderr, "Vertex index out of bounds.\n");
        return -1;
    }
    int degree = 0;
    AdjListNode* current = graph->adjList[vertex];
    while (current != NULL) {
        degree++;
        current = current->next;
    }
    return degree;
}

/**
 * Gets the neighbors of a vertex.
 * @param graph A pointer to the AdjListGraph.
 * @param vertex The vertex to get neighbors for.
 * @return A pointer to an array of neighbor vertex indices (caller must free).
 */
int* getNeighbors(AdjListGraph* graph, int vertex) {
    if (vertex < 0 || vertex >= graph->numVertices) {
        fprintf(stderr, "Vertex index out of bounds.\n");
        return NULL;
    }
    int degree = getDegree(graph, vertex);
    int* neighbors = (int*)malloc(degree * sizeof(int));
    if (neighbors == NULL) {
        fprintf(stderr, "Memory allocation failed for neighbors array.\n");
        return NULL;
    }
    AdjListNode* current = graph->adjList[vertex];
    for (int i = 0; i < degree; i++) {
        if (current != NULL) {
            neighbors[i] = current->vertex;
            current = current->next;
        }
    }
    return neighbors;
}

/**
 * Gets the distance of the edge from src to dest.
 * @param graph A pointer to the AdjListGraph.
 * @param src The source vertex.
 * @param dest The destination vertex.
 * @return The distance of the edge, or 0 if no edge exists.
 */
int getDistance(AdjListGraph* graph, int src, int dest) {
    if (src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
        fprintf(stderr, "Vertex index out of bounds.\n");
        return 0;
    }
    AdjListNode* current = graph->adjList[src];
    while (current != NULL) {
        if (current->vertex == dest) {
            return current->distance;
        }
        current = current->next;
    }
    return 0; // No edge exists
}

/**
 * Prints the adjacency list of the graph.
 * Prints in the format of "Vertex: [(neighbor1, weight1), (neighbor2, weight2), ...]"
 * @param graph A pointer to the AdjListGraph.
 */
void printGraph(AdjListGraph* graph) {
   for(int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        printf("[");
        AdjListNode* current = graph->adjList[i];
        while (current != NULL) {
            printf("(%d, %d)", current->vertex, current->distance);
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
void loadFromFile(AdjListGraph* graph, const char* filename) {
    GraphReader* reader = reader_open(filename);
    if (reader == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }

    int* line;
    while ((line = reader_next(reader)) != NULL) {
        char* src = line[0];
        char* dest = line[1];
        int distance = line[2];
        DEBUG_PRINT(DEBUG_INFO, "Adding edge from %s to %s with weight %d\n", src, dest, distance);
        addEdge(graph, src, dest, distance);
    }

    reader_close(reader);
    
}