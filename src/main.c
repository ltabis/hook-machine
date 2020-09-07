// main.c
// Program entry point.

#include <string.h>

#include "hook_machine.h"

void my_hook(const char *hook_string)
{
  if (strcmp(hook_string, "my hook!"))
    printf("My hook event received!");
}

int main(void)
{
  hm_t hm = {NULL, 0};
  plugin_t *plugin = init_plugin("my plugin", &my_hook);

  free(plugin);
  return 0;
}
