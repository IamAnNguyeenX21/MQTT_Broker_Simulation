#ifndef ROUTING_TABLE_H
#define ROUTING_TABLE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct routing_information
{
    /* data */
    char* client_path;
    struct routing_information* next;
} routing_information;

void add_last(routing_information** head, const char* client_path);
void delete_node(routing_information** head, const char* client_path);


#endif