// Clase 7

#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char* argv[])
{
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\t -n   - create new database file (path required)\n");
    printf("\t -f   - open database file (path required)\n");

    return;
}

int main(int argc, char** argv)
{
    char* filepath = NULL;
    bool newfile = false;
    int c;
    int dbfd = -1; //-1 to not to use it as a valid file descriptor

    while((c = getopt(argc, argv, "n:f:")) != -1)
    {
        switch(c)
        {
            case 'n':
                newfile = true;
                filepath = optarg;
                break;
            case 'f':
                filepath = optarg;
                break;
            case '?':
                printf("Unknown option -%c\n", c);
                break;
            default:
                return -1;
        }
    }

    if(filepath == NULL)
    {
        printf("Filepath is a required argument\n");
        print_usage(argv);

        return 0;
    }

    if(newfile)
    {
        int dbfd = create_db_file(filepath);
        if(dbfd == STATUS_ERROR)
        {
            printf("Unable to create database file\n");
            return -1;
        }
    } else {
        int dbfd = open_db_file(filepath);
        if(dbfd == STATUS_ERROR)
        {
            printf("Unable to open database file\n");
            return -1;
        }
    }

    printf("Newfile: %d\n", newfile);
    printf("filepath: %s\n", filepath);

    return 0;
}