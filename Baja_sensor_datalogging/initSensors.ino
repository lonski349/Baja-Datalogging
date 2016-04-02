//Sensor initilization function 
void initSensors(){
  Serial.println("Initilizing");
  accel.begin();
  Serial.println("Accel done");
  gyro.begin();
  Serial.println("Gyro done");
}
