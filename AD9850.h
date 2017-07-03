/******************************************************************************************************************
 * Arduino library for AD9850
 * Created 23/08/2014
 * Christophe Caiveau f4goj@free.fr 
 *
 * this version modified by jodalyst 7/03/2017
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
 
 
#ifndef AD9850_H
#define AD9850_H
#include <Arduino.h>

class AD9850
{
	public:
  	AD9850();

	void begin(int w_clk, int fq_ud, int data, int reset);
	void setfreq(double f, uint8_t p);
	void down();
	void up();
	void calibrate(double TrimFreq);
	
	private:
	int W_CLK;
	int FQ_UD;
	int DATA;
	int RESET;
	uint32_t deltaphase;
	uint8_t phase;
	void update();
	void begin_priv();
	void pulse(int pin);
	double calibFreq;
};
class DualAD9850{
	public:
  	AD9850();

	void begin(int w_clka, int fq_uda, int dataa, int reseta,int w_clkb, int fq_udb, int datab, int resetb);
	void setfreq(double f, uint8_t p);
	void down();
	void up();
	void calibrate(double TrimFreq);
	
	private:
	int W_CLKA;
	int FQ_UDA;
	int DATAA;
	int RESETA;
	int W_CLKB;
	int FQ_UDB;
	int DATAB;
	int RESETB;
	uint32_t deltaphase;
	uint8_t phase;
	void update();
	void begin_priv();
	void pulse(int pin);
	double calibFreq;
	
	
}

class dualAD9850
{
    public:
  dualAD9850();

    void begin(int w_clk1, int fq_ud1, int data1, int reset1,int w_clk2, int fq_ud2, int data2, int reset2);
    void setfreq(double f1, uint8_t p1,double f2, uint8_t p2);
    void down();
    void up();
    void calibrate(double TrimFreq);
    
    private:
    int W_CLK1;
    int FQ_UD1;
    int DATA1;
    int RESET1;
  int W_CLK2;
  int FQ_UD2;
  int DATA2;
  int RESET2;
    uint32_t deltaphase1;
    uint8_t phase1;
  uint32_t deltaphase2;
  uint8_t phase2;
    void update();
    void begin_priv();
    void pulse(int pin);
    double calibFreq;
};

#endif
