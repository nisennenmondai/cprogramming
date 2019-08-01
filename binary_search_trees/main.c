/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  binary search tree
 *
 *        Version:  1.0
 *        Created:  08/01/2019 08:53:32 AM
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
    int data;                 /* value */
    struct node *left_child;  /* left child */
    struct node *right_child; /* right child */
};

/* function to create new node in the tree */
struct node *new_node(int data);

/* traversal algorithms */
void preorder(struct node *root); /* n->print, l->left subtree, r-> rightsubtree */
void inorder(struct node *root);  /* l->left subtree, n->print, r-> rightsubtree */
void postorder(struct node *root);/* l->left subtree, r->right subtree, n->print */

/* find min max */
struct node *find_min(struct node *root);
struct node *find_max(struct node *root);

/* tree queries */
struct node *insert(struct node *root, int val);
struct node *search(struct node *root, int val);
struct node *delete(struct node *root, int val);


int main(void)
{
    /* let's create our tree */
    /*
                   20
                 /    \
                /      \
               5       30
             /   \     /\
            /     \   /  \
           1      15 25  40
                /          \
               /            \
              9             45
            /   \          /
           /     \        /
          7      12      42
    */

    struct node *root;
    root = new_node(20);
    insert(root, 5);
    insert(root, 30);
    insert(root, 1);
    insert(root, 15);
    insert(root, 25);
    insert(root, 66);
    insert(root, 9);
    insert(root, 45);
    insert(root, 7);
    insert(root, 42);
    insert(root, 12);

    printf("\npreorder\n");
    preorder(root);
    printf("\n");

    printf("\ninorder\n");
    inorder(root);
    printf("\n");

    printf("\npostorder\n");
    postorder(root);
    printf("\n\n");

    printf("min %d\n", find_min(root)->data);
    printf("max %d\n\n", find_max(root)->data);

    printf("searching node 9\n");
    search(root, 9);
    printf("\n");

    printf("searching node 88\n");
    search(root, 88);
    printf("\n");

    printf("searching node 777\n");
    search(root, 777);
    printf("\n");

    printf("searching node 66\n");
    search(root, 66);
    printf("\n");

    delete(root, 9);
    delete(root, 45);
    delete(root, 30);
    delete(root, 66);

    printf("\ninorder\n");
    inorder(root);
    printf("\n");

    return 0;
}

struct node *new_node(int data)
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
        printf(" %d ", root->data);    /* N */
        preorder(root->left_child);    /* L */
        preorder(root->right_child);   /* R */
    } 
}

void inorder(struct node *root)
{
    if (root != NULL) {
        inorder(root->left_child);     /* L */
        printf(" %d ", root->data);    /* N */
        inorder(root->right_child);    /* R */
    }
}

void postorder(struct node *root)
{
    if (root != NULL) {
        postorder(root->left_child);   /* L */
        postorder(root->right_child);  /* R */
        printf(" %d ", root->data);    /* N */
    }
}

struct node *find_min(struct node *root)
{
    if (root == NULL)
        return NULL;
    /* node with min value will have no left child */
    else if (root->left_child != NULL)     
        /* left most element will be min */
        return find_min(root->left_child); 

    return root;
}

struct node *find_max(struct node *root)
{
    if (root == NULL)
        return NULL;
    /* node with max value will have no right child */
    else if (root->right_child != NULL)     
        /* right most element will be max */
        return find_max(root->right_child);

    return root;
}

struct node *insert(struct node *root, int val)
{
    /* searching for the place to insert */
    if (root == NULL)
        return new_node(val);

    else if (val > root->data) /* val is greater. should be inserted to right */
        root->right_child = insert(root->right_child, val);

    else /* val is smaller. should be inserted to left */
        root->left_child = insert(root->left_child, val);

    return root;
}

struct node *search(struct node *root, int val)
{
    if (root == NULL) {
        printf("node %d not found!\n", val);
        return NULL;
    }

    if (val == root->data) {
        printf("node %d found!\n", root->data);
        return root;
    }
    
    if (val > root->data)
        return search(root->right_child, val);

    else if (val < root->data)
        return search(root->left_child, val);

    return NULL;
}

struct node *delete(struct node *root, int val)
{
    if (root == NULL)
        return NULL;

    if (val > root->data)
        /* 
         * will traverse the tree recursively until the node is found and
         * return *tmp, therefore the parent will be assigned to his new child
         * after deletion, root->child = tmp (delete...)
         */
        root->right_child = delete(root->right_child, val);
    
    else if (val < root->data)
        root->left_child = delete(root->left_child, val);

    else {
        /* no children */
        if (root->left_child == NULL && root->right_child == NULL) {
            printf("deleting node %d\n", root->data);
            free(root);
            return NULL;

        } else if (root->left_child == NULL || root->right_child == NULL) {
        /* one child */
            struct node *tmp;
            if (root->left_child == NULL)
                tmp = root->right_child;
            else
                tmp = root->left_child;
            printf("deleting node %d\n", root->data);
            free(root);
            return tmp;

        } else {
        /* two children */
            struct node *tmp = find_min(root->right_child);
            root->data = tmp->data;
            root->right_child = delete(root->right_child, tmp->data);
        }
    }
    return root;
}
