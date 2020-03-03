
################################################################
# This is a generated script based on design: design_3
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2019.1
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_3_script.tcl

set bCheckIPsPassed 1
##################################################################
# CHECK IPs
##################################################################
set bCheckIPs 1
if { $bCheckIPs == 1 } {
   set list_check_ips "\ 
xilinx.com:ip:axi_datamover:5.1\
xilinx.com:ip:fifo_generator:13.2\
asmpt.com:user:test_pattern:1.0\
xilinx.com:ip:xlconstant:1.1\
"

   set list_ips_missing ""
   common::send_msg_id "BD_TCL-006" "INFO" "Checking if the following IPs exist in the project's IP catalog: $list_check_ips ."

   foreach ip_vlnv $list_check_ips {
      set ip_obj [get_ipdefs -all $ip_vlnv]
      if { $ip_obj eq "" } {
         lappend list_ips_missing $ip_vlnv
      }
   }

   if { $list_ips_missing ne "" } {
      catch {common::send_msg_id "BD_TCL-115" "ERROR" "The following IPs are not found in the IP Catalog:\n  $list_ips_missing\n\nResolution: Please add the repository containing the IP(s) to the project." }
      set bCheckIPsPassed 0
   }

}

if { $bCheckIPsPassed != 1 } {
  common::send_msg_id "BD_TCL-1003" "WARNING" "Will not continue with creation of design due to the error(s) above."
  return 3
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set M_AXIS_S2MM_STS_0 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 M_AXIS_S2MM_STS_0 ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {150000000} \
   ] $M_AXIS_S2MM_STS_0

  set M_AXI_S2MM_0 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_S2MM_0 ]
  set_property -dict [ list \
   CONFIG.ADDR_WIDTH {32} \
   CONFIG.DATA_WIDTH {32} \
   CONFIG.FREQ_HZ {150000000} \
   CONFIG.HAS_BURST {0} \
   CONFIG.HAS_CACHE {0} \
   CONFIG.HAS_LOCK {0} \
   CONFIG.HAS_PROT {0} \
   CONFIG.HAS_QOS {0} \
   CONFIG.HAS_REGION {0} \
   CONFIG.HAS_RRESP {0} \
   CONFIG.NUM_READ_OUTSTANDING {2} \
   CONFIG.NUM_WRITE_OUTSTANDING {2} \
   CONFIG.PROTOCOL {AXI4} \
   CONFIG.READ_WRITE_MODE {WRITE_ONLY} \
   ] $M_AXI_S2MM_0

  set S_AXIS_S2MM_CMD_0 [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 S_AXIS_S2MM_CMD_0 ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {150000000} \
   CONFIG.HAS_TKEEP {0} \
   CONFIG.HAS_TLAST {0} \
   CONFIG.HAS_TREADY {1} \
   CONFIG.HAS_TSTRB {0} \
   CONFIG.LAYERED_METADATA {undef} \
   CONFIG.TDATA_NUM_BYTES {9} \
   CONFIG.TDEST_WIDTH {0} \
   CONFIG.TID_WIDTH {0} \
   CONFIG.TUSER_WIDTH {0} \
   ] $S_AXIS_S2MM_CMD_0


  # Create ports
  set ap_clk_0 [ create_bd_port -dir I -type clk ap_clk_0 ]
  set_property -dict [ list \
   CONFIG.FREQ_HZ {150000000} \
 ] $ap_clk_0
  set ap_rst_n_0 [ create_bd_port -dir I -type rst ap_rst_n_0 ]
  set axis_data_count_0 [ create_bd_port -dir O -from 12 -to 0 axis_data_count_0 ]
  set axis_prog_full_0 [ create_bd_port -dir O axis_prog_full_0 ]
  set grab_0 [ create_bd_port -dir I grab_0 ]
  set reg_image_col_0 [ create_bd_port -dir I -from 15 -to 0 reg_image_col_0 ]
  set reg_image_row_0 [ create_bd_port -dir I -from 15 -to 0 reg_image_row_0 ]
  set s2mm_addr_req_posted_0 [ create_bd_port -dir O s2mm_addr_req_posted_0 ]
  set s2mm_err_0 [ create_bd_port -dir O s2mm_err_0 ]

  # Create instance: axi_datamover_0, and set properties
  set axi_datamover_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_datamover:5.1 axi_datamover_0 ]
  set_property -dict [ list \
   CONFIG.c_dummy {1} \
   CONFIG.c_enable_mm2s {0} \
   CONFIG.c_enable_s2mm_adv_sig {1} \
   CONFIG.c_include_mm2s {Omit} \
   CONFIG.c_include_mm2s_stsfifo {false} \
   CONFIG.c_mm2s_include_sf {false} \
   CONFIG.c_s2mm_btt_used {11} \
   CONFIG.c_s2mm_burst_size {256} \
 ] $axi_datamover_0

  # Create instance: fifo_generator_0, and set properties
  set fifo_generator_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:fifo_generator:13.2 fifo_generator_0 ]
  set_property -dict [ list \
   CONFIG.Empty_Threshold_Assert_Value_axis {4094} \
   CONFIG.Empty_Threshold_Assert_Value_rach {14} \
   CONFIG.Empty_Threshold_Assert_Value_wach {14} \
   CONFIG.Empty_Threshold_Assert_Value_wrch {14} \
   CONFIG.Enable_Data_Counts_axis {true} \
   CONFIG.FIFO_Implementation_axis {Common_Clock_Block_RAM} \
   CONFIG.FIFO_Implementation_rach {Common_Clock_Distributed_RAM} \
   CONFIG.FIFO_Implementation_rdch {Common_Clock_Builtin_FIFO} \
   CONFIG.FIFO_Implementation_wach {Common_Clock_Distributed_RAM} \
   CONFIG.FIFO_Implementation_wdch {Common_Clock_Builtin_FIFO} \
   CONFIG.FIFO_Implementation_wrch {Common_Clock_Distributed_RAM} \
   CONFIG.Full_Threshold_Assert_Value_axis {1023} \
   CONFIG.Full_Threshold_Assert_Value_rach {15} \
   CONFIG.Full_Threshold_Assert_Value_wach {15} \
   CONFIG.Full_Threshold_Assert_Value_wrch {15} \
   CONFIG.HAS_TKEEP {true} \
   CONFIG.INTERFACE_TYPE {AXI_STREAM} \
   CONFIG.Input_Depth_axis {4096} \
   CONFIG.Programmable_Full_Type_axis {Single_Programmable_Full_Threshold_Constant} \
   CONFIG.Reset_Type {Asynchronous_Reset} \
   CONFIG.TDATA_NUM_BYTES {4} \
   CONFIG.TKEEP_WIDTH {4} \
   CONFIG.TSTRB_WIDTH {4} \
 ] $fifo_generator_0

  # Create instance: test_pattern_0, and set properties
  set test_pattern_0 [ create_bd_cell -type ip -vlnv asmpt.com:user:test_pattern:1.0 test_pattern_0 ]

  # Create instance: xlconstant_00, and set properties
  set xlconstant_00 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_00 ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {0} \
   CONFIG.CONST_WIDTH {4} \
 ] $xlconstant_00

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property -dict [ list \
   CONFIG.CONST_VAL {0} \
 ] $xlconstant_0

  # Create instance: xlconstant_1, and set properties
  set xlconstant_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_1 ]

  # Create interface connections
  connect_bd_intf_net -intf_net S_AXIS_S2MM_CMD_0_1 [get_bd_intf_ports S_AXIS_S2MM_CMD_0] [get_bd_intf_pins axi_datamover_0/S_AXIS_S2MM_CMD]
  connect_bd_intf_net -intf_net axi_datamover_0_M_AXIS_S2MM_STS [get_bd_intf_ports M_AXIS_S2MM_STS_0] [get_bd_intf_pins axi_datamover_0/M_AXIS_S2MM_STS]
  connect_bd_intf_net -intf_net axi_datamover_0_M_AXI_S2MM [get_bd_intf_ports M_AXI_S2MM_0] [get_bd_intf_pins axi_datamover_0/M_AXI_S2MM]
  connect_bd_intf_net -intf_net fifo_generator_0_M_AXIS [get_bd_intf_pins axi_datamover_0/S_AXIS_S2MM] [get_bd_intf_pins fifo_generator_0/M_AXIS]
  connect_bd_intf_net -intf_net test_pattern_0_video [get_bd_intf_pins fifo_generator_0/S_AXIS] [get_bd_intf_pins test_pattern_0/video]

  # Create port connections
  connect_bd_net -net ap_clk_0_1 [get_bd_ports ap_clk_0] [get_bd_pins axi_datamover_0/m_axi_s2mm_aclk] [get_bd_pins axi_datamover_0/m_axis_s2mm_cmdsts_awclk] [get_bd_pins fifo_generator_0/s_aclk] [get_bd_pins test_pattern_0/clk]
  connect_bd_net -net ap_rst_n_0_1 [get_bd_ports ap_rst_n_0] [get_bd_pins axi_datamover_0/m_axi_s2mm_aresetn] [get_bd_pins axi_datamover_0/m_axis_s2mm_cmdsts_aresetn] [get_bd_pins fifo_generator_0/s_aresetn] [get_bd_pins test_pattern_0/reset_l]
  connect_bd_net -net axi_datamover_0_s2mm_addr_req_posted [get_bd_ports s2mm_addr_req_posted_0] [get_bd_pins axi_datamover_0/s2mm_addr_req_posted]
  connect_bd_net -net axi_datamover_0_s2mm_err [get_bd_ports s2mm_err_0] [get_bd_pins axi_datamover_0/s2mm_err]
  connect_bd_net -net fifo_generator_0_axis_data_count [get_bd_ports axis_data_count_0] [get_bd_pins fifo_generator_0/axis_data_count]
  connect_bd_net -net fifo_generator_0_axis_prog_full [get_bd_ports axis_prog_full_0] [get_bd_pins fifo_generator_0/axis_prog_full]
  connect_bd_net -net grab_0_1 [get_bd_ports grab_0] [get_bd_pins test_pattern_0/grab]
  connect_bd_net -net reg_image_col_0_1 [get_bd_ports reg_image_col_0] [get_bd_pins test_pattern_0/reg_image_col]
  connect_bd_net -net reg_image_row_0_1 [get_bd_ports reg_image_row_0] [get_bd_pins test_pattern_0/reg_image_row]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins axi_datamover_0/s2mm_dbg_sel] [get_bd_pins xlconstant_00/dout]
  connect_bd_net -net xlconstant_1_dout [get_bd_pins axi_datamover_0/s2mm_allow_addr_req] [get_bd_pins xlconstant_1/dout]
  connect_bd_net -net xlconstant_2_dout [get_bd_pins axi_datamover_0/s2mm_halt] [get_bd_pins xlconstant_0/dout]

  # Create address segments
  create_bd_addr_seg -range 0x00010000 -offset 0x10000000 [get_bd_addr_spaces axi_datamover_0/Data_S2MM] [get_bd_addr_segs M_AXI_S2MM_0/Reg] SEG_M_AXI_S2MM_0_Reg


  # Restore current instance
  current_bd_instance $oldCurInst

}
# End of create_root_design()




proc available_tcl_procs { } {
   puts "##################################################################"
   puts "# Available Tcl procedures to recreate hierarchical blocks:"
   puts "#"
   puts "#    create_root_design"
   puts "#"
   puts "#"
   puts "# The following procedures will create hiearchical blocks with addressing "
   puts "# for IPs within those blocks and their sub-hierarchical blocks. Addressing "
   puts "# will not be handled outside those blocks:"
   puts "#"
   puts "#    create_root_design"
   puts "#"
   puts "##################################################################"
}

available_tcl_procs
