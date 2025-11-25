#include "queue.h"

queue new_queue(size_t size_data)
{
    queue new = {NULL, NULL, size_data, 0};
    return new;
}

qnodo *new_qnodo(void *dato, size_t size_data)
{
    if (!dato)
    {
        printf("Error: Dato nulo\n");
        return NULL;
    }

    qnodo *new = (qnodo *)malloc(sizeof(qnodo));
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

int enqueue(queue *q, void *data)
{
    if (!q || !data)
    {
        printf("Error: Cola o dato nulo\n");
        return 0;
    }

    qnodo *new = new_qnodo(data, q->size_data);
    if (!new)
        return 0;

    if (q->front == NULL)
    {
        // Cola vacia
        q->front = new;
        q->rear = new;
    }
    else
    {
        // Cola no vacia - insertar al final
        q->rear->prox = new;
        q->rear = new;
    }

    q->size++;
    return 1;
}

int dequeue(queue *q)
{
    if (!q || !q->front)
    {
        printf("Error: Cola nula o vacia\n");
        return 0;
    }

    qnodo *temp = q->front;

    if (q->front == q->rear)
    {
        // Solo un elemento en la cola
        q->front = NULL;
        q->rear = NULL;
    }
    else
    {
        // Multiples elementos
        q->front = q->front->prox;
    }

    free(temp->elem);
    free(temp);
    q->size--;
    return 1;
}

void *queue_front(const queue q)
{
    if (!q.front)
    {
        printf("Error: Cola vacia\n");
        return NULL;
    }
    return q.front->elem;
}

void *queue_rear(const queue q)
{
    if (!q.rear)
    {
        printf("Error: Cola vacia\n");
        return NULL;
    }
    return q.rear->elem;
}

int queue_size(const queue q)
{
    return q.size;
}

int queue_is_empty(const queue q)
{
    return q.front == NULL;
}

int queue_clear(queue *q)
{
    if (!q)
    {
        printf("Error: Cola nula\n");
        return 0;
    }

    qnodo *actual = q->front;
    qnodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->prox;
        free(actual->elem);
        free(actual);
        actual = siguiente;
    }

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return 1;
}

void queue_traverse(const queue q, void (*callback)(void *))
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    qnodo *actual = q.front;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->prox;
    }
}

int queue_search(const queue q, void *data, int (*compare)(const void *, const void *))
{
    if (!data || !compare)
    {
        printf("Error: Datos o funcion de comparacion nulos\n");
        return 0;
    }

    qnodo *actual = q.front;
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

int queue_copy(const queue src, queue *dest)
{
    if (!dest)
    {
        printf("Error: Cola destino nula\n");
        return 0;
    }

    // Limpiar la cola destino si no esta vacia
    if (!queue_is_empty(*dest))
    {
        queue_clear(dest);
    }

    // Copiar todos los elementos
    qnodo *actual = src.front;
    while (actual != NULL)
    {
        if (!enqueue(dest, actual->elem))
        {
            return 0; // Error al encolar
        }
        actual = actual->prox;
    }

    return 1;
}