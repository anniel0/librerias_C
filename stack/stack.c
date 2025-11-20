#include "stack.h"

stack new_stack(size_t size_data)
{
    stack new = {NULL, size_data, 0};
    return new;
}

snodo *new_snodo(void *dato, size_t size_data)
{
    if (!dato)
    {
        printf("Error: Dato nulo\n");
        return NULL;
    }

    snodo *new = (snodo *)malloc(sizeof(snodo));
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

int push(stack *s, void *data)
{
    if (!s || !data)
    {
        printf("Error: Pila o dato nulo\n");
        return 0;
    }

    snodo *new = new_snodo(data, s->size_data);
    if (!new)
        return 0;

    // Insertar en la cima (como en una lista enlazada simple)
    new->prox = s->top;
    s->top = new;
    s->size++;

    return 1;
}

int pop(stack *s)
{
    if (!s || !s->top)
    {
        printf("Error: Pila nula o vacia\n");
        return 0;
    }

    snodo *temp = s->top;
    s->top = s->top->prox;

    free(temp->elem);
    free(temp);
    s->size--;

    return 1;
}

void *stack_top(const stack s)
{
    if (!s.top)
    {
        printf("Error: Pila vacia\n");
        return NULL;
    }
    return s.top->elem;
}

int stack_size(const stack s)
{
    return s.size;
}

int stack_is_empty(const stack s)
{
    return s.top == NULL;
}

int stack_clear(stack *s)
{
    if (!s)
    {
        printf("Error: Pila nula\n");
        return 0;
    }

    snodo *actual = s->top;
    snodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->prox;
        free(actual->elem);
        free(actual);
        actual = siguiente;
    }

    s->top = NULL;
    s->size = 0;
    return 1;
}

void stack_traverse(const stack s, void (*callback)(void *))
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    snodo *actual = s.top;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->prox;
    }
}

int stack_search(const stack s, void *data, int (*compare)(const void *, const void *))
{
    if (!data || !compare)
    {
        printf("Error: Datos o funcion de comparacion nulos\n");
        return 0;
    }

    snodo *actual = s.top;
    while (actual != NULL)
    {
        if (compare(actual->elem, data) == 0)
        {
            return 1; // Encontrado
        }
        actual = actual->prox;
    }

    return 0; // No encontrado
}

int stack_copy(const stack src, stack *dest)
{
    if (!dest)
    {
        printf("Error: Pila destino nula\n");
        return 0;
    }

    // Limpiar la pila destino si no está vacía
    if (!stack_is_empty(*dest))
    {
        stack_clear(dest);
    }

    // Para copiar una pila necesitamos invertir temporalmente
    stack temp = new_stack(src.size_data);
    snodo *actual = src.top;

    // Primero copiar a una pila temporal (esto invierte el orden)
    while (actual != NULL)
    {
        if (!push(&temp, actual->elem))
        {
            stack_clear(&temp);
            return 0;
        }
        actual = actual->prox;
    }

    // Luego copiar de la temporal a la destino (recupera el orden original)
    actual = temp.top;
    while (actual != NULL)
    {
        if (!push(dest, actual->elem))
        {
            stack_clear(&temp);
            stack_clear(dest);
            return 0;
        }
        actual = actual->prox;
    }

    stack_clear(&temp);
    return 1;
}

int stack_reverse(stack *s)
{
    if (!s)
    {
        printf("Error: Pila nula\n");
        return 0;
    }

    if (stack_is_empty(*s) || s->top->prox == NULL)
    {
        // Pila vacia o con un solo elemento, ya esta invertida
        return 1;
    }

    stack temp = new_stack(s->size_data);
    snodo *actual = s->top;

    // Vaciar la pila original en la temporal (esto invierte el orden)
    while (actual != NULL)
    {
        if (!push(&temp, actual->elem))
        {
            stack_clear(&temp);
            return 0;
        }
        actual = actual->prox;
    }

    // Limpiar la original y copiar de vuelta
    stack_clear(s);

    actual = temp.top;
    while (actual != NULL)
    {
        if (!push(s, actual->elem))
        {
            stack_clear(&temp);
            stack_clear(s);
            return 0;
        }
        actual = actual->prox;
    }

    stack_clear(&temp);
    return 1;
}