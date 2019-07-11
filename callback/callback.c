#include <stdio.h>
#include <stdlib.h>

typedef void(* callback_t)(const char *data);
void print_helloworld(const char *data);
void print_byeworld(const char *data);

struct p_callback {
        callback_t foo;
        callback_t bar;
};

void register_cb_foo(struct p_callback *f, callback_t ptr);
void register_cb_bar(struct p_callback *f, callback_t ptr);

int main(void)
{
        struct p_callback *p = (struct p_callback*)malloc(sizeof(struct p_callback));
        const char *data = "nisennenmondai";
        register_cb_foo(p, print_helloworld);
        register_cb_bar(p, print_byeworld);
        p->foo(data);
        p->bar(data);
        free(p);

        return 0;
}

void print_helloworld(const char *data)
{
        printf("inside callback hello\n");
        printf("%s says hello callback\n", data);
}

void print_byeworld(const char *data)
{
        printf("inside callback bye\n");
        printf("%s says bye callback\n", data);
}

void register_cb_foo(struct p_callback *p, callback_t ptr)
{
        printf("registers callback hello\n");
        p->foo = ptr;
}

void register_cb_bar(struct p_callback *p, callback_t ptr)
{
        printf("registers callback bye\n");
        p->bar = ptr;
}
