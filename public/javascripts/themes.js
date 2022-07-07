import {EditorView} from "@codemirror/view"

// custom theme
const easyEyes = EditorView.theme({
    "&": {
        color: "#fff",
        backgroundColor: "#101"
    },
    ".cm-content": {
        caretColor: "#fff"
    },
    "&.cm-focused .cm-cursor": {
        borderLeftColor: "#fff"
    },
    "&.cm-focused .cm-selectionBackground": {
        backgroundColor: "#303"
    },
    ".cm-selectionBackground": {
        backgroundColor: "#303"
    },
    ".cm-gutters": {
        backgroundColor: "#202",
        color: "#ddd",
        border: "none"
    },
    ".cm-activeLine": {
        backgroundColor: "#202",
    },
    ".cm-activeLineGutter": {
        backgroundColor: "#303",
    },
    ".cm-panels": {
        position: "fixed",
        bottom: "23px !important",
        borderBottom: "1px solid black !important",
        backgroundColor: "#202",
    },
    ".cm-panel": {
        padding: "0 !important", 
    },
    ".cm-search br, button[name='close'], button[name='next'], button[name='prev'], button[name='select']": {
        display: "none",
    }, 
    ".cm-search label": {
        float: "right",
    },
    "button, input, label": {
        border: "none !important",
        borderLeft: "1px solid black !important",

        outline: "none !important",

        padding: "2px 5px 3px 5px !important",
        margin: "0 !important",

        lineHeight: "16px !important",
        
        backgroundImage: "none !important",
        color: "white !important",

        fontSize: "70% !important",
    },
    "input, label": {
        backgroundColor: "#202 !important",
    },
    "button": {
        backgroundColor: "#303 !important",
        cursor: "pointer !important"
    },
    "input[type='checkbox']": {
        color: "#303 !important",
        marginRight: "5px !important"
    }
}, {dark: true});

export { easyEyes };
