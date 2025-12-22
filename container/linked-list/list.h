#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __TYPE__ void *

typedef __TYPE__ __type__;

typedef int (*compare_func)(const void *, const void *);

typedef void (*func)(void *);

/**
 * @struct Estructura nodo elemento que forma la propia lista
 * @param elem
 */
typedef struct nodo
{
    __type__ elem;     // Puntero al dato almacenado
    struct nodo *next; // Puntero al siguiente nodo
    struct nodo *prev; // Puntero al nodo anterior
} nodo;

/**
 * @struct Estructura lista
 */
typedef struct
{
    nodo *head; // Puntero al primer nodo
    nodo *tail; // Puntero al último nodo
    nodo *iterator;
    size_t size_data; // Tamaño de cada elemento en bytes
    int size;         // Numero de elementos en la lista
} list;

// Prototipos de funciones

/**
 * @brief Crea una nueva lista doblemente enlazada vacia
 * @param size_data Tamaño en bytes de cada elemento
 * @return Lista inicializada
 * @note Metodo: Creador | Complejidad temporal O(1)
 */
list list_create(size_t size_data);

/**
 * @brief Agrega un elemento al final de la lista
 * @param this Puntero a la lista
 * @param data Puntero a los datos a agregar
 * @note Metodo: Modificador | Complejidad temporal O(1)
 */
void list_append(list *this, __type__ data);
/**
 * @brief Agrega un elemento al inicio de la lista
 * @param this Puntero a la lista
 * @param data Puntero a los datos a agregar
 * @note Metodo: Modificador | Complejidad temporal O(1)
 */
void list_appstart(list *this, __type__ data);
/**
 * @brief Elimina el primer elemento de la lista
 * @param this Puntero a la lista
 * @note Metodo: Modificador | Complejidad temporal O(1)
 */
int list_popstart(list *this);
/**
 * @brief Elimina el ultimo elemento de la lista
 * @param this Puntero a la lista
 * @note Metodo: Modificador | Complejidad temporal O(1)
 */
int list_popend(list *this);
/**
 * @brief Elimina el elemento en la posición especificada
 * @param this Puntero a la lista
 * @param position Posición del elemento a eliminar (0-based)
 * @return 1 si se eliminó correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_pop(list *this, int position);
/**
 * @brief Elimina todos los elementos de la lista
 * @param this Puntero a la lista
 * @return 1 si se elimino correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_free(list *this);

/**
 * @brief Obtiene el elemento en la posicion especificada
 * @param this Lista (por valor)
 * @param position Posición del elemento (0-based)
 * @return Puntero al elemento o NULL si la posicion es invalida
 * @note Metodo: Consultor | Complejidad temporal O(n)
 */
__type__ list_at(const list this, int position);
/**
 * @brief Obtiene el ultimo elemento de la lista
 * @param this Lista (por valor)
 * @param this valor a obtener (por referencia)
 * @note Metodo: Consultor | Complejidad temporal O(1)
 */
void list_back(const list this, __type__ valor);
/**
 * @brief Obtiene el primer elemento de la lista
 * @param this Lista (por valor)
 * @param this valor a obtener (por referencia)
 * @note Metodo: Consultor | Complejidad temporal O(1)
 */
void list_front(const list this, __type__ valor);

/**
 * @brief Obtiene la longitud de la lista
 * @param this Lista (por valor)
 * @return Numero de elementos en la lista
 * @note Metodo: Consultor | Complejidad temporal: O(1)
 */
int list_length(const list this);

/**
 * @brief Verifica si la lista esta vacia
 * @param this Lista (por valor)
 * @return 1 si la lista esta vacia, 0 en caso contrario
 * @note Metodo: Consultor | Complejidad temporal: O(1)
 */
int list_empty(const list this);

/**
 * @brief Invierte el orden de los elementos en la lista
 * @param this Puntero a la lista a invertir
 * @return 1 si se invirtio correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_reverse(list *this);

/**
 * @brief Modifica el primer elemento de la lista
 * @param this Puntero a la lista
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modificó correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(1)
 */
int list_setfirst(list *this, const __type__ new_data);

/**
 * @brief Modifica el ultimo elemento de la lista
 * @param this Puntero a la lista
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modifico correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(1)
 */
int list_setlast(list *this, const __type__ new_data);

/**
 * @brief Modifica el elemento en la posicion especificada
 * @param this Puntero a la lista
 * @param position Posición del elemento a modificar (0-based)
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modificó correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_set(list *this, int position, const __type__ new_data);

/**
 * @brief Inserta un elemento en la posicion especificada
 * @param this Puntero a la lista
 * @param position Posición donde insertar (0-based)
 * @param data Puntero a los datos a insertar
 * @return 1 si se insertó correctamente, 0 en caso de error
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_insert(list *this, int position, const __type__ data);

/**
 * @brief Recorre la lista desde el inicio hasta el fin
 * @param this Lista (por valor)
 * @param callback Funcion a ejecutar para cada elemento
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
void list_forward(list *this, void (*callback)(void *));

/**
 * @brief Recorre la lista desde el fin hasta el inicio
 * @param this Lista (por valor)
 * @param callback Funcion a ejecutar para cada elemento
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
void list_backward(list *this, void (*callback)(void *));

/**
 * @brief Recorre la lista desde inicio hasta el final
 * @param this lista a recorrer
 * @param sizevar tamaño de dato
 * @param valor a buscar
 * @return indice a la primera aparicion del elemento, -1 si no lo encuentra
 * @note Metodo: Consultor | Complejidad temporal O(n)
 * @note no necesita funcion auxiliar realiza la operacion a nivel de bytes (solo para datos primitivos(int,float,char..etc))
 */
long list_findb(const list *this, size_t sizevar, const __type__ valor);

/**
 * @brief Recorre la lista desde inicio hasta el final
 * @param this lista a recorrer
 * @param sizevar tamaño o longitud del dato
 * @param valor a buscar
 * @param compare funcion de busqueda
 * @return indice a la primera aparicion del elemento, -1 si no lo encuentra
 * @note Metodo: Consultor | Complejidad temporal O(n)
 */
long list_findf(const list *this, size_t sizevar, const __type__ valor, compare_func compare);

/**
 * @brief Recorre la lista desde inicio hasta el final contando el elemento
 * @param this lista a recorrer
 * @param sizevar tamaño o longitud del dato
 * @param valor a contar
 * @return Cantidad de elementos existentes en la lista
 * @note Metodo: Consultor | Complejidad temporal O(n)
 * @note no necesita funcion auxiliar realiza la operacion a nivel de bytes (solo para datos primitivos(int,float,char..etc))
 */
size_t list_countb(const list *this, size_t sizevar, const __type__ valor);

/**
 * @brief Recorre la lista desde inicio hasta el final
 * @param this lista a recorrer
 * @param sizevar tamaño o longitud del dato
 * @param valor a contar
 * @param compare funcion de busqueda
 * @return  Cantidad de elementos existentes en la lista
 * @note Metodo: Consultor | Complejidad temporal O(n)
 */
size_t list_countf(const list *this, size_t sizevar, const __type__ valor, compare_func compare);

/**
 * @brief Retorna una lista filtrada
 * @param this lista a recorrer
 * @param filter funcion de busqueda
 * @return lista filtrada
 * @note Metodo: Modificador | Complejidad temporal O(n)
 * @note operaciones de filtrado simple
 */
list list_filter(const list *this, int (*filter)(void *));

/**
 * @brief conversion de un string a lista
 * @param s string a convertir
 * @return lista de caracteres
 * @note Metodo: Creador | Complejidad temporal O(n)
 */
list list_str(const char *s);

/**
 * @brief imprime la lista usando función callback
 * @param this lista a imprimir
 * @param print funcion auxiliar para imprimir
 * @note Metodo: Creador | Complejidad temporal O(n)
 */
void list_print(const list *this, void (*print)(void *));

/**
 * @brief Crea una lista a partir de un array
 * @param arr Puntero al array
 * @param n Numero de elementos en el array
 * @param size Tamaño de cada elemento en bytes
 * @return Nueva lista con los elementos del array
 * @note Metodo: Creador | Complejidad temporal O(n)
 */
list list_arr(const __type__ arr, size_t n, size_t size);

/**
 * @brief Ordena la lista usando mergesort
 * @param this Puntero a la lista
 * @param compare Funcion de comparacion (retorna <0 si a<b, 0 si a==b, >0 si a>b)
 * @note Metodo: Modificador | Complejidad temporal O(n log n)
 */
void list_sort(list *this, compare_func compare);

/**
 * @brief Ordena la lista en orden inverso usando mergesort
 * @param this Puntero a la lista
 * @param compare Funcion de comparacion
 * @note Metodo: Modificador | Complejidad temporal O(n log n)
 */
void list_sort_reverse(list *this, compare_func compare);

/**
 * @brief Verifica si una lista esta ordenada
 * @param this Lista a verificar
 * @param compare Funcion de comparacion
 * @note Metodo: Consultor | Complejidad temporal O(n)
 * @return 1 si esta ordenada, 0 si no lo esta
 */
int list_is_sorted(const list *this, compare_func compare);

/**
 * @brief Une dos listas ordenadas manteniendo el orden
 * @param this Lista principal (debe estar ordenada)
 * @param other Lista a unir (debe estar ordenada)
 * @param compare Funcion de comparacion
 * @note Metodo: Modificador | Complejidad temporal O(n)
 * @note Ambas listas deben estar ordenadas previamente
 */
void list_merge_sorted(list *this, list *other, compare_func compare);

/**
 * @brief Modifica el dato
 * @param this lista por referencia
 * @param valor nuevo valor a tomar
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
void list_concat(list *this, const list *other);

/**
 * @brief Inicia el iterador al principio de la lista
 * @param this Puntero a la lista
 * @return 1 si exito, 0 si lista vacia
 * @note Metodo: Consultor | Complejidad temporal O(1)
 * @note Debe llamarse antes de usar list_iterator_next/prev
 */
int list_iterator_begin(list *this);

/**
 * @brief Inicia el iterador al final de la lista
 * @param this Puntero a la lista
 * @return 1 si exito, 0 si lista vacia
 * @note Metodo: Consultor | Complejidad temporal O(1)
 * @note Debe llamarse antes de usar list_iterator_next/prev
 */
int list_iterator_beginReverse(list *this);

/**
 * @brief Inicia el iterador al final de la lista
 * @param this Puntero a la lista
 * @return 1 si exito, 0 si lista vacia
 * @note Metodo: Consultor | Complejidad temporal O(1)
 * @note Debe llamarse antes de usar list_iterator_next/prev
 */
int list_iterator_set(list *this, const __type__ new_data);

/**
 * @brief Inicia el iterador al final de la lista
 * @param this Puntero a la lista
 * @return 1 si exito, 0 si lista vacia
 * @note Metodo: Consultor | Complejidad temporal O(1)
 * @note Debe lusarse despues de llamar a list_iterator_begin
 */
int list_iterator_next(list *this);

/**
 * @brief Inicia el iterador al final de la lista
 * @param this Puntero a la lista
 * @return 1 si exito, 0 si lista vacia
 * @note Metodo: Consultor | Complejidad temporal O(1)
 * @note Debe lusarse despues de llamar a list_iterator_begin_reverse
 */
int list_iterator_prev(list *this);

/**
 * @brief Inicia el iterador al final de la lista
 * @param this Puntero a la lista
 * @return 1 si exito, 0 si lista vacia
 * @note Metodo: Consultor | Complejidad temporal O(1)
 * @note Debe usarse despues de llamar a list_iterator_begin_reverse
 */
__type__ list_iterator_current(const list *this);

/**
 * @brief Verifica si el iterador es valido
 * @param this Lista
 * @return 1 si valido, 0 si no
 */
int list_iterator_valid(const list *this);

/**
 * @brief Ordena la lista usando mergesort iterativo (no recursivo)
 * @param this Lista a ordenar
 * @param compare Funcion de comparacion
 * @note Metodo: Modificador | Complejidad temporal O(n log n)
 * @note Version iterativa que evita desbordamiento de pila en listas grandes
 */
void list_sortIterativo(list *this, compare_func compare);

/**
 * @brief Remueve todas las ocurrencias de un elemento
 * @param this Lista a ordenar
 * @param valor elemento a eliminar
 * @param compare Funcion de comparacion
 * @note Metodo: Modificador | Complejidad temporal O(n log n)
 */
int list_removeAll(list *this, const __type__ valor, compare_func compare);

/**
 * @brief Remueve la primera ocurrencia de un elemento
 * @param this Lista a ordenar
 * @param valor elemento a eliminar
 * @param compare Funcion de comparacion
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_remove(list *this, const __type__ valor, compare_func compare);

/**
 * @brief Destruye la lista liberando memoria con funcion personalizada
 * @param this Puntero a la lista
 * @param destroy_func Funcion para liberar cada elemento (NULL si no se necesita)
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
void list_destroy(list *this, func destroy_func);

/**
 * @brief Elimina todos los elementos pero mantiene la estructura de lista
 * @param this Puntero a la lista
 * @param destroy_func Funcion para liberar cada elemento
 * @return Numero de elementos eliminados
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
int list_clear(list *this, func destroy_func);

/**
 * @brief Obtiene una sublista desde start hasta end (no inclusive)
 * @param this Lista original
 * @param start Posición inicial (0-based)
 * @param end Posición final (no inclusive, -1 para hasta el final)
 * @return Nueva lista con los elementos del rango
 * @note Metodo: Modificador | Complejidad temporal O(n)
 */
list list_sublist(const list *this, int start, int end);

/**
 * @brief Elimina elementos duplicados consecutivos
 * @param this Puntero a la lista
 * @param compare Funcion de comparacion
 * @return Numero de elementos eliminados
 * @note Metodo: Modificador | Complejidad temporal O(n)
 * @note Requiere lista ordenada previamente
 */
int list_unique(list *this, compare_func compare);

/**
 * @brief Elimina todas las ocurrencias duplicadas de un valor específico
 * @param this Lista
 * @param valor Valor a desduplicar
 * @param compare Funcion de comparacion
 * @return Numero de elementos eliminados
 * @note Metodo: Modificador | Complejidad temporal O(n)
 * @note Elimina duplicados no consecutivos
 */
int list_deduplicate(list *this, const __type__ valor, compare_func compare);

/**
 * @brief Realiza un copia apartir de una lista
 * @param this Lista a ordenar
 * @param compare Funcion de comparacion
 * @return Lista copia
 * @note Metodo: Creador | Complejidad temporal O(n)
 * @note Version iterativa que evita desbordamiento de pila en listas grandes
 */
list list_copy(const list *this);

/**
 * @brief Divide un string en tokens usando un delimitador
 * @param s String a dividir
 * @param delim Delimitador (string)
 * @return Lista de strings (cada token)
 * @note Metodo: Creador | Complejidad temporal O(n)
 * @note Los strings en la lista son copias independientes
 */
list list_split_str(const char *s, const char *delim);

#endif
