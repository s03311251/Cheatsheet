# Hello

## Analogue circuit

### Open collector

![circuit](img\300px-OpencollectorV3.png)

behaves like a switch that is either connected to ground or disconnected

### Zero-ohm link

* typically 10–50 mΩ
* For trace requiring large trace current, better use a 0.001-0.003-ohm resistor, rather than the generic "zero-ohm" resistor in which the actual resistance may be higher, and tolerance is not given

* Usage:
  * Jumper
  * Selective connections
    * R40, R41, R44, R45 in [06-22332B schematic](C:\Users\aeemcng\Documents\Cone\2019-07-03_burnt_5M_cam\06-22332_@_A1_NOTED.pdf)  
      ![0 ohm](img\06-22332_zero_ohm.PNG)
      * 0 ohm between USB port and CY7C68013A USB Peripheral Controller
      * not a jumper
        * either use 0 ohm resistor / the U6 choke, actually U6 is absent in the real product
    * > Concern of the 0ohm resistance (we may call it the “bridge”) is not current capacity, but how much impedance it will create.  2A passing through 10 milliohm will drop the 0.85V by more than 2%.  AC impedance also needs to be considered (i.e. whether the bridge will become current path bottleneck).  If the load is scattered on power planes, it would be better to provide more bridges to connect two planes because it will result in more effective use of the planes.
  * Current sensing before production
    * [StackExchange](https://electronics.stackexchange.com/questions/42756/what-is-the-usage-of-zero-ohm-miliohm-resistor)
    * provide a current measurement point. During development and testing you can place a low resistance shunt resistor to measure the current, and for production replace it with a zero ohm jumper. Then you don't have to cut traces to insert the shunt resistor in the circuit. Probably less applicable, since you should have measured the current before creating the final PCB, but for very low current circuits the layout and PCB material may matter, and then you do want to measure on the final board.

* Calculation: consider power & voltage loss
  * source of resistance: solder, 0ohm resistor, constrainted PCB traces connection the 0Ω resistor
  * e.g. Resistor: 20mΩ
         Solder: Resitivity × Length ÷ Area  
               = 0.153 μΩ∙m × 0.45mm?(~ height of SMD) ÷ (0.45mm×0.85mm)?(~W × H)
               = 0.00018μΩ = ~0Ω

### Shunt

[StackExchange](https://electronics.stackexchange.com/questions/42756/what-is-the-usage-of-zero-ohm-miliohm-resistor)

* Bypassing the sense resistor with a capacitor - maybe 10 uF or 100 uF depending on circuit
  * further reduce impact on the circuit
* Use an eg 0.1 Ohm shunt,  
  feed the voltage via a series 1k resistor to the meter, and  
  a say 10 uF across the meter terminals.
  * reduce affected by high frequency noise

### Snubber for relay

[Stack Exchange](https://electronics.stackexchange.com/questions/26944/when-why-would-you-use-a-zener-diode-as-a-flywheel-diode-on-the-coil-of-a-relay)

#### RC Snubber

RC circuit -> reduce V surge
please refer to ELEC3143 Power Electronics

#### MOV (Metal Oxide Varistor)

variable resistor that reduce resistance when voltage difference is high
-> I-V characterics look like a diode in both ways
-> absorb energy when the voltage exceeds a certain level

#### Zener Snubber

Flyback diode + Zener in series (of course in anodes opposite direction, so current flow in the same direction)
single flyback diode: RL circuit -> slow
with Zener: drop immediately -> fast

## Digital circuit

* Passive Delay Line
  * [Passive Delay Line Design Considerations](http://www.rhombus-ind.com/dlcat/app1_pas.pdf)
  * A Passive Delay Line is a special purpose Low Pass Filter designed to delay (phase shift) the input signal by a specifiedincrement of time, and is composed of series inductors andshunt capacitors with values dictated by the line impedance.

* Schmitt trigger
  * comparator with hysteresis: originally LOW, need higher voltage to switch to HIGH, vice versa
  * achieved by positive feedback to noninverting input of a comparator
  * e.g. 74HC9115

* Ground bounce
  * [Allaboutcircuits](https://www.allaboutcircuits.com/technical-articles/how-to-reduce-ground-bounce-mitigating-noise-pcb-design-best-practices/)
  * CMOS in IC: inductance in trace between output and VDD/GND -> when changing state, inductance causes -ve voltage -> Gate voltage not low enough, MOS keep open and close -> oscillate
    * solution: decoupling cap close to ICs power rail, current limit resistor, reduce inductance i.e. shorter return path

### Signal

* UI: Unit interval = 1 / baud
* Baud = symbol rate, Baud rate = ATM machine (grammatically)
* Slack
  * [(原創) timing中的slack是什麼意思? (SOC) (Quartus II) - 真 OO无双](https://www.cnblogs.com/oomusou/archive/2010/08/04/timing_slack.html)
  * Required arrival time (RAT): affected by setup time / hold time of next clock edge and clock skew
  * Actual arrival time: based on hold time from this clock edge, propagation delay though logic and clock skew

  * Setup Slack =  RAT - Actual arrival time
    * worst on slowest path
      * [What is the best way to improve negative slack? - Xilinx Forum](https://forums.xilinx.com/t5/Timing-Analysis/What-is-the-best-way-to-improve-negative-slack/td-p/995872)
      * Possible reasons: too much processing, clock crossings, I/O, high fanout
      * To improve: use constants, LUT, parallel processing

  * Hold Slack = Actual arrival time of next data - RAT
    * worst on fastest path (e.g. flip-flop to flip-flop), but usually solved by the router in FPGA implementation

  * Setup slack is a function of frequency but hold slack is not
    * [Negative Hold Slack for AXI Interconnnect - Xilinx Forum](https://forums.xilinx.com/t5/Timing-Analysis/Negative-Hold-Slack-for-AXI-Interconnnect/m-p/1073222#M18781)

  * -ve slack = SHIT!

#### Signal format

* [Van Eck phreaking](https://en.wikipedia.org/wiki/Van_Eck_phreaking)
* [Data strobe encoding](https://en.wikipedia.org/wiki/Data_strobe_encoding)
  * XOR always equal to clock signal

##### I2C

* more peripheral -> more capacitance -> longer rise time -> slower bus speed

###### Inertial delay

[Xilinx forum](https://forums.xilinx.com/t5/Networking-and-Connectivity/Set-INERTIAL-DELAY-in-IIC-module/td-p/495248)

* parameters in Xilinx AXI IIC IP
  * e.g. AXI clock = 100MHz, C_SCL_INERTIAL_DELAY = 5, delay = 10ns * 5 = 50ns
* pulse rejection & delay inside
* SCL delay longer than SDA -> undesirable
* SDA delay longer than SCL -> increase hold time, may eliminate errorneous starts/stops

##### USB

[USB in a NutShell](https://beyondlogic.org/usbnutshell/usb1.shtml)

* Endpoint: 1 IN, 1 OUT
  * EP0 for control transfer
  * at most 16

* in 1 transaction: 1 token packet, 1 or more data packet, 1 handshake packet

* Packet
  * Include diff. fields
    * Sync, PID, ADDR, ENDP, CRC, EOP
    * No any types contains all fields
  * Types: Token, Data, Handshake Packets
    * Token: In, Out, Setup
    * Data: Data0, Data1
    * HandShake: ACK, NAK, STALL

* Transfer
  * Control Transfer
    * Setup, Data, Status Stages
    * reserved 10% (20% for USB3.0) bandwidth for control transfer
      * bandwidth will release if there's no control transfer waiting
  * Interrupt Transfer
  * Bulk Transfer
  * Isochronous Transfer

###### Electrical

Pin Number | Cable Colour | Function
-----------|--------------|---------
1 | Red | V_BUS (5 volts)
2 | White | D-
3 | Green | D+
4 | Black | Ground

* D+ and D-
  * both differential and single ended
    * differential:
      * 'J' = diff. '0' = D- - D+ > 200mV
      * 'K' = diff. '1' = D+ - D- > 200mV
      * On low and full speed devices, a differential ‘1’ is transmitted by pulling D+ over 2.8V with a 15K ohm resistor pulled to ground and D- under 0.3V with a 1.5K ohm resistor pulled to 3.6V. A differential ‘0’ on the other hand is a D- greater than 2.8V and a D+ less than 0.3V with the same appropriate pull down/up resistors. 
    * single ended:
      * SE0 D+ & D- < 0.3V (low) for > 10ms
* characteristic impedance: 90 ohms +/- 15%
* High Speed (480Mbits/s) mode uses a 17.78mA constant current for signalling to reduce noise. 
* Speed Identification: pulling D+/D-
  * based on speed
    * 1.5k ohm pull up D+: full speed
    * 1.5k ohm pull up D-: low speed
    * High speed devices will start by connecting as a full speed device
  * identify existance of USB device too
  * some ICs uses built-in resistor in silicon -> can turn on/off
    * off before ready for initialising the USB function
* Power
  * Low-power bus powered functions
    * work under 4.40V - 5.25V
    * 1 unit load = 100mA
  * High-power bus powered functions
    * detected and enumerated under 4.40V - 5.25V
    * work under 4.75V - 5.25V
    * 5 unit load = 500mA
  * Self-powered functions
    * 1 unit load from bus = 100mA
      * identification
  * Never drive V_BUS on its upstream facing port
  * Suspend Current 500uA per unit load
    * Sth drawing currents:
      * pull up resistors
      * linear regulator's quiescent current
      * MCU's clock
    * Suspend Mode
      * no activity for 3 ms
        * has to drawn less than suspend current in further 7 ms
      * send frame packet to keep alive
        * high speed: micro-frames every 125.0 µs ±62.5 ns
        * full speed bus: frame sent down each 1.000 ms ±500 ns
        * low speed bus: keep alive which is a EOP (End of Packet) every 1ms only in the absence of any low speed data
    * Signalling rate
      * High speed: 480.00Mb/s ± 500ppm
      * Full speed: 12.000Mb/s ±0.25% or 2,500ppm
      * Low speed: 1.50Mb/s with ±1.5% or 15,000ppm
        * therefore resonator is acceptable for low speed only

###### Class

[USB-IF](https://www.usb.org/defined-class-codes)

* Application Specific (FEh)
* Vendor Specific (FFh)

###### Enumeration

* SuperSpeed enumeration does not require D+ and D-
  * [USB 3.x SS enumeration - StackExchange](https://electronics.stackexchange.com/questions/297031/usb-3-x-ss-enumeration)

###### OTG

* [USB On-The-Go - Wikipedia](https://en.wikipedia.org/wiki/USB_On-The-Go#Plug)
* A: ID pin connected to ground
  * different resistance to ground -> different ID
* B: ID pin floating

##### PCI Express = PCIe

* _Referenece: [Wikipedia](https://en.wikipedia.org/wiki/PCI_Express#Pinout)_

Lane        | Total Pin number
------------|-----------------
before notch| 11
PCIe ×1     | 18
PCIe ×4     | 32
PCIe ×8     | 49
PCIe ×16    | 82

##### AXI

###### Handshake

* A3.2.2 Channel signaling requirements - Channel handshake signals
  * for Write / Address, not recommend a default READY, as transfer takes >= 2 cycles (1 for VALID, 1 for READY)

* A3.3.1 Dependencies between channel handshake signals
  * assertion of VALID can never be dependent on READY
    * but de-assertion of VALID should depend on READY (cannot de-assert until READY accepts the transaction)
  * READY can:
    * wait for VALID
    * not detecting VALID at all

##### JTAG

* [JTAG pull-up/down resistors : mandatory or optional?](https://e2e.ti.com/support/microcontrollers/other/f/908/t/348680?JTAG-pull-up-down-resistors-mandatory-or-optional-CORTEX-M4-0-JTAG-Communication-Error-Error-1170-0x0-)
* pull-up / pull-down is necessary for TCK to prevent fake TCK pulse at power up
* ARM: TMS, TDI, TDO must have pull-ups
  * may enter boundary scan mode if not doing so

#### Signal integrity

* slew rate
  * ΔV/s or ΔA/s
  * higher slew rate -> higher frequencies of intrest, higher EMI

##### high speed connection

* not much design difference
* ESD protector

##### cable

###### USB shielding & termination

* attenuation
* insertion loss
* return loss
  * Voltage Standing Wave Ratio (VSWR) is the same thing, just a different calculation
    * Reflection coefficient Γ = V_r (reflected) / V_f (forward) = (Z_L - Z_O) / (Z_L + Z_O)
    * VSWR = (1 + |Γ|) / (1 - |Γ|)
    * return loss = -10 log Γ^2 (because return loss is related to power) = -20 log ((VSWR - 1)/(VSWR + 1))
* skew rate
* EFT test
* EMC resortion lost
* Eye pattern
  * [Understanding Eye Pattern Measurements](https://rintintin.colorado.edu/~gifford/5830-AWL/Anritsu%20Eye%20Diagram.pdf)

  * Eye Crossing Percentage = [(crossing level – zero level) / (one level – zero level)]
    * Eye crossing is the crossing points (X-shape) on the left/right of the eye pattern
    * Percentage is a measure in vertical axis
  * Eye Height = (One level - 3σ) - (Zero level + 3σ)
  * Signal-to-Noise Ratio = (One level - Zero level) / (1σ [One level] + 1σ [Zero level])

  * Eye Width = (right crossing - 3σ) – (left crossing + 3σ)
  * Jitter: variances at the eye crossing point

* instrument: network analyzer
  * source of error
    * fixture loss calibration
    * setup parameter
      * rise time
      * IF resolution
      * sampling frequency

##### Transmission line model

Ref: *ELEC3342 Ch. 8*

transmission line effect: ringing in transmission

apply when:

* rise time ~= path delay
  * depends on:
    * length
    * speed of light in the medium

* trace length
  * [Why do characteristic impedances matter only when traces are longer than half a wavelength? - Stackexchange](https://electronics.stackexchange.com/questions/178112/why-do-characteristic-impedances-matter-only-when-traces-are-longer-than-half-a)
  * [How to Calculate Trace Length from Time Delay Value for High-speed Signals - ZUKEN Blog](https://blog.zuken.com/how-to-calculate-trace-length-from-time-delay-value-for-high-speed-signals/)
    *             v_Er = f λ_Er  
          c / sqrt(Er) = f λ_Er  
      c / sqrt(Er) / f = λ_Er
    * v_Er: signal speed on a PCB transmission line
    * Er: dielectric constant of the PCB material, 4 for FR4
      * if microstrips is used instead of striplines, Er_effective ~ (0.64 Er = 0.36)
    * trace length need to be 1/10 of λ_Er

###### Characteristic Impedance

* ratio between voltage and current waves that travel down the channel
* uniform, lossless line: Z_0 = sqrt(L/C)
* typical: 50-75 ohm

Ref: *[What is Characteristic Impedance? - Eric Bogatin](..\Hello_references\BTS002_Characteristic_Impedance_NOTED.pdf)*

* Z_0 = 1/(C_L v), C_L = C of the line, v = speed of the signal

* Impedance mismatch when connecting multiple DRAM -> T in the lines
  * [Selecting different impedances then 50 ohm in DDR3 - StackExchange](https://electronics.stackexchange.com/questions/108345/selecting-different-impedances-then-50-ohm-in-ddr3)

###### Reflections

* occurs when unmatched line with source/load
* Γ = (Z_L - Z_0)/(Z_L + Z_0)
* V_reflected = Γ V_incident

###### Termination

* Source termination: invalid levels momentarily
  * e.g. P2P connection
* Load termination: power dissipation exists
  * e.g. multi-drop bus
* Both end
  * e.g. bus with multiple receivers and drivers <- prevent reflections from either end

##### Intersymbol Interference

* bit affected by bit before
* sources:
  * Next bit before reflections damp out
    * unterminated transmission line: mim. bit time = several round trips
  * dispersion <- nonzero line resistance
  * crosstalk
    * capacitance to its neighbour
    * noise on non-switching wires
      * if victim is floating: ![crosstalk on nonswitching wires](img\crosstalk.png)
      * if victim is driven: ![crosstalk on driven wires](img\crosstalk_driven.png)
    * increased delay on switching wires
  * ground bounce <- nonzero return path impedance

#### High-speed I/O

Ref: *ELEC3342 Ch. 8*

* transmit data > flight time
* high-impedance driver + load termination?
* low-impedance driver + source termination?

##### Repeater

* Reason: R, C proporational to l -> RC delay proporation to l^2
  * break long wires into segments -> l/N
* buffer or inverter

## High-level digital circuit design (e.g. FPGA)

### FPGA

* CLB (configurable logic block)

* Simulation
  * input **cannot** change at the same time as rising edge of clock
    * if clock is in another process, the order of the execution between these processes is unknown -> unexpected result

### Low-pass filter

* design consideration: the signal that you want to filter
  * noise has specific waveform (e.g. EFT, ESD human-body model)
  * based on sampling rate and latency requirement, select target clock

* high speed -> analogue; low speed -> digital
* Debouncer
  * Take multiple samples, change state only when all samples are the same
    * Actually it's just a low-pass filter with extreme threshold!

* Implementation
  * Method 1: shift register, take all input
  * Method 2: counter and FIFO, +1 if HIGH, -1 if LOW for FIFO in,  -1 if HIGH, +1 if LOW for FIFO out
    * may be better because more flexible, and the actual implementation is similar to method 1
  * Method 3: counter, +1 if HIGH, -1 if LOW, but there's upper limit and lower limit
  * BTW, Low-pass filter is just a subset of FIR/IIR filters!

## EMC













## Package

* Dimension
  * BSC (Basic Space between Centres)
    * [Xilinx Forum](https://www.xilinx.com/support/answers/8393.html)
    * is used to describe the **theoretically** exact size, shape, or location of a feature or datum target; this is shown on drawings enclosed in a rectangle. It is the basis for determining which permissible variations are established by tolerances on other dimensions.
  * REF (Reference)
    * = appropximately

## Instrument

* Thermocoupler
  * [感溫棒(熱電偶)的接線種類差異與選擇、Ktype、Ntype、Stype、Jtype-SJ儀錶](https://www.sj-gauge.com/_tw/faq/detail.php?cid=15&faqid=167)

* example of vendors
  * Keysight
  * Fairview Microwave
  * Southwest Microwave
  * Amphenol
  * Hubersuhner

## DMA

* DMA is an **ability**
* **bus master** can be a **DMA Controller**, a **CPU** or a **FPGA**'s functional block

## PCB

* Active Low
  * Recommanded
    `my_signal#`, PCI standard
  * Not recommanded
  * `/my_signal`
  * `my_signal` with a bar on top
    * the bar may mixed with signal line
  * `my_signal_n`
    * may mixed with differential signal (`_p`, `_n`)
  * `my_signalb`

* Fiducial Mark
  * [What is a Fiducial Mark - PCB 3D](http://www.pcb-3d.com/tutorials/what-is-a-fiducial-mark/)
  * referent points on the PCB to position the Surface Mount Components (Packages) on the PCB during assembly

* Via
  * through hole VS blind (in one of outermost layers only) VS buried (not shown in outermost layers)
    * cost with blind/buried vias is significantly higher
  * via-on-pad
    * [導通孔在墊(Vias-in-pad)的缺點及處理原則](https://www.researchmfg.com/2010/11/vias-in-pad/)
    * Copper-Filled Vias
      * [What Are Copper-Filled Vias?](https://www.mclpcb.com/copper-filled-vias/)
      * fills the through holes with epoxy resin and copper
      * increase thermal and electrical conductivity

* Thinkness = Cu weight
  * 1oz of copper = 1oz of copper is pressed flat and spread evenly over a one-square-foot area
    * = 1.37 mil
    * = 0.03479 mm
  * minimum space between copper features
    * [Copper Thickness FAQ - PCB Universe](https://www.pcbuniverse.com/pcbu-tech-tips.php?a=4)
    * 1oz: 3.5 mil
    * 2oz: 8 mil
    * 3oz: 10 mil
  * DNP in schematics
    * Do Not Place
* multi-layer board
  * [Stack Exchange](https://electronics.stackexchange.com/questions/356063/what-exactly-is-prepreg-and-core-in-a-pcb)
  * copper - prepreg - copper - core - copper - prepreg - copper
    * usually FR4
* BGA
  * SMD VS NSMD
    * ![SMD VS NSMD](img/SMD_vs_NSMD.png)
    * [MACROFAB](https://macrofab.com/blog/bga-pad-creation-smd-nsmd/)
    * depends on manufacturers' recommended footprints
    * NSMD pad style is recommended wherever possible due to its improved solderability and pad accuracy
* differential pair length matching

### Ground

* Ground region - separated in ground plane
  * usually continuous ground is good enough
    * Don't separate ground (e.g. DGND, AGND), unless you know clearly how to do, why to do and what to do
      * e.g. analogue and digital components
  * Signal Interconnect - Principle
    * Signal is always a loop, larger loop -> *usually* more interference because like an antenna
      * e.g. ground layer shorten the loop
      * Solution:
        * singal on upper layer, bridge between ground plane in ground layer right underneath it

#### CHGND = Chassis ground

* [Stack Exchange](https://electronics.stackexchange.com/questions/149643/physically-how-does-connecting-a-pcb-to-chassis-ground-reduce-noise)
* [Stack Exchange](https://electronics.stackexchange.com/questions/357474/circuit-ground-vs-chassis-ground)
* [EEVblog Electronics Community Forum](https://www.eevblog.com/forum/projects/usb-shield-ground-connection/)
* Capacitor to Digital Ground
  * low impedance path for high freq.
    * USB connector -> chassis ground -> digital ground
  * but why cap for metal shell too?

#### Use thick ground plate to short CHGND together

![Use thick ground plate to short CHGND together](img\Use_thick_ground_plate_to_short_CHGND_together.PNG)

* In [06-22332B schematic](C:\Users\aeemcng\Documents\Cone\2019-07-03_burnt_5M_cam\06-22332_@_A1_NOTED.pdf)
* between the case of USB port and CHGND

#### e.g.



* ESD -> connector pins to MGND
* 

### Thermal

* graphite sheet roll into a block
  * volume resitivity high but surface resitivity low
  * less affected by thickness, can up to 10~20mm
  * should be non-conductive

* high wattage IC e.g. FPGA, thermal can actually be put under PCB, as copper couduct better than the plastic package
  * bottom cannot have huge components
  * even better: Specific a GND pad for thermal pad!

* layout design
  * e.g. thermal conductivity of ground plane
  * online calculator!

* coefficient of thermal expansion (CTE)

* IC parameters
  * [Semiconductorand IC Package Thermal Metrics - TI](\\AHKPC0393\Cone\Hello_references\spra953c_Semiconductorand IC Package Thermal Metrics_NOTED.pdf)

  * Operating junction temperature, T_J

  * R_θJA: Junction-to-ambient thermal resistance
    * based on standardized test, e.g. JEDEC EIA/JESD51-x
    * misuse: T_J = T_A + (R_θJA × Power)
      * affected by: PCB > pad size > internal package of IC > altitude > T_A > power dissipation
    * best used as a comparison of package thermal performance between different companies
      * e.g. TI: 40°C/W, ST: 45°C/W, TI will likely run 10% cooler

  * R_θJC: Junction-to-case thermal resistance
    * EIA/JESD51-1  
      > the thermal resistance from the operating portion of a semiconductor device to outside surface of the package (case) closest to the chip mounting area when that same surface is properly heat sunk so as to minimize temperature variation across that surface.
    * used when there's a heat sink
  * R_θJB: Junction-to-board thermal resistance

## Memory

### Flash Memory

* [Flash 101: NAND Flash vs NOR Flash](https://www.embedded.com/flash-101-nand-flash-vs-nor-flash/)
* NOR
  * one end of each memory cell is connected to the source line and the other end directly to a bit line resembling a NOR Gate
  * slower, larger
  * more power on current, less standby current
  * similar instantaneous active power, but NOR has faster random read time
  * allows code execution directly from NOR Flash
  * has enough address and data lines to map the entire memory region
    * faster random read
* NAND
  * memory cells (transistor) connected in series similar to a NAND gate
  * use an 8-bit or 16-bit multiplexed address/data bus with additional signals such as Chip Enable, Write Enable, Read Enable, Address Latch Enable, Command Latch Enable, and Ready/Busy
    * slower random read

### DDR

* SDP (1 die per package) vs DDP (2 dice per package)
* Pin
  * CA (Command Address)
    * LPDDR4: latched on rising edge of the clock
      * 2-tick CA capture, i.e. each command requires 2 clock edges to latch (does this depends on RAM model?)
  * CLK (Clock)
  * DQ (Data)
  * DQS (Data Strobe)
    * clock for DQ, active only when read/write
    * Read & Write has different sampling postition for DQ on DQS
  * CKE (Clock Enable)
    * active high, act as clock stopped if LOW
  * CS (Chip Select)
    * active low, act as NOP received if HIGH
  * Mode Registers
    * programmable by controllers
  * V_ref
    * middle of voltage swing
    * in LPDDR4 (and DDR4), V_ref is changable through V_ref training
      * 2 range: range0 (10% - 30% of V_DD2), range1 (default, 22% - 42% of V_DD2)
        * V_DD2 = 1.06 - 1.17V

## EMC (electro-magnetic compatibility)

* Radiation
  * high risk:
    * oscillator
    * I/O without insulator
      * no need to add CM choke if isolated
* Immunity
  * Electrical Fast Transient (EFT)
    * Once the Teli camera has spark during test
      * Solution:
        * Shell coating removed (1 side of Teli cam is silvery)
        * Capicitors added
* Coupling
  * R, C, L - conductive, capacitive, inductive
    * loop is inductive
    * wire, PCB trace are conductive and some capacitive
* Electrostatic Discharge (ESD)

  * Ref: *ELEC3342 Ch. 8*
    * current limiting resistor
    * diode clamps -> over/under-voltage surge
    * thin gate oxides

  * low standard in A5M, as nobody would touch the machine in operation
    * performance degrade is acceptable, but should be able to restart

  * 

* filter from origin (e.g. add cap.) is better than from connector
  * e.g. between origin and EMI filter, other signal may be contiminated -> EMI too
  * e.g. VGA box clock signal

### differential-mode VS common-mode noise

* [Differential (Normal) Mode Noise and Common Mode Noise－Causes and Measures](https://micro.rohm.com/en/techweb/knowledge/emc/s-emc/01-s-emc/6899)
* internal differential-mode + stray cap & inductance -> common-mode noise externally

#### Common-mode choke

* passing differential-mode (DM, equal but opposite) currents, while blocking common-mode (CM) currents
  * The magnetic flux produced by DM currents in the core tend to cancel each other due to negative coupled windings
  * little inductance or impedance to DM currents -> cone won't saturate -> maximum current rating is determined by the heating effect of the winding resistance only
  * Opposingly, CM currents see a high impedance

* L6 in [06-22332C schematic](C:\Users\aeemcng\Documents\Cone\2019-07-03_burnt_5M_cam\06-22332C_wrong_version\64-22332C_X_X1-CIRCUIT.sch)  
  ![CM choke](img\CM_choke.png)
  * between 3.3V and GND from connector and 3.3V and GND being actually used

## IC

* Power-up and Power-down sequence
  * avoid some voltage is higher than others internally
  * concern: voltage and current
  * e.g. diode for protection, but sudden need to conduct continuously if in wrong sequence

## Power

* Power Sequence
  * UG925 P.15
  * IC
    * CAT811 Power Supply Supervisor
    * MAX705–MAX708/MAX813L Low-Cost, μP Supervisory Circuits

* power regulator
  * has ramp up time
    * must be accounted in power sequence
  * Buck Converter
    * [PFM - Wikipedia](https://en.wikipedia.org/wiki/Pulse-frequency_modulation#Buck_Converters)
    * PWM vs PFM
      * PFM: suitable for low load
        * fixed 50% duty cycle for a period of time, then shut off
        * ![PFM of LMZ20502](PFM_of_LMZ20502.png)
      * Pros: PFM prevents inductor current drops to 0 -> no distinuous mode -> reduce conduction loss in inductors and capacitors
      * Cons: Higher ripple
    * Output capacitor
      * determines transient response behavior, ripple and accuracy and stability
      * [Optimal Transient Response for Processor Based Systems - Power Electronics](https://www.powerelectronics.com/technologies/regulators/article/21853270/optimal-transient-response-for-processor-based-systems)

* Protection
  * Fuse

  * Zener / TVS
    * TVS absorbs surge voltage

    * Zener provides constant voltage
    * Max. reverse standoff voltage: the voltage below which no significant conduction occurs
    * Breakdown voltage: the voltage at which some specified and significant conduction occurs

  * Reverse voltage protection
    * ![ElectroBoom](2019-11-07-10-40-06.png)

  * Load switch
    * e.g. FPF2702
      * Over-current protection
      * UVLO
      * Thermal shutdown

## Capacitor

* ![type of capacitor: Radial, Axial and Disc](2019-11-01-09-35-36.png)
* tantalum cap
  * not enough design margin -> short-circuit -> on fire -> DON'T USE

* Bypass & Decoupling Cap.
  * Bypass Cap.: reduce high freq. current
  * Decoupling Cap.: reduce peak-to-peak voltage
  * consider 100 Hz up to 100 MHz
  * usually 0.1uF in parallel with higher value capacitor
  * no thermal reliefs <- increase ESL

* Bulk Cap.
  * [De-coupling capacitor and Bulk capacitor - StackExchange](https://electronics.stackexchange.com/questions/170957/de-coupling-capacitor-and-bulk-capacitor)
  * A bulk capacitor is used to prevent the output of a supply from dropping too far during the periods when current is not available (e.g. buck converter)

* Ceramic
  * MLCCs: Multilayer Ceramic Capacitors
  * Rating
    * [X7R, X5R, C0G…: A Concise Guide to Ceramic Capacitor Types - All About Circuits](https://www.allaboutcircuits.com/technical-articles/x7r-x5r-c0g...-a-concise-guide-to-ceramic-capacitor-types/)
    * Class 2,3 dielectrics, e.g. X5R, X7R
      X: -55°C  
      5: 85°C; 7: 125°C
      R: capacitance change over temperature = ±15%
      * Class 2 caps exhibit piezoelectric behaviour that can cause them to function as both microphones and buzzers
    * Class 1, e.g. C0G
      * suitable for audio due to the lack of piezoelectric behaviour
  * Life expenctancy
    * search for "hour", "endurance", "Load Life" in datasheet

## spark even if switch is off

* EMI filter (e.g. cap) before switch
  * they are reliable, no worry
  * prevent noise entering the device -> better

## Insulation

* clearance
  * The shortest path between two conductive parts, or between a conductive part and the bounding surface of the equipment, measured through air.
* creepage
  * The shortest path between two conductive parts, or between a conductive part and the bounding surface of the equipment, measured along the surface of the insulation.
  * [MySensors](https://forum.mysensors.org/topic/4175/clearance-creepage-and-other-safety-aspects-in-mysensors-pcbs)

## WTF are you talking about?

* https://www.ximea.com/en/corporate-news/camera-carbon-neutral-energy

> It uses XIMEA’s circular DMA buffers to predict where the next frame will be delivered.
> It then polls on the last pixel of that frame until it is non-zero, meaning that the frame was just delivered to the DMA buffer.
> This approach resulted in communication jitter reduction from ~1ms to less than 200 ns on 10 cameras simultaneously. 
> “I was shocked when I found out how well the cameras performed in our real-time application, and all of that with a simple change of synchronisation scheme.” — Artur Perek, MANTIS system developer.

## I/O

### GPIO

* ![Balser 14M camera example](2019-11-27-19-56-24.png)
  * upper part: input - Diode-transistor logic
  * transistor in lower part: output

## System

* compensation capacitor
  * for [frequency compensation](https://en.wikipedia.org/wiki/Frequency_compensation)
  * e.g. LMZ20502 Voltage regulator's feedback (C_FF)
    * ![](2019-11-28-19-04-57.png)

## Response Time

* [Response Time Measurement](https://www.tftcentral.co.uk/articles/response_time.htm)
