const webpack = require('webpack');

const config = {
    entry:  __dirname + '/js/index.js',
    output: {
        path: __dirname + '/dist',
        filename: 'bundle.js',
        libraryTarget: 'var',
        library: 'myLibrary'
    },
    resolve: {
        extensions: ['.js']
    },
};

module.exports = config;