#! /bin/bash

node_modules/.bin/rollup public/javascripts/main.js -f iife -o public/javascripts/main.bundle.js -p @rollup/plugin-node-resolve
