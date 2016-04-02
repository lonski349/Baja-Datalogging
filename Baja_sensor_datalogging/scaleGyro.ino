double scaleGyro (double gyro) {
  
  switch (GyroScale){
    case 0:
      gyro = gyro * 50.0;
      break;
    case 1:
      gyro = gyro * 2;
      break;
    case 2:
      gyro = gyro * 4;
      break;
    case 3:
      gyro = gyro * 4;
      break;
    default:
      gyro = gyro;
      break;
    
  return gyro;
  }
}
