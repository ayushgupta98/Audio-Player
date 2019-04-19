#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int select = 0;
bool flag = false;
struct dataDecode {
  int _screen;
  String _timee = "";
  String _battery = "";
  String _songs[10] = {"","","","","","","","","",""};
  String _currentlyPlaying = "YEAH";
  String _duration = "2:32";
  String _isPlaying = "paused";
  int _cursorPosition = 1;
};

typedef struct dataDecode dac_type;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  Serial1.begin(4800);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //{ // Address 0x3C for 128x32
    //Serial.println(F("SSD1306 allocation failed"));
    ////for(;;); // Don't proceed, loop forever
  //}

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //display.display();
  //delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  struct dataDecode dac;

}

void listFace(struct dataDecode dac){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Player");
  display.setCursor(50, 0);
  display.print("2:15");
  display.setCursor(106, 0);
  display.print("42");
  display.print("%");
  display.setCursor(0, 0);
  display.drawLine(0, 12, display.width(), 12, WHITE);
  display.setCursor(3,18);
  display.print(dac._songs[dac._cursorPosition + 0]);
  display.setCursor(3,32);
  display.print(dac._songs[dac._cursorPosition + 1]);
  display.setCursor(3,45);
  display.print(dac._songs[dac._cursorPosition + 2]);
  display.drawRoundRect(0,15, 128, 15, 0, WHITE);
//  switch(dac._cursorPosition%3){
//    case 0:display.drawRoundRect(0,15, 128, 15, 0, WHITE);
//            break;
//    case 1:display.drawRoundRect(0,29, 128, 15, 0, WHITE);
//            break;
//    case 2:display.drawRoundRect(0,42, 128, 15, 0, WHITE);
//            break;
//  }
  display.display(); // Update screen with each newly-drawn line
  delay(1);
}

void playerFace(struct dataDecode dac){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Player");
  display.setCursor(50, 0);
  display.print("2:15");
  display.setCursor(106, 0);
  display.print("42");
  display.print("%");
  display.setCursor(0, 0);
  display.drawLine(0, 12, display.width(), 12, WHITE);
  display.setCursor(3,20);
  display.print(dac._currentlyPlaying);
  display.drawLine(0, 46, display.width(), 46, WHITE);
  display.setCursor(2,50);
  if(dac._isPlaying == "playing"){
    display.print("Playing  ");
  }else if(dac._isPlaying == "paused"){
    display.print("Paused  ");
  }
  display.drawLine(48, 46, 48, 64, WHITE);
  display.setCursor(51 ,51);
  display.print("Length: ");
  display.print(dac._duration);
  display.drawLine(0, 63, display.width(), 63, WHITE);
  display.drawLine(0, 46, 0, 64, WHITE);
  display.drawLine(127, 46, 127, 64, WHITE);
  display.display(); // Update screen with each newly-drawn line
  delay(1);
}

dac_type stringToStrct(String s){
    dac_type dac;
    String readStringFromUART = s;
    //String readStringFromUART = "screen:1;time:2:15;battery:42;s1,s2,s3,s4,s5;currentlyplaying:s2;duration:4:15;playing:paused;cursorpos:1;"; //s;
    //Serial.println(readStringFromUART);
    
    int ind1 = readStringFromUART.indexOf(';');  //finds location of first ,
    String screen = readStringFromUART.substring(0, ind1);   //captures first data String

    int ind2 = readStringFromUART.indexOf(';', ind1 + 1); //finds location of second ,
    String timee = readStringFromUART.substring(ind1 + 1, ind2 + 1); //captures second data String

    int ind3 = readStringFromUART.indexOf(';', ind2 + 1); //finds location of first ,
    String battery = readStringFromUART.substring(ind2 + 1, ind3 + 1); //captures first data String

    int ind4 = readStringFromUART.indexOf(';', ind3 + 1); //finds location of second ,
    String song = readStringFromUART.substring(ind3 + 1, ind4 + 1); //captures second data String

    int ind5 = readStringFromUART.indexOf(';', ind4 + 1); //finds location of first ,
    String currentlyPlaying = readStringFromUART.substring(ind4 + 1, ind5 + 1); //captures first data String

    int ind6 = readStringFromUART.indexOf(';', ind5 + 1); //finds location of second ,
    String duration = readStringFromUART.substring(ind5 + 1, ind6 + 1); //captures second data String

    int ind7 = readStringFromUART.indexOf(';', ind6 + 1); //finds location of second ,
    String pausPlay = readStringFromUART.substring(ind6 + 1, ind7 + 1); //captures second data String

    int ind8 = readStringFromUART.indexOf(';', ind7 + 1); //finds location of second ,
    String cursorPos = readStringFromUART.substring(ind7 + 1, ind8 + 1); //captures second data String
    
    dac._timee = timee.substring(5, 9);
    dac._battery = battery.substring(8, 10);
    dac._screen = screen.charAt(8) - 48;
    
    currentlyPlaying = currentlyPlaying.substring(17);
    currentlyPlaying.remove(currentlyPlaying.length()-1,1);
    dac._currentlyPlaying = currentlyPlaying;
    
    dac._duration = duration.substring(9, 13);
    dac._isPlaying = pausPlay.substring(8, pausPlay.length()-1);
    dac._cursorPosition = cursorPos.charAt(10) - 48;
    
    ind1 = song.indexOf(',');  //finds location of first ,
    String songOne = song.substring(0, ind1);   //captures first data String

    ind2 = song.indexOf(',', ind1 + 1); //finds location of second ,
    String songTwo = song.substring(ind1 + 1, ind2 + 1); //captures second data String
    int s1 = songTwo.length();
    songTwo.remove(s1 - 1, 1);

    ind3 = song.indexOf(',', ind2 + 1); //finds location of first ,
    String songThree = song.substring(ind2 + 1, ind3 + 1); //captures first data String
    int s2 = songThree.length();
    songThree.remove(s2 - 1, 1);

    ind4 = song.indexOf(',', ind3 + 1); //finds location of second ,
    String songFour = song.substring(ind3 + 1, ind4 + 1); //captures second data String
    int s3 = songFour.length();
    songFour.remove(s3 - 1, 1);

    ind5 = song.indexOf(';', ind4 + 1); //finds location of first ,
    String songFive = song.substring(ind4 + 1, ind5 + 1); //captures first data String
    int s4 = songFive.length();
    songFive.remove(s4 - 1, 1);

    dac._songs[0] = songOne;
    dac._songs[1] = songTwo;
    dac._songs[2] = songThree;
    dac._songs[3] = songFour;
    dac._songs[4] = songFive;
    return dac;
  
  } 




void loop() {
  // put your main code here, to run repeatedly:
  
  dac_type d;
  //#if ENABLE_READUART
  if(Serial.available()>0) {
    Serial.flush();  
    //String s ="screen:1;time:2:15;battery:42;a.wav,b.wav,c.wav,d.wav,e.wav;currentlyplaying:s2;duration:4:15;playing:paused;cursorpos:3;";
    String s = Serial.readStringUntil('#');
    //Serial.println(s);
  
    d = stringToStrct(s);
    Serial.print("Screen : ");
    Serial.print(d._screen);
    Serial.print(" Time : ");
    Serial.print(d._timee);
    Serial.print(" Battery : ");
    Serial.print(d._battery);
    Serial.print(" Song 0 : ");
    Serial.print(d._songs[0]);
    Serial.print(" Song 1 : ");
    Serial.print(d._songs[1]);
    Serial.print(" Song 2 : ");
    Serial.print(d._songs[2]);
    Serial.print(" Song 3 : ");
    Serial.print(d._songs[3]);
    Serial.print(" Song 4 : ");
    Serial.print(d._songs[4]);
    Serial.print(" Currently Playing : ");
    Serial.print(d._currentlyPlaying);
    Serial.print(" Duration : ");
    Serial.print(d._duration);
    Serial.print(" Is playing : ");
    Serial.print(d._isPlaying);
    Serial.print(" cursor Pos : ");
    Serial.println(d._cursorPosition);
  
//  if(flag){
    if(!d._screen)
      playerFace(d);
    //delay(2000);
//    flag = false;
//    select = -1;
//  }
    else 
      listFace(d);
//  }
//  
//  delay(1000);
//
//  select += 1;
//  if(select == 3) {
//    select = 0;
//    flag = true;
//  }
//}

  Serial.flush();
//delay(500);
  }
 }
