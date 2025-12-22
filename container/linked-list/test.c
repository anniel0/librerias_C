#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"

// ==================== FUNCIONES AUXILIARES ====================

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

void destroy_string_ptr(void *data)
{
    if (data)
    {
        char **str_ptr = (char **)data;
        if (*str_ptr)
        {
            free(*str_ptr);  // Libera el string
            *str_ptr = NULL; // Opcional: marca como NULL
        }
    }
}

// ==================== TESTS COMPREHENSIVOS ====================

void run_test(const char *name, void (*test_func)(void))
{
    printf("\n=== %s ===\n", name);
    test_func();
    printf("✅ %s completado\n", name);
}

void test_creation_and_basic_ops()
{
    list l = list_create(sizeof(int));
    assert(list_empty(l) == 1);
    assert(list_length(l) == 0);

    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
    {
        list_append(&l, &values[i]);
    }

    assert(list_empty(l) == 0);
    assert(list_length(l) == 5);

    int front_val, back_val;
    list_front(l, &front_val);
    list_back(l, &back_val);
    assert(front_val == 10);
    assert(back_val == 50);

    int *elem = (int *)list_at(l, 2);
    assert(elem != NULL && *elem == 30);

    list_free(&l);
}

void test_insertion_and_deletion()
{
    list l = list_create(sizeof(int));

    // Insertar al inicio
    int val1 = 1, val2 = 2, val3 = 3;
    list_appstart(&l, &val3);
    list_appstart(&l, &val2);
    list_appstart(&l, &val1);

    assert(list_length(l) == 3);

    int first;
    list_front(l, &first);
    assert(first == 1);

    // Eliminar del inicio
    assert(list_popstart(&l) == 1);
    list_front(l, &first);
    assert(first == 2);

    // Eliminar del final
    assert(list_popend(&l) == 1);
    assert(list_length(l) == 1);

    // Insertar en posición específica
    int insert_val = 99;
    assert(list_insert(&l, 0, &insert_val) == 1);
    assert(list_length(l) == 2);

    list_free(&l);
}

void test_search_functions()
{
    list l = list_create(sizeof(int));
    int values[] = {1, 2, 3, 2, 4, 2, 5};
    for (int i = 0; i < 7; i++)
    {
        list_append(&l, &values[i]);
    }

    int target = 2;

    // Buscar con función
    long pos = list_findf(&l, sizeof(int), &target, compare_int);
    assert(pos == 1);

    // Buscar con bytes
    pos = list_findb(&l, sizeof(int), &target);
    assert(pos == 1);

    // Contar con función
    size_t count = list_countf(&l, sizeof(int), &target, compare_int);
    assert(count == 3);

    // Contar con bytes
    count = list_countb(&l, sizeof(int), &target);
    assert(count == 3);

    // Eliminar primera ocurrencia
    assert(list_remove(&l, &target, compare_int) == 1);
    assert(list_length(l) == 6);

    // Eliminar todas las ocurrencias
    int removed = list_removeAll(&l, &target, compare_int);
    assert(removed == 2);
    assert(list_length(l) == 4);

    list_free(&l);
}

void test_sorting_algorithms()
{
    // Test merge sort recursivo
    list l1 = list_create(sizeof(int));
    int vals1[] = {5, 3, 8, 1, 2, 7, 4, 6};
    for (int i = 0; i < 8; i++)
    {
        list_append(&l1, &vals1[i]);
    }

    list_sort(&l1, compare_int);
    assert(list_is_sorted(&l1, compare_int) == 1);

    // Test merge sort inverso
    list l2 = list_copy(&l1);
    list_sort_reverse(&l2, compare_int);

    // Verificar orden descendente
    list_iterator_begin(&l2);
    int prev;
    int *first = (int *)list_iterator_current(&l2);
    prev = *first;
    while (list_iterator_next(&l2))
    {
        int *curr = (int *)list_iterator_current(&l2);
        assert(*curr <= prev);
        prev = *curr;
    }

    // Test sort iterativo
    list l3 = list_create(sizeof(int));
    int vals3[] = {9, 2, 5, 1, 8, 3, 7, 4, 6};
    for (int i = 0; i < 9; i++)
    {
        list_append(&l3, &vals3[i]);
    }

    list_sortIterativo(&l3, compare_int);
    assert(list_is_sorted(&l3, compare_int) == 1);

    list_free(&l1);
    list_free(&l2);
    list_free(&l3);
}

void test_merge_sorted()
{
    list l1 = list_create(sizeof(int));
    list l2 = list_create(sizeof(int));

    int vals1[] = {1, 3, 5, 7};
    int vals2[] = {2, 4, 6, 8};

    for (int i = 0; i < 4; i++)
    {
        list_append(&l1, &vals1[i]);
        list_append(&l2, &vals2[i]);
    }

    list_sort(&l1, compare_int);
    list_sort(&l2, compare_int);

    list_merge_sorted(&l1, &l2, compare_int);

    assert(list_length(l1) == 8);
    assert(list_is_sorted(&l1, compare_int) == 1);

    // Verificar que l2 está vacío
    assert(list_empty(*((list *)&l2)) == 1);

    list_free(&l1);
}

void test_copy_and_filter()
{
    list l = list_create(sizeof(int));
    int values[10];
    for (int i = 0; i < 10; i++)
    {
        values[i] = i + 1;
        list_append(&l, &values[i]);
    }

    // Test copia
    list copy = list_copy(&l);
    assert(list_length(copy) == 10);

    // Modificar copia sin afectar original
    int new_val = 999;
    list_setfirst(&copy, &new_val);

    int orig_first, copy_first;
    list_front(l, &orig_first);
    list_front(copy, &copy_first);
    assert(orig_first == 1);
    assert(copy_first == 999);

    // Test filtro
    list filtered = list_filter(&l, filter_even);
    assert(list_length(filtered) == 5);

    // Verificar que solo hay pares
    list_iterator_begin(&filtered);
    while (list_iterator_valid(&filtered))
    {
        int *val = (int *)list_iterator_current(&filtered);
        assert(*val % 2 == 0);
        list_iterator_next(&filtered);
    }

    list_free(&l);
    list_free(&copy);
    list_free(&filtered);
}

void test_sublist_and_concat()
{
    list l = list_create(sizeof(int));
    int values[10];
    for (int i = 0; i < 10; i++)
    {
        values[i] = i * 10;
        list_append(&l, &values[i]);
    }

    // Test sublista
    list sub = list_sublist(&l, 2, 7);
    assert(list_length(sub) == 5);

    // Verificar contenido de sublista
    int *first_sub = (int *)list_at(sub, 0);
    assert(*first_sub == 20);

    // Test concatenación
    list extra = list_create(sizeof(int));
    int extra_vals[] = {100, 200};
    for (int i = 0; i < 2; i++)
    {
        list_append(&extra, &extra_vals[i]);
    }

    list_concat(&l, &extra);
    assert(list_length(l) == 12);

    int last_val;
    list_back(l, &last_val);
    assert(last_val == 200);

    list_free(&l);
    list_free(&sub);
    list_free(&extra);
}

void test_reverse_and_unique()
{
    list l = list_create(sizeof(int));
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        list_append(&l, &values[i]);
    }

    // Test reverse
    assert(list_reverse(&l) == 1);

    int first;
    list_front(l, &first);
    assert(first == 5);

    // Test unique con duplicados consecutivos
    list dup = list_create(sizeof(int));
    int dup_vals[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4};
    for (int i = 0; i < 10; i++)
    {
        list_append(&dup, &dup_vals[i]);
    }

    list_sort(&dup, compare_int);
    int removed = list_unique(&dup, compare_int);
    assert(removed == 6);
    assert(list_length(dup) == 4);

    // Test deduplicate
    list dedup = list_create(sizeof(int));
    int target = 5;
    for (int i = 0; i < 10; i++)
    {
        list_append(&dedup, &target);
    }

    int dedup_removed = list_deduplicate(&dedup, &target, compare_int);
    assert(dedup_removed == 9);
    assert(list_length(dedup) == 1);

    list_free(&l);
    list_free(&dup);
    list_free(&dedup);
}

void test_iterators_comprehensive()
{
    list l = list_create(sizeof(int));
    int values[5];
    for (int i = 0; i < 5; i++)
    {
        values[i] = (i + 1) * 10;
        list_append(&l, &values[i]);
    }

    // Iteración hacia adelante
    int sum = 0;
    list_iterator_begin(&l);
    while (list_iterator_valid(&l))
    {
        int *val = (int *)list_iterator_current(&l);
        sum += *val;
        if (!list_iterator_next(&l))
            break;
    }
    assert(sum == 150); // 10+20+30+40+50

    // Iteración hacia atrás
    sum = 0;
    list_iterator_beginReverse(&l);
    while (list_iterator_valid(&l))
    {
        int *val = (int *)list_iterator_current(&l);
        sum += *val;
        if (!list_iterator_prev(&l))
            break;
    }
    assert(sum == 150);

    // Modificar con iterador
    list_iterator_begin(&l);
    int new_val = 999;
    for (int i = 0; i < 2; i++)
    {
        list_iterator_next(&l);
    }
    list_iterator_set(&l, &new_val);

    int *elem = (int *)list_at(l, 2);
    assert(*elem == 999);

    list_free(&l);
}

void test_string_operations()
{
    printf("=== Test 10: Operaciones con strings ===\n");

    // Test list_str
    list chars = list_str("Hello");
    assert(list_length(chars) == 5);

    char first_char = *(char *)list_at(chars, 0);
    assert(first_char == 'H');
    printf("✓ list_str funcionando\n");

    // Test list_split_str - CORRECTO: usa destroy_string_ptr
    list tokens = list_split_str("apple,banana,cherry", ",");
    assert(list_length(tokens) == 3);

    char **first_token = (char **)list_at(tokens, 0);
    assert(strcmp(*first_token, "apple") == 0);
    printf("✓ list_split_str funcionando\n");

    // En su lugar, crea strings duplicados
    list from_array = list_create(sizeof(char *));
    const char *str_values[] = {"first", "second", "third"};

    for (int i = 0; i < 3; i++)
    {
        char *str_copy = strdup(str_values[i]); // Duplica el string
        list_append(&from_array, &str_copy);    // Almacena el duplicado
    }

    assert(list_length(from_array) == 3);

    char **first_str = (char **)list_at(from_array, 0);
    assert(strcmp(*first_str, "first") == 0);
    printf("✓ Array de strings funcionando (con strdup)\n");

    // Limpiar CORRECTAMENTE
    list_free(&chars); // chars: caracteres simples, no allocados

    // tokens: strings allocados con strdup en list_split_str
    list_destroy(&tokens, destroy_string_ptr);

    // from_array: strings allocados con strdup arriba
    list_destroy(&from_array, destroy_string_ptr);

    printf("✓ Tests de strings completados\n\n");
}

void test_clear_and_destroy()
{
    // Test list_clear
    list l = list_create(sizeof(int));
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        list_append(&l, &values[i]);
    }

    int cleared = list_clear(&l, NULL);
    assert(cleared == 5);
    assert(list_empty(l) == 1);

    // Test list_destroy con función personalizada
    list str_list = list_create(sizeof(char *));
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    list_append(&str_list, &str1);
    list_append(&str_list, &str2);

    list_destroy(&str_list, destroy_string_ptr);

    list_free(&l);
}

void test_performance_large_dataset()
{
    printf("  Creando lista grande... ");
    fflush(stdout);

    const int SIZE = 10000;
    list big = list_create(sizeof(int));

    // Insertar muchos elementos
    for (int i = 0; i < SIZE; i++)
    {
        int val = rand() % 10000;
        list_append(&big, &val);
    }

    printf("✓ (size: %d)\n", list_length(big));

    printf("  Ordenando... ");
    fflush(stdout);
    list_sort(&big, compare_int);
    assert(list_is_sorted(&big, compare_int) == 1);
    printf("✓\n");

    printf("  Creando copia... ");
    fflush(stdout);
    list copy = list_copy(&big);
    assert(list_length(copy) == SIZE);
    printf("✓\n");

    printf("  Filtrando... ");
    fflush(stdout);
    list filtered = list_filter(&big, filter_even);
    printf("✓ (filtered: %d)\n", list_length(filtered));

    printf("  Creando sublista... ");
    fflush(stdout);
    list sub = list_sublist(&big, SIZE / 4, SIZE * 3 / 4);
    assert(list_length(sub) == SIZE / 2);
    printf("✓\n");

    list_free(&big);
    list_free(&copy);
    list_free(&filtered);
    list_free(&sub);
}

void test_error_handling()
{
    printf("  Probando manejo de errores...\n");

    // Lista NULL
    list *null_list = NULL;
    // Las funciones deberían manejar NULL sin crashear

    // Lista vacía
    list empty = list_create(sizeof(int));

    int val;
    list_front(empty, &val); // Debería imprimir error
    list_back(empty, &val);  // Debería imprimir error

    assert(list_popstart(&empty) == 0);
    assert(list_popend(&empty) == 0);
    assert(list_pop(&empty, 0) == 0);
    assert(list_setfirst(&empty, &val) == 0);
    assert(list_setlast(&empty, &val) == 0);

    // Posiciones inválidas
    list l = list_create(sizeof(int));
    int values[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        list_append(&l, &values[i]);
    }

    assert(list_pop(&l, -1) == 0);
    assert(list_pop(&l, 5) == 0);
    assert(list_set(&l, -1, &values[0]) == 0);
    assert(list_set(&l, 5, &values[0]) == 0);
    assert(list_insert(&l, -1, &values[0]) == 0);
    assert(list_insert(&l, 10, &values[0]) == 0);

    // Parámetros NULL
    list_append(NULL, &values[0]);   // Debería imprimir error
    list_appstart(NULL, &values[0]); // Debería imprimir error

    list_free(&empty);
    list_free(&l);

    printf("  ✓ Manejo de errores completado\n");
}

// ==================== MAIN ====================

int main()
{
    printf("=========================================\n");
    printf("  PRUEBA COMPLETA DE LIBRERÍA LIST.H\n");
    printf("=========================================\n");

    srand(time(NULL));

    // Ejecutar todos los tests
    run_test("Test 1: Creación y operaciones básicas", test_creation_and_basic_ops);
    run_test("Test 2: Inserción y eliminación", test_insertion_and_deletion);
    run_test("Test 3: Funciones de búsqueda", test_search_functions);
    run_test("Test 4: Algoritmos de ordenamiento", test_sorting_algorithms);
    run_test("Test 5: Merge de listas ordenadas", test_merge_sorted);
    run_test("Test 6: Copia y filtrado", test_copy_and_filter);
    run_test("Test 7: Sublista y concatenación", test_sublist_and_concat);
    run_test("Test 8: Reverse y unique", test_reverse_and_unique);
    run_test("Test 9: Iteradores", test_iterators_comprehensive);
    run_test("Test 10: Operaciones con strings", test_string_operations);
    run_test("Test 11: Clear y destroy", test_clear_and_destroy);

    printf("\n=== Test 12: Rendimiento con dataset grande ===\n");
    test_performance_large_dataset();
    printf("✅ Test de rendimiento completado\n");

    printf("\n=== Test 13: Manejo de errores ===\n");
    test_error_handling();
    printf("✅ Test de manejo de errores completado\n");

    printf("\n=========================================\n");
    printf("  ✅ TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE\n");
    printf("=========================================\n");

    return 0;
}
