#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Player structure
typedef struct {
    char name[50];
    int wins;
    int total_games;
} Player;

// AI personalities (0=Random, 1=Aggressive, 2=Defensive)
typedef struct {
    char name[20];
    int personality;
    int wins;
} AI;

// Game choices
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

// Function prototypes
int get_player_choice();
int get_ai_choice(AI ai);
int determine_winner(int player, int ai);
void display_choice(int choice);
void play_match(Player* player, AI* ai);
void save_leaderboard(Player players[], int num_players);
void load_leaderboard(Player players[], int* num_players);
void display_leaderboard(Player players[], int num_players);
void tournament_bracket(Player* player);

int main() {
    srand(time(NULL));
    Player players[10];
    int num_players = 0;
    
    printf("\n=== ROCK-PAPER-SCISSORS TOURNAMENT ===\n");
    printf("Battle 4 unique AI opponents!\n\n");
    
    // Load existing leaderboard
    load_leaderboard(players, &num_players);
    
    char choice;
    do {
        printf("\n1. Play Tournament\n2. View Leaderboard\n3. Quit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);
        
        switch(choice) {
            case '1':
                printf("\nEnter your name: ");
                scanf("%s", players[num_players].name);
                players[num_players].wins = 0;
                players[num_players].total_games = 0;
                tournament_bracket(&players[num_players]);
                num_players++;
                break;
            case '2':
                display_leaderboard(players, num_players);
                break;
        }
    } while(choice != '3');
    
    save_leaderboard(players, num_players);
    printf("\nThanks for playing!\n");
    return 0;
}

// Get player choice (0=Rock, 1=Paper, 2=Scissors)
int get_player_choice() {
    int choice;
    printf("\nChoose: 0=Rock, 1=Paper, 2=Scissors: ");
    scanf("%d", &choice);
    
    if(choice < 0 || choice > 2) {
        printf("Invalid! Choosing Rock.\n");
        return ROCK;
    }
    return choice;
}

// AI choice based on personality
int get_ai_choice(AI ai) {
    int choice;
    if(ai.personality == 0) { // Random
        choice = rand() % 3;
    } else if(ai.personality == 1) { // Aggressive - favors Rock
        choice = (rand() % 2 == 0) ? ROCK : (rand() % 2 * 2);
    } else { // Defensive - favors Paper/Scissors
        choice = (rand() % 100 < 60) ? PAPER : SCISSORS;
    }
    return choice;
}

// Determine match winner
int determine_winner(int player, int ai) {
    if(player == ai) return 0; // Tie
    if((player == ROCK && ai == SCISSORS) ||
       (player == PAPER && ai == ROCK) ||
       (player == SCISSORS && ai == PAPER)) {
        return 1; // Player wins
    }
    return -1; // AI wins
}

// Display choice name
void display_choice(int choice) {
    switch(choice) {
        case ROCK: printf("?? ROCK"); break;
        case PAPER: printf("?? PAPER"); break;
        case SCISSORS: printf("?? SCISSORS"); break;
    }
}

// Play single match
void play_match(Player* player, AI* ai) {
    int player_choice = get_player_choice();
    int ai_choice = get_ai_choice(*ai);
    
    printf("\nYou: ");
    display_choice(player_choice);
    printf("  vs  ");
    display_choice(ai_choice);
    printf(" : %s\n", ai->name);
    
    int result = determine_winner(player_choice, ai_choice);
    player->total_games++;
    
    switch(result) {
        case 1:
            printf("?? YOU WIN!\n");
            player->wins++;
            ai->wins--;
            break;
        case -1:
            printf("?? %s WINS!\n", ai->name);
            ai->wins++;
            break;
        default:
            printf("?? TIE!\n");
    }
}

// Tournament bracket vs 4 AI opponents
void tournament_bracket(Player* player) {
    AI opponents[4] = {
        {"RandoBot", 0, 0},      // Random
        {"Rocko", 1, 0},         // Aggressive
        {"Paperina", 2, 0},      // Defensive
        {"Scissorix", 2, 0}      // Defensive
    };
    
    printf("\n?? TOURNAMENT STARTS!\n");
    printf("Defeat all opponents to become champion!\n\n");
    
    int i;  // declare outside
    for(i = 0; i < 4; i++) {
        printf("\n--- ROUND %d: %s ---\n", i+1, opponents[i].name);
        play_match(player, &opponents[i]);
        
        printf("Your record: %dW-%dL\n", player->wins, player->total_games - player->wins);
        
        // Increasing difficulty
        if(i == 2) {
            printf("?? FINAL BOSS!\n");
            opponents[3].personality = 1; // Makes final boss aggressive
        }
    }
    
    printf("\n?? TOURNAMENT COMPLETE!\n");
    printf("%s's Final Score: %d/%d (%.1f%% win rate)\n", 
           player->name, player->wins, player->total_games,
           (float)player->wins/player->total_games*100);
}

// Save leaderboard to file
void save_leaderboard(Player players[], int num_players) {
    FILE* file = fopen("leaderboard.txt", "w");
    if(file) {
        fprintf(file, "%d\n", num_players);
        int i;
        for(i = 0; i < num_players; i++) {
            fprintf(file, "%s %d %d\n", players[i].name, players[i].wins, players[i].total_games);
        }
        fclose(file);
    }
}

// Load leaderboard from file
void load_leaderboard(Player players[], int* num_players) {
    FILE* file = fopen("leaderboard.txt", "r");
    if(file) {
        fscanf(file, "%d", num_players);
        int i;
        for(i = 0; i < *num_players; i++) {
            fscanf(file, "%s %d %d", players[i].name, &players[i].wins, &players[i].total_games);
        }
        fclose(file);
    }
}

// Display top players
void display_leaderboard(Player players[], int num_players) {
    printf("\n?? LEADERBOARD ??\n");
    printf("Name           Wins  Win%%\n");
    printf("--------------------------------\n");
    
    int i, j;
    // Simple bubble sort by win percentage
    for(i = 0; i < num_players-1; i++) {
        for(j = 0; j < num_players-i-1; j++) {
            float pct1 = players[j].total_games ? 
                (float)players[j].wins/players[j].total_games*100 : 0;
            float pct2 = players[j+1].total_games ? 
                (float)players[j+1].wins/players[j+1].total_games*100 : 0;
            if(pct1 < pct2) {
                Player temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }
    
    for(i = 0; i < num_players; i++) {
        float pct = players[i].total_games ? 
            (float)players[i].wins/players[i].total_games*100 : 0;
        printf("%-14s %2d    %5.1f%%\n", players[i].name, 
               players[i].wins, pct);
    }
}
