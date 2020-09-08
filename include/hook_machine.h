// hook_machine.h
// Hook machine definitions.

#ifndef HOOK_MACHINE_H_
#define HOOK_MACHINE_H_

#include <stdlib.h>
#include <stdio.h>

#include "plugin.h"

typedef struct hook_machine_s {
  /* ! Could be replaced with a chained list ! */
  plugin_t **plugins;
  size_t size;
} hm_t;

int register_plugin(hm_t *hm, plugin_t *plugin);
int debug_hook_machine(const hm_t *hm);

int emit(hm_t *hm, const char *message);
int destroy_hook_machine(hm_t *hm);

#endif /* ! HOOK_MACHINE_H_ */
