#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node* listNode;

void display_list(listNode head)
{
    listNode cur = head;
    printf ("\n\nThe list is:\n");
    printf ("\nHead:%p \n\t  |\n\t  |\n\t  V ", head);
    while (cur != NULL) {
        printf ("\n\tnode\naddress:%p\n", cur);
        printf ("data=%d\nnext:%p  \n\t  |\n\t  |\n\t  V ", cur->data, cur->next);
        cur = cur->next;
    }
    printf("\n\tNULL\n");
}

listNode make_node(int val) {
    listNode nd;
    nd = (listNode ) malloc(sizeof(struct node));
    nd->data = val; 
    nd->next = NULL;
    return nd; 
}

listNode insert_front(int val, listNode head) {
    listNode newnode = make_node(val); 
    newnode->next = head;
    head = newnode; 
    return head;
}

void insert_end(int val, listNode *headPtr) {
    listNode tempnode = *headPtr, newnode = make_node(val);
    if (*headPtr == NULL)
        *headPtr = newnode;
    else{
        while (tempnode->next != NULL)
            tempnode = tempnode->next;
        tempnode->next = newnode;
    }
}

// AFTER PREVIOUS CODES FOR FUNCTIONS

void insert_after_node(listNode *pcurr, listNode pnew, char flag) {
    if (*pcurr != NULL) {
        // Order of statements is important
        if (flag == 'H') {
            pnew->next = *pcurr; // if adding at the head
            *pcurr = pnew;
        }
        else {
            pnew->next = (*pcurr)->next; // for adding after regular nodes
            (*pcurr)->next = pnew; 
        }
    }
    else *pcurr = pnew; // assuming that the new node is terminated by NULL
} 

void delete_node(listNode *ppnode, listNode pnode, char flag) {

    if (*ppnode != NULL) {
        if (flag == 'H')
            *ppnode = pnode->next;
        else
            (*ppnode)->next = pnode->next;
        free (pnode);
    }
}


int main() {
     
    listNode head = NULL, temp;
    int val, loc, listLength=0;

    /* CREATING THE LINKED LIST */
    printf("Enter an integer to the list (-10 to stop): ");
    scanf ("%d", &val);
    while (val !=-10){
        listLength++;
        // head = insert_front(val, head);
        insert_end(val, &head);
    //    printf ("\nIntermediate list:\n");
    //    display_list (head);
        printf("Enter an integer to the list (-10 to stop): ");
        scanf ("%d", &val);
    }

    printf ("\nFinal list:\n");
    display_list (head);
    printf ("listLength = %d\n", listLength);

    /* ADDING ANOTHER NODE AT A DESIRED LOCATION */

    /* loc = listLength+1;
    // add node at a specific pointer
    while (loc > listLength){
        printf ("\nWhich location do you want to add a node (0 for beginning): ");
        scanf("%d", &loc);
    }
    printf ("Enter the integer of the node: ");
    scanf ("%d", &val);
    listNode newnode = make_node(val);

    if (loc == 0)
        insert_after_node(&head, newnode, 'H');
    else{
        temp = head;
        for (int i=0; i<loc-1; i++)
            temp = temp->next;
        insert_after_node(&temp, newnode, 'X');
    }
    listLength++;
    
    printf ("\nAfter adding the node:\n");
    display_list (head);  */

    /* DELETING A NODE AT A DESIRED LOCATION */

    char cont = 'y'; // continue with deletion repeatedly

    while (cont == 'y' || cont == 'Y') {

        loc = listLength+1;
        // add node at a specific pointer
        while (loc >= listLength || loc < 0){
            printf ("\nWhich location do you want to delete a node (0 for beginning): ");
            scanf("%d", &loc);
        }

        if (loc == 0)
            delete_node(&head, head, 'H');
        else{
            temp = head;
            for (int i=0; i<loc-1; i++)
                temp = temp->next;
            delete_node(&temp, temp->next, 'X');
        }
        listLength--;

        printf ("\nAfter deleting the node:\n");
        display_list (head);

        printf("Want to continue? (y/n) ");
        scanf(" %c", &cont);

        if (listLength == 0) {
            printf ("Empty list, exiting ... \n");
            break;
        }
    }

    
    return 0;
}