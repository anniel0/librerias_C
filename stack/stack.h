#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo de la pila
typedef struct snodo
{
    void *elem;         // Puntero al dato almacenado
    struct snodo *prox; // Puntero al siguiente nodo
} snodo;

// Estructura principal de la pila
typedef struct
{
    snodo *top;       // Puntero a la cima de la pila
    size_t size_data; // Tamaño de cada elemento en bytes
    int size;         // Numero de elementos en la pila
} stack;

// Prototipos de funciones

/**
 * Crea una nueva pila vacia
 * @param size_data Tamaño en bytes de cada elemento
 * @return Pila inicializada
 */
stack new_stack(size_t size_data);

/**
 * Crea un nuevo nodo con los datos proporcionados
 * @param dato Puntero a los datos a almacenar
 * @param size_data Tamaño en bytes de los datos
 * @return Puntero al nuevo nodo o NULL en caso de error
 */
snodo *new_snodo(void *dato, size_t size_data);

/**
 * Apila un elemento (inserta en la cima de la pila)
 * @param s Puntero a la pila
 * @param data Puntero a los datos a apilar
 * @return 1 si se apilo correctamente, 0 en caso de error
 */
int push(stack *s, void *data);

/**
 * Desapila un elemento (elimina de la cima de la pila)
 * @param s Puntero a la pila
 * @return 1 si se desapilo correctamente, 0 en caso de error
 */
int pop(stack *s);

/**
 * Obtiene el elemento de la cima de la pila sin eliminarlo
 * @param s Pila (por valor)
 * @return Puntero al elemento de la cima o NULL si la pila esta vacia
 */
void *stack_top(const stack s);

/**
 * Obtiene el tamaño de la pila
 * @param s Pila (por valor)
 * @return Numero de elementos en la pila
 */
int stack_size(const stack s);

/**
 * Verifica si la pila esta vacia
 * @param s Pila (por valor)
 * @return 1 si la pila esta vacia, 0 en caso contrario
 */
int stack_is_empty(const stack s);

/**
 * Elimina todos los elementos de la pila
 * @param s Puntero a la pila
 * @return 1 si se vacio correctamente, 0 en caso de error
 */
int stack_clear(stack *s);

/**
 * Recorre la pila ejecutando una funcion para cada elemento (de cima a base)
 * @param s Pila (por valor)
 * @param callback Funcion a ejecutar para cada elemento
 */
void stack_traverse(const stack s, void (*callback)(void *));

/**
 * Busca un elemento en la pila usando una funcion de comparacion
 * @param s Pila (por valor)
 * @param data Puntero a los datos a buscar
 * @param compare Funcion de comparacion (devuelve 0 si son iguales)
 * @return 1 si se encontro, 0 si no se encontro
 */
int stack_search(const stack s, void *data, int (*compare)(const void *, const void *));

/**
 * Copia toda la pila
 * @param src Pila fuente (por valor)
 * @param dest Puntero a la pila destino
 * @return 1 si se copio correctamente, 0 en caso de error
 */
int stack_copy(const stack src, stack *dest);

/**
 * Invierte el orden de los elementos en la pila
 * @param s Puntero a la pila a invertir
 * @return 1 si se invirtio correctamente, 0 en caso de error
 */
int stack_reverse(stack *s);

#endif