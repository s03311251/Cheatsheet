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

## Battery

* NiCd & NiMH
  * charging
    * https://www.youtube.com/watch?v=_ROhH9EkhtU
    * end-of-charge detection:
      * negative delta V detection
      * temperature increase 
        * NiMH: exothermic charging reaction
        * NiCd: endothermic rx, only rise temperature when finished charging <- pressure built up
    * stages
      * fast charge (1C)
      * top-up (0.1C, ~ 10 min)
      * trickle charge (1/300 C, several hours)

  * internal impedance
    * electrical impedance: contact resistance etc., almost constant, valid in short period of time only (that's why @ 1 kHz mentioned in the datasheet)
    * ionic resistance: resistance due to chemical reaction

## Emergency lights

* https://www.elprocus.com/what-is-an-emergency-light-circuit-diagram-its-working/
  * 


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

