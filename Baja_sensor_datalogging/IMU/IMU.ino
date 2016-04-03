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

const int BOARDLED = 7;
const int SWLED = 8;
const int RECSW = 6;

int ACCSCALE = 0;
double AccelX;
double AccelY;
double AccelZ;

float AngleX;
float AngleY;

boolean nextSwitch = false;
boolean prevSwitch = false;

//Create a name for a sensor event
sensors_event_t accelerometers;
sensors_vec_t orientation;

void setup() {
  
  pinMode(BOARDLED, OUTPUT);
  pinMode(SWLED, OUTPUT);
  pinMode(RECSW, INPUT);
  
  digitalWrite(SWLED, HIGH);
  
  /*
  DIAGNOSTICS
  These serial communications to the computer are a last resort becasue the arduino may
  reset many times while connecting causing multiples of data to show in the file system
  Also utilizing the USB connection requires us to open the sealed box. 
  */
 
  //Serial.begin(115200);
  //Serial.println("Booting");
  initSensors();
  /*
  Flash the LED's for the initilization success
  */
  digitalWrite(SWLED, LOW);
  digitalWrite(BOARDLED, HIGH);
  delay(200);
  digitalWrite(SWLED, HIGH);
  digitalWrite(BOARDLED, LOW);
  delay(100);
  //Serial.println("Sensors Initilized");
  setAccScl();
  /*
  Flash the LED's for scale setting success
  */
  digitalWrite(SWLED, LOW);
  digitalWrite(BOARDLED, HIGH);
  delay(200);
  digitalWrite(SWLED, HIGH);
  digitalWrite(BOARDLED, LOW);
  //Serial.println("Acc Scaled");
  
  //Begin the SD communications protocols. Failures here will tend to be when the sd card is disconnected or was not properly connected.
  if(!SD.begin(4)){
    while(true){
      /*
      Flash the LED's in a specific pattern if the SD card read fails
      */
      fileReadFail();
    }
  }
  else{
    /*
    Flash the LED's for sucessful SD card read
    */
    digitalWrite(SWLED, LOW);
    digitalWrite(BOARDLED, HIGH);
    delay(200);
    digitalWrite(SWLED, HIGH);
    digitalWrite(BOARDLED, LOW);
  }
}

//Start the loop for logging the data after all initilization tasks are done
void loop() {
  
  /*
  GET SWITCH VAL
  Sets the new switch vlaue to give us information when the switch has changed and when we need to
  make a new file
  */
  prevSwitch = nextSwitch;
  nextSwitch = digitalRead(RECSW);

  
  accel.getEvent(&accelerometers); //Get a new accelerometer event(Refreashes the values)
  
  /*
  ACCELEROMETER SCALING
  The scaling function for this is in a seperate file titled scaleAcc
  */
  
  AccelX = scaleAcc(accelerometers.acceleration.x);
  AccelY = scaleAcc(accelerometers.acceleration.y);
  AccelZ = scaleAcc(accelerometers.acceleration.z);
  
  /*
  GET ANGLES
  Utilize the orientation library from the Adafruit 10DOF sensor to get the current angle 
  of the device and in this situation the car. 
  Roll is the side to side angle of the car 
  Pitch is the front to back angle of the car
  */
  if (dof.accelGetOrientation(&accelerometers, &orientation)){
    AngleX = orientation.pitch;
    AngleY = orientation.roll;
  }
  
  /*
  DIAGNOSTICS
  Use these diagnostics as a last resort to solving a problem because this will
  require the sealed box to be opened.
  */
  
  //Serial.println(nextTimeY - prevTimeY);
  
  //Serial.print(",Y: ");
  //Serial.println(AngleY);
  //Serial.print(",X: ");
  //Serial.println(AngleX);
  //Serial.print("Accel ");
  //Serial.print("X: ");
  //Serial.print(accelerometers.acceleration.x);
  //Serial.print(",Y: ");
  //Serial.print(accelerometers.acceleration.y);
  //Serial.print(",Z: ");
  //Serial.println(accelerometers.acceleration.z);
  
  //Serial.println(digitalRead(RECSW));
  
  /*
  SWITCH CHECKING
  */
  
  if(nextSwitch && !prevSwitch){
    /*
    Create a new file because the switch has just changed positions 
    */
    fullName = newFileName();
    fileNameArray = new char [fullName.length()];
    fullName.toCharArray(fileNameArray, fullName.length());
    
    printData(AccelX, AccelY, AccelZ, AngleX, AngleY);
  }
  else if (nextSwitch && prevSwitch){ 
    /*
    The switch has not changed positions so keep writing data to the same place
    */
    printData(AccelX, AccelY, AccelZ, AngleX, AngleY);   
  }
  
  else{
    /*
    Flash the LED's to show the user that there is power and the device is waiting
    for input from the user, E.G when the device is not recording data
    */
    
    digitalWrite(BOARDLED, LOW);
    digitalWrite(SWLED, HIGH);
    delay(300);
    digitalWrite(BOARDLED, HIGH);
    digitalWrite(SWLED, LOW);
    delay(100);
    digitalWrite(BOARDLED, LOW);
    digitalWrite(SWLED, HIGH);
  }
}
