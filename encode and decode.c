#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100000
#define BASE_URL "http://tinyurl.com/"

struct node {
    char key[5000];
    char value[10000];
    struct node *next;
};

struct node *hashtable[TABLE_SIZE];

unsigned int hash(const char *key) {
    unsigned int hashvalue = 0;
    while (*key) {
        hashvalue = (hashvalue * 31) + *key++;
    }
    return hashvalue % TABLE_SIZE;
}

void insert(const char *key, const char *value) {
    unsigned int index = hash(key);
    struct node *newNode = malloc(sizeof(struct node));
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);
    newNode->next = NULL;

    if (hashtable[index] == NULL) {
        hashtable[index] = newNode;
    } else {
        struct node *temp = hashtable[index];
        while (temp->next != NULL) {
            if (strcmp(temp->key, key) == 0) {
                strcpy(temp->value, value);
                free(newNode);
                return;
            }
            temp = temp->next;
        }
        if (strcmp(temp->key, key) == 0) {
            strcpy(temp->value, value);
            free(newNode);
            return;
        }
        temp->next = newNode;
    }
}

char *search(const char *key) {
    unsigned int index = hash(key);
    struct node *temp = hashtable[index];
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

void generateCode(int id, char* code) {
    char map[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int base = 62;
    char temp[10];
    int i = 0;
    while (id > 0) {
