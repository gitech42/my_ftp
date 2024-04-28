/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myftp-bilel.barkallah
** File description:
** command_bis
*/

#include "my_ftp.h"

void my_port(int clifd, server_t *server, char *buff)
{
    return 0;
}

int my_retr(int clifd, server_t server, char *buff)
{
    return 0;
}

int my_stor(int clifd, server_t *server, char *buff)
{
    return 0;
}

void my_list(int clifd, server_t *server, char *buff)
{
    return 0;
}


char *get_server_ip()
{
    static char ip[32];
    FILE *f = popen("ip a | grep 'scope global' | grep -v ':' | awk '{print $2}' | cut -d '/' -f1", "r");
    int c, i = 0;
    while ((c = getc(f)) != EOF) {
        if (c == '\n' || c == ' ' || c =='\0')
            break;
        i += sprintf(ip+i, "%c", c);
    }
    pclose(f);
    return ip;
}

server_t my_pasv(int clifd, server_t *server)
{
    return *server;
}