"use strict";

	/**
	 * Friendly compiler for the friendly computing machine
	 */

// This structure is used to avoid polluting the global namespace
var compileAsm = (function(){
	// Instruction parsers
	function parseLine(line, schema) {
		// Removing leading/trailing whitespaces and multiple whitespaces
		line = line.replace(/^\s*/, "").replace(/\s*$/, "").replace(/\s+/, " ");
		return line.split(" ");
	}
	// Instruction list
	var instructions = {
	};

	return function(src) {
		var lines = src.replace("\r\n", "\n") // Simplify line feed
			.split("\n") // get each instruction individually
		// Maps label name to address
		var labels = {};
		var address = 0;

		var labelSchema = /^\s*([a-z_-][a-z0-9_-]*)\s*:\s*$/i;
		var code = lines.map(function(line, lineno) {
			// First we test
			if (labelSchema.test(line)) {
				var label = line.replace(labelSchema, "$1");
				if (labels[label] == undefined) labels[label] = address;
				else throw "Error: redefinition of label `" + label + "` at " +
					"line " + lineno;
			}
			else {
				address++;
				return parseLine(line);
			}
		}).filter(function(i){ return i != undefined; });
	};
})();


