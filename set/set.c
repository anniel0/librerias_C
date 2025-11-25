#include "set.h"

setnodo *new_setnodo(void *elem, size_t data)
{
    if (!elem)
    {
        printf("Error: Dato nulo\n");
        return NULL;
    }

    setnodo *new = (setnodo *)malloc(sizeof(setnodo));
    if (!new)
    {
        printf("Error: No se pudo asignar memoria para el nodo\n");
        return NULL;
    }

    new->elem = malloc(data);
    if (!new->elem)
    {
        free(new);
        printf("Error: No se pudo asignar memoria para el dato\n");
        return NULL;
    }

    memcpy(new->elem, elem, data);
    new->prox = NULL;

    return new;
}

set new_set(size_t data)
{
    set s = {NULL, NULL, data, 0, NULL};
    return s;
}

set new_setin(size_t data, int (*pertain)(const void *, const void *))
{
    set s = {NULL, NULL, data, 0, pertain};
    return s;
}

int set_app(set *prime, void *elem)
{
    if (!prime || !elem)
    {
        printf("Error: conjunto o dato nulo\n");
        return 0;
    }

    if (set_pertain(prime, elem))
    {
        printf("Error: el elemento ya pertence al conjunto\n");
        return 0;
    }

    setnodo *new = new_setnodo(elem, prime->data);
    if (!new)
    {
        return 0;
    }

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
    return 1;
}

int set_pertain(const set *prime, void *elem)
{
    if (!prime || !elem || prime->head == NULL)
    {
        return 0;
    }

    setnodo *aux = prime->head;
    for (int i = 0; i < prime->size && aux != NULL; i++)
    {
        if (prime->pertain != NULL)
        {
            if (prime->pertain(aux->elem, elem) == 0)
            {
                return 1;
            }
        }
        else
        {
            if (memcmp(aux->elem, elem, prime->data) == 0)
            {
                return 1;
            }
        }
        aux = aux->prox;
    }
    return 0;
}

int set_empty(const set prime)
{
    return prime.head == NULL;
}

int set_size(const set prime)
{
    return prime.size;
}

set set_difference(const set *prime, const set *otro)
{

    set res = new_set(prime->data);

    setnodo *aux = prime->head;
    for (int i = 0; i < prime->size; i++)
    {
        if (!set_pertain(otro, aux->elem))
        {
            set_app(&res, aux->elem);
        }
        aux = aux->prox;
    }
    return res;
}

set set_union(const set *prime, const set *otro)
{

    set res = new_set(prime->data);
    setnodo *aux = prime->head;
    for (int i = 0; i < prime->size; i++)
    {
        set_app(&res, aux->elem);
        aux = aux->prox;
    }
    setnodo *aux1 = otro->head;
    for (int i = 0; i < otro->size; i++)
    {
        if (!set_pertain(&res, aux1->elem))
        {
            set_app(&res, aux1->elem);
        }
        aux1 = aux1->prox;
    }
    return res;
}

set set_intersection(const set *prime, const set *otro)
{
    set res = new_set(prime->data);
    setnodo *aux = prime->head;
    for (int i = 0; i < prime->size; i++)
    {
        if (set_pertain(otro, aux->elem))
        {
            set_app(&res, aux->elem);
        }
        aux = aux->prox;
    }

    return res;
}

int set_subset(const set *prime, const set *otro)
{
    setnodo *aux = otro->head;
    for (int i = 0; i < otro->size; i++)
    {
        if (!set_pertain(prime, aux->elem))
        {
            return 0;
        }
    }
    return 1;
}

void set_at(const set *prime, int position, void *elem)
{
    setnodo *aux = prime->head;
    for (int i = 0; i < position; i++)
    {
        aux = aux->prox;
    }
    memcpy(elem, aux->elem, prime->data);
}

int set_popat(set *prime, int position)
{
    if (!prime || prime->head == NULL)
    {
        printf("Error: conjunto vacio o nulo\n");
        return 0;
    }

    if (position < 0 || position >= prime->size)
    {
        printf("Error: posicion invalida\n");
        return 0;
    }

    setnodo *aux = prime->head;
    setnodo *prev = NULL;

    // Caso especial: eliminar el primer elemento
    if (position == 0)
    {
        prime->head = aux->prox;
        // Si era el único elemento, actualizar tail
        if (prime->tail == aux)
        {
            prime->tail = NULL;
        }
        free(aux->elem);
        free(aux);
        prime->size--;
        return 1;
    }

    // Buscar el nodo en la posición especificada
    for (int i = 0; i < position && aux != NULL; i++)
    {
        prev = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        return 0;
    }

    // Actualizar punteros
    prev->prox = aux->prox;

    // Si era el último elemento, actualizar tail
    if (prime->tail == aux)
    {
        prime->tail = prev;
    }

    free(aux->elem);
    free(aux);
    prime->size--;
    return 1;
}

int set_swap(set *prime, int pos1, int pos2)
{
    if (!prime || pos1 < 0 || pos1 >= prime->size ||
        pos2 < 0 || pos2 >= prime->size || pos1 == pos2)
    {
        printf("Error: posiciones invalidas\n");
        return 0;
    }

    // Encontrar los nodos en las posiciones especificadas
    setnodo *node1 = prime->head;
    setnodo *node2 = prime->head;

    for (int i = 0; i < pos1 && node1 != NULL; i++)
    {
        node1 = node1->prox;
    }

    for (int i = 0; i < pos2 && node2 != NULL; i++)
    {
        node2 = node2->prox;
    }

    if (!node1 || !node2)
    {
        return 0;
    }

    // Intercambiar los elementos
    void *temp = malloc(prime->data);
    if (!temp)
    {
        return 0;
    }

    memcpy(temp, node1->elem, prime->data);
    memcpy(node1->elem, node2->elem, prime->data);
    memcpy(node2->elem, temp, prime->data);

    free(temp);
    return 1;
}

int free_set(set *prime)
{
    if (!prime)
    {
        return 0;
    }

    setnodo *current = prime->head;
    while (current != NULL)
    {
        setnodo *next = current->prox;
        free(current->elem);
        free(current);
        current = next;
    }

    prime->head = NULL;
    prime->tail = NULL;
    prime->size = 0;
    return 1;
}

void **set_to_array(const set prime)
{
    if (prime.size == 0)
    {
        return NULL;
    }

    void **array = (void **)malloc(prime.size * sizeof(void *));
    if (!array)
    {
        return NULL;
    }

    setnodo *aux = prime.head;
    for (int i = 0; i < prime.size && aux != NULL; i++)
    {
        array[i] = malloc(prime.data);
        if (array[i])
        {
            memcpy(array[i], aux->elem, prime.data);
        }
        aux = aux->prox;
    }

    return array;
}

static void merge(void **arr, int left, int mid, int right, int (*compare)(const void *, const void *), size_t elem_size)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales
    void **L = (void **)malloc(n1 * sizeof(void *));
    void **R = (void **)malloc(n2 * sizeof(void *));

    if (!L || !R)
    {
        if (L)
            free(L);
        if (R)
            free(R);
        return;
    }

    // Copiar datos a los arreglos temporales
    for (i = 0; i < n1; i++)
    {
        L[i] = malloc(elem_size);
        if (L[i])
            memcpy(L[i], arr[left + i], elem_size);
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = malloc(elem_size);
        if (R[j])
            memcpy(R[j], arr[mid + 1 + j], elem_size);
    }

    // Fusionar los arreglos temporales
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (compare(L[i], R[j]) <= 0)
        {
            memcpy(arr[k], L[i], elem_size);
            i++;
        }
        else
        {
            memcpy(arr[k], R[j], elem_size);
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes
    while (i < n1)
    {
        memcpy(arr[k], L[i], elem_size);
        i++;
        k++;
    }

    while (j < n2)
    {
        memcpy(arr[k], R[j], elem_size);
        j++;
        k++;
    }

    // Liberar memoria temporal
    for (i = 0; i < n1; i++)
        free(L[i]);
    for (j = 0; j < n2; j++)
        free(R[j]);
    free(L);
    free(R);
}

static void mergeSort(void **arr, int left, int right, int (*compare)(const void *, const void *), size_t elem_size)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, compare, elem_size);
        mergeSort(arr, mid + 1, right, compare, elem_size);
        merge(arr, left, mid, right, compare, elem_size);
    }
}

void set_msort(set *prime, int (*compare)(const void *, const void *))
{
    if (!prime || !compare || prime->size <= 1)
    {
        return;
    }

    // Convertir a arreglo
    void **array = set_to_array(*prime);
    if (!array)
    {
        return;
    }

    // Ordenar el arreglo
    mergeSort(array, 0, prime->size - 1, compare, prime->data);

    // Actualizar el conjunto con el arreglo ordenado
    setnodo *current = prime->head;
    for (int i = 0; i < prime->size && current != NULL; i++)
    {
        memcpy(current->elem, array[i], prime->data);
        current = current->prox;
    }

    // Liberar el arreglo temporal
    for (int i = 0; i < prime->size; i++)
    {
        free(array[i]);
    }
    free(array);
}

set array_to_set(void *arr, int size, size_t data_size)
{
    set s = new_set(data_size);

    if (!arr || size <= 0)
    {
        return s;
    }

    char *byte_arr = (char *)arr;
    for (int i = 0; i < size; i++)
    {
        void *element = byte_arr + (i * data_size);
        set_app(&s, element);
    }

    return s;
}

static void mergeb(void **arr, int left, int mid, int right, size_t elem_size)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear arreglos temporales
    void **L = (void **)malloc(n1 * sizeof(void *));
    void **R = (void **)malloc(n2 * sizeof(void *));

    if (!L || !R)
    {
        if (L)
            free(L);
        if (R)
            free(R);
        return;
    }

    // Copiar datos a los arreglos temporales
    for (i = 0; i < n1; i++)
    {
        L[i] = malloc(elem_size);
        if (L[i])
            memcpy(L[i], arr[left + i], elem_size);
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = malloc(elem_size);
        if (R[j])
            memcpy(R[j], arr[mid + 1 + j], elem_size);
    }

    // Fusionar los arreglos temporales
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (memcmp(L[i], R[j], elem_size) <= 0)
        {
            memcpy(arr[k], L[i], elem_size);
            i++;
        }
        else
        {
            memcpy(arr[k], R[j], elem_size);
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes
    while (i < n1)
    {
        memcpy(arr[k], L[i], elem_size);
        i++;
        k++;
    }

    while (j < n2)
    {
        memcpy(arr[k], R[j], elem_size);
        j++;
        k++;
    }

    // Liberar memoria temporal
    for (i = 0; i < n1; i++)
        free(L[i]);
    for (j = 0; j < n2; j++)
        free(R[j]);
    free(L);
    free(R);
}

static void mergeSortb(void **arr, int left, int right, size_t elem_size)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortb(arr, left, mid, elem_size);
        mergeSortb(arr, mid + 1, right, elem_size);
        mergeb(arr, left, mid, right, elem_size);
    }
}

void set_msortb(set *prime)
{
    if (!prime || prime->size <= 1)
    {
        return;
    }

    // Convertir a arreglo
    void **array = set_to_array(*prime);
    if (!array)
    {
        return;
    }

    // Ordenar el arreglo
    mergeSortb(array, 0, prime->size - 1, prime->data);

    // Actualizar el conjunto con el arreglo ordenado
    setnodo *current = prime->head;
    for (int i = 0; i < prime->size && current != NULL; i++)
    {
        memcpy(current->elem, array[i], prime->data);
        current = current->prox;
    }

    // Liberar el arreglo temporal
    for (int i = 0; i < prime->size; i++)
    {
        free(array[i]);
    }
    free(array);
}

set set_filter(const set *prime, int (*filter)(const void *))
{

    set res = new_set(prime->size);

    setnodo *aux = prime->head;
    for (size_t i = 0; i < prime->size; i++)
    {
        if (filter(aux->elem) == 0)
        {
            set_app(&res, aux->elem);
        }
        aux = aux->prox;
    }

    return res;
}
