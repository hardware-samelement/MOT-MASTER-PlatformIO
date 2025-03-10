#include "pin_config.h"
#include "stone.h"
#include "data_parse.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
// #include "DFRobotDFPlayerMini.h"
#include <SensirionI2CScd4x.h>

// DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

data_parse dparse;
unsigned long int timeSampling = 0;

SensirionI2cScd4x scd4x;
int bounc = 0;
int Temperature_ = 0;
int Humidity_ = 0;
float Pressure_ = 0;
int Temperature_cpy_ = 0;
int Humidity_cpy_ = 0;
float Pressure_cpy_ = 0;
uint16_t co2_cpy = 0;

int min_Temp_ = 19;
int max_Temp_ = 24;
int track_;
int min_Humid_ = 55;
int max_Humid_ = 65;

int sensor_sampling = 41;
int send_interval = 5000;
uint16_t co2 = 0;

uint32_t kuning_ = 4293579568;
uint32_t hijau_ = 4278227762;
uint32_t merah_ = 4294901760;
String title_ = "";
String title_cpy_ = "Track";
char t_music_[10];

String bahasa_;
//int bounc;
bool _play = false;

int jumlah_track;
int currentTrack;
int lastTrack = 1;

void pin_setup() {
  pinMode(lampu1, OUTPUT);
  pinMode(lampu2, OUTPUT);
  pinMode(lampu3, OUTPUT);
  pinMode(lampu4, OUTPUT);
  pinMode(lampu5, OUTPUT);
  pinMode(fog, OUTPUT);
  pinMode(hvac, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(kalibrasi, INPUT);


  digitalWrite(lampu1, HIGH);
  digitalWrite(lampu2, HIGH);
  digitalWrite(lampu3, HIGH);
  digitalWrite(lampu4, HIGH);
  digitalWrite(lampu5, HIGH);
  digitalWrite(fog, HIGH);
  digitalWrite(hvac, HIGH);
  digitalWrite(enPin, LOW);

  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 14, 27);
  Serial2.begin(115200);
  Wire.begin();
}

//sensor_config::
void mplayer(void) {
  player_begin();
}


void player_begin(void) {
  // Serial1.begin(9600,SERIAL_8N1,27,14);

  // if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
  //   sdebug_println(F("Unable to begin:"));
  //   sdebug_println(F("1.Please recheck the connection!"));
  //   sdebug_println(F("2.Please insert the SD card!"));
  //   while(true){
  //     delay(0); // Code to compatible with ESP8266 watch dog.
  //   }
  // }
  // jumlah_track = myDFPlayer.readFileCounts();
  jumlah_track = df_player("readFileCounts");
  // myDFPlayer.volume(5);
  df_player("volume", 5);
  lib_set_value("slider", "slider4", "15", "%d");
}


//sensor_config::
void read_mplayer(void) {
  read_mplayers();
}

void update_status(void) {
  check_temp(Temperature_);
  check_humid(Humidity_);
}

//sensor_config::

void read_mplayers2(void) {

  int track = df_player("readCurrentFileNumber");

  if (track != -1) {
    currentTrack = track;         //ambil track
    setTrack(currentTrack);  //set track
  }

  //update judul track
  if (currentTrack != lastTrack) {
    if (currentTrack != 128) {
      lib_set_text("label", "label_judul_lagu", "Track " + String(currentTrack));
    }

    if ((currentTrack == 128 && lastTrack == 127) || (currentTrack == 128 && lastTrack == 129)) {
      lib_set_text("label", "label_judul_lagu", "Track " + String(currentTrack));
    }
  }



  lastTrack = currentTrack;
}

int df_player(String command, int value) {
  if (command == "play") {
    i2cSend(0x01, value);
  } else if (command == "pause") {
    i2cSend(0x02);
  } else if (command == "volume") {
    i2cSend(0x03, value);
  } else if (command == "next") {
    i2cSend(0x04);
  } else if (command == "prev") {
    i2cSend(0x05);
  } else if (command == "start") {
    i2cSend(0x06);
  } else if (command == "readState") {
    return i2cReq(0x11);
  } else if (command == "readFileCounts") {
    return i2cReq(0x12);
  } else if (command == "readVolume") {
    return i2cReq(0x13);
  } else if (command == "readCurrentFileNumber") {
    return i2cReq(0x14);
  }
  return 0;
}

void i2cSend(byte data, byte data2) {
  Wire.beginTransmission(slave_addr);
  Wire.write(data);
  if (data2 != 0xFF) {
    Wire.write(data2);
  }
  Wire.endTransmission();
}

int i2cReq(byte data) {
  int receivedData;
  byte dataHeader;
  i2cSend(data);
  delay(1);

  Wire.requestFrom(slave_addr, 2);

  if (1 <= Wire.available()) {
    dataHeader = Wire.read();
    if (dataHeader == 'M') {
      receivedData = Wire.read();
    } else {
      Wire.read();
      return 0;
    }
  }
  delay(10);
  Serial.print("receivedData : ");
  Serial.println(receivedData);
  return receivedData;
}

void rs485Send(String _data) {
  delay(10);
  digitalWrite(enPin, HIGH);
  delay(1);
  Serial.println(_data);
  delay(10);
  digitalWrite(enPin, LOW);
}
