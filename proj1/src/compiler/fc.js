"use strict";

/**
 * Friendly compiler
 */

const fs = require("fs");

function printUsage() {
	console.log(
		"Usage: " + process.argv[0]+" "+process.argv[1] + " [-o output] input\n",
		"        input: input file name\n",
		"        -o output: output file name\n",
		"           if no output is specified, outputs to stdout"
	);
}
// Check arguments
if (process.argv.length <= 2) { // Node has two program name arguments
	printUsage();
	process.exit(-1);
}

var fo = process.stdout;
var fi = null;

for (var i = 2; i < process.argv.length; i++) {
	if (process.argv[i] == "-o") {
		fo = fs.createWriteStream(argv[i + 1], {
			flags: "w", defaultEncoding: "utf8", fd: null, mode: 0o666,
			autoClose: true
		});
		i++;
	}
	else fi = fs.readFileSync(process.argv[i]);
}

if (fi == null) {
	console.log("Missing input file");
	process.exit(-2);
}

const compiler = require("./compile");

fo.write(compiler.arrayToString(compiler.compileAsm(fi.toString())));

