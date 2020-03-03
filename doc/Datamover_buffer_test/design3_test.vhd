----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/24/2020 01:32:08 PM
-- Design Name: 
-- Module Name: design3_test - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
library UNISIM;
use UNISIM.VComponents.all;

entity design3_test is
--  Port ( );
end design3_test;

architecture Behavioural of design3_test is
    component design_3 is
        port (
            M_AXIS_S2MM_STS_0_tdata : out STD_LOGIC_VECTOR ( 7 downto 0 );
            M_AXIS_S2MM_STS_0_tkeep : out STD_LOGIC_VECTOR ( 0 to 0 );
            M_AXIS_S2MM_STS_0_tlast : out STD_LOGIC;
            M_AXIS_S2MM_STS_0_tready : in STD_LOGIC;
            M_AXIS_S2MM_STS_0_tvalid : out STD_LOGIC;
            M_AXI_S2MM_0_awaddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
            M_AXI_S2MM_0_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
            M_AXI_S2MM_0_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
            M_AXI_S2MM_0_awid : out STD_LOGIC_VECTOR ( 3 downto 0 );
            M_AXI_S2MM_0_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
            M_AXI_S2MM_0_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
            M_AXI_S2MM_0_awready : in STD_LOGIC;
            M_AXI_S2MM_0_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
            M_AXI_S2MM_0_awuser : out STD_LOGIC_VECTOR ( 3 downto 0 );
            M_AXI_S2MM_0_awvalid : out STD_LOGIC;
            M_AXI_S2MM_0_bready : out STD_LOGIC;
            M_AXI_S2MM_0_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
            M_AXI_S2MM_0_bvalid : in STD_LOGIC;
            M_AXI_S2MM_0_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
            M_AXI_S2MM_0_wlast : out STD_LOGIC;
            M_AXI_S2MM_0_wready : in STD_LOGIC;
            M_AXI_S2MM_0_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
            M_AXI_S2MM_0_wvalid : out STD_LOGIC;
            S_AXIS_S2MM_CMD_0_tdata : in STD_LOGIC_VECTOR ( 71 downto 0 );
            S_AXIS_S2MM_CMD_0_tready : out STD_LOGIC;
            S_AXIS_S2MM_CMD_0_tvalid : in STD_LOGIC;
            ap_clk_0 : in STD_LOGIC;
            ap_rst_n_0 : in STD_LOGIC;
            axis_data_count_0 : out STD_LOGIC_VECTOR ( 12 downto 0 );
            axis_prog_full_0 : out STD_LOGIC;
            grab_0 : in STD_LOGIC;
            reg_image_col_0 : in STD_LOGIC_VECTOR ( 15 downto 0 );
            reg_image_row_0 : in STD_LOGIC_VECTOR ( 15 downto 0 );
            s2mm_err_0 : out STD_LOGIC;
            s2mm_addr_req_posted_0 : out STD_LOGIC
        );
    end component design_3;
  
    signal M_AXIS_S2MM_STS_0_tdata : STD_LOGIC_VECTOR ( 7 downto 0 );
    signal M_AXIS_S2MM_STS_0_tkeep : STD_LOGIC_VECTOR ( 0 to 0 );
    signal M_AXIS_S2MM_STS_0_tlast : STD_LOGIC;
    signal M_AXIS_S2MM_STS_0_tready : STD_LOGIC := '1';
    signal M_AXIS_S2MM_STS_0_tvalid : STD_LOGIC;
    signal M_AXI_S2MM_0_awaddr : STD_LOGIC_VECTOR ( 31 downto 0 );
    signal M_AXI_S2MM_0_awburst : STD_LOGIC_VECTOR ( 1 downto 0 );
    signal M_AXI_S2MM_0_awcache : STD_LOGIC_VECTOR ( 3 downto 0 );
    signal M_AXI_S2MM_0_awid : STD_LOGIC_VECTOR ( 3 downto 0 );
    signal M_AXI_S2MM_0_awlen : STD_LOGIC_VECTOR ( 7 downto 0 );
    signal M_AXI_S2MM_0_awprot : STD_LOGIC_VECTOR ( 2 downto 0 );
    signal M_AXI_S2MM_0_awready : STD_LOGIC := '1';
    signal M_AXI_S2MM_0_awsize : STD_LOGIC_VECTOR ( 2 downto 0 );
    signal M_AXI_S2MM_0_awuser : STD_LOGIC_VECTOR ( 3 downto 0 );
    signal M_AXI_S2MM_0_awvalid : STD_LOGIC;
    signal M_AXI_S2MM_0_bready : STD_LOGIC;
    signal M_AXI_S2MM_0_bresp : STD_LOGIC_VECTOR ( 1 downto 0 ) := "00";
    signal M_AXI_S2MM_0_bvalid : STD_LOGIC := '0';
    signal M_AXI_S2MM_0_wdata : STD_LOGIC_VECTOR ( 31 downto 0 );
    signal M_AXI_S2MM_0_wlast : STD_LOGIC;
    signal M_AXI_S2MM_0_wready : STD_LOGIC := '1';
    signal M_AXI_S2MM_0_wstrb : STD_LOGIC_VECTOR ( 3 downto 0 );
    signal M_AXI_S2MM_0_wvalid : STD_LOGIC;
    signal S_AXIS_S2MM_CMD_0_tdata : STD_LOGIC_VECTOR ( 71 downto 0 ) := x"001000000000800100";
    signal S_AXIS_S2MM_CMD_0_tready : STD_LOGIC;
    signal S_AXIS_S2MM_CMD_0_tvalid : STD_LOGIC := '0';
    signal ap_clk_0 : STD_LOGIC := '0';
    signal ap_rst_n_0 : STD_LOGIC := '1';
    signal axis_data_count_0 : STD_LOGIC_VECTOR ( 12 downto 0 );
    signal axis_prog_full_0 : STD_LOGIC;
    signal grab_0 : STD_LOGIC := '0';
    signal reg_image_col_0 : STD_LOGIC_VECTOR ( 15 downto 0 );
    signal reg_image_row_0 : STD_LOGIC_VECTOR ( 15 downto 0 );
    signal s2mm_err_0 : STD_LOGIC := '0';
    signal s2mm_addr_req_posted_0 : STD_LOGIC;
    
begin
    design_3_i: component design_3
        port map (
            M_AXIS_S2MM_STS_0_tdata(7 downto 0) => M_AXIS_S2MM_STS_0_tdata(7 downto 0),
            M_AXIS_S2MM_STS_0_tkeep(0) => M_AXIS_S2MM_STS_0_tkeep(0),
            M_AXIS_S2MM_STS_0_tlast => M_AXIS_S2MM_STS_0_tlast,
            M_AXIS_S2MM_STS_0_tready => M_AXIS_S2MM_STS_0_tready,
            M_AXIS_S2MM_STS_0_tvalid => M_AXIS_S2MM_STS_0_tvalid,
            M_AXI_S2MM_0_awaddr(31 downto 0) => M_AXI_S2MM_0_awaddr(31 downto 0),
            M_AXI_S2MM_0_awburst(1 downto 0) => M_AXI_S2MM_0_awburst(1 downto 0),
            M_AXI_S2MM_0_awcache(3 downto 0) => M_AXI_S2MM_0_awcache(3 downto 0),
            M_AXI_S2MM_0_awid(3 downto 0) => M_AXI_S2MM_0_awid(3 downto 0),
            M_AXI_S2MM_0_awlen(7 downto 0) => M_AXI_S2MM_0_awlen(7 downto 0),
            M_AXI_S2MM_0_awprot(2 downto 0) => M_AXI_S2MM_0_awprot(2 downto 0),
            M_AXI_S2MM_0_awready => M_AXI_S2MM_0_awready,
            M_AXI_S2MM_0_awsize(2 downto 0) => M_AXI_S2MM_0_awsize(2 downto 0),
            M_AXI_S2MM_0_awuser(3 downto 0) => M_AXI_S2MM_0_awuser(3 downto 0),
            M_AXI_S2MM_0_awvalid => M_AXI_S2MM_0_awvalid,
            M_AXI_S2MM_0_bready => M_AXI_S2MM_0_bready,
            M_AXI_S2MM_0_bresp(1 downto 0) => M_AXI_S2MM_0_bresp(1 downto 0),
            M_AXI_S2MM_0_bvalid => M_AXI_S2MM_0_bvalid,
            M_AXI_S2MM_0_wdata(31 downto 0) => M_AXI_S2MM_0_wdata(31 downto 0),
            M_AXI_S2MM_0_wlast => M_AXI_S2MM_0_wlast,
            M_AXI_S2MM_0_wready => M_AXI_S2MM_0_wready,
            M_AXI_S2MM_0_wstrb(3 downto 0) => M_AXI_S2MM_0_wstrb(3 downto 0),
            M_AXI_S2MM_0_wvalid => M_AXI_S2MM_0_wvalid,
            S_AXIS_S2MM_CMD_0_tdata(71 downto 0) => S_AXIS_S2MM_CMD_0_tdata(71 downto 0),
            S_AXIS_S2MM_CMD_0_tready => S_AXIS_S2MM_CMD_0_tready,
            S_AXIS_S2MM_CMD_0_tvalid => S_AXIS_S2MM_CMD_0_tvalid,
            ap_clk_0 => ap_clk_0,
            ap_rst_n_0 => ap_rst_n_0,
            axis_data_count_0(12 downto 0) => axis_data_count_0(12 downto 0),
            axis_prog_full_0 => axis_prog_full_0,
            grab_0 => grab_0,
            reg_image_col_0(15 downto 0) => reg_image_col_0(15 downto 0),
            reg_image_row_0(15 downto 0) => reg_image_row_0(15 downto 0),
            s2mm_err_0 => s2mm_err_0,
            s2mm_addr_req_posted_0 => s2mm_addr_req_posted_0
        );
    
    process begin
        ap_clk_0 <= not ap_clk_0;
        wait for 0.5ns;
    end process;
    
    process begin
        ap_rst_n_0 <= '1';
        wait for 5ns;
        ap_rst_n_0 <= '0';
        wait for 5ns;
        ap_rst_n_0 <= '1';
        wait for 5ns;
        
        
        
        reg_image_col_0 <= x"0040";
        reg_image_row_0 <= x"0010";
        wait for 2ns;
        
        grab_0 <= '1';
        wait for 2ns;
        grab_0 <= '0';
        wait for 500ns;
        
--        while true loop
--            grab_0 <= '1';
--            wait for 5ns;
            
--            grab_0 <= '0';
--            wait for 25ns;
--        end loop;

--        grab_0 <= '1';
--        wait for 5ns;
        
--        grab_0 <= '0';
--        wait for 5ns;

--        -- FIFO input

--        S_AXIS_0_tdata <= x"12345678";
--        S_AXIS_0_tuser <= x"F";
--        wait for 1ns;
--        while S_AXIS_0_tdata /= x"12345A78" loop
--            S_AXIS_0_tvalid <= '1';
--            S_AXIS_0_tdata <= std_logic_vector(unsigned(S_AXIS_0_tdata)+1);
--            wait for 1ns;
--        end loop;

--        grab_0 <= '1';
--        wait for 5ns;
        
--        grab_0 <= '0';   

        
        S_AXIS_S2MM_CMD_0_tdata <= x"001000000000800100";
        wait for 1ns;
        S_AXIS_S2MM_CMD_0_tvalid <= '1';
        wait for 1ns; -- exac7ly 1 cycle
        S_AXIS_S2MM_CMD_0_tvalid <= '0';
        wait for 10ns;

        S_AXIS_S2MM_CMD_0_tdata <= x"001000000000800200";
        wait for 1ns;
        S_AXIS_S2MM_CMD_0_tvalid <= '1';
        wait for 1ns;
        S_AXIS_S2MM_CMD_0_tvalid <= '0';
        
        wait for 30ns;
        M_AXI_S2MM_0_awready <= '0';
        wait for 50ns;
        M_AXI_S2MM_0_awready <= '1';
        wait;
    end process;
    
end Behavioural;
