#! /bin/bash

node_modules/.bin/rollup public/javascripts/editor.js -f iife -o public/javascripts/editor.bundle.js -p @rollup/plugin-node-resolve

node_modules/.bin/rollup public/javascripts/directory.js -f iife -o public/javascripts/directory.bundle.js -p @rollup/plugin-node-resolve
