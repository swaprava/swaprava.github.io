#include <stdio.h>
#include <string.h>

#define SIZE 50

int read_into_array (char t[], int size) {
    char ch;
    int count = 0;
    scanf("%c", &ch);
    while (count < size && ch != '\n') {
	    t[count] = ch;
	    count = count + 1;
        scanf("%c", &ch);
    }
    t[count] = '\0';
    return count;
}

void strrev (char str[]){
    char temp;
    int size = strlen(str);
    int start = 0, end = size-1;

    while (start < end){
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


int count_letters(char str[], char letter)
{
    char temp[SIZE];
    int idx,i,count = 0;
    char *p = strchr(str, letter);

    while (p != NULL) {
        count++;
        idx = p - str + 1;				// locate
        strrev(str);			// reverse
        strncpy(temp,str,strlen(str)-idx);		// truncate
        strcpy(str,temp);	// replace

        for(i=0; i<strlen(temp); i++)
            temp[i] = -1;
        p = strchr(str, letter);			// search
    } 
    return count;
}

/* int count_letters_pointers (char *str, char letter)
{
     int cnt = 0;
     char *p = strchr(str, letter);
     while(p != NULL) {
        cnt++;
        // puts (p);
        p = strchr(p+1, letter);			// search
   } 
   return cnt;
} */



int main(){
    char str[SIZE], cpy_str[SIZE];
    int i;

    int size = 1000;
    printf ("Enter the sentence (press Enter to end): ");
    read_into_array(str, size);

    char alphabet[26];

    for (i = 0; i < 26; i++){
        alphabet[i] = 'a' + i;
        // printf ("alphabet[%d] = %c\n", i, alphabet[i]);
    }

    for(i=0; i<sizeof(alphabet); i++){
        strcpy(cpy_str,str);  // why do we need this?
        printf("%c\t%d\n", alphabet[i], count_letters(cpy_str,alphabet[i]));
    }
    return 0;
}
