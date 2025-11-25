# 📚 Librería de Conjuntos en C 

## 🏗️ Estructuras de Datos

| Estructura | Descripción | Campos |
|------------|-------------|---------|
| `setnodo` | Nodo del conjunto | `void *elem`, `setnodo *prox` |
| `set` | Conjunto principal | `head`, `tail`, `data`, `size`, `pertain` |

## 📋 Tabla de Funciones

### 🎯 Creación y Destrucción
| Función | Descripción | Complejidad | Retorno |
|---------|-------------|-------------|---------|
| **[new_setnodo](#new_setnodo)** | Crea nuevo nodo | O(1) | `setnodo*` |
| **[new_set](#new_set)** | Crea conjunto vacío | O(1) | `set` |
| **[new_setin](#new_setin)** | Conjunto con función personalizada | O(1) | `set` |
| **[free_set](#free_set)** | Libera memoria del conjunto | O(n) | `int` |

### 🔍 Operaciones Básicas
| Función | Descripción | Complejidad | Retorno |
|---------|-------------|-------------|---------|
| **[set_app](#set_app)** | Agrega elemento único | O(n) | `int` |
| **[set_pertain](#set_pertain)** | Verifica pertenencia | O(n) | `int` |
| **[set_popat](#set_popat)** | Elimina por posición | O(n) | `int` |
| **[set_size](#set_size)** | Cantidad de elementos | O(1) | `int` |
| **[set_empty](#set_empty)** | Verifica si está vacío | O(1) | `int` |
| **[set_at](#set_at)** | Obtiene elemento por posición | O(n) | `void` |
| **[set_swap](#set_swap)** | Intercambia elementos | O(n) | `int` |

### 🔄 Operaciones de Conjunto
| Función | Descripción | Complejidad | Retorno |
|---------|-------------|-------------|---------|
| **[set_union](#set_union)** | Unión de conjuntos | O(n×m) | `set` |
| **[set_intersection](#set_intersection)** | Intersección de conjuntos | O(n×m) | `set` |
| **[set_difference](#set_difference)** | Diferencia de conjuntos | O(n×m) | `set` |
| **[set_subset](#set_subset)** | Verifica subconjunto | O(n×m) | `int` |

### 📊 Ordenamiento
| Función | Descripción | Complejidad | Retorno |
|---------|-------------|-------------|---------|
| **[set_msort](#set_msort)** | Ordena con función comparación | O(n log n) | `void` |
| **[set_msortb](#set_msortb)** | Ordena con memcmp | O(n log n) | `void` |

### 🔄 Conversiones
| Función | Descripción | Complejidad | Retorno |
|---------|-------------|-------------|---------|
| **[set_to_array](#set_to_array)** | Convierte a arreglo | O(n) | `void**` |
| **[array_to_set](#array_to_set)** | Crea desde arreglo | O(n) | `set` |
| **[set_filter](#set_filter)** | Filtra elementos | O(n) | `set` |

---

## 📖 Documentación Detallada por Función

### <a name="new_setnodo"></a>🔹 `new_setnodo`
```c
setnodo *new_setnodo(void *elem, size_t data)
```
**Parámetros:**
- `elem`: Puntero al elemento a almacenar
- `data`: Tamaño en bytes del elemento

**Retorno:** Puntero al nuevo nodo o NULL en error

---

### <a name="new_set"></a>🔹 `new_set`
```c
set new_set(size_t data)
```
**Parámetros:**
- `data`: Tamaño en bytes de cada elemento

**Retorno:** Conjunto vacío inicializado

---

### <a name="new_setin"></a>🔹 `new_setin`
```c
set new_setin(size_t data, int (*pertain)(const void *, const void *))
```
**Parámetros:**
- `data`: Tamaño en bytes de cada elemento
- `pertain`: Función de comparación personalizada

**Retorno:** Conjunto con función de pertenencia personalizada

---

### <a name="free_set"></a>🔹 `free_set`
```c
int free_set(set *prime)
```
**Parámetros:**
- `prime`: Puntero al conjunto a liberar

**Retorno:** 1 en éxito, 0 en error

---

### <a name="set_app"></a>🔹 `set_app`
```c
int set_app(set *prime, void *elem)
```
**Parámetros:**
- `prime`: Conjunto destino
- `elem`: Elemento a agregar

**Retorno:** 1 si se agregó, 0 si ya existía o error

---

### <a name="set_pertain"></a>🔹 `set_pertain`
```c
int set_pertain(const set *prime, void *elem)
```
**Parámetros:**
- `prime`: Conjunto a verificar
- `elem`: Elemento a buscar

**Retorno:** 1 si pertenece, 0 si no pertenece

---

### <a name="set_popat"></a>🔹 `set_popat`
```c
int set_popat(set *prime, int position)
```
**Parámetros:**
- `prime`: Conjunto a modificar
- `position`: Posición del elemento a eliminar (0-based)

**Retorno:** 1 en éxito, 0 en error

---

### <a name="set_size"></a>🔹 `set_size`
```c
int set_size(const set prime)
```
**Parámetros:**
- `prime`: Conjunto a verificar

**Retorno:** Número de elementos en el conjunto

---

### <a name="set_empty"></a>🔹 `set_empty`
```c
int set_empty(const set prime)
```
**Parámetros:**
- `prime`: Conjunto a verificar

**Retorno:** 1 si está vacío, 0 si tiene elementos

---

### <a name="set_at"></a>🔹 `set_at`
```c
void set_at(const set *prime, int position, void *elem)
```
**Parámetros:**
- `prime`: Conjunto fuente
- `position`: Posición del elemento (0-based)
- `elem`: Buffer donde copiar el elemento

**Retorno:** void (resultado por referencia)

---

### <a name="set_swap"></a>🔹 `set_swap`
```c
int set_swap(set *prime, int pos1, int pos2)
```
**Parámetros:**
- `prime`: Conjunto a modificar
- `pos1`, `pos2`: Posiciones a intercambiar

**Retorno:** 1 en éxito, 0 en error

---

### <a name="set_union"></a>🔹 `set_union`
```c
set set_union(const set *prime, const set *otro)
```
**Parámetros:**
- `prime`, `otro`: Conjuntos a unir

**Retorno:** Nuevo conjunto con la unión

---

### <a name="set_intersection"></a>🔹 `set_intersection`
```c
set set_intersection(const set *prime, const set *otro)
```
**Parámetros:**
- `prime`, `otro`: Conjuntos para intersección

**Retorno:** Nuevo conjunto con la intersección

---

### <a name="set_difference"></a>🔹 `set_difference`
```c
set set_difference(const set *prime, const set *otro)
```
**Parámetros:**
- `prime`: Conjunto minuendo
- `otro`: Conjunto sustraendo

**Retorno:** Nuevo conjunto con A - B

---

### <a name="set_subset"></a>🔹 `set_subset`
```c
int set_subset(const set *prime, const set *otro)
```
**Parámetros:**
- `prime`: Supuesto superconjunto
- `otro`: Supuesto subconjunto

**Retorno:** 1 si B ⊆ A, 0 en caso contrario

---

### <a name="set_msort"></a>🔹 `set_msort`
```c
void set_msort(set *prime, int (*compare)(const void *, const void *))
```
**Parámetros:**
- `prime`: Conjunto a ordenar
- `compare`: Función de comparación

**Retorno:** void (ordenamiento in-place)

---

### <a name="set_msortb"></a>🔹 `set_msortb`
```c
void set_msortb(set *prime)
```
**Parámetros:**
- `prime`: Conjunto a ordenar

**Retorno:** void (ordenamiento in-place con memcmp)

---

### <a name="set_to_array"></a>🔹 `set_to_array`
```c
void **set_to_array(const set prime)
```
**Parámetros:**
- `prime`: Conjunto a convertir

**Retorno:** Arreglo dinámico con los elementos

---

### <a name="array_to_set"></a>🔹 `array_to_set`
```c
set array_to_set(void *arr, int size, size_t data_size)
```
**Parámetros:**
- `arr`: Arreglo fuente
- `size`: Número de elementos
- `data_size`: Tamaño de cada elemento

**Retorno:** Nuevo conjunto con elementos del arreglo

---

### <a name="set_filter"></a>🔹 `set_filter`
```c
set set_filter(const set *prime, int (*filter)(const void *))
```
**Parámetros:**
- `prime`: Conjunto a filtrar
- `filter`: Función de filtrado (retorna 1 para mantener)

**Retorno:** Nuevo conjunto filtrado

---

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
   
## 📝 Notas de Uso
- ✅ Verifica siempre los retornos de las funciones
- ✅ Usa `free_set` para liberar memoria
- ✅ Proporciona funciones de comparación para tipos complejos
- ❌ No modifiques elementos directamente en el conjunto
- ❌ No uses posiciones inválidas en operaciones por índice

Esta tabla proporciona una referencia rápida para todas las funciones disponibles en la librería de conjuntos.


## Licencia

Esta librería es de uso libre para fines educativos y proyectos personales.
