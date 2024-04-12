#include "arduinoFFT.h"

#define SAMPLES 128         //Must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC

unsigned int sampling_period;
unsigned long microseconds;

arduinoFFT FFT = arduinoFFT();

double vReal[SAMPLES];
double vImag[SAMPLES];

//DELs
int tuned_green = 6;
int higher_yellow = 7;
int lower_yellow = 5;
int higher_red = 8;
int lower_red = 4;

int g_string = 0;
int c_string = 1;
int e_string = 2;
int a_string = 3;

//bouttons
int g_button = 9;
int c_button = 10;
int e_button = 11;
int a_button = 12;

//microphone
int micro=A0;

void setup() {
  //DELs 
    pinMode(tuned_green, OUTPUT);
    pinMode(higher_yellow, OUTPUT);
    pinMode(lower_yellow, OUTPUT);
    pinMode(higher_red, OUTPUT);
    pinMode(lower_red, OUTPUT);
    
    pinMode(g_string, OUTPUT);
    pinMode(c_string, OUTPUT);
    pinMode(e_string, OUTPUT);
    pinMode(a_string, OUTPUT);
    
    //bouttons
    pinMode(g_button, INPUT);
    pinMode(c_button, INPUT);
    pinMode(e_button, INPUT);
    pinMode(a_button, INPUT);
    
    //microphone
    pinMode(micro, INPUT);
    
    Serial.begin(9600);
    sampling_period = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop() {
    int g_tunning = digitalRead(g_button);
    int c_tunning = digitalRead(c_button);
    int e_tunning = digitalRead(e_button);
    int a_tunning = digitalRead(a_button);
    
    frequence = FindDominantFrequency();
    
    //si le boutton pour accorder la corde G est appuyee
    if (g_tunning == HIGH) {
      
      digitalWrite(g_string, HIGH);
      
      if (frequence >= 387 && frequence <= 397) {
        digitalWrite(tuned_green, HIGH);
      } 
      else if (frequence >= 382 && frequence <= 386) {
        digitalWrite(lower_yellow, HIGH);
      } 
      else if (frequence >= 398 && frequence <= 402) {
        digitalWrite(higher_yellow, HIGH);
      }
      else if (frequence < 382) {
        digitalWrite(lower_red, HIGH);
      }
      else if (frequence > 403) {
        digitalWrite(higher_red, HIGH);
      }
    }
    
    
    //si le boutton pour accorder la corde C est appuyee
    else if (c_tunning == HIGH) {
       
      digitalWrite(c_string, HIGH);
      
      if (frequence >= 258 && frequence <= 267) {
        digitalWrite(tuned_green, HIGH);
      } 
      else if (frequence >= 252 && frequence <= 257) {
        digitalWrite(lower_yellow, HIGH);
      } 
      else if (frequence >= 268 && frequence <= 272) {
        digitalWrite(higher_yellow, HIGH);
      }
      else if (frequence < 252) {
        digitalWrite(lower_red, HIGH);
      }
      else if (frequence > 272) {
        digitalWrite(higher_red, HIGH);
    }
    
    
    //si le boutton pour accorder la corde E est appuyee
    else if (e_tunning == HIGH) {
       
      digitalWrite(e_string, HIGH);
      
      if (frequence >= 325 && frequence <= 335) {
        digitalWrite(tuned_green, HIGH);
      } 
      else if (frequence >= 320 && frequence <= 324) {
        digitalWrite(lower_yellow, HIGH);
      } 
      else if (frequence >= 336 && frequence <= 340) {
        digitalWrite(higher_yellow, HIGH);
      }
      else if (frequence < 320) {
        digitalWrite(lower_red, HIGH);
      }
      else if (frequence > 340) {
        digitalWrite(higher_red, HIGH);
    }
    
    
    //si le boutton pour accorder la corde A est appuyee
    else if (a_tunning == HIGH) {
      
      digitalWrite(a_string, HIGH);
      
      if (frequence >= 335 && frequence <= 345) {
        digitalWrite(tuned_green, HIGH);
      } 
      else if (frequence >= 330 && frequence <= 334) {
        digitalWrite(lower_yellow, HIGH);
      } 
      else if (frequence >= 346 && frequence <= 350) {
        digitalWrite(higher_yellow, HIGH);
      }
      else if (frequence < 330) {
        digitalWrite(lower_red, HIGH);
      }
      else if (frequence > 350) {
        digitalWrite(higher_red, HIGH);
    }
    
    
    //si aucun boutton est appuye
    else{
      
      //toutes les DELs sont eteintes si les bouttons ne sont pas appuyes
      //DELs pour accorder
      digitalWrite(tuned_green, LOW);
      digitalWrite(higher_yellow, LOW);
      digitalWrite(lower_yellow, LOW);
      digitalWrite(higher_red, LOW);
      digitalWrite(lower_red, LOW);
      
      //DELs pour identifier quelle corde on accorde
      digitalWrite(g_string, LOW);
      digitalWrite(c_string, LOW);
      digitalWrite(e_string, LOW);
      digitalWrite(a_string, LOW);
      
    }
  }  
    
  double FindDominantFrequency(){
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
        vReal[i] = analogRead(2);
        vImag[i] = 0;
        while(micros() < (microseconds + sampling_period_us));
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    Serial.println(peak); //Print out what frequency is the most dominant.

    peak = peak * 0.990;
    return peak;
}




