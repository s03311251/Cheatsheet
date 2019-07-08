-- # Use Altera Quartus II

-- 1. File -> New Project Wizard, use a proper folder and name add files wanted
-- 2. In New Project Wizard, select Cyclone II & EP2C20F484C7
-- 3. File -> New -> Block Diagram/Schematic File
-- 4. Symbol Tool -> Libraries: -> C:\(ry -> primitives -> pin -> input/output
-- 5. Save (same name as project name)
-- 6. File -> New -> VHDL File
-- 7. Save VHDL FIle
-- 8. File -> Create/Update -> Create Symbol Files for Current File
-- 9. Go back to Schematic
-- 10. Symbol Tool -> Project -> (VHDL you made)
-- 11. Orthogonal Node/Bus Tool
-- 12. Start Compilation (Purple Triangle)
-- 13. Assignments -> Pins
-- 14. Start Compilation (Purple Triangle)
-- 15. Tools -> Programmer
-- 16. Hardware Setup.. -> Currently selected hardware: USB-Blaster
-- 17. Start



-- ## Simulation
-- VHDL Cookbook Ch.1
--
-- 1. File -> New -> Vector Waveform File
-- 2. add pins (double clink in white space under Name and Value at...)
-- 3. select Node Finder -> List -> select the nodes you want -> OK
--    	if your node is not here, select Filter:
-- 4. edit you waveform
--    	for clock, right the signal -> Value -> Clock...
--    	change end time, Edit -> End Time...
-- 5. Save
-- 6. Processing -> Simulator Tool -> Simulation mode: Functional
-- 7. Simulation input: -> [your].vwf
-- 8. Generate Functional Simulation Netlist -> Start -> Report

-- # Simulation: Discrete Event Time Model
-- 1. changing input value
-- 2. run code
-- 3. schedule transactions: new output values at later simulated time
--    event: new value =/= old
--
-- Initialisation phase
-- 2-stage simulation cycle
-- 1. advance time to earilest scheduled transaction
-- 2. react to events



-- # Entity
entity_declaration ::=
    entity identifier is
        entity_header
        entity_declarative_part
    [ begin
        entity_statement_part ]
    end [ entity_simple_name ] ;

-- important, spec of generic constants (ctrl structure and behaviour) and ports
entity_header ::=
    [ formal_generic_clause ]
    [ formal_port_clause ]
generic_clause ::= generic ( generic_list ) ;
generic_list ::= generic_interface_list
port_clause ::= port ( port_list ) ;
port_list ::= port_interface_list

-- declare items to be used, usually will be included in the implementation, only mentioned here for completness
entity_declarative_part ::= { entity_declarative_item }



-- in xor3_gate.vhd

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY xor3_gate IS
	PORT(
		-- IN, OUT, INOUT, BUFFER
		A,B,C : IN STD_LOGIC;
		Result : OUT STD_LOGIC);
END xor3_gate;

ARCHITECTURE structural OF xor3_gate IS
	COMPONENT xor2 IS
	PORT(
		I1 : IN STD_LOGIC; I2 : IN STD_LOGIC;
		Y : OUT STD_LOGIC
	);
	END COMPONENT;

	SIGNAL U1_OUT : STD_LOGIC;

	BEGIN
		U1: xor2 PORT MAP (I1 => A, I2 => B, Y => U1_OUT);
		U2: xor2 PORT MAP (I1 => U1_OUT, I2 => C, Y => Result);
END structural;



-- in xor2_gate.vhd

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY xor2 IS
	PORT(
		I1 : IN STD_LOGIC; I2 : IN STD_LOGIC;
		Y : OUT STD_LOGIC);
END xor2;

ARCHITECTURE dataflow OF xor2 IS
	BEGIN
		Y <= I1 xor I2;
END dataflow;


-- ## Component: sub-module
-- ## Block: inline component


-- # Library
LIBRARY ieee;
USE ieee.std_logic_1164.all; -- interconnection
USE ieee.numeric_std.all; -- +-*/, compare, convert
USE ieee.std_logic_arith.all; -- depreciated version of numeric_std



-- # Data Types
-- VHDL Cookbook Ch.2
-- Comments
-- Identifiers

-- Numbers, Characters, Strings, Bit Strings
-- Integer, Floating, Enumeration
-- Physical: 1st and 2nd types e.g.
TYPE resistance IS RANGE 0 TO 1E8
    UNITS
        ohms;
        kohms = 1000 ohms;
        Mohms = 1E6 ohms;
    END UNITS

-- Array
--   Array aggregate:
('f', 'o', 'o', 'd') -- position association
(1 => 'f', 4 => 'd', 3 => 'o', 2 => 'o') -- named association

-- Record = struct in C
-- Subtype
SUBTYPE pin_count IS integer RANGE 0 TO 400;

-- Object: constant, variable, signal

-- Attributes: additional info
-- VHDL Cookbook Ch.2.2.9
T'left -- left bound of T
T'pos(X) -- position number of X in T
T'rightof(X) -- value in T which is one position right from X
A'range(N) -- Index range of dim'n N of A
A'length(N) -- Length of index range of dim'n N of A



bit 
-- 0,1 (Forcing); L,H (Weak); X (Forcing Unknown); W (Weak Unknown)
-- Z (High Impedance); - (Don’t Care); U (Uninitialized)
-- U > X > - > 0,1 > L,H > Z

integer -- 2^31-1 to -2^31-1

SIGNAL list_of_names: type [:= initial value];
-- wires in schematic, concurrent
SIGNAL SUM, CARRY: STD_LOGIC := '1';
SIGNAL STR: STD_LOGIC_VECTOR (7 DOWNTO 0);

VARIABLE list_of_names: type [:= initial value];
-- not exist physically
VARIABLE STS_BIT: BIT_VECTOR (0 TO 7);
VARIABLE SUM: INTEGER RANGE 0 TO 256 :=16;

CONSTANT list_of_names: type [:= initial value];
-- fixed variable
CONSTANT DATA_BUS: INTEGER:= 16;
CONSTANT RISE_TIME, FALL_TIME: TIME := 1 ns;



-- ## Declare
SIGNAL a: STD_LOGIC;
SIGNAL b: STD_LOGIC_VECTOR(3 DOWNTO 0); -- DOWNTO -> little-endian
SIGNAL c: STD_LOGIC_VECTOR(3 DOWNTO 0);
SIGNAL d: STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL e: STD_LOGIC_VECTOR(8 DOWNTO 0);



-- ## Assign
-- ### Concurrent : SIGNAL and PORT, non-blocking only last assignment matters, event triggered
		a <= '1'; -- Single-quote
		b <= "1010"; -- Double-quote
		c <= B"0001"; -- Binary base
		d <= X"AF67"; -- Hexadecimal
		e <= O"723"; -- Octal base

-- ### := : VARIABLE, blocking evaluate sequentially
		p := a XOR b;



-- ## Arithmetic
SIGNAL x, y, z : STD_LOGIC;
SIGNAL a, b, c : STD_LOGIC_VECTOR(0 TO 7);
-- Signal Assignment Statements
		x <= y AND z;
		a <= b OR c;

-- PRECEDENCE OF ORDER
-- ** ABS NOT
-- * / MOD REM
-- +(sign) -(sign)
-- + - &(concatenate) 
-- ROR ROL(rotate) SRL SLL(shift logical) SRA SLA(shift arithmetic)
-- = /= < <= > >=
-- AND OR NAND NOR XOR



-- # Enumerated Type
TYPE my_3values IS ('0', '1', 'Z');
TYPE PC_OPER IS (load, store, add, sub, div, mult);
TYPE state_type IS (S0, S1, S2, S3);

SIGNAL my_state : state_type



-- # Modelling
-- ## Structural Modelling
-- Describe components and interconnections
-- e.g. in # Entity

-- ### COMPONENT, PORT MAP

ARCHITECTURE structural OF xor3_gate IS
	COMPONENT xor2 IS
	PORT(
		I1 : IN STD_LOGIC; I2 : IN STD_LOGIC;
		Y : OUT STD_LOGIC
	);
	END COMPONENT;

	SIGNAL U1_OUT : STD_LOGIC;

	BEGIN
		U1: xor2 PORT MAP (I1 => A, I2 => B, Y => U1_OUT);
		U2: xor2 PORT MAP (I1 => U1_OUT, I2 => C, Y => Result);
END structural;



-- ## Data-flow Modelling
-- Function and flow of data

ARCHITECTURE dataflow OF xor3_gate IS
	SIGNAL U1_OUT : STD_LOGIC;

	BEGIN
		U1_OUT <= A XOR B;
		Y <= U1_OUT XOR C;
END dtatflow;



-- ### WHEN-ELSE
		target <= '1' WHEN Sth = '0' ELSE
		          '0' WHEN Sth = '1' ELSE
		          'Z';



-- ## Behavioural Modelling
-- overall behaviour

-- ### PROCESS: IF-ELSE
ARCHITECTURE behavioral OF xor3_gate IS
	BEGIN
		xor3_behave: PROCESS (A, B, C) -- A, B, C is SIGNAL used (sensitivity list)
			BEGIN
			IF ((A XOR B XOR C) = '1') THEN
				Result <= '1';
			ELSE
				Result <= '0';
			END IF;
		END PROCESS xor3_behave;
END behavioral;

-- ### PROCESS: CASE (switch)
ARCHITECTURE behav OF decoder IS
	BEGIN
		PROCESS (P) BEGIN
			CASE P IS
				WHEN "00" => Y <= "0001";
				WHEN "01" => Y <= "0010";
				WHEN "10" => Y <= "0100";
				WHEN "11" => Y <= "1000";
				WHEN OTHERS => Y <= "XXXX";
			END CASE;
		END PROCESS;
END behav;



-- # Clock & D flip-flops
-- lecture05 P.36



-- # Event

-- Synchronous sequential logic
	PROCESS (clk) BEGIN
		IF clk’event AND clk = ‘1’ THEN
			nl <= d; -- nonblocking
			q <= nl; -- nonblocking
		END IF;
	END PROCESS;



-- # Wait & Test bench
-- lecture05 P.40



-- # FSM
-- VARIABLE exist within PROCESS
-- SIGNAL declare outside PROCESS <- usually use this
-- lecture05 P.48

-- ## Synchronous Counter
-- lecture05 P.51



-- # WAIT
		WAIT ON x; -- signal event
		wait until x='1'; -- condition
		WAIT FOR 20 us; -- time
		WAIT ON x UNTIL x='1' AND y='1' FOR 1 us; -- combined



-- # LOOP
		[loop_label] LOOP
		{sequential statement}
		EXIT loop_label;
		END LOOP;



-- # WHILE
		WHILE <condition> LOOP
		{sequential statements}
		END LOOP;



-- # FOR
		FOR <identifier> IN <range>
		LOOP
		{sequential statements}
		END LOOP;



-- # NULL
-- do nothing = pass in Python
CASE cmd IS
    WHEN forward => engage_motor_forward;
    WHEN reverse => engage_motor_reverse;
    WHEN forward => NULL;
END CASE;



-- # ASSERT
-- = Exception in Python
-- 
assertion_statement ::==
    ASSERT condition
        [ report expression ]
        [ severity expression ];

-- report expression type: string
-- severity expression type: severity_level, error if omitted
-- simulator may terminate execution



-- # Procedures and Functions, Overloading
-- # Packages
-- VHDL Cookbook Ch.2.5

-- # Functions, procedures and parameterized modules
-- # New types and sub-types
-- # Array and matrix
-- # Floating-point arithmetic
-- # Testbenching with testvector file
-- http://digitaldesign.ashenden.com.au/vhdl/vhdl-tutorial.pdf
-- http://www.seas.upenn.edu/~ese171/vhdl/vhdl_primer.html
-- http://www.vhdl.org/comp.lang.vhdl/FAQ1.html













