// plugin.c
// Plugin implementation.

#include <string.h>

#include "plugin.h"
#include "status.h"

plugin_t *init_plugin(const char *name, void (*hook)(const char *hook_string))
{
  if (!name || !hook)
    return NULL;

  // allocating memory.
  plugin_t *plugin = malloc(sizeof(plugin_t));

  if (!plugin)
    return NULL;

  // filling the struct with parameters.
  plugin->name = strdup(name);
  plugin->hook = hook;

  if (!plugin->name)
    return NULL;

  return plugin;
}
