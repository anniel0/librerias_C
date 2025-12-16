#include <stdio.h>
#include "list.h"

// Función para imprimir entero
void print_int(void *data)
{
    printf("%d", *((int *)data));
}

int main()
{
    list nuevo = new_list(sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        list_append(&nuevo, &(int){i + 2});
    }

    printf("Lista impresa con list_printf: ");
    list_printf(&nuevo, "%d");

    printf("Lista impresa con list_print: ");
    list_print(&nuevo, print_int);

    // Probar búsqueda
    int buscar = 3;
    long pos = list_findb(&nuevo, sizeof(int), &buscar);
    printf("Elemento %d encontrado en posición: %ld\n", buscar, pos);

    // Contar elementos
    int contar = 2;
    size_t cantidad = list_countb(&nuevo, sizeof(int), &contar);
    printf("Elemento %d aparece %zu veces\n", contar, cantidad);

    // Liberar memoria
    delete_list(&nuevo);

    // Probar con strings
    list cadena = list_str("Hola");
    printf("Cadena como lista: ");
    list_printf(&cadena, "%c");
    delete_list(&cadena);

    return 0;
}
