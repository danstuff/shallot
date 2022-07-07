import {basicSetup} from "codemirror"

import {autocompletion, CompletionContext} from "@codemirror/autocomplete"

import {EditorState, Compartment} from "@codemirror/state"

import {EditorView, keymap} from "@codemirror/view"
import {indentWithTab} from "@codemirror/commands"

import {language, syntaxTree} from "@codemirror/language"

import {cpp} from "@codemirror/lang-cpp"
import {html} from "@codemirror/lang-html"
import {java} from "@codemirror/lang-java"
import {javascript} from "@codemirror/lang-javascript"
import {json} from "@codemirror/lang-json"
import {markdown} from "@codemirror/lang-markdown"
import {python} from "@codemirror/lang-python"
import {xml} from "@codemirror/lang-xml"

import {easyEyes} from "./themes.js"

//autocomplete functionality
let completions = ["ping", "pong", "Ping"];

function myAutoComplete(context) {
    if (context.explicit) {

        // separate words by CamelCase and_underscores_too
        let phrase = context.matchBefore(/[A-Z][a-z0-9]*|[a-z0-9]+/);

        if(phrase) {
            let options = [];

            for(let i in completions) {
                if(completions[i].includes(phrase.text)) {
                    options.push({label: completions[i]});
                }
            }

            return {
                from: phrase.from,
                options: options
            };
        }
    }

    return null;
}

// language detection based on combo box
const langConf = new Compartment;
let lastFormat = "";

const autoLang = EditorState.transactionExtender.of(
    tr => {
        if(!tr.docChanged) return null;

        let format = $("#language").val();

        if (format == lastFormat) return null;

        lastFormat = format;

        function l(lang) {
            return { effects: langConf.reconfigure(lang()) };
        }

        switch(format) {
            case "cpp": return l(cpp); break;
            case "html": return l(html); break;
            case "java": return l(java); break;
            case "js": return l(javascript); break;
            case "json": return l(json); break;
            case "md": return l(markdown); break;
            case "py": return l(python); break;
            case "xml": return l(xml); break;
            default: return l(cpp); break;
        }
    }
);

// footer message fade out
function showMessage(str) {
    $("#foot_msg").html(str);
    $("#foot_msg").show();

    setTimeout(() => {
        $("#foot_msg").fadeOut();
    }, 1000);
}

// post to save
function postDoc(view) {
    showMessage("Saved");
    $.post(window.location.href, 
        { data: view.state.doc.toString() }
    );
}

// enter to submit a password
$("#password").keypress(function(e) {
    let code = e.which || e.keyCode;
    if(code == 13) { // enter
        $.post(window.location.href,
            { password : $("#password").val() },
            (d) => {
                $("#password").val("");
                showMessage(d.foot_msg);
            }
        );
    }
});

document.onkeydown = (e) => {
    let code = e.which || e.keyCode;

    // disable CTRL-S default behavior
    if(e.ctrlKey && code == 83) { // s
        e.preventDefault();
        e.stopPropagation();
    }


    // reroute a tab key press in find (ctrl-f) to replace and vice versa
    if(e.ctrlKey && code == 70) { // f
        function tabLink(a, b) {
            $(a).keydown((e) => {
                let code = e.which || e.keyCode;
                if(code == 9) { // tab
                    $(b).focus();
                    
                    e.preventDefault();
                    e.stopPropagation();
                }
            });
        }

        tabLink(".cm-textfield[name=search]", ".cm-textfield[name=replace]");
        tabLink(".cm-textfield[name=replace]", ".cm-textfield[name=search]");
    }
}

// create the editor if you're on an edit page
if($("#file-body").length) {
    new EditorView({
        doc: $("#file-body").text(),
        extensions: [
            easyEyes,
            basicSetup,
            keymap.of([indentWithTab]),
            keymap.of([{key: "Ctrl-s", run: postDoc}]),
            langConf.of(cpp()),
            autoLang,
            autocompletion({ override: [myAutoComplete] })
        ],
        parent: document.querySelector("body")
    });
}

