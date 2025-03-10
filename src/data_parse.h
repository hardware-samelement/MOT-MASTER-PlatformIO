#ifndef _DATA_PARSE_H__
#define _DATA_PARSE_H__


void parse_begin(void);
void do_parse(void);
void set_date_time(int years, int months, int date, int hours, int minutes);
void set_bahasa(String _bahasa);
void check_gas(float _data_O2, float _data_N2O, float _data_Air, int _data_Vacuum,  bool upt);
void status_pressure(int stat, String label_gas);
void setTrack(int Trek);
void status_ambient(int stat_, String label_sensor);
class data_parse;
void reset_anastetion(void);
void check_temp(int ch_temp);
void check_humid(int ch_hum);
void check_press(float ch_press);
void check_co2(int ch_co2);
void setPlay(bool play_, int cmd);
void pref_send(bool pref);
void set_state_anastesi(bool stan);
void gas_update(float o2_g, float n2o_g, float air_g, float vacum_g);
void ambient_update(float temp_a, float humid_a, float press_a, int co2_a);
void status_update(void);
void reset_operation(void);
void set_mode_timer(int _mode);
void saveCalibration(void);
void setvolume(int _vol);
void setVolumeVoip(int _vol);
void calibrationPopup(void);
void calibrationPopup_eng(void);
void calibrationInit(void);
float calibrationStart(int sensorNumber, float inp);
void calibrationReset(int sensorNumber);
void checkAlarm(void);
void popupAlarm(int status);
void labelAlarmUpdate(void);
void relay_setup(void);
void setkecerahan(int _brg);
void setButtonOp(void);
void setButtonAn(void);
void button_timer_update(void);
void savevar_lock(int varlock);
void iotSendData(void);
void iotReset(void);
void iotSendConfig(String ssid, String Password);
void iotStatusUpdate(int flag = 0);
void addressBookShow(void);
void addressBookSort(void);
void addressBookPrint(void);
void contactDetail(int i);
void closeContactDetail(void);
void timerOp_forceStop(void);

int addressBookFullCheck(void);
void addressBookDelete(void);
String addressBookCheck(String number);
void addressBookSavetoMemory(void);
void addressBookLoad(void);
void keypadPressed(int key);

// int savedOpTimeRTC(void);
class data_parse {
public:
  int getOpVal(void);
  int getAnVal(void);
  int getAnastetionTime(void);
  String getLanguage(void);
  int getTrack(void);
  int getsTates(void);
  bool isPopupMusic(void);
  bool isPlayMusic(void);
  long int get_mill_an(void);
  long int get_mill_op(void);
  int getState_timer(void);
  int getState_timer_an(void);
  bool isCalibrateSensor(void);
  int getSensorNumber(void);
  void saveSensorData(float);
  bool isAlarmBip(void);
  bool isSnooze(void);
  void setAlarmDelayDone(int en);
  void setBip(int duration);
  void openCalibrationPage(void);
  void savestlcd(bool state);
  void timeoutLoading(int progres);
  void loadingReset(void);
  void set_state_counter(int counters, int val_counter);
  void set_rtc_time(int dys, int hr, int mnt, int dtk);
};


#endif
