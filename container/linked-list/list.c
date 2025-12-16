#include "list.h"

list new_list(size_t size_data)
{
    list new = {NULL, NULL, size_data, 0, NULL};
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
    new->ant = NULL;

    return new;
}

void list_append(list *prime, void *data)
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
        // Lista vacía
        prime->head = new;
        prime->tail = new;
    }
    else
    {
        // Lista no vacía
        new->ant = prime->tail;
        prime->tail->prox = new;
        prime->tail = new;
    }

    prime->size++;
}

void list_appstart(list *prime, void *data)
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
        // Lista vacia
        prime->head = new;
        prime->tail = new;
    }
    else
    {
        // Lista no vacía
        new->prox = prime->head;
        prime->head->ant = new;
        prime->head = new;
    }

    prime->size++;
}

void list_popstart(list *prime)
{
    if (!prime || !prime->head)
    {
        printf("Error: Lista nula o vacía\n");
        return;
    }

    nodo *temp = prime->head;

    if (prime->head == prime->tail)
    {
        // Solo un elemento
        prime->head = NULL;
        prime->tail = NULL;
    }
    else
    {
        // Múltiples elementos
        prime->head = prime->head->prox;
        prime->head->ant = NULL;
    }

    free(temp->elem);
    free(temp);
    prime->size--;
}

void list_popend(list *prime)
{
    if (!prime || !prime->head)
    {
        printf("Error: Lista nula o vacía\n");
        return;
    }

    nodo *temp = prime->tail;

    if (prime->head == prime->tail)
    {
        // Solo un elemento
        prime->head = NULL;
        prime->tail = NULL;
    }
    else
    {
        // Múltiples elementos
        prime->tail = prime->tail->ant;
        prime->tail->prox = NULL;
    }

    free(temp->elem);
    free(temp);
    prime->size--;
}

int list_pop(list *prime, int position)
{
    if (!prime || !prime->head || position < 0 || position >= prime->size)
    {
        printf("Error: Posición inválida o lista vacía\n");
        return 0;
    }

    if (position == 0)
    {
        list_popstart(prime);
        return 1;
    }

    if (position == prime->size - 1)
    {
        list_popend(prime);
        return 1;
    }

    // Buscar el nodo en la posición especificada
    nodo *actual = prime->head;
    for (int i = 0; i < position; i++)
    {
        actual = actual->prox;
    }

    // Reenlazar los nodos adyacentes
    actual->ant->prox = actual->prox;
    actual->prox->ant = actual->ant;

    free(actual->elem);
    free(actual);
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

void *list_at(const list prime, int position)
{
    if (position < 0 || position >= prime.size || !prime.head)
    {
        printf("Error: Posicion invalida o lista vacia\n");
        return NULL;
    }

    // Optimizacion: decidir desde donde empezar a buscar
    if (position < prime.size / 2)
    {
        // Buscar desde el inicio
        nodo *aux = prime.head;
        for (int i = 0; i < position; i++)
        {
            aux = aux->prox;
        }
        return aux->elem;
    }
    else
    {
        // Buscar desde el final
        nodo *aux = prime.tail;
        for (int i = prime.size - 1; i > position; i--)
        {
            aux = aux->ant;
        }
        return aux->elem;
    }
}

void *list_end(const list prime)
{
    if (!prime.tail)
    {
        printf("Error: Lista vacia\n");
        return NULL;
    }
    return prime.tail->elem;
}

void *list_start(const list prime)
{
    if (!prime.head)
    {
        printf("Error: Lista vacia\n");
        return NULL;
    }
    return prime.head->elem;
}

int list_length(const list prime)
{
    return prime.size;
}

int list_empty(const list prime)
{
    return prime.head == NULL;
}

int list_reverse(list *prime)
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

    nodo *actual = prime->head;
    nodo *temp = NULL;

    // Intercambiar cabeza y cola
    prime->head = prime->tail;
    prime->tail = actual;

    // Invertir los punteros de cada nodo
    while (actual != NULL)
    {
        temp = actual->ant;
        actual->ant = actual->prox;
        actual->prox = temp;
        actual = actual->ant; // Moverse al siguiente (que era el anterior)
    }

    return 1;
}

int list_setfirst(list *prime, void *new_data)
{
    if (!prime || !prime->head || !new_data)
    {
        printf("Error: Lista vacia o datos nulos\n");
        return 0;
    }

    memcpy(prime->head->elem, new_data, prime->size_data);
    return 1;
}

int list_setlast(list *prime, void *new_data)
{
    if (!prime || !prime->tail || !new_data)
    {
        printf("Error: Lista vacia o datos nulos\n");
        return 0;
    }

    memcpy(prime->tail->elem, new_data, prime->size_data);
    return 1;
}

int list_set(list *prime, int position, void *new_data)
{
    if (!prime || !prime->head || !new_data || position < 0 || position >= prime->size)
    {
        printf("Error: Parametros invalidos\n");
        return 0;
    }

    if (position == 0)
    {
        return list_setfirst(prime, new_data);
    }

    if (position == prime->size - 1)
    {
        return list_setlast(prime, new_data);
    }

    // Buscar el nodo de manera óptima
    nodo *actual;
    if (position < prime->size / 2)
    {
        actual = prime->head;
        for (int i = 0; i < position; i++)
        {
            actual = actual->prox;
        }
    }
    else
    {
        actual = prime->tail;
        for (int i = prime->size - 1; i > position; i--)
        {
            actual = actual->ant;
        }
    }

    memcpy(actual->elem, new_data, prime->size_data);
    return 1;
}

int list_insert(list *prime, int position, void *data)
{
    if (!prime || !data || position < 0 || position > prime->size)
    {
        printf("Error: Parametros invalidos\n");
        return 0;
    }

    if (position == 0)
    {
        list_appstart(prime, data);
        return 1;
    }

    if (position == prime->size)
    {
        list_append(prime, data);
        return 1;
    }

    // Crear nuevo nodo
    nodo *new = new_nodo(data, prime->size_data);
    if (!new)
    {
        return 0;
    }

    // Buscar la posicion de insercion (de manera optima)
    nodo *actual;
    if (position < prime->size / 2)
    {
        actual = prime->head;
        for (int i = 0; i < position; i++)
        {
            actual = actual->prox;
        }
    }
    else
    {
        actual = prime->tail;
        for (int i = prime->size - 1; i >= position; i--)
        {
            actual = actual->ant;
        }
    }

    // Insertar el nuevo nodo
    new->prox = actual;
    new->ant = actual->ant;
    actual->ant->prox = new;
    actual->ant = new;

    prime->size++;
    return 1;
}

void list_forward(list *prime, void (*callback)(void *))
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    nodo *actual = prime->head;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->prox;
    }
}

void list_backward(list *prime, void (*callback)(void *))
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    nodo *actual = prime->tail;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->ant;
    }
}

long list_findf(const list *this, size_t sizevar, void *valor, int (*compare)(void *, void *))
{
    if (!this || !this->head || !compare || !valor)
    {
        printf("Error\n");
        return 0;
    }
    nodo *aux = this->head;
    size_t i = 0;
    while (aux != NULL)
    {
        if (compare(aux->elem, valor))
        {
            return i;
        }
        i++;
        aux = aux->prox;
    }
    return -1;
}

size_t list_countf(const list *this, size_t sizevar, void *valor, int (*compare)(void *, void *))
{
    if (!this || !this->head || !compare || !valor)
    {
        printf("Error\n");
        return 0;
    }
    nodo *aux = this->head;
    size_t i = 0;
    while (aux != NULL)
    {
        if (compare(aux->elem, valor))
        {
            i++;
        }
        aux = aux->prox;
    }
    return i;
}

list list_filter(const list *this, int (*filter)(void *))
{
    if (!this || !filter)
    {
        printf("Error: Parámetros inválidos\n");
        return new_list(0); // Retorna lista vacía con tamaño 0
    }

    list result = new_list(this->size_data); // Usar size_data, no size
    if (this->size_data == 0)
        return result;

    nodo *aux = this->head;
    while (aux != NULL)
    {
        if (filter(aux->elem))
        {
            list_append(&result, aux->elem);
        }
        aux = aux->prox;
    }
    return result;
}

list list_str(const char *s)
{
    list this = new_list(sizeof(char));
    if (!s)
        return this;

    while (*s != '\0')
    {
        char letra = *s;
        list_append(&this, &letra);
        s++; // CORREGIDO: incremento correcto
    }
    return this;
}

void list_print(const list *this, void (*print)(void *))
{
    if (!this || !print)
    {
        printf("Error: Parámetros inválidos\n");
        return;
    }

    printf("[");
    nodo *aux = this->head;
    while (aux != NULL)
    {
        print(aux->elem);
        if (aux->prox != NULL) // CORREGIDO: solo verificar prox, no prox->prox
        {
            printf(", ");
        }
        aux = aux->prox;
    }
    printf("]\n");
}

void list_printf(const list *this, const char *format)
{
    if (!this || !format)
    {
        printf("Error: Parametros invalidos\n");
        return;
    }

    printf("[");
    nodo *aux = this->head;
    while (aux != NULL)
    {
        if (this->size_data == sizeof(int))
        {
            printf(format, *((int *)aux->elem));
        }
        else if (this->size_data == sizeof(char))
        {
            printf(format, *((char *)aux->elem));
        }
        else if (this->size_data == sizeof(float))
        {
            printf(format, *((float *)aux->elem));
        }
        else if (this->size_data == sizeof(double))
        {
            printf(format, *((double *)aux->elem));
        }
        else
        {
            printf("%p", aux->elem);
        }

        if (aux->prox != NULL)
        {
            printf(", ");
        }
        aux = aux->prox;
    }
    printf("]\n");
}

long list_findb(const list *this, size_t sizevar, void *valor)
{
    if (!this || !this->head || !valor)
    {
        printf("Error: Parámetros inválidos\n");
        return -1;
    }
    nodo *aux = this->head;
    long i = 0;
    while (aux != NULL)
    {
        if (memcmp(aux->elem, valor, sizevar) == 0)
        {
            return i;
        }
        i++;
        aux = aux->prox;
    }
    return -1;
}

size_t list_countb(const list *this, size_t sizevar, void *valor)
{
    if (!this || !this->head || !valor)
    {
        printf("Error: Parámetros inválidos\n");
        return 0;
    }
    nodo *aux = this->head;
    size_t count = 0;
    while (aux != NULL)
    {
        if (memcmp(aux->elem, valor, sizevar) == 0)
        {
            count++;
        }
        aux = aux->prox;
    }
    return count;
}