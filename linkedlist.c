#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


// Singly Linked list's node struct
typedef struct LlsNode {
    int curr;
    struct LlsNode *next;
} llsnode_t;


// Initializes linked list's first node
llsnode_t *lls_new(int val) 
{
    llsnode_t *new = (llsnode_t *)malloc(sizeof(llsnode_t));
    new->curr = val;
    new->next = NULL;
    return new;
}


// Inserts node to the end of the list
void lls_insert(llsnode_t *head, int val) 
{
    llsnode_t *tmp = head;
    // reassigns tmp to the last llsnode_t
    for (; tmp->next != NULL; tmp = tmp->next);
    // allocates memory to the next node and assigns its curr value
    tmp->next = (llsnode_t *)malloc(sizeof(llsnode_t));
    tmp = tmp->next;
    tmp->curr = val;
    tmp->next = NULL;
}

llsnode_t *lls_insert_first(llsnode_t *head, int val)
{
    llsnode_t *tmp = malloc(sizeof(llsnode_t));
    tmp->curr = val;
    tmp->next = head;
    return tmp;
}

llsnode_t *lls_insert_at(llsnode_t *head, int index, int val)
{
    for (int i = 0; i <= index; i++)
    {
        printf("%d", i);
    }
}


void lls_print(llsnode_t *head) 
{
    llsnode_t *tmp = head;
    while (true) 
    {
        printf("%d", tmp->curr);
        tmp = tmp->next;
        if (tmp == NULL) break;
        printf("->");
    }
    printf("\n");
}


bool lls_search(llsnode_t *head, int val)
{
    llsnode_t *tmp = head;
    while (true) 
    {
        if (tmp->curr == val) return true;
        tmp = tmp->next;
        if (tmp == NULL) return false;
    }
}

int main(void) 
{
    llsnode_t *node = lls_new(0);
    lls_insert(node, 5);
    lls_insert(node, 7);
    lls_insert(node, 2);
    lls_insert(node, 9);
    node = lls_insert_first(node, 23);
    lls_print(node);
    
    printf("%d", lls_search(node, 3));
    return 0;
}