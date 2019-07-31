/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  double_pointers
 *
 *        Version:  1.0
 *        Created:  07/31/2019 09:26:45 AM
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


int main(void)
{
    int var1 = 10;
    int *p1 = NULL;
    int **p2 = NULL;

    p1 = &var1;
    printf("\n\np1 = &var1\n");
    printf("var1    %d\n&var1   %p\n\n", var1, &var1);
    printf("p1      %p\n&p1     %p\n\n", p1, &p1);

    p2 = &p1;
    printf("p2 = &p1\n");
    printf("p2      %p\n&p2     %p\n*p2     %p\n"
            "**p2    %d\n\n", p2, &p2, *p2, **p2);

    **p2 = 20;
    printf("**p2 = 20\n");
    printf("var1    %d\n&var1   %p\n\n", var1, &var1);

    *p2 = 0;
    printf("*p2 = 0\n");
    printf("p1      %p\n&p1     %p\n\n", p1, &p1);

    return 0;
}
