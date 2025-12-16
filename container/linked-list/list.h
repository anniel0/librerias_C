#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura de un nodo de la lista doblemente enlazada
typedef struct nodo
{
    void *elem;        // Puntero al dato almacenado
    struct nodo *prox; // Puntero al siguiente nodo
    struct nodo *ant;  // Puntero al nodo anterior
} nodo;

// Estructura principal de la lista doblemente enlazada
typedef struct
{
    nodo *head;       // Puntero al primer nodo
    nodo *tail;       // Puntero al último nodo
    size_t size_data; // Tamaño de cada elemento en bytes
    int size;         // Número de elementos en la lista
    int (*comp)(void *, void *);
} list;

// Prototipos de funciones

/**
 * Crea una nueva lista doblemente enlazada vacía
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
 * Elimina el último elemento de la lista
 * @param prime Puntero a la lista
 */
void list_popend(list *prime);

/**
 * Elimina el elemento en la posición especificada
 * @param prime Puntero a la lista
 * @param position Posición del elemento a eliminar (0-based)
 * @return 1 si se eliminó correctamente, 0 en caso de error
 */
int list_pop(list *prime, int position);

/**
 * Elimina todos los elementos de la lista
 * @param prime Puntero a la lista
 * @return 1 si se eliminó correctamente, 0 en caso de error
 */
int delete_list(list *prime);

/**
 * Obtiene el elemento en la posición especificada
 * @param prime Lista (por valor)
 * @param position Posición del elemento (0-based)
 * @return Puntero al elemento o NULL si la posición es inválida
 */
void *list_at(const list prime, int position);

/**
 * Obtiene el último elemento de la lista
 * @param prime Lista (por valor)
 * @return Puntero al último elemento o NULL si la lista está vacía
 */
void *list_end(const list prime);

/**
 * Obtiene el primer elemento de la lista
 * @param prime Lista (por valor)
 * @return Puntero al primer elemento o NULL si la lista está vacía
 */
void *list_start(const list prime);

/**
 * Obtiene la longitud de la lista
 * @param prime Lista (por valor)
 * @return Número de elementos en la lista
 */
int list_length(const list prime);

/**
 * Verifica si la lista está vacía
 * @param prime Lista (por valor)
 * @return 1 si la lista está vacía, 0 en caso contrario
 */
int list_empty(const list prime);

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
 * Modifica el elemento en la posicion especificada
 * @param prime Puntero a la lista
 * @param position Posición del elemento a modificar (0-based)
 * @param new_data Puntero a los nuevos datos
 * @return 1 si se modificó correctamente, 0 en caso de error
 */
int list_set(list *prime, int position, void *new_data);

/**
 * Inserta un elemento en la posición especificada
 * @param prime Puntero a la lista
 * @param position Posición donde insertar (0-based)
 * @param data Puntero a los datos a insertar
 * @return 1 si se insertó correctamente, 0 en caso de error
 */
int list_insert(list *prime, int position, void *data);

/**
 * Recorre la lista desde el inicio hasta el fin
 * @param prime Lista (por valor)
 * @param callback Función a ejecutar para cada elemento
 */
void list_forward(list *prime, void (*callback)(void *));

/**
 * Recorre la lista desde el fin hasta el inicio
 * @param prime Lista (por valor)
 * @param callback Funcion a ejecutar para cada elemento
 */
void list_backward(list *prime, void (*callback)(void *));

/**
 * @brief Recorre la lista desde inicio hasta el final
 * @param this lista a recorrer
 * @param sizevar tamaño de dato
 * @param valor a buscar
 * @return indice a la primera aparicion del elemento, -1 si no lo encuentra
 * @note Complejidad temporal O(n)
 * @note no necesita funcion auxiliar realiza la operacion a nivel de bytes (solo para datos primitivos(int,float,char..etc))
 */
long list_findb(const list *this, size_t sizevar, void *valor);

/**
 * @brief Recorre la lista desde inicio hasta el final
 * @param this lista a recorrer
 * @param sizevar tamaño o longitud del dato
 * @param valor a buscar
 * @param compare funcion de busqueda
 * @return indice a la primera aparicion del elemento, -1 si no lo encuentra
 * @note Complejidad temporal O(n)
 */
long list_findf(const list *this, size_t sizevar, void *valor, int (*compare)(void *, void *));

/**
 * @brief Recorre la lista desde inicio hasta el final contando el elemento
 * @param this lista a recorrer
 * @param sizevar tamaño o longitud del dato
 * @param valor a contar
 * @return cantidad de elementos existentes en la lista
 * @note Complejidad temporal O(n)
 * @note no necesita funcion auxiliar realiza la operacion a nivel de bytes (solo para datos primitivos(int,float,char..etc))
 */
size_t list_countb(const list *this, size_t sizevar, void *valor);

/**
 * @brief Recorre la lista desde inicio hasta el final
 * @param this lista a recorrer
 * @param sizevar tamaño o longitud del dato
 * @param valor a contar
 * @param compare funcion de busqueda
 * @return  cantidad de elementos existentes en la lista
 * @note Complejidad temporal O(n)
 */
size_t list_countf(const list *this, size_t sizevar, void *valor, int (*compare)(void *, void *));

/**
 * @brief Retorna una lista filtrada
 * @param this lista a recorrer
 * @param filter funcion de busqueda
 * @return lista filtrada
 * @note Complejidad temporal O(n)
 * @note operaciones de filtrado simple
 */
list list_filter(const list *this, int (*filter)(void *));

/**
 * @brief conversion de un string a lista
 * @param s string a convertir
 * @return lista de caracteres
 * @note Complejidad temporal O(n)
 */
list list_str(const char *s);

/**
 * @brief imprime la lista usando función callback
 * @param this lista a imprimir
 * @param print funcion auxiliar para imprimir
 * @note Complejidad temporal O(n)
 */
void list_print(const list *this, void (*print)(void *));

/**
 * @brief imprime la lista usando formato de printf
 * @param this lista a imprimir
 * @param format cadena de formato (ej: "%d", "%f", "%c")
 * @note Complejidad temporal O(n)
 */
void list_printf(const list *this, const char *format);

#endif