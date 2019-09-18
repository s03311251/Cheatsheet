# Visual Studio code Cheatsheet

## Multiple selections (multi-cursor)

[Visual Studio](https://code.visualstudio.com/docs/editor/codebasics#_multiple-selections-multicursor)
Alt + click
Ctrl + Alt + Up/Down (move)
Ctrl + D (next occurances with selected text)
Ctrl + Shift + L (all occurances with selected text)



## Format code

Shift + Alt + F    (Windows)
Shift + Option + F (Mac)
Ctrl + Shift + I   (Ubuntu)



## User Setting

### Setting

    "workbench.settings.editor": "json"

### Theme

    "workbench.colorTheme": "Default Light+",
    "editor.fontSize": 12,

### Terminal Theme

``` json
    "terminal.integrated.fontSize": 12,
    "workbench.colorCustomizations": {
        "terminal.foreground": "#ffffff",
        "terminal.background": "#383737"
    },
```

### Minimap

    "editor.minimap.enabled": false,

### Formatter

    "editor.formatOnPaste": true,

### Git

    "git.autofetch": true,


### Preferences: Configure language specific settings...

    "[markdown]": {
        "editor.tabSize": 2
    }


## Zen mode

Enter: Ctrl + K, Z
Leave: Esc, Esc

### User Setting

    "zenMode.centerLayout": false



## Quick start
Ctrl + P



## Command palette
Ctrl + Shift + P



## Doxygen
[Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen#overview)

Type /**, Enter



## Markdown preview
[Markdown and Visual Studio Code](https://code.visualstudio.com/Docs/languages/markdown)
Ctrl + Shift + V



## Jump between braces

Ctrl + Shift + \


@startuml
Bob -[#red]> Alice : hello
Alice -[#0000FF]->Bob : ok
@enduml

## Ctrl + Tab
F1 -> Open Keyboard Shortcuts (JSON)

``` json
[
    {
        "key": "ctrl+tab",
        "command": "workbench.action.nextEditor"
    },
    {
        "key": "ctrl+shift+tab",
        "command": "workbench.action.previousEditor"
    }
]
```
