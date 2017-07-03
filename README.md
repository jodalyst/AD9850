# Arduino serial library for AD9850 #
F4GOJ Christophe f4goj@free.fr

August 2014

Modified significantly by Joe Steinmeyer, 2016, 2017.


AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf

Use this library freely.


## Usage notes ##

Library has two classes, `AD9850` and `dualAD9850`.

```c++
#include <AD9850.h> 
```

or 
```
#include 'AD9850.h'
```

## Hardware connections : ##

![ad9850](https://raw.githubusercontent.com/F4GOJ/AD9850/master/images/AD9850.png)

- W_CLK   -> any pin
- FQ_UD   -> any pin
- DATA/D7 -> any pin
- RESET   -> any pin

## Functions : ##

###begin(int w_clk_pin, int fq_ud_pin, int data_pin, int reset_pin)
#####Description
Initialize the output pins and master reset the AD9850
#####Syntax
`DDS.begin(w_clk, fq_ud, data, reset);`
#####Parameters
**w_clk :** Working clock output pin, any pin *(int)*<br>
**fq_ud :** Frequency update pin, any pin. *(int)*<br>
**data  :** Serial data output pin, any pin *(int)*<br>
**reset :** Reset output pin, any pin. *(int)*
#####Returns
None.
#####Example
```c++
void setup(){
 DDS.begin(6, 7, 8, 9);
}
```
###calibrate(double trim_frequency)
#####Description
Compensation of crystal oscillator frequency.<br>
Can be used at any time after initialization.
#####Syntax
`DDS.calibrate(trim_freq);`
#####Parameters
**trim_freq :** Adjust around 125000000 to match the real crystal oscillator frequency. *(double)*
#####Returns
None.
#####Example
```c++
void setup(){
 DDS.begin(6, 7, 8, 9);
}

void loop(){
 DDS.calibrate(124999000);
}
```
###setfreq(double frequency, int phase)
#####Description
Sets the output frequency of the AD9850 and the phase of the signal.
#####Syntax
`DDS.setfreq(frequency, phase);`
#####Parameters
**frequency :** Output frequency in Hz. *(double)*<br>
**phase :** Sets the phase of the output signal, coded on 5 bits allows 32 phase steps of 11,25° each. *(int)*
#####Returns
None.
#####Example
```c++
double frequency = 10000000;
int phase = 0;
DDS.setfreq(frequency, phase);
```
###down()
#####Description
Power down mode reducing the dissipated power from 380mW to 30mW at 5V
#####Syntax
`DDS.down();`
#####Parameters
None.
#####Returns
None.
#####Example
```c++
DDS.down();
```
###up()
#####Description
Wakes-up the AD9850 from power down mode.
#####Syntax
`DDS.up();`
#####Parameters
None.
#####Returns
None.
#####Example
```c++
DDS.down(); // Entering power down mode

// some code doing something

...

DDS.up(); // WAKE-UP !!! :)
```

###Additional Code
The `AD98502.cpp` and `AD98502.h` files are temporary holders for a dual AD9850 controller class.  Originally this was written as a simple wrapper for two standard AD9850 objects (one for each), but the delays in triggering the two devices, caused me to just rewrite to ensure faster, more synchronized setting of digital pins.  Will add examples, once I'm happy with the repackaging.  

* Must add fast Digital Writes

####


