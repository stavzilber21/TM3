#include <stdio.h>
#include <string.h>

#define TXT 1024
#define WORD 30

int gematria(char *s)
{
    int answer = 0;
    int i = 0;
    while (s[i])
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            answer += s[i] - 'a' + 1;
        }
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            answer += s[i] - 'A' + 1;
        }
        i++;
    }
    return answer;
}

char atbash(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return 'z' + 'a' - c;
    }
    if (c >= 'A' && c <= 'Z')
    {
        return 'Z' + 'A' - c;
    }
    return c;
}

int isidentical(char *s, char *c)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] != c[i])
        {
            return 0;
        }
    }
    return 1;
}

// Question 1
void Q1(char *w, char *t)
{
    int num = gematria(w);
    int length = strlen(t) - 1;
    char hold[TXT] = {'\0'};
    int k = 0;
    int first = 1;

    for (int i = 0; i < length; i++)
    {
        int wordlen = strlen(w);
        for (int j = i; j < j+wordlen && j<length+1; j++)
        {
            if(gematria(&t[j])==0){
                wordlen++;
                hold[k]=t[j];
                k++;
                break;
            }
            hold[k] = t[j];
            int temp = gematria(hold);
            if(temp==0){
                memset(hold, 0, strlen(hold));
                k = 0;
                break;
            }
            if (temp == num)
            {
                if(first ==0){printf("~");}
                first=0;
                printf("%s", hold);
                memset(hold, 0, strlen(hold));
                k = 0;
                break;
            }
            if (temp > num)
            {
                memset(hold, 0, strlen(hold));
                k = 0;
                break;
            }
            if (temp < num)
            {
                k++;
                continue;
            }
        }
    }
}

// Question 2
void Q2(char *w, char *t)
{
    char wordatbash[WORD] = {'\0'};
    char reversewordatbash[WORD] = {'\0'};
    char hold[TXT] = {'\0'};
    int lengtht = strlen(t);
    int lengthw = strlen(w);
    int k = 0;
    int first = 1;

    for (int i = 0; i < lengthw; i++)
    {
        wordatbash[i] = atbash(w[i]);
        reversewordatbash[lengthw - i - 1] = atbash(w[i]);
    }

    for (int i = 0; i < lengtht; i++)
    {
        for (int j = i; j < lengtht; j++)
        {
            hold[k] = t[j];
            if (strlen(hold) < lengthw)
            {
                k++;
                continue;
            }
            if (isidentical(hold, wordatbash) == 1 || isidentical(hold, reversewordatbash) == 1)
            {
                if(first ==0){printf("~");}
                first=0;
                printf("%s", hold);
                memset(hold, 0, TXT);
                k = 0;
                break;
            }
            if (strlen(hold) >= lengthw)
            {
                memset(hold, 0, TXT);
                k = 0;
                break;
            }
        }
    }
}

// turn pointer to point at original word
void rewrite(char *w, char *og)
{
    for (int i = 0; i < strlen(og); i++)
    {
        w[i] = og[i];
    }
}

int contains(char *w, char c)
{
    for (int i = 0; i < strlen(w); i++)
    {
        if (w[i] == c)
        {
            return 1;
        }
    }
    return 0;
}


void removechar(char *str, const char toRemove){
    int i = 0;
    int len = strlen(str);

    /* Run loop till the first occurrence of the character is not found */
    while(i<len && str[i]!=toRemove)
        i++;

    /* Shift all characters right to the position found above, to one place left */
    while(i < len){
        str[i] = str[i+1];
        i++;
    }
}

int checkforall(char *w, char *s)
{
    int k = 1;
    char hold[TXT] = {'\0'};
    rewrite(hold, w);
    for (int i = 0; i < strlen(s); i++)
    {
        if (contains(hold, s[i]))
        {
            removechar(hold, s[i]);
        }
    }
    if (strlen(hold) == 0)
    {
        return k;
    }
    else
    {
        for (int i = 0; i < strlen(hold); i++)
        {
            if (s[i] != 32)
            {
                k = 0;
            }
        }
    }
    return k;
}

// Question 3
void Q3(char *w, char *t)
{
    char hold[TXT] = {'\0'};  // add to this as we go along
    char edit[WORD] = {'\0'}; // from original - remove what we've already taken
    int length = strlen(t);
    rewrite(edit, w);
    int k = 0;
    int editLen = strlen(w);
    int first = 1;


    for (int j = 0; j < length; j++)
    {
        if(t[j]==32){
            continue;
        }
        int wordlen = strlen(w);
        if (contains(edit, t[j]))
        {
            hold[k] = t[j];
            removechar(edit, t[j]);
            editLen--;
            k++;
        }
        else
        {
            continue;
        }
        for (int i = j + 1; i<length && i < i+wordlen; i++)
        {
            // printf("hold: %s\n",hold);
            // printf("len: %d\n",editLen);
            if (t[i] == 32 || contains(edit, t[i]))
            {
                if(contains(edit, t[i])){
                    editLen--;
                }
                hold[k] = t[i];
                removechar(edit, t[i]);
                k++;
                if(t[i] == 32){
                    wordlen++;
                }
            }
            else{
                memset(hold, 0, TXT);
                rewrite(edit, w);
                k = 0;
                editLen = strlen(w);
                break;
            }
            if (editLen == 0)
            {
                if(first ==0){printf("~");}
                first=0;
                hold[k]='\0';
                printf("%s", hold);
                memset(hold, 0, TXT);
                rewrite(edit, w);
                editLen = strlen(w);
                k = 0;
                break;
            }
        }
    }
}

int main()
{

    char word[WORD] = {'\0'};
    char txt[TXT] = {'\0'};
    char ch_w;
    char ch_t;

    // to get the word
    int i = 0;
    do
    {
        scanf("%c", &ch_w);
        word[i] = ch_w;
        i++;
    } while (ch_w != '\t' && ch_w != '\n' && ch_w != ' ');
    word[i-1]='\0';

    // to get the txt
    i = 0;
    do
    {
        scanf("%c", &ch_t);
        txt[i] = ch_t;
        i++;
    } while (ch_t != '~');
   txt[i-1]='\0';


    printf("Gematria Sequences: ");
    Q1(word,txt); //to add what the function gets
    printf("\n");
    printf("Atbash Sequences: ");
    Q2(word,txt); //to add what the function gets
    printf("\n");
    printf("Anagram Sequences: ");
    Q3(word,txt); //to add what the function gets

}
