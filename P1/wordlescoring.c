// Zavier Quintero
// 8/21/2025
// Calculates word scores based on the frequency of letters

#include <stdio.h>

// Set up constants for the program's limits.
#define MAX_WORDS 1000
#define WORD_LEN 5
#define ALPHABET_SIZE 26

// Function Prototypes
void calculate_letter_frequencies(int n, char words[MAX_WORDS][WORD_LEN + 1], int letter_counts[ALPHABET_SIZE]);
int calculate_word_score(char word[], int letter_counts[ALPHABET_SIZE]);
void print_word_scores(int n, char words[MAX_WORDS][WORD_LEN + 1], int letter_counts[ALPHABET_SIZE]);


int main() {

    // n stores the number of words.
    int n;

    // A 2D array to hold all the words.
    char words[MAX_WORDS][WORD_LEN + 1];

    // Stores the frequency of each letter, initialized to 0.
    int letter_counts[ALPHABET_SIZE] = {0};

    // Read in the number of words.
    scanf("%d", &n);

    // Read in each word into the array.
    for (int i = 0; i < n; i++)
    {
        scanf("%s", words[i]);
    }

    // Populate the letter frequency counts.
    calculate_letter_frequencies(n, words, letter_counts);

    // Print each word with its calculated score.
    print_word_scores(n, words, letter_counts);

    return 0;
}

// Counts the total frequency of each letter across all words.
void calculate_letter_frequencies(int n, char words[MAX_WORDS][WORD_LEN + 1], int letter_counts[ALPHABET_SIZE]) {

    // Loop through each word.
    for (int i = 0; i < n; i++)
    {
        // Loop through each character of the current word.
        for (int j = 0; j < WORD_LEN; j++)
        {
            char current_char = words[i][j];
            // Increment the count for the current letter.
            letter_counts[current_char - 'a']++;
        }
    }
}

// Calculates the score for a single word based on letter frequencies.
int calculate_word_score(char word[], int letter_counts[ALPHABET_SIZE]) {

    int score = 0;

    // Loop through the characters of the word.
    for (int i = 0; i < WORD_LEN; i++)
    {
        char current_char = word[i];
        // Add the frequency of the current letter to the total score.
        score += letter_counts[current_char - 'a'];
    }

    return score;
}

// Prints the score for each word in the list.
void print_word_scores(int n, char words[MAX_WORDS][WORD_LEN + 1], int letter_counts[ALPHABET_SIZE]) {

    // Loop through each word.
    for (int i = 0; i < n; i++)
    {
        // Get the score for the current word.
        int score = calculate_word_score(words[i], letter_counts);
        // Print the word and its corresponding score.
        printf("%s %d\n", words[i], score);
    }
}