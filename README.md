# ObsCureFileParserCPP
This is a rewrite of ObsCureFileParser, a tool to parse the game files of
ObsCure, in C++. Using this tool requires a minimal amount of knowledge about
the game files, check the
[documentation](https://elpitifor.github.io/ObsCureDocs) if needed.

## Usage
This tool can be used through a CLI and a GUI.

### CLI
To read the contents of an IT file, run this command:
```
ObsCureFileParser --it-parse <it_file_path>
```

### GUI
Run the `ObsCureFileParserGUI.exe` program. Type the path to your IT file in the
search bar and hit the Load button. You can then modify each item with the text
boxes, the dropdowns, etc, and finally you can save the changes by pressing the
Save button.

You can also drag and drop your IT file into the `ObsCureFileParserGUI.exe` so
that the search bar is auto completed, or use a configuration file.

#### Config files
Example of a config file used in ObsCureFileParser:

```
IT_DEFAULT_PATH=C:\SteamLibrary\steamapps\common\Obscure\data\_common\allitems.it
```

It is a sequence of key-value pairs, the key and the value are separated by one
equal sign ('='), and there is one pair per line of the config file. The file
must be named "OCFP.config" and it must be in the same directory as the
executable file. Note that whitespaces (' ') are allowed in the key and in the
value.

Here's a list of the different keys there may be in the config file and their
meaning:
- `IT_DEFAULT_PATH`: the path to an IT file, the IT search bar will be
auto-completed with this value when the program is started.

## Dependencies
This project uses Raylib and Raygui for the GUI. Both projects are a creation
of [raysan5](https://github.com/raysan5), check out his work!

In order to compile ObsCureFileParser you will need these libraries. Here's the
contents that you need to have inside the `deps` folder:
```
deps/
├── raygui/
│   └── include/
│       └── raygui.h
└── raylib/
    ├── bin/
    │    └── raylib.dll
    ├── include/
    │    ├── raylib.h
    │    ├── raymath.h
    │    └── rlgl.h
    └── lib/
        ├── libraylib.a
        └── libraylibdll.a
```

You can get the needed files on the GitHub page of each project:
[Raylib](https://github.com/raysan5/raylib),
[Raygui](https://github.com/raysan5/raygui).

The ZLib license notice can be found inside the header files of Raylib and
Raygui, both projects use said license.