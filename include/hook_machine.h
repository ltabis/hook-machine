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

hm_t *init_hook_machine(void);
int destroy_hook_machine(hm_t *hm);
int destroy_registered_plugins(hm_t *hm);

int emit(hm_t *hm, const char *hook);
int debug_hook_machine(const hm_t *hm);
int register_plugin(hm_t *hm,
		    const char *name,
		    void (*hook)(const char *hook_string));

#endif /* ! HOOK_MACHINE_H_ */
