#include "list.h"

list new_list(size_t size_data)
{
    list new = {NULL, NULL, size_data, 0};
    return new;
}

nodo *new_nodo(void *dato, size_t size_data)
{
    if (!dato)
    {
        printf("Error: Dato nulo\n");
        return NULL;
    }

    nodo *new = (nodo *)malloc(sizeof(nodo));
    if (!new)
    {
        printf("Error: No se pudo asignar memoria para el nodo\n");
        return NULL;
    }

    new->elem = malloc(size_data);
    if (!new->elem)
    {
        free(new);
        printf("Error: No se pudo asignar memoria para el dato\n");
        return NULL;
    }

    memcpy(new->elem, dato, size_data);
    new->prox = NULL;

    return new;
}

void app_end(list *prime, void *data)
{
    if (!prime || !data)
    {
        printf("Error: Lista o dato nulo\n");
        return;
    }

    nodo *new = new_nodo(data, prime->size_data);
    if (!new)
        return;

    if (prime->head == NULL)
    {
        prime->head = new;
    }
    else
    {
        prime->tail->prox = new;
    }

    prime->tail = new;
    prime->size++;
}

void app_start(list *prime, void *data)
{
    if (!prime || !data)
    {
        printf("Error: Lista o dato nulo\n");
        return;
    }

    nodo *new = new_nodo(data, prime->size_data);
    if (!new)
        return;

    if (prime->head == NULL)
    {
        prime->head = new;
        prime->tail = new;
    }
    else
    {
        new->prox = prime->head;
        prime->head = new;
    }

    prime->size++;
}

void delete_start(list *prime)
{
    if (!prime || !prime->head)
    {
        printf("Error: Lista nula o vacia\n");
        return;
    }

    nodo *temp = prime->head;
    prime->head = prime->head->prox;

    free(temp->elem);
    free(temp);

    if (!prime->head)
    {
        prime->tail = NULL;
    }
    prime->size--;
}

void delete_end(list *prime)
{
    if (!prime || !prime->head)
    {
        printf("Error: Lista nula o vacia\n");
        return;
    }

    if (prime->head == prime->tail)
    {
        free(prime->head->elem);
        free(prime->head);
        prime->head = NULL;
        prime->tail = NULL;
        prime->size = 0;
        return;
    }

    nodo *actual = prime->head;
    while (actual->prox != prime->tail)
    {
        actual = actual->prox;
    }

    free(prime->tail->elem);
    free(prime->tail);
    prime->tail = actual;
    prime->tail->prox = NULL;
    prime->size--;
}

int delete_position(list *prime, int position)
{
    if (!prime || !prime->head || position < 0 || position >= prime->size)
    {
        printf("Error: Posicion invalida o lista vacia\n");
        return 0;
    }

    if (position == 0)
    {
        delete_start(prime);
        return 1;
    }

    if (position == prime->size - 1)
    {
        delete_end(prime);
        return 1;
    }

    nodo *anterior = prime->head;
    for (int i = 0; i < position - 1; i++)
    {
        anterior = anterior->prox;
    }

    nodo *temp = anterior->prox;
    anterior->prox = temp->prox;

    free(temp->elem);
    free(temp);
    prime->size--;
    return 1;
}

int delete_list(list *prime)
{
    if (!prime)
    {
        printf("Error: Lista nula\n");
        return 0;
    }

    nodo *actual = prime->head;
    nodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->prox;
        free(actual->elem);
        free(actual);
        actual = siguiente;
    }

    prime->head = NULL;
    prime->tail = NULL;
    prime->size = 0;
    return 1;
}

void *index_list(const list prime, int position)
{
    if (position < 0 || position >= prime.size || !prime.head)
    {
        printf("Error: Posicion invalida o lista vacia\n");
        return NULL;
    }

    if (position == 0)
    {
        return prime.head->elem;
    }

    if (position == prime.size - 1)
    {
        return prime.tail->elem;
    }

    nodo *aux = prime.head;
    for (int i = 0; i < position; i++)
    {
        aux = aux->prox;
    }
    return aux->elem;
}

void *end_list(const list prime)
{
    if (!prime.tail)
    {
        printf("Error: Lista vacia\n");
        return NULL;
    }
    return prime.tail->elem;
}

void *start_list(const list prime)
{
    if (!prime.head)
    {
        printf("Error: Lista vacia\n");
        return NULL;
    }
    return prime.head->elem;
}

int list_lenght(const list prime)
{
    return prime.size;
}

int list_is_empty(const list prime)
{
    return prime.head == NULL;
}

int reverse_list(list *prime)
{
    if (!prime)
    {
        printf("Error: Lista nula\n");
        return 0;
    }

    // Si la lista esta vacia o tiene un solo elemento, ya esta invertida
    if (!prime->head || prime->head == prime->tail)
    {
        return 1;
    }

    nodo *anterior = NULL;
    nodo *actual = prime->head;
    nodo *siguiente = NULL;

    // Guardar la cabeza original para luego asignarla como cola
    nodo *vieja_cabeza = prime->head;

    while (actual != NULL)
    {
        // Guardar el siguiente nodo
        siguiente = actual->prox;

        // Cambiar la direccion del puntero
        actual->prox = anterior;

        // Mover los punteros una posicion adelante
        anterior = actual;
        actual = siguiente;
    }

    // Actualizar cabeza y cola
    prime->head = anterior;     // anterior ahora es el ultimo nodo procesado (la nueva cabeza)
    prime->tail = vieja_cabeza; // la vieja cabeza ahora es la nueva cola

    return 1;
}

int modify_first(list *prime, void *new_data)
{
    if (!prime || !prime->head || !new_data)
    {
        printf("Error: Lista vacia o datos nulos\n");
        return 0;
    }

    // Copiar los nuevos datos al elemento existente
    memcpy(prime->head->elem, new_data, prime->size_data);
    return 1;
}

int modify_last(list *prime, void *new_data)
{
    if (!prime || !prime->tail || !new_data)
    {
        printf("Error: Lista vacia o datos nulos\n");
        return 0;
    }

    // Copiar los nuevos datos al elemento existente
    memcpy(prime->tail->elem, new_data, prime->size_data);
    return 1;
}

int modify_at(list *prime, int position, void *new_data)
{
    if (!prime || !prime->head || !new_data || position < 0 || position >= prime->size)
    {
        printf("Error: Parámetros inválidos\n");
        return 0;
    }

    // Caso especial: primer elemento
    if (position == 0)
    {
        return modify_first(prime, new_data);
    }

    // Caso especial: último elemento
    if (position == prime->size - 1)
    {
        return modify_last(prime, new_data);
    }

    // Buscar el nodo en la posición especificada
    nodo *actual = prime->head;
    for (int i = 0; i < position; i++)
    {
        actual = actual->prox;
    }

    // Copiar los nuevos datos al elemento existente
    memcpy(actual->elem, new_data, prime->size_data);
    return 1;
}
