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
    // allocates memory to the next n0 =+ 24-de and assigns its curr value
    tmp->next = (llsnode_t *)malloc(sizeof(llsnode_t));
    tmp = tmp->next;
    tmp->curr = val;
    tmp->next = NULL;
}

// Swap linked list head to new node
llsnode_t *lls_insert_first(llsnode_t *head, int val)
{
    llsnode_t *tmp = malloc(sizeof(llsnode_t));
    tmp->curr = val;
    tmp->next = head;
    return tmp;
}

// Insert node at specified index
void lls_insert_at(llsnode_t *head, int index, int val)
{
    llsnode_t *tmp = head;
    llsnode_t *old = NULL;
    llsnode_t *new = lls_new(val);

    for (int i = 0; i < index - 1; i++)
    {
        tmp = tmp->next;
    }

    old = tmp->next;
    tmp->next = new;
    new->next = old;
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

// Find the index of a node by value
int lls_search(llsnode_t *head, int val) 
{
    llsnode_t *tmp = head;
    int index = -1;
    for (; tmp->next != NULL; tmp = tmp->next) 
    {
        index++;
        if (tmp->curr == val) break;
    }

    return index;
}

// Deletes last node
int lls_delete(llsnode_t *head) 
{
	llsnode_t *tmp = head;
	for (; tmp->next->next != NULL; tmp = tmp->next);
	int val = tmp->next->curr;
	free(tmp->next);
	tmp->next = NULL;
	return val;
}
// Deletes the node in the specified index
// bug: doesn't delete index 0
int lls_delete_index(llsnode_t *head, int index) 
{
	llsnode_t *tmp = head;
	llsnode_t *old = NULL;
	int count = 0;
	int val = 0;
	for (; tmp->next->next != NULL; tmp = tmp->next) 
	{
		if (count < index - 1) count++;
		else break;
	}

	old = tmp->next;
	tmp->next = old->next;
	val = old->curr;
	free(old);
	return val;
}

// Delete the first node
// needs to reassign head
llsnode_t *lls_delete_first(llsnode_t *head) 
{
	llsnode_t *tmp = head->next;
	free(head);
	return tmp;
}

int main(void) 
{
    llsnode_t *node = lls_new(0);
    lls_insert(node, 1);
    lls_insert(node, 2);
    lls_insert(node, 3);
    lls_insert(node, 4);
    lls_insert(node, 5);
    lls_insert(node, 6);
    lls_insert(node, 7);
    lls_insert(node, 8);
    lls_insert(node, 9);

	lls_print(node);
	node = lls_delete_first(node);
	lls_print(node);
    
    return 0;
}
