#include "main.h"

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *input, int bool)
{
int i;

if (bool == 0)
{
for (i = 0; input[i]; i++)
{
if (input[i] == '|')
{
if (input[i + 1] != '|')
input[i] = 16;
else
i++;
}

if (input[i] == '&')
{
if (input[i + 1] != '&')
input[i] = 12;
else
i++;
}
}
}
else
{
for (i = 0; input[i]; i++)
{
input[i] = (input[i] == 16 ? '|' : input[i]);
input[i] = (input[i] == 12 ? '&' : input[i]);
}
}

return (input);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
int i;
char *line;

input = swap_char(input, 0);

for (i = 0; input[i]; i++)
{
if (input[i] == ';')
{
add_sep_node_end(head_s, input[i]);
i++;
}
else if (input[i] == '|' || input[i] == '&')
{
add_sep_node_end(head_s, input[i]);
i++;
}
}

line = strtok(input, ";|&");
do

{
line = swap_char(line, 1);
add_line_node_end(head_l, line);
line = strtok(NULL, ";|&");
} while (line != NULL);
}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
int loop_sep;
sep_list *ls_s;
line_list *ls_l;

loop_sep = 1;
ls_s = *list_s;
ls_l = *list_l;

while (ls_s != NULL && loop_sep)
{
if (datash->status == 0)
{
if (ls_s->separator == '&' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '|')
ls_l = ls_l->next, ls_s = ls_s->next;
}
else
{
if (ls_s->separator == '|' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '&')
ls_l = ls_l->next, ls_s = ls_s->next;
}
if (ls_s != NULL && !loop_sep)
ls_s = ls_s->next;
}

*list_s = ls_s;
*list_l = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{
sep_list *head_s = NULL, *list_s = NULL;
line_list *head_l = NULL, *list_l = NULL;
int loop;

add_nodes(&head_s, &head_l, input);

list_s = head_s;
list_l = head_l;

while (list_l != NULL)
{
datash->input = _strdup(list_l->line);
split_line(datash->args, datash->input);
loop = get_builtin(*datash);

go_next(&list_s, &list_l, datash);

if (loop == 0 && list_l->next == NULL)
break;
list_l = list_l->next;
}
free_sep_list(&head_s);
free_sep_list(&list_s);
free_line_list(&head_l);
free_sep_list(&list_l);

if (loop == 0)
return (0);
return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @input: input string.
 * @tokens : char**
 * Return: void
 */
void split_line(char **tokens, char *input)
{
char *token;

token = strtok(input, TOK_DELIM);
while (token != NULL)
{
*tokens = _strdup(token);
token = strtok(NULL, TOK_DELIM);
tokens++;
}
*tokens = NULL;
}
