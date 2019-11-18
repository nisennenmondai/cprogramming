/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  basic shell in C following this tutorial
 *                  https://brennan.io/2015/01/16/write-a-shell-in-c/
 *
 *        Version:  1.0
 *        Created:  11/14/2019 09:33:53 AM
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
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define LSH_RL_BUFFSIZE 1024
#define LSH_TOK_BUFFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/******************************************************************************
 * BUILT IN FUNCTION
 ******************************************************************************/

/* those functions do not need arguments for now */
int lsh_help(char **args);
int lsh_exit(char **args);

/* list of builtin commands */
char *builtin_cmd[] = {
    "help",
    "exit"
};

/* list of function pointers */
int (*builtin_func[]) (char **args) = {
    &lsh_help,
    &lsh_exit
};

/* return number of builtin function */
int lsh_num_builtins() {
    return sizeof(builtin_cmd) / sizeof(char *);
}

/* builtin function implementation */
int lsh_help(char **args)
{
    int i;
    printf("nisennenmondai's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++) {
        printf("  %s\n", builtin_cmd[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}



char *lsh_read_line(void)
{
    int buffsize = LSH_RL_BUFFSIZE;
    int position = 0;
    char *buffer = (char*)malloc(buffsize * sizeof(char));
    int c;

    /* check if buffer has been allocated */
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* read line */
    while (1) {
        /* use of function getline is much easier */
        c = getchar();

        /* if we hit EOF, replace it with a null character and return */
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        /* if we have exceeded the buffer, reallocate */
        if (position >= buffsize) {
            buffsize += LSH_RL_BUFFSIZE;
            buffer = realloc(buffer, buffsize);

            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
            }
        }
    }
}

char **lsh_split_line(char *line)
{
    int buffsize = LSH_TOK_BUFFSIZE;
    int position = 0;
    char **tokens = malloc(buffsize * sizeof(char*));
    char *token;

    /* check if buffer has been allocated */
    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* get the first argument (char*) */
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        /* put the token inside the array of pointers */
        tokens[position] = token;
        /* go to next index */
        position++;

        /* check if buffer overflow, then allocate more memory */
        if (position >= buffsize) {
            buffsize += LSH_TOK_BUFFSIZE;
            tokens = realloc(tokens, buffsize);

            if (!tokens) {
                fprintf(stderr, "lsh: alloation error\n");
                exit(EXIT_FAILURE);
            }
        }
        /* parse the next argument and jump back to the top of while loop */
        token  = strtok(NULL, LSH_TOK_DELIM);
    }
    /* parsing is done end the array with a NULL pointer */
    tokens[position] = NULL;
    return tokens;
}

/* this function launches a process */
int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        /* child process, execute program by providing filename, vector args */
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* forking error */
        perror("lsh");
    } else {
        /* parent process */
        do {
            /* wait for child process to finish by checking status */
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    /* returns a 1 as a signal to the calling func that we should prompt for
     * input again */
    return 1;
}

/* this function execute a builtin function */
int lsh_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        /* An empty command was entered. */
        return 1;
    }

    /* check if command equals a builtin function and execute it, if not then
     * launch a process */
    for (i = 0; i < lsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_cmd[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return lsh_launch(args);
}

/* loop getting input and executing it */
void lsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv)
{
    /* load config file if any */

    /* run command loop */
    lsh_loop();

    /* perform any shutdown/cleanup */
    return 0;
}
