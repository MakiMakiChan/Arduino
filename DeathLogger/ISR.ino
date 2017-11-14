//ISR
void gameDown (){
  counter --;
  changeGame = true;
 if (counter < 0) counter = myFilesLength-1;
}
void gameUp () {
   counter++;
   changeGame = true;
   counter = counter % myFilesLength;
  }
void save () {
  store = true;
}
