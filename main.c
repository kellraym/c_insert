#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 64

typedef struct String
{
    char *str;
    size_t length;
} String;

void str_copy(char *target, char *source, int len)
{
    while (len)
    {
        *target++ = *source++;
        len--;
    }
    *target = '\0';
}

size_t str_len(char *s) // returns length including space for null char
{
    size_t l = 0;
    while (s[l++]);
    return l;
}

String *new_string(char *str)
{
    size_t l = str_len(str);

    String *s = malloc(sizeof(String));
    s->str = calloc(sizeof(char), l);
    s->length = l;
    str_copy(s->str, str, s->length);
    return s;
}

String *get_string()
{
    char input_buffer[BUFFER_SIZE];
    int i, ch;
    i = 0;
    
    while ((ch = getchar()) != '\n')
    {
        if (i == BUFFER_SIZE - 1) break;

        input_buffer[i++] = ch;
    }
    input_buffer[i] = '\0';
    String *s = malloc(sizeof(String));
    s->str = calloc(sizeof(char), i);
    s->length = i;
    str_copy(s->str, input_buffer, i);
    return s;
}

int char_to_int(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    fprintf(stderr, "Error in char to int: non-number char entered by user");
    exit(1);
}

int str_to_int(String *s)
{
    int factor = 1;
    int res = 0;
    // index of last non-null char in s->str
    for (int i = s->length - 1; i >= 0; i--)
    {
        res += char_to_int(s->str[i]) * factor; 
        factor *= 10;
    }    
    return res;
}   

int get_index()
{
    String *s;
    int res;
    s = get_string();
    res = str_to_int(s);

    return res;
    
}

void free_string(String *s)
{
    free(s->str);
    free(s);
}

String *insert( String *org, String *ins, int index) // consumes both input Strings and returns a new one 
{
    int i, new_i;
    size_t new_len = org->length + ins->length - 1;
    String *new_string = malloc(sizeof(String));
    new_string->str = calloc(sizeof(char), new_len);
    new_string->length = new_len;
    
    for ( i = 0; i < index; i++)
    {
        if (!org->str[i])
        {
            fprintf(stderr, "Error appending first half or original");
            exit(1);
        }
        new_string->str[i] = org->str[i]; // fills new string with org up to index
    }

    new_i = i;
    for (int j = 0; ins->str[j]; j++) // fills new string with insertion string at given index
    {
        if (!ins->str[j])
        {
            fprintf(stderr, "Error inserting string");
            exit(1);
        }
        new_string->str[new_i++] = ins->str[j];
    }
    while (new_i <= new_string->length) // fills new string with remaining original string
    {
        new_string->str[new_i++] = org->str[i++];
    }
    new_string->str[new_i] = '\0';

    free_string(org);
    free_string(ins); // consumes org and ins before returning new String
    return new_string;
}

int main()
{
    int ind;
    String *str1, *str2, *final_s;
    printf("Enter some words: ");
    str1 = get_string();
    printf("Enter index to insert (original string is %u characters): ", str1->length);
    ind = get_index();
    printf("Enter string to insert: ");
    str2 = get_string();
    final_s = insert(str1, str2, ind);
    printf("Your final string is: '%s'", final_s->str);
    return 0;
}
