// To delete a node from a BST
// Assume given value is guaranteed to be in the tree


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


node successor(node nde){
	node curr = nde->right; 
    while (curr->left != NULL) 
        curr = curr->left; 
    return curr;
}


/* Given a binary search tree and a value, this function deletes the value 
   and returns the new root */
node deleteNode(node root, int value) 
{ 
    if (root == NULL) return root; 
  
    if (value < root->val) 
        root->left = deleteNode(root->left, value); 
    else if (value > root->val) 
        root->right = deleteNode(root->right, value); 
    else
    { 
        if (root->left == NULL) 
        { 
            node temp = root->right; 
            free(root); 
            return temp; 
        } 
        else if (root->right == NULL) 
        { 
            node temp = root->left; 
            free(root); 
            return temp; 
        } 
        node temp = successor(root); 
        root->val = temp->val; 
        root->right = deleteNode(root->right, temp->val); 
    } 
    return root; 
} 

void preOrder(node root){
	if (root == NULL)
		return;
	printf("%d ", root->val);
	preOrder(root->left);
	preOrder(root->right);
}


int main(){
	int i, n, m, val;
	scanf("%d %d", &n, &m);
	node root = NULL;
	for (i=0; i<n; i++){
		scanf("%d", &val);
		root = insertNode(root, val);
	}
	preOrder(root);
	printf("\n");
	for (i=0; i<m; i++){
		scanf("%d", &val);
		root = deleteNode(root, val);
	}
	preOrder(root);
}
