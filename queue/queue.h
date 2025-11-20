#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo de la cola
typedef struct qnodo
{
    void *elem;         // Puntero al dato almacenado
    struct qnodo *prox; // Puntero al siguiente nodo
} qnodo;

// Estructura principal de la cola
typedef struct
{
    qnodo *front;     // Puntero al frente de la cola (para eliminar)
    qnodo *rear;      // Puntero al final de la cola (para insertar)
    size_t size_data; // Tamaño de cada elemento en bytes
    int size;         // Numero de elementos en la cola
} queue;

// Prototipos de funciones

/**
 * Crea una nueva cola vacia
 * @param size_data Tamaño en bytes de cada elemento
 * @return Cola inicializada
 */
queue new_queue(size_t size_data);

/**
 * Crea un nuevo nodo con los datos proporcionados
 * @param dato Puntero a los datos a almacenar
 * @param size_data Tamaño en bytes de los datos
 * @return Puntero al nuevo nodo o NULL en caso de error
 */
qnodo *new_qnodo(void *dato, size_t size_data);

/**
 * Encola un elemento (inserta al final de la cola)
 * @param q Puntero a la cola
 * @param data Puntero a los datos a encolar
 * @return 1 si se encoló correctamente, 0 en caso de error
 */
int enqueue(queue *q, void *data);

/**
 * Desencola un elemento (elimina del frente de la cola)
 * @param q Puntero a la cola
 * @return 1 si se desencolo correctamente, 0 en caso de error
 */
int dequeue(queue *q);

/**
 * Obtiene el elemento del frente de la cola sin eliminarlo
 * @param q Cola (por valor)
 * @return Puntero al elemento del frente o NULL si la cola esta vacia
 */
void *queue_front(const queue q);

/**
 * Obtiene el elemento del final de la cola sin eliminarlo
 * @param q Cola (por valor)
 * @return Puntero al elemento del final o NULL si la cola esta vacia
 */
void *queue_rear(const queue q);

/**
 * Obtiene el tamaño de la cola
 * @param q Cola (por valor)
 * @return Numero de elementos en la cola
 */
int queue_size(const queue q);

/**
 * Verifica si la cola esta vacia
 * @param q Cola (por valor)
 * @return 1 si la cola esta vacia, 0 en caso contrario
 */
int queue_is_empty(const queue q);

/**
 * Elimina todos los elementos de la cola
 * @param q Puntero a la cola
 * @return 1 si se vacio correctamente, 0 en caso de error
 */
int queue_clear(queue *q);

/**
 * Recorre la cola ejecutando una funcion para cada elemento
 * @param q Cola (por valor)
 * @param callback Funcion a ejecutar para cada elemento
 */
void queue_traverse(const queue q, void (*callback)(void *));

/**
 * Busca un elemento en la cola usando una funcion de comparacion
 * @param q Cola (por valor)
 * @param data Puntero a los datos a buscar
 * @param compare Funcion de comparacion (devuelve 0 si son iguales)
 * @return 1 si se encontro, 0 si no se encontro
 */
int queue_search(const queue q, void *data, int (*compare)(const void *, const void *));

/**
 * Copia toda la cola
 * @param src Cola fuente (por valor)
 * @param dest Puntero a la cola destino
 * @return 1 si se copio correctamente, 0 en caso de error
 */
int queue_copy(const queue src, queue *dest);

#endif