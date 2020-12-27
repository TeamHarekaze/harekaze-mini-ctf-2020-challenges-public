#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NOTES 7
#define MAX_SIZE 0x70

void getnline(char *buf, int size) {
    int len = 0;
    for (int i = 0; i < size-1; i++) {
        len += read(0, buf + i, 1);
        if (buf[i] == '\n') {
            len--;
            break;
        }
    }
    buf[len] = '\0';
}

int getint(void) {
    char buf[0x10];
    getnline(buf, 0x10);

    return atoi(buf);
}

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(-1);
}

int menu(void) {
    puts("1. Alloc");
    puts("2. Show");
    puts("3. Move");
    puts("4. Copy");
    printf("> ");

    return getint();
}

typedef struct {
    char *buf;
    unsigned int size;
} Note;

Note notes[MAX_NOTES];

void alloc(void) {
    printf("Index: ");
    unsigned int index = getint();
    if (index >= MAX_NOTES) {
        error("Invalid index");
    }
    printf("Size: ");
    unsigned int size = getint();
    if (size == 0 || size > MAX_SIZE) {
        error("Invalid size");
    }
    notes[index].buf = malloc(size);
    notes[index].size = size;
    printf("Content: ");
    getnline(notes[index].buf, size);
}

void show(void) {
    printf("Index: ");
    unsigned int index = getint();
    if (index >= MAX_NOTES || notes[index].buf == NULL) {
        error("Invalid index");
    }
    puts(notes[index].buf);
}

void copy(bool delete_src) {
    printf("Index (src): ");
    unsigned int src = getint();
    if (src >= MAX_NOTES || notes[src].buf == NULL) {
        error("Invalid index");
    }

    printf("Index (dest): ");
    unsigned int dest = getint();
    if (dest >= MAX_NOTES) {
        error("Invalid index");
    }

    char *p = NULL;
    if (notes[dest].buf == NULL) {
        p = malloc(notes[src].size);
    } else if (notes[dest].size >= notes[src].size) {
        p = notes[dest].buf;
    } else {
        error("No enough space");
    }
    memcpy(p, notes[src].buf, notes[src].size);

    if (delete_src) {
        free(notes[src].buf);
        notes[src].buf = NULL;
    }
    notes[dest].buf = p;
    notes[dest].size = notes[src].size;
}

int main(void) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    for (;;) {
        switch (menu()) {
            case 1:
                alloc();
                break;
            case 2:
                show();
                break;
            case 3:
                copy(true);
                break;
            case 4:
                copy(false);
                break;
            default:
                puts("Bye");
                exit(0);
        }
    }

    return 0;
}
