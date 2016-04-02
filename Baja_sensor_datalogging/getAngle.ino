float getAngle (float startTime, float endTime, float angularRate, float currentAngle){
  float timeScale = endTime - startTime;
  float newAngle;
  float rotationrateLim = 0.5;
  
  Serial.println(currentAngle);
  
  if (angularRate >= rotationrateLim || angularRate <= -rotationrateLim){
    //Calculate new Angle
    timeScale = timeScale / 1000;
    newAngle = (currentAngle + (angularRate * timeScale));
    //Serial.println(newAngle, 6);
  }
  else {
    //Return the previous angle because there would be a divide by zero for start time and end time equaling 0
    newAngle = currentAngle;
  }
  
  return newAngle;
}
