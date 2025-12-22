#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*funcion)(void *);

typedef int (*compare_func)(const void *, const void *);

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
 * @brief Crea una nueva pila vacia
 * @param size_data Tamaño en bytes de cada elemento
 * @return Pila inicializada
 * @note Metodo: Creador | Complejidad Temporal: O(1)
 */
stack stack_create(size_t size_data);

/**
 * @brief Apila un elemento (inserta en la cima de la pila)
 * @param s Puntero a la pila
 * @param data Puntero a los datos a apilar
 * @return 1 si se apilo correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad Temporal: O(1)
 */
int stack_push(stack *s, const void *data);
/**
 * @brief Desapila un elemento (elimina de la cima de la pila)
 * @param s Puntero a la pila
 * @return 1 si se desapilo correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad Temporal: O(1)
 */
int stack_pop(stack *s);

/**
 * @brief Obtiene el elemento de la cima de la pila sin eliminarlo
 * @param s Pila (por valor)
 * @return Puntero al elemento de la cima o NULL si la pila esta vacia
 * @note Metodo: Consultor | Complejidad Temporal: O(1)
 */
int stack_top(const stack *s, void *output);

/**
 * @brief Obtiene el tamaño de la pila
 * @param s Pila (por valor)
 * @return Numero de elementos en la pila
 * @note Metodo: Consultor | Complejidad Temporal: O(1)
 */
int stack_length(const stack *s);
/**
 * @brief Verifica si la pila esta vacia
 * @param s Pila (por valor)
 * @return 1 si la pila esta vacia, 0 en caso contrario
 * @note Metodo: Consultor | Complejidad Temporal: O(1)
 */
int stack_empty(const stack *s);

/**
 * @brief Elimina todos los elementos de la pila
 * @param s Puntero a la pila
 * @return 1 si se vacio correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
int stack_clear(stack *s);

/**
 * @brief Recorre la pila ejecutando una funcion para cada elemento (de cima a base)
 * @param s Pila (por valor)
 * @param callback Funcion a ejecutar para cada elemento
 * @note Ejemplo de funcion(stack ) manipula el elemento de stack
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
void stack_traverse(stack *s, funcion callback);
/**
 * @brief Busca un elemento en la pila usando una funcion de comparacion
 * @param s Pila (por valor)
 * @param data Puntero a los datos a buscar
 * @param compare Funcion de comparacion (devuelve 0 si son iguales)
 * @return 1 si se encontro, 0 si no se encontro
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
int stack_search(const stack *s, const void *data, compare_func compare);

/**
 * @brief Realiza una copia de una pila
 * @param src Pila fuente (por valor)
 * @param dest Puntero a la pila destino
 * @return 1 si se copio correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
int stack_copy(const stack *src, stack *dest);
/**
 * @brief Invierte el orden de los elementos en la pila
 * @param s Puntero a la pila a invertir
 * @return 1 si se invirtio correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
int stack_reverse(stack *s);

/**
 * @brief Consulta el fondo de la pila
 * @param s stack por referencia
 * @param output valor a leer
 * @return 1 si fue exito o 0 en caso contrario
 * @note Metodo: Consultor | Complejidad Temporal: O(n)
 */
int stack_back(const stack *s, void *output);
/**
 * @brief Imprime el contenido de la pila
 * @param s Puntero a la pila
 * @param print_func funcion de impresion
 * @return 1 si se invirtio correctamente, 0 en caso de error
 * @note Metodo: Consultor | Complejidad Temporal: O(n)
 */
int stack_print(const stack *s, void (*print_func)(const void *));
/**
 * @brief Crea una pila atra vez del contenido de un arreglo
 * @param s Puntero a la pila
 * @param size cantidad de elementos de arreglo
 * @param nbyts tamaño de cada dato en bytes
 * @return Pila con los elementos del  arreglo
 * @note Metodo: Creador | Complejidad Temporal: O(n)
 */
stack stack_to_array(const void *arrays, int size, size_t nbytes);
/**
 * @brief Concatena dos pilas en una sola
 * @param s Puntero a la pila concatenar
 * @param p Puntero a la pila a borrar
 * @return Pila con los elementos concatenados
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
void stack_concat(stack *s, stack *p);

/**
 * @brief Ordena una pila usando ordenamiento por inserción
 * @param s Pila a ordenar
 * @param compare Función de comparación (<0 si a<b, 0 si a==b, >0 si a>b)
 * @return 1 si exito, 0 si error
 * @note Metodo: Modificador | Complejidad Temporal: O(n²)
 */
int stack_sort(stack *s, compare_func compare);
/**
 * @brief Verifica si dos pilas son iguales
 * @param s Puntero a la pila1
 * @param p Puntero a la pila2
 * @param compare Funcion de compararacion ( a == b -> 0)
 * @return 1 en caso de ser igaules o 0 en caso contrario
 * @note Metodo: Consultor | Complejidad Temporal: O(n)
 */
int stack_equal(const stack *s, const stack *p, compare_func compare);
/**
 * @brief Destruye una pila liberando memoria con funcion personalizada
 * @param s Puntero a la pila
 * @param destroy_func Funcion para liberar cada elemento (NULL si no se necesita)
 * @note Para datos complejos que necesitan liberacion especial (ej: strings)
 */
void stack_destroy(stack *s, funcion destroy_func);

#endif
