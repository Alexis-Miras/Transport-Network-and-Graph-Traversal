// Auteur : Adam Zekari - Alexis Miras

#ifndef HASH_H
#define HASH_H

#define TABLE_SIZE 1000

struct HashNode {
    char *name;
    int id;
    struct HashNode *next;
};
typedef struct HashNode* HashMap;

void init_hash();
void insert_hash(char *, int);
int search_hash(char *);
void free_hash();
void print_hash();

#endif