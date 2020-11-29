## EMC

### dipole effect

analog GND <-> power supply <-> digital GND
-> effective antenna
decoupling cap/filter

### EMI mitigration techniques

1. striplines
2. microstrip
3. ...

* avoid via for high speed
  * small via = high inductance
  * application specific
* slower rising edge
* board guarding
  * if multiple GND domains, each use guarding if high speed

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

