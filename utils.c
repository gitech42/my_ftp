/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myftp-bilel.barkallah
** File description:
** utils
*/

#include "my_ftp.h"

char **my_str_to_word_array(char *str, char c)
{
    int a = 0;
    int j = 0;
    char **tab = malloc(sizeof(char *) * 10);
    tab[j] = malloc(sizeof(char) * 20);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            tab[j++][a] = '\0';
            a = 0;
            tab[j] = malloc(sizeof(char) * 20);
        }
        else if (str[i] != c)
            tab[j][a++] = str[i];
    }
    tab[j + 1] = NULL;
    tab[j][a] = '\0';
    return (tab);
}


char *delete_first_char(char *contents, size_t n )
{
   char *b = contents + n;
   int i = strlen(b);
   b[i - 2] = '\0';
   return b;
}

char *get_format_Ip(char *ip)
{
    char **tab = my_str_to_word_array(ip, ',');
    char *temp = tab[0];
    temp = strcat(temp, ".");
    temp = strcat(temp, tab[1]);
    temp = strcat(temp, ".");
    temp = strcat(temp, tab[2]);
    temp = strcat(temp, ".");
    temp = strcat(temp, tab[3]);
    return temp;
}

int get_format_port(char *port)
{
    char **tab = my_str_to_word_array(port, ',');
    int stock = atoi((tab[4])) * 256 + atoi(tab[5]);
    return stock;
}