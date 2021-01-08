# mentor graphics PADS

## PADS Logic

[Reference](http://www.people.vcu.edu/~rhklenke/tutorials/PADS/PADS_Tutorial_User_Interface/UserInterface.html)

* `Edit` -> `Insert New objects`

### Navigation in PADS Logic

* Panning - Scrollbars / Scroll wheel / Insert Key / Middle click
* Ctrl + W -> Left / Right / Left and drag / Middle and drag
* Modeless Commands  
    For a complete list, select Help -> Modeless Commands
    Shortcut key | Description
    -------------|------------
    UN {n}       | Multiple undo command. {n} is the number of operations to undo
    RE {n}       | Multiple redo command. {n} is the number of operations to redo.
    S {s}        | Part search. {s} is the reference designator.
    G {n}        | Set the design grid spacing to {n}.
    GD {n}       | Set the display grid spacing to {n}.
    M            | Display the shortcut menu for the current mode.
    Q            | Quick Measure distances </br> [Measuring in 3D](https://communities.mentor.com/thread/17896)
    U{M/MM/I}    | Use mils/mm/inches as Design Unit

* Toggle Layers
  * F4
  * [mentor communities](https://communities.mentor.com/thread/17896)

#### Select

Select nets only: right click -> Select nets

#### Find

Modeless -> type `s (to be found)`

### Decal

* DGND1, DGND2, DGND3, DGND4...
  * avoid duplicated port name (which may be a constraint of the software but not essential from design point of view).

* Power Symbol, e.g. GND, Power
  * $PWR_SYMS

### Create Schematics

* [Tutorials for PCB Design using PADS - Computer engineering Laboratory](http://www.people.vcu.edu/~rhklenke/tutorials/PADS/PADS_Tutorial_3.3V_Reg/SimpleReg.html)

1. Include necessary library
    * File -> Library -> Manage Lib. List...
2. Change Sheet Size
    * Tools -> Options -> Design -> Sheet ->
      * Size:
      * Sheet: -> Choose...
      * at least A3 for A5M
      * To use A5M Sheet, in `Manage Lib. List...` remove `common` ~~or lower its priority below~~ `PADSLib\ASM`
3. Edit labels
    * Right click the border -> Fields...
    * or use `ASM Template Setup`? (not tried before)
      * U:\APPLCN\APPINI\ASMTSET\ASMTSET.BAT
4. Add Part: ![Add Part](img\PADS_Add_Part.png)
    * Ctrl + R to rotate, Ctrl + F to flip
    * Assign values to your components when necessary
5. Add Connection: Press `F2`
    * add power / ground: right click when routing
      * change symbol: Ctrl + Tab
    * `Bus`

* Replace Part
  * Right click -> Properties -> Change Type

### Design Rules

* Setup -> Design Rules
* Net Constraints
* Only 3 levels available in PADS Logic: `Default`, `Class`, `Net`

* Clearance
  * Setup -> Design Rules -> Default -> Clearance

* Conditional Rules
  * e.g. specific clearance between 2 nets
  * Select Source and Against -> Clearance / High Speed -> `Create` -> 

#### Layers

* `Setup` -> `Layer Deifintion...`

* No. of layers
  * `Modify...`
* Plane
  * CAM Plane
    * no routing and copper planes
    * automatically generated copper
    * assigned to net(s)
  * Mixed Plane
    * allow routing and copper planes
      * copper planes avoid trances by a clearance area
    * assigned to net(s)
* `Thickness...`
  * select thickness, dielectric, material: subtrate/prepreg

### Export

* Intelligent PDF
  * embedded attribute information in PDF
  * File -> Create PDF -> Save

* To PADS Layout
  * Tools -> PADS Layout -> New
    * PADS Layout Link
      * Selection: Tick `Receive Selections`
      * Preferences: Tick `Compare PCB Decal Assignments`
      * Design: Click `Send Netlist`

* BOM
  * .txt: Files -> Reports -> Bills of Materials
  * .xls: Tools -> Basic Scripts -> Basic Scripts -> Load File -> `C:\PADS Projects\Samples\Scripts\Logic\Bill of Materials to Excel`

### View

* Colour
  * Tools -> Display Colors...

* Tie-dots
  * Tools -> Options -> Design -> Tie Dot Diameter: 25 -> 50

* Toggle Bottom view (mirror / flip view)
  * `Alt + B` / ![](2020-10-12-12-20-44.png) in the toolbar

### Check

unused pin
net statastics: net name
  Net has only one pin
  
  net that should not exist
  net that exist but did not exist

MGND vs GND

net name 1, 2, 3 -> 01, 02, 03

## Measure the distance btw 2 traces

* View -> Clearance...

## Macros

* Output Window at the bottom -> Macro
* Visual Basic
  * string replace
    * name = Replace(name, "From this", "To this")
* Unit
  * Tools -> Options -> Global -> General -> Design Units

``` vb
NUM = 30
DIRECTION = 1 ' Left: -1, Right: 1
X = 8300
dX = 300 * DIRECTION
Y = 5486 
EACH_STEP = -100

Dim NET_NAME(NUM)

' import pyperclip
' 
' info = ["SEN1_SHUTTER", "SEN2_SHUTTER", "SEN3_SHUTTER", "SEN4_SHUTTER", "SEN5_SHUTTER", "SEN6_SHUTTER", "SEN7_SHUTTER", "SEN8_SHUTTER", ' "SEN1_FLASH", "SEN2_FLASH", "SEN3_FLASH", "SEN4_FLASH"]
' info_str = str()
' for i in range(len(info)):
'     info_str += 'NET_NAME(' + str(i)+ ') = "' + info[i] + '"\n'
'     print("NET_NAME(" + str(i)+ ') = "' + info[i] + '"')
'     #print(info_str)
' 
' pyperclip.copy(info_str)

NET_NAME(0) = "SPARE_3.3V_1"
NET_NAME(1) = "SPARE_3.3V_2"
NET_NAME(2) = "SPARE_3.3V_3"
NET_NAME(3) = "SPARE_3.3V_4"
NET_NAME(4) = "SPARE_3.3V_5"
NET_NAME(5) = "SPARE_3.3V_6"
NET_NAME(6) = "SPARE_3.3V_7"
NET_NAME(7) = "SPARE_1.8V_1"
NET_NAME(8) = "SPARE_1.8V_2"
NET_NAME(9) = "SPARE_1.8V_3"
NET_NAME(10) = "SPARE_1.8V_4"
NET_NAME(11) = "SPARE_1.8V_5"
NET_NAME(12) = "SPARE_1.8V_6"
NET_NAME(13) = "SPARE_1.8V_7"
NET_NAME(14) = "SEN1_SCL"
NET_NAME(15) = "SEN1_SDA"
NET_NAME(16) = "SEN2_SCL"
NET_NAME(17) = "SEN2_SDA"
NET_NAME(18) = "SEN3_SCL"
NET_NAME(19) = "SEN3_SDA"
NET_NAME(20) = "SEN4_SCL"
NET_NAME(21) = "SEN4_SDA"
NET_NAME(22) = "SEN5_SCL"
NET_NAME(23) = "SEN5_SDA"
NET_NAME(24) = "SEN6_SCL"
NET_NAME(25) = "SEN6_SDA"
NET_NAME(26) = "SEN7_SCL"
NET_NAME(27) = "SEN7_SDA"
NET_NAME(28) = "SEN8_SCL"
NET_NAME(29) = "SEN8_SDA"

' Add Off-page
Application.ExecuteCommand("Add Connection")

For i = 0 To (NUM - 1)
    dY = i * EACH_STEP
    
    Application.ExecuteCommand("Add Connection Corner", X, Y + dY)
    Application.ExecuteCommand("Off-page")
    If DIRECTION = 1 Then
        Application.ExecuteCommand("X Mirror")
    End If

    Application.ExecuteCommand("Finish Move", X, Y + dY)
Next

Application.ExecuteCommand("Cancel")

' Edit Net Name

For i = 0 To (NUM - 1)
    dY = i * EACH_STEP
    
    Application.ExecuteCommand("Select",  X + dX, Y + dY)
    Application.ExecuteCommand("DoubleClick", X + dX, Y + dY)
    DlgQueryNetNameProperties.NetName.Text = NET_NAME(i)
    DlgQueryNetNameProperties.Ok.Click()
Next
```

## PADS Layout

* Right click -> Select Pin pair

* Click Drafting Toolbar (icon with triangle, circle and square) -> Click Board Outline and Cut out

* Tools -> Disperse Components

* Show whole Board `Ctrl+B`

* Show some layers only
  * Modeless: `Z*` (all), `Z1` (1st layer), `1Z 2` (1st and 2nd)...
  * Ctrl + Alt + C / Setup -> Display Color

* Hide all nets
  * View -> Nets -> Select `Default` -> Untick "Traces Plus the Following Unroutes"
  * unrouted nets
    * View -> Nets -> Select `Default` -> View Details: `None`

* Measure Length
  * modeless: `QL` (Quick length)
  * from pin to pin
    * select net / select pin pairs -> double click

  * View -> Clearance

  * Set Origin
    1. Right click -> select Board Outline, and select the board corner (or anything you like)
    2. Setup -> Set Origin
    3. Right click -> select components
    4. right click the component -> Properties
       * It is the distance between the board origin you set, and the origin of the component selected (usually equals the centre, but depends on how it is drawn on the library)

* Pour copper
  * Tools -> Copper Plane Manager -> Start

* ECO mode
  * view -> Toolbars -> Eco Toolbar 


## HyperLynx

* is a simulation tool

* BoardSim - Multiboard
  1. New Multiboard Project
  2. select the connection
      * edit with connection editor
      * simple: just RCL
      * advanced: SPICE / S-parameter, coupling is considered
  3. export sch. -> HyperLynx LineSim

* select nets
  * if you want to force an unmatched IBIS model, there may be some unrelated signals when you select the net
    * Solution: in the IBIS model, remove those [Diff Pin]

* `Simulate SI`
  * `Run Interactive Simulation...`

  * `Run DDRx Batch Simulation...`
    * References:
      * [DDR3 Simulation Setup Guideline](..\Hello_references\Mentor_graphics\DDR3_sim_guide.pdf)
      * [DDR3 ---- 時序嚮導和Write Leveling - Mentor Graphics](..\Hello_references\Mentor_graphics\Mentor%20Graphics_Lab2-DDRx.docx)
      * [Explanation of the HyperLynx DDR Wizard Results Spreadsheets - Mentor Graphics](..\Hello_references\Mentor_graphics\HyperLynx%20DDR3\Explanation%20of%20the%20HyperLynx%20DDR%20Wizard%20Results%20Spreadsheets_10685_A.pdf)
      * Congratulations if you can open the links above

    * `Disable Nets`: depends on your circuit, CKE & CS
    * `ODT Models`: when select OD (in `ODT Behavior`)
    * `IBIS Model Selectors`: may affect V_ref
      * For MT53B256M32D1DS used on Xilinx ZU4CG, use CA/CLK/CS_INPUT_ODT40_3733
        * possible to enable ODT on CA/CLK/CS with MR11 & MR22
    * `Vref Training`:
      * e.g.:

        ``` plaintext
        PinName: U27.W28  Vref: 498
        PinName: U27.Y28  Vref: 498
        PinName: U27.AB28  Vref: 498
        PinName: U27.AA28  Vref: 498
        PinName: U27.Y27  Vref: 498
        PinName: U27.AA27  Vref: 498
        ```
    * `Simulation Options`: `Select IC model corners`: Select all (`Fast-Strong`, `Typical`, `Slow-weak`), `At Die`

* `Simulate SERDES`
  * PCI-e
    * Method 1: compliance wizard
      * available if the whole channel exists, e.g. from board to PC
      * e.g. USB, PCI-e, but no MIPI
      1. `simulate SERDES` -> `(compliance check only)`
      2. select type
      3. channel sweep <- if there's connector in between
      4. disable package model if package model already in the schematic
      5. Report!
          * sdd21, sdd11, impedance, crosstalk...
          * suggestion on pre-emphesis, CTLE value etc.!
      6. Do IBIS-AMI to double confirm if necessary

    * Method 2: IBIS-AMI
      * available even only part of the channel exists, and see if match with the standard
      * `simulate SERDES` -> `IBIS-AMI`
      * Eye-diagram
      * without pre-emphesis and CTLE

  * MIPI
    * compliance wizard not supported yet
    * use HyperLynx DRC

  * FPC
    * if low speed, treat like a cable
    * if high speed (e.g. 800Mbps) & FPC is 2 layers (with GND plane), cannot treat like a cable
      * use multiboard
      * for better accuracy, in `Coupling Setting`, tick `Include trace to area fill coupling`

  * Case: PCI-e board, add-in board <-> connector board <-> PC
    * limitition: connector cannot be simulated in HyperLynx
      * Method 1: make 2 bare PCBs with connectors only -> measure S-parameter
        * variation mainly comes from PCB supplier
      * Method 2: use PCI-e standard S-parameter model (Touchstone .s12p file)
      * Method 3: standard equivalent trace (length & ohm) from PCI-e
        * valid for slower connection (e.g. Gen3 8Gbps)

    * Equalization
      * PCI-e Gen 1: pre-emphesis
      * PCI-e Gen 3: receiver equalization
      * all in buffer model

## Mentor Install

* check license status
  * Manage Licensing -> License Utilities -> Diagnostics & Repair -> Query Status Information -> all licenses (takes times)
    * Feature: padsstdplus_c includes HyperLynx
