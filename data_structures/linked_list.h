#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// BUG: delete_first causes entire list to disappear

#define LLS_INIT(T)                                                               \
    /* Singly Linked list's node struct */                                        \
    typedef struct LlsNode_##T                                                    \
    {                                                                             \
        T curr;                                                                   \
        struct LlsNode_##T *next;                                                 \
    } LlsNode_##T;                                                                \
                                                                                  \
    /* Initializes linked list's first node*/                                     \
    LlsNode_##T *lls_new_##T(T val)                                               \
    {                                                                             \
        LlsNode_##T *new = malloc(sizeof(*new));                                  \
        new->curr = val;                                                          \
        new->next = NULL;                                                         \
        return new;                                                               \
    }                                                                             \
    /* Inserts node to the end of the list */                                     \
    void lls_insert_##T(LlsNode_##T *head, T val)                                 \
    {                                                                             \
        LlsNode_##T *tmp = head;                                                  \
        /* reassigns tmp to the last LlsNode */                                   \
        for (; tmp->next != NULL; tmp = tmp->next)                                \
            ;                                                                     \
        /* allocates memory to the next n0 =+ 24-de and assigns its curr value */ \
        tmp->next = malloc(sizeof(LlsNode_##T));                                  \
        tmp = tmp->next;                                                          \
        tmp->curr = val;                                                          \
        tmp->next = NULL;                                                         \
    }                                                                             \
                                                                                  \
    /* Swap linked list head to new node */                                       \
    LlsNode_##T *lls_insert_first_##T(LlsNode_##T *head, T val)                   \
    {                                                                             \
        LlsNode_##T *tmp = malloc(sizeof(*tmp));                                  \
        tmp->curr = val;                                                          \
        tmp->next = head;                                                         \
        return tmp;                                                               \
    }                                                                             \
                                                                                  \
    /* Insert node at specified index */                                          \
    void lls_insert_at_##T(LlsNode_##T *head, int index, T val)                   \
    {                                                                             \
        LlsNode_##T *tmp = head;                                                  \
        LlsNode_##T *old = NULL;                                                  \
        LlsNode_##T *new = lls_new_##T(val);                                          \
                                                                                  \
        for (int i = 0; i < index - 1; i++)                                       \
        {                                                                         \
            tmp = tmp->next;                                                      \
        }                                                                         \
                                                                                  \
        old = tmp->next;                                                          \
        tmp->next = new;                                                          \
        new->next = old;                                                          \
    }                                                                             \
                                                                                  \
    void lls_print(LlsNode_##T *head)                                             \
    {                                                                             \
        LlsNode_##T *tmp = head;                                                  \
        while (true)                                                              \
        {                                                                         \
            printf("%d", tmp->curr);                                              \
            tmp = tmp->next;                                                      \
            if (tmp == NULL)                                                      \
                break;                                                            \
            printf("->");                                                         \
        }                                                                         \
        printf("\n");                                                             \
    }                                                                             \
                                                                                  \
    /* Deletes last node*/                                                        \
    T lls_delete_##T(LlsNode_##T *head)                                           \
    {                                                                             \
        LlsNode_##T *tmp = head;                                                  \
        for (; tmp->next->next != NULL; tmp = tmp->next)                          \
            ;                                                                     \
        T val = tmp->next->curr;                                                  \
        free(tmp->next);                                                          \
        tmp->next = NULL;                                                         \
        return val;                                                               \
    }                                                                             \
    /* Deletes the node in the specified index */                                 \
    /* bug: doesn't delete index 0 */                                             \
    T lls_delete_index_##T(LlsNode_##T *head, int index)                          \
    {                                                                             \
        LlsNode_##T *tmp = head;                                                  \
        LlsNode_##T *old = NULL;                                                  \
        int count = 0;                                                            \
        T val;                                                                    \
        for (; tmp->next->next != NULL; tmp = tmp->next)                          \
        {                                                                         \
            if (count < index - 1)                                                \
                count++;                                                          \
            else                                                                  \
                break;                                                            \
        }                                                                         \
                                                                                  \
        old = tmp->next;                                                          \
        tmp->next = old->next;                                                    \
        val = old->curr;                                                          \
        free(old);                                                                \
        return val;                                                               \
    }                                                                             \
                                                                                  \
    /* Delete the first node needs to reassign head*/                             \
    LlsNode_##T *lls_delete_first_##T(LlsNode_##T *head)                          \
    {                                                                             \
        LlsNode_##T *tmp = head->next;                                            \
        free(head);                                                               \
        return tmp;                                                               \
    }

/* TODO
// Find the index of a node by value
int lls_search(llsnode_t *head, int val)
{
    llsnode_t *tmp = head;
    int index = -1;
    for (; tmp->next != NULL; tmp = tmp->next)
    {
        index++;
        if (tmp->curr == val)
            break;
    }

    return index;
}*/
#endif