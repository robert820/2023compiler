#include "SymbolTable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

int hashFunc(std::string s)
{
    unsigned long long result = 0;

    int len = s.size();
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

LinkedList *insert(Hash *symbolTable, std::string name)
{
    LinkedList *lookupEntry = lookup(symbolTable, name);
    if (lookupEntry)
        return lookupEntry;

    LinkedList *newEntry = (LinkedList *)malloc(sizeof(LinkedList));
    newEntry->next = NULL;
    newEntry->index = symbolTable->size;
    // strcpy(newEntry->name, name);
    newEntry->name = name;

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

LinkedList *lookup(Hash *symbolTable, std::string name)
{
    int hashResult = hashFunc(name);
    if (!symbolTable->entries[hashResult])
        return NULL;
    LinkedList *curEntry = symbolTable->entries[hashResult];
    while (curEntry)
    {
        if (curEntry->name == name)
        {
            return curEntry;
        }
        curEntry = curEntry->next;
    }
    return NULL;
}

std::vector<std::string> dump(Hash *symbolTable)
{
    std::vector<std::string> dumpResult(symbolTable->size);
    for (int i = 0; i < LINKEDLIST_MAX_SIZE; i++)
    {
        LinkedList *entry = symbolTable->entries[i];
        while (entry)
        {
            dumpResult[entry->index] = entry->name;
            entry = entry->next;
        }
    }
    return dumpResult;
}