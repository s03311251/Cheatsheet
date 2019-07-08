# Schematic

## Names
R	Resistors
C	Capacitors
L	Inductors
S	Switches
D	Diodes
Q	Transistors
U	Integrated Circuits
Y	Crystals and Oscillators

## Create Schematic
1. ADD components and frame
	When using search, remember use * e.g. "*atmega328*"

2. NAME components

3. Draw NET
	WIRE just draw wires, not connecting components

4. NAME and LABEL nets

5. SHOW
	click on a pin -> connected pins light up

## Schematic Opearation
1. find
	SHOW -> in text box type "@ VCC"











# Board Layout

## Show Component's Name and Value
Turn on  Layer 25-28 (tNames, bNames, tValues, bValues)

## Move names and parts separately
use SMASH














# PCB Design

## 100 nF on reset pin of MCU
[Source](http://forum.arduino.cc/index.php?topic=165422.0)

In most arduino builds the reset is pulled high with a pullup-resistor, so it doesn't reset. If a new sketch gets uploaded, DTR is going LOW, making the RESET pin go LOW as well. As far as I understand, the DTR pin is LOW for a certain amount of time, which is too long for the RESET pulse of the arduino: the RESET pin has to be pulled HIGH in a shorter time than DTR goes HIGH again. To accomplish this a capacitor is added between RESET and DTR, the capacitor charges (through the pull-up resistor) and reaches +5V again in about the right time for the arduino to see the signal as a RESET signal. As soon as DTR goes HIGH again the capacitor is discharged and is ready for the next RESET signal from DTR.

## 22pF capacitors for crystal oscillator
[Source](http://forum.arduino.cc/index.php?topic=5677.0)

Cl = ((C1 * C2) / (C1 + C2)) + Cs

Where Cl is load capacitance, C1 and C2 are the capacitor values, and Cs is the stray capacitance of the board.

Assuming we want to use two of the same capacitor value, the equation becomes:
Cl = ((C^2)/(2*C)) + Cs

Solving for C gets:
C = 2(Cl - Cs)
