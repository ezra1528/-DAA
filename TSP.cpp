#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 10

// Function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Function to find the minimum distance from the current city
int tsp(int graph[MAX_CITIES][MAX_CITIES], int cities[], int n, int current, int count, int cost) {
    if (count == n && graph[current][cities[0]] != 0) {
        return cost + graph[current][cities[0]]; // Return back to the starting city
    }

    int minCost = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!cities[i] && graph[current][i] != 0) {
            cities[i] = 1; // Mark as visited
            minCost = min(minCost, tsp(graph, cities, n, i, count + 1, cost + graph[current][i]));
            cities[i] = 0; // Mark as unvisited (backtrack)
        }
    }

    return minCost;
}

int main() {
    int graph[MAX_CITIES][MAX_CITIES] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    int n = 4; // Number of cities
    int cities[MAX_CITIES] = {0}; // Array to keep track of visited cities
    cities[0] = 1; // Starting from city 0

    int minCost = tsp(graph, cities, n, 0, 1, 0); // Start from city 0
    printf("Minimum cost of the TSP tour: %d\n", minCost);

    return 0;
}
