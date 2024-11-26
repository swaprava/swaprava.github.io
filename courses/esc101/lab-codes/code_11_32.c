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

void read_number(node** head) {
	// This function reads a number into a linked
	// list. Note that each node will store one digit

	node* curr = NULL;

	int c;
	while ((c = getchar()) >= '0' && c <= '9') {
		c -= '0';
		if (curr == NULL) {
			if (c != 0)
				*head = curr = new_node(c);
		}
		else
			curr = curr->next = new_node(c);
	}
}

node* reverse_number(node* head) {
	// This function reverses a linked list and
	// returns the head pointer of the reversed list

	if (head == NULL || head->next == NULL)
		return head;

	node* new_head = reverse_number(head->next);
	head->next->next = head;
	head->next = NULL;

	return new_head;
}

void print_number(node* head) {
	// This function prints a list digit by digit

	while (head != NULL) {
		printf("%d", head->x);
		head = head->next;
	}
	printf("\n");
}

node* add_numbers(node* num1, node* num2) {
	// You are supposed to fill this function to add
	// the two numbers into a new linked list. The
	// funtion must return the head pointer of the new
	// list

	num1 = reverse_number(num1);
	num2 = reverse_number(num2);

	node *sum, *curr = NULL;
	int s, carry = 0;

	while (num1 != NULL && num2 != NULL) {
		s = num1->x + num2->x + carry;

		carry = s / 10;
		s %= 10;

		if (curr == NULL)
			sum = curr = new_node(s);
		else
			curr = curr->next = new_node(s);

		num1 = num1->next;
		num2 = num2->next;
	}

	node* rest = (num1 == NULL) ? num2 : num1;

	while (rest != NULL) {
		s = rest->x + carry;

		carry = s / 10;
		s %= 10;

		if (curr == NULL)
			sum = curr = new_node(s);
		else
			curr = curr->next = new_node(s);

		rest = rest->next;
	}

	if (carry != 0) {
		curr->next = new_node(carry);
	}

	return reverse_number(sum);
}

int main() {
	node *num1, *num2;

	read_number(&num1);
	read_number(&num2);

	node* sum = add_numbers(num1, num2);

    print_number(sum);

	return 0;
}
