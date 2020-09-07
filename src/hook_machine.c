// hook_machine.c
// Hook machine implementation.

#include "hook_machine.h"
#include "status.h"

/* register a plugin into the hook machine. */
int register_plugin(hm_t *hm, plugin_t *plugin)
{
  if (!hm || !plugin)
    return PTR_ERROR;

  plugin_t **n_ptr = malloc(sizeof(plugin_t *) * (hm->size + 1));

  if (!n_ptr)
    return MALLOC_ERROR;

  // copying all pointers.
  for (size_t i = 0; i < hm->size; ++i)
    n_ptr[i] = hm->plugins[i];
  n_ptr[hm->size] = plugin;

  // deleting the array of plugins.
  free(hm->plugins);

  // reassigning the pointer.
  hm->plugins = n_ptr;
  return SUCCESS;
}

int debug_hook_machine(const hm_t *hm)
{
  if (!hm)
    return PTR_ERROR;

  // displaying data about plugins.
  printf("%ld plugins found.", hm->size);
  for (size_t i = 0; i < hm->size; ++i)
    printf("- %s\n", hm->plugins[i]->name);

  return SUCCESS;
}
