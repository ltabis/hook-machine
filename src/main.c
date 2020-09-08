// main.c
// Program entry point.

#include <string.h>

#include "hook_machine.h"
#include "status.h"
#include "map.h"

void my_hook(void)
{
  printf("I'm doing stuff!\n");
}

int main(void)
{
  hm_t *hm = init_hook_machine();

  if (!hm) {
    fprintf(stderr, "Couldn't create the hook machine.");
    return ERROR;
  }

  // debuging.
  debug_hook_machine(hm);

  // registering the plugin into the machine.
  if (register_plugin(hm, "my plugin")) {
    fprintf(stderr, "Couldn't register the plugin.");
    return ERROR;
  }

  // checking if the plugin has been registered.
  debug_hook_machine(hm);

  // adding a hook to the registered plugin.
  add_hook_to_plugin(hm, "my plugin", "my hook", &my_hook);

  // sending an event.
  printf("Sending 'random event'.\n");
  emit(hm, "random event");

  // sending an event.
  printf("Sending 'my hook'.\n");
  emit(hm, "my hook");

  // destroying the machine.
  destroy_hook_machine(hm);
  return 0;
}
