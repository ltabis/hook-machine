// map.c
// map implementation.

#include "map.h"

ptr_map_t *map_init(void)
{
  ptr_map_t *map = malloc(sizeof(ptr_map_t));

  if (!map)
    return NULL;

  return memset(map, 0, sizeof(ptr_map_t));
}

ptr_map_t *map_push(ptr_map_t *map, const char *key, void *ptr)
{
  if (!map || map_get(map, key))
    return map;

  ptr_map_t *node = malloc(sizeof(ptr_map_t));
  
  if (!node || !key)
    return map;

  node->key = strdup(key);
  node->ptr = ptr;
  node->next = map;

  return node;
}

void destroy_node(ptr_map_t *map)
{
    free(map->key);
    free(map);  
}

ptr_map_t *map_remove(ptr_map_t *map, const char *key)
{
  if (!map || !key)
    return map;

  ptr_map_t *last_node = NULL;
  ptr_map_t *head = map;

  for (; map->key; last_node = map, map = map->next)
    if (!strcmp(key, map->key))
      break;

  if (!map->key)
    return map;

  if (last_node != map)
    last_node->next = map->next;
  else
    head = map->next;

  destroy_node(map);
  return head;
}

void *map_get(ptr_map_t *map, const char *key)
{
  if (!map || !key)
    return NULL;

  for (; map->key; map = map->next)
    if (!strcmp(key, map->key))
      return map->ptr;

  return NULL;
}

size_t map_size(ptr_map_t *map)
{
  if (!map)
    return 0;

  size_t size = 0;

  for (; map->key; map = map->next, ++size);
  return size;
}

void map_debug(ptr_map_t *map)
{
  if (!map) {
    fprintf(stderr, "The map is unititialized.\n");
    return;
  }

  if (!map_size(map)) {
    printf("No hook registered.\n");
    return;
  }

  printf("%ld hook(s) registered.\n", map_size(map));
  for (; map->key; map = map->next)
    printf("  { key: '%s', ptr: '%p' }\n", map->key, map->ptr);
}

void map_destroy(ptr_map_t *map)
{
  if (map_size(map) == 1) {
    destroy_node(map->next);
    destroy_node(map);
    return;
  }

  for (ptr_map_t *tmp = NULL; map->key; map = tmp) {
    tmp = map->next;
    free(map->key);
    free(map->ptr);
    free(map);
  }

  free(map);
}
