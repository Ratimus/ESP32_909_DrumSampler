# MORAD_DrumsPLUS
This is a Lo-Fi sampler running on Rich Heslip's Motivation Radio hardware platform.
Motivation Radio (MoRad) is an ESP32-based Eurorack module with an MCP3204 12-bit, 4 channel
ADC and two MCP4822 12-bit, 2 channel DACs.

All four DAC channels are used as individual outputs, allowing four samples to play (mostly)
independently at a sample rate of 22 KHz. The following parameters are independently variable
for each sample:
  * Pitch
  * Level
  * Decay
    
Each sample channel has a corresponding CV input, which can be freely assigned to modify any
of the aforementioned parameters. Additionally, the CV can be assigned to the sample selection
for the channel.
