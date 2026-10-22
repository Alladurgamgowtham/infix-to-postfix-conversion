stack.h

#define MAX 100

extern char stack[MAX][3];
extern int top;

int push(char *c);
char *pop(void);
char *peek(void);
int precedence(char *op);

int isOpening(char c);
int isClosing(char c);
int isMatching(char open, char close);