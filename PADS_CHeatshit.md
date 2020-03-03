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
      * To use A5M Sheet, in `Manage Lib. List...` remove `common` or lower its priority below `PADSLib\ASM`
3. Edit labels
    * Right click the border -> Fields...
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

### Check

unused pin
net statastics: net name
  Net has only one pin
  
  net that should not exist
  net that exist but did not exist

MGND vs GND

net name 1, 2, 3 -> 01, 02, 03

## Macros

* Output Window at the bottom -> Macro
* Visual Basic
  * string replace
    * name = Replace(name, "From this", "To this")
* Unit
  * Tools -> Options -> Global -> General -> Design Units

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

* Pour copper
  * Tools -> Copper Plane Manager -> Start

## HyperLynx

* for simulation

* BoardSim - Multiboard
  1. New Multiboard Project
  2. select the connection
      * edit with connection editor
      * simple: just RCL
      * advanced: SPICE / S-parameter, coupling is considered
  3. export sch. -> HyperLynx LineSim

  * SI
    * if you want to force an unmatched IBIS model, there may be some unrelated signals when you select the net
      * Solution: in the IBIS model, remove those [Diff Pin]

* LineSim
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
