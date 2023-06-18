#include "SymbolTable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int hashFunc(char *s)
{
    unsigned long long result = 0;

    int len = strlen(s);
    if (len > NAME_MAX_LENGTH)
        len = NAME_MAX_LENGTH;
    for (int i = 0; i < len; i++)
    {
        result += s[i];
    }
    result = result % LINKEDLIST_MAX_SIZE;

    return result;
}

Hash *create()
{
    Hash *symbolTable = (Hash *)malloc(sizeof(Hash));
    symbolTable->size = 0;
    for (int i = 0; i < LINKEDLIST_MAX_SIZE; i++)
        symbolTable->entries[i] = NULL;
    return symbolTable;
}

LinkedList *insert(Hash *symbolTable, char *name)
{
    LinkedList *lookupEntry = lookup(symbolTable, name);
    if (lookupEntry)
        return lookupEntry;

    LinkedList *newEntry = (LinkedList *)malloc(sizeof(LinkedList));
    newEntry->next = NULL;
    newEntry->index = symbolTable->size;
    strcpy(newEntry->name, name);

    int hashResult = hashFunc(name);
    if (!symbolTable->entries[hashResult])
    {
        symbolTable->entries[hashResult] = newEntry;
    }
    else
    {
        LinkedList *cur = symbolTable->entries[hashResult];
        while (cur->next)
            cur = cur->next;
        cur->next = newEntry;
    }
    symbolTable->size++;
    return newEntry;
}

LinkedList *lookup(Hash *symbolTable, char *name)
{
    int hashResult = hashFunc(name);
    if (!symbolTable->entries[hashResult])
        return NULL;
    LinkedList *curEntry = symbolTable->entries[hashResult];
    while (curEntry)
    {
        if (strcmp(curEntry->name, name) == 0)
        {
            return curEntry;
        }
        curEntry = curEntry->next;
    }
    return NULL;
}

char *dump(Hash *symbolTable)
{
    char *dumpResult = (char *)malloc(sizeof(char) * NAME_MAX_LENGTH * symbolTable->size);
    for (int i = 0; i < NAME_MAX_LENGTH * symbolTable->size; i++)
    {
        dumpResult[i] = '\0';
    }
    for (int i = 0; i < LINKEDLIST_MAX_SIZE; i++)
    {
        LinkedList *entry = symbolTable->entries[i];
        char *cur = dumpResult;
        while (entry)
        {
            cur = dumpResult + entry->index * NAME_MAX_LENGTH;
            cur[0] = '\0';
            strcpy(cur, entry->name);
            entry = entry->next;
        }
    }
    return dumpResult;
}