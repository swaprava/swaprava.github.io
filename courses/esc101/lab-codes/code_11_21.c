#include<stdio.h>
#include<stdlib.h>
 

typedef struct Node node;
struct Node{
    int value;
    struct Node * next;
};


node*top1;
node*top2;


node* new_node(int x) {
    node* t = (node*) malloc(sizeof(node));

    t -> value = x;
    t -> next = NULL;

    return t;
}


void push(int x, node**top){
    node*temp;
    temp = new_node(x);
    if(*top == NULL){
        *top = temp;
    }
    else{
        temp -> next = *top;
        *top = temp;
    }
}
    

node* pop(node**top){
    if(*top == NULL){
        return NULL;
    }
    node*temp = *top;
    *top = (*top)->next;
    return temp;
}


void enqueue(int val){
    node*temp = pop(&top1);
    while(temp!=NULL){
        push(temp->value,&top2);
        temp = pop(&top1);
    }
    push(val,&top1);
    temp = pop(&top2);
    while(temp!=NULL){
        push(temp->value,&top1);
        temp = pop(&top2);
    }
}

void dequeue(){
    node*temp = pop(&top1);
}

void disp(){
    node*last = top1;
    if(last == NULL){
        printf("Empty\n"); return;
    }
    while(last!=NULL){
        printf("%d ",last->value);
        last = last -> next;
    }
    printf("\n");
}


int main(){
  
    top1 = NULL;
    top2 = NULL;

    int t;
    scanf("%d",&t);
    for (int i = 0; i < t; ++i)
    {
        int n;
        scanf("%d",&n);
        if(n == -1){
            // printf("Hi11");
            dequeue();
            disp();
        }
        else{
            // printf("Hi");
            enqueue(n);
            disp();
        }


    }
    
    return 0;
}
