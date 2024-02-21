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


void weirdOp(node root, int h){
    // if leaf node
    if(root->left==NULL && root->right==NULL){
        root->val = h*(root->val);
    }
    // otherwise
    else if (root->left == NULL){
        weirdOp(root->right, h+1);
        root->val = root->right->val - 2*h*(root->val);
    }
    else if (root->right==NULL){
        weirdOp(root->left, h+1);
        root->val = 2*(root->left->val) - 2*h*(root->val);
    }
    else {
        weirdOp(root->left, h+1);
        weirdOp(root->right, h+1);
        root->val = 2*(root->left->val) + root->right->val - 2*h*(root->val);
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
    return 0;
}
