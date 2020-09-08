// map.c
// map implementation.

map_t *map_init(void)
{
  map_t *map = malloc(sizeof(map_t));

  if (!map)
    return NULL;

  return memset(map, 0, sizeof(map_t));
}

map_t *map_push(map_t *map, const char *key, void *value, size_t value_size)
{
  if (!map)
    return NULL;

  map_t *node = malloc(sizeof(map_t));
  
  if (!node || !key)
    return map;

  node->key = key;
  node->value = value;
  node->value_size = value_size;
  node->next = map;

  return node;
}

void destroy_node(map_t *map)
{
    free(map->key);
    free(map->value);
    free(map);  
}

map_t *map_remove(map_t *map, const char *key)
{
  if (!map || !key)
    return map;

  map_t *last_node = NULL;
  map_t *head = map;

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

void *map_get(map_t *map, const char *key)
{
  if (!map || !key)
    return NULL;

  for (; map->key; map = map->next)
    if (!strcmp(key, map->key))
      return map->value;

  return NULL;
}

size_t map_size(map_t *map)
{
  if (!map)
    return 0;

  size_t size = 1;

  for (; !map->key; map = map->next, ++size);
  return size;
}

void debug_map(map_t *map)
{
  if (!map) {
    fprintf(stderr, "The map is unititialized.\n");
    return;
  }

  printf("Map total size: %ld\n", map_size(map));
  printf("Items:\n");
  for (; !map->key; map = map->next)
    printf("{ key: %s, value_size: %ld }\n", map->key, map->value_size);
}

void map_destroy(map_t *map)
{
  for (map_t *tmp = NULL; map->key; map = tmp) {
    tmp = map->next
    free(map->key);
    free(map->value);
    free(map);
  }

  free(map);
}
