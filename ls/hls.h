#ifndef MY_LS
#define MY_LS

#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdint.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * opt_list - singly linked list
 * => manage argument passed to 'ls' custom program
 * @str: option as a string (malloc'ed)
 * @len: length of the 'option'(str)
 * @next: pointer to next option instruction
*/

typedef struct opt_list
{
	char *str;
	unsigned int len;
	struct opt_list *next;
} opt_t;


/* LS CORE */
void display_dir(opt_t *nodes, int *options);
void display_local(char *head, int *opt);
void display_with_options(opt_t *nodes, int *opt, int multi);
void overload(struct dirent *entry, int *options);
opt_t *args_cooking(int argc, char *argv[], int *opt);
void print_long(struct dirent *entry);
void one_by_line(char *dir, int *options);

/*error*/
void handle_error(char *dir);

/* linked list stuff */
opt_t *add_node(opt_t **head, char *str);
void free_list(opt_t *head);


/* strings functions */
int _strcmp(char const *s1, char *s2);
int _strlen(const char *s);
char *_strncpy(char *dest, char const *src, int n);
char *_strdup(const char *str);



#endif
