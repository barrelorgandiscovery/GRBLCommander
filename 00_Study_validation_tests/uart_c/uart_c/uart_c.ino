

HardwareSerial s = HardwareSerial(1); // UART 1


void setup() {

  Serial.begin(115200);

  pinMode (25, FUNCTION_4); // U1RXD 
  pinMode (26, FUNCTION_4); // U1TXD

  s.begin(115200,SERIAL_8N1,25,26);

  delay(2000);
  // s.write("$H\n");


}

int deplacementX = 100;

void loop() {

  s.write("?\n");
  delay(1000);

  String st = String("G90 X") + deplacementX + String(".0 Y50.0 \n");
  Serial.println(st);
  deplacementX -= 1;
  s.println(st);
  
  String sRead = s.readString();
  while (sRead != "") {
  Serial.println(sRead);
  sRead = s.readString();
  }

}
