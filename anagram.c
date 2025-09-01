/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1000

typedef struct Node {
    char *key;       // sorted string (ex: "eat" -> "aet")
    char **words;    // list of anagrams
    int count;       // number of words
    int capacity;    // capacity of array
    struct Node *next; 
} Node;

unsigned long hashFunc(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % HASH_SIZE;
}

char* sortString(const char *str) {
    char *sorted = strdup(str);
    int len = strlen(sorted);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (sorted[i] > sorted[j]) {
                char tmp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = tmp;
            }
        }
    }
    return sorted;
}

Node* createNode(const char *key, const char *word) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = strdup(key);
    node->capacity = 4;
    node->count = 0;
    node->words = (char **)malloc(sizeof(char *) * node->capacity);
    node->next = NULL;

    node->words[node->count++] = strdup(word);
    return node;
}

void addWord(Node **table, const char *key, const char *word) {
    unsigned long hash = hashFunc(key);
    Node *cur = table[hash];

    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            if (cur->count >= cur->capacity) {
                cur->capacity *= 2;
                cur->words = (char **)realloc(cur->words, sizeof(char *) * cur->capacity);
            }
            cur->words[cur->count++] = strdup(word);
            return;
        }
        cur = cur->next;
    }

    Node *newNode = createNode(key, word);
    newNode->next = table[hash];
    table[hash] = newNode;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    Node *hashTable[HASH_SIZE] = {0};

    // Insert all words into hashTable
    for (int i = 0; i < strsSize; i++) {
        char *sorted = sortString(strs[i]);
        addWord(hashTable, sorted, strs[i]);
        free(sorted);
    }

    // Count total groups
    int groups = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *cur = hashTable[i];
        while (cur) {
            groups++;
            cur = cur->next;
        }
    }

    *returnSize = groups;
    *returnColumnSizes = (int *)malloc(sizeof(int) * groups);
    char ***result = (char ***)malloc(sizeof(char **) * groups);

    int idx = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *cur = hashTable[i];
        while (cur) {
            (*returnColumnSizes)[idx] = cur->count;
            result[idx] = (char **)malloc(sizeof(char *) * cur->count);
            for (int j = 0; j < cur->count; j++) {
                result[idx][j] = cur->words[j];
            }
            idx++;
            cur = cur->next;
        }
    }

    return result;
}

#ifdef LOCAL_TEST
int main() {
    char *strs[] = {"eat","tea","tan","ate","nat","bat"};
    int strsSize = 6;

    int returnSize;
    int *returnColumnSizes;
    char ***groups = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    printf("Output groups:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("[ ");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%s ", groups[i][j]);
        }
        printf("]\n");
    }

    return 0;
}
#endif
