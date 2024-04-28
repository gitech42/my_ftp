/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myftp-bilel.barkallah
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
#define MY_FTP_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdbool.h>
#include <assert.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <ifaddrs.h>


typedef struct server_s
{
    bool isConnect;
    char *av_path;
    int data_transfer;
    int fd;
    struct sockaddr_in serveraddr;
    int new_fd;
    int pasv_port;
} server_t;


char **my_str_to_word_array(char *str, char c);
char *delete_first_char(char *contents, size_t n );
char *get_format_Ip(char *ip);
int get_format_port(char *port);
int my_cdup(int clifd, char *av_path);
int my_pwd(int clifd);
void my_cwd(char *path_direction, int clifd);
int my_delete(int clifd, char *path);
int my_quit(int clifd);
void my_port(int clifd, server_t *server, char *buff);
int my_retr(int clifd, server_t server, char *buff);
int my_stor(int clifd, server_t *server, char *buff);
void my_list(int clifd, server_t *server_s, char *buff);
server_t my_pasv(int clifd, server_t *server);
int my_help(int clifd);
int handle_client(server_t server, int clifd);
int connect_client(server_t serv, int clifd);


#endif /* !MY_FTP_H_ */
