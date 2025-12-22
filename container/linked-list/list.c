#include "list.h"

int list_iterator_begin(list *this)
{
    if (!this)
    {
        return 0;
    }
    this->iterator = this->head;
    return this->iterator != NULL;
}

int list_iterator_beginReverse(list *this)
{
    if (!this)
    {
        return 0;
    }
    this->iterator = this->tail;
    return this->iterator != NULL;
}

int list_iterator_next(list *this)
{
    if (!this || !this->iterator)
    {
        return 0;
    }

    this->iterator = this->iterator->next;
    return this->iterator != NULL;
}

__type__ list_iterator_current(const list *this)
{
    return (this && this->iterator) ? this->iterator->elem : NULL;
}

int list_iterator_set(list *this, const __type__ new_data)
{
    if (!this || !this->iterator || !new_data)
    {
        return 0;
    }

    memcpy(this->iterator->elem, new_data, this->size_data);
    return 1;
}

int list_iterator_valid(const list *this)
{
    return (this && this->iterator);
}

int list_iterator_prev(list *this)
{
    if (!this || !this->iterator)
    {
        return 0;
    }

    this->iterator = this->iterator->prev;
    return this->iterator != NULL;
}

list list_create(size_t size_data)
{
    list new = {NULL, NULL, NULL, size_data, 0};
    return new;
}

static nodo *new_nodo(void *dato, size_t size_data)
{
    if (!dato)
    {
        printf("Error: Dato nulo\n");
        return NULL;
    }

    nodo *new = (nodo *)malloc(sizeof(nodo));
    if (!new)
    {
        printf("Error: No se pudo asignar memoria para el nodo\n");
        return NULL;
    }

    new->elem = malloc(size_data);
    if (!new->elem)
    {
        free(new);
        printf("Error: No se pudo asignar memoria para el dato\n");
        return NULL;
    }

    memcpy(new->elem, dato, size_data);
    new->next = NULL;
    new->prev = NULL;

    return new;
}

void list_append(list *this, __type__ data)
{
    if (!this || !data)
    {
        printf("Error: Lista o dato nulo\n");
        return;
    }

    nodo *new = new_nodo(data, this->size_data);
    if (!new)
        return;

    if (this->head == NULL)
    {
        // Lista vacia
        this->head = new;
        this->tail = new;
    }
    else
    {
        // Lista no vacia
        new->prev = this->tail;
        this->tail->next = new;
        this->tail = new;
    }

    this->size++;
}

void list_appstart(list *this, __type__ data)
{
    if (!this || !data)
    {
        printf("Error: Lista o dato nulo\n");
        return;
    }

    nodo *new = new_nodo(data, this->size_data);
    if (!new)
        return;

    if (this->head == NULL)
    {
        // Lista vacia
        this->head = new;
        this->tail = new;
    }
    else
    {
        // Lista no vacia
        new->next = this->head;
        this->head->prev = new;
        this->head = new;
    }

    this->size++;
}

int list_popstart(list *this)
{
    if (!this || !this->head)
    {
        printf("Error: Lista nula o vacia\n");
        return 0;
    }

    nodo *temp = this->head;

    if (this->head == this->tail)
    {
        // Solo un elemento
        this->head = NULL;
        this->tail = NULL;
    }
    else
    {
        // Multiples elementos
        this->head = this->head->next;
        this->head->prev = NULL;
    }

    free(temp->elem);
    free(temp);
    this->size--;
    return 1;
}

int list_popend(list *this)
{
    if (!this || !this->head)
    {
        printf("Error: Lista nula o vacia\n");
        return 0;
    }

    nodo *temp = this->tail;

    if (this->head == this->tail)

    {
        // Solo un elemento
        this->head = NULL;
        this->tail = NULL;
    }
    else
    {
        // Multiples elementos
        this->tail = this->tail->prev;
        this->tail->next = NULL;
    }

    free(temp->elem);
    free(temp);
    this->size--;
    return 1;
}

int list_pop(list *this, int position)
{
    if (!this || !this->head || position < 0 || position >= this->size)
    {
        printf("Error: Posicin invalida o lista vacia\n");
        return 0;
    }

    if (position == 0)
    {
        list_popstart(this);
        return 1;
    }

    if (position == this->size - 1)
    {
        list_popend(this);
        return 1;
    }

    // Buscar el nodo en la posición especificada
    nodo *actual = this->head;
    for (int i = 0; i < position; i++)
    {
        actual = actual->next;
    }

    // Reenlazar los nodos adyacentes
    actual->prev->next = actual->next;
    actual->next->prev = actual->prev;

    free(actual->elem);
    free(actual);
    this->size--;
    return 1;
}

int list_free(list *this)
{
    if (!this)
    {
        printf("Error: Lista nula\n");
        return 0;
    }

    nodo *actual = this->head;
    nodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->next;
        free(actual->elem);
        free(actual);
        actual = siguiente;
    }

    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
    return 1;
}

__type__ list_at(const list this, int position)
{
    if (position < 0 || position >= this.size || !this.head)
    {
        printf("Error: Posicion invalida o lista vacia\n");
        return NULL;
    }

    if (position < this.size / 2)
    {
        // Buscar desde el inicio
        nodo *aux = this.head;
        for (int i = 0; i < position; i++)
        {
            aux = aux->next;
        }
        return aux->elem;
    }
    else
    {
        // Buscar desde el final
        nodo *aux = this.tail;
        for (int i = this.size - 1; i > position; i--)
        {
            aux = aux->prev;
        }
        return aux->elem;
    }
}

void list_back(const list this, __type__ valor)
{
    if (!this.tail)
    {
        printf("Error: Lista vacia\n");
        return;
    }
    memcpy(valor, this.tail->elem, this.size_data);
}

void list_front(const list this, __type__ valor)
{
    if (!this.head)
    {
        printf("Error: Lista vacia\n");
        return;
    }
    memcpy(valor, this.head->elem, this.size_data);
}

int list_length(const list this)
{
    return this.size;
}

int list_empty(const list this)
{
    return this.head == NULL;
}

int list_reverse(list *this)
{
    if (!this)
    {
        printf("Error: Lista nula\n");
        return 0;
    }

    // Si la lista esta vacia o tiene un solo elemento, ya esta invertida
    if (!this->head || this->head == this->tail)
    {
        return 1;
    }

    nodo *actual = this->head;
    nodo *temp = NULL;

    // Intercambiar cabeza y cola
    this->head = this->tail;
    this->tail = actual;

    // Invertir los punteros de cada nodo
    while (actual != NULL)
    {
        temp = actual->prev;
        actual->prev = actual->next;
        actual->next = temp;
        actual = actual->prev; // Moverse al siguiente (que era el anterior)
    }

    return 1;
}

int list_setfirst(list *this, const __type__ new_data)
{
    if (!this || !this->head || !new_data)
    {
        printf("Error: Lista vacia o datos nulos\n");
        return 0;
    }

    memcpy(this->head->elem, new_data, this->size_data);
    return 1;
}

int list_setlast(list *this, const __type__ new_data)
{
    if (!this || !this->tail || !new_data)
    {
        printf("Error: Lista vacia o datos nulos\n");
        return 0;
    }

    memcpy(this->tail->elem, new_data, this->size_data);
    return 1;
}

int list_set(list *this, int position, const __type__ new_data)
{
    if (!this || !this->head || !new_data || position < 0 || position >= this->size)
    {
        printf("Error: Parametros invalidos\n");
        return 0;
    }

    if (position == 0)
    {
        return list_setfirst(this, new_data);
    }

    if (position == this->size - 1)
    {
        return list_setlast(this, new_data);
    }

    // Buscar el nodo de manera optima
    nodo *actual;
    if (position < this->size / 2)
    {
        actual = this->head;
        for (int i = 0; i < position; i++)
        {
            actual = actual->next;
        }
    }
    else
    {
        actual = this->tail;
        for (int i = this->size - 1; i > position; i--)
        {
            actual = actual->prev;
        }
    }

    memcpy(actual->elem, new_data, this->size_data);
    return 1;
}

int list_insert(list *this, int position, const __type__ data)
{
    if (!this || !data || position < 0 || position > this->size)
    {
        printf("Error: Parametros invalidos\n");
        return 0;
    }

    if (position == 0)
    {
        list_appstart(this, data);
        return 1;
    }

    if (position == this->size)
    {
        list_append(this, data);
        return 1;
    }

    // Crear nuevo nodo
    nodo *new = new_nodo(data, this->size_data);
    if (!new)
    {
        return 0;
    }

    // Buscar la posicion de insercion
    nodo *actual;
    if (position < this->size / 2)
    {
        actual = this->head;
        for (int i = 0; i < position; i++)
        {
            actual = actual->next;
        }
    }
    else
    {
        actual = this->tail;
        for (int i = this->size - 1; i > position; i--)
        {
            actual = actual->prev;
        }
    }

    // Insertar el nuevo nodo
    new->next = actual;
    new->prev = actual->prev;
    actual->prev->next = new;
    actual->prev = new;

    this->size++;
    return 1;
}

void list_forward(list *this, void (*callback)(void *))
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    nodo *actual = this->head;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->next;
    }
}

void list_backward(list *this, void (*callback)(void *))
{
    if (!callback)
    {
        printf("Error: Funcion callback nula\n");
        return;
    }

    nodo *actual = this->tail;
    while (actual != NULL)
    {
        callback(actual->elem);
        actual = actual->prev;
    }
}

long list_findf(const list *this, size_t sizevar, const __type__ valor, compare_func compare)
{
    if (!this || !this->head || !compare || !valor)
    {
        printf("Error\n");
        return -1;
    }

    nodo *aux = this->head;
    size_t i = 0;
    while (aux != NULL)
    {
        if (compare(aux->elem, valor) == 0)
        {
            return i;
        }
        i++;
        aux = aux->next;
    }
    return -1;
}

size_t list_countf(const list *this, size_t sizevar, const __type__ valor, compare_func compare)
{
    if (!this || !this->head || !compare || !valor)
    {
        printf("Error\n");
        return 0;
    }
    nodo *aux = this->head;
    size_t i = 0;
    while (aux != NULL)
    {
        if (compare(aux->elem, valor) == 0)
        {
            i++;
        }
        aux = aux->next;
    }
    return i;
}

list list_filter(const list *this, int (*filter)(void *))
{
    if (!this || !filter)
    {
        printf("Error: Parámetros inválidos\n");
        return list_create(0); // Retorna lista vacia con tamaño 0
    }

    list result = list_create(this->size_data);
    if (this->size_data == 0)
        return result;

    nodo *aux = this->head;
    while (aux != NULL)
    {
        if (filter(aux->elem))
        {
            list_append(&result, aux->elem);
        }
        aux = aux->next;
    }
    return result;
}

list list_str(const char *s)
{
    list this = list_create(sizeof(char));
    if (!s)
    {
        return this;
    }

    for (size_t i = 0; i < strlen(s); i++)
    {
        list_append(&this, (void *)&s[i]);
    }

    return this;
}

void list_print(const list *this, void (*print)(void *))
{
    if (!this || !print)
    {
        printf("Error: Parametros invalidos\n");
        return;
    }

    if (!this->head)
    {
        printf("list[%d] = (empty)\n", this->size);
        return;
    }

    printf("list[%d] = ", this->size);
    nodo *aux = this->head;
    while (aux != NULL)
    {
        print(aux->elem);
        if (aux->next != NULL)
        {
            printf(" <-> ");
        }
        aux = aux->next;
    }
    printf("\n");
}

long list_findb(const list *this, size_t sizevar, const __type__ valor)
{
    if (!this || !this->head || !valor)
    {
        printf("Error: Parámetros inválidos\n");
        return -1;
    }
    nodo *aux = this->head;
    long i = 0;
    while (aux != NULL)
    {
        if (memcmp(aux->elem, valor, sizevar) == 0)
        {
            return i;
        }
        i++;
        aux = aux->next;
    }
    return -1;
}

size_t list_countb(const list *this, size_t sizevar, const __type__ valor)
{
    if (!this || !this->head || !valor)
    {
        printf("Error: Parametros invalidos\n");
        return 0;
    }

    nodo *aux = this->head;
    size_t count = 0;
    while (aux != NULL)
    {
        if (memcmp(aux->elem, valor, sizevar) == 0)
        {
            count++;
        }
        aux = aux->next;
    }
    return count;
}

list list_arr(const __type__ arr, size_t n, size_t size)
{
    list result = list_create(size);

    if (!arr || n == 0 || size == 0)
    {
        printf("Error: Parametros invalidos\n");
        return result; // Retorna lista vacia
    }

    // Recorrer el array
    for (size_t i = 0; i < n; i++)
    {
        // Calcular la direccion de cada elemento
        char *byte_ptr = (char *)arr;
        void *element = byte_ptr + (i * size);

        list_append(&result, element);
    }

    return result;
}

void list_concat(list *this, const list *other)
{
    nodo *aux = other->head;
    while (aux != NULL)
    {
        list_append(this, aux->elem);
        aux = aux->next;
    }
}

/**
 * @brief Divide una lista en dos mitades
 * @param this Lista a dividir
 * @param left Mitad izquierda (salida)
 * @param right Mitad derecha (salida)
 */
static void list_split(list *this, list *left, list *right)
{
    if (!this || this->size < 2)
    {
        return;
    }

    // Usamos el método de puntero rápido/lento para encontrar el medio
    nodo *slow = this->head;
    nodo *fast = this->head->next;

    // Avanzar fast 2 nodos y slow 1 nodo
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' ahora está en el nodo medio
    // Configurar lista izquierda
    left->head = this->head;
    left->tail = slow;
    left->size_data = this->size_data;
    left->size = (this->size + 1) / 2; // Techo de n/2

    // Configurar lista derecha
    right->head = slow->next;
    right->tail = this->tail;
    right->size_data = this->size_data;
    right->size = this->size / 2; // Piso de n/2

    // Desconectar las dos mitades
    if (slow->next != NULL)
    {
        slow->next->prev = NULL;
    }
    slow->next = NULL;

    // Limpiar la lista original (ahora vacia)
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

/**
 * @brief Mezcla dos listas ordenadas
 * @param left Lista ordenada izquierda
 * @param right Lista ordenada derecha
 * @param compare Función de comparación
 * @return Lista mezclada ordenada
 */
static list list_merge(list *left, list *right, compare_func compare)
{
    list result = list_create(left->size_data);

    nodo *l_node = left->head;
    nodo *r_node = right->head;

    while (l_node != NULL && r_node != NULL)
    {
        if (compare(l_node->elem, r_node->elem) <= 0)
        {
            // El elemento izquierdo es menor o igual
            list_append(&result, l_node->elem);
            l_node = l_node->next;
        }
        else
        {
            // El elemento derecho es menor
            list_append(&result, r_node->elem);
            r_node = r_node->next;
        }
    }

    // Agregar los elementos restantes
    while (l_node != NULL)
    {
        list_append(&result, l_node->elem);
        l_node = l_node->next;
    }

    while (r_node != NULL)
    {
        list_append(&result, r_node->elem);
        r_node = r_node->next;
    }

    return result;
}

/**
 * @brief Mezcla dos listas ordenadas en orden inverso
 * @param left Lista ordenada izquierda
 * @param right Lista ordenada derecha
 * @param compare Función de comparación
 * @return Lista mezclada ordenada en reversa
 */
static list list_merge_reverse(list *left, list *right, compare_func compare)
{
    list result = list_create(left->size_data);

    nodo *l_node = left->head;
    nodo *r_node = right->head;

    while (l_node != NULL && r_node != NULL)
    {
        if (compare(l_node->elem, r_node->elem) >= 0)
        {
            // Para orden descendente, invertimos la comparación
            list_append(&result, l_node->elem);
            l_node = l_node->next;
        }
        else
        {
            list_append(&result, r_node->elem);
            r_node = r_node->next;
        }
    }

    // Agregar los elementos restantes
    while (l_node != NULL)
    {
        list_append(&result, l_node->elem);
        l_node = l_node->next;
    }

    while (r_node != NULL)
    {
        list_append(&result, r_node->elem);
        r_node = r_node->next;
    }

    return result;
}

void list_sort(list *this, compare_func compare)
{
    // Casos base
    if (!this || !compare)
    {
        printf("Error: Parámetros inválidos\n");
        return;
    }

    if (this->size <= 1)
    {
        // Lista ya ordenada
        return;
    }

    // Dividir la lista en dos mitades
    list left = list_create(this->size_data);
    list right = list_create(this->size_data);

    list_split(this, &left, &right);

    // Ordenar recursivamente cada mitad
    list_sort(&left, compare);
    list_sort(&right, compare);

    // Mezclar las mitades ordenadas
    list merged = list_merge(&left, &right, compare);

    list_free(&left);
    list_free(&right);

    // Copiar el resultado de vuelta a la lista original
    *this = merged;
}

void list_sort_reverse(list *this, compare_func compare)
{
    // Casos base
    if (!this || !compare)
    {
        printf("Error: Parámetros inválidos\n");
        return;
    }

    if (this->size <= 1)
    {
        // Lista ya ordenada
        return;
    }

    // Dividir la lista en dos mitades
    list left = list_create(this->size_data);
    list right = list_create(this->size_data);

    list_split(this, &left, &right);

    // Ordenar recursivamente cada mitad (en orden inverso)
    list_sort_reverse(&left, compare);
    list_sort_reverse(&right, compare);

    // Mezclar las mitades ordenadas en orden inverso
    list merged = list_merge_reverse(&left, &right, compare);

    list_free(&left);
    list_free(&right);

    // Copiar el resultado de vuelta a la lista original
    *this = merged;
}

int list_is_sorted(const list *this, compare_func compare)
{
    if (!this || !this->head || !compare || this->size <= 1)
    {
        return 1;
    }

    nodo *actual = this->head;
    while (actual->next != NULL)
    {
        if (compare(actual->elem, actual->next->elem) > 0)
        {
            return 0; // No está ordenada
        }
        actual = actual->next;
    }
    return 1;
}

void list_merge_sorted(list *this, list *other, compare_func compare)
{
    if (!this || !other || !compare)
    {
        printf("Error: Parametros invalidos\n");
        return;
    }

    // Verificar que ambas listas estén ordenadas
    if (!list_is_sorted(this, compare))
    {
        printf("Advertencia: La lista principal no esta ordenada\n");
    }
    if (!list_is_sorted(other, compare))
    {
        printf("Advertencia: La lista secundaria no esta ordenada\n");
    }

    // Si una lista esta vacia, no hay nada que hacer
    if (list_empty(*other))
    {
        return;
    }

    if (list_empty(*this))
    {
        // Si this esta vacia, simplemente copiar other
        nodo *actual = other->head;
        while (actual != NULL)
        {
            list_append(this, actual->elem);
            actual = actual->next;
        }
        list_free(other);
        return;
    }

    // Crear lista temporal para el resultado
    list result = list_create(this->size_data);

    nodo *p_node = this->head;
    nodo *o_node = other->head;

    // Mezcla similar a list_merge
    while (p_node != NULL && o_node != NULL)
    {
        if (compare(p_node->elem, o_node->elem) <= 0)
        {
            list_append(&result, p_node->elem);
            p_node = p_node->next;
        }
        else
        {
            list_append(&result, o_node->elem);
            o_node = o_node->next;
        }
    }

    // Agregar elementos restantes
    while (p_node != NULL)
    {
        list_append(&result, p_node->elem);
        p_node = p_node->next;
    }

    while (o_node != NULL)
    {
        list_append(&result, o_node->elem);
        o_node = o_node->next;
    }

    // Primero limpiar this sin liberar la estructura
    list_clear(this, NULL);
    // Luego limpiar other
    list_free(other);

    // Finalmente, asignar el resultado a this
    *this = result;
}

list list_copy(const list *this)
{
    list result = list_create(this->size_data);
    if (!this || !this->head)
    {
        return result;
    }

    nodo *aux = this->head;
    for (size_t i = 0; i < this->size; i++)
    {
        list_append(&result, aux->elem);
        aux = aux->next;
    }

    return result;
}

void list_sortIterativo(list *this, compare_func compare)
{
    if (!this || this->size <= 1 || !compare)
        return;

    int sublist_size = 1;
    int n = this->size;

    while (sublist_size < n)
    {
        nodo *prev_tail = NULL;
        nodo *current = this->head;
        this->head = NULL;
        this->tail = NULL;

        while (current)
        {
            // Sublista izquierda
            nodo *left = current;
            nodo *left_tail = left;
            int left_count = 1;

            for (int i = 1; i < sublist_size && left_tail->next; i++)
            {
                left_tail = left_tail->next;
                left_count++;
            }

            // Sublista derecha
            nodo *right = left_tail->next;
            nodo *right_tail = right;
            int right_count = 0;

            if (right)
            {
                right_count = 1;
                for (int i = 1; i < sublist_size && right_tail->next; i++)
                {
                    right_tail = right_tail->next;
                    right_count++;
                }
            }

            // Preparar siguiente iteración
            current = right_tail ? right_tail->next : NULL;

            if (right_tail)
            {
                right_tail->next = NULL;
            }
            left_tail->next = NULL;

            // Mezclar las dos sublistas
            nodo *merged_head = NULL;
            nodo *merged_tail = NULL;
            int merged_count = 0;

            while (left && right)
            {
                nodo *smaller;
                if (compare(left->elem, right->elem) <= 0)
                {
                    smaller = left;
                    left = left->next;
                }
                else
                {
                    smaller = right;
                    right = right->next;
                }

                smaller->next = NULL;

                if (!merged_head)
                {
                    merged_head = smaller;
                    merged_tail = smaller;
                }
                else
                {
                    merged_tail->next = smaller;
                    smaller->prev = merged_tail;
                    merged_tail = smaller;
                }
                merged_count++;
            }

            // Agregar elementos restantes
            nodo *remaining = left ? left : right;
            int remaining_count = left ? left_count - merged_count : right ? right_count - merged_count
                                                                           : 0;

            while (remaining)
            {
                nodo *next = remaining->next;
                remaining->next = NULL;

                if (!merged_head)
                {
                    merged_head = remaining;
                    merged_tail = remaining;
                }
                else
                {
                    merged_tail->next = remaining;
                    remaining->prev = merged_tail;
                    merged_tail = remaining;
                }
                remaining = next;
            }

            // Conectar a la lista principal
            if (!this->head)
            {
                this->head = merged_head;
            }
            else
            {
                prev_tail->next = merged_head;
                merged_head->prev = prev_tail;
            }
            prev_tail = merged_tail;
        }

        this->tail = prev_tail;
        sublist_size *= 2;
    }
}

int list_remove(list *this, const __type__ valor, compare_func compare)
{
    if (!this || !this->head || !compare || !valor)
    {
        return 0;
    }

    nodo *actual = this->head;
    nodo *previo = NULL;

    while (actual != NULL)
    {
        if (compare(actual->elem, valor) == 0)
        {
            if (previo == NULL)
            {
                // Es el primer elemento
                list_popstart(this);
            }
            else if (actual->next == NULL)
            {
                // Es el ultimo elemento
                list_popend(this);
            }
            else
            {
                // Elemento en medio
                previo->next = actual->next;
                actual->next->prev = previo;
                free(actual->elem);
                free(actual);
                this->size--;
            }
            return 1;
        }
        previo = actual;
        actual = actual->next;
    }

    return 0;
}

int list_removeAll(list *this, const __type__ valor, compare_func compare)
{
    if (!this || !this->head || !compare || !valor)
    {
        return 0;
    }

    int removed = 0;
    nodo *actual = this->head;
    nodo *previo = NULL;

    while (actual != NULL)
    {
        nodo *siguiente = actual->next;

        if (compare(actual->elem, valor) == 0)
        {
            // Eliminar este nodo en O(1)
            if (previo == NULL)
            {
                // Es el primer elemento
                this->head = siguiente;
                if (this->head)
                {
                    this->head->prev = NULL;
                }
                else
                {
                    this->tail = NULL;
                }
            }
            else if (actual->next == NULL)
            {
                // Es el último elemento
                this->tail = previo;
                previo->next = NULL;
            }
            else
            {
                // Elemento en medio
                previo->next = siguiente;
                siguiente->prev = previo;
            }

            free(actual->elem);
            free(actual);
            this->size--;
            removed++;

            // No actualizar previo porque se eliminó
        }
        else
        {
            // Solo actualizar previo si no eliminamos
            previo = actual;
        }

        actual = siguiente;
    }

    return removed;
}

void list_destroy(list *this, func destroy_func)
{
    if (!this)
    {
        return;
    }

    if (destroy_func)
    {
        nodo *actual = this->head;
        while (actual)
        {
            destroy_func(actual->elem);
            actual = actual->next;
        }
    }

    list_free(this);
}

int list_clear(list *this, func destroy_func)
{
    if (!this)
        return 0;

    int count = 0;
    nodo *actual = this->head;

    while (actual)
    {
        nodo *siguiente = actual->next;

        if (destroy_func)
        {
            destroy_func(actual->elem);
        }

        free(actual->elem);
        free(actual);
        actual = siguiente;
        count++;
    }

    this->head = NULL;
    this->tail = NULL;
    this->iterator = NULL;
    this->size = 0;

    return count;
}

list list_sublist(const list *this, int start, int end)
{
    list result = list_create(this->size_data);

    if (!this || !this->head || start < 0 ||
        (end != -1 && end <= start) || start >= this->size)
    {
        return result;
    }

    if (end == -1 || end > this->size)
        end = this->size;

    nodo *actual = this->head;
    // Avanzar hasta start (optimizado)
    if (start < this->size / 2)
    {
        for (int i = 0; i < start; i++)
            actual = actual->next;
    }
    else
    {
        actual = this->tail;
        for (int i = this->size - 1; i > start; i--)
            actual = actual->prev;
    }

    // Copiar elementos
    for (int i = start; i < end && actual; i++)
    {
        list_append(&result, actual->elem);
        actual = actual->next;
    }

    return result;
}

int list_unique(list *this, compare_func compare)
{
    if (!this || !this->head || !compare || this->size <= 1)
    {
        return 0;
    }

    int removed = 0;
    nodo *actual = this->head;

    while (actual && actual->next)
    {
        if (compare(actual->elem, actual->next->elem) == 0)
        {
            // Eliminar duplicado
            nodo *duplicado = actual->next;
            actual->next = duplicado->next;
            if (duplicado->next)
            {
                duplicado->next->prev = actual;
            }
            else
            {
                this->tail = actual;
            }

            free(duplicado->elem);
            free(duplicado);
            this->size--;
            removed++;
        }
        else
        {
            actual = actual->next;
        }
    }

    return removed;
}

int list_deduplicate(list *this, const __type__ valor, compare_func compare)
{
    if (!this || !this->head || !valor || !compare)
    {
        return 0;
    }

    int removed = 0;
    int kept = 0; // Contador de cuantos hemos mantenido
    nodo *actual = this->head;
    nodo *previo = NULL;

    while (actual)
    {
        nodo *next = actual->next;

        if (compare(actual->elem, valor) == 0)
        {
            if (kept > 0)
            {
                if (previo)
                {
                    previo->next = next;
                    if (next)
                    {
                        next->prev = previo;
                    }
                    else
                    {
                        this->tail = previo;
                    }
                }
                else
                {
                    this->head = next;
                    if (next)
                    {
                        next->prev = NULL;
                    }
                    else
                    {
                        this->tail = NULL;
                    }
                }

                free(actual->elem);
                free(actual);
                this->size--;
                removed++;
            }
            else
            {
                kept = 1;
                previo = actual;
            }
        }
        else
        {
            previo = actual;
        }

        actual = next;
    }

    return removed;
}

list list_split_str(const char *s, const char *delim)
{
    list result = list_create(sizeof(char *));

    if (!s || !delim || strlen(delim) == 0)
    {
        printf("Error: Parametros invalidos\n");
        return result;
    }

    // Hacer una copia del string para usar con strtok
    char *str_copy = strdup(s);
    if (!str_copy)
    {
        printf("Error: No se pudo asignar memoria\n");
        return result;
    }

    char *token = strtok(str_copy, delim);
    while (token != NULL)
    {
        // Crear copia del token
        char *token_copy = strdup(token);
        if (token_copy)
        {
            list_append(&result, &token_copy);
        }
        token = strtok(NULL, delim);
    }

    free(str_copy);
    return result;
}
