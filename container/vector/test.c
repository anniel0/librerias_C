#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Funcion de comparacion para enteros
int compare_int(const void *a, const void *b)
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;
    if (int_a < int_b)
    {
        return -1;
    }
    if (int_a > int_b)
    {
        return 1;
    }
    return 0;
}

// Función de comparacion para cadenas
int compare_string(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

// Funcion para imprimir vector de enteros
void print_int_vector(const vector *vec, const char *name)
{
    printf("%s: [", name);
    for (size_t i = 0; i < vector_size(vec); i++)
    {
        int *val = (int *)vector_at(vec, i);
        if (val)
        {
            printf("%d", *val);
            if (i < vector_size(vec) - 1)
            {
                printf(", ");
            }
        }
    }
    printf("] (size: %zu, capacity: %zu)\n", vector_size(vec), vector_capacity(vec));
}

// Funcion para imprimir vector de cadenas
void print_string_vector(const vector *vec, const char *name)
{
    printf("%s: [", name);
    for (size_t i = 0; i < vector_size(vec); i++)
    {
        char **val = (char **)vector_at(vec, i);
        if (val && *val)
        {
            printf("\"%s\"", *val);
            if (i < vector_size(vec) - 1)
                printf(", ");
        }
    }
    printf("] (size: %zu, capacity: %zu)\n", vector_size(vec), vector_capacity(vec));
}

// Pruebas con enteros
void test_int_vector()
{
    printf("\n=== PRUEBAS CON ENTEROS ===\n");

    // Crear vector de enteros
    vector vec = vector_create(sizeof(int));

    // Agregar elementos al final
    printf("1. Agregando elementos al final...\n");
    for (int i = 1; i <= 5; i++)
    {
        vector_pushback(&vec, &i);
    }
    print_int_vector(&vec, "Despues de pushback");

    // Agregar elemento al inicio
    printf("\n2. Agregando 0 al inicio...\n");
    int zero = 0;
    vector_pushfront(&vec, &zero);
    print_int_vector(&vec, "Después de pushfront");

    // Insertar elemento en posicion especifica
    printf("\n3. Insertando 100 en posición 3...\n");
    int hundred = 100;
    vector_insert(&vec, 3, &hundred);
    print_int_vector(&vec, "Después de insert en posición 3");

    // Acceder a elementos
    printf("\n4. Accediendo a elementos...\n");
    int *front = (int *)vector_front(&vec);
    int *back = (int *)vector_back(&vec);
    int *at3 = (int *)vector_at(&vec, 3);

    if (front)
        printf("Front: %d\n", *front);
    if (back)
        printf("Back: %d\n", *back);
    if (at3)
        printf("At index 3: %d\n", *at3);

    // Buscar elemento
    printf("\n5. Buscando elementos...\n");
    int search_val = 100;
    long found = vector_findb(&vec, sizeof(int), &search_val);
    printf("Buscar 100: encontrado en indice %ld\n", found);

    search_val = 999;
    found = vector_findb(&vec, sizeof(int), &search_val);
    printf("Buscar 999: %s\n", found >= 0 ? "encontrado" : "no encontrado");

    // Ordenar vector
    printf("\n6. Ordenando vector...\n");
    vector_qsort(&vec, compare_int);
    print_int_vector(&vec, "Despues de ordenar");

    // Busqueda binaria (requiere vector ordenado)
    printf("\n7. Busqueda binaria...\n");
    search_val = 3;
    long bsearch_result = vector_bsearch(&vec, &search_val, compare_int);
    printf("Busqueda binaria de 3: indice %ld\n", bsearch_result);

    // Revertir vector
    printf("\n8. Revirtiendo vector...\n");
    vector_reverse(&vec);
    print_int_vector(&vec, "Despues de revertir");

    // Eliminar elementos
    printf("\n9. Eliminando elementos...\n");
    vector_popback(&vec);
    print_int_vector(&vec, "Despues de popback");

    vector_popfront(&vec);
    print_int_vector(&vec, "Despues de popfront");

    vector_erase(&vec, 2);
    print_int_vector(&vec, "Despues de erase en indice 2");

    // Contar elementos
    printf("\n10. Contando ocurrencias...\n");
    int count_val = 1;
    size_t count = vector_countb(&vec, sizeof(int), &count_val);
    printf("Numero de veces que aparece 1: %zu\n", count);

    // Reducir capacidad
    printf("\n11. Reduciendo capacidad...\n");
    printf("Antes de shrink_to_fit - Capacidad: %zu\n", vector_capacity(&vec));
    vector_shrink_to_fit(&vec);
    printf("Despues de shrink_to_fit - Capacidad: %zu\n", vector_capacity(&vec));

    // Limpiar vector
    printf("\n12. Limpiando vector...\n");
    vector_clear(&vec);
    printf("Despues de clear - Vacio: %s, Size: %zu\n", vector_empty(&vec) ? "si" : "no", vector_size(&vec));

    // Liberar memoria
    vector_free(&vec);
}

// Pruebas con cadenas
void test_string_vector()
{
    printf("\n\n=== PRUEBAS CON CADENAS ===\n");

    vector vec = vector_create(sizeof(char *));

    // Agregar cadenas
    printf("1. Agregando cadenas...\n");
    char *fruits[] = {"manzana", "banana", "naranja", "uva", "fresa"};

    for (int i = 0; i < 5; i++)
    {
        vector_pushback(&vec, &fruits[i]);
    }
    print_string_vector(&vec, "Vector de frutas");

    // Buscar cadena
    printf("\n2. Buscando 'banana'...\n");
    char *search = "banana";
    long found = vector_findf(&vec, &search, compare_string);
    printf("'banana' encontrada en índice: %ld\n", found);

    // Ordenar
    printf("\n3. Ordenando alfabeticamente...\n");
    vector_qsort(&vec, compare_string);
    print_string_vector(&vec, "Frutas ordenadas");

    // Insertar nueva fruta
    printf("\n4. Insertando 'cereza'...\n");
    char *cherry = "cereza";
    vector_insert(&vec, 2, &cherry);
    print_string_vector(&vec, "Despues de insertar 'cereza'");

    // Contar ocurrencias
    printf("\n5. Contando ocurrencias...\n");
    size_t count = vector_countf(&vec, &search, compare_string);
    printf("Número de 'banana': %zu\n", count);

    // Liberar memoria (importante para cadenas)
    printf("\n6. Limpiando...\n");
    vector_free(&vec);
}

// Pruebas con estructuras personalizadas
typedef struct
{
    int id;
    char name[20];
    float salary;
} Employee;

int compare_employee_by_id(const void *a, const void *b)
{
    Employee *emp_a = (Employee *)a;
    Employee *emp_b = (Employee *)b;
    if (emp_a->id < emp_b->id)
        return -1;
    if (emp_a->id > emp_b->id)
        return 1;
    return 0;
}

int compare_employee_by_salary(const void *a, const void *b)
{
    Employee *emp_a = (Employee *)a;
    Employee *emp_b = (Employee *)b;
    if (emp_a->salary < emp_b->salary)
        return -1;
    if (emp_a->salary > emp_b->salary)
        return 1;
    return 0;
}

void test_struct_vector()
{
    printf("\n\n=== PRUEBAS CON ESTRUCTURAS ===\n");

    vector vec = vector_create(sizeof(Employee));

    // Crear empleados
    Employee emp1 = {101, "Juan", 2500.50};
    Employee emp2 = {102, "Maria", 3200.75};
    Employee emp3 = {103, "Pedro", 2800.00};
    Employee emp4 = {104, "Ana", 3100.25};

    // Agregar empleados
    printf("1. Agregando empleados...\n");
    vector_pushback(&vec, &emp1);
    vector_pushback(&vec, &emp2);
    vector_pushback(&vec, &emp3);

    printf("Número de empleados: %zu\n", vector_size(&vec));

    // Insertar empleado
    printf("\n2. Insertando empleado en posición 1...\n");
    vector_insert(&vec, 1, &emp4);

    // Mostrar empleados
    printf("\n3. Lista de empleados:\n");
    for (size_t i = 0; i < vector_size(&vec); i++)
    {
        Employee *emp = (Employee *)vector_at(&vec, i);
        if (emp)
        {
            printf("  [%zu] ID: %d, Nombre: %s, Salario: %.2f\n",
                   i, emp->id, emp->name, emp->salary);
        }
    }

    // Ordenar por ID
    printf("\n4. Ordenando por ID...\n");
    vector_qsort(&vec, compare_employee_by_id);

    printf("Empleados ordenados por ID:\n");
    for (size_t i = 0; i < vector_size(&vec); i++)
    {
        Employee *emp = (Employee *)vector_at(&vec, i);
        if (emp)
        {
            printf("  ID: %d, Nombre: %s\n", emp->id, emp->name);
        }
    }

    // Ordenar por salario
    printf("\n5. Ordenando por salario...\n");
    vector_qsort(&vec, compare_employee_by_salary);

    printf("Empleados ordenados por salario:\n");
    for (size_t i = 0; i < vector_size(&vec); i++)
    {
        Employee *emp = (Employee *)vector_at(&vec, i);
        if (emp)
        {
            printf("  Nombre: %s, Salario: %.2f\n", emp->name, emp->salary);
        }
    }

    // Buscar empleado por ID
    printf("\n6. Buscando empleado con ID 102...\n");
    Employee search_emp = {102, "", 0};
    long found = vector_findb(&vec, sizeof(int), &search_emp.id);
    if (found >= 0)
    {
        Employee *emp = (Employee *)vector_at(&vec, found);
        printf("  Encontrado: %s\n", emp->name);
    }
    else
    {
        printf("  No encontrado\n");
    }

    // Eliminar empleado
    printf("\n7. Eliminando segundo empleado...\n");
    vector_erase(&vec, 1);
    printf("Número de empleados después de eliminar: %zu\n", vector_size(&vec));

    vector_free(&vec);
}

// Pruebas de rendimiento y casos límite
void test_edge_cases()
{
    printf("\n\n=== PRUEBAS DE CASOS LÍMITE ===\n");

    // Vector vacío
    printf("1. Vector vacío:\n");
    vector empty_vec = vector_create(sizeof(int));
    printf("  Vacío: %s\n", vector_empty(&empty_vec) ? "sí" : "no");
    printf("  Size: %zu\n", vector_size(&empty_vec));
    printf("  Front: %s\n", vector_front(&empty_vec) ? "no NULL" : "NULL");
    printf("  Back: %s\n", vector_back(&empty_vec) ? "no NULL" : "NULL");

    // Acceder a posición inválida
    printf("\n2. Accediendo a posición inválida:\n");
    void *invalid = vector_at(&empty_vec, 10);
    printf("  vector_at(10): %s\n", invalid ? "no NULL" : "NULL");

    // Pop en vector vacío
    printf("\n3. Pop en vector vacío (no debería crash):\n");
    vector_popback(&empty_vec);
    vector_popfront(&empty_vec);
    printf("  Operaciones completadas sin crash\n");

    // Insertar en posición mayor que size
    printf("\n4. Insertar en posición mayor que size:\n");
    int val = 42;
    vector_insert(&empty_vec, 100, &val);
    printf("  Size después de insert(100): %zu\n", vector_size(&empty_vec));

    // Agregar muchos elementos
    printf("\n5. Prueba con muchos elementos:\n");
    for (int i = 0; i < 1000; i++)
    {
        vector_pushback(&empty_vec, &i);
    }
    printf("  Después de 1000 pushbacks - Size: %zu, Capacity: %zu\n",
           vector_size(&empty_vec), vector_capacity(&empty_vec));

    // Reducir capacidad
    printf("\n6. Reduciendo capacidad drásticamente:\n");
    vector_shrink_to_fit(&empty_vec);
    printf("  Después de shrink_to_fit - Size: %zu, Capacity: %zu\n",
           vector_size(&empty_vec), vector_capacity(&empty_vec));

    // Limpiar
    vector_clear(&empty_vec);
    printf("  Después de clear - Size: %zu\n", vector_size(&empty_vec));

    // Reservar memoria
    printf("\n7. Reservando memoria:\n");
    vector_reserve(&empty_vec, 100);
    printf("  Después de reserve(100) - Capacity: %zu\n", vector_capacity(&empty_vec));

    vector_free(&empty_vec);
}

void fn(void *element)
{
    if (element)
    {
        int *value = (int *)element;
        *value = *value * 2;
    }
}

int main()
{
    printf("====== PRUEBAS DEL VECTOR GENERICO EN C ======\n");

    // Ejecutar todas las pruebas
    test_int_vector();
    test_string_vector();
    test_struct_vector();
    test_edge_cases();

    vector vec = vector_create(sizeof(int));
    for (size_t i = 0; i < 6; i++)
    {
        vector_pushback(&vec, &(int){i + 1});
    }
    print_int_vector(&vec, "int:");
    vector_foreach(&vec, fn);
    print_int_vector(&vec, "int:");

    printf("\n====== TODAS LAS PRUEBAS COMPLETADAS ======\n");

    return 0;
}