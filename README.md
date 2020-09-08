# hook-machine
A program that register plugins, which can be used using hooks.

## compile & launch

```sh
$ make ; ./hook-machine
```

## makefile rules

```sh
$ make        # recompile changed files and link them.
$ make clean  # clean the repository from object file.
$ make fclean # same as above and delete the binary. 
$ make re     # cleans everything and recompile the program.
```

## how to use

### add a plugin

.so / .dll loading isn't yet supported.
You can set your code directly in the ``src/main.c`` file.

Initialize your plugin using

```c
plugin_t *my_plugin = init_plugin("my plugin", &my_hook);
```

``my plugin`` is the name of your plugin.
``my_hook`` is the callback used when the hook machine emits a hook.
