#include <defs.h>
#include <arduinoFFT.h>
#include <types.h>

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */

#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC
unsigned int sampling_period_us;
unsigned long microseconds;

const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2
const double signalFrequency = 1000;
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;

/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
double vReal[samples];
double vImag[samples];

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void setup()
{
  Serial.begin(115200);
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop()
{
  /* Build raw data */
  Serial.println("Begin Data Collection");
  double cycles = (((samples-1) * signalFrequency) / samplingFrequency); //Number of signal cycles that the sampling will read
  for (uint16_t i = 0; i < samples; i++)
  {
    microseconds = micros();
    
    vReal[i] = analogRead(0);
    
    //vReal[i] = int8_t((amplitude * (sin((i * (twoPi * cycles)) / samples))) / 2.0);/* Build data with positive and negative values*/
    //vReal[i] = uint8_t((amplitude * (sin((i * (twoPi * cycles)) / samples) + 1.0)) / 2.0);/* Build data displaced on the Y axis to include only positive values*/
    vImag[i] = 0.0; //Imaginary part must be zeroed in case of looping to avoid wrong calculations and overflows
    
    while(micros() < (microseconds + sampling_period_us));
  }
  Serial.println("Begin FFT ");
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  Serial.println("FFT Finished, printing ");
  
  PrintVector(vReal, samples>>1, SCL_PLOT);
  
  double x = FFT.MajorPeak(vReal, samples, samplingFrequency);
  
  for(int i=0; i<(samples/2); i++)
  {
      /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
       
      //Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
      //Serial.print(" ");
      Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
  }
  
  Serial.println("Delay now for 2 seconds");
  delay(2000); /* Repeat after delay */
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
	      break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
        break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
	      break;
    }
    if(scaleType!=SCL_PLOT)
    {
      Serial.print(abscissa, 6);
      if(scaleType==SCL_FREQUENCY)
        Serial.print("Hz");
      Serial.print(" ");
    }
    Serial.println(vData[i], 4);
  }
  Serial.println();
}
