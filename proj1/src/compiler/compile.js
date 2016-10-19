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
	function parseRegister(s) {
		let schema = /^\$r([0-7])$/i;
		// Check the format
		if (!schema.test(s)) return null;
		// Get the register number and convert to number
		return +s.replace(schema, "$1");
	}
	function parseImmediate(s) {
		let schema = /^(-?[0-9a-f]+)h$/i;
		// Check format
		if (!schema.test(s)) return null;
		// Get the immediate value and convert to number
		return parseInt(s.replace(schema, "$1"), 16);
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
				// Even with a valid label, we don't return anything so that
				// we get an array with only instructions
			}
			else {
				address++;
				return parseLine(line).map(function(s) {
					return s.toLowerCase();
				});
			}
		}).filter(function(i){ return i != undefined; }).map(function(l, lno) {
			// Check the instruction actually exists
			var i = instruction[l[0]];
			if (i != undefined) {
				l = i.parser(l);
				l[0] = i.opcode;
				return l;
			}
			else throw "Error: illegal instruction `" + l[0] + "` at address " +
				lno;
		});
		console.log(labels);
		return code;
	};
})();

console.log(compileAsm("main:\n    lwi 2, $r1\n    lwi 20, $r2\n    loop:\n    multi $r1, $r1, 2\n    subi  $r2, $r2, 1\n    bne   $r2, $r0, -2"))

