/*
SENSOR INITILIZATION
Runs through the process of initilizing all of the sensors one by one 
*/

void initSensors(){
  //Serial.println("Initilizing");
  accel.begin();
  //Serial.println("Accel done");
  gyro.begin();
  //Serial.println("Gyro done");
}
