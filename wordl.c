#include <stdio.h>
#include <string.h>

// Color codes for feedback (green, yellow, white)
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";

/**
 * Main function where the word-guessing game is implemented.
 * The user has six attempts to guess the word passed in as an argument.
 *
 * @param argc The number of command-line arguments (should be 2: program name and word to guess).
 * @param argv[] Array containing command-line arguments. The second argument is the word to guess.
 */
void main( int argc , char *argv[]) {
    int len = strlen(argv[1]);  // Get the length of the word to guess
    int tries = 0;              // Track the number of attempts
    char try[len+1];            // Buffer for storing the player's guess
    char *wordl = argv[1];      // The word to guess (from command-line argument)
    int done = 0;               // Flag indicating if the game has been completed

    // Loop until the player uses all tries or correctly guesses the word
    while (tries != 6) {
        printf("Enter guess: ");
        scanf("%s", try);       // Read the player's guess
        unsigned int G_count = 0;  // Count for green feedback (correct letter, correct position)
        unsigned int occurance = 0; // Count occurrences of the guessed letter
        int Y_count = 0;        // Count for yellow feedback (correct letter, wrong position)

        // Check if the player's guess is correct
        if (strcmp(try, argv[1]) == 0) {
            printf("%s", GREEN);
            printf("%s\n", try);  
            printf("%s", WHITE); // Reset color to white
            printf("Finished in %d guesses\n", tries + 1);
            ++done;              // Mark the game as finished
            break; 
        }

        // Loop through each character in the guess
        for (int i = 0; i < len; ++i) {
            unsigned int G_count = 0;
            unsigned int occurance = 0;
            int Y_count = 0;    // Reset counters for each character

            // Check for green and yellow conditions
            for (int j = 0; j < len; ++j) {
                if (try[i] == try[j]) {
                    if (try[j] == wordl[j]) {
                        ++G_count;  // Correct letter in the correct position (green)
                    }
                }

                if (try[i] == wordl[j]) {
                    ++occurance;  // Count occurrences of the letter in the word
                }
            }

            Y_count = occurance - G_count;  // Yellow is the difference between occurrence and green

            // Print green for correct position and letter
            if (try[i] == wordl[i]) {
                printf("%s", GREEN);
                printf("%c", try[i]);
                printf("%s", WHITE);
                continue;
            }

            // Handle yellow feedback (correct letter, wrong position)
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k < i; ++k) {
                    if (try[i] == try[j]) {
                        if (try[j] != wordl[j]) { 
                            if (try[j] == wordl[k]) {
                                Y_count = Y_count - 1;  // Adjust yellow count
                            }
                        }
                    }
                }
            }

            // Print yellow if applicable, else print white for incorrect guess
            if (Y_count > 0) {
                printf("%s", YELLOW);
                printf("%c", try[i]);
                printf("%s", WHITE);
            } else {
                printf("%s", WHITE);
                printf("%c", try[i]);
            }
        }

        printf("\n");
        ++tries;                 // Increment the number of attempts
        printf("%s", WHITE);      // Reset color to white
    }

    // If the player failed to guess the word in six tries, reveal the word
    if (done != 1) {
        printf("Failed to guess the word: ");
        printf("%s\n", wordl);
    }
}
