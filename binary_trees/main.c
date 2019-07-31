/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  binary tree implementation
 *
 *        Version:  1.0
 *        Created:  07/31/2019 01:21:12 PM
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

struct node
{
    char data;                /* node will store character */
    struct node *left_child;  /* left child */
    struct node *right_child; /* right child */
};

/* function to create new node in the tree */
struct node *new_node(char data);

/* traversal */
void preorder(struct node *root); /* n->print, l->left subtree, r-> rightsubtree */
void inorder(struct node *root);  /* l->left subtree, n->print, r-> rightsubtree */
void postorder(struct node *root);/* l->left subtree, r->right subtree, n->print */

int is_leaf(struct node *a);    /* check if is a leaf */
int get_max(int a, int b);      /* return max of 2 numbers */
int get_height(struct node *a); /* compute the height of a tree or node */


int main(void)
{
    /* let's create our tree */
    struct node *root;

    root = new_node('D');
    /*
     ____
    |  D |
    |____|

    */

    root->left_child = new_node('A');
    /*
             ____
            |  D |
           /|____|
     ____ /
    |  A |
    |____|

    */

    root->right_child = new_node('F');
    /*
             ____
            |  D |
           /|____|\
     ____ /       _\___
    |  A |        |  F |
    |____|        |____|

    */

    root->left_child->left_child = new_node('E');
    /*
                     ____
                    |  D |
                   /|____|\
             ____ /       _\___
            |  A |        |  F |
           /|____|        |____|
      ____/
     |  E |
     |____|

    */

    root->left_child->right_child = new_node('B');
    /*
                     ____
                    |  D |
                   /|____|\
             ____ /       _\___
            |  A |        |  F |
           /|____|\       |____|
      ____/       _\___
     |  E |      |   B |
     |____|      |_____|

    */

    printf("\npreorder\n");
    preorder(root);
    printf("\n");

    printf("\ninorder\n");
    inorder(root);
    printf("\n");

    printf("\npostorder\n");
    postorder(root);
    printf("\n");

    printf("\nheigh of tree\n");
    printf("%d\n", get_height(root));

    printf("\nheigh of node A\n");
    printf("%d\n", get_height(root->left_child));

    printf("\nheigh of node B\n");
    printf("%d\n", get_height(root->left_child->right_child));

    return 0;
}

struct node *new_node(char data)
{
    struct node *p;
    p = (struct node*)malloc(sizeof(struct node));
    p->data = data;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

void preorder(struct node *root)
{
    if (root != NULL) {
        printf(" %c ", root->data);    /* N */
        preorder(root->left_child);    /* L */
        preorder(root->right_child);   /* R */
    } 
}

void inorder(struct node *root)
{
    if (root != NULL) {
        inorder(root->left_child);     /* L */
        printf(" %c ", root->data);    /* N */
        inorder(root->right_child);    /* R */
    }
}

void postorder(struct node *root)
{
    if (root != NULL) {
        postorder(root->left_child);   /* L */
        postorder(root->right_child);  /* R */
        printf(" %c ", root->data);    /* N */ 
    }
}

int is_leaf(struct node *a)
{
    if (a->left_child == NULL && a->right_child == NULL)
        return 1;

    return 0;
}

int get_max(int a, int b)
{
    return (a > b) ? a : b;
}

int get_height(struct node *a)
{
    if(a == NULL || is_leaf(a)) /* height will be 0 if the node is leaf or null */
        return 0;

    /* height of a node will be 1+ greater among height of right subtree and 
     * height of left subtree
     */
    return(get_max(get_height(a->left_child), get_height(a->right_child)) + 1);
}
