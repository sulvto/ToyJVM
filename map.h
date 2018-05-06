//
// Created by sulvto on 18-5-6.
//

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#define T Map_T
typedef struct T *T;

extern T Map_new(unsigned int hint, int cmp(const void *x, const void *y), unsigned hash(const void *key));

extern void Map_free(T *map);

extern unsigned int Map_length(T map);

extern void *Map_put(T map, void *key, void *value);

extern void *Map_get(T map, void *key);

extern void *Map_remove(T map, void *key);

#undef T
#endif // MAP_INCLUDED
