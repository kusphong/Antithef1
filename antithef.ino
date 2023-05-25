#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int time1=0;
int _timeout;
String _buffer;
int buzzer = 7;
int led = 8;
int pir = 9;
String number = "+84828842251";
void setup() {
  delay(1000);                                                                                                                                                                                                                                                               
  Serial.begin(9600);
  sim.begin(9600);
  _buffer.reserve(50);
  lcd.init();
  lcd.backlight();
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(buzzer,OUTPUT);
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  lcd.setCursor(2, 1);
  lcd.print("TO WITH DOAN");
  runletter();
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   ANTI THEFT   ");
  lcd.setCursor(0, 1);
  lcd.print("Status:");
  Serial.println("<<Connected>>");
  delay(1000);
  }
  void loop() {
  if (digitalRead(9) == 0)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: ");
    lcd.setCursor(8, 1);
    lcd.print("NORMAL  ");
    Serial.println("normal");
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
  else
  {
//    if (Serial.available() > 0)
    lcd.setCursor(8, 1);
    lcd.print("WARNING ");
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    Serial.println("WARNING");
    Serial.println(number);
    Serial.println("send meggase");
    lcd.setCursor(0, 1);
    Serial.println("Calling to phone");
    //delay(20000);
    lcd.print("Call to phone");
    callNumberr();
    lcd.setCursor(0, 1);
    //delay(20000);
    lcd.print("Send message ");
    SendMessage();
//    while(1){
//    lcd.setCursor(0,1);
//    lcd.print("Call to phone2");
//    callNumberr1();
//    lcd.setCursor(0,1);
//    lcd.print("Send message2");
//    SendMessage();
    }
  }
//    if (sim.available() > 0)
//    Serial.write(sim.read());


    void SendMessage()
{
  Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "oi lang nuoc oi co trom";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();

}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
void callNumberr() {
  sim.println("AT");
  updateSerial();
  sim.println("ATD+ " + number + ';');
  updateSerial();
  Serial.println("calling");
  delay(20000); // wait for 20 seconds...
  sim.println("ATH");
  updateSerial();
}
void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    sim.write(Serial.read());
  }
  while (sim.available())
  {
    Serial.write(sim.read());
  }
  }
//  void callNumberr1() {
//  sim.println("AT");
//  updateSerial();
//  sim.println("ATD+ " + +84328843998 + ';');
//  updateSerial();
//  Serial.println("calling");
//  delay(20000); // wait for 20 seconds...
//  sim.println("ATH");
//  updateSerial();
//  }
//      void SendMessage1()
//{
//  Serial.println ("Sending Message");
//  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
//  delay(1000);
//  Serial.println ("Set SMS Number");
//  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
//  delay(1000);
//  String SMS = "WARNING";
//  sim.println(SMS);
//  delay(100);
//  sim.println((char)26);// ASCII code of CTRL+Z
//  delay(1000);
////  _buffer = _readSerial();
//
//}
  void runletter()
{
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
