#include "timer.h"
#include "serial_read_write.h"
#include "circular_buffer.h"
#define Vibration_sen A0 
float value; 
char*  p_Working_Freq = (char*)& _Working_Freq; 
uint16_t numberCycle;
char*  p_numberCycle = (char*)&numberCycle; 
float threshold = 4500; 
char*  p_threshold = (char*)&threshold; 
void setup() {
 cli();
  // put your setup code here, to run once:
  onBaseTimer();
pinMode (A0, INPUT); 
Serial.begin(115200);
  sei();

}

void loop() {
  // put your main code here, to run repeatedly:
 if (F_Working_Cycle)
  {
      F_Working_Cycle = false;
      value = mapFloat(analogRead(A0),0,1023,0,5000); // chan A0 0 -> 1023;
      send_num_float(value, "co");    
      send_num_float(threshold, "ct");
      FIFOBufferWrite(value);
      count++;
      Serial.println(count);
      for (int j = 0; j < ARRAY_SIZE; j++) {
      Serial.println(gBuffer[j]);
      }
      if (value >= threshold){
      Serial.println("Da vuot qua gia tri cho phep tien hanh thu thap du lieu");
      d = 0; 
      fistCircularBufferHalf();
      Serial.println(d);
      secondCircularBufferHalf();
      for (int i = 0 ; i < ARRAY_SIZE; i++){
      send_num_float(gBuffer[i], "ci");
      }
      }
}
if (Serial.available() >= 7)
  {
    switch (Serial.read())
    {
      case 'P':
      {
        switch (Serial.read())
        {
          case 'S':
          {
            Serial.readBytes(read_buffer, 2); 
            if (Serial.read() == ';')
            {
              *p_numberCycle = (char)read_buffer[1];
              *(p_numberCycle + 1) = (char)read_buffer[0];
            } 
            break;
          }
          case 'P':
          {
            Serial.readBytes(read_buffer, 4); 
            if (Serial.read() == ';')
            {              
              *p_threshold = (char)read_buffer[3];
              *(p_threshold + 1) = (char)read_buffer[2];
              *(p_threshold + 2) = (char)read_buffer[1];
              *(p_threshold + 3) = (char)read_buffer[0];
            }        
            break;
          }
        }
        break;
      }
      case 'S':
      {
        if (Serial.read() == 'P')
          Serial.readBytes(read_buffer, 4); 
        if (Serial.read() == ';')
        {
          *p_Working_Freq = (char)read_buffer[3];
          *(p_Working_Freq + 1) = (char)read_buffer[2];
          *(p_Working_Freq + 2) = (char)read_buffer[1];
          *(p_Working_Freq + 3) = (char)read_buffer[0];
        } 
        break;
      }
    }
  }
}
float mapFloat(float x, float x_min, float x_max, float y_min, float y_max)
{
  float y;
  y = y_min + (x - x_min)/(x_max - x_min)*(y_max - y_min);// (x - x_min)/(x_max - x_min) = (y - y_min)/(y_max - y_min)
  y = (y>y_max)?y_max:((y<y_min)?y_min:y);
  return y;
}
