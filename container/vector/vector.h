#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __TYPE__ void *

typedef __TYPE__ __type__;

typedef int (*compar_func)(const void *, const void *);

typedef void (*func)(void *);

typedef struct
{
    void **arr;       // Array de punteros a elementos
    size_t elem_size; // Tamaño de cada elemento (en bytes)
    size_t size;      // Numero actual de elementos
    size_t capacity;  // Capacidad actual del array
} vector;

/**
 * @brief Inicializa el vector previamente declarado
 * @param elem_size tamaño de dato que se va utilizar
 * @return vector inicializado
 * @note Metodo: creador | Complejidad Temporal: O(1)
 */
vector vector_create(size_t elem_size);

/**
 * @brief Agrega un elemento al final del vector
 * @param vec vector donde se va agregar
 * @param valor elemento que se va agregar
 * @note Metodo: Modificador | Complejidad Temporal: O(1)
 */
void vector_pushback(vector *vec, const __type__ valor);
/**
 * @brief Agrega un elemento al inicio del vector
 * @param vec vector donde se va agregar
 * @param valor elemento que se va agregar
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
void vector_pushfront(vector *vec, const __type__ valor);
/**
 * @brief Agrega un elemento en una posicion del vector
 * @param vec vector donde se va agregar
 * @param pos posicion donde se va agregar
 * @param valor elemento que se va agregar
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
void vector_insert(vector *vec, size_t pos, const __type__ valor);

/**
 * @brief Elimina un elemento al final del vector
 * @param vec vector donde se va eliminar
 * @note Metodo: Modificador | Complejidad Temporal: O(1)
 */
void vector_popback(vector *vec);
/**
 * @brief Elimina un elemento al inicio del vector
 * @param vec vector donde se va eliminar
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
void vector_popfront(vector *vec);
/**
 * @brief Elimina un elemento en una posicion del vector
 * @param vec vector donde se va eliminar
 * @param pos posicion donde se va eliminar
 * @note Metodo: Modificador | Complejidad Temporal: O(n)
 */
void vector_erase(vector *vec, size_t pos);

/**
 * @brief Verifica si el vector esta vacio
 * @param vec vector por referencia
 * @return 1 si esta vacio, 0 si no
 * @note Metodo: consultor | Complejidad Temporal O(1)
 */
int vector_empty(const vector *vec);
/**
 * @brief Obtiene el numero de elementos en el vector
 * @param vec vector por referencia
 * @return Cantidad de elementos en el vector
 * @note Metodo: consultor | Complejidad Temporal O(1)
 */
size_t vector_size(const vector *vec);
/**
 * @brief Obtiene la capacidad del vector
 * @param vec vector por referencia
 * @return Capacidad del vector
 * @note Metodo: consultor | Complejidad Temporal O(1)
 */
size_t vector_capacity(const vector *vec);

/**
 * @brief Accede al elemento de una posicion especifica
 * @param vec vector por referencia
 * @param pos posicion dentro del vector
 * @note Metodo: consultor | Complejidad Temporal O(1)
 */
__type__ vector_at(const vector *vec, size_t pos);
/**
 * @brief Accede al primer elemento del vector
 * @param vec vector por referencia
 * @note Metodo: consultor | Complejidad Temporal O(1)
 */
__type__ vector_front(const vector *vec);
/**
 * @brief Accede al ultimo elemento del vector
 * @param vec vector por referencia
 * @note Metodo: consultor | Complejidad Temporal O(1)
 */
__type__ vector_back(const vector *vec);
/**
 * @brief Modifica el elemento de una posicion especifica
 * @param vec vector por referencia
 * @param pos posicion dentro del vector
 * @note Metodo: Modificador | Complejidad Temporal O(1)
 */
void vector_set(vector *arr, size_t pos, const __type__ valor);

/**
 * @brief Reserva memoria en el vector
 * @param vec vector por referencia
 * @param new_capacity nuevo tamaño
 * @note Metodo: Modificador | Complejidad Temporal O(n)
 */
void vector_reserve(vector *vec, size_t new_capacity);
/**
 * @brief Ajusta la capacidad al tamaño del vector
 * @param vec vector por referencia
 * @note Metodo: Modificador | Complejidad Temporal O(n)
 */
void vector_shrink_to_fit(vector *vec);

/**
 * @brief Limpia la memoria utilizada en el vector
 * @param vec vector por referencia
 * @note Metodo: Modificador | Complejidad Temporal O(n)
 */
void vector_clear(vector *vec);
/**
 * @brief Libera la memoria utilizada por el propio vector
 * @param vec vector por referencia
 * @note Metodo: Destructor | Complejidad Temporal O(n)
 */
void vector_free(vector *vec);

/**
 * @brief Accede al ultimo elemento del vector
 * @param vec vector por referencia al cual se va acceder
 * @param nbyte tipo de dato o longitud de puntero
 * @param valor elemento que se desea encontrar
 * @return Indice de la poscion del elemento, -1 en caso de no encontrarlo
 * @note Metodo: Consultor | Complejidad Temporal O(n)
 */
long vector_findb(const vector *vec, size_t nbyte, const __type__ valor);
/**
 * @brief Accede al ultimo elemento del vector
 * @param vec vector por referencia al cual se va acceder
 * @param nbyte tipo de dato o longitud de puntero
 * @param valor elemento que se desea contar
 * @return Cantidad de repeticiones del elemento que se encuentran el vector
 * @note Metodo: Consultor | Complejidad Temporal O(n)
 */
size_t vector_countb(const vector *vec, size_t nbyte, const __type__ valor);
/**
 * @brief Accede al ultimo elemento del vector
 * @param vec vector por referencia
 * @param valor elemento que se desea encontrar
 * @param compare funcion de comparacion
 * @return Indice de la poscion del elemento, -1 en caso de no encontrarlo
 * @note Metodo: Consultor | Complejidad Temporal O(n)
 */
long vector_findf(const vector *vec, const __type__ valor, compar_func compare);
/**
 * @brief Accede al ultimo elemento del vector
 * @param vec vector por referencia
 * @param valor elemento que se desea contar
 * @param compare funcion de comparacion
 * @return Cantidad de repeticiones del elemento que se encuentran el vector
 * @note Metodo: Consultor | Complejidad Temporal O(n)
 */
size_t vector_countf(const vector *vec, const __type__ valor, compar_func compare);

/**
 * @brief Realiza un ordenamiento con quirkSort
 * @param vec vector por referencia
 * @param compare funcion de comparacion
 * @note Metodo: Modificador | Complejidad Temporal O(n log n)
 */
void vector_qsort(vector *vec, compar_func compare);
/**
 * @brief Realiza una busqueda binaria en el vector
 * @param vec vector por referencia
 * @param valor elemento que se desea encontrar
 * @param compare funcion de comparacion
 * @return Indice de la poscion del elemento, -1 en caso de no encontrarlo
 * @note Metodo: consultor | Complejidad Temporal O(log n)
 * @note Precondicion: vector debe estar ordenado
 */
long vector_bsearch(const vector *vec, const __type__ valor, compar_func compare);
/**
 * @brief Invierte un vector
 * @param vec vector por referencia
 * @note Metodo: Modificador | Complejidad Temporal O(n)
 */
void vector_reverse(vector *vec);
/**
 * @brief Realiza un recorrido en el vector
 * @param vec vector por referencia
 * @param compare funcion de comparacion
 * @note Metodo: Modificador | Complejidad Temporal O(n)
 */
void vector_foreach(vector *vec, func funcion);

#endif