#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define GAMES 400
#define MAX_GAME_SIZE 15

void init_game(int *nums, int n) {
    for (int i = 0; i < n; i++) {
        nums[i] = (rand() % 50) + 20;
    }
}

void print_state(int *nums, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d%c", nums[i], " \n"[i==n-1]);
    }
}

bool is_finished(int *nums, int n) {
    bool finished = true;
    for (int i = 0; i < n; i++) {
        finished &= nums[i] == 0;
    }
    return finished;
}

void opponent_action(int *nums, int n, int *index, int *num) {
    do {
        *index = rand() % n;
    } while (nums[*index] == 0);
    *num = (rand() % min(3, nums[*index])) + 1;
}

int main(void) {
    int nums[MAX_GAME_SIZE];
    int choice;
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    srand(time(NULL));
    alarm(300);

    puts("Be the last to take a pebble!");

    int remaining_games = GAMES;
    while (remaining_games) {
        puts("Creating a new problem...");
        sleep(1);

        int n = min(MAX_GAME_SIZE, GAMES - remaining_games + 1);
        init_game(nums, n);
        bool won = false;
        while (!is_finished(nums, n)) {
            print_state(nums, n);

            int index;
            if (n == 1) {
                index = 0;
            } else {
                do {
                    printf("Choose a heap [0-%d]: ", n - 1);
                    scanf("%d", &index);
                } while (nums[index] == 0);
            }
            do {
                printf("How many pebbles do you want to take? ");
                if (nums[index] > 1) {
                    printf("[1-%d]: ", min(3, nums[index]));
                } else {
                    printf("[1]: ");
                }
                scanf("%d", &choice);
            } while (choice < 1 || min(3, nums[index]) < choice);
            nums[index] -= choice;
            if (is_finished(nums, n)) {
                won = true;
                break;
            }
            opponent_action(nums, n, &index, &choice);
            printf("The opponent took %d from %d\n", choice, index);
            nums[index] -= choice;
        }
        if (won) {
            remaining_games--;
            puts("Won!");
        } else {
            printf("You lost :(");
        }
        printf("Remaining games: %d\n", remaining_games);
    }

    FILE *fp = fopen("flag", "r");
    char flag[0x40] = {};
    fread(flag, 0x40, 1, fp);
    printf("Congratulations! Here is the flag: %s", flag);

    return 0;
}
