#include<stdio.h>

int search1 (int [], int, int, int); // args refer to arr, start, end, key
int search2 (int [], int, int, int); // args refer to arr, start, end, key

int search1CallCounter = 0;
int search2CallCounter = 0;

int main(){
    int arr[] = {31, 4, 10, 35, 59};
    int index, start = 0, end = 4;
    int key;

    printf ("Please enter the integer key to search: ");
    scanf ("%d", &key);

    index = search1 (arr, start, end, key);

    if (index != -1) printf ("After searching via search1, key FOUND at index %d\n", index);
    else printf ("After searching via search1, key NOT FOUND\n");

    printf ("search1CallCounter = %d\n", search1CallCounter);

    index = search2 (arr, start, end, key);

    if (index != -1) printf ("After searching via search2, key FOUND at index %d\n", index);
    else printf ("After searching via search2, key NOT FOUND\n");

    printf ("search2CallCounter = %d\n", search2CallCounter);

    return 0;
}

int search1 (int arr[], int start, int end, int key){

    search1CallCounter++;
    if (start > end) return -1;
    if (arr[start] == key) return start;
    return search1(arr, start+1, end, key);
}

int search2 (int arr[], int start, int end, int key){

    search2CallCounter++;
    if (start > end) return -1;
    int mid = (start + end)/ 2;
    if (arr[mid] == key) return mid;
    int leftindex = search2(arr, start, mid-1, key);
    int rightindex = search2(arr, mid+1, end, key);

    if (leftindex != -1) return leftindex;
    else if (rightindex != -1) return rightindex;
    else return -1;

}