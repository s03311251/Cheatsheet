# Snubber for relay

[Stack Exchange](https://electronics.stackexchange.com/questions/26944/when-why-would-you-use-a-zener-diode-as-a-flywheel-diode-on-the-coil-of-a-relay)

## RC Snubber
RC circuit -> reduce V surge
please refer to ELEC3143 Power Electronics

## MOV (Metal Oxide Varistor)
variable resistor that reduce resistance when voltage difference is high
-> I-V characterics look like a diode in both ways
-> absorb energy when the voltage exceeds a certain level

## Zener Snubber
Flyback diode + Zener in series (of course in anodes opposite direction, so current flow in the same direction)
single flyback diode: RL circuit -> slow
with Zener: drop immediately -> fast



