#include <stdio.h>

int main() {
    int mat[8][8];
    int r,c,n;
    memset(mat,0,sizeof(mat));
    scanf("%d",&n);
    int row[8],col[8],diag1[16],diag2[16];
    memset(row,0,sizeof(row));
    memset(col,0,sizeof(col));
    memset(diag1,0,sizeof(diag1));
    memset(diag2,0,sizeof(diag2));
    int found=0;
    for(int i=0;i<n;i++) {
        scanf("%d %d",&r,&c);
        mat[r][c]=1;
        
        if(row[r]==1){
        	found=1;
        } else {
        	row[r]=1;
        }
        if(col[c]==1){
        	found=1;
        } else {
        	col[c]=1;
        }
        if(diag1[r+c]==1){
        	found=1;
        } else {
        	diag1[r+c]=1;
        }
        if(diag2[8+r-c]==1){
        	found=1;
        } else {
        	diag2[8+r-c]=1;
        }
    }
    if(found==1){
        printf("no\n");
    } else{
        printf("yes\n");
    }
}
