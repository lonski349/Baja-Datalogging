//Kaelan Strones
//10/15/2015
//
//This program will take the sensor data from the adafruit 10 DOF sensor
//specifically the gyro and accelerometer data
//This data will then be saved into the SD card that is on the wifi shield of the arduino

//I am saving the data that I get to a .csv file for ease of importing into excel for evaluating, however the format of all the data going into the 
//file is as follows 
/*

time, title, title, title, title, title, title\n
data, data, data, data, data, data, data\n

*/
//Commas designate a new cells and the end line designates the end of the row.

//Libraries needed to read and write data to the SD card that is installed in the wifi shield on the arduino
#include <SPI.h>
#include <SD.h>

//Libraries needed to run the sensors
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_10DOF.h>

//Accelerometer
#include <Adafruit_LSM303_U.h>
//Gyro
#include <Adafruit_L3GD20_U.h>
//Bmp
#include <Adafruit_BMP085_U.h>


//Assign ID's to the sensors so we do not have to use the full name 
Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

unsigned long startTime;
File sensorData;
String fullName;
char *fileNameArray;

const int LED = 7;
const int SWLED = 8;
const int RECSW = 6;

int GyroScale = 0;
int ACCSCALE = 0;
double AccelX;
double AccelY;
double AccelZ;
  
float GyroX = 0;    //equals zero temporarily
float GyroY = 0;
//double GyroZ;

float AngleX;
float AngleY;

float prevTimeX = 0;
float nextTimeX = 0;
float prevTimeY = 0;
float nextTimeY = 0;

boolean nextSwitch = false;
boolean prevSwitch = false;

//Create a name for a sensor event
sensors_event_t accelerometers;
sensors_event_t gyros;
sensors_vec_t orientation;

void setup() {
  
  pinMode(LED, OUTPUT);
  pinMode(SWLED, OUTPUT);
  pinMode(RECSW, INPUT);
  
  digitalWrite(SWLED, HIGH);
  
  //Last resort diagnostics
  //These serial communications to the computer are a last resort becasue the arduino may
  //reset many times while connecting causing multiples of data to show in the data
 
  //Serial.begin(115200);
  //Serial.println("Booting");
  initSensors();
  digitalWrite(SWLED, LOW);
  delay(200);
  digitalWrite(SWLED, HIGH);
  delay(100);
  //Serial.println("Sensors Initilized");
  setAccScl();
  digitalWrite(SWLED, LOW);
  delay(200);
  digitalWrite(SWLED, HIGH);
  //Serial.println("Acc Scaled");
  //setGyroScl;
  
  //Begin the SD communications protocols. Failures here will tend to be when the sd card is disconnected or was not properly connected.
  if(!SD.begin(4)){
    while(true){
      fileReadFail();
    }
  }
  else{
    digitalWrite(SWLED, LOW);
    delay(200);
    digitalWrite(SWLED, HIGH);
  }
}

//Start the loop for logging the data after all initilization tasks are done
void loop() {
  
  prevSwitch = nextSwitch;
  nextSwitch = digitalRead(RECSW);

  //The following two lines gets a new accelerometer event(Refreashes the values)
  accel.getEvent(&accelerometers);
  
  AccelX = scaleAcc(accelerometers.acceleration.x);
  AccelY = scaleAcc(accelerometers.acceleration.y);
  AccelZ = scaleAcc(accelerometers.acceleration.z);
  
  if (dof.accelGetOrientation(&accelerometers, &orientation)){
    AngleX = orientation.pitch;
    AngleY = orientation.roll;
  }
  
  //GyroX = scaleGyro(gyros.gyro.x);
  //nextTimeX = millis();
  //GyroY = gyros.gyro.y * 50;
  //nextTimeY = millis();
  //GyroZ = gyros.gyro.z;    //Leaving out the z value as it seems useless for our applicaiton
  //Serial.println(GyroY);
  //AngleY = getAngle(prevTimeY, nextTimeY, GyroY, AngleY);
      
  //Serial.print(",Y: ");
  //Serial.println(AngleY);
  //Serial.println(nextTimeY - prevTimeY);
  
  //Serial.print(",Y: ");
  //Serial.println(AngleY);
  //Serial.print("Accel ");
  //Serial.print("X: ");
  //Serial.print(accelerometers.acceleration.x);
  //Serial.print(",Y: ");
  //Serial.print(accelerometers.acceleration.y);
  //Serial.print(",Z: ");
  //Serial.println(accelerometers.acceleration.z);
  
  //Serial.print("Gyro ");
  //Serial.print("X: ");
  //Serial.print(gyros.gyro.x);
  //Serial.print(",Y: ");
  //Serial.print(gyros.gyro.y);
  
  //Serial.println(digitalRead(RECSW));
  
  if(nextSwitch && !prevSwitch){
    
    fullName = newFileName();
    fileNameArray = new char [fullName.length()];
    fullName.toCharArray(fileNameArray, fullName.length());
    
    printData(AccelX, AccelY, AccelZ, GyroX, GyroY);
  }
  else if (nextSwitch && prevSwitch){ 
    printData(AccelX, AccelY, AccelZ, AngleX, AngleY);   
  }
  
  else{
    digitalWrite(LED, LOW);
    digitalWrite(SWLED, HIGH);
  }
}
