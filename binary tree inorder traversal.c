/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = malloc(100 * sizeof(int)); // store values
  //  int* result= malloc(100 * sizeof(int));
    struct TreeNode* stack[100]; // store nodes
    int top = -1;
    *returnSize = 0;

    struct TreeNode* current = root;

    while (current != NULL || top != -1) {
        // Go as left as possible
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        // Process the node
        current = stack[top--];
        result[(*returnSize)++] = current->val;

        // Go right
        current = current->right;
    } 

    return result;
}

    
