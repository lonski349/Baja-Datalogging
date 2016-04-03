/*
PRINT DATA
This function goes through the process of printing all of the data from the 
sensors onto the CSV sheet that was created
*/

void printData (double AccX, double AccY, double AccZ, double AngX, double AngY){
  
  //Open the data file and make it editable. editing location begins at the last line in the file
  sensorData = SD.open(fileNameArray, FILE_WRITE);
      
  //Loop to check that the file is open and set a LED to high to show that the data is being recorded to the drive
  if (sensorData){
    //Last resort diagnostics
    //Serial.println("File open");
    digitalWrite(BOARDLED, HIGH);
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
    sensorData.print(AngX);
    sensorData.print(",");
    sensorData.println(AngY);
    //sensorData.print(",");
    //The last value entered needs a println to end that line to begin the new line
    //sensorData.println(GyroZ);
  
    sensorData.close();
  }
  
  /*
  FILE OPEN FAILURE
  If the file that was specified fails to open then flash the LED's quickly to let the user know that 
  the file that is being used may be corrupted
  */
  
  else {
        //Last resort diagnostics
        //Serial.println("File open fail");
        digitalWrite(BOARDLED, LOW);
        digitalWrite(SWLED, HIGH);
        delay(50);
        digitalWrite(BOARDLED, HIGH);
        digitalWrite(SWLED, LOW);
        delay(50);
        digitalWrite(BOARDLED, LOW);
        digitalWrite(SWLED, HIGH);
      }
}
