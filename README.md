# minishell

Organisation:
1. master: keep it clean. Add whats works and have been tested.
2. 2 extra branches: one VJ and one LL. Easier to work on our stuff without creating too many conflicts.

TODO Tree setup:
Pour le fichier .json
{
    "files.autoSave": "afterDelay",
    "editor.renderWhitespace": "all",
    "editor.rulers": [
    80
    ],
 
    "todo-tree.highlights.customHighlight": {
    

        "TODO": {
            "icon": "checklist",
            "iconColour": "#FF8000",
            "type": "line",
            "foreground": "#FF8000"
        },
        "FIXME": {

            "icon": "bug",
            "iconColour": "#FFFF00",
            "type": "line",
            "foreground": "#FFFF00"
        },
        "FIXED": {
            "icon": "check-circle",
            "iconColour": "#33FF99",
            "type": "line",
            "foreground": "#33FF99"
        },
        "COMMENT": {
            "icon": "log",
            "iconColour": "#6666FF",
            "type": "line",
            "foreground": "#6666FF",
        },
        "QUESTION": {
            "icon": "alert",
            "iconColour": "#FF0000",
            "type": "line",
            "foreground": "#FF0000"
        },
        "LEAKS": {
            "icon": "beaker",
            "iconColour": "#00ddff",
            "type": "line",
            "foreground": "#00ddff"
        },
    },
    "todo-tree.general.showIconsInsteadOfTagsInStatusBar": true,
    "todo-tree.general.tags": [
        "FIXME",
        "TODO",
        "FIXED",
        "QUESTION",
        "COMMENT",
        "LEAKS"
    ],
    "gitlens.defaultDateLocale": null,
    "explorer.confirmDragAndDrop": false,
    "todo-tree.general.tagGroups": {
    
    },
