// hook_machine.c
// Hook machine implementation.

#include <string.h>

#include "hook_machine.h"
#include "status.h"

hm_t *init_hook_machine(void)
{
  hm_t *hm = malloc(sizeof(hm_t));

  if (!hm)
    return NULL;

  // no plugins and size of 0.
  return memset(hm, 0, sizeof(hm_t));
}

int destroy_hook_machine(hm_t *hm)
{
  if (!hm)
    return PTR_ERROR;

  if (destroy_registered_plugins(hm) > SUCCESS)
    return ERROR;
  free(hm);

  return SUCCESS;
}

int destroy_registered_plugins(hm_t *hm)
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

/* register a plugin into the hook machine. */
int register_plugin(hm_t *hm, const char *name)
{
  if (!hm)
    return PTR_ERROR;

  plugin_t *plugin = init_plugin(name);

  if (!plugin)
    return PTR_ERROR;

  plugin_t **n_ptr = malloc(sizeof(plugin_t *) * (hm->size + 1));

  if (!n_ptr)
    return MALLOC_ERROR;

  // copying all pointers.
  for (size_t i = 0; i < hm->size; ++i)
    n_ptr[i] = hm->plugins[i];

  // adding the new plugin to the list.
  n_ptr[hm->size++] = plugin;

  // reassigning the pointer.
  free(hm->plugins);
  hm->plugins = n_ptr;
  return SUCCESS;
}

int debug_hook_machine(const hm_t *hm)
{
  if (!hm)
    return PTR_ERROR;

  // displaying plugin data.
  printf("%ld plugins found.\n\n", hm->size);
  for (size_t i = 0; i < hm->size; ++i)
  {
    printf("- %s\n", hm->plugins[i]->name);
    debug_plugin(hm->plugins[i]);
  }

  return SUCCESS;
}

int emit(hm_t *hm, const char *hook_name)
{
  if (!hm || !hook_name)
    return PTR_ERROR;

  // emitting the message to all plugins.
  // ! there is a way to optimize this.
  for (size_t i = 0; i < hm->size; ++i)
  {
    void (*hook)(void) = map_get(hm->plugins[i]->hooks, hook_name);

    // executing the hook if it exists inside the current plugin.
    if (hook)
      (*hook)();
  }

  return SUCCESS;
}

plugin_t *get_plugin(hm_t *hm, const char *plugin_name)
{
  if (!hm || !plugin_name)
    return NULL;

  for (size_t i = 0; i < hm->size; ++i)
    if (!strcmp(hm->plugins[i]->name, plugin_name))
      return hm->plugins[i];

  return NULL;
}

void add_hook_to_plugin(hm_t *hm,
                        const char *plugin_name,
                        const char *hook_name,
                        void (*hook)(void))
{
  if (!hm || !plugin_name || !hook)
    return;

  plugin_t *plugin = get_plugin(hm, plugin_name);

  if (!plugin)
    return;

  add_hook(plugin, hook_name, hook);
}
