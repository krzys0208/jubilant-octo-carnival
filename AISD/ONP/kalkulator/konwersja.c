#include "konwersja.h"

// Zwraca kolejkę z rowaniem w ONP
node * parseONP(const char *equation)
{
    node *out = NULL;
    node *stack = NULL;
    int i = 0;
    int num;
    while (equation[i] != '\0')
    {
        if (isdigit(equation[i]))
        {
            num = atoi(equation + i);
            enqueue(&out, num, integer);
            // Przesuwa i o długość liczby wczytanej z wejścia
            i += (int) log10(num);
        }
        else if (is_operation(equation[i]))
        {
            while (stack != NULL && priority(equation[i]) <= priority(top(&stack)) )
            {
                enqueue(&out, pop(&stack), operation);
            }
            push(&stack, equation[i]);
        }
        else if (equation[i] == '(')
        {
            push(&stack, equation[i]);
        }
        else if (equation[i] == ')')
        {
            int op;
            while (stack != NULL)
            {
                op = pop(&stack);
                if (op == '(')
                {
                    break;
                }
                else
                {
                    enqueue(&out, op, operation);
                }
            }
            if (stack == NULL && op != '(')
            {
                printf("Złe rownianie.\n");
                return NULL;
            }
        }
        i++;
    }
    while (stack != NULL)
    {
        int op = pop(&stack);
        if (op == '(' || op == ')')
        {
            printf("Złe rownianie.\n");
            return NULL;
        }
        enqueue(&out, op, operation);
    }
    if (out == NULL)
        {
            printf("Coś poszło nie tak.\n");
            return NULL;
        }
    return out;
}

int priority(const char c)
{
    if (c == '(')
        return 0;
    else if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/' || c == '%')
        return 2;
    else if (c == '^')
        return 3;
    else return -1;
}
int is_operation (const char c)
{
    char operations[] = "+-/*^%%";
    for (int i = 0; i < strlen(operations); i++)
    {
        if (c == operations[i])
            return 1;
    }
    return 0;
}

void queue_to_string(node **queue, char *output)
{
    node *temp;
    int i = 0;
    for (node *ptr = *queue; ptr != NULL; ptr = temp)
    {
        temp = ptr->next;
        if (ptr->type == integer)
        {
            sprintf(output + i, "%d ", ptr->value);
            i += (int) log10(ptr->value);
        }
        else
            sprintf(output + i, "%c ", ptr->value);
        free(ptr);
        i+=2;
    }
    *queue = NULL;
}