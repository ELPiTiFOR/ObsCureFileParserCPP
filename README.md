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
that the search bar is auto completed.