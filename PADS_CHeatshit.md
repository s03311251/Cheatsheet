# mentor graphics PADS

## PADS Logic

[Reference](http://www.people.vcu.edu/~rhklenke/tutorials/PADS/PADS_Tutorial_User_Interface/UserInterface.html)

### Navigation

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

### Select

Select nets only: right click -> Select nets

### Find

Modeless -> type `s (to be found)`

## PADS Layout

Right click -> Select Pin pair

## PADS VX

### Flow

* netlist flow: 1 schematic, 1 layout
* integrated flow: project based

PADS DX-Designer:
* has schematic verify, checking, simulation
* DxDatabook: database
  * link with PNA
* VNC Manager, BoM creation compare in PADS Schematic

### HyperLynx power / DDRx signal integrity
* simulation
  * after layout
