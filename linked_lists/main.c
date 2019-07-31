/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  linked list example
 *
 *        Version:  1.0
 *        Created:  07/30/2019 09:35:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nisennenmondai,
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdlib.h>
#include <stdio.h>

struct node {
    int val;
    struct node *next;
};

void print_list(struct node *root);

void push_back(struct node *root, int val);

void push_front(struct node **root, int val);

int pop_front(struct node **root);

int pop_back(struct node *root);

int pop_by_index(struct node **root, int idx);

int pop_by_value(struct node **root, int val);

void free_list(struct node *root);

int main(void)
{
    struct node *root = (struct node*)malloc(sizeof(struct node));
    root->val = 1;
    root->next = NULL;

    printf("\npush back\n");
    push_back(root, 2);
    print_list(root);

    printf("\npush back\n");
    push_back(root, 3);
    print_list(root);

    printf("\npush front\n");
    push_front(&root, 4);
    print_list(root);

    printf("\npush front\n");
    push_front(&root, 5);
    print_list(root);

    printf("\npop front\n");
    pop_front(&root);
    print_list(root);

    printf("\npop front\n");
    pop_front(&root);
    print_list(root);

    printf("\npop back\n");
    pop_back(root);
    print_list(root);

    printf("\npop back\n");
    pop_back(root);
    print_list(root);

    printf("\npush back\n");
    push_back(root, 2);
    print_list(root);

    printf("\npush back\n");
    push_back(root, 3);
    print_list(root);

    printf("\npush back\n");
    push_back(root, 4);
    print_list(root);

    printf("\npop by index\n");
    pop_by_index(&root, 2);
    print_list(root);

    printf("\npop by index\n");
    pop_by_index(&root, 2);
    print_list(root);

    printf("\npush back\n");
    push_back(root, 3);
    print_list(root);

    printf("\npush back\n");
    push_back(root, 4);
    print_list(root);

    printf("\npop by value\n");
    pop_by_value(&root, 1);
    print_list(root);

    printf("\npush front\n");
    push_front(&root, 1);
    print_list(root);

    printf("\npop by value\n");
    pop_by_value(&root, 3);
    print_list(root);

    printf("\npop by value\n");
    pop_by_value(&root, 1);
    print_list(root);

    printf("\nfree list\n");
    free_list(root);
    print_list(root);

    free(root);

    return 0;
}

void print_list(struct node *root)
{
    struct node *current = root;

    while (current != NULL) {
        printf("val %d\n", current->val);
        current = current->next;
    }
}

void push_back(struct node *root, int val)
{
    struct node *current = root;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (struct node*)malloc(sizeof(struct node));
    current->next->val = val;
    current->next->next = NULL;
}

void push_front(struct node **root, int val)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->val = val;
    new_node->next = *root;
    *root = new_node;
}

int pop_front(struct node **root)
{
    int ret = -1;
    struct node *next_node = NULL;

    if (*root == NULL) {
        return -1;
    }

    next_node = (*root)->next;
    ret = (*root)->val;
    free(*root);
    *root = next_node;

    return ret;
}

int pop_back(struct node *root)
{
    int ret = 0;

    /* if there is only one item in the list remove it */
    if (root->next == NULL) {
        ret = root->val;
        free(root);

        return ret;
    }

    /* get to the second to the last node in the list */
    struct node *current = root;

    while (current->next->next != NULL) {
        current = current->next;
    }

    /* 
     * now current points to the second to last item of the list, so let's
     * remove current->next
     */
    ret = current->next->val;
    free(current->next);
    current->next = NULL;

    return ret;
}

int pop_by_index(struct node **root, int idx)
{
    int i = 0;
    int ret = 0;
    struct node *current = *root;
    struct node *tmp_node = NULL;

    if (idx == 0) {
        return pop_front(root);
    }

    for (i = 0; i < idx - 1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }
    tmp_node = current->next;
    ret = tmp_node->val;
    current->next = tmp_node->next;
    free(tmp_node);

    return ret;
}

int pop_by_value(struct node **root, int val)
{
    if (*root == NULL) {
        return -1;
    }

    /* if element is at first position */
    if ((*root)->val == val) {
        return pop_front(root);
    }

    struct node *current = (*root)->next;
    struct node *previous = current;

    while (current != NULL) {
        if (current->val == val) {
            previous->next = current->next;
            free(current);
            return val;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

void free_list(struct node *root)
{
    struct node *current = root;
    struct node *next = root;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
