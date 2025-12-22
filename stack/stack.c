#include "stack.h"

stack stack_create(size_t size_data)
{
    stack new = {NULL, size_data, 0};
    return new;
}

static snodo *new_snodo(const void *dato, size_t size_data)
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

int stack_push(stack *s, const void *data)
{
    if (!s || !data)
    {
        printf("Error: Pila o dato nulo\n");
        return 0;
    }

    snodo *new = new_snodo(data, s->size_data);
    if (!new)
    {
        return 0;
    }

    new->prox = s->top;
    s->top = new;
    s->size++;

    return 1;
}

int stack_pop(stack *s)
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

int stack_top(const stack *s, void *output)
{
    if (!s || !s->top || !output)
    {
        printf("Error: Pila nula, vacia o output nulo\n");
        return 0;
    }

    memcpy(output, s->top->elem, s->size_data);
    return 1;
}

int stack_length(const stack *s)
{
    return s->size;
}

int stack_empty(const stack *s)
{
    return s->top == NULL;
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

void stack_traverse(stack *s, funcion callback)
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    snodo *actual = s->top;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->prox;
    }
}

int stack_search(const stack *s, const void *data, compare_func compare)
{
    if (!data || !compare)
    {
        printf("Error: Datos o funcion de comparacion nulos\n");
        return 0;
    }

    snodo *actual = s->top;
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

int stack_copy(const stack *src, stack *dest)
{
    if (!src || !dest) // ← Verificar ambas pilas
    {
        printf("Error: Pila fuente o destino nula\n");
        return 0;
    }

    // Limpiar la pila destino si no esta vacia
    if (!stack_empty(dest))
    {
        stack_clear(dest);
    }

    // Copiar tamaño de datos IMPORTANTE
    dest->size_data = src->size_data;

    // Si la fuente esta vacia, retornar éxito
    if (stack_empty(src))
    {
        return 1;
    }

    // Para copiar una pila necesitamos invertir temporalmente
    stack temp = stack_create(src->size_data);
    snodo *actual = src->top;

    // Primero copiar a una pila temporal (esto invierte el orden)
    while (actual != NULL)
    {
        if (!stack_push(&temp, actual->elem))
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
        if (!stack_push(dest, actual->elem))
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

    if (stack_empty(s) || s->top->prox == NULL)
    {
        // Pila vacia o con un solo elemento, ya esta invertida
        return 1;
    }

    stack temp = stack_create(s->size_data);
    snodo *actual = s->top;

    // Vaciar la pila original en la temporal
    while (actual != NULL)
    {
        if (!stack_push(&temp, actual->elem))
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
        if (!stack_push(s, actual->elem))
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

int stack_back(const stack *s, void *output)
{
    if (!s || !s->top || !output)
    {
        return 0;
    }

    snodo *aux = s->top;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    memcpy(output, aux->elem, s->size_data);
    return 1;
}

int stack_print(const stack *s, void (*print_func)(const void *))
{
    if (!s || !print_func)
    {
        return 0;
    }

    if (stack_empty(s))
    {
        printf("stack[%d] = (empty)\n", s->size);
        return 1;
    }

    printf("stack[%d] = ", s->size);
    snodo *aux = s->top;
    while (aux != NULL)
    {
        print_func(aux->elem);
        aux = aux->prox;
        if (aux != NULL)
        {
            printf(" -> ");
        }
    }
    printf(" \n");

    return 1;
}

stack stack_to_array(const void *array, int n, size_t size_data)
{
    if (!array || n <= 0 || size_data == 0)
    {
        return stack_create(0);
    }

    stack result = stack_create(size_data);

    // Convertir a const char* para aritmetica de punteros
    const char *ptr = (const char *)array;

    // Insertar en orden inverso para mantener orden del array
    for (int i = n - 1; i >= 0; i--)
    {
        const void *element = ptr + (i * size_data);
        if (!stack_push(&result, (void *)element))
        {
            stack_clear(&result);
            return stack_create(0);
        }
    }

    return result;
}

void stack_concat(stack *s, stack *p)
{
    if (!s || !p || s == p || s->size_data != p->size_data)
    {
        return;
    }

    if (stack_empty(p))
    {
        return;
    }

    // Crear array temporal con los elementos de p
    void **elements = malloc(p->size * sizeof(void *));
    if (!elements)
    {
        printf("Error: Memoria insuficiente\n");
        return;
    }

    // Extraer elementos de p y almacenarlos en array
    int index = 0;
    while (!stack_empty(p))
    {
        elements[index] = malloc(p->size_data);
        if (!elements[index])
        {
            // Liberar memoria ya asignada
            for (int i = 0; i < index; i++)
            {
                free(elements[i]);
            }
            free(elements);
            return;
        }

        stack_top(p, elements[index]);
        stack_pop(p);
        index++;
    }

    // Apilar elementos en s en orden inverso (para mantener orden)
    for (int i = index - 1; i >= 0; i--)
    {
        stack_push(s, elements[i]);
        free(elements[i]);
    }

    free(elements);
}

int stack_sort(stack *s, compare_func compare)
{
    if (!s || !compare)
    {
        printf("Error: Parametros invalidos\n");
        return 0;
    }

    // Pila vacaa o con un solo elemento ya esta ordenada
    if (stack_empty(s) || s->size == 1)
    {
        return 1;
    }

    // Pila temporal para ordenamiento
    stack temp = stack_create(s->size_data);
    int success = 1;

    while (!stack_empty(s) && success)
    {
        // Extraer elemento de la pila original
        void *element = malloc(s->size_data);
        if (!element)
        {
            printf("Error: Memoria insuficiente\n");
            success = 0;
            break;
        }

        if (!stack_top(s, element))
        {
            free(element);
            success = 0;
            break;
        }

        stack_pop(s);

        // Mover elementos mayores de temp a s
        void *temp_elem = malloc(s->size_data);
        if (!temp_elem)
        {
            free(element);
            success = 0;
            break;
        }

        int moved_back = 0;
        while (!stack_empty(&temp) && success)
        {
            if (!stack_top(&temp, temp_elem))
            {
                success = 0;
                break;
            }

            // Si el elemento en temp es mayor que element
            if (compare(temp_elem, element) > 0)
            {
                // Mover de temp a s
                if (!stack_push(s, temp_elem))
                {
                    success = 0;
                    break;
                }
                stack_pop(&temp);
                moved_back = 1;
            }
            else
            {
                break;
            }
        }

        if (success)
        {
            // Insertar element en temp
            if (!stack_push(&temp, element))
            {
                success = 0;
            }
        }

        free(element);
        free(temp_elem);

        // Si movimos elementos de vuelta, necesitamos continuar
        if (moved_back && success)
        {
            continue;
        }
    }

    // Transferir elementos ordenados de vuelta a s si todo fue exitoso
    if (success)
    {
        while (!stack_empty(&temp))
        {
            void *elem = malloc(s->size_data);
            if (!elem)
            {
                success = 0;
                break;
            }

            if (!stack_top(&temp, elem))
            {
                free(elem);
                success = 0;
                break;
            }

            if (!stack_push(s, elem))
            {
                free(elem);
                success = 0;
                break;
            }

            stack_pop(&temp);
            free(elem);
        }
    }

    // Limpiar temp si hubo error
    if (!success)
    {
        stack_clear(&temp);
        return 0;
    }

    return 1;
}

int stack_equal(const stack *s, const stack *p, compare_func compare)
{
    // Verificar punteros NULL
    if (!s || !p || !compare)
    {
        return 0;
    }

    // Si son el mismo objeto, son iguales
    if (s == p)
    {
        return 1;
    }

    // Si tamaños diferentes, no pueden ser iguales
    if (s->size != p->size || s->size_data != p->size_data)
    {
        return 0;
    }

    // Si ambas estan vacias, son iguales
    if (stack_empty(s) && stack_empty(p))
    {
        return 1;
    }

    // Si una est vacia y la otra no, son diferentes
    if (stack_empty(s) != stack_empty(p))
    {
        return 0;
    }

    // Comparar elemento por elemento
    snodo *nodo_s = s->top;
    snodo *nodo_p = p->top;

    while (nodo_s != NULL && nodo_p != NULL)
    {
        if (compare(nodo_s->elem, nodo_p->elem) != 0)
        {
            return 0;
        }
        nodo_s = nodo_s->prox;
        nodo_p = nodo_p->prox;
    }

    // Ambas deben haber llegado al final simultAneamente
    return (nodo_s == NULL && nodo_p == NULL);
}

void stack_destroy(stack *s, funcion destroy_func)
{
    if (!s)
    {
        return;
    }

    // Si se proporciono función de destruccion, usarla
    if (destroy_func)
    {
        snodo *actual = s->top;
        snodo *siguiente;

        while (actual != NULL)
        {
            siguiente = actual->prox;
            destroy_func(actual->elem);
            free(actual->elem);
            free(actual);
            actual = siguiente;
        }
    }
    else
    {
        // Usar stack_clear normal
        stack_clear(s);
    }

    s->top = NULL;
    s->size = 0;
}
