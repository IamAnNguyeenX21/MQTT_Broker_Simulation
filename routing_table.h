#ifndef ROUTING_TABLE_H
#define ROUTING_TABLE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct routing_information
{
    /* data */
    char* client_path;
    routing_information* next;
} routing_information;



#endif