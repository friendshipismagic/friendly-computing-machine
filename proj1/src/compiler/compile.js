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
		if (!schema.test(s)) throw "Invalid register `" + s + "`";
		// Get the register number and convert to number
		return +s.replace(schema, "$1");
	}
	function parseImmediate(s) {
		let schema = /^(-?[0-9a-f]+)h$/i;
		// Check format
		if (!schema.test(s)) throw "Invalid immediate value `" + s + "`";
		// Get the immediate value and convert to number
		return parseInt(s.replace(schema, "$1"), 16);
	}
	function mergeArray(array, widths) {
		// MSBs are at the BEGINNING of array
		var shift = 16, // 16 bit instructions
		    val = 0;
		array.forEach(function(n, i) {
			let w = widths[i];
			// Taking care of negative values : converting them to CA2
			if (n < 0) n = Math.pow(2, w) + n;
			shift -= w;
			val |= n << shift;
		});
		return val;
	}
	function parseI(i, l) {
		// instruction $reg value
		return mergeArray(
			[i, parseRegister(l[1]), parseImmediate(l[2])],
			[2, 3, 11]
		);
	}
	function parseJ(i, l) {
		// instruction $reg1 $reg2 value
		return mergeArray(
			[i, parseRegister(l[1]), parseRegister(l[2]), parseImmediate(l[3])],
			[4, 3, 3, 6]
		);
	}
	function parseK(i, l) {
		// instruction value $reg1 $reg2
		return mergeArray(
			[i, parseImmediate(l[1]), parseRegister(l[2]), parseRegister(l[3])],
			[2, 8, 3, 3]
		);
	}
	function parseR(i, l) {
		// instruction $reg1 $reg2 $reg3
		return mergeArray(
			[i, parseRegister(l[1]), parseRegister(l[2]), parseRegister(l[3])],
			[7, 3, 3, 3]
		);
	}
	// Instruction list
	var instructions = {
		nop: {
			opcode: 0x00,
			parser: function() { return 0x00; }
		},
		add:   { opcode: 0x03, parser: parseR },
		addu:  { opcode: 0x07, parser: parseR },
		sub:   { opcode: 0x02, parser: parseR },
		subu:  { opcode: 0x06, parser: parseR },
		mulu:  { opcode: 0x04, parser: parseR },
		addiu: { opcode: 0x02, parser: parseI },
		lwi:   { opcode: 0x03, parser: parseI },
		lw:    { opcode: 0x02, parser: parseJ },
		sw:    { opcode: 0x03, parser: parseJ },
		bne:   { opcode: 0x01, parser: parseK }
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
			var i = instructions[l[0]];
			if (i != undefined) {
				try {
					return i.parser(i.opcode, l);
				}
				catch (e) {
					throw "Error: " + e + " at address " + lno;
				}
			}
			else throw "Error: illegal instruction `" + l[0] + "` at address " +
				lno;
		});
		console.log(labels);
		return code;
	};
})();

function arrayToString(arr) {
	/**
	 * Pads the string s to length l with f
	 * @example paddingLeft("42", 4, "0") = "0042"
	 */
	function paddingLeft(s, l, f) {
		if (s.length >= l) return s;
		else return paddingLeft(f + s, l, f);
	}
	return arr.map(n => {
		return paddingLeft(n.toString("16"), 4, "0");
	}).join("");
}

