#include "shell.h"

list_t *add_node(list_t **head, const char *str, int num)
{
    if (!head)
        return NULL;

    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->num = num;
    new_node->str = (str) ? _strdup(str) : NULL;
    new_node->next = *head;
    *head = new_node;

    return new_node;
}

list_t *add_node_end(list_t **head, const char *str, int num)
{
    if (!head)
        return NULL;

    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->num = num;
    new_node->str = (str) ? _strdup(str) : NULL;
    new_node->next = NULL;

    if (*head)
    {
        list_t *node = *head;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
    {
        *head = new_node;
    }

    return new_node;
}

size_t print_list_str(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        count++;
    }

    return count;
}

int delete_node_at_index(list_t **head, unsigned int index)
{
    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        list_t *node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    list_t *prev_node = NULL;
    list_t *node = *head;
    unsigned int i = 0;

    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }
        i++;
        prev_node = node;
        node = node->next;
    }

    return 0;
}

void free_list(list_t **head_ptr)
{
    if (!head_ptr || !*head_ptr)
        return;

    list_t *node = *head_ptr;

    while (node)
    {
        list_t *next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }

    *head_ptr = NULL;
}
