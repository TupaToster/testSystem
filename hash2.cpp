#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// THIS CODE WAS ENTIRELY GENERATED BY CHAT GPT4 AND IT FUCKING WORKS, APART FROM THE CODE, WRITTEN IN Main.cpp, HashTable.cpp and HashTable.h

typedef struct Node {
    char key[100];
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (Node**)calloc(size, sizeof(Node*));
    return ht;
}

unsigned int hash(const char* key, int size) {
    unsigned int hashValue = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hashValue = (hashValue * 31 + key[i]) % size;
    }
    return hashValue;
}

void addElement(HashTable* ht, const char* key, int value) {
    unsigned int index = hash(key, ht->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

int searchElement(HashTable* ht, const char* key) {
    unsigned int index = hash(key, ht->size);
    Node* currentNode = ht->table[index];
    while (currentNode != NULL) {
        if (strcmp(currentNode->key, key) == 0) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }
    return -1;
}

int main() {
    HashTable* ht = createHashTable(10);
    addElement(ht, "apple", 1);
    addElement(ht, "banana", 2);
    addElement(ht, "orange", 3);

    printf("Value of apple: %d\n", searchElement(ht, "apple"));
    printf("Value of banana: %d\n", searchElement(ht, "banana"));
    printf("Value of orange: %d\n", searchElement(ht, "orange"));

    return 0;
}