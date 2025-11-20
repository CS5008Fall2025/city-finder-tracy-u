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

// TODO add documentation
//
// edge_t *creat_node(int v, int weight) {
//     edge_t *new_node = (edge_t *)malloc(sizeof(edge_t));
//     new_node->vertex = v;
//     new_node->weight = weight;
//     new_node->next = NULL;
//     return new_node;
// }
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
    // TODO: update, or handled by initial validation
    // if (src < 0  ||  dest < 0 ) {
    //     fprintf(stderr, "city index out of bounds.\n");
    //     return;
    // }

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
    
    // TODO
    if (!graph->directed) {
        // DEBUG_PRINT(DEBUG_INFO, "Adding reverse");
        AdjListNode* reverseNode = createNewNode(src, distance);
        reverseNode->next = graph->adjList[destIndex]->next;
        graph->adjList[destIndex]->next = reverseNode;
    }
}

// /**
//  * Gets the degree (number of neighbors) of a city.
//  * @param graph A pointer to the AdjListGraph.
//  * @param city The city to get the degree of.
//  * @return The degree of the city.  -1 if not found.
//  */
// int getDegree(AdjListGraph* graph, char* city) {
//     // TODO: update, or handled by initial validation
//     // if (city < 0 || city >= graph->numVertices) {
//     //     fprintf(stderr, "city index out of bounds.\n");
//     //     return -1;
//     // }

//     int index = findCityIndex(graph, city);
//     if (index < 0) {
//         fprintf(stderr, "City %s not found.\n", city);
//         return -1;
//     }
//     int degree = 0;
//     //AdjListNode* current = graph->adjList[city];
//     // start with next b/c first node is self-referential
//     AdjListNode* current = graph->adjList[index]->next;
//     while (current != NULL) {
//         degree++;
//         current = current->next;
//     }
//     return degree;
// }

/**
 * Gets the neighbors of a city.
 * @param graph A pointer to the AdjListGraph.
 * @param city The city to get neighbors for.
 * @return A pointer to an array of neighbor city names (caller must free).
 */
// char* getNeighbors(AdjListGraph* graph, char* city) {
//     // TODO: update, or handled by initial validation

//     // if (city < 0 || city >= graph->numVertices) {
//     //     fprintf(stderr, "city index out of bounds.\n");
//     //     return NULL;
//     // }

//     int index = findCityIndex(graph, city);
//     if (index < 0) {
//         fprintf(stderr, "City %s not found.\n", city);
//         return NULL;
//     }
//     int degree = getDegree(graph, city);
//     // TODO -- update this and signature to nodes??
//     char* neighbors = (char*)malloc(degree * BUFFER_SIZE * sizeof(char));
//     if (neighbors == NULL) {
//         fprintf(stderr, "Memory allocation failed for neighbors array.\n");
//         return NULL;
//     }
//     //AdjListNode* current = graph->adjList[city];
//     AdjListNode* current = graph->adjList[index]->next;
//     for (int i = 0; i < degree; i++) {
//         if (current != NULL) {
//             neighbors[i] = *current->city;
//             current = current->next;
//         }
//     }
//     return neighbors;
// }

// /**
//  * Gets the distance of the edge from src to dest.
//  * @param graph A pointer to the AdjListGraph.
//  * @param src The source city.
//  * @param dest The destination city.
//  * @return The distance of the edge, or 0 if no edge exists.
//  */
// int getDistance(AdjListGraph* graph, char* src, char* dest) {
//     // TODO: update, or handled by initial validation
//     // if (src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
//     //     fprintf(stderr, "city index out of bounds.\n");
//     //     return 0;
//     // }
    
//     // find src
//     AdjListNode* current = findNode(graph, src);
//     while (current != NULL) {
//         if (current->city == dest) {
//             return current->distance;
//         }
//         current = current->next;
//     }
//     return 0; // No edge exists
// }

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
        // DEBUG_PRINT(DEBUG_INFO, "Adding city vertex %s\n", line->src);
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
        // DEBUG_PRINT(DEBUG_INFO, "Adding edge from %s to %s with distance %d\n", src, dest, distance);
        addEdge(graph, src, dest, distance);
    }
    reader_close(distanceReader);
}


// TODO add documentation
int findCityIndex(AdjListGraph* graph, char* city) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjList[i] != NULL && 
            strcasecmp(graph->adjList[i]->city, city) == 0) {
            return i;
        }
    }
    return -1;
}

// /**
//  * Finds a node based on the city name
//  * @param graph A pointer to the AdjListGraph.
//  * @param city The name of city
//  * @return the node with this city name if found; otherwise NULL
//  */
// AdjListNode* findNode(AdjListGraph* graph, char* city) {
//     DEBUG_PRINT(DEBUG_INFO, "Finding node for %s\n", city);
//     int index = findCityIndex(graph, city);
//     if (index == -1) {
//         return NULL;
//     }
//     DEBUG_PRINT(DEBUG_INFO, "City found %s\n", city);
//     return graph->adjList[index];
// }

// TODO add documentation
void printCityVertices(AdjListGraph* graph) {
   for (int i = 0; i < graph->numVertices; i++) {
        printf("%s\n", graph->adjList[i]->city);
    }
}