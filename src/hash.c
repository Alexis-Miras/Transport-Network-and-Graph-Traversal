#include "../include/hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


HashMap hash_table[TABLE_SIZE];

void init_hash(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

static unsigned int hash(char *str) {
    unsigned int h = 0;
    while (*str) {
        h = (h * 31 + *str) % TABLE_SIZE;
        str++;
    }
    return h;
}

void insert_hash(char *name, int id) {
    unsigned int idx = hash(name);
    HashMap node = malloc(sizeof(struct HashNode));
    node->name = strdup(name);
    node->id = id;
    node->next = hash_table[idx];
    hash_table[idx] = node;
}

int search_hash(char *name) {
    unsigned int idx = hash(name);
    HashMap node = hash_table[idx];
    while (node) {
        if (!strcmp(node->name, name)) return node->id;
        node = node->next;
    }
    return -1;
}

void free_hash() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashNode *node = hash_table[i];
        while (node) {
            struct HashNode *tmp = node;
            node = node->next;
            free(tmp->name);
            free(tmp);
        }
    }
}

void print_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashMap node = hash_table[i];
        if (node) {
            printf("Bucket %i:\n", i);
            while (node) {
                printf("  name='%s', id=%i\n", node->name, node->id);
                node = node->next;
            }
        }
    }
}