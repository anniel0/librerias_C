# Librería de Conjuntos en C

Una implementación genérica de conjuntos (Sets) en lenguaje C que permite almacenar elementos de cualquier tipo mediante el uso de punteros void y funciones de comparación personalizadas.

## Características

- **Genérica**: Almacena cualquier tipo de dato
- **Flexible**: Soporta funciones de pertenencia personalizadas
- **Completa**: Implementa todas las operaciones básicas de conjuntos
- **Eficiente**: Incluye algoritmos de ordenamiento optimizados
- **Segura**: Manejo robusto de memoria y verificación de errores

## Estructuras de Datos

### setnodo
```c
typedef struct setnodo {
    void *elem;           // Puntero al elemento
    struct setnodo *prox; // Puntero al siguiente nodo
} setnodo;
```

### set
```c
typedef struct {
    setnodo *head, *tail; // Primer y último nodo
    size_t data;          // Tamaño de cada elemento
    int size;             // Cantidad de elementos
    int (*pertain)(const void *, const void *); // Función de pertenencia
} set;
```

## API de la Librería

### Creación y Destrucción

#### `new_setnodo(void *elem, size_t data)`
Crea un nuevo nodo para el conjunto.
```c
int valor = 42;
setnodo *nodo = new_setnodo(&valor, sizeof(int));
```

#### `new_set(size_t data)`
Crea un conjunto vacío.
```c
set conjunto = new_set(sizeof(int));
```

#### `new_setin(size_t data, int (*pertain)(const void *, const void *))`
Crea un conjunto con función de pertenencia personalizada.
```c
int comparar_enteros(const void *a, const void *b) {
    return *(int*)a == *(int*)b;
}
set conjunto = new_setin(sizeof(int), comparar_enteros);
```

#### `free_set(set *prime)`
Libera toda la memoria del conjunto.
```c
free_set(&conjunto);
```

### Operaciones Básicas

#### `set_app(set *prime, void *elem)`
Agrega un elemento al conjunto si no existe.
```c
int nuevo_elemento = 100;
set_app(&conjunto, &nuevo_elemento);
```

#### `set_pertain(const set *prime, void *elem)`
Verifica si un elemento pertenece al conjunto.
```c
if (set_pertain(&conjunto, &elemento_buscado)) {
    printf("Elemento encontrado\n");
}
```

#### `set_popat(set *prime, int position)`
Elimina un elemento en una posición específica.
```c
set_popat(&conjunto, 2); // Elimina el tercer elemento
```

#### `set_size(const set prime)`
Retorna el número de elementos.
```c
int cantidad = set_size(conjunto);
```

#### `set_empty(const set prime)`
Verifica si el conjunto está vacío.
```c
if (set_empty(conjunto)) {
    printf("Conjunto vacío\n");
}
```

### Operaciones de Conjunto

#### `set_union(const set *prime, const set *otro)`
Unión de dos conjuntos.
```c
set union = set_union(&conjunto1, &conjunto2);
```

#### `set_intersection(const set *prime, const set *otro)`
Intersección de dos conjuntos.
```c
set interseccion = set_intersection(&conjunto1, &conjunto2);
```

#### `set_difference(const set *prime, const set *otro)`
Diferencia entre conjuntos.
```c
set diferencia = set_difference(&conjunto1, &conjunto2);
```

#### `set_subset(const set *prime, const set *otro)`
Verifica si un conjunto es subconjunto de otro.
```c
if (set_subset(&conjunto1, &conjunto2)) {
    printf("conjunto1 es subconjunto de conjunto2\n");
}
```

### Acceso y Manipulación

#### `set_at(const set *prime, int position, void *elem)`
Obtiene un elemento por posición.
```c
int elemento;
set_at(&conjunto, 0, &elemento); // Obtiene el primer elemento
```

#### `set_swap(set *prime, int pos1, int pos2)`
Intercambia dos elementos.
```c
set_swap(&conjunto, 0, 1); // Intercambia primer y segundo elemento
```

### Ordenamiento

#### `set_msort(set *prime, int (*compare)(const void *, const void *))`
Ordena el conjunto usando merge sort con función de comparación.
```c
int comparar(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}
set_msort(&conjunto, comparar);
```

#### `set_msortb(set *prime)`
Ordena el conjunto usando memcmp para comparación binaria.
```c
set_msortb(&conjunto);
```

### Conversiones

#### `set_to_array(const set prime)`
Convierte el conjunto a un arreglo.
```c
void **arreglo = set_to_array(conjunto);
```

#### `array_to_set(void *arr, int size, size_t data_size)`
Crea un conjunto a partir de un arreglo.
```c
int arreglo[] = {1, 2, 3, 4, 5};
set conjunto = array_to_set(arreglo, 5, sizeof(int));
```

#### `set_filter(const set *prime, int (*filter)(const void *))`
Filtra el conjunto según una condición.
```c
int es_par(const void *elem) {
    return (*(int*)elem % 2 == 0);
}
set pares = set_filter(&conjunto, es_par);
```

## Ejemplos de Uso

### Ejemplo 1: Conjunto de Enteros
```c
#include "set.h"
#include <stdio.h>

int main() {
    // Crear conjunto de enteros
    set conjunto = new_set(sizeof(int));
    
    // Agregar elementos
    int elementos[] = {5, 2, 8, 1, 9};
    for (int i = 0; i < 5; i++) {
        set_app(&conjunto, &elementos[i]);
    }
    
    // Verificar pertenencia
    int buscado = 8;
    if (set_pertain(&conjunto, &buscado)) {
        printf("El elemento %d está en el conjunto\n", buscado);
    }
    
    // Mostrar tamaño
    printf("Tamaño del conjunto: %d\n", set_size(conjunto));
    
    // Liberar memoria
    free_set(&conjunto);
    
    return 0;
}
```

### Ejemplo 2: Conjunto de Strings
```c
#include "set.h"
#include <stdio.h>
#include <string.h>

int comparar_strings(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b) == 0;
}

int main() {
    // Crear conjunto de strings con función personalizada
    set conjunto = new_setin(50, comparar_strings);
    
    // Agregar strings
    char str1[] = "hola";
    char str2[] = "mundo";
    char str3[] = "programacion";
    
    set_app(&conjunto, str1);
    set_app(&conjunto, str2);
    set_app(&conjunto, str3);
    
    // Verificar si existe un string
    char buscado[] = "mundo";
    if (set_pertain(&conjunto, buscado)) {
        printf("La palabra '%s' está en el conjunto\n", buscado);
    }
    
    free_set(&conjunto);
    return 0;
}
```

### Ejemplo 3: Operaciones entre Conjuntos
```c
#include "set.h"
#include <stdio.h>

int main() {
    set A = new_set(sizeof(int));
    set B = new_set(sizeof(int));
    
    int a[] = {1, 2, 3, 4};
    int b[] = {3, 4, 5, 6};
    
    for (int i = 0; i < 4; i++) {
        set_app(&A, &a[i]);
        set_app(&B, &b[i]);
    }
    
    // Unión
    set union = set_union(&A, &B);
    printf("Unión: tamaño %d\n", set_size(union));
    
    // Intersección
    set interseccion = set_intersection(&A, &B);
    printf("Intersección: tamaño %d\n", set_size(interseccion));
    
    // Diferencia
    set diferencia = set_difference(&A, &B);
    printf("Diferencia A-B: tamaño %d\n", set_size(diferencia));
    
    free_set(&A);
    free_set(&B);
    free_set(&union);
    free_set(&interseccion);
    free_set(&diferencia);
    
    return 0;
}
```

## Compilación

Para usar la librería, simplemente incluye el archivo header y compila con tu programa:

```bash
gcc -o programa main.c set.c
```

## Notas Importantes

1. **Manejo de Memoria**: La librería asume que los elementos pasados son válidos durante la vida útil del conjunto
2. **Tipos de Datos**: Para tipos complejos, proporciona una función de pertenencia adecuada
3. **Thread Safety**: Esta implementación no es thread-safe
4. **Rendimiento**: Las operaciones de búsqueda son O(n), considere esto para conjuntos grandes

## Licencia

Esta librería es de uso libre para fines educativos y proyectos personales.
