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



-- # Use Xilinx ISE
-- ## Simulation: ISim

-- ### reload VHDL code without restart ISim
-- https://forums.xilinx.com/t5/Simulation-and-Verification/Isim-How-to-update-vhdl-code-without-restarting-Isim/td-p/61954
-- Re-launch at top-right corner


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


-- # convention

	component XOR2 is
	port(
		I1 : in std_logic; -- each signal per line -> easy comment and write port map
		I2 : in std_logic;
		Y : out std_logic
	);
	end component;

	begin
		U1: XOR2
		port map(
			I1 => A,
			I2 => B,
			Y => U1_OUT);
		U2: XOR2
		port map(
			I1 => U1_OUT,
			I2 => C,
			Y => open); -- leave open when you don't care the output port

-- ## Signal name

-- Suffix
	signal a_d1 : std_logic; -- for delayed 1 cycle
	signal a_l : std_logic; -- for active low


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
		f <= (others => '0'); -- filled with all zeros

-- ??? if multiple assignment -> synthesis error? warning? simulation error?

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

-- ### Concat

   a <= b(19 downto 12) & b(9 downto 2);

-- ### Shift
-- https://web.archive.org/web/20160604094455/http://homepage.ntlworld.com/jonathan.deboynepollard/FGA/bit-shifts-in-vhdl.html
-- https://stackoverflow.com/questions/43362834/real-life-use-of-sla-operator-in-vhdl
-- SRL SLL SRA SLA never works
-- sll, sla behaves differently for different types, which makes them unexpected:
-- sll, sla for old types are wrong: copies the original LSB into the new LSB, instead of filling the LSB of the result with zero
-- sll, sla for new types (unsigned and signed) are correct
-- use shift_left(), shift_right(), rotate_left(), rotate_right() instead for unsigned and signed
process is
begin
  -- Left Shift
  r_Unsigned_L <= shift_left(unsigned(r_Shift1), 1);
  r_Signed_L   <= shift_left(signed(r_Shift1), 1);
  
  -- Right Shift
  r_Unsigned_R <= shift_right(unsigned(r_Shift1), 2);
  r_Signed_R   <= shift_right(signed(r_Shift1), 2);

  wait for 100 ns;
end process;



-- # Enumerated Type
TYPE my_3values IS ('0', '1', 'Z');
TYPE PC_OPER IS (load, store, add, sub, div, mult);
TYPE state_type IS (S0, S1, S2, S3);

SIGNAL my_state : state_type



-- # Generate
entity debounce is
    generic (C_DEBUG : std_logic := '1');
end entity debounce;

architecture RTL of debounce is
begin
    DEBUG : if (C_DEBUG = '1') generate
        -- something
    end generate DEBUG;
end architecture RTL;



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

if (done = '1' and led /= all_zero) then
    simtimeprint;
    report "Test Completed Successfully" severity failure;
elsif (status = '0' and done = '1') then
    simtimeprint;
    report "Test Failed !!!" severity failure;
end if;


-- # Procedures and Functions, Overloading
-- # Packages
-- VHDL Cookbook Ch.2.5

-- # Functions, procedures and parameterized modules

-- between "process" and "begin"

signal s_axi_awaddr  : STD_LOGIC_VECTOR(31 DOWNTO 0);
signal s_axi_awvalid : STD_LOGIC;
signal s_axi_awready : STD_LOGIC;
signal s_axi_wdata   : STD_LOGIC_VECTOR(31 DOWNTO 0);
signal s_axi_wvalid  : STD_LOGIC;
signal s_axi_wready  : STD_LOGIC;
signal s_axi_bvalid  : STD_LOGIC;
signal s_axi_bready  : STD_LOGIC;
signal s_axi_araddr  : STD_LOGIC_VECTOR(31 DOWNTO 0);
signal s_axi_arvalid : STD_LOGIC;
signal s_axi_arready : STD_LOGIC;
signal s_axi_rdata   : STD_LOGIC_VECTOR(31 DOWNTO 0);
signal s_axi_rvalid  : STD_LOGIC;
signal s_axi_rready  : STD_LOGIC;


variable data: std_logic_vector(31 downto 0);

procedure AXI_WRITE (
	constant ADDR : in std_logic_vector(31 downto 0);
	constant DATA : in std_logic_vector(31 downto 0)
	) is
begin  -- AXI_WRITE
	--start of write access
--            wait until rising_edge(s_axi_aclk);
	s_axi_awaddr  <= ADDR;
	s_axi_awvalid <= '1';
	s_axi_wvalid  <= '1';
	s_axi_bready  <= '1';
	s_axi_wdata   <= DATA;
	s_axi_arvalid <= '0';
	s_axi_rready  <= '0';
	
	wait until (s_axi_awready = '1') and (s_axi_wready = '1');
	wait until rising_edge(s_axi_aclk);
	s_axi_awvalid <= not s_axi_awready;
	s_axi_wvalid  <= not s_axi_wready;
	s_axi_bready  <= not s_axi_bvalid;
		
--            while (s_axi_awready = '0') or (s_axi_wready = '0')
--            loop
--                wait until rising_edge(s_axi_aclk);
--                s_axi_awvalid <= not s_axi_awready;
--                s_axi_wvalid  <= not s_axi_wready;
--                s_axi_bready  <= not s_axi_bvalid;
--            end loop;
--            s_axi_bready <= not s_axi_bvalid;


	--access is finished
	wait until rising_edge(s_axi_aclk);
	s_axi_bready <= not s_axi_bvalid;
--          s_axi_awaddr <= (others => '0');
--          s_axi_wdata  <= (others => '0');
	s_axi_awvalid <= '0';
	s_axi_wvalid  <= '0';
   
end AXI_WRITE;


procedure AXI_READ (
	constant ADDR : in std_logic_vector(31 downto 0);
	variable DATA : out std_logic_vector(31 downto 0)
	) is
begin  -- AXI_READ
	--start of read access
	wait until rising_edge(s_axi_aclk);
	s_axi_araddr  <= ADDR;
	s_axi_arvalid <= '0';
	s_axi_rready  <= '1';
	s_axi_awvalid <= '0';
	s_axi_wvalid  <= '0';

	wait until s_axi_arready = '0';
	wait until rising_edge(s_axi_aclk);
	s_axi_arvalid <= not s_axi_arready;
	wait until s_axi_rvalid = '1';
	wait until rising_edge(s_axi_aclk);
	s_axi_rready  <= not s_axi_rvalid;
	data := s_axi_rdata;
	s_axi_arvalid <= '0';
	
--           while (s_axi_arready = '0')
--           loop
--                wait until rising_edge(s_axi_aclk);
--                s_axi_arvalid <= not s_axi_arready;
--            end loop;
--           while (s_axi_rvalid = '0')
--           loop
--                wait until rising_edge(s_axi_aclk);
--                s_axi_rready  <= not s_axi_rvalid;
--                data := s_axi_rdata;
--                s_axi_arvalid <= '0';
--                if (ADDR = ADDR_ISR) then
--                    interrupt <= s_axi_rdata(7 downto 0); 
--                end if;
--                if (ADDR = ADDR_SR) then
--                    sr <= s_axi_rdata(7 downto 0); 
--                end if;

--            end loop;

	--access is finished
	wait until rising_edge(s_axi_aclk);
	s_axi_arvalid <= '0';
	s_axi_rready  <= '0';
	wait until rising_edge(s_axi_aclk);         
end AXI_READ;


-- # New types and sub-types
-- # Array and matrix
-- # Floating-point arithmetic
-- # Testbenching with testvector file
-- http://digitaldesign.ashenden.com.au/vhdl/vhdl-tutorial.pdf
-- http://www.seas.upenn.edu/~ese171/vhdl/vhdl_primer.html
-- http://www.vhdl.org/comp.lang.vhdl/FAQ1.html



-- # flip-flop / counter / FSM
-- rising_edge are for clock input only, because it designates the signal that connects to the clock pin of a flip-flop
-- https://electronics.stackexchange.com/questions/176708/why-rising-edge-is-only-used-to-detect-clock-input
    process (CLK_I, RST_I )
    begin

		-- set and reset first
	    if ( RST_I = '1') then
		    RST_R <= '1' ;

		-- use elsif for other process
	    elsif ( rising_edge (CLK_I) ) then
		    if (CNT_RST(WIDTH-1) = '1' ) then
			    RST_R <= '0' ;
		    end if ;
	    end if ;
    end process ;



-- ## buffer
-- = out + register (as buffer)

-- with dummy signal
port (
	my_output: out std_logic;
);
...
signal my_output_i: std_logic;-- dummy signal, -i stands for "internal"
...
my_output_i <= not my_output_i; -- cannot read from "out"

my_output <= my_output_i;

-- with buffer, same as above
port (
	my_output: buffer std_logic;
);
...
my_output <= not my_output;

-- https://roger7313.blogspot.com/2011/03/outbuffer.html
-- dummy signal is better, because signal every level of hierarchy in your design that connects to my_output must be declared as a buffer. However, buffer types are not commonly used in VHDL designs because they can cause problems during synthesis. 
-- Also, data-type buffer does not have all of the required defined functions to perform common arithmetic operations.


-- ### IBUF

library UNISIM;
use UNISIM.VComponents.all;

-- ...

    -- define the buffers for the incoming data, clocks, and control
	IBUF_rst_i0:    IBUF    port map (I=>rst_pin, O=>rst_i);
	
-- ### OBUF

    -- define the buffers for the outgoing data
    OBUF_led_ix: for i in 0 to 7 generate
          OBUF_led_i: OBUF port map (I=>LED_o(i), O=>LED_pins(i));
       end generate;

-- ### IOBUF
-- [7 Series FPGAs SelectIO Resources User Guide](https://www.xilinx.com/support/documentation/user_guides/ug471_7Series_SelectIO.pdf)
-- input buffer and a 3-state output buffer
--	T: disable output buffer

scl_inst : IOBUF
port map (
  IO         => scl_io,
  I          => scl_o,
  O          => scl_i,
  T          => scl_tri);



-- ## glitches of 100ps
-- https://stackoverflow.com/questions/45143101/cascading-to-avoid-glitches-vhdl
-- What you see is not really a glitch, it is the difference of the propagation delays between bit 0 and bit 1 of your output. Nothing to worry about, unless you intend to use this output in an unusual way.



-- # inout
-- https://blog.csdn.net/ghjk014/article/details/7833776

library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity dir_data is
	port(
		clk : in STD_LOGIC;
		rst : in STD_LOGIC;
		rw : in STD_LOGIC;
		address : in STD_LOGIC_VECTOR(1 downto 0);
		data : inout STD_LOGIC_VECTOR(7 downto 0)
	);
end dir_data;

architecture arc_dir of dir_data is

	signal data_in : STD_LOGIC_VECTOR(7 downto 0);
	signal data_out: STD_LOGIC_VECTOR(7 downto 0);
	signal reg_a: STD_LOGIC_VECTOR(7 downto 0);
	signal reg_b: STD_LOGIC_VECTOR(7 downto 0);

begin

	data_in<=data;

	d1:process(clk,rst,rw)
	begin
		if rst='1' then
			reg_a <= (others=>'0');
			reg_b <= (others=>'0');
		elsif clk'event and clk='1' then
			if rw='1' then
				-- write: in
				if address="00" then
					reg_a <= data_in;
				elsif address="01" then
					reg_b <= data_in;
				end if;
			else
				-- read: out
				if address="00" then
					data_out <= reg_a;
				elsif address="01" then
					data_out <= reg_b;
				end if;
			end if;
		end if;
	end process d1;

	data <= data_out when (rw='0' and address(1)='0') else (others=>'Z'); -- 'Z' prevent multiple drivers

end arc_dir;



