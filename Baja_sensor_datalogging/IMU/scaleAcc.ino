/*
SCALE ACCELEROMETERS
Based on a constant value that can only be set in the program set the scaler value for 
the accelerometers so that the values writen to the spreadsheet are a value that makes 
sense to us. 
*/

double scaleAcc (double acc) {
  
  switch (ACCSCALE) {
    case 0:
      acc = acc;
      break;
    case 1:
      acc = acc * 2;
      break;
    case 2:
      acc = acc * 4;
      break;
    case 3:
      acc = acc * 12;
      break;
    default:
      acc = acc;
      break;
  }
  
  return acc;
}
