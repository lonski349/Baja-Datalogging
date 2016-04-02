void setGyroScl (){
  
  //Settings for updating the accelerometer data not the gyro.
  byte address = 0x6B;
  byte reg = 0x23;
  byte value = 0x00;
  
  /*****************************************************************
  Values for the accelerometer:
  
  00000000    0x00    250 dps
  00000001    0x01    500 dps
  00010000    0x10    2000 dps
  00010001    0x11    2000 dps
  
  *****************************************************************/
  
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
  
  GyroScale = 0;
}
