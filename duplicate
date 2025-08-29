#define TABLE_SIZE 10000

typedef struct Node{
    int val;
    struct Node* next;
}Node;

int hash(int x){
    return (x % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

bool containsDuplicate(int* nums, int numsSize) {
   Node* table[TABLE_SIZE] = {0};
    for(int i = 0; i < numsSize; i++){
        int idx = hash(nums[i]);
        Node* cur = table[idx];
        while(cur){
            if (cur->val == nums[i]) return true;
            cur = cur->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = nums[i];
        newNode->next = table[idx];
        table[idx] = newNode;
    }
    return false;
}
