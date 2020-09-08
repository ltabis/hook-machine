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

  // deleting the array of plugins.
  destroy_hook_machine(hm);

  // copying all pointers.
  for (size_t i = 0; i < hm->size; ++i)
    n_ptr[i] = hm->plugins[i];
  n_ptr[hm->size++] = plugin;

  // reassigning the pointer.
  hm->plugins = n_ptr;
  return SUCCESS;
}

int debug_hook_machine(const hm_t *hm)
{
  if (!hm)
    return PTR_ERROR;

  // displaying data about plugins.
  printf("%ld plugins found.\n", hm->size);
  for (size_t i = 0; i < hm->size; ++i)
    printf("- %s\n", hm->plugins[i]->name);

  return SUCCESS;
}

int emit(hm_t *hm, const char *message)
{
  if (!hm || !message)
    return PTR_ERROR;

  // emiting the message to all plugins.
  // ! there is a way to optimize this.
  for (size_t i = 0; i < hm->size; ++i)
    hm->plugins[i]->hook(message);

  return SUCCESS;
}

int destroy_hook_machine(hm_t *hm)
{
  if (!hm)
    return PTR_ERROR;

  // destroying all plugins and freeing memory of the machine.
  for (size_t i = 0; i < hm->size; ++i)
    destroy_plugin(hm->plugins[i]);

  if (hm->plugins)
    free(hm->plugins);

  return SUCCESS;
}
