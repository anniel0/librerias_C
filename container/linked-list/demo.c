#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

// ==================== FUNCIONES DE VISUALIZACIÓN ====================

void print_header(const char *title)
{
    printf("\n%s\n", title);
    for (int i = 0; i < strlen(title); i++)
        printf("=");
    printf("\n");
}

void print_subheader(const char *title)
{
    printf("\n▶ %s\n", title);
    for (int i = 0; i < strlen(title) + 2; i++)
        printf("-");
    printf("\n");
}

void print_int(void *data)
{
    if (data)
        printf("%d", *(int *)data);
    else
        printf("NULL");
}

void print_char(void *data)
{
    if (data)
        printf("'%c'", *(char *)data);
    else
        printf("NULL");
}

void print_string_ptr(void *data)
{
    if (data)
    {
        char **str_ptr = (char **)data;
        if (*str_ptr)
            printf("\"%s\"", *str_ptr);
        else
            printf("(null)");
    }
    else
        printf("NULL");
}

int compare_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int compare_string_ptr(const void *a, const void *b)
{
    char **str_a = (char **)a;
    char **str_b = (char **)b;
    return strcmp(*str_a, *str_b);
}

int filter_even(void *data)
{
    return (*(int *)data) % 2 == 0;
}

int filter_greater_than_5(void *data)
{
    return *(int *)data > 5;
}

void destroy_string_ptr(void *data)
{
    if (data)
    {
        char **str_ptr = (char **)data;
        if (*str_ptr)
        {
            free(*str_ptr);
        }
    }
}

// ==================== DEMOSTRACIONES VISUALES ====================

void demo_creacion_basica()
{
    print_subheader("Creación de Lista");

    list l = list_create(sizeof(int));
    printf("Lista creada: ");
    list_print(&l, print_int);
    printf("¿Está vacía? %s\n", list_empty(l) ? "Sí" : "No");

    int values[] = {10, 20, 30, 40, 50};
    printf("\nAgregando elementos: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", values[i]);
        list_append(&l, &values[i]);
    }
    printf("\n");

    printf("Lista actual: ");
    list_print(&l, print_int);
    printf("Tamaño: %d\n", list_length(l));

    int front_val, back_val;
    list_front(l, &front_val);
    list_back(l, &back_val);
    printf("Primer elemento: %d\n", front_val);
    printf("Último elemento: %d\n", back_val);

    list_free(&l);
}

void demo_insercion_eliminacion()
{
    print_subheader("Inserción y Eliminación");

    list l = list_create(sizeof(int));
    printf("Lista inicial vacía: ");
    list_print(&l, print_int);

    // Insertar al inicio
    int vals_start[] = {3, 2, 1};
    printf("\nInsertando al inicio: ");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", vals_start[i]);
        list_appstart(&l, &vals_start[i]);
    }
    printf("\nLista: ");
    list_print(&l, print_int);

    // Insertar al final
    int vals_end[] = {4, 5, 6};
    printf("\nInsertando al final: ");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", vals_end[i]);
        list_append(&l, &vals_end[i]);
    }
    printf("\nLista: ");
    list_print(&l, print_int);

    // Eliminar del inicio
    printf("\nEliminando primer elemento...\n");
    list_popstart(&l);
    printf("Lista: ");
    list_print(&l, print_int);

    // Eliminar del final
    printf("Eliminando último elemento...\n");
    list_popend(&l);
    printf("Lista: ");
    list_print(&l, print_int);

    // Insertar en posición específica
    int insert_val = 99;
    printf("\nInsertando %d en posición 2...\n", insert_val);
    list_insert(&l, 2, &insert_val);
    printf("Lista: ");
    list_print(&l, print_int);

    // Eliminar de posición específica
    printf("Eliminando elemento en posición 3...\n");
    list_pop(&l, 3);
    printf("Lista: ");
    list_print(&l, print_int);

    list_free(&l);
}

void demo_acceso_modificacion()
{
    print_subheader("Acceso y Modificación");

    list l = list_create(sizeof(int));
    int values[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++)
    {
        list_append(&l, &values[i]);
    }

    printf("Lista original: ");
    list_print(&l, print_int);

    // Acceder por posición
    printf("\nAccediendo por posición:\n");
    for (int i = 0; i < list_length(l); i++)
    {
        int *elem = (int *)list_at(l, i);
        printf("  Posición %d: %d\n", i, *elem);
    }

    // Modificar elementos
    int new_first = 111;
    int new_last = 555;
    int new_mid = 333;

    printf("\nModificando elementos:\n");
    list_setfirst(&l, &new_first);
    printf("  Cambiando primer elemento a %d\n", new_first);

    list_setlast(&l, &new_last);
    printf("  Cambiando último elemento a %d\n", new_last);

    list_set(&l, 2, &new_mid);
    printf("  Cambiando elemento en posición 2 a %d\n", new_mid);

    printf("\nLista modificada: ");
    list_print(&l, print_int);

    list_free(&l);
}

void demo_busqueda_conteo()
{
    print_subheader("Búsqueda y Conteo");

    list l = list_create(sizeof(int));
    int values[] = {1, 2, 3, 2, 4, 2, 5, 2};
    printf("Creando lista con valores: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", values[i]);
        list_append(&l, &values[i]);
    }
    printf("\n");

    printf("Lista: ");
    list_print(&l, print_int);

    int target = 2;
    printf("\nBuscando el valor %d:\n", target);

    // Buscar primera ocurrencia
    long pos = list_findb(&l, sizeof(int), &target);
    printf("  Primera ocurrencia (usando bytes): posición %ld\n", pos);

    pos = list_findf(&l, sizeof(int), &target, compare_int);
    printf("  Primera ocurrencia (usando función): posición %ld\n", pos);

    // Contar ocurrencias
    size_t count = list_countb(&l, sizeof(int), &target);
    printf("  Cantidad total (usando bytes): %zu\n", count);

    count = list_countf(&l, sizeof(int), &target, compare_int);
    printf("  Cantidad total (usando función): %zu\n", count);

    // Eliminar primera ocurrencia
    printf("\nEliminando primera ocurrencia de %d...\n", target);
    list_remove(&l, &target, compare_int);
    printf("Lista después: ");
    list_print(&l, print_int);

    // Eliminar todas las ocurrencias
    printf("\nEliminando todas las ocurrencias de %d...\n", target);
    int removed = list_removeAll(&l, &target, compare_int);
    printf("Eliminados %d elementos\n", removed);
    printf("Lista después: ");
    list_print(&l, print_int);

    list_free(&l);
}

void demo_ordenamiento()
{
    print_subheader("Ordenamiento");

    list l = list_create(sizeof(int));
    int values[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    printf("Lista desordenada: ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d ", values[i]);
        list_append(&l, &values[i]);
    }
    printf("\n");

    printf("Lista original: ");
    list_print(&l, print_int);

    // Orden ascendente
    printf("\nOrdenando ascendente...\n");
    list_sort(&l, compare_int);
    printf("Lista ordenada: ");
    list_print(&l, print_int);
    printf("¿Está ordenada? %s\n", list_is_sorted(&l, compare_int) ? "Sí" : "No");

    // Orden descendente
    printf("\nOrdenando descendente...\n");
    list_sort_reverse(&l, compare_int);
    printf("Lista ordenada descendente: ");
    list_print(&l, print_int);

    // Ordenamiento iterativo
    printf("\nCreando nueva lista desordenada...\n");
    list l2 = list_create(sizeof(int));
    int values2[] = {9, 2, 5, 1, 8, 3, 7, 4, 6};
    for (int i = 0; i < 9; i++)
    {
        list_append(&l2, &values2[i]);
    }
    printf("Lista antes: ");
    list_print(&l2, print_int);

    printf("Ordenando con algoritmo iterativo...\n");
    list_sortIterativo(&l2, compare_int);
    printf("Lista después: ");
    list_print(&l2, print_int);

    list_free(&l);
    list_free(&l2);
}

void demo_fusion_ordenada()
{
    print_subheader("Fusión de Listas Ordenadas");

    list l1 = list_create(sizeof(int));
    list l2 = list_create(sizeof(int));

    int vals1[] = {1, 3, 5, 7};
    int vals2[] = {2, 4, 6, 8};

    printf("Lista 1: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", vals1[i]);
        list_append(&l1, &vals1[i]);
    }
    printf("\n");

    printf("Lista 2: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", vals2[i]);
        list_append(&l2, &vals2[i]);
    }
    printf("\n");

    printf("\nFusionando listas ordenadas...\n");
    list_merge_sorted(&l1, &l2, compare_int);

    printf("Lista fusionada: ");
    list_print(&l1, print_int);
    printf("Tamaño: %d\n", list_length(l1));

    list_free(&l1);
}

void demo_filtrado_copia()
{
    print_subheader("Filtrado y Copia");

    list l = list_create(sizeof(int));
    printf("Creando lista con números 1 al 10: ");
    for (int i = 1; i <= 10; i++)
    {
        printf("%d ", i);
        list_append(&l, &i);
    }
    printf("\n");

    printf("Lista original: ");
    list_print(&l, print_int);

    // Filtrar números pares
    printf("\nFiltrando números pares...\n");
    list pares = list_filter(&l, filter_even);
    printf("Números pares: ");
    list_print(&pares, print_int);

    // Filtrar números mayores que 5
    printf("\nFiltrando números mayores que 5...\n");
    list mayores = list_filter(&l, filter_greater_than_5);
    printf("Números > 5: ");
    list_print(&mayores, print_int);

    // Crear copia
    printf("\nCreando copia de la lista original...\n");
    list copia = list_copy(&l);
    printf("Copia: ");
    list_print(&copia, print_int);

    // Modificar copia sin afectar original
    int nuevo_valor = 999;
    printf("\nModificando primer elemento de la copia a %d...\n", nuevo_valor);
    list_setfirst(&copia, &nuevo_valor);

    int orig_first, copy_first;
    list_front(l, &orig_first);
    list_front(copia, &copy_first);

    printf("Original - primer elemento: %d\n", orig_first);
    printf("Copia - primer elemento: %d\n", copy_first);

    list_free(&l);
    list_free(&pares);
    list_free(&mayores);
    list_free(&copia);
}

void demo_sublista_concatenacion()
{
    print_subheader("Sublista y Concatenación");

    list l = list_create(sizeof(int));
    printf("Creando lista con números 0 al 9: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i);
        list_append(&l, &i);
    }
    printf("\n");

    printf("Lista original: ");
    list_print(&l, print_int);

    // Crear sublista
    printf("\nCreando sublista (posiciones 2 a 7):\n");
    list sub = list_sublist(&l, 2, 7);
    printf("Sublista: ");
    list_print(&sub, print_int);

    // Crear lista adicional
    printf("\nCreando lista adicional con valores 100, 200, 300:\n");
    list extra = list_create(sizeof(int));
    int extra_vals[] = {100, 200, 300};
    for (int i = 0; i < 3; i++)
    {
        list_append(&extra, &extra_vals[i]);
    }
    printf("Lista adicional: ");
    list_print(&extra, print_int);

    // Concatenar
    printf("\nConcatenando listas...\n");
    list_concat(&l, &extra);
    printf("Lista concatenada: ");
    list_print(&l, print_int);
    printf("Tamaño total: %d\n", list_length(l));

    list_free(&l);
    list_free(&sub);
    list_free(&extra);
}

void demo_inversion_duplicados()
{
    print_subheader("Inversión y Eliminación de Duplicados");

    list l = list_create(sizeof(int));
    int values[] = {1, 2, 3, 4, 5};
    printf("Creando lista: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", values[i]);
        list_append(&l, &values[i]);
    }
    printf("\n");

    printf("Lista original: ");
    list_print(&l, print_int);

    // Invertir lista
    printf("\nInvirtiendo lista...\n");
    list_reverse(&l);
    printf("Lista invertida: ");
    list_print(&l, print_int);

    // Volver a invertir
    printf("\nVolviendo a invertir...\n");
    list_reverse(&l);
    printf("Lista original restaurada: ");
    list_print(&l, print_int);

    // Lista con duplicados consecutivos
    printf("\n\nCreando lista con duplicados consecutivos:\n");
    list dup = list_create(sizeof(int));
    int dup_vals[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4};
    for (int i = 0; i < 10; i++)
    {
        list_append(&dup, &dup_vals[i]);
    }
    printf("Lista con duplicados: ");
    list_print(&dup, print_int);

    // Primero ordenar (list_unique requiere lista ordenada)
    list_sort(&dup, compare_int);
    printf("Lista ordenada: ");
    list_print(&dup, print_int);

    // Eliminar duplicados consecutivos
    printf("\nEliminando duplicados consecutivos...\n");
    int removed = list_unique(&dup, compare_int);
    printf("Eliminados %d elementos\n", removed);
    printf("Lista sin duplicados consecutivos: ");
    list_print(&dup, print_int);

    // Eliminar todas las ocurrencias de un valor específico
    printf("\n\nCreando lista con múltiples ocurrencias del mismo valor:\n");
    list dedup = list_create(sizeof(int));
    int target = 5;
    for (int i = 0; i < 10; i++)
    {
        list_append(&dedup, &target);
    }
    printf("Lista con 10 ocurrencias del valor %d: ", target);
    list_print(&dedup, print_int);

    printf("\nEliminando duplicados (manteniendo una ocurrencia)...\n");
    int dedup_removed = list_deduplicate(&dedup, &target, compare_int);
    printf("Eliminados %d elementos\n", dedup_removed);
    printf("Lista resultante: ");
    list_print(&dedup, print_int);

    list_free(&l);
    list_free(&dup);
    list_free(&dedup);
}

void demo_iteradores()
{
    print_subheader("Iteradores");

    list l = list_create(sizeof(int));
    printf("Creando lista: ");
    for (int i = 1; i <= 5; i++)
    {
        printf("%d ", i * 10);
        list_append(&l, &(int){i * 10});
    }
    printf("\n");

    printf("Lista: ");
    list_print(&l, print_int);

    // Iteración hacia adelante
    printf("\nIteración hacia adelante:\n");
    list_iterator_begin(&l);
    int count = 0;
    while (list_iterator_valid(&l))
    {
        int *val = (int *)list_iterator_current(&l);
        printf("  Elemento %d: %d\n", count, *val);
        if (!list_iterator_next(&l))
            break;
        count++;
    }

    // Iteración hacia atrás
    printf("\nIteración hacia atrás:\n");
    list_iterator_beginReverse(&l);
    count = list_length(l) - 1;
    while (list_iterator_valid(&l))
    {
        int *val = (int *)list_iterator_current(&l);
        printf("  Elemento %d: %d\n", count, *val);
        if (!list_iterator_prev(&l))
            break;
        count--;
    }

    // Modificar usando iterador
    printf("\nModificando tercer elemento usando iterador...\n");
    list_iterator_begin(&l);
    for (int i = 0; i < 2; i++)
    {
        list_iterator_next(&l);
    }

    int new_value = 999;
    list_iterator_set(&l, &new_value);
    printf("Lista después de modificar: ");
    list_print(&l, print_int);

    list_free(&l);
}

void demo_operaciones_strings()
{
    print_subheader("Operaciones con Strings");

    // Convertir string a lista de caracteres
    printf("Convirtiendo string 'Hola Mundo' a lista de caracteres:\n");
    list chars = list_str("Hola Mundo");
    printf("Lista de caracteres: ");
    list_print(&chars, print_char);
    printf("Tamaño: %d\n", list_length(chars));

    // Iterar sobre caracteres
    printf("\nIterando sobre caracteres:\n");
    list_iterator_begin(&chars);
    while (list_iterator_valid(&chars))
    {
        char *c = (char *)list_iterator_current(&chars);
        printf("  '%c' ", *c);
        list_iterator_next(&chars);
    }
    printf("\n");

    // Dividir string por delimitador
    printf("\n\nDividiendo string 'manzana,pera,banana,uva' por comas:\n");
    list tokens = list_split_str("manzana,pera,banana,uva", ",");
    printf("Tokens encontrados: ");
    list_print(&tokens, print_string_ptr);

    // Mostrar cada token
    printf("\nTokens individuales:\n");
    for (int i = 0; i < list_length(tokens); i++)
    {
        char **token = (char **)list_at(tokens, i);
        printf("  Token %d: \"%s\"\n", i, *token);
    }

    // Array a lista (con enteros para demostración)
    printf("\n\nConvirtiendo array de enteros a lista:\n");
    int arr[] = {100, 200, 300, 400, 500};
    list from_arr = list_arr(arr, 5, sizeof(int));
    printf("Array convertido a lista: ");
    list_print(&from_arr, print_int);

    // Limpiar
    list_free(&chars);
    list_destroy(&tokens, destroy_string_ptr);
    list_free(&from_arr);
}

void demo_clear_destroy()
{
    print_subheader("Clear y Destroy");

    // Crear lista con datos simples
    list l = list_create(sizeof(int));
    printf("Creando lista con 5 elementos...\n");
    for (int i = 1; i <= 5; i++)
    {
        list_append(&l, &(int){i * 100});
    }
    printf("Lista: ");
    list_print(&l, print_int);

    // Usar clear
    printf("\nUsando list_clear...\n");
    int cleared = list_clear(&l, NULL);
    printf("Elementos eliminados: %d\n", cleared);
    printf("Lista después de clear: ");
    list_print(&l, print_int);
    printf("¿Está vacía? %s\n", list_empty(l) ? "Sí" : "No");

    // Crear lista con strings (necesita destroy)
    printf("\n\nCreando lista de strings...\n");
    list str_list = list_create(sizeof(char *));

    char *str1 = strdup("Primer string");
    char *str2 = strdup("Segundo string");
    char *str3 = strdup("Tercer string");

    list_append(&str_list, &str1);
    list_append(&str_list, &str2);
    list_append(&str_list, &str3);

    printf("Lista de strings: ");
    list_print(&str_list, print_string_ptr);

    printf("\nUsando list_destroy con función personalizada...\n");
    list_destroy(&str_list, destroy_string_ptr);
    printf("Lista destruida correctamente.\n");

    list_free(&l);
}

void demo_rendimiento()
{
    print_subheader("Demostración de Rendimiento");

    const int SIZE = 20; // Reducido para visualización

    printf("Creando lista grande con %d elementos aleatorios...\n", SIZE);
    list big = list_create(sizeof(int));

    printf("Elementos: ");
    for (int i = 0; i < SIZE; i++)
    {
        int val = rand() % 100;
        printf("%d ", val);
        list_append(&big, &val);
    }
    printf("\n");

    printf("\nTamaño de la lista: %d\n", list_length(big));

    printf("\nOrdenando lista grande...\n");
    list_sort(&big, compare_int);
    printf("Lista ordenada (primeros 10 elementos): ");

    // Mostrar solo primeros 10 elementos
    printf("[");
    for (int i = 0; i < 10 && i < list_length(big); i++)
    {
        int *val = (int *)list_at(big, i);
        printf("%d", *val);
        if (i < 9 && i < list_length(big) - 1)
            printf(", ");
    }
    if (list_length(big) > 10)
        printf(", ...");
    printf("]\n");

    printf("\nCreando copia de la lista grande...\n");
    list copy = list_copy(&big);
    printf("Copia creada. Tamaño: %d\n", list_length(copy));

    printf("\nFiltrando números pares...\n");
    list filtered = list_filter(&big, filter_even);
    printf("Elementos pares encontrados: %d\n", list_length(filtered));

    printf("\nCreando sublista (elementos 5 a 15)...\n");
    list sub = list_sublist(&big, 5, 15);
    printf("Sublista creada. Tamaño: %d\n", list_length(sub));

    // Liberar memoria
    list_free(&big);
    list_free(&copy);
    list_free(&filtered);
    list_free(&sub);

    printf("\nTodas las operaciones completadas exitosamente.\n");
}

// ==================== MAIN ====================

int main()
{
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║          DEMOSTRACIÓN VISUAL DE LIBRERÍA LIST.H          ║\n");
    printf("║           Listas Doblemente Enlazadas en C               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    srand(42); // Semilla fija para resultados reproducibles

    int opcion;
    do
    {
        system("clear");
        printf("\n\n════════════════════════════════════════════════════════════\n");
        printf("MENÚ DE DEMOSTRACIONES:\n");
        printf("════════════════════════════════════════════════════════════\n");
        printf(" 1. Creación Básica y Estado\n");
        printf(" 2. Inserción y Eliminación\n");
        printf(" 3. Acceso y Modificación\n");
        printf(" 4. Búsqueda y Conteo\n");
        printf(" 5. Ordenamiento\n");
        printf(" 6. Fusión de Listas Ordenadas\n");
        printf(" 7. Filtrado y Copia\n");
        printf(" 8. Sublista y Concatenación\n");
        printf(" 9. Inversión y Eliminación de Duplicados\n");
        printf("10. Iteradores\n");
        printf("11. Operaciones con Strings\n");
        printf("12. Clear y Destroy\n");
        printf("13. Demostración de Rendimiento\n");
        printf(" 0. Salir\n");
        printf("════════════════════════════════════════════════════════════\n");
        printf("Seleccione una opción (0-13): ");

        if (scanf("%d", &opcion) != 1)
        {
            printf("Entrada inválida.\n");
            while (getchar() != '\n')
                ; // Limpiar buffer
            continue;
        }

        switch (opcion)
        {
        case 1:
            demo_creacion_basica();
            break;
        case 2:
            demo_insercion_eliminacion();
            break;
        case 3:
            demo_acceso_modificacion();
            break;
        case 4:
            demo_busqueda_conteo();
            break;
        case 5:
            demo_ordenamiento();
            break;
        case 6:
            demo_fusion_ordenada();
            break;
        case 7:
            demo_filtrado_copia();
            break;
        case 8:
            demo_sublista_concatenacion();
            break;
        case 9:
            demo_inversion_duplicados();
            break;
        case 10:
            demo_iteradores();
            break;
        case 11:
            demo_operaciones_strings();
            break;
        case 12:
            demo_clear_destroy();
            break;
        case 13:
            demo_rendimiento();
            break;
        case 0:
            printf("\nSaliendo...\n");
            break;
        default:
            printf("Opción inválida. Intente de nuevo.\n");
        }

        if (opcion != 0)
        {
            printf("\n════════════════════════════════════════════════════════════\n");
            printf("Presione Enter para continuar...");
            while (getchar() != '\n')
                ;      // Limpiar buffer
            getchar(); // Esperar Enter
        }

    } while (opcion != 0);

    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║         DEMOSTRACIÓN COMPLETADA EXITOSAMENTE            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");

    return 0;
}