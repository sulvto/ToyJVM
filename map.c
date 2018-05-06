//
// Created by sulvto on 18-5-6.
//

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include "map.h"

#define T Map_T

struct T {
    unsigned int size;
    unsigned int length;
    int (*cmp)(const void *x, const void *y);
    unsigned (*hash)(const void *key);
    struct binding {
        struct binding *next;
        const void *key;
        void *value;
    } **buckets;
};

static int cmpatom(const void *x, const void *y) {
    return x != y;
}

static unsigned hashatom(const void *key) {
    return (unsigned long) key >> 2;
}

T Map_new(unsigned int hint,
          int cmp(const void *x, const void *y),
          unsigned hash(const void *key)) {

    assert(hint >= 0);
    static int primes[] = {509, 509, 1021, 2053, 4093,
                           8191, 16381, 32771, 65521, INT_MAX};
    int i;
    for (i = 1; primes[i] < hint; ++i) ;

    T table;
    table = (T) malloc(sizeof(*table) + primes[i - 1] * sizeof(table->buckets[0]));

    table->size = primes[i - 1];
    table->cmp = cmp ? cmp : cmpatom;
    table->hash = hash ? hash : hashatom;

    table->buckets = (struct binding **) (table + 1);
    for (int j = 0; j < table->size; ++j) {
        table->buckets[j] = NULL;
    }
    table->length = 0;

    return table;
}

void Map_free(T *map) {
    // TODO
}

unsigned int Map_length(T map) {
    assert(map);
    return map->length;
}

void *Map_put(T map, void *key, void *value) {
    assert(map);
    assert(key);
    struct binding *p;
    int i = map->hash(key) % map->size;
    for (p = map->buckets[i]; p; p = p->next) {
        if (map->cmp(key, p->key) == 0) {
            break;
        }
    }

    void *prev;
    if (p == NULL) {
        p = (struct binding *) malloc(sizeof(struct binding));
        p->key = key;
        p->next = map->buckets[i];
        map->buckets[i] = p;
        map->length++;
        prev = NULL;
    } else {
        prev = p->value;
    }
    p->value = value;
    return prev;
}

void *Map_get(T map, void *key) {
    assert(map);
    assert(key);
    struct binding *p;
    int i = map->hash(key) % map->size;
    for (p = map->buckets[i]; p; p = p->next) {
        if (map->cmp(p->key, key) == 0) {
            break;
        }
    }
    return p ? p->value : NULL;
}

void *Map_remove(T map, void *key) {
    assert(map);
    assert(key);
    struct binding **pp;
    int i = map->hash(key) % map->size;
    for (pp = &map->buckets[i]; *pp; pp = &(*pp)->next) {
        if (map->cmp(key, (*pp)->key) == 0) {
            struct binding *p = *pp;
            void *value = p->value;
            *pp = p->next;
            free(p);
            map->length--;
            return value;
        }
    }

    return NULL;
}