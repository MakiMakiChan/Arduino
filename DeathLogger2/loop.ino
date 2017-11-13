void loop() {
for (int i = 0; i < 100; i++) {
  lcd.setCursor(0,1);
  lcd.print(i);  
}
  if (changeGame == true) {
    //display current game
    lcd.clear();
    lcd.print(myGames[counter]);
    changeGame = false;
   
  }


  if (store == true) {
    //display current game
    lcd.clear();
    lcd.print(myGames[counter]);


    myFile = SD.open(logFile, FILE_WRITE);
    int test = myFile.println(myGames[counter] + ", " + getTime());
    if ((test > 0)) {
      //  Serial.println("Write successfull");
      lcd.setCursor(0, 1);
      lcd.print("All:OK");
    }
    else {
      //  Serial.println("Write unsuccessfull");
      lcd.setCursor(0, 1);
      lcd.print("All:fail");
    }
    myFile.close(); // close the file


    //Save to individual game file

    myFile = SD.open(myFiles[counter], FILE_WRITE);
    test = myFile.println(getTime());
    if ((test > 0)) {
      //  Serial.println("Write successfull");
      lcd.setCursor(9, 1);
      lcd.print("Game:OK");
    }
    else {
      //  Serial.println("Write unsuccessfull");
      lcd.setCursor(9, 1);
      lcd.print("Game:fail");
    }
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  store = false;
}

void writeToFile(String file, String data, int displayPosition) {
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
