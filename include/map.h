// map.h
// map struct declaration

#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Warning, this map can only be used to store pointers.

typedef struct ptr_map_s {
  char *key;
  void *ptr;

  struct ptr_map_s *next;
} ptr_map_t;

ptr_map_t *map_init(void);
ptr_map_t *map_push(ptr_map_t *map, const char *key, void *ptr);
ptr_map_t *map_remove(ptr_map_t *map, const char *key);
void *map_get(ptr_map_t *map, const char *key);
size_t map_size(ptr_map_t *map);

void map_debug(ptr_map_t *map);

void map_destroy(ptr_map_t *map);

#endif /* ! MAP_H_ */
