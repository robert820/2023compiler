#ifndef SYMTAB_H
#define SYMTAB_H

#define NAME_MAX_LENGTH 256
#define LINKEDLIST_MAX_SIZE 32

typedef struct LinkedList
{
    char name[NAME_MAX_LENGTH];
    struct LinkedList *next;
    int index;
} LinkedList;

typedef struct Hash
{
    struct LinkedList *entries[LINKEDLIST_MAX_SIZE];
    int size;
} Hash;

Hash *create();
LinkedList *insert(Hash *, char *name);
LinkedList *lookup(Hash *, char *name);

char *dump(Hash *);

#endif