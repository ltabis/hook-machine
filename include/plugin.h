// plugin.h
// Plugin definitions.

#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <stdlib.h>

typedef struct plugin_s {
  char *name;
  void (*hook)(const char *hook_string);
} plugin_t;

plugin_t *init_plugin(const char *name, void (*hook)(const char *hook_string));
int destroy_plugin(plugin_t *plugin);

#endif /* ! PLUGIN_H_ */
