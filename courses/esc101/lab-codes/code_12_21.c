// To find number of node in the subtree rooted at a value
// and the sum of leaves in that subtree
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


int getLeafSum(node root){
    if (root==NULL)
        return 0;
    else if (root->left==NULL && root->right==NULL)
        return root->val;
    else
        return getLeafSum(root->left)+getLeafSum(root->right);
}


void leafySum(node root, int value){
    if(root==NULL) 
        return;
    if(value < root->val)
        leafySum(root->left, value);
    else if(value > root->val)
        leafySum(root->right, value);
    else{
        int sum = getLeafSum(root);
        printf("%d\n", sum);
    }
    return;
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
		leafySum(root, val);
	}
    return 0;
}
