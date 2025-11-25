#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct setnodo
{
    void *elem;
    struct setnodo *prox;
} setnodo;

typedef struct
{
    setnodo *head, *tail;
    size_t data;
    int size;
    int (*pertain)(const void *, const void *);
} set;

/**
 * @brief Crea un nodo para el conjunto
 * @param elem valor de dato
 * @param data tamaño de dato
 * @return Puntero a nodo de conjunto, en caso erro retorna NULL
 */
setnodo *new_setnodo(void *elem, size_t data);

/**
 * @brief Crea un conjunto vacio
 * @param data tamaño de dato
 * @return conjunto vacio
 */
set new_set(size_t data);

/**
 * @brief Crea un conjunto vacio con función de pertenencia personalizada
 * @param data tamaño de dato
 * @param pertain función de pertenencia
 * @return conjunto vacio
 */
set new_setin(size_t data, int (*pertain)(const void *, const void *));

/**
 * @brief Retorna la cantidad de elementos que se encentran dentro del conjunto
 * @param prime conjunto
 * @return Cantidad de elementos que pertenecen al conjunto
 */
int set_size(const set prime);

/**
 * @brief Verifica si un elemento pertenece a un conjunto
 * @param prime conjunto
 * @param elem elemento a verificar
 * @return 1 en caso que el elemento pertenece al conjunto, 0 en caso contrario
 */
int set_pertain(const set *prime, void *elem);

/**
 * @brief agrega al final del conjunto un nuevo elemento que no pertenesca a este mismo
 * @param prime conjunto
 * @param elem nuevo elemento
 * @return 1 en caso de poder ser agregado, 0 en caso de contrario
 */
int set_app(set *prime, void *elem);

/**
 * @brief Retorna un conjuto producto de la diferencia de dos conjuntos
 * @param prime primer conjunto
 * @param otro segundo conjunto
 * @return Un conjuto producto de la diferencia de dos conjuntos
 */
set set_difference(const set *prime, const set *otro);

/**
 * @brief Retorna un conjuto producto de la union de dos conjuntos
 * @param prime primer conjunto
 * @param otro segundo conjunto
 * @return Un conjuto producto de la union de dos conjuntos
 */
set set_union(const set *prime, const set *otro);

/**
 * @brief Retorna un conjuto producto de la interccion de dos conjuntos
 * @param prime primer conjunto
 * @param otro segundo conjunto
 * @return Un conjuto producto de la interccion de dos conjuntos
 */
set set_intersection(const set *prime, const set *otro);

/**
 * @brief Verifica si un conjunto es subconjunto de otro
 * @param prime conjunto principal
 * @param otro conjunto secundario
 * @return 1 en caso de ser subconjunto o 0 en caso contrario
 */
int set_subset(const set *prime, const set *otro);

/**
 * @brief Obtiene el elemento de un conjunto en una posicion dada
 * @param prime conjunto principal
 * @param position posicion del conjunto
 * @param elem por referencia
 */
void set_at(const set *prime, int position, void *elem);

/**
 * @brief Verifica si un conjunto esta vacio
 * @param prime conjunto principal
 * @return 1 en caso de estar vacio o 0 en caso contrario
 */
int set_empty(const set prime);

/**
 * @brief Elimina un elemento del conjunto
 * @param prime conjunto principal
 * @param position posicion de elemento a eliminar
 * @return 1 en caso de exito, 0 en caso contrario
 */
int set_popat(set *prime, int position);

/**
 * @brief Intercambia dos elementos del conjunto
 * @param prime conjunto principal
 * @param pos1 primera posicion
 * @param pos2 segunda posicion
 * @return 1 en caso de exito, 0 en caso contrario
 */
int set_swap(set *prime, int pos1, int pos2);

/**
 * @brief Libera la memoria del conjunto
 * @param prime conjunto principal
 * @return 1 en caso de exito, 0 en caso contrario
 */
int free_set(set *prime);

/**
 * @brief Convierte el conjunto a un arreglo
 * @param prime conjunto
 * @return arreglo con los elementos del conjunto
 */
void **set_to_array(const set prime);

/**
 * @brief Ordena el conjunto usando merge sort
 * @param prime conjunto a ordenar
 * @param compare funcion de comparacion
 */
void set_msort(set *prime, int (*compare)(const void *, const void *));

/**
 * @brief Ordena el conjunto usando merge sort con memcmp
 * @param prime conjunto a ordenar
 */
void set_msortb(set *prime);

/**
 * @brief Crea un conjunto a partir de un arreglo
 * @param arr arreglo de elementos
 * @param size tamaño del arreglo
 * @param data_size tamaño de cada elemento
 * @return conjunto creado
 */
set array_to_set(void *arr, int size, size_t data_size);

/**
 * @brief Filtra el conjunto según una condición
 * @param prime conjunto a filtrar
 * @param filter función de filtrado
 * @return conjunto filtrado
 */
set set_filter(const set *prime, int (*filter)(const void *));

#endif