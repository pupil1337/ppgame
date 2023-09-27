cd godot
scons compiledb=yes compile_commands.json
scons platform=windows bits=64 target=editor custom_modules=../ppgame dev_build=yes debug_symbols=yes vsproj=yes
pause