#include <stdio.h>
#include <string.h>

// Function to perform string matching using brute force
int stringMatch(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) // If pattern is found
            return i;
    }
    return -1; // Pattern not found
}

int main() {
    char text[] = "AABAACAADAABAABA";
    char pattern[] = "AABA";
    
    int index = stringMatch(text, pattern);
    if (index != -1)
        printf("Pattern found at index %d\n", index);
    else
        printf("Pattern not found\n");
    
    return 0;
}
