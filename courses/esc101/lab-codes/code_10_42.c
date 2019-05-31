#include <stdio.h>
#include <stdlib.h>


void **root;

void **getNode()
{
    void **temp = calloc(3,sizeof(void*));
    temp[1]=malloc(sizeof(int));
    return temp;
}


void insert(void **node,int value)
{
    if(value<=*(int*)node[1])
        {
            if(node[0]==0)
                {
                    node[0]=(void**)getNode();
                    void **newnode=node[0];
                    *(int*)newnode[1]=value;
                }
            else
                {
                    insert((void**)node[0],value);
                }
        }
    else
        {
            if(node[2]==0)
                {
                    node[2]=(void**)getNode();
                    void **newnode=node[2];
                    *(int*)newnode[1]=value;
                }
            else
                {
                    insert((void**)node[2],value);
                }
        }
        
}



void print(void **node)
{
    if(node[0]!=0)
        print((void**)node[0]);
    
    printf("%d ",*(int*)node[1]);
    
    if(node[2]!=0)
        print((void**)node[2]);    
    
}

void preorder(void **node)
{
    printf("%d ",*(int*)node[1]);
    if(node[0]!=0)
        preorder((void**)node[0]);
    
    if(node[2]!=0)
        preorder((void**)node[2]);    
    
}

int main()
{
    void **node=getNode();
   *((int*)node[1])=3;
    
//    printf("%d",*((int*)node[1]) );
    

    int n;
    scanf("%d",&n);
    
    root=getNode();
    scanf("%d",(int*)root[1]);
    
    
    int temp;
    int i;
    for(i=1;i<n;i++)
    {
        scanf("%d",&temp);
        
        insert(root,temp);
    }
    
    print(root);
    printf("\n");
    preorder(root);
    
    return 0;
}
