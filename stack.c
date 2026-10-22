
#include <string.h>
#include "stack.h"

char stack[MAX][3];
int top = -1;

int push(char *c)
{
    if (top >= MAX - 1)
        return 0;

    strcpy(stack[++top], c);
    return 1;
}

char *pop(void)
{
    if (top == -1)
        return NULL;

    return stack[top--];
}

char *peek(void)
{
    if (top == -1)
        return NULL;

    return stack[top];
}

int isOpening(char c)
{
    return c == '(' || c == '[' || c == '{';
}

int isClosing(char c)
{
    return c == ')' || c == ']' || c == '}';
}

int isMatching(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

int precedence(char *op)
{
    if (strcmp(op, "!") == 0) return 8;
    if (strcmp(op, "^") == 0) return 7;

    if (strcmp(op, "*") == 0 ||
        strcmp(op, "/") == 0 ||
        strcmp(op, "%") == 0)
        return 6;

    if (strcmp(op, "+") == 0 ||
        strcmp(op, "-") == 0)
        return 5;

    if (strcmp(op, ">") == 0 ||
        strcmp(op, "<") == 0 ||
        strcmp(op, ">=") == 0 ||
        strcmp(op, "<=") == 0)
        return 4;

    if (strcmp(op, "==") == 0 ||
        strcmp(op, "!=") == 0)
        return 3;

    if (strcmp(op, "&&") == 0 ||
        strcmp(op, "&") == 0)
        return 2;

    if (strcmp(op, "||") == 0 ||
        strcmp(op, "|") == 0)
        return 1;

    return -1;
}