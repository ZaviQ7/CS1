// Zavier Quintero
// 9/21/2025
// SpellingBee

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Memory management for the dictionary
char** readDictionary(int numWords);
void freeDictionary(char** dictionary, int numWords);

// Sorting and swapping helpers
void sortLetters(char* letters);
void swap(char* a, char* b);

// recursive logic
void findWords(char* letters, int k, int n, char requiredLetter, char** dictionary, int dictSize);

// Validation functions 
void isValidWord(char* word, char requiredLetter, char** dictionary, int dictSize);
int hasRequiredLetter(char* word, char requiredLetter);
int isInDictionary(char* word, char** dictionary, int dictSize);
int binarySearch(char* word, char** dictionary, int low, int high);


int main() {
    char letters[8];
    int numWords;

    // Get the 7 puzzle letters and the number of dictionary words
    scanf("%s", letters);
    scanf("%d", &numWords);

    // The 4th letter is the required one
    char requiredLetter = letters[3];
    char** dictionary = readDictionary(numWords);
    sortLetters(letters);
    findWords(letters, 0, 7, requiredLetter, dictionary, numWords);
    freeDictionary(dictionary, numWords);

    return 0;
}

// Reads all the words from the input and stores them
char** readDictionary(int numWords) {
    char** dictionary = malloc(numWords * sizeof(char*));
    char buffer[10]; 
    for (int i = 0; i < numWords; i++) {
        scanf("%s", buffer);
        dictionary[i] = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(dictionary[i], buffer);
    }
    return dictionary;
}

// Frees all the memory used by the dictionary
void freeDictionary(char** dictionary, int numWords) {
    for (int i = 0; i < numWords; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
}


// Bubble Sort
void sortLetters(char* letters) {
    int n = strlen(letters);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (letters[j] > letters[j + 1]) {
                swap(&letters[j], &letters[j + 1]);
            }
        }
    }
}

// Swap two characters
void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Recursively finds all valid words
void findWords(char* letters, int k, int n, char requiredLetter, char** dictionary, int dictSize) {

    if (k >= 4) {
        char tempWord[k + 1];
        strncpy(tempWord, letters, k);
        tempWord[k] = '\0'; 
        isValidWord(tempWord, requiredLetter, dictionary, dictSize);
    }

    // Base case
    if (k == n) {
        return;
    }

    // Permutation loop
    for (int i = k; i < n; i++) {
        swap(&letters[k], &letters[i]);
        findWords(letters, k + 1, n, requiredLetter, dictionary, dictSize);
        swap(&letters[k], &letters[i]);
    }
}

// Checks if a word is valid 
void isValidWord(char* word, char requiredLetter, char** dictionary, int dictSize) {
    if (hasRequiredLetter(word, requiredLetter) && isInDictionary(word, dictionary, dictSize)) {
        printf("%s\n", word);
    }
}

// Check for special char
int hasRequiredLetter(char* word, char requiredLetter) {
    return strchr(word, requiredLetter) != NULL;
}

// Binary search 
int isInDictionary(char* word, char** dictionary, int dictSize) {
    return binarySearch(word, dictionary, 0, dictSize - 1);
}

// Recursive binary search implementation
int binarySearch(char* word, char** dictionary, int low, int high) {
    if (low > high) {
        return 0; 
    }

    int mid = low + (high - low) / 2;

    int comparison = strcmp(word, dictionary[mid]);

    if (comparison == 0) {
        return 1; 
    } else if (comparison < 0) {
        return binarySearch(word, dictionary, low, mid - 1);
    } else {
        return binarySearch(word, dictionary, mid + 1, high);
    }
}