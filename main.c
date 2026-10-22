#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int main(void)
{
    char infix[MAX];
    char postfix[MAX * 2];
    char op[3];

    int i = 0, j = 0;
    int k, valid;
    size_t len;

    printf("Enter Infix: ");

    if (scanf("%99s", infix) != 1)
        return 1;

    len = strlen(infix);

    while (i < (int)len)
    {
        char c = infix[i];

        // Operand 
        if (isalnum((unsigned char)c))
        {
            postfix[j++] = c;
        }

        // opening bracket 
        else if (isOpening(c))
        {
            op[0] = c;
            op[1] = '\0';

            if (!push(op))
            {
                printf("Stack overflow\n");
                return 1;
            }
        }

        //Any closing bracket
        else if (isClosing(c))
        {
            /* Pop operators until an opening bracket */
            while (top != -1 &&
                   !isOpening(peek()[0]))
            {
                char *p = pop();

                for (k = 0; k < (int)strlen(p); k++)
                    postfix[j++] = p[k];
            }

            /* Check matching bracket */
            if (top == -1 ||
                !isMatching(peek()[0], c))
            {
                printf("Invalid brackets\n");
                return 1;
            }

            /* Remove opening bracket */
            pop();
        }

        /* 4. Operator */
        else
        {
            op[0] = c;
            op[1] = '\0';
            op[2] = '\0';

            /* Detect two-character operators */
            if (i + 1 < (int)len)
            {
                char n = infix[i + 1];

                if ((c == '&' && n == '&') ||
                    (c == '|' && n == '|') ||
                    (c == '>' && n == '=') ||
                    (c == '<' && n == '=') ||
                    (c == '=' && n == '=') ||
                    (c == '!' && n == '='))
                {
                    op[1] = n;
                    op[2] = '\0';
                    i++;
                }
            }

            /* Reject unsupported operators */
            if (precedence(op) == -1)
            {
                printf("Invalid character/operator: %s\n", op);
                return 1;
            }

            /* Pop operators with higher/equal precedence */
            while (top != -1 &&
                   !isOpening(peek()[0]) &&
                   precedence(peek()) >= precedence(op))
            {
                char *p = pop();

                for (k = 0; k < (int)strlen(p); k++)
                    postfix[j++] = p[k];
            }

            if (!push(op))
            {
                printf("Stack overflow\n");
                return 1;
            }
        }

        i++;
    }

    /* Pop remaining operators */
    while (top != -1)
    {
        char *p = pop();

        /* Opening bracket left over means mismatch */
        if (isOpening(p[0]))
        {
            printf("Invalid brackets\n");
            return 1;
        }

        for (k = 0; k < (int)strlen(p); k++)
            postfix[j++] = p[k];
    }

    postfix[j] = '\0';

    printf("Postfix: %s\n", postfix);

    return 0;
}