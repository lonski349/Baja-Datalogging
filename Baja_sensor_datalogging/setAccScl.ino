void setAccScl (){
  byte address = 0b0011001;
  byte reg = 0x23;
  byte value = 0x30;
  
  /*****************************************************************
  Values for the accelerometer:
  
  00000000    0x00    +-2G
  00001000    0x08    Hires +-2G
  00010000    0x10    +-4G
  00011000    0x18    Hires +-4G
  00110000    0x20    +-8G
  00111000    0x28    Hires +-8G
  00100000    0x30    +-16G
  00101000    0x38    Hires +-16G
  
  *****************************************************************/
  
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
  
  /*****************************************************************
  Be sure to change this lower value so that the arduino prints the
  correct data to the SD card using the proper scaler.
  *****************************************************************/
  ACCSCALE = 3;
}
