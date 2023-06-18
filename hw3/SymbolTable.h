#ifndef SYMTAB_H
#define SYMTAB_H

#define NAME_MAX_LENGTH 256
#define LINKEDLIST_MAX_SIZE 32

typedef enum identifier_type
{
    function_i,
    variable_i,
    constant_i
} identifier_type;

enum SymbolType
{
    sinteger,
    sreal,
    sboolean,
    sstring,
    sarray,
    sfunction,
    sprocedure,
    sunknown,
    none
};

enum TokenType
{
    vint,
    vreal,
    vbool,
    vstring,
    varray,
    idList,
    typeList,
    idType,
    vunknown,
    blank
};

typedef struct LinkedList
{
    char name[NAME_MAX_LENGTH];
    struct LinkedList *next;
    int index;
    identifier_type type;
} LinkedList;

typedef struct Hash
{
    struct LinkedList *entries[LINKEDLIST_MAX_SIZE];
    struct Hash *upper_idtab;
    int size;
} Hash;

Hash *create();
LinkedList *insert(Hash *, char *name);
LinkedList *lookup(Hash *, char *name);

char *dump(Hash *);

#endif