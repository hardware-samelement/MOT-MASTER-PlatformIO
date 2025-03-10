#ifndef _PIN_CONFIG_H__
#define _PIN_CONFIG_H__

#include "Arduino.h"
#include "stone.h"
#include "stone_config.h"


const int lampu1 = 23;
const int lampu2 = 18;
const int lampu3 = 13;
const int lampu4 = 26;
const int lampu5 = 25;
const int fog    = 33;
const int hvac   = 32;
const int enPin  = 19;
// #define lampu1          23
// #define lampu2          18
// #define lampu3          32
// #define lampu4          33
// #define lampu5          25
// #define fog             26
// #define hvac            13
// #define enPin           19
#define kalibrasi       5

#define VOIP_IDLE     0
#define VOIP_CALLING  1
#define VOIP_INCALL   2
#define VOIP_RINGING  3
#define VOIP_ENDED    4
#define VOIP_CANCEL   5
#define VOIP_DISCONNECT 6

void pin_setup(void);

//class sensor_config;

//class sensor_config{
//  public:
  void allSensor(void);
  void co2_sensor(void);
  void bme_sensor(void);
  void mplayer(void);
  
  void read_allSensor(void);
  void read_co2_sensor(void);
  void read_bme_sensor(void);
  void read_mplayer(void);

//  private:
  void co2_begin(void);
  void bme_begin(void);
  void player_begin(void);

  void read_co2_sensors(void);
  void read_bme_sensors(void);
  void read_mplayers(void);
  void read_mplayers2(void);

  void status_ambient(int stat_, String label_sensor);

  // void df_player(String command, int cvalue);

  void update_status(void);

  #define slave_addr 9

  int df_player(String command, int value = 0);
  int i2cReq(byte data);
  void i2cSend(byte data, byte data2 = 0xFF);
  
  void rs485Send(String _data);
  
//};

#endif
