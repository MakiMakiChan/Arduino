/*void writeToFile(String file, String data, int displayPosition){
    myFile = SD.open(file, FILE_WRITE);
    int test = myFile.println(data);
    if ((test > 0)) {
    //  Serial.println("Write successfull");
      lcd.setCursor(displayPosition, 1);
      lcd.print("All:OK");
    }
    else {
    //  Serial.println("Write unsuccessfull");
      lcd.setCursor(0, 1);
      lcd.print("Save failed");
    }
    myFile.close(); // close the file
}
*/
String getTime() {
  String dTime = rtc.getDateStr() +String(", ") + rtc.getTimeStr();
  return dTime;
}
int readDeath(int game) {
 // re-open the file for reading:
  myFile = SD.open(myFiles[game]);
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

