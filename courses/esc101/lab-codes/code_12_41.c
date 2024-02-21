// To makeroot a node in a BST
// Assume given value is guaranteed to be in the

#include <stdio.h>
#include <stdlib.h>

struct tree_node{
    struct tree_node* left;
    struct tree_node* right;
    int val;
};

typedef struct tree_node* node;

node makeNode(int value){
    node root;
    root = (node)malloc(sizeof(struct tree_node));
    root->left = NULL;
    root->right = NULL;
    root->val = value;
    return root;
}

/* A function to insert a new node with given value in BST */
node insertNode(node nde, int value) 
{ 
    if (nde == NULL) return makeNode(value); 
    if (value < nde->val) 
        nde->left  = insertNode(nde->left, value); 
    else
        nde->right = insertNode(nde->right, value); 
    return nde; 
} 


int weirdOp(node root, int d){
    int left_num, right_num;
    // if leaf node
    if(root->left==NULL && root->right==NULL){
        root->val = d*(root->val);
        return 1;
    }
    // otherwise
    else if (root->left == NULL){
        right_num = weirdOp(root->right, d+1);
        root->val = (right_num+1)*(root->val) - right_num*(root->right->val);
        return right_num+1;
    }
    else if (root->right==NULL){
        left_num = weirdOp(root->left, d+1);
        root->val = (left_num+1)*(root->val) - left_num*(root->left->val);
        return left_num+1;
    }
    else {
        left_num = weirdOp(root->left, d+1);
        right_num = weirdOp(root->right, d+1);
        root->val = (left_num+right_num+1)*(root->val) - (left_num)*(root->left->val) - right_num*(root->right->val) ;
        return left_num + right_num + 1;
    }
}

void preOrder(node root){
    if (root == NULL)
        return;
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}


int main(){
    int i, n, val;
    scanf("%d", &n);
    node root = NULL;
    for (i=0; i<n; i++){
        scanf("%d", &val);
        root = insertNode(root, val);
    }
    preOrder(root);
    printf("\n");
    weirdOp(root, 0);
    preOrder(root);
    // printf("%d", root->val);
    return 0;
}
