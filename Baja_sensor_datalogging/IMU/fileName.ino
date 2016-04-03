/************************************************************************************
When the following function is called a new file with name DataX.csv will be created
where X is the number that is changing based on what files are already writen onto
the SD card in the arduino
************************************************************************************/

String newFileName (){
  String fileName = "Data";
  String fileEnd = ".csv ";
  int fileNum = 1;
  String fullName;
  char *fileNameArray;
  
  /*
  FIND A VALID FILE NAME
  Create a new file name and then check if the file name already exists
  if the name already exists then start to add numbers to the end of the 
  file name to make it different
  */
  
  fullName += fileName;
  fullName += fileEnd;
  fileNameArray = new char [fullName.length()];
  fullName.toCharArray(fileNameArray, fullName.length());
  
  if(SD.exists(fileNameArray)){
    fullName = fileName;
    fullName += fileNum;
    fullName += fileEnd;
    fileNameArray = new char [fullName.length()];
    fullName.toCharArray(fileNameArray, fullName.length());
    while(SD.exists(fileNameArray)){
      fileNum ++;
      fullName = fileName;
      fullName += fileNum;
      fullName += fileEnd;
      fullName.toCharArray(fileNameArray, fullName.length());
    }
  }
  
  //Open the file on the sd card with the name and set it up to be editing
  sensorData = SD.open(fileNameArray, FILE_WRITE);
  
  //Print our labels for our data as the first line 
  //sensorData.println("Time, Accelerometer X, Accelerometer Y, Accelerometer Z, Gyro X, Gyro Y, Gyro Z");
  sensorData.println("Time, Accelerometer X, Accelerometer Y, Accelerometer Z, Pitch, Roll");
  
  //Close the file. Not needed, used as a safety to prevent random data when switching the loops.
  sensorData.close();
  
  //Get the start time after all the initilization processed have been completed so we can have an accurate time for when
  //the data was collected
  startTime = millis();
  
  return fullName;
}
