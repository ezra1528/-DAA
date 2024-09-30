#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// A Huffman tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// A Min Heap
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};

// Function to create a new Min Heap node
struct MinHeapNode *newNode(char data, unsigned freq) {
    struct MinHeapNode *temp = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Function to create a Min Heap
struct MinHeap *createMinHeap(unsigned capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// Function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Standard minHeapify function
void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap *minHeap) {
    return (minHeap->size == 1);
}

// Function to extract minimum value node from heap
struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
    struct MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// Function to insert a new node to Min Heap
void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Function to build a Huffman Tree
struct MinHeapNode *buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;

    // Create a min heap and inserts all characters of data[]
    struct MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, newNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {
        // Extract two minimum freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Create a new internal node with these two nodes as children and
        // with a frequency equal to the sum of the two nodes' frequencies.
        // Add the new node to the min heap.
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    // The remaining node is the root node and the tree is complete
    return extractMin(minHeap);
}

// Function to print Huffman codes from the root of Huffman Tree
void printCodes(struct MinHeapNode *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, print the character and its code from arr[]
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Function to perform Huffman coding
void HuffmanCodes(char data[], int freq[], int size) {
    // Construct Huffman Tree
    struct MinHeapNode *root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using the Huffman Tree built above
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

// Driver program to test above functions
int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(data) / sizeof(data[0]);

    printf("Huffman codes for the characters are:\n");
    HuffmanCodes(data, freq, size);

    return 0;
}
