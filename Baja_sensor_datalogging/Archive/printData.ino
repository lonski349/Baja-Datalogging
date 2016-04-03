void printData (double AccX, double AccY, double AccZ, double GyX, double GyY){
  
  //Open the data file and make it editable. editing location begins at the last line in the file
  sensorData = SD.open(fileNameArray, FILE_WRITE);
      
  //Loop to check that the file is open and set a LED to high to show that the data is being recorded to the drive
  if (sensorData){
    //Last resort diagnostics
    //Serial.println("File open");
    digitalWrite(LED, HIGH);
    digitalWrite(SWLED, LOW);
    
    //Print the data that will go onto the chart, commas must be placed in between each item because it is a .csv file type
    sensorData.print(millis() - startTime);
    sensorData.print(",");
    sensorData.print(AccX);
    sensorData.print(",");
    sensorData.print(AccY);
    sensorData.print(",");
    sensorData.print(AccZ);
    sensorData.print(",");
    sensorData.print(GyX);
    sensorData.print(",");
    sensorData.println(GyY);
    //sensorData.print(",");
    //The last value entered needs a println to end that line to begin the new line
    //sensorData.println(GyroZ);
  
    sensorData.close();
  }
  
  //Keep the light off if the file is not opened, if the file was not opened 
  //E.G. the card was connected after the program started, it will most likly not connect 
  //If it does it will be missing the data writen to the file during initilization
  else {
        //Last resort diagnostics
        //Serial.println("File open fail");
        digitalWrite(LED, LOW);
        digitalWrite(SWLED, HIGH);
        delay(50);
        digitalWrite(LED, HIGH);
        digitalWrite(SWLED, LOW);
        delay(50);
        digitalWrite(LED, LOW);
        digitalWrite(SWLED, HIGH);
      }
}
