#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo de la lista
typedef struct nodo
{
    void *elem;        // Puntero al dato almacenado
    struct nodo *prox; // Puntero al siguiente nodo
} nodo;

// Estructura principal de la lista
typedef struct
{
    nodo *head;       // Puntero al primer nodo
    nodo *tail;       // Puntero al último nodo
    size_t size_data; // Tamaño de cada elemento en bytes
    int size;         // Número de elementos en la lista
} list;

// Prototipos de funciones

/**
 * Crea una nueva lista vacia
 * @param size_data Tamaño en bytes de cada elemento
 * @return Lista inicializada
 */
list new_list(size_t size_data);

/**
 * Crea un nuevo nodo con los datos proporcionados
 * @param dato Puntero a los datos a almacenar
 * @param size_data Tamaño en bytes de los datos
 * @return Puntero al nuevo nodo o NULL en caso de error
 */
nodo *new_nodo(void *dato, size_t size_data);

/**
 * Agrega un elemento al final de la lista
 * @param prime Puntero a la lista
 * @param data Puntero a los datos a agregar
 */
void list_append(list *prime, void *data);

/**
 * Agrega un elemento al inicio de la lista
 * @param prime Puntero a la lista
 * @param data Puntero a los datos a agregar
 */
void list_appstart(list *prime, void *data);

/**
 * Elimina el primer elemento de la lista
 * @param prime Puntero a la lista
 */
void list_popstart(list *prime);

/**
 * Elimina el ultimo elemento de la lista
 * @param prime Puntero a la lista
 */
void list_popend(list *prime);

/**
 * Elimina el elemento en la posicion especificada
 * @param prime Puntero a la lista
 * @param position Posicion del elemento a eliminar (0-based)
 * @return 1 si se elimino correctamente, 0 en caso de error
 */
int list_popat(list *prime, int position);

/**
 * Elimina todos los elementos de la lista
 * @param prime Puntero a la lista
 * @return 1 si se elimino correctamente, 0 en caso de error
 */
int free_list(list *prime);

/**
 * Obtiene el elemento en la posicion especificada
 * @param prime Lista (por valor)
 * @param position Posición del elemento (0-based)
 * @return Puntero al elemento o NULL si la posicion es invalida
 */
void *list_see(const list prime, int position);

/**
 * Obtiene el ultimo elemento de la lista
 * @param prime Lista (por valor)
 * @return Puntero al ultimo elemento o NULL si la lista esta vacía
 */
void *list_end(const list prime);

/**
 * Obtiene el primer elemento de la lista
 * @param prime Lista (por valor)
 * @return Puntero al primer elemento o NULL si la lista esta vacia
 */
void *list_start(const list prime);

/**
 * Obtiene la longitud de la lista
 * @param prime Lista (por valor)
 * @return Numero de elementos en la lista
 */
int list_lenght(const list prime);

/**
 * Verifica si la lista esta vacia
 * @param prime Lista (por valor)
 * @return 1 si la lista esta vacia, 0 en caso contrario
 */
int list_is_empty(const list prime);

/**
 * Invierte el orden de los elementos en la lista
 * @param prime Puntero a la lista a invertir
 * @return 1 si se invirtio correctamente, 0 en caso de error
 */
int list_reverse(list *prime);

/**
 * Modifica el primer elemento de la lista
 * @param prime Puntero a la lista
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modificó correctamente, 0 en caso de error
 */
int list_setfirst(list *prime, void *new_data);

/**
 * Modifica el ultimo elemento de la lista
 * @param prime Puntero a la lista
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modifico correctamente, 0 en caso de error
 */
int list_setlast(list *prime, void *new_data);

/**
 * Modifica el elemento en la posición especificada
 * @param prime Puntero a la lista
 * @param position Posición del elemento a modificar (0-based)
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modificó correctamente, 0 en caso de error
 */
int list_setall(list *prime, int position, void *new_data);

/**
 * Convierte la lista en un arreglo de punteros a sus elementos
 * @param prime Puntero a la lista
 * @return Arreglo de punteros a los elementos de la lista
 */
void **list_arrays(const list *prime);

/**
 * Crea una lista a partir de un arreglo de punteros
 * @param arr Arreglo de punteros a los elementos
 * @param size Tamaño en bytes de cada elemento
 * @return Nueva lista creada a partir del arreglo
 */
list array_list(void *arr, int size, size_t data_size);

/**
 * Ordena la lista usando el algoritmo Merge Sort con funcion de comparacion personalizada
 * @param prime Puntero a la lista a ordenar
 * @param compare Función de comparación para ordenar los elementos
 */
void list_msort(list *prime, int (*compare)(const void *, const void *));

/**
 * Ordena la lista usando el algoritmo Merge Sort con comparacion por bytes (memcmp)
 * @param prime Puntero a la lista a ordenar
 */
void list_msortb(list *prime);

/**
 * Cuenta las ocurrencias de un elemento en la lista
 * @param prime Puntero a la lista
 * @param elem Elemento a buscar
 * @return Numero de ocurrencias del elemento en la lista
 */
int list_count(const list *prime, void *elem);

/**
 * Busca la primera ocurrencia de un elemento en la lista
 * @param prime Puntero a la lista
 * @param elem Elemento a buscar
 * @return Indice de la primera ocurrencia o -1 si no se encuentra
 */
int list_index(const list *prime, void *elem);

/**
 * Filtra los elementos que cumplan la condicion en una lista
 * @param prime Puntero a la lista
 * @param filter funcion para filtrar
 * @return Una lista con elementos que retornen 0 en caso de cumplir la condicion
 */
list list_filter(const list *prime, int (*filter)(const void *));
#endif