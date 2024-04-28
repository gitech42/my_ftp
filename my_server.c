/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myftp-bilel.barkallah
** File description:
** my_server
*/

#include "my_ftp.h"


int handle_client(server_t server, int clifd)
{
    char buff[256];
    int len = 0;
    char temp[256];
    int i = 4;
    int k = 0;

    while ((len = read(clifd, buff, sizeof(buff))) > 0 && server.isConnect == true) {
        buff[len] = '\0';
        write(1, buff, len);
        if ((strncmp(buff, "QUIT", 4)) == 0)
            my_quit(clifd);
        else if ((strncmp(buff, "PWD", 3)) == 0)
            my_pwd(clifd);
        else if ((strncmp(buff, "USER ", 4)) == 0)
            write(clifd, "230 User logged in, proceed.\n", 29);
        else if ((strncmp(buff, "PASS ", 4)) == 0)
            write(clifd, "230 User logged in, proceed.\n", 29);
        else if ((strncmp(buff, "CWD ", 4)) == 0)
            my_cwd(delete_first_char(buff, 4), clifd);
        else if ((strncmp(buff, "CDUP", 4)) == 0)
            my_cdup(clifd, "..");
        else if ((strncmp(buff, "NOOP", 4)) == 0)
            write(clifd, "200 Command okay.\n", 18);
        else if ((strncmp(buff, "DELE", 4)) == 0)
            my_delete(clifd, buff);
        else if ((strncmp(buff, "HELP", 4)) == 0)
            my_help(clifd);
        else if ((strncmp(buff, "PASV", 4)) == 0)
            server = my_pasv(clifd, &server);
        else if ((strncmp(buff, "PORT", 4)) == 0)
            my_port(clifd, &server, delete_first_char(buff, 5));
        else if ((strncmp(buff, "RETR ", 5)) == 0)
            my_retr(clifd, server, buff);
        else if ((strncmp(buff, "STOR ", 5)) == 0)
            my_stor(clifd, &server, buff);
        else if ((strncmp(buff, "LIST", 4)) == 0)
            my_list(clifd, &server, buff);
        else
            write (clifd, "500 Syntax error, command unrecognized.\n", 40);
    }
    if (len == -1)
        exit (0);
}

int connect_client(server_t serv, int clifd)
{
    char buff[256];
    int stock = 0;

    while (serv.isConnect == false) {
        read(clifd, buff, sizeof(buff));
        if ((strncmp(buff, "PWD", 3)) == 0 || (strncmp(buff, "CWD", 3)) == 0
        || (strncmp(buff, "DELE", 4)) == 0 || (strncmp(buff, "CDUP", 4)) == 0)
            write(clifd, "530 not logged in.", 18);
        if ((strncmp(buff, "USER Anonymous", 14)) == 0 && stock == 0)
            stock = 1;
        else if ((strncmp(buff, "USER ", 5)) == 0 && stock == 0)
            stock = 9;
        if (stock == 9 && (strncmp(buff, "PASS ", 5)) != 0)
            write(clifd, "331 User name okay, need password.", 34);
        if (stock == 1) {
            write(clifd, "331 User name okay, need password.", 34);
            stock = 2;
        }
        if ((strncmp(buff, "PASS", 4)) == 0 && stock == 2) {
            stock = 3;
            break;
        }
        if ((strncmp(buff, "PASS ", 5)) == 0 && stock == 0 || (strncmp(buff, "PASS ", 5)) == 0 && stock == 9) {
            write(clifd, "332 Need account for login.", 27);
            stock = 0;
        }
            write(clifd, "\n", 1);
    }
        write(clifd, "230 User logged in, proceed.\n", 28);
        write(clifd, "\n", 1);
        if (stock == 3) {
            return 1;
        }
    return 0;
}

int check_arg(char *av)
{
    for (int i = 0; av[i] != '\0'; i++)
        if (av[i] < '0' || av[i] > '9')
            return (-1);
    return (0);
}

int main(int ac, char **av)
{
    int sockfd, ret;
    int newsocket;
    struct sockaddr_in newaddr;
    char buffer[1024];
    pid_t pid;
    int addrsize;
    fd_set readfds;
    int max_fd, arr_client_socket[30], activity;
    server_t serv;

    serv.isConnect = false;
    serv.av_path = av[2];
    serv.data_transfer = 0;
    serv.pasv_port = 44592;
    if (ac != 3)
        exit (84);
    if (chdir(av[2]) != 0) {
        perror("error with path arg2");
        exit(84);
    }
    if ((check_arg(av[1])) == -1)
        exit(84);
    for (int i = 0; arr_client_socket[i]; i++)
        arr_client_socket[i] = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("error socket");
        exit(84);
    }
    printf("server socket is crearted \n");
    memset(&serv.serveraddr, '\0', sizeof(serv.serveraddr));
    serv.serveraddr.sin_addr.s_addr = INADDR_ANY;
    serv.serveraddr.sin_family = AF_INET;
    serv.serveraddr.sin_port = htons(atoi(av[1]));
    ret = bind(sockfd, (struct sockaddr*)&serv.serveraddr, sizeof(serv.serveraddr));
    if (ret < 0) {
        perror ("error bind");
        exit (84);
    }
    printf ("bind ok \n");
    if (listen(sockfd, SOMAXCONN) == 0)
        printf("Listenning....\n");
    else
        exit(84);
    addrsize = sizeof(serv.serveraddr);
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        max_fd = sockfd;
        for (int i = 0 ; arr_client_socket[i] ; i++) {
            serv.fd = arr_client_socket[i];
            if(serv.fd > 0)
                FD_SET(serv.fd , &readfds);
            if(serv.fd > max_fd)
                max_fd = serv.fd;
        }
        activity = select( max_fd + 1 , &readfds , NULL , NULL , NULL);
        newsocket = accept(sockfd, (struct sockaddr*)&serv.serveraddr, (socklen_t*)&addrsize);
        if (newsocket < 0) {
            perror ("error accept");
            exit (84);
        }
        getpeername(serv.fd, (struct sockaddr*)&serv.serveraddr, (socklen_t*)&addrsize);
        printf("Connection from ip %s, and port %d\n", inet_ntoa(serv.serveraddr.sin_addr), ntohs(serv.serveraddr.sin_port));
        write (newsocket, "220 Service ready for new user.\n", 32);
        if ((pid = fork()) == 0) {
            close(sockfd);
            while (1) {
                if ((connect_client(serv, newsocket)) == 1)
                    serv.isConnect = true;
                handle_client(serv, newsocket);
            }
        }
    }
}