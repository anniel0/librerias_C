# Librerías en C 🚀

[![C Language](https://img.shields.io/badge/Language-C-blue.svg)](https://www.cprogramming.com/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Active-brightgreen.svg)](https://github.com/anniel0/librerias_C)

Una colección de librerías útiles y eficientes escritas en C para diversos propósitos y aplicaciones.

## 📚 Librerías Disponibles

### [Lista Enlazada](./linked_list/)
Implementación completa de una lista enlazada con todas las operaciones básicas:
- Inserción (inicio, final, posición específica)
- Eliminación de nodos
- Búsqueda de elementos
- Recorrido e impresión
- Liberación de memoria

### [Pila (Stack)](./stack/)
Implementación de una estructura LIFO (Last In, First Out) con:
- Push y pop de elementos
- Verificación de pila vacía
- Acceso al elemento superior
- Gestión de memoria automática

### [Cola (Queue)](./queue/)
Implementación de una estructura FIFO (First In, First Out) que incluye:
- Enqueue y dequeue
- Verificación de estado
- Gestión de elementos

## 🛠️ Características

- **Código limpio y bien documentado**
- **Implementaciones eficientes**
- **Manejo robusto de errores**
- **Completamente probado**
- **Fácil de integrar en tus proyectos**

## 📋 Requisitos

- Compilador de C (GCC recomendado)
- Sistema operativo: Linux, Windows o macOS
- Make (opcional, para usar los Makefiles incluidos)

## 🔧 Instalación y Uso

### Compilación Individual
```bash
gcc -c nombre_libreria.c -o nombre_libreria.o
gcc tu_programa.c nombre_libreria.o -o tu_programa
```

### Usando Makefiles
Cada librería incluye su propio Makefile:
```bash
cd nombre_libreria
make
```

### Ejemplo de Uso
```c
#include "linked_list/linked_list.h"

int main() {
    LinkedList* list = create_linked_list();
    
    // Agregar elementos
    append(list, 10);
    append(list, 20);
    
    // Imprimir lista
    print_list(list);
    
    // Liberar memoria
    free_linked_list(list);
    return 0;
}
```

## 🧪 Testing

Cada librería incluye ejemplos de uso y pruebas básicas. Para ejecutar las pruebas:

```bash
cd nombre_libreria
make test
./test
```

## 📁 Estructura del Proyecto

```
librerias_C/
├── linked_list/          # Implementación de lista enlazada
│   ├── linked_list.h     # Archivo de cabecera
│   ├── linked_list.c     # Implementación
│   ├── main.c           # Ejemplo de uso
│   └── Makefile         # Script de compilación
├── stack/               # Implementación de pila
│   ├── stack.h
│   ├── stack.c
│   ├── main.c
│   └── Makefile
├── queue/               # Implementación de cola
│   ├── queue.h
│   ├── queue.c
│   ├── main.c
│   └── Makefile
└── README.md           # Este archivo
```

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Si deseas agregar nuevas librerías o mejorar las existentes:

1. Haz un fork del proyecto
2. Crea una rama para tu feature (`git checkout -b feature/nueva-caracteristica`)
3. Commit tus cambios (`git commit -am 'Agrega nueva característica'`)
4. Push a la rama (`git push origin feature/nueva-caracteristica`)
5. Abre un Pull Request

## 📝 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo [LICENSE](LICENSE) para más detalles.

## 👨‍💻 Autor

Creado por [anniel0](https://github.com/anniel0)

## ⭐ Mostrar tu apoyo

Si este proyecto te fue útil, por favor dale una ⭐ al repositorio.

---

**¿Encontraste un bug?** Por favor abre un [issue](https://github.com/anniel0/librerias_C/issues) para que podamos solucionarlo.
```
