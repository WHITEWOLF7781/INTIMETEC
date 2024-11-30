#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

int operation(int a, int b, char op)
{
    switch (op)
    {
    case '*':
        return a * b;
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '/':
        if (b == 0)
        {
            printf("Error dividing by zero\n");
            exit(0);
        }
        return a / b;
    default:
        return 0;
    }
}

int evaluate(char *exp)
{
    int numstack[MAX], topn = -1;
    char opstack[MAX], topo = -1;
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (isspace(exp[i]))
            continue;
        if (isdigit(exp[i]))
        {
            int x = 0;
            while (i < strlen(exp) && isdigit(exp[i]))
            {
                x = x * 10 + (exp[i++] - '0');
            }
            topn++;
            numstack[topn] = x;
            i--;
        }
        else if (strchr("+-*/", exp[i]))
        {
            while (topo >= 0 && precedence(opstack[topo]) >= precedence(exp[i]))
            {
                int y = numstack[topn--];
                int x = numstack[topn--];
                char op = opstack[topo--];
                topn++;
                numstack[topn] = operation(x, y, op);
            }
            topo++;
            opstack[topo] = exp[i];
        }
        else
        {
            printf("Error: Invalid expression.\n");
            return -1000000000;
        }
    }

    while (topo >= 0)
    {
        int b = numstack[topn--];
        int a = numstack[topn--];
        char op = opstack[topo--];
        numstack[++topn] = operation(a, b, op);
    }

    return numstack[topn];
}

int main()
{
    char expression[MAX];
    printf("Enter an expression: ");
    fgets(expression, MAX, stdin);
    int ans = evaluate(expression);
    if (ans != -1000000000)
    {
        printf("Answer: %d\n", ans);
    }
    return 0;
}
