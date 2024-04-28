/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myftp-bilel.barkallah
** File description:
** command
*/

#include "my_ftp.h"

int my_quit(int clifd)
{
    write(1, "exit by client", 14);
    write(clifd, "221 Service closing control connection.\n", 40);
    clifd = -1;
    close(clifd);
}

int my_delete(int clifd, char *path)
{
    if ((unlink(delete_first_char(path, 5))) == 0)
        write(clifd, "250 Requested file action okay, completed.\n", 43);
    else {
        write(clifd, "216 No such file.\n", 18);
        return 0;
    }
}

void my_cwd(char *path_direction, int clifd)
{
    if (chdir(path_direction) == -1) {
        write(clifd, "failed", 6);
        write(clifd, "\n", 1);
        return;
    }
    else
        write(clifd, "250 Requested file action okay, completed.\n", 43);
}

int my_pwd(int clifd)
{
    char path[1024];

    getcwd(path, sizeof(path));
    write(clifd, "257 \"", 5);
    write(clifd, path, strlen(path));
    write(clifd, "\" ", 2);
    write(clifd, "created.", 8);
    write(clifd, "\n", 1);
}

int my_cdup(int clifd, char *av_path)
{
    if (chdir(av_path) == -1) {
        write(clifd, "failed", 6);
        write(clifd, "\n", 1);
    }
    else {
        write(clifd, "200 Command okay.", 17);
        write(clifd, "\n", 1);
    }
}

int my_help(int clifd)
{
    write(clifd, "USER <SP> <username> <CRLF>   : Specify user for authentication\n", 64);
    write(clifd, "PASS <SP> <password> <CRLF>   : Specify password for authentication\n", 68);
    write(clifd, "CWD  <SP> <pathname> <CRLF>   : Change working directory\n", 57);
    write(clifd, "CDUP <CRLF>                   : Change working directory to parent directory\n", 77);
    write(clifd, "QUIT <CRLF>                   : Disconnection\n", 46);
    write(clifd, "DELE <SP> <pathname> <CRLF>   : Delete file on the server\n", 58);
    write(clifd, "PWD  <CRLF>                   : Print working directory\n", 56);
    write(clifd, "PASV <CRLF>                   : Enable \"passive\" mode for data transfer\n", 72);
    write(clifd, "PORT <SP> <host-port> <CRLF>  : Enable \"active\" mode for data transfer\n", 71);
    write(clifd, "HELP [<SP> <string>] <CRLF>   : List available commands\n", 56);
    write(clifd, "NOOP <CRLF>                   : Do nothing\n", 43);
    write (clifd, "RETR <SP> <pathname> <CRLF>   : Download file from server to client\n", 68);
    write(clifd, "STOR <SP> <pathname> <CRLF>   : Upload file from client to server\n", 66);
    write (clifd, "LIST [<SP> <pathname>] <CRLF> : List files in the current working directory\n", 76);
    write(clifd, "214 Help message.\n", 18);
}