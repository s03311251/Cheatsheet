## SnapEDA
[SnapEDA](https://www.snapeda.com/about/import/)
Drag to projects
Layers:	10 -> Mechanical Layer 1
	20 -> Mechanical Layer 13
	21 -> Mechanical Layer 15


## Schematic

### Numbering
Tools -> Annotation -> Update Changes List



## PCB

### View
Flip		Ctrl+F

### Place Components
Rotate		Spacebar
Flip		X / Y

### Board Size
1. View -> Board Planning Mode
2. Design -> Edit Board Shape

### Hole / Pad
Place -> Pad

### Unit
Snap Grid dialog		Ctrl+Shift+G
Snap Grid			G
Toggle Units			Q / View -> Toggle Units

### Routing
next available signal layer     * / Ctrl+Shift+WheelRoll

### Layers
Available Single Layer Modes	Shift+S
Layer View Configuration	L
Layer Stack			Design -> Layer Stack

### Ground Plane
Place > Polygon Pour

### Track
Change Layer			Ctrl+Shift+Scroll

### Find Similar Object
Shift+F -> Left Click

### Designators font size
Tools -> Preferences -> PCB Editor -> Defaults -> Designator

### Ground Plate
Place -> Polygon Pours
Tools -> Polygon Pours -> Repour All

#### Hide
Tools » Polygon Pours » Shelve xx Polygons

## Output job
[Altium](https://www.altium.com/documentation/18.0/display/ADES/((Preparing+Multiple+Outputs+in+an+OutputJob))_AD)
File -> New -> output job

### PDF
Documentation Output
remember to tick enable
On right hand side, "add new output container" -> "Generate content"





## General Stuff
Thermal Relief: links between pads and planes, ease soldering
Setting under Design Rule -> Plane > Polycon Connect Style

## ComponentClearance
To put things under Blue Pill
Design Rule -> Placement -> Component Clearance -> Minimum Vertical Clearance set to 0mil

