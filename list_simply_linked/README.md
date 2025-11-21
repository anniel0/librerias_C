# Lista Simplemente Enlazada 🔗

[![C Language](https://img.shields.io/badge/Language-C-blue.svg)](https://www.cprogramming.com/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](../LICENSE)
[![Status](https://img.shields.io/badge/Status-Stable-brightgreen.svg)](https://github.com/anniel0/librerias_C)

Una implementación eficiente y robusta de una lista simplemente enlazada en C, con operaciones completas para manipulación de datos.

## 📋 Características

- **Inserción** al inicio, final y en posición específica
- **Eliminación** de nodos por valor, posición o liberación completa
- **Búsqueda** de elementos por valor
- **Recorrido** e impresión de la lista
- **Gestión automática** de memoria
- **Código documentado** y fácil de entender
- **Manejo de errores** robusto


## 📚 API de la Librería

### Funciones Principales

| Función | Descripción | Complejidad |
|---------|-------------|-------------|
| `create_list()` | Crea una nueva lista vacía | O(1) |
| `app_end(list, data)` | Agrega elemento al final | O(n) |
| `app_start(list, data)` | Agrega elemento al inicio | O(1) |
| `app_position(list, data, position)` | Inserta en posición específica | O(n) |
| `delete_position(list, position)` | Elimina nodo por posición | O(n) |
| `search(list, data)` | Busca elemento en la lista | O(n) |
| `list_size(list)` | Retorna el tamaño de la lista | O(1) |
| `print_list(list)` | Imprime todos los elementos | O(n) |
| `delete_list(list)` | Libera toda la memoria | O(n) |

## 🔧 Instalación

### Compilación Manual
```bash
gcc -c list.c -o list.o
gcc tu_programa.c list.o -o tu_programa
```

### Usando el Makefile
```bash
make all          # Compila la librería y el ejemplo
make example      # Compila y ejecuta el programa de ejemplo
make clean        # Limpia los archivos compilados
make test         # Compila y ejecuta las pruebas
```
## 📝 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo [LICENSE](../LICENSE) para más detalles.

---

**¿Problemas o sugerencias?** Abre un [issue](https://github.com/anniel0/librerias_C/issues) en el repositorio principal.
``
