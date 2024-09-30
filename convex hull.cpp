#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a point in 2D space
struct Point {
    int x, y;
};

// Global variable to store the reference point (bottom-most/left-most point)
struct Point refPoint;

// Function to swap two points
void swap(struct Point *p1, struct Point *p2) {
    struct Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Function to find the next to top in a stack
struct Point nextToTop(struct Point stack[], int size) {
    return stack[size - 2];
}

// Function to calculate the square of the Euclidean distance between two points
int distSq(struct Point p1, struct Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

// Function to compare two points based on polar angle
int compare(const void *vp1, const void *vp2) {
    struct Point *p1 = (struct Point *)vp1;
    struct Point *p2 = (struct Point *)vp2;

    // Find orientation
    int orientation = (p1->y - refPoint.y) * (p2->x - p1->x) -
                      (p1->x - refPoint.x) * (p2->y - p1->y);

    if (orientation == 0)
        return (distSq(refPoint, *p2) >= distSq(refPoint, *p1)) ? -1 : 1;

    return (orientation < 0) ? -1 : 1;
}

// Function to perform the Graham Scan algorithm
void convexHull(struct Point points[], int n) {
    // Find the bottom-most point (and left-most if there are ties)
    int minY = points[0].y;
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < minY) || (y == minY && points[i].x < points[minIdx].x)) {
            minY = points[i].y;
            minIdx = i;
        }
    }

    // Place the bottom-most/left-most point at the beginning of the array
    swap(&points[0], &points[minIdx]);
    refPoint = points[0];

    // Sort the points based on polar angle
    qsort(&points[1], n - 1, sizeof(struct Point), compare);

    // Create an empty stack and push the first three points to it
    struct Point stack[n];
    int stackSize = 0;
    stack[stackSize++] = points[0];
    stack[stackSize++] = points[1];
    stack[stackSize++] = points[2];

    for (int i = 3; i < n; i++) {
        while (stackSize > 1 && ((points[i].x - nextToTop(stack, stackSize).x) * (stack[stackSize - 1].y - nextToTop(stack, stackSize).y) -
                                 (points[i].y - nextToTop(stack, stackSize).y) * (stack[stackSize - 1].x - nextToTop(stack, stackSize).x)) <= 0)
            stackSize--;

        // Add points[i] to the stack
        stack[stackSize++] = points[i];
    }

    // Print points of the convex hull in counter-clockwise order
    printf("Convex Hull points:\n");
    for (int i = 0; i < stackSize; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    struct Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}}; // Example points
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);

    return 0;
}
