#include <stdio.h>
#include <stdlib.h>

typedef struct tnode node;

// The defined structure to be used for each digit of
// a number when represented using a list
struct tnode {
	int x;
	node* next;
};

node* new_node(int x) {
	// This function creates a new node and returns
	// a pointer to the node

	node* t = (node*) malloc(sizeof(node));

	t -> x = x;
	t -> next = NULL;

	return t;
}

void print_list(node* head) {
	// This function prints a list node by node

	while (head != NULL) {
		printf("%d", head->x);
		head = head->next;
		
		if (head != NULL) {
		    printf(" ");
		}
	}
}


void sorted_insert(node** head, int x) {
	// You are supposed to fill this function to do a
	// sorted insert into a linked list.

	node* t = new_node(x);

	if (*head == NULL) {
		*head = t;
	}
	else if ((*head)->x > x) {
		t->next = *head;
		*head = t;
	}
	else {
		node *curr = *head;
		while(curr->next != NULL && curr->next->x < x)
			curr = curr->next;

		t->next = curr->next;
		curr->next = t;
	}
}

int main() {
	node* head = NULL;

	int n;
	scanf("%d", &n);
	
	int arr[n];

	for (int i = 0; i < n; i++) {
		scanf("%d", arr + i);
	}
	
	for (int i = 0; i < n; i++) {
		sorted_insert(&head, arr[i]);
		print_list(head);
		
		for (int j = i + 1; j < n; j++) {
		    printf(" %d", arr[j]);
		}
		
		printf("\n");
	}

	return 0;
}
