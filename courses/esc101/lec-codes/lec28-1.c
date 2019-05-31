#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};


void display_list(struct node *head)
{
    struct node *cur = head;
    printf ("\n\nThe list is:\n");
    printf ("\nHead:%p \n\t  |\n\t  |\n\t  V ", head);
    while (cur != NULL) {
        printf ("\n\tnode\naddress:%p\n", cur);
        printf ("data=%d\nnext:%p  \n\t  |\n\t  |\n\t  V ", cur->data, cur->next);
        cur = cur->next;
    }
    printf("\n\tNULL\n");
}

struct node *make_node(int val) {
    struct node *nd;
    nd = (struct node *) malloc(sizeof(struct node));
    nd->data = val; 
    nd->next = NULL;
    return nd; 
}

struct node *insert_front(int val, struct node *head) {
    struct node *newnode= make_node(val); 
    newnode->next = head;
    head = newnode; 
    return head;
}

void insert_end(int val, struct node **headPtr) {
    struct node *tempnode = *headPtr, *newnode = make_node(val);
    if (*headPtr == NULL)
        *headPtr = newnode;
    else{
        while (tempnode->next != NULL)
            tempnode = tempnode->next;
        tempnode->next = newnode;
    }
}

int main() {
     
    struct node *head = NULL;
    int val;
    printf("Enter an integer to the list (-10 to stop): ");
    scanf ("%d", &val);
    while (val !=-10){
        // head = insert_front(val, head);
        insert_end(val, &head);
        printf ("\nIntermediate list:\n");
        display_list (head);
        printf("Enter an integer to the list (-10 to stop): ");
        scanf ("%d", &val);
    }

    printf ("\nFinal list:\n");
    display_list (head);
    
    return 0;
}