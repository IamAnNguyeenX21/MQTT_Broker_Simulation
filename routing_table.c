#include "routing_table.h"

routing_information* routing_table[100];

routing_information* node_init(const char* client_path)
{
    routing_information* new_node = (routing_information*)malloc(sizeof(routing_information));
    if (new_node != NULL)
    {
        /* allocate new node */
        new_node->client_path = (char*)(client_path);
        new_node->next = NULL;
        return new_node;
    }
    return NULL;
}



