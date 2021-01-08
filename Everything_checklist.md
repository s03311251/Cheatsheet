# Everything checklist

## PCB

* Design

  * select components
    * [ ] use a table to jog down you search results
      * automatically a checklist + can reuse later 

    * Regulator
      * [ ] check if minimum load fulfill min. requirement -> if not: dummy load
      * [ ] heat dissipation
      * [ ] power-on sequence, use a truth table to check what if one of them powers on before others

      * Switching mode
        * [ ] max. duty cycle
        * [ ] input voltage range
        * [ ] drop out behaviour / inductor voltage drop
        * [ ] input cap: Rated voltage & current
        * Voltage: more margin (e.g. 20% bcz cheaper devices has poorer tolerance)
        * For simplification, choose an input capacitor with an RMS current rating that exceeds half of the maximum load current. The input capacitor value determines the converter input voltage ripple
          * The capacitors must have a ripple current rating that exceeds the converter’s maximum input ripple current. (Ref: MPM3583-7 Datasheet)

      * Linear
        * [ ] dropout voltage
        * Adjustable
          * [ ] min. input voltage
          * [ ] min. output voltage

      * Tolerance
        * [ ] Regulator ripple
        * [ ] voltage drop along the path
        * Adjustable
          * [ ] Tolerance of resistors

    * Op-amp
      * [ ] capacitive load -> stable output?
      * [ ] gain bandwidth
      * [ ] open loop gain
      * [ ] out impedance
      * as current source & sink
        * [ ] source voltage (+/-5V = need Vs+ - Vs- > 10V)
        * [ ] voltage swing / output voltage high/low limit
          * depends on current too
        * [ ] input voltage, voltage diff. from rail
          * 
        * [ ] current source & sink / short-circuit current

    * cap
      * [ ] rating (mind of derating & voltage spike(unless you've TVS @ input))
      * [ ] DC bias -> drop in capacitance

    * charge pump
      * Boost
        * regulated
          * [ ] Can/Would V_in > V_out?

    * Power input
      * [ ] cable & contact resistance
        * VCC & GND, so should double counted 

    * Crystals
      * [ ] crystal cut, oscillation mode, calibration mode, PPM budgets, shunt capacitance, load capacitance, drive level, equivalent series resistance etc.
        * ref: USB3320 P.16 TABLE 4-11: USB3320 QUARTZ CRYSTAL SPECIFICATIONS 

* decal
  * [ ] must be aligned with the datasheet
    * decal downloaded online is usually missing/wrong pin number
    * pin number maybe very small in datasheet

* schematics
  * ref design
    * [ ] use copy & paste when you can copy & paste
    * [ ] if copy & paste in PADS logic, check if those `$XXXXX` nets collide with existing nets
    * [ ] check pinout into the IC, don't rely on common sense/net name
      * e.g. USB RX TX direction
  * [ ] tidy connection, no overlap
  * [ ] reports: unused nets, net list

  * layout guideline
    * [ ] > 5mm between board edge & components
      * during reflow soldering need space to clamp the PCB + space to repair + underfill if BGA
        * affect yield otherwise
        * 3mm is a bare minimum
    * [ ] > 3mm between FPC & components
      * avoid stress from FPC apply on solder joint causing cracks
    * [ ] heat sink (copper pour @ top & bottom)
    * [ ] regulator thermal pad -> heat sink (usually GND, depends on ICs)
    * [ ] ring guard
    * [ ] test point for ICT
    * [ ] no trace near (net behind CM chokes)
    * power trace width
      * [ ] heat: average power (I_PWM)
      * [ ] V drop: peak current
    * ...

  * safety
    * Abnormal power input
      * not necessary to tackle all of them, but at least the most common one

      * If more than one power source (use a truth table to help you):
        * [ ] Not connected
        * [ ] Connected but not powered
        * Alternate solutions: pwr seq., using dedicated pwr supply... but not so user-friendly
      * [ ] Hot plug
        * if not feasible, alternatively mentioned in appl note that: need slow start & power seq. (e.g. GND first)
      * [ ] voltage surge
      * [ ] short-circuit within
      * [ ] short-circuit outside
      * [ ] reverse voltage

    * [ ] EMC
    * [ ] safety & EMC checklist

  * net name
    * [ ] if multiple src with same voltage, put suffix on all of them (e.g. +1.3V_D & +1.3V_AD)
      * if you named it +1.3V, you'll forget that +1.3V_AD does not have the same src as +1.3V

* PCB layout review
  * [ ] symmetry PCB stack-up?
  * high speed signals
    * [ ] length not greater than wavelength / 10
    * [ ] put in inner layer if possible
      * [ ] if can't (e.g. PCI-e conn.), minimum length
  * [ ] check thermal plane & thermal relief

  * signal & power integrity
    * [ ] continuous power plane? whether cut by vias?
    * [ ] GND loop?

  * mech
    * [ ] screw holes keep-out large enough (PCB gp library should hv handle this, but sometimes not, e.g. non-standard usage == without washer)

* solder
  * [ ] use paper to draft your plan, not with your mind

## A5M

* upload files (PNA/ECM/EOR)
  * [ ] no invalid characters in the path (e.g. Greek, Chinese characters)

* eOR
  * [ ] BoM, after import .txt, check if the total no. of parent parts are what you want
  * [ ] 03-, need to include 64-

  * eOR 03-XXXXV1 prototype, BoM to AL5 directly
    * Just export from PADS Logic
    * [ ] include 64- too
    * [ ] include Part Description (e.g. C-CAP 0.01UF 100V +/-10% X7R SMT 0805)
    * [ ] all REF-DES exists

## FPGA

* write code
  * find that some logic need many resources to implement
    * [ ] think twice about the relationship of input data, maybe you can assume something, and so there'll be many cases you don't have to handle

  * propagation delay is too long, even though you think the logic is already very simple
    * [ ] is timing constraint correct?
    * [ ] is it clock domaining crossing (CDC)?
    * [ ] is the pin assignment correct?
      * e.g. if your input signal is a clock, which you'll forward to global clock, you should connect it to a global-clock-capable (GC) pin
    * [ ] can some registers be replaced with constants?
      * e.g. comparing a constant only needs half the LUT as comparing a register
    * [ ] can + pipeline?
      * put 2 registers back-to-back, even though no. of LUT between registers is not shorten, the register need the critical path can be physically placed closer to the LUT and make the delay shorter
      * comparing a 10-bit registers -> comparing 2 5-bit registers in 2 clock cycles, as a LUT has 6 inputs, no cascaded LUT needed

## debug

* [ ] have you turn it off and turn it back on?
* [ ] check if cable connection is tight
* [ ] check .sch, is there any necessary cable you havn't connected?
* [ ] DMM check power input
* using oscilloscope
  * [ ] Have you tried trigger mode already?
  * [ ] using very high sampling rate? If so, it is using "effective sampling rate", and your signal must be repetitive
  * [ ] If look like noise, have you tried larger time scale?
* [ ] calm down, drink some water
