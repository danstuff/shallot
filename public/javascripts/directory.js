import {basicSetup} from "codemirror"
import {EditorView} from "@codemirror/view"
import {EditorState, Compartment, Facet} from "@codemirror/state"

import {easyEyes} from "./themes.js"

function enableDirectory() {
    $("#foot_msg").html("Directory View");

    $(".cm-editor").keydown((e) => {
        if (e.keyCode == 13){ // enter/return
            let dir_string = $(".cm-activeLine").text();
            window.location.assign(window.location.href + dir_string);
        }
    });
}

if($("#file-body").length) {
    let ev = new EditorView({
        doc: $("#file-body").text(),
        extensions: [
            easyEyes,
            basicSetup,
            EditorState.readOnly.of(true)
        ],
        parent: document.querySelector("body")
    });

    ev.focus();

    enableDirectory();
}

