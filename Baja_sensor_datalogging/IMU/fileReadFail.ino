/*
FILE READ FAIL SEQUENCE
If the system fails to initilize the SD Card then run through this sequence of flashes 
to inform the user that the card was not read
*/

void fileReadFail (){
  digitalWrite(SWLED, LOW);
  digitalWrite(BOARDLED, HIGH);
  delay(300);
  digitalWrite(SWLED, HIGH);
  digitalWrite(BOARDLED, LOW);
  delay(100);
  digitalWrite(SWLED, LOW);
  digitalWrite(BOARDLED, HIGH);
  delay(100);
  digitalWrite(SWLED, HIGH);
  digitalWrite(BOARDLED, LOW);
  delay(100);
  digitalWrite(SWLED, LOW);
  digitalWrite(BOARDLED, HIGH);
  delay(100);
  digitalWrite(SWLED, HIGH);
  digitalWrite(BOARDLED, LOW);
  delay(100);
}
