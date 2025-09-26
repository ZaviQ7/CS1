// Zavier Quintero
// 9/7/2025
// CS1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Holds player info
typedef struct {
    char *playerName;
    int totalScore;
} Player;

// Holds info for one puzzle
typedef struct {
    char *puzzleType;
    int puzzleNo;
    Player **players;
    int *scores;
    int playerCount;
} Puzzle;

// Holds all the puzzles
typedef struct {
    Puzzle *puzzles;
    int puzzleCount;
} Archive;

// Function Prototypes
Player* createPlayer(char *name);
Player** readPlayerPool(int *playerCount);
char** readPuzzleTypes(int *countOut);
Archive* createArchive(int puzzleCount);
char* getPuzzleTypePtr(char **puzzleTypes, int count, char *type);
Player* getPlayerPtrByName(Player **playerPool, int playerCount, char *playerName);
void readPuzzleData(Puzzle* puzzlePtr, char** puzzleTypes, int numPuzzleTypes, Player** playerList, int numPlayers);
void printBestScorer(Puzzle *puzzle);
void printMaxTotalScorer(Player **playerPool, int numPlayers);
void freePlayerPool(Player **pool, int count);
void freePuzzleTypes(char **puzzleTypes, int numPuzzles);
void freeArchive(Archive *archive);

int main() {
    // Variables to hold all our data
    char **puzzleTypes = NULL;
    int puzzleTypeCount = 0;
    Player **playerPool = NULL;
    int playerCount = 0;
    Archive *archive = NULL;
    int archiveSize = 0;

    // Read in the puzzle types
    puzzleTypes = readPuzzleTypes(&puzzleTypeCount);

    // Read in the players
    playerPool = readPlayerPool(&playerCount);

    // Set up the main puzzle archive
    scanf("%d", &archiveSize);
    archive = createArchive(archiveSize);

    // Read the data for each puzzle
    for (int i = 0; i < archiveSize; i++) {
        readPuzzleData(&archive->puzzles[i], puzzleTypes, puzzleTypeCount, playerPool, playerCount);
    }

    // Handle the user's queries
    int numQueries;
    scanf("%d", &numQueries);
    for (int i = 0; i < numQueries; i++) {
        int queryType;
        scanf("%d", &queryType);

        if (queryType == 1) {
            // Find the best overall player
            printMaxTotalScorer(playerPool, playerCount);
        } else if (queryType == 2) {
            // Find the best player for each puzzle
            printf("Top scorer per puzzle:\n");
            for (int j = 0; j < archive->puzzleCount; j++) {
                printBestScorer(&archive->puzzles[j]);
            }
        }
    }

    // Free all the memory we used
    freeArchive(archive);
    freePlayerPool(playerPool, playerCount);
    freePuzzleTypes(puzzleTypes, puzzleTypeCount);

    return 0;
}

// Makes a new player struct
Player* createPlayer(char *name) {
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    newPlayer->playerName = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newPlayer->playerName, name);
    newPlayer->totalScore = 0;
    return newPlayer;
}

// Reads and creates the list of all players
Player** readPlayerPool(int *playerCount) {
    int count;
    scanf("%d", &count);
    *playerCount = count;

    Player **pool = (Player **)malloc(count * sizeof(Player *));
    char buffer[21];

    for (int i = 0; i < count; i++) {
        scanf("%s", buffer);
        pool[i] = createPlayer(buffer);
    }
    return pool;
}

// Reads the names of all puzzle types
char** readPuzzleTypes(int *countOut) {
    int count;
    scanf("%d", &count);
    *countOut = count;

    char **types = (char **)malloc(count * sizeof(char *));
    char buffer[21];

    for (int i = 0; i < count; i++) {
        scanf("%s", buffer);
        types[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(types[i], buffer);
    }
    return types;
}

// Creates the main archive to hold all puzzles
Archive* createArchive(int puzzleCount) {
    Archive *newArchive = (Archive *)malloc(sizeof(Archive));
    newArchive->puzzleCount = puzzleCount;
    newArchive->puzzles = (Puzzle *)malloc(puzzleCount * sizeof(Puzzle));
    return newArchive;
}

// Finds a puzzle type in our list
char* getPuzzleTypePtr(char **puzzleTypes, int count, char *type) {
    for (int i = 0; i < count; i++) {
        if (strcmp(puzzleTypes[i], type) == 0) {
            return puzzleTypes[i];
        }
    }
    return NULL;
}

// Finds a player in our list by name
Player* getPlayerPtrByName(Player **playerPool, int playerCount, char *playerName) {
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(playerPool[i]->playerName, playerName) == 0) {
            return playerPool[i];
        }
    }
    return NULL;
}

// Reads all the data for one puzzle
void readPuzzleData(Puzzle* puzzlePtr, char** puzzleTypes, int numPuzzleTypes, Player** playerList, int numPlayers) {
    char typeBuffer[21];
    int id;
    int numPlayersInPuzzle;
    scanf("%s %d %d", typeBuffer, &id, &numPlayersInPuzzle);

    puzzlePtr->puzzleType = getPuzzleTypePtr(puzzleTypes, numPuzzleTypes, typeBuffer);
    puzzlePtr->puzzleNo = id;
    puzzlePtr->playerCount = numPlayersInPuzzle;

    // If anyone played, get their info
    if (numPlayersInPuzzle > 0) {
        puzzlePtr->players = (Player **)malloc(numPlayersInPuzzle * sizeof(Player *));
        puzzlePtr->scores = (int *)malloc(numPlayersInPuzzle * sizeof(int));

        // Read each player's name and score
        for (int j = 0; j < numPlayersInPuzzle; j++) {
            char nameBuffer[21];
            int score;
            scanf("%s %d", nameBuffer, &score);

            // Link this puzzle back to the main player list
            Player *playerPtr = getPlayerPtrByName(playerList, numPlayers, nameBuffer);
            puzzlePtr->players[j] = playerPtr;
            puzzlePtr->scores[j] = score;

            // Update the player's total score
            if (playerPtr != NULL) {
                playerPtr->totalScore += score;
            }
        }
    } else {
        // No players, nothing to do here
        puzzlePtr->players = NULL;
        puzzlePtr->scores = NULL;
    }
}

// Prints the top scorer for a single puzzle
void printBestScorer(Puzzle *puzzle) {
    // Check if anyone even played
    if (puzzle->playerCount == 0) {
        printf("%s#%d No player yet for this puzzle\n", puzzle->puzzleType, puzzle->puzzleNo);
        return;
    }

    int maxScore = -1;
    Player *bestPlayer = NULL;

    // Find the highest score
    for (int i = 0; i < puzzle->playerCount; i++) {
        if (puzzle->scores[i] > maxScore) {
            maxScore = puzzle->scores[i];
            bestPlayer = puzzle->players[i];
        }
    }

    if (bestPlayer != NULL) {
        printf("%s#%d %s %d\n", puzzle->puzzleType, puzzle->puzzleNo, bestPlayer->playerName, maxScore);
    }
}

// Prints the player with the highest total score
void printMaxTotalScorer(Player **playerPool, int numPlayers) {
    if (numPlayers == 0) {
        return;
    }

    // Start by assuming the first player is the best
    Player *topPlayer = playerPool[0];
    int maxTotalScore = topPlayer->totalScore;

    // Check if anyone else has a higher score
    for (int i = 1; i < numPlayers; i++) {
        if (playerPool[i]->totalScore > maxTotalScore) {
            maxTotalScore = playerPool[i]->totalScore;
            topPlayer = playerPool[i];
        }
    }
    printf("Top player: %s with total score %d\n", topPlayer->playerName, topPlayer->totalScore);
}

// Frees the player list
void freePlayerPool(Player **pool, int count) {
    if (pool == NULL) return;
    for (int i = 0; i < count; i++) {
        free(pool[i]->playerName);
        free(pool[i]);
    }
    free(pool);
}

// Frees the puzzle type list
void freePuzzleTypes(char **puzzleTypes, int numPuzzles) {
    if (puzzleTypes == NULL) return;
    for (int i = 0; i < numPuzzles; i++) {
        free(puzzleTypes[i]);
    }
    free(puzzleTypes);
}

// Frees the main archive
void freeArchive(Archive *archive) {
    if (archive == NULL) return;
    // Free the lists inside each puzzle first
    for (int i = 0; i < archive->puzzleCount; i++) {
        free(archive->puzzles[i].players);
        free(archive->puzzles[i].scores);
    }
    // Then free the main puzzle list and the archive itself
    free(archive->puzzles);
    free(archive);
}