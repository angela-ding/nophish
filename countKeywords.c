/**
 * This program counts the frequency of all the words that 
 * appear in the string provided. It then compares it to the
 * common keywords and if a certain keyword appears more than
 * three times, it is considered a malicious word.
*/

#include <stdio.h>
#include <string.h>
 
int main()
{
    int count = 0, c = 0, i, j = 0, k, space = 0;
 
    char str[100], p[50][100], str1[20], ptr1[50][100];
 
    char *ptr;
 
    printf("Enter the string\n");
    scanf(" %[^\n]s", str);
 
    //counts spaces after punctuation, function does not count a space as a word, only spaces
    //after a comma or period
    for (i = 0;i<strlen(str);i++)
    {
        if ((str[i] == ' ')||(str[i] == ',' && str[i+1] == ' ')||(str[i] == '.'))
        {
            space++;
        }
    }
 
    for (i = 0, j = 0, k = 0;j < strlen(str);j++)
    {
        if ((str[j] == ' ')||(str[j] == 44)||(str[j] == 46))  
        {    
            p[i][k] = '\0';
            i++;
            k = 0;
        }        
        else
             p[i][k++] = str[j];
    }
 
    k = 0;
 
    for (i = 0; i <= space; i++)
    {
        for (j = 0; j <= space; j++)
        {
            if (i == j)
            {
                strcpy(ptr1[k], p[i]);
                k++;
                count++;
 
                break;
            }
            else
            {
                if (strcmp(ptr1[j], p[i]) != 0)
                    continue;
                else
                    break;
            }
        }
    }
    char *line = NULL;
    FILE *fp;
    size_t len = 0;
    ssize_t read;

    fp = fopen("keywords.txt", "r");

    if (fp == NULL) //if text file is empty
        printf("error!");

    //counts frequency of each word that appears in the string
    //compares each word to each line in the text file
    //if word occurs over 3 times, it is considered a malicious word

    for (i = 0; i < count; i++)
    {
        for (j = 0; j <= space; j++)
        {
            if (strcmp(ptr1[i], p[j]) == 0)
                c++;
        }
        while ((read = getline(&line, &len, fp)) != -1){
            if ((strcmp(line, ptr1[i]) == 0) && (c >= 2))
                printf("%s is a malicious word", ptr1[i]);
                break;
        }
        fclose(fp);
        c = 0;
    }
}