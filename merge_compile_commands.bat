@echo off
setlocal enabledelayedexpansion

set "jq_path=jq.exe"
set "file1=godot/compile_commands.json"
set "file2=ppgame/game_gdextension/compile_commands.json"
set "output=compile_commands.json"

%jq_path% -s "add" %file1% %file2% > %output%
echo Merged JSON arrays from %file1% and %file2% into %output%

pause
