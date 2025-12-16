#include "vector.h"

vector vector_create(size_t elem_size)
{
    vector nuevo = {NULL, elem_size, 0, 0};
    return nuevo;
}

void vector_pushback(vector *arr, const __type__ valor)
{
    if (!arr)
        return;

    // Si no hay capacidad suficiente, aumentar
    if (arr->size >= arr->capacity)
    {
        size_t new_capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;

        void **new_arr = (void **)realloc(arr->arr, new_capacity * sizeof(void *));
        if (!new_arr)
        {
            perror("Error en realloc");
            exit(EXIT_FAILURE);
        }

        arr->arr = new_arr;
        arr->capacity = new_capacity;
    }

    // Asignar memoria para el nuevo elemento
    arr->arr[arr->size] = malloc(arr->elem_size);
    if (!arr->arr[arr->size])
    {
        perror("Error en malloc");
        exit(EXIT_FAILURE);
    }

    // Copiar los datos del valor
    memcpy(arr->arr[arr->size], valor, arr->elem_size);
    arr->size++;
}

void vector_pushfront(vector *arr, const __type__ valor)
{
    vector_insert(arr, 0, valor);
}

void vector_insert(vector *arr, size_t pos, const __type__ valor)
{
    if (!arr || pos > arr->size)
        return;

    // Si la posicion es al final, usar pushback
    if (pos == arr->size)
    {
        vector_pushback(arr, valor);
        return;
    }

    // Asegurar que hay capacidad
    if (arr->size >= arr->capacity)
    {
        size_t new_capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;

        void **new_arr = (void **)realloc(arr->arr, new_capacity * sizeof(void *));
        if (!new_arr)
        {
            perror("Error en realloc");
            exit(EXIT_FAILURE);
        }

        arr->arr = new_arr;
        arr->capacity = new_capacity;
    }

    // Crear espacio moviendo elementos hacia la derecha
    for (size_t i = arr->size; i > pos; i--)
    {
        arr->arr[i] = arr->arr[i - 1];
    }

    // Asignar memoria para el nuevo elemento
    arr->arr[pos] = malloc(arr->elem_size);
    if (!arr->arr[pos])
    {
        perror("Error en malloc");
        exit(EXIT_FAILURE);
    }

    // Copiar el valor
    memcpy(arr->arr[pos], valor, arr->elem_size);
    arr->size++;
}

void vector_popback(vector *arr)
{
    if (!arr || !arr->arr || arr->size == 0)
    {
        return;
    }

    free(arr->arr[arr->size - 1]);
    arr->arr[arr->size - 1] = NULL;
    arr->size--;

    // Reducir capacidad si es mucho mayor que el tamaño
    if (arr->capacity > arr->size * 2 && arr->capacity > 1)
    {
        size_t new_capacity = arr->capacity / 2;
        void **new_arr = (void **)realloc(arr->arr, new_capacity * sizeof(void *));
        if (new_arr)
        {
            arr->arr = new_arr;
            arr->capacity = new_capacity;
        }
    }
}

void vector_popfront(vector *arr)
{
    vector_erase(arr, 0);
}

void vector_erase(vector *arr, size_t pos)
{
    if (!arr || !arr->arr || arr->size == 0 || pos >= arr->size)
        return;

    // Liberar el elemento a eliminar
    free(arr->arr[pos]);

    // Mover elementos hacia adelante
    for (size_t i = pos; i < arr->size - 1; i++)
    {
        arr->arr[i] = arr->arr[i + 1];
    }

    arr->size--;
    arr->arr[arr->size] = NULL;

    // Reducir capacidad si es necesario
    if (arr->capacity > arr->size * 2 && arr->capacity > 1)
    {
        size_t new_capacity = arr->capacity / 2;
        void **new_arr = (void **)realloc(arr->arr, new_capacity * sizeof(void *));
        if (new_arr)
        {
            arr->arr = new_arr;
            arr->capacity = new_capacity;
        }
    }
}

int vector_empty(const vector *arr)
{
    return !arr || arr->size == 0;
}

size_t vector_size(const vector *arr)
{
    return arr ? arr->size : 0;
}

size_t vector_capacity(const vector *arr)
{
    return arr ? arr->capacity : 0;
}

__type__ vector_at(const vector *arr, size_t pos)
{
    if (!arr || !arr->arr || pos >= arr->size)
    {
        return NULL;
    }
    return arr->arr[pos];
}

__type__ vector_front(const vector *arr)
{
    return vector_at(arr, 0);
}

__type__ vector_back(const vector *arr)
{
    if (!arr || arr->size == 0)
    {
        return NULL;
    }
    return vector_at(arr, arr->size - 1);
}

void vector_set(vector *arr, size_t pos, const __type__ valor)
{
    if (!arr || !valor || !arr->arr)
    {
        return;
    }

    if (pos >= arr->size)
    {
        return;
    }
    memcpy(arr->arr[pos], valor, arr->elem_size);
}

void vector_reserve(vector *arr, size_t new_capacity)
{
    if (!arr || new_capacity <= arr->capacity)
    {
        return;
    }

    void **new_arr = (void **)realloc(arr->arr, new_capacity * sizeof(void *));
    if (!new_arr)
    {
        perror("Error en realloc (reserve)");
        exit(EXIT_FAILURE);
    }

    // Inicializar los nuevos punteros a NULL
    for (size_t i = arr->capacity; i < new_capacity; i++)
    {
        new_arr[i] = NULL;
    }

    arr->arr = new_arr;
    arr->capacity = new_capacity;
}

void vector_shrink_to_fit(vector *arr)
{
    if (!arr || arr->capacity == arr->size)
        return;

    if (arr->size == 0)
    {
        // Solo liberar si existe
        if (arr->arr)
        {
            free(arr->arr);
            arr->arr = NULL;
        }
        arr->capacity = 0;
    }
    else
    {
        void **new_arr = (void **)realloc(arr->arr, arr->size * sizeof(void *));
        if (new_arr)
        {
            arr->arr = new_arr;
            arr->capacity = arr->size;
        }
    }
}

void vector_clear(vector *arr)
{
    if (!arr || !arr->arr)
    {
        return;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->arr[i]) // Verificar antes de liberar
        {
            free(arr->arr[i]);
            arr->arr[i] = NULL;
        }
    }
    arr->size = 0;
}

void vector_free(vector *arr)
{
    if (!arr)
        return;

    // Liberar todos los elementos primero
    for (size_t i = 0; i < arr->size; i++)
    {
        free(arr->arr[i]);
    }

    // Liberar el array principal
    free(arr->arr);
    arr->arr = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

long vector_findb(const vector *vec, size_t nbyte, const __type__ valor)
{
    if (!vec || !vec->arr)
    {
        return -1;
    }

    for (size_t i = 0; i < vec->size; i++)
    {
        if (memcmp(vec->arr[i], valor, nbyte) == 0)
        {
            return i;
        }
    }
    return -1;
}

size_t vector_countb(const vector *vec, size_t nbyte, const __type__ valor)
{
    size_t count = 0;
    if (!vec || !vec->arr)
    {
        return count;
    }

    for (size_t i = 0; i < vec->size; i++)
    {
        if (memcmp(vec->arr[i], valor, nbyte) == 0)
        {
            count++;
        }
    }
    return count;
}

long vector_findf(const vector *vec, const __type__ valor, compar_func compare)
{
    if (!vec || !vec->arr || !compare)
    {
        return -1;
    }

    for (size_t i = 0; i < vec->size; i++)
    {
        if (compare(vec->arr[i], valor) == 0)
        {
            return i;
        }
    }
    return -1;
}

size_t vector_countf(const vector *vec, const __type__ valor, compar_func compare)
{
    size_t count = 0;
    if (!vec || !vec->arr || !compare)
    {
        return count;
    }

    for (size_t i = 0; i < vec->size; i++)
    {
        if (compare(vec->arr[i], valor) == 0)
        {
            count++;
        }
    }
    return count;
}

void vector_qsort(vector *vec, compar_func compare)
{
    if (!vec || !vec->arr || vec->size == 0 || !compare)
    {
        return;
    }

    qsort(vec->arr, vec->size, sizeof(void *), compare);
}

long vector_bsearch(const vector *vec, const __type__ valor, compar_func compare)
{
    if (!vec || !vec->arr || vec->size == 0 || !compare)
    {
        return -1;
    }

    void **result = (void **)bsearch(&valor, vec->arr, vec->size, sizeof(void *), compare);

    if (result)
    {
        // Calcular el índice
        return (result - vec->arr);
    }
    return -1;
}

void vector_reverse(vector *vec)
{
    if (!vec || !vec->arr || vec->size < 2)
    {
        return;
    }

    size_t i = 0, j = vec->size - 1;
    while (i < j)
    {
        void *temp = vec->arr[i];
        vec->arr[i] = vec->arr[j];
        vec->arr[j] = temp;
        i++;
        j--;
    }
}

void vector_foreach(vector *vec, func funcion)
{
    if (!vec || !funcion)
    {
        return;
    }

    for (size_t i = 0; i < vec->size; i++)
    {
        funcion(vec->arr[i]);
    }
}
