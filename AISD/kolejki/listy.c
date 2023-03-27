#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;
void dodaj(node **lista, int val);
void wypisz(node *lista);
void zwolnij(node *lista);
void wstaw(node **lista, int pozycja, int val);
void usun(node **lista, int pozycja);
void wypisz_odwrotnie(node *lista);


int main(void)
{
    node *nowy;
    node *lista = NULL;
    dodaj(&lista, 5);
    dodaj(&lista, 6);
    wstaw(&lista, 2, 3);
    wypisz(lista);
    printf("\n");
    wypisz_odwrotnie(lista);
    zwolnij(lista);

}


void zamien(node *lista, int poz1, int poz2)
{
    node *ptr1 = lista, *ptr2 = lista;
    for (int i = 0; i < poz1; i++)
    {
        if (ptr1 == NULL)
        {
            printf("Nie udało się znaleść pozycji 1.\n");
            return;
        }
        ptr1 = ptr1->next;
    }
    for (int i = 0; i < poz2; i++)
    {
        if (ptr2 == NULL)
        {
            printf("Nie udało się znaleść pozycji 2.\n");
            return;
        }
        ptr2 = ptr2->next;
    }

    //Zamieniamy
    node *temp = ptr1->next;
    node *temp2 = ptr2->next;
    
}

void wypisz_odwrotnie(node *lista)
{
    if (lista->next == NULL)
    {
        printf("%d\t", lista->val);
        return;
    }
    wypisz_odwrotnie(lista->next);
    printf("%d\t", lista->val);
}
void usun(node **lista, int pozycja)
{
    int obecna_poz = 0;
    node *ptr = *lista;
    if (pozycja == 0)
    {
        *lista = (*lista)->next;
        free(ptr);
        return;
    }
    while (1)
    {
        if (obecna_poz == pozycja - 1)
        {
            node *new_next = ptr->next->next;
            free(ptr->next);
            ptr->next = new_next;
            break;
        }
        obecna_poz ++;
        ptr = ptr->next;
    }
    
}

void wstaw(node **lista, int pozycja, int val)
{
    int obecna_poz = 0;
    node *nowy = malloc(sizeof(node));
    nowy->val = val;
    node *ptr = *lista;
    if (pozycja == 0)
    {
        nowy->next = *lista;
        *lista = nowy;
    }
    else
    {
        while (1)
        {
            if (obecna_poz == pozycja - 1)
            {
                nowy->next = ptr->next;
                ptr->next = nowy;
                break;
            }
            else if (ptr == NULL)
            {
                printf("Lista jest za krótka, nie udało się wstawić.\n");
                break;
            }
            obecna_poz++;
            ptr = ptr->next;
        }
    }
}

void dodaj(node **lista, int val)
{
    node *nowy = malloc(sizeof(node));
    node *ptr = *lista;
    nowy->val = val;
    nowy->next = NULL;
    while(1)
    {
        if (*lista == NULL)
        {
            *lista = nowy;
            break;
        }
        else if (ptr->next == NULL)
        {
            ptr->next = nowy;
            break;
        }
        ptr = ptr->next;
    }
}

void wypisz(node *lista)
{
    for(node *ptr = lista; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\t", ptr->val);
    }
}

void zwolnij(node *lista)
{
    node *ptr = lista, *next;
    while(ptr != NULL)
    {
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
}