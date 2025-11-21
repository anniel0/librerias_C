# Cola (Queue) en C 📊

[![C Language](https://img.shields.io/badge/Language-C-blue.svg)](https://www.cprogramming.com/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](../LICENSE)
[![Status](https://img.shields.io/badge/Status-Stable-brightgreen.svg)](https://github.com/anniel0/librerias_C)

Una implementación eficiente de una estructura de datos Cola (FIFO - First In, First Out) en C, con manejo robusto de memoria y operaciones completas.

## 📋 Características

- **Operaciones básicas**: enqueue (encolar), dequeue (desencolar)
- **Consultas**: front (frente), isEmpty (está vacía)
- **Gestión de memoria** automática y segura
- **Código documentado** y fácil de entender
- **Manejo de errores** robusto
- **Tamaño dinámico**

## 🏗️ Estructura de Datos

```c
typedef struct qnodo {
    void* dato;               // Datos almacenados en el nodo
    struct qnodo* prox; // Puntero al siguiente nodo
} nodo;

typedef struct {
    nodo* frente;   // Puntero al primer elemento de la cola
    nodo* final;    // Puntero al último elemento de la cola
    size_t size_data; // tamaño de dato en memoria
    int tamaño;     // Número de elementos en la cola
} queue;


## 📚 API de la Librería

### Funciones Principales

| Función | Descripción | Complejidad |
|---------|-------------|-------------|
| `crearCola()` | Crea una nueva cola vacía | O(1) |
| `encolar(cola, dato)` | Agrega elemento al final de la cola | O(1) |
| `desencolar(cola)` | Elimina y retorna el elemento del frente | O(1) |
| `frenteCola(cola)` | Retorna el elemento del frente sin eliminarlo | O(1) |
| `estaVacia(cola)` | Verifica si la cola está vacía | O(1) |
| `tamanoCola(cola)` | Retorna el número de elementos en la cola | O(1) |
| `mostrarCola(cola)` | Muestra todos los elementos de la cola | O(n) |
| `liberarCola(cola)` | Libera toda la memoria utilizada por la cola | O(n) |

## 🔧 Instalación

### Compilación Manual
```bash
gcc -c queue.c -o queue.o
gcc tu_programa.c queue.o -o tu_programa
```

### Usando el Makefile
```bash
make all          # Compila la librería y el ejemplo
make example      # Compila y ejecuta el programa de ejemplo
make clean        # Limpia los archivos compilados
```

### Casos de Prueba Incluidos
- Creación de cola vacía
- Operaciones de encolar y desencolar
- Comportamiento FIFO (primero en entrar, primero en salir)
- Manejo de cola vacía
- Verificación de tamaño y estado
- Liberación de memoria

## 📊 Complejidad Algorítmica

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| crearCola() | O(1) | O(1) |
| encolar() | O(1) | O(1) |
| desencolar() | O(1) | O(1) |
| frenteCola() | O(1) | O(1) |
| estaVacia() | O(1) | O(1) |
| tamanoCola() | O(1) | O(1) |
| mostrarCola() | O(n) | O(1) |
| liberarCola() | O(n) | O(1) |

## 🤝 Contribuir

Si deseas mejorar esta librería:

1. Haz fork del repositorio
2. Crea una rama para tu feature (`git checkout -b feature/nueva-mejora`)
3. Commit tus cambios (`git commit -am 'Agrega nueva mejora'`)
4. Push a la rama (`git push origin feature/nueva-mejora`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo [LICENSE](../LICENSE) para más detalles.

---

**¿Problemas o sugerencias?** Abre un [issue](https://github.com/anniel0/librerias_C/issues) en el repositorio principal.

**¿Te fue útil?** ¡Dale una ⭐ al repositorio!
```
