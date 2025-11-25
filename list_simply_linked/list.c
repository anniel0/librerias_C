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
        prime->head = new;
    }
    else
    {
        prime->tail->prox = new;
    }

    prime->tail = new;
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

void list_popstart(list *prime)
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

void list_popend(list *prime)
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

int list_popat(list *prime, int position)
{
    if (!prime || !prime->head || position < 0 || position >= prime->size)
    {
        printf("Error: Posicion invalida o lista vacia\n");
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

int free_list(list *prime)
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

void *list_see(const list prime, int position)
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

int list_lenght(const list prime)
{
    return prime.size;
}

int list_is_empty(const list prime)
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

int list_setfirst(list *prime, void *new_data)
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

int list_setlast(list *prime, void *new_data)
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

int list_setall(list *prime, int position, void *new_data)
{
    if (!prime || !prime->head || !new_data || position < 0 || position >= prime->size)
    {
        printf("Error: Parámetros inválidos\n");
        return 0;
    }

    // Caso especial: primer elemento
    if (position == 0)
    {
        return list_setfirst(prime, new_data);
    }

    // Caso especial: último elemento
    if (position == prime->size - 1)
    {
        return list_setlast(prime, new_data);
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

void **list_arrays(const list *prime)
{
    if (prime->size == 0)
    {
        return NULL;
    }

    void **array = (void **)malloc(prime->size * sizeof(void *));
    if (!array)
    {
        return NULL;
    }

    nodo *aux = prime->head;
    for (int i = 0; i < prime->size && aux != NULL; i++)
    {
        array[i] = malloc(prime->size_data);
        if (array[i])
        {
            memcpy(array[i], aux->elem, prime->size_data);
        }
        aux = aux->prox;
    }

    return array;
}

list array_list(void *arr, int size, size_t data_size)
{
    list s = new_list(data_size);

    if (!arr || size <= 0)
    {
        return s;
    }

    char *byte_arr = (char *)arr;
    for (int i = 0; i < size; i++)
    {
        void *element = byte_arr + (i * data_size);
        list_append(&s, element);
    }

    return s;
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

void list_msort(list *prime, int (*compare)(const void *, const void *))
{
    if (!prime || !compare || prime->size <= 1)
    {
        return;
    }

    // Convertir a arreglo
    void **array = list_arrays(prime);
    if (!array)
    {
        return;
    }

    // Ordenar el arreglo
    mergeSort(array, 0, prime->size - 1, compare, prime->size_data);

    // Actualizar el conjunto con el arreglo ordenado
    nodo *current = prime->head;
    for (int i = 0; i < prime->size && current != NULL; i++)
    {
        memcpy(current->elem, array[i], prime->size_data);
        current = current->prox;
    }

    // Liberar el arreglo temporal
    for (int i = 0; i < prime->size; i++)
    {
        free(array[i]);
    }
    free(array);
}

void list_msortb(list *prime)
{
    if (!prime || prime->size <= 1)
    {
        return;
    }

    // Convertir a arreglo
    void **array = list_arrays(prime);
    if (!array)
    {
        return;
    }

    // Ordenar el arreglo
    mergeSortb(array, 0, prime->size - 1, prime->size_data);

    // Actualizar el conjunto con el arreglo ordenado
    nodo *current = prime->head;
    for (int i = 0; i < prime->size && current != NULL; i++)
    {
        memcpy(current->elem, array[i], prime->size_data);
        current = current->prox;
    }

    // Liberar el arreglo temporal
    for (int i = 0; i < prime->size; i++)
    {
        free(array[i]);
    }
    free(array);
}

int list_count(const list *prime, void *elem)
{
    if (!prime->head || !elem)
    {
        return 0;
    }

    nodo *aux = prime->head;
    int count = 0;
    for (int i = 0; i < prime->size; i++)
    {
        if (memcmp(aux->elem, elem, prime->size_data) == 0)
        {
            count++;
        }
    }

    return count;
}

int list_index(const list *prime, void *elem)
{
    if (!prime->head || !elem)
    {
        return -1;
    }

    nodo *aux = prime->head;
    for (int i = 0; i < prime->size; i++)
    {
        if (memcmp(aux->elem, elem, prime->size_data) == 0)
        {
            return i;
        }
    }

    return -1;
}

list list_filter(const list *prime, int (*filter)(const void *))
{
    list res = new_list(prime->size_data);

    nodo *aux = prime->head;

    for (int i = 0; i < prime->size; i++)
    {
        if (filter(aux->elem) == 0)
        {
            list_append(&res, aux->elem);
        }
        aux = aux->prox;
    }

    return res;
}
