#include <Wire.h>

#define SLAVE_ADDR 0x10

uint8_t sensor_val_table[4]; // initially i assume we have 4 sensor each of which has 1 byte value. In the case that sensor's values occupies more than 1 byte then divide 2 or more btyes into 1 bytes arrays.   
uint8_t recieved_Dat;
bool flag = false;
void setup() 
{
  Wire.begin(SLAVE_ADDR);       // join i2c bus with address SLAVE_ADDR
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
}

void loop() 
{
  // Following values are hard coded. They should be replaced after reading sensor data
  // It is written here just only to show that we can pass those values on RasberryPi
  if(flag)
  {
  sensor_val_table[0]=0; // ie. sensor_val_table[0]=read_sensor1();
  sensor_val_tablele[1]=0;
  sensor_val_table[2]=0;
  sensor_val_table[3]=0;
  flag= false;
  }
  
}


// IMPORTANT NOTICE
// The second parameter of write() function take int value. It should be the same size with sensor_val_table's size. Then we pass all values at a time one by one.
void requestEvent()
{
  Wire.write(Buffer,4);  
}

// callback for received event
void receiveEvent(int byteCount)
{
  while(Wire.available()) 
  {
    number = Wire.read();
    Serial.print(“data received: “);
    Serial.println(number);
    //following alg. represent FSM(Very basic Finite State Machine / Moore Implementation )
    if (number == 1) 
    {
      flag = true; // initiate reading op.
    }
    else
    {
      flag = false; // close reading op. 
    }
  }
}
