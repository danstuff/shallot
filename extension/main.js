const word_regex = /[A-Z]+[a-z0-9]*|[a-z0-9]+|[^A-Za-z0-9\s]/g;

function makeWordLinks(prev, current, next) {
    return [
        { word: prev, strength: 1 },
        { word: next, strength: 1 }
    ];
}

// construct a directed graph of all the words in the document
function recursiveScrape(element, words) {
    console.log(words);

    let text_str = element.clone()
        .children()
        .remove()
        .end()
        .text();

    // split text into words and generate a weighted graph
    word_iter = text_str.matchAll(word_regex);

    let iter_state = word_iter.next();
    let last_word = "";

    while(!iter_state.done) {
        let this_word = iter_state.value[0];

        if(last_word != "") {
            if(words[last_word][this_word]) {
                words[last_word][this_word]++;
            } else {
                words[last_word][this_word] = 1;
            }
        }

        iter_state = word_iter.next();
        last_word = this_word;
    }

    element.children().forEach((child) => {
        console.log(child);
        words = recursiveScrape(child, words);
    });

    return words;
}

let words = recursiveScrape($("body"), {});


$.post("localhost:3000/dictionary/", { dictionary: words });
