#include "routing_table.h"
#include <string.h>

routing_information* node_init(const char* client_path)
{
    routing_information* new_node = (routing_information*)malloc(sizeof(routing_information));
    if (new_node != NULL)
    {
        /* allocate new node */
        new_node->client_path = (char*)(client_path);
        new_node->next = NULL;
        printf("Node created with client path: %s\n", new_node->client_path);
        return new_node;
    }
    return NULL;
}

void add_last(routing_information** head, const char* client_path)
{
    routing_information* new_node = node_init(client_path);
    // if (head == NULL)
    // {
    //     head = new_node;
    // }
    
    if (new_node != NULL)
    {
        if (*head == NULL)
        {
            *head = new_node;
            return;
        }
        /* loop through the topic list */
        routing_information* temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        //add new node to the end of the list
        temp->next = new_node;
    }
}

void delete_node(routing_information** head, const char* client_path)
{
    if (head == NULL)
    {
        /* code */
        printf("No client subcribed this topic!\n");
        return;
    }
    
    routing_information* temp = *head;
    routing_information* prev = NULL;
    while (temp != NULL && strcmp(temp->client_path, client_path) != 0)
    {
        /* code */
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        /* code */
        printf("Client path not found in the routing table.\n");
        return;
    }
    prev->next = temp->next;
    temp->next = NULL;
    free(temp);
}