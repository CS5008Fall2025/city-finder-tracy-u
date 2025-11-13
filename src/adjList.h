/**
 * Reference: based on code-along, updated. 
* Solution Code for Adjacency List Representation of Graph Code Along
* @author Albert Lionelle
* @date 2025-05-20
**/



#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node_t {
    char* vertex; //city
    int distance;
    struct node_t* next;
} AdjListNode;

typedef struct {
    int numVertices;
    int capacity;
    AdjListNode** adjList;
    bool directed;
} AdjListGraph;

#define SCALE_FACTOR 2


AdjListGraph* createGraph(int capacity, bool directed); 
void freeGraph(AdjListGraph* graph);

void addEdge(AdjListGraph* graph, char* src, char dest, int distance);
int getDegree(AdjListGraph* graph, char* vertex);
int* getNeighbors(AdjListGraph* graph, char* vertex);
int getDistance(AdjListGraph* graph, char* src, char* dest);
void printGraph(AdjListGraph* graph);
void loadFromFile(AdjListGraph* graph, const char* filename);




#endif /* ADJ_LIST_H */