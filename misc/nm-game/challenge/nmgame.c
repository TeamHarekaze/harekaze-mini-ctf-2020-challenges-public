#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define GAMES 15

int nums[GAMES];
int heaps;
int heap_indices[GAMES];
int inv_heap_indices[GAMES];

void init_game(int n) {
    heaps = n;
    int grundy;
    do {
        grundy = 0;
        for (int i = 0; i < n; i++) {
            nums[i] = (rand() % 20) + 10;
            grundy ^= nums[i] % 4;
            heap_indices[i] = i;
            inv_heap_indices[i] = i;
        }
    } while (grundy == 0);
}

void print_state(int n) {
    for (int i = 0; i < n; i++) {
        printf("%d%c", nums[i], " \n"[i==n-1]);
    }
}

bool is_finished(int n) {
    bool finished = true;
    for (int i = 0; i < n; i++) {
        finished &= nums[i] == 0;
    }
    return finished;
}

void update_heap_indices(int index) {
    if (nums[index] == 0) {
        heaps--;
        heap_indices[inv_heap_indices[index]] = heap_indices[heaps];
        inv_heap_indices[heap_indices[heaps]] = inv_heap_indices[index];
    }
}

void opponent_action(int *index, int *num) {
    int grundy = 0;
    for (int i = 0; i < heaps; i++) {
        grundy ^= nums[heap_indices[i]] % 4;
    }
    if (grundy == 0) {
        *index = heap_indices[rand() % heaps];
        *num = (rand() % min(3, nums[*index])) + 1;
    } else {
        do {
            *index = heap_indices[rand() % heaps];
            *num = (nums[*index] - (nums[*index] ^ grundy) + 4) % 4;
        } while (nums[*index] - *num < 0);
    }
}

int main(void) {
    int choice;
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    srand(time(NULL));

    puts("Be the last to take a pebble!");

    int remaining_games = GAMES;
    while (remaining_games) {
        puts("Creating a new problem...");

        int n = GAMES - remaining_games + 1;
        init_game(n);
        bool won = false;
        while (!is_finished(n)) {
            print_state(n);

            int index;
            if (n == 1) {
                index = 0;
            } else {
                do {
                    printf("Choose a heap [0-%d]: ", n - 1);
                    scanf("%d", &index);
                } while (index < 0 || n - 1 < index || nums[index] == 0);
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
            update_heap_indices(index);
            if (is_finished(n)) {
                won = true;
                break;
            }
            opponent_action(&index, &choice);
            printf("The opponent took %d from %d\n", choice, index);
            nums[index] -= choice;
            update_heap_indices(index);
        }
        if (won) {
            remaining_games--;
            puts("Won!");
        } else {
            printf("You lost :(");
            exit(0);
        }
        printf("Remaining games: %d\n", remaining_games);
    }

    FILE *fp = fopen("flag", "r");
    char flag[0x40] = {};
    fread(flag, 0x40, 1, fp);
    printf("Congratulations! Here is the flag: %s", flag);

    return 0;
}
