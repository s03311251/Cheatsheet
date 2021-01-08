# Verilog Cheatsheet

* [VLSI Design - Verilog Introduction - Tutorialspoint](https://www.tutorialspoint.com/vlsi_design/vlsi_design_verilog_introduction.htm)

* Syntax
  * case_sensitive
  * key words are in lower case
  * comment: `\\`, `/* */`

* literals

  ``` verilog
  "time is"  // string literal
  267        // 32-bit decimal number
  2’b01      // 2-bit binary
  20’hB36F   // 20-bit hexadecimal number
  ‘062       // 32-bit octal number
  ```

  * logical level: '0', '1', 'X', 'Z'
  * number: (size) (radix) (value)
    * e.g. `3'b010`

* Wire
  * physical wire, read-only
  * `wand`, `wor`: logical AND/OR of all device drivers connected
  * `tri`: all but 1 drivers must be 'Z'
  * `supply0`, `supply1`: tied to 0/1

* vector: `Wire [9:0] A;`

  ``` verilog
  reg [7:0] x, y;
  reg [3:0] z;
  reg a;
  a = x[7] & y[7];      // bit-selects
  z = x[7:4] + y[3:0];  // part-selects
  ```

* Register
  * `reg a;`

* Parameter
  * generic in VHDL, constant in C
  * e.g. `parameter a = 3'b010, b = 2'b11;`

* time
  * for simulation only
  * `time c;`
  * `c = $time; // current sim time`

* if
  * https://www.chipverify.com/verilog/verilog-if-else-if
  ``` verilog
	if ([expression])
		Single statement

	// Use "begin" and "end" blocks for more than 1 statements		
	if ([expression]) begin          
		Multiple statements
	end
	
	// Use else to execute statements for which expression is false
	if ([expression]) begin
		Multiple statements
	end else begin
		Multiple statements
	end
	
	// if-else-if style to check for more expressions if the previous one doesn't match
	if ([expression 1]) 
		Single statement
	else if ([expression 2]) begin
		Multiple Statements
	end else
		Single statement
  ```

* switch-case
  * https://www.chipverify.com/verilog/verilog-case-statement

  ``` verilog
  case ([expression]) 
    case_item1 : 	single statement;
    case_item2,
    case_item3 : 	single statement;
    case_item4 : 	begin
                    multiple statements;
                  end
    default 	 : statement;
  endcase
  ```

* NAND: ~&, NOR: ~|, XOR: ^, XNOR: ~^ or ^~
* concat:

  ``` verilog
  wire [1:0] a, h;
  wire [2:0] x;
  wire [3:0] y, Z;
  assign x = {1'b0, a}; // x[2] = 0, x[1] = a[1], x[0] = a[0]
  assign b = {a, h}; // b[3] = a[1], b[2] = a[0], b[1] = h[1],  b[0] = h[0]
  assign {cout, b} = x + Z; // Concatenation of a result
  ```

* function

  ``` verilog
  Example  
  Assign x = y & z & chk_yz(z, y); // chk_yz is a function 

  . . ./* Definition of the function */ 
  Function chk_yz; // function definition 
  Input z,y;
  chk_yz = y^z;
  End function
  ```

* module
