#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TEAMS 20
#define HALF_SEASON_MATCHDAYS (NUM_TEAMS - 1)
#define TOTAL_MATCHDAYS (HALF_SEASON_MATCHDAYS * 2)
#define MATCHES_PER_DAY (NUM_TEAMS / 2)

// Structure to hold a single match
struct Match {
    char home[50];
    char away[50];
};

// Function to print the calendar for a given set of matchdays
void print_calendar(struct Match schedule[HALF_SEASON_MATCHDAYS][MATCHES_PER_DAY], int start_day) {
    for (int i = 0; i < HALF_SEASON_MATCHDAYS; i++) {
        printf("\n--- Matchday %d ---\n", i + 1 + start_day);
        for (int j = 0; j < MATCHES_PER_DAY; j++) {
            printf("%s vs %s\n", schedule[i][j].home, schedule[i][j].away);
        }
    }
}

int main() {
    const char *initial_teams[NUM_TEAMS] = {
        "Atalanta", "Bologna", "Cagliari", "Como", "Empoli",
        "Fiorentina", "Genoa", "Inter", "Juventus", "Lazio",
        "Lecce", "Milan", "Monza", "Napoli", "Parma",
        "Roma", "Torino", "Udinese", "Venezia", "Verona"
    };

    // Create a mutable list of teams
    char teams[NUM_TEAMS][50];
    for (int i = 0; i < NUM_TEAMS; i++) {
        strcpy(teams[i], initial_teams[i]);
    }

    // Schedule for the first half of the season
    struct Match first_half_schedule[HALF_SEASON_MATCHDAYS][MATCHES_PER_DAY];

    // Generate fixtures for the first half (19 matchdays)
    for (int round = 0; round < HALF_SEASON_MATCHDAYS; round++) {
        for (int i = 0; i < MATCHES_PER_DAY; i++) {
            char *team1 = teams[i];
            char *team2 = teams[NUM_TEAMS - 1 - i];

            // Alternate home/away for the fixed team (teams[0])
            if (round % 2 == 0) {
                 strcpy(first_half_schedule[round][i].home, team1);
                 strcpy(first_half_schedule[round][i].away, team2);
            } else {
                 strcpy(first_half_schedule[round][i].home, team2);
                 strcpy(first_half_schedule[round][i].away, team1);
            }
        }

        // Rotate teams (excluding the first one)
        char last_team[50];
        strcpy(last_team, teams[NUM_TEAMS - 1]);
        for (int j = NUM_TEAMS - 1; j > 1; j--) {
            strcpy(teams[j], teams[j - 1]);
        }
        strcpy(teams[1], last_team);
    }

    // Create schedule for the second half by swapping home and away
    struct Match second_half_schedule[HALF_SEASON_MATCHDAYS][MATCHES_PER_DAY];
    for (int i = 0; i < HALF_SEASON_MATCHDAYS; i++) {
        for (int j = 0; j < MATCHES_PER_DAY; j++) {
            strcpy(second_half_schedule[i][j].home, first_half_schedule[i][j].away);
            strcpy(second_half_schedule[i][j].away, first_half_schedule[i][j].home);
        }
    }

    // Print the full calendar
    printf("--- Serie A Championship Calendar ---\n");
    print_calendar(first_half_schedule, 0);
    print_calendar(second_half_schedule, HALF_SEASON_MATCHDAYS);

    return 0;
}
