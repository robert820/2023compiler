#ifndef SYMTAB_H
#define SYMTAB_H

#include <vector>
#include <string>

enum
{
    NAME_MAX_LENGTH = 256,
    LINKEDLIST_MAX_SIZE = 32
};

enum class identifier_type
{
    function_i,
    variable_i,
    constant_i
};

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

struct LinkedList
{
    std::string name = std::string(NAME_MAX_LENGTH, '\0');
    struct LinkedList *next;
    int index;
    identifier_type type;
};

struct Hash
{
    struct LinkedList *entries[LINKEDLIST_MAX_SIZE];
    struct Hash *upper_idtab;
    int size;
};

Hash *create();
LinkedList *insert(Hash *, std::string name);
LinkedList *lookup(Hash *, std::string name);

std::vector<std::string> dump(Hash *);

#endif