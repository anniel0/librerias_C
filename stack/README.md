# Stack Library in C

Una implementación genérica de pila (stack) en C que utiliza memoria dinámica y permite almacenar cualquier tipo de dato.

## Características

- Implementación genérica usando `void*`
- Gestión automática de memoria
- Operaciones estándar de pila (push, pop, top)
- Funciones adicionales para manipulación avanzada
- Complejidad temporal óptima para operaciones básicas
- Tipo seguro en tiempo de compilación

## Tabla de Funciones

| Función | Descripción | Complejidad Temporal | Enlace |
|---------|-------------|---------------------|---------|
| **`new_stack`** | Crea una nueva pila vacía | O(1) | [Documentación](#new_stack) |
| **`new_snodo`** | Crea un nuevo nodo (interno) | O(1) | [Documentación](#new_snodo) |
| **`stack_push`** | Apila un elemento | O(1) | [Documentación](#stack_push) |
| **`stack_pop`** | Desapila un elemento | O(1) | [Documentación](#stack_pop) |
| **`stack_top`** | Obtiene el elemento de la cima | O(1) | [Documentación](#stack_top) |
| **`stack_size`** | Obtiene el número de elementos | O(1) | [Documentación](#stack_size) |
| **`stack_is_empty`** | Verifica si la pila está vacía | O(1) | [Documentación](#stack_is_empty) |
| **`stack_clear`** | Elimina todos los elementos | O(n) | [Documentación](#stack_clear) |
| **`stack_traverse`** | Recorre la pila ejecutando una función | O(n) | [Documentación](#stack_traverse) |
| **`stack_search`** | Busca un elemento en la pila | O(n) | [Documentación](#stack_search) |
| **`stack_copy`** | Copia toda la pila | O(n) | [Documentación](#stack_copy) |
| **`stack_reverse`** | Invierte el orden de los elementos | O(n) | [Documentación](#stack_reverse) |

## Documentación Detallada de Funciones

### `new_stack`

```c
stack new_stack(size_t size_data);
```

Crea una nueva pila vacía.

**Parámetros:**
- `size_data`: Tamaño en bytes de cada elemento

**Retorna:**
- Pila inicializada lista para usar

---

### `new_snodo`

```c
snodo *new_snodo(void *dato, size_t size_data);
```

Función interna que crea un nuevo nodo con los datos proporcionados.

**Parámetros:**
- `dato`: Puntero a los datos a almacenar
- `size_data`: Tamaño en bytes de los datos

**Retorna:**
- Puntero al nuevo nodo o NULL en caso de error

---

### `stack_push`

```c
int stack_push(stack *s, void *data);
```

Apila un elemento (inserta en la cima de la pila).

**Parámetros:**
- `s`: Puntero a la pila
- `data`: Puntero a los datos a apilar

**Retorna:**
- 1 si se apiló correctamente, 0 en caso de error

---

### `stack_pop`

```c
int stack_pop(stack *s);
```

Desapila un elemento (elimina de la cima de la pila).

**Parámetros:**
- `s`: Puntero a la pila

**Retorna:**
- 1 si se desapiló correctamente, 0 en caso de error

---

### `stack_top`

```c
void *stack_top(const stack s);
```

Obtiene el elemento de la cima de la pila sin eliminarlo.

**Parámetros:**
- `s`: Pila (por valor)

**Retorna:**
- Puntero al elemento de la cima o NULL si la pila está vacía

---

### `stack_size`

```c
int stack_size(const stack s);
```

Obtiene el tamaño de la pila (número de elementos).

**Parámetros:**
- `s`: Pila (por valor)

**Retorna:**
- Número de elementos en la pila

---

### `stack_is_empty`

```c
int stack_is_empty(const stack s);
```

Verifica si la pila está vacía.

**Parámetros:**
- `s`: Pila (por valor)

**Retorna:**
- 1 si la pila está vacía, 0 en caso contrario

---

### `stack_clear`

```c
int stack_clear(stack *s);
```

Elimina todos los elementos de la pila.

**Parámetros:**
- `s`: Puntero a la pila

**Retorna:**
- 1 si se vació correctamente, 0 en caso de error

---

### `stack_traverse`

```c
void stack_traverse(const stack s, void (*callback)(void *));
```

Recorre la pila ejecutando una función para cada elemento (de cima a base).

**Parámetros:**
- `s`: Pila (por valor)
- `callback`: Función a ejecutar para cada elemento

---

### `stack_search`

```c
int stack_search(const stack s, void *data, int (*compare)(const void *, const void *));
```

Busca un elemento en la pila usando una función de comparación.

**Parámetros:**
- `s`: Pila (por valor)
- `data`: Puntero a los datos a buscar
- `compare`: Función de comparación (devuelve 0 si son iguales)

**Retorna:**
- 1 si se encontró, 0 si no se encontró

---

### `stack_copy`

```c
int stack_copy(const stack src, stack *dest);
```

Copia toda la pila a otra pila.

**Parámetros:**
- `src`: Pila fuente (por valor)
- `dest`: Puntero a la pila destino

**Retorna:**
- 1 si se copió correctamente, 0 en caso de error

---

### `stack_reverse`

```c
int stack_reverse(stack *s);
```

Invierte el orden de los elementos en la pila.

**Parámetros:**
- `s`: Puntero a la pila a invertir

**Retorna:**
- 1 si se invirtió correctamente, 0 en caso de error

## Ejemplo de Uso

```c
#include "stack.h"
#include <stdio.h>

int main() {
    // Crear una pila para integers
    stack s = new_stack(sizeof(int));
    
    // Apilar algunos elementos
    int a = 10, b = 20, c = 30;
    stack_push(&s, &a);
    stack_push(&s, &b);
    stack_push(&s, &c);
    
    // Ver el elemento de la cima
    int *top = (int*)stack_top(s);
    printf("Cima: %d\n", *top); // Output: 30
    
    // Desapilar
    stack_pop(&s);
    
    // Verificar tamaño
    printf("Tamaño: %d\n", stack_size(s)); // Output: 2
    
    // Limpiar la pila
    stack_clear(&s);
    
    return 0;
}
```

## Compilación

```bash
gcc -c stack.c -o stack.o
gcc main.c stack.o -o programa
```

## Notas

- Todas las funciones que modifican la pila reciben un puntero a `stack`
- Las funciones de solo lectura reciben `stack` por valor
- La memoria se gestiona automáticamente, pero el usuario es responsable de los datos almacenados
- La pila es genérica y puede almacenar cualquier tipo de dato
