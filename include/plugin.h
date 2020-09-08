// plugin.h
// Plugin definitions.

#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <stdlib.h>

#include "map.h"

typedef struct plugin_s {
  char *name;
  ptr_map_t *hooks;
} plugin_t;

plugin_t *init_plugin(const char *name);
int destroy_plugin(plugin_t *plugin);

void debug_plugin(plugin_t *plugin);

void add_hook(plugin_t *plugin,
              const char *hook_name,
              void (*hook)(void));

#endif /* ! PLUGIN_H_ */
