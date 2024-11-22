#include <stdio.h>
void reverse(char* str) {
    char *begin = str;
    char *end = str;

    while (*end != '\0') {
        end++;
    }
    end--;

    while (begin < end) {
        char temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }
}
int main()
{
    char str[21];
    printf("Enter a string: ");
    scanf("%20[^\n]", str);

    if (str[0]== '\n')
        {printf("порожня стрічка\n");
        return 0;

    }
    printf("Original string: %s\n", str);
    reverse(str);
    printf("Reversed string: %s\n", str);

    return 0;
}