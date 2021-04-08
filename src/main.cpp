//---------------------------------             librerias

#include <Arduino.h>
#include <URTouch.h>
#include <UTFT.h>
#include <Separador.h>
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define LedPin 13
#define vSensor 8
//---------------------------------              Creating Objects

UTFT myGLCD(SSD1963_800ALT, 38, 39, 40, 41); // Objeto LCD

URTouch myTouch(6, 5, 4, 3, 2); // Objeto Touch

const byte pindato = 9;
OneWire oneWireObjeto(pindato);
DallasTemperature sensorDS18B20(&oneWireObjeto);

//-----------------------------------        Defining Variables
const int chipSelect = 53; // para el arduino mega
Separador splt;

String incomingString;

String st;

int kb;

String temp;

unsigned long ultTrans = 0;
unsigned long lastTrans = 0;

const int interval = 1000;
const int intervalo = 200;


int ref = 0;
int ref2 = 0;

byte pg;
byte wpg;
int x, y;
String reboton1 = "OFF";
String reboton2 = "OFF";
//
//------IMAGES--------

extern unsigned int BDWAT[];

//------FONTS

extern uint8_t Arial_round_16x24[];
extern uint8_t SevenSegmentFull[];
extern uint8_t OCR_A_Extended_M[];
extern uint8_t Various_Symbols_32x32[];
//

struct boton
{
  int estado = 0;
};

typedef struct boton Val;

Val vlv;

/* ------------------------------------------------- FUNCIONES -------------------------------------------------------------*/
//----Barra de tareas----

void taskBar()
{
  myGLCD.fillScr(182, 153, 119); // fondo

  myGLCD.setColor(50, 121, 192);
  myGLCD.fillRect(0, 0, 799, 58);
  myGLCD.setColor(30, 101, 172);
  myGLCD.drawLine(0, 59, 799, 59);
  myGLCD.drawLine(0, 60, 799, 60);
  myGLCD.setColor(50, 121, 192);
  myGLCD.drawBitmap(300, 0, 200, 58, BDWAT);
  myGLCD.drawRect(300, 0, 500, 58);
  myGLCD.drawRect(301, 0, 499, 58);
}

//
void drawHomeScreen()
{

  pg = 0;
  myGLCD.setDisplayPage(pg);

  for (wpg = 0; wpg <= 4; wpg++)
  {
    myGLCD.setWritePage(wpg);

    switch (wpg)
    {
    case 0:

      taskBar();
      break;

    case 1:
      //
      //----BLOQUE A----

      myGLCD.setColor(126, 115, 112);

      myGLCD.drawRect(1, 62, 399, 269);
      myGLCD.drawRect(2, 63, 398, 268);
      myGLCD.setColor(212, 183, 149);
      myGLCD.fillRect(3, 64, 397, 267);
      myGLCD.setFont(Various_Symbols_32x32);
      myGLCD.setColor(126, 115, 112);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("1", 360, 230);
      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("Nogal", 130, 80);

      myGLCD.setColor(212, 183, 149);

      break;

    case 2:
      //
      //----BLOQUE B----
      //

      myGLCD.setColor(126, 115, 112);

      myGLCD.drawRect(401, 62, 798, 269);
      myGLCD.drawRect(402, 63, 797, 268);
      myGLCD.setColor(212, 183, 149);
      myGLCD.fillRect(403, 64, 796, 267);
      myGLCD.setFont(Various_Symbols_32x32);
      myGLCD.setColor(126, 115, 112);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("2", 410, 230);
      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("Uva", 530, 80);

      break;

    case 3:

      //
      //----BLOQUE C----
      //

      myGLCD.setColor(126, 115, 112);

      myGLCD.drawRect(1, 271, 399, 478);
      myGLCD.drawRect(2, 272, 398, 477);
      myGLCD.setColor(212, 183, 149);
      myGLCD.fillRect(3, 273, 397, 476);

      myGLCD.setFont(Various_Symbols_32x32);
      myGLCD.setColor(126, 115, 112);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("3", 360, 280);
      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("Naranjo", 130, 285);
      break;

    case 4:

      //
      //---- BLOQUE D
      //

      myGLCD.setColor(126, 115, 112);

      myGLCD.drawRect(401, 271, 798, 478);
      myGLCD.drawRect(402, 272, 797, 477);
      myGLCD.setColor(212, 183, 149);
      myGLCD.fillRect(403, 273, 796, 476);

      myGLCD.setFont(Various_Symbols_32x32);
      myGLCD.setColor(126, 115, 112);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("4", 410, 280);
      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("Sandia", 530, 285);
      break;
    }
  }
}

void nodeWindow()
{
  pg = 1;
  myGLCD.setDisplayPage(pg);

  int mx = myGLCD.getDisplayXSize();
  int my = myGLCD.getDisplayYSize();

  for (wpg = 0; wpg <= 4; wpg++)
  {
    myGLCD.setWritePage(wpg);
    switch (wpg)
    {
    case 0:

      taskBar();
      myGLCD.setColor(0, 71, 142);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.setFont(Various_Symbols_32x32);
      myGLCD.print("?", 13, 13);
      myGLCD.drawLine(70, 0, 70, 60);
      myGLCD.drawLine(69, 0, 69, 60);
      myGLCD.drawLine(68, 0, 68, 60);

      break;

    case 1:
      //

      // -------------- --------------------------      BOTON

      myGLCD.setColor(255, 104, 4);
      myGLCD.drawRoundRect(0, 190, 222, 270);
      myGLCD.setColor(36, 200, 36);
      myGLCD.fillRoundRect(1, 191, 221, 269);

      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("ACTIVAR", 50, 220);

      myGLCD.setColor(182, 153, 119);
      myGLCD.fillRoundRect(50, 110, 200, 140);
      myGLCD.setFont(OCR_A_Extended_M);
      myGLCD.setColor(255, 79, 33);
      myGLCD.print("APAGADA", 50, 110);

      myGLCD.setColor(182, 153, 119);
      myGLCD.fillRoundRect(50, 320, 200, 340);
      myGLCD.setFont(OCR_A_Extended_M);
      myGLCD.setColor(255, 79, 33);
      myGLCD.print("APAGADA", 50, 320);

      myGLCD.setColor(255, 104, 4);
      myGLCD.drawRoundRect(0, 405, 222, 479);
      myGLCD.setColor(36, 200, 36);
      myGLCD.fillRoundRect(1, 406, 221, 478);

      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("VALVULA 1", 50, 70);

      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("VALVULA 2", 50, 285);

      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.setBackColor(VGA_TRANSPARENT);
      myGLCD.print("ACTIVAR", 50, 433);
      break;
      //

    case 2:
      //
      //----BLOQUE B----
      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("SENSORES DE HUMEDAD(Kpa)", 300, 70);
      myGLCD.print("S1 (15cm)", 230, 120);
      myGLCD.print("S2 (30cm)", 430, 120);
      myGLCD.print("S3 (45cm)", 630, 120);

      myGLCD.drawRect(223, 61, 799, 479);
      myGLCD.drawLine(223, 270, 800, 270);
      myGLCD.drawLine(405, 61, 405, 479);
      myGLCD.drawLine(600, 61, 600, 479);

      myGLCD.setFont(Arial_round_16x24);
      myGLCD.setColor(VGA_BLACK);
      myGLCD.print("S4 (15cm)", 230, 295);
      myGLCD.print("S5 (30cm)", 430, 295);
      myGLCD.print("S6 (45cm)", 630, 295);
      break;

    case 3:

      break;

    case 4:

      //
      //---- BLOQUE D
      //

      break;
    }
  }
}

void printScreen()
{

  myGLCD.setColor(50, 121, 192);
  myGLCD.fillRect(630, 1, 790, 59);
  myGLCD.setFont(Arial_round_16x24);
  myGLCD.setColor(0, 51, 122);
  myGLCD.setBackColor(VGA_TRANSPARENT);
  myGLCD.printNumI(sensorDS18B20.getTempCByIndex(0), 670, 19);
  myGLCD.print("T=", 640, 19);

  if (pg == 1)
  {

    myGLCD.setColor(182, 153, 119);
    myGLCD.fillRect(230, 150, 400, 250);
    myGLCD.setFont(SevenSegmentFull);
    myGLCD.setColor(VGA_BLACK);
    myGLCD.setBackColor(VGA_TRANSPARENT);
    myGLCD.print(st, 270, 170);

    // SENSOR TEMPERATURA
  }
}

void touchRead()
{
  myTouch.read();
  x = myTouch.getX(); // X coordinate where the screen has been pressed
  y = myTouch.getY(); // Y coordinates where the screen has been pressed
  switch (pg)
  {
  case 0:

    if ((x >= 60) && (x <= 340) && (y >= 120) && (y <= 210)) //nogal
    {
      nodeWindow();
    }
    if ((x >= 400) && (x <= 799) && (y >= 120) && (y <= 210)) // uva
    {
      nodeWindow();
    }

    if ((x >= 60) && (x <= 340) && (y >= 240) && (y <= 479)) //  naranjo
    {
      nodeWindow();
    }
    if ((x >= 400) && (x <= 799) && (y >= 240) && (y <= 479)) // uva
    {
      nodeWindow();
    }

    break;
  case 1:

    if ((x >= 0) && (x <= 50) && (y >= 0) && (y <= 60))

    {
      drawHomeScreen();
    }

    if ((x >= 0) && (x <= 360) && (y >= 150) && (y <= 300))

    {

      if (reboton1 == "OFF")
      {

        myGLCD.setColor(255, 104, 4);
        myGLCD.drawRoundRect(0, 190, 222, 270);
        myGLCD.setColor(255, 200, 36);
        myGLCD.fillRoundRect(1, 191, 221, 269);

        myGLCD.setFont(Arial_round_16x24);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_TRANSPARENT);
        myGLCD.print("DESACTIVAR", 30, 220);

        myGLCD.setFont(OCR_A_Extended_M);
        myGLCD.setBackColor(182, 153, 119);
        myGLCD.setColor(0, 186, 34);
        myGLCD.print("ENCENDIDA", 50, 110);

        reboton1 = "ON";

        for (int i = 0; i <= 9; i++)
        {
          Serial2.println("AT+SEND=1,3," + reboton1);
          delay(333);
        }
      }

      else if (reboton1 == "ON")
      {

        myGLCD.setColor(15, 104, 4);
        myGLCD.drawRoundRect(0, 190, 222, 270);
        myGLCD.setColor(36, 200, 36);
        myGLCD.fillRoundRect(1, 191, 221, 269);

        myGLCD.setFont(Arial_round_16x24);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_TRANSPARENT);
        myGLCD.print("ACTIVAR", 50, 220);

        myGLCD.setColor(182, 153, 119);
        myGLCD.fillRoundRect(50, 110, 200, 140);
        myGLCD.setFont(OCR_A_Extended_M);
        myGLCD.setBackColor(182, 153, 119);
        myGLCD.setColor(255, 79, 33);
        myGLCD.print("APAGADA", 50, 110);

        reboton1 = "OFF";
        for (int i = 0; i <= 9; i++)
        {
          Serial2.println("AT+SEND=1,3," + reboton1);
          delay(333);
        }
      }
    }

    if ((x >= 0) && (x <= 360) && (y >= 360) && (y <= 480))

    {

      if (reboton2 == "OFF")
      {
        myGLCD.setColor(255, 104, 4);
        myGLCD.drawRoundRect(0, 405, 222, 479);
        myGLCD.setColor(36, 200, 36);
        myGLCD.fillRoundRect(1, 406, 221, 478);

        myGLCD.setFont(Arial_round_16x24);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_TRANSPARENT);
        myGLCD.print("ACTIVAR", 50, 433);

        myGLCD.setColor(182, 153, 119);
        myGLCD.fillRoundRect(50, 320, 200, 340);
        myGLCD.setFont(OCR_A_Extended_M);
        myGLCD.setColor(255, 79, 33);
        myGLCD.print("APAGADA", 50, 320);

        reboton2 = "ON";
      }

      else if (reboton2 == "ON")
      {

        myGLCD.setColor(15, 104, 4);
        myGLCD.drawRoundRect(0, 405, 222, 479);
        myGLCD.setColor(255, 200, 36);
        myGLCD.fillRoundRect(1, 406, 221, 478);

        myGLCD.setFont(Arial_round_16x24);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_TRANSPARENT);
        myGLCD.print("DESACTIVAR", 30, 433);
        myGLCD.setFont(OCR_A_Extended_M);
        myGLCD.setBackColor(182, 153, 119);
        myGLCD.setColor(0, 186, 34);
        myGLCD.print("ENCENDIDA", 50, 320);
        reboton2 = "OFF";
      }
    }

    break;
  }
}

/*--------------------------------------------------- SETUP -----------------------------------------------------------*/

void setup()

{

  Serial.begin(9600);
  Serial2.begin(115200);
  sensorDS18B20.begin();
  pinMode(LedPin, OUTPUT);
  pinMode(vSensor, OUTPUT);
  digitalWrite(vSensor, HIGH);
  pinMode(chipSelect, OUTPUT);

  //  LCD

  myGLCD.InitLCD();
  myGLCD.clrScr();

  // Touch

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_LOW);
  //nodeWindow();
  drawHomeScreen();
}

/*---------------------------------------- MAIN LOOP -------------------------------------*/

void loop()
{
  SD.begin(chipSelect);
  sensorDS18B20.begin();
  sensorDS18B20.requestTemperatures();

  if (millis() - ultTrans > intervalo)
  if (myTouch.dataAvailable())
  {
    touchRead();
    ultTrans = millis();
  }

  if (millis() - lastTrans > interval)
    if (Serial2.available())
    {
      incomingString = Serial2.readString();

      digitalWrite(LedPin, HIGH);
      //delay(100);
      digitalWrite(LedPin, LOW);

      st = splt.separa(incomingString, ',', 2);

      temp = "";

      temp = String(sensorDS18B20.getTempCByIndex(0)) + String();

      
      Serial.println(incomingString);

      File dataFile = SD.open("logTemp.txt", FILE_WRITE);
      if (dataFile)
      {
        dataFile.print("Transmisor Ciano/Receptor nogal: ");
        dataFile.print("Temperatura=");
        dataFile.print(",");
        dataFile.print(temp);
        dataFile.print(",");
        dataFile.print("Valvula 1");
        dataFile.print(",");
        dataFile.print(" Humedad Sensor(35cm)=");
        dataFile.println(st);

        dataFile.close();

        lastTrans = millis();
      }
      SD.end();
    }

    printScreen();

  
}