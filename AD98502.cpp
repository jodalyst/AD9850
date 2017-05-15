/******************************************************************************************************************
 * Arduino library for AD9850
 * Created 23/08/2014
 * Christophe Caiveau f4goj@free.fr 
 * Modified by Joe Steinmeyer, 10/24/2016 jodalyst@mit.edu
 * BAD CODING PRACTICE RIGHT NOW...WILL MERGE WITH ORIGINAL LIBRARY EVENTUALLY!!!!
 *
 * Use this library freely
 *
 * Hardware connections : 
 * W_CLK   -> any pin
 * FQ_UD   -> any pin
 * DATA/D7 -> any pin
 * RESET   -> any pin
 *
 * Functions :
 * dds.begin(W_CLK pin, FQ_UD pin, DATA pin, RESET pin); Initialize the output pins and master reset the AD9850 
 * dds.calibrate(frequency); Compensation of crystal oscillator frequency
 * dds.setfreq(frequency,phase); frequency in Hz, phase coded on 5 bits
 * dds.down(); power down mode reducing the dissipated power from 380mW to 30mW @5V
 * dds.up(); wake-up the AD9850
 *
 * AD9850 datasheet at http://www.analog.com/static/imported-files/data_sheets/AD9850.pdf
 *
 *****************************************************************************************************************/

#include "AD98502.h"

dualAD9850 DDS;
dualAD9850::dualAD9850() {

}

void dualAD9850::begin(int w_clk1, int fq_ud1, int data1, int reset1,int w_clk2, int fq_ud2, int data2, int reset2) {
    W_CLK1 = w_clk1;
    FQ_UD1 = fq_ud1;
    DATA1 = data1;
    RESET1 = reset1;
  W_CLK2 = w_clk2;
  FQ_UD2 = fq_ud2;
  DATA2 = data2;
  RESET2 = reset2;
    deltaphase1 = 0;
    phase1 = 0;
  deltaphase2 = 0;
  phase2 = 0;
    calibFreq = 125000000;
    begin_priv();
}

void dualAD9850::begin_priv() {
    pinMode(W_CLK1, OUTPUT);
    pinMode(FQ_UD1, OUTPUT);
    pinMode(DATA1, OUTPUT);
    pinMode(RESET1, OUTPUT);
    pinMode(W_CLK2, OUTPUT);
  pinMode(FQ_UD2, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(RESET2, OUTPUT);
    pulse(RESET1);
  pulse(RESET2);
    pulse(W_CLK1);
  pulse(W_CLK2);
    pulse(FQ_UD1);
  pulse(FQ_UD2);
 
}

void dualAD9850::update() {

    for (int i=0; i<4; i++, deltaphase1>>=8) {
     shiftOut(DATA1, W_CLK1, LSBFIRST, deltaphase1 & 0xFF);
    }
    shiftOut(DATA1, W_CLK1, LSBFIRST, phase1 & 0xFF);
    for (int i=0; i<4; i++, deltaphase2>>=8) {
     shiftOut(DATA2, W_CLK2, LSBFIRST, deltaphase2 & 0xFF);
    }
    shiftOut(DATA2, W_CLK2, LSBFIRST, phase2 & 0xFF);
    pulse(FQ_UD1);
    pulse(FQ_UD2);
}


void dualAD9850::setfreq(double f1, uint8_t p1,double f2, uint8_t p2) {
    deltaphase1 = f1 * 4294967296.0 / calibFreq;
    phase1 = p1 << 3;
  deltaphase2 = f2 * 4294967296.0 / calibFreq;
  phase2 = p2 << 3;
    update();
}


void dualAD9850::down() {
    pulse(FQ_UD1);
  pulse(FQ_UD2);
    shiftOut(DATA1, W_CLK1, LSBFIRST, 0x04);
  shiftOut(DATA2, W_CLK2, LSBFIRST, 0x04);
    pulse(FQ_UD1);
  pulse(FQ_UD2);
}
    

void dualAD9850::up() {
    update();
}


void dualAD9850::calibrate(double TrimFreq)
{
    calibFreq = TrimFreq;
}


void dualAD9850::pulse(int pin) {
    digitalWrite(pin, HIGH);
    digitalWrite(pin, LOW);
}
