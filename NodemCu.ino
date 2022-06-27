#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

const int r1 = D3;
const int r2 = D7;
const int r3 = D5;
const int r4 = D6;

const int led1 = D0;
const int led2 = D4;

//String urlpost = "https://addequar.com/valvulas/v2.json";
//String urlget = "https://addequar.com/valvulas/v2.json";//"http://jsonplaceholder.typicode.com/users/1";//

const char *host = "addequar.com";

String Link[4] = {"/valvulas/v1.json", "/valvulas/v2.json", "/valvulas/v3.json", "/valvulas/v4.json"};

String liner[4];



String stdv[4];
int tiemp[4];

int seg = 0;
int minm = 0;
int hor = 0;
int dia = 0;

String modo[4];
int horact[4];
String diact[4];

int dias1[4][7];

int stado = 1;

int con1 = 0;
int con2 = 0;
int con3 = 0;
int con4 = 0;

const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80

//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "f6b771155e681001e71456e03daad3aa6553aab5";//"D7 85 BF F3 FC 1D 53 B0 2F 0A 62 E0 F7 6D 10 B6 58 7D D9 8D";

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;

unsigned long currentMillis = 0;

long interval1 = 0;//6;
long interval2 = 0;//3;
long interval3 = 0;//10;
long interval4 = 0;//8;
long interval5 = 60;//8;

int ban = 0;

void setup() {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("Juana", "Jpolo10+");   //WiFi connection

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  pinMode(r1, OUTPUT); digitalWrite(r1, HIGH);
  pinMode(r2, OUTPUT); digitalWrite(r2, HIGH);
  pinMode(r3, OUTPUT); digitalWrite(r3, HIGH);
  pinMode(r4, OUTPUT); digitalWrite(r4, HIGH);

  pinMode(led1, OUTPUT); digitalWrite(led1, HIGH);
  pinMode(led2, OUTPUT); digitalWrite(led2, HIGH);

  Serial.print("Waiting for connection");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    digitalWrite(led1, !digitalRead(led1));
    delay(200);
    Serial.print(".");
  }
  digitalWrite(led1, HIGH);

  Serial.println("");
  //If connection successful show IP address in serial monitor
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  getdat();
  currentMillis = millis() / 1000;
  control();

}

void loop() {
  currentMillis = millis() / 1000;
  hora();


  if (currentMillis - previousMillis5 >= interval5 and ban == 1) {
    previousMillis5 = currentMillis;
    Serial.println("Lectura red");
    getdat();
    control();
  }


  for (int i = 0; i < 4; i++) {
    if (horact[i] == hor and seg < 8 and minm == 0 and modo[i] == "a") {
      for (int j = 0; j < 7; j++) {
        if (dias1[i][j] == dia) {

          if (i == 0) {
            Serial.println("Valvula 1");
            digitalWrite(r1, LOW);
            previousMillis1 = currentMillis;
            con1 = 1;
          }
          if (i == 1) {
            Serial.println("Valvula 2");
            digitalWrite(r2, LOW);
            previousMillis2 = currentMillis;
            con2 = 1;
          }
          if (i == 2) {
            Serial.println("Valvula 3");
            digitalWrite(r3, LOW);
            previousMillis3 = currentMillis;
            con3 = 1;
          }
          if (i == 3) {
            Serial.println("Valvula 4");
            digitalWrite(r4, LOW);
            previousMillis4 = currentMillis;
            con4 = 1;
          }

        }
      }
    }
  }

  eval();




  delay(100);
  //Serial.println(actualtime);
}


//------------------------------------------------------
void getdat() {
  digitalWrite(led2, LOW);
  for (int i = 0; i < 4; i++) {

    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

      WiFiClientSecure httpsClient;    //Declare object of class WiFiClient

      Serial.println(host);

      Serial.printf("Using fingerprint '%s'\n", fingerprint);
      httpsClient.setFingerprint(fingerprint);
      httpsClient.setTimeout(15000); // 15 Seconds
      delay(500);

      Serial.print("HTTPS Connecting");
      int r = 0; //retry counter
      while ((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
        delay(100);
        Serial.print(".");
        r++;
      }
      if (r == 30) {
        Serial.println("Connection failed");
      }
      else {
        Serial.println("Connected to web");
      }

      Serial.print("requesting URL: ");
      Serial.println(host + Link[i]);

      httpsClient.print(String("GET ") + Link[i] + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n\r\n");

      Serial.println("request sent");

      while (httpsClient.connected()) {
        String line = httpsClient.readStringUntil('\n');
        if (line == "\r") {
          Serial.println("headers received");
          break;
        }
      }

      Serial.println("reply was:");
      Serial.println("==========");

      while (httpsClient.available()) {
        liner[i] = httpsClient.readStringUntil('\n');  //Read Line by Line
        Serial.println(liner[i]); //Print response
      }
      Serial.println("==========");
      Serial.println("closing connection");

    }

  }
  digitalWrite(led2, HIGH);

  int datos0 = 0;
  int datos1 = 0;
  int datos2 = 0;
  int datos3 = 0;


  if (liner[0] == "") {
    Serial.println("No Datos 1");
    datos0 = 0;
  } else if (liner[0] != "") {
    Serial.println("Datos 1");
    datos0 = 1;
  }
  if (liner[1] == "") {
    Serial.println("No Datos 2");
    datos1 = 0;
  } else if (liner[1] != "") {
    Serial.println("Datos 2");
    datos1 = 1;
  }
  if (liner[2] == "") {
    Serial.println("No Datos 3");
    datos2 = 0;
  } else if (liner[2] != "") {
    Serial.println("Datos 3");
    datos2 = 1;
  }
  if (liner[3] == "") {
    Serial.println("No Datos 4");
    datos3 = 0;
  } else if (liner[3] != "") {
    Serial.println("Datos 4");
    datos3 = 1;
  }

  datain(datos0, datos1, datos2, datos3);
  Serial.println("Actualizado");
  /*
    if (datos == 1) {
      for (int  i = 0; i < 4; i++) {
        Serial.println(liner[i]);
        stdv[i] = getValue(liner[i], '*', 0);
        tiemp[i] = (getValue(liner[i], '*', 1)).toInt();
        modo[i] = getValue(liner[i], '*', 2);
        horact[i] = (getValue(liner[i], '*', 4)).toInt();
        diact[i] = getValue(liner[i], '*', 3);
        Serial.println(stdv[i]);
        Serial.println(tiemp[i]);
        Serial.println(modo[i]);
        Serial.println(horact[i]);
        Serial.println(diact[i]);
      }
      digitalWrite(led1, LOW);

      int diasvol[7];
      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 7; i++) {
          diasvol[i] = getValue(diact[j], '-', i).toInt();
          if (i == 0) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 7;
            }
          }
          if (i == 1) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 1;
            }
          }
          if (i == 2) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 2;
            }
          }
          if (i == 3) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 3;
            }
          }
          if (i == 4) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 4;
            }
          }
          if (i == 5) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 5;
            }
          }
          if (i == 6) {
            if (diasvol[i] == 1) {
              dias1[j][i] = 6;
            }
          }
          //Serial.println(diasvol[i]);
        }
      }

      for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 7; i++) {
          Serial.print(dias1[j][i]);
        }
        Serial.println("");
      }
      Serial.println("");

      interval1 = tiemp[0] * 60;
      interval2 = tiemp[1] * 60;
      interval3 = tiemp[2] * 60;
      interval4 = tiemp[3] * 60;
    }
    memset(liner, 0, sizeof(liner));
  */
  memset(liner, 0, sizeof(liner));
}

//------------------------------------------------------
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//-------------------------------------------------------------------
void control() {



  if (stdv[0] == "ON" and modo[0] == "m") {
    digitalWrite(r1, LOW);
    previousMillis1 = currentMillis;
    stdv[0] = "";
  } else if (stdv[0] == "OFF" and modo[0] == "m") {
    digitalWrite(r1, HIGH);
    stdv[0] = "G";
  }

  if (stdv[1] == "ON" and modo[1] == "m") {
    digitalWrite(r2, LOW);
    previousMillis2 = currentMillis;
    stdv[1] = "";
  } else if (stdv[0] == "OFF" and modo[0] == "m") {
    digitalWrite(r2, HIGH);
    stdv[1] = "G";
  }

  if (stdv[2] == "ON" and modo[2] == "m") {
    digitalWrite(r3, LOW);
    previousMillis3 = currentMillis;
    stdv[2] = "";
  } else if (stdv[0] == "OFF" and modo[0] == "m") {
    digitalWrite(r3, HIGH);
    stdv[2] = "G";
  }

  if (stdv[3] == "ON" and modo[3] == "m") {
    digitalWrite(r4, LOW);
    previousMillis4 = currentMillis;
    stdv[3] = "G";
  } else if (stdv[0] == "OFF" and modo[0] == "m") {
    digitalWrite(r4, HIGH);
  }


}


//-------------------------------------------------------------------
void hora() {
  DateTime now = rtc.now();
  //  Serial.print(now.year(), DEC);
  //  Serial.print('/');
  //  Serial.print(now.month(), DEC);
  //  Serial.print('/');
  dia = now.dayOfTheWeek();
  //Serial.println(dia);
  seg = now.second();

  minm = now.minute();

  if (seg > 10 and minm != 0) {
    ban = 1;
  } else {
    ban = 0;
  }

  if (dia == 0) {
    dia = 7;
  }

  //  Serial.print(dia, DEC);

  hor = now.hour();

  //  Serial.print(hor);
  //  Serial.print(':');
  //  Serial.print(now.minute(), DEC);
  //  Serial.print(':');
  //  Serial.print(now.second(), DEC);
  //  Serial.println();

}


//--------------------------------------------------------------------
void print_tiempo(unsigned long tiempo_millis) {
  Serial.print("Tiempo: ");
  tiempo_millis = tiempo_millis / 1000;
  Serial.print(tiempo_millis);
  Serial.print("s - ");
}

//-------------------------------------------------------------------
void eval() {

  for (int i = 0; i < 4; i++) {
    if (modo[i] == "m") {
      if (currentMillis - previousMillis1 >= interval1 and i == 0) {
        //Serial.println(currentMillis - previousMillis1);
        // save the last time you blinked the LED
        previousMillis1 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 1 m");
        digitalWrite(r1, HIGH);

      }

      if (currentMillis - previousMillis2 >= interval2 and i == 1) {
        //Serial.println(currentMillis - previousMillis2);
        // save the last time you blinked the LED
        previousMillis2 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 2 m");
        digitalWrite(r2, HIGH);
        stdv[1] = "";
      }

      if (currentMillis - previousMillis3 >= interval3 and i == 2) {
        //Serial.println(currentMillis - previousMillis3);
        // save the last time you blinked the LED
        previousMillis3 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 3 m");
        digitalWrite(r3, HIGH);
        stdv[2] = "";
      }

      if (currentMillis - previousMillis4 >= interval4 and i == 3) {
        //Serial.println(currentMillis - previousMillis4);
        // save the last time you blinked the LED
        previousMillis4 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 4 m");
        digitalWrite(r4, HIGH);
        stdv[3] = "";

      }
    } else if (modo[i] == "a") {
      if (currentMillis - previousMillis1 >= interval1 and i == 0 and con1 == 1) {
        //Serial.println(currentMillis - previousMillis1);
        // save the last time you blinked the LED
        previousMillis1 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 1 a");
        digitalWrite(r1, HIGH);
      }

      if (currentMillis - previousMillis2 >= interval2 and i == 1 and con2 == 1) {
        //Serial.println(currentMillis - previousMillis2);
        // save the last time you blinked the LED
        previousMillis2 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 2 a");
        digitalWrite(r2, HIGH);
      }

      if (currentMillis - previousMillis3 >= interval3 and i == 2 and con3 == 1) {
        //Serial.println(currentMillis - previousMillis3);
        // save the last time you blinked the LED
        previousMillis3 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 3 a");
        digitalWrite(r3, HIGH);
      }

      if (currentMillis - previousMillis4 >= interval4 and i == 3 and con4 == 1) {
        //Serial.println(currentMillis - previousMillis4);
        // save the last time you blinked the LED
        previousMillis4 = currentMillis;
        Serial.println("Timepo Cumplido Valvula 4 a");
        digitalWrite(r4, HIGH);
      }
    }
  }
}

//-------------------------------------------------------------------
void postv() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    WiFiClientSecure httpsClient;    //Declare object of class WiFiClient

    Serial.println(host);

    Serial.printf("Using fingerprint '%s'\n", fingerprint);
    httpsClient.setFingerprint(fingerprint);
    httpsClient.setTimeout(15000); // 15 Seconds
    delay(1000);

    Serial.print("HTTPS Connecting");
    int r = 0; //retry counter
    while ((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
      delay(100);
      Serial.print(".");
      r++;
    }
    if (r == 30) {
      Serial.println("Connection failed");
    }
    else {
      Serial.println("Connected to web");
    }

    String getData, linkp;

    //POST Data
    linkp = "/valvulas/borrado.php";
    //Link = "/post";

    Serial.print("requesting URL: ");
    Serial.println(host);
    /*
      POST /post HTTP/1.1
      Host: postman-echo.com
      Content-Type: application/x-www-form-urlencoded
      Content-Length: 13

      say=Hi&to=Mom

    */

    httpsClient.print(String("POST ") + linkp + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                      "Content-Length: 0" + "\r\n\r\n");

    Serial.println(String("POST ") + linkp + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
                      "Content-Length: 0" + "\r\n\r\n");
                      
    Serial.println("request sent");

    while (httpsClient.connected()) {
      String line1 = httpsClient.readStringUntil('\n');
      if (line1 == "\r") {
        Serial.println("headers received");
        break;
      }
    }

    Serial.println("reply was:");
    Serial.println("==========");
    String line1;
    while (httpsClient.available()) {
      line1 = httpsClient.readStringUntil('\n');  //Read Line by Line
      Serial.println(line1); //Print response
    }
    Serial.println("==========");
    Serial.println("closing connection");
  }


}


//-------------------------------------------------------------------
void datain(int dt1, int dt2, int dt3, int dt4) {

  if (dt1 == 1) {
    for (int  i = 0; i < 1; i++) {
      Serial.println(liner[i]);
      stdv[i] = getValue(liner[i], '*', 0);
      tiemp[i] = (getValue(liner[i], '*', 1)).toInt();
      modo[i] = getValue(liner[i], '*', 2);
      horact[i] = (getValue(liner[i], '*', 4)).toInt();
      diact[i] = getValue(liner[i], '*', 3);
      Serial.println(stdv[i]);
      Serial.println(tiemp[i]);
      Serial.println(modo[i]);
      Serial.println(horact[i]);
      Serial.println(diact[i]);
    }
    digitalWrite(led1, LOW);

    int diasvol[7];
    for (int j = 0; j < 1; j++) {
      for (int i = 0; i < 7; i++) {
        diasvol[i] = getValue(diact[j], '-', i).toInt();
        if (i == 0) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 7;
          }
        }
        if (i == 1) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 1;
          }
        }
        if (i == 2) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 2;
          }
        }
        if (i == 3) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 3;
          }
        }
        if (i == 4) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 4;
          }
        }
        if (i == 5) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 5;
          }
        }
        if (i == 6) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 6;
          }
        }
        //Serial.println(diasvol[i]);
      }
    }

    for (int j = 0; j < 1; j++) {
      for (int i = 0; i < 7; i++) {
        Serial.print(dias1[j][i]);
      }
      Serial.println("");
    }
    Serial.println("");

    interval1 = tiemp[0] * 60;
    interval2 = tiemp[1] * 60;
    interval3 = tiemp[2] * 60;
    interval4 = tiemp[3] * 60;

  }

  if (dt2 == 1) {
    for (int  i = 1; i < 2 ; i++) {
      Serial.println(liner[i]);
      stdv[i] = getValue(liner[i], '*', 0);
      tiemp[i] = (getValue(liner[i], '*', 1)).toInt();
      modo[i] = getValue(liner[i], '*', 2);
      horact[i] = (getValue(liner[i], '*', 4)).toInt();
      diact[i] = getValue(liner[i], '*', 3);
      Serial.println(stdv[i]);
      Serial.println(tiemp[i]);
      Serial.println(modo[i]);
      Serial.println(horact[i]);
      Serial.println(diact[i]);
    }
    digitalWrite(led1, LOW);

    int diasvol[7];
    for (int j = 1; j < 2; j++) {
      for (int i = 0; i < 7; i++) {
        diasvol[i] = getValue(diact[j], '-', i).toInt();
        if (i == 0) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 7;
          }
        }
        if (i == 1) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 1;
          }
        }
        if (i == 2) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 2;
          }
        }
        if (i == 3) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 3;
          }
        }
        if (i == 4) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 4;
          }
        }
        if (i == 5) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 5;
          }
        }
        if (i == 6) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 6;
          }
        }
        //Serial.println(diasvol[i]);
      }
    }

    for (int j = 1; j < 2; j++) {
      for (int i = 0; i < 7; i++) {
        Serial.print(dias1[j][i]);
      }
      Serial.println("");
    }
    Serial.println("");

    interval1 = tiemp[0] * 60;
    interval2 = tiemp[1] * 60;
    interval3 = tiemp[2] * 60;
    interval4 = tiemp[3] * 60;


  }

  if (dt3 == 1) {
    for (int  i = 2; i < 3 ; i++) {
      Serial.println(liner[i]);
      stdv[i] = getValue(liner[i], '*', 0);
      tiemp[i] = (getValue(liner[i], '*', 1)).toInt();
      modo[i] = getValue(liner[i], '*', 2);
      horact[i] = (getValue(liner[i], '*', 4)).toInt();
      diact[i] = getValue(liner[i], '*', 3);
      Serial.println(stdv[i]);
      Serial.println(tiemp[i]);
      Serial.println(modo[i]);
      Serial.println(horact[i]);
      Serial.println(diact[i]);
    }
    digitalWrite(led1, LOW);

    int diasvol[7];
    for (int j = 2; j < 3; j++) {
      for (int i = 0; i < 7; i++) {
        diasvol[i] = getValue(diact[j], '-', i).toInt();
        if (i == 0) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 7;
          }
        }
        if (i == 1) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 1;
          }
        }
        if (i == 2) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 2;
          }
        }
        if (i == 3) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 3;
          }
        }
        if (i == 4) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 4;
          }
        }
        if (i == 5) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 5;
          }
        }
        if (i == 6) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 6;
          }
        }
        //Serial.println(diasvol[i]);
      }
    }

    for (int j = 2; j < 3; j++) {
      for (int i = 0; i < 7; i++) {
        Serial.print(dias1[j][i]);
      }
      Serial.println("");
    }
    Serial.println("");

    interval1 = tiemp[0] * 60;
    interval2 = tiemp[1] * 60;
    interval3 = tiemp[2] * 60;
    interval4 = tiemp[3] * 60;

  }

  if (dt4 == 1) {
    for (int  i = 3; i < 4 ; i++) {
      Serial.println(liner[i]);
      stdv[i] = getValue(liner[i], '*', 0);
      tiemp[i] = (getValue(liner[i], '*', 1)).toInt();
      modo[i] = getValue(liner[i], '*', 2);
      horact[i] = (getValue(liner[i], '*', 4)).toInt();
      diact[i] = getValue(liner[i], '*', 3);
      Serial.println(stdv[i]);
      Serial.println(tiemp[i]);
      Serial.println(modo[i]);
      Serial.println(horact[i]);
      Serial.println(diact[i]);
    }
    digitalWrite(led1, LOW);

    int diasvol[7];
    for (int j = 3; j < 4; j++) {
      for (int i = 0; i < 7; i++) {
        diasvol[i] = getValue(diact[j], '-', i).toInt();
        if (i == 0) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 7;
          }
        }
        if (i == 1) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 1;
          }
        }
        if (i == 2) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 2;
          }
        }
        if (i == 3) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 3;
          }
        }
        if (i == 4) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 4;
          }
        }
        if (i == 5) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 5;
          }
        }
        if (i == 6) {
          if (diasvol[i] == 1) {
            dias1[j][i] = 6;
          }
        }
        //Serial.println(diasvol[i]);
      }
    }

    for (int j = 3; j < 4; j++) {
      for (int i = 0; i < 7; i++) {
        Serial.print(dias1[j][i]);
      }
      Serial.println("");
    }
    Serial.println("");

    interval1 = tiemp[0] * 60;
    interval2 = tiemp[1] * 60;
    interval3 = tiemp[2] * 60;
    interval4 = tiemp[3] * 60;

  }

if(dt1 == 1 or  dt2 == 1 or dt3 == 1 or dt4 == 1){
  postv();
}

}
