import json

load_json_paths: list[str] = [
    "godot/compile_commands.json",
    "ppgame/game_gdextension/compile_commands.json"
]

write_json_path: str = "compile_commands.json"


merged_json: list[any] = []
for path in load_json_paths:
    with open(path, "r", encoding="utf-8") as file:
        merged_json += json.load(file)

with open(write_json_path, "w", encoding="utf-8", newline="\n") as output_file:
    json.dump(merged_json, output_file, indent=4)
    output_file.write("\n")
