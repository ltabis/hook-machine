# hook-machine
A program (not yet a library) that register plugins, which can be used using hooks.

![](https://img.shields.io/github/v/release/ltabis/hook-machine?style=for-the-badge)

<!-- TODO: add a simple example -->

## How to use

start by building the machine using
```c
hm_t *hook_machine = init_hook_machine();
```

### Add a plugin

I didn't made a library from this code yet, so to test it you can set your code directly in the ``src/main.c`` file.

Register your plugin using:

```c
// will create a plugin named "my-plugin".
register_plugin(hook_machine, "my-plugin");
```

### Add a hook

To add a hook to a plugin, use the following syntax
```c
// this is the callback we will use.
void my_hook(void)
{
  printf("I'm doing stuff!\n");
}

// here, we register a hook called "my-hook" and attaching it to the
// plugin "my-plugin". when the hook is called, the machine will
// use the my_hook function.
add_hook_to_plugin(hook_machine, "my-plugin", "my-hook", &my_hook);
```

### Trigger a hook

To trigger a hook, use the following syntax:
```c
// following the last example, this hook won't call anything.
emit(hook_machine, "event");

// following the last example, this hook will call my_hook(),
// registered in the plugin "-plugin".
emit(hook_machine, "my-hook");
```

### Handle memory

To clean your memory, you need to destroy your machine when you don't
need it anymore.

You just have to use:
```c
destroy_hook_machine(hook_machine);
```

This function will free all resources.

### Debug

To debug your machine, use:
```c
debug_hook_machine(hm);
```

You will get an output showing all plugins and their content.

```
3 plugins found.

- my plugin
1 hook(s) registered.
  { key: 'my hook', ptr: '0x55eaed8227b0' }
- my plugin 2
- my plugin 3
```

## Contribute

Any PR is welcome ! If you find a problem, don't hesitate to open an issue.

### Compile & launch

```sh
$ make && ./hook-machine
```

### Makefile rules

```sh
$ make        # recompile changed files and link them.
$ make clean  # clean the repository from object file.
$ make fclean # same as above and delete the binary. 
$ make re     # cleans everything and recompile the program.
```

## Dependencies

- gcc
- makefile
