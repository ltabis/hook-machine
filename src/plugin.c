// plugin.c
// Plugin implementation.

#include <string.h>

#include "plugin.h"
#include "status.h"

plugin_t *init_plugin(const char *name)
{
  if (!name)
    return NULL;

  // allocating memory.
  plugin_t *plugin = malloc(sizeof(plugin_t));

  if (!plugin)
    return NULL;

  // filling the struct with parameters.
  plugin->name = strdup(name);
  plugin->hooks = map_init();

  if (!plugin->name || !plugin->hooks)
    return NULL;

  return plugin;
}

int destroy_plugin(plugin_t *plugin)
{
  if (!plugin)
    return PTR_ERROR;

  // freeing plugin memory.
  map_destroy(plugin->hooks);
  free(plugin->name);
  free(plugin);

  return SUCCESS;
}

void debug_plugin(plugin_t *plugin)
{
  if (!plugin || !map_size(plugin->hooks))
    return;
  map_debug(plugin->hooks);
}

void add_hook(plugin_t *plugin,
              const char *hook_name,
              void (*hook)(void))
{
  // add a hook to the list of hooks.
  plugin->hooks = map_push(plugin->hooks, hook_name, hook);
}
