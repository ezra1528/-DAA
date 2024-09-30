#include <stdio.h>

// Structure to represent each item
struct Item {
    int value;
    int weight;
};

// Function to merge two subarrays of items[]
void merge(struct Item items[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    struct Item L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = items[left + i];
    for (j = 0; j < n2; j++)
        R[j] = items[mid + 1 + j];

    // Merge the temporary arrays back into items[]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if ((double)L[i].value / L[i].weight >= (double)R[j].value / R[j].weight) {
            items[k] = L[i];
            i++;
        } else {
            items[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        items[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        items[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform merge sort on items[]
void mergeSort(struct Item items[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);

        // Merge the sorted halves
        merge(items, left, mid, right);
    }
}

// Function to solve fractional knapsack
double fractionalKnapsack(int capacity, struct Item items[], int n) {
    // Sort items based on value per unit weight using merge sort
    mergeSort(items, 0, n - 1);

    double totalValue = 0.0; // Total value in the knapsack
    int currentWeight = 0; // Current weight in the knapsack

    // Fill the knapsack greedily
    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            // Take the whole item
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take a fraction of the item
            int remainingCapacity = capacity - currentWeight;
            totalValue += items[i].value * ((double)remainingCapacity / items[i].weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    struct Item items[] = {{60, 10}, {100, 20}, {120, 30}}; // Example items
    int capacity = 50; // Knapsack capacity
    int n = sizeof(items) / sizeof(items[0]); // Number of items

    double maxValue = fractionalKnapsack(capacity, items, n);
    printf("Maximum value in the knapsack: %lf\n", maxValue);

    return 0;
}
