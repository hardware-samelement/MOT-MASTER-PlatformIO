#include "stone.h"
#include "pin_config.h"
#include "data_parse.h"
#include <Preferences.h>
#include <rom/rtc.h>
#include "RTClib.h"

RTC_DS3231 RTC;
Preferences pref;

//#define DS3231_I2C_ADDRESS 0x68
String bahasa;
data_parse dp;
edit_data eds;
bool ref = false;
float data_O2;   //ADC Value from Pressure O2 Sensor
float data_N2O;  //ADC Value from Pressure N2O Sensor
float data_Air;  //ADC Value from Pressure CO2 Sensor
float data_Vacuum;
int data_O2_cpy = 0;
int data_N2O_cpy = 0;
int data_Air_cpy = 0;
int data_Vacuum_cpy = 0;
float temp;
float humid;
float pressU;
int co2_;
int first = 0;
long int second_of_Anastetion = 0;
unsigned long int second_of_timeOperation = 0;

unsigned long int longTimer = 0;
unsigned long int longTimer1 = 0;
unsigned long int longTimer2 = 0;
unsigned long int longTimer3 = 0;
unsigned long int longTimerResetReason = 0;
unsigned long int longTimerBzr = 0;
unsigned long int push_start = 0;
unsigned long int longTimerTest = 0;
unsigned long int longTimerVoip = 0;

unsigned long int timer_An_proc = 0;
unsigned long int timer_Op_proc = 0;
unsigned long int timer_updateStatus = 0;
unsigned long int timer_updateTrack = 0;

unsigned long int waktu_update = 0;
unsigned long int interval_update = 300000;
int ad = 0;
int ct_an = 0;
int _cnt = 0;
// unsigned long int second_of_timeOperation = 0;
// unsigned long int second_of_Anastetion = 0;
unsigned long int operate_start;
unsigned long int anastetion_start;
unsigned long int now_count = 0;
unsigned long int var_lock = 0;
int cnt = 0;
bool ops = true;
bool ans = false;
int tmr = 0;
bool raspi = false;
bool s_loop = false;
int cpy_stat;
int cpy_state;
unsigned long int operating_timer = 0;
bool t_ans = true;
unsigned long int timeout_op = 0;
unsigned long int timeout_an = 0;
bool loop_op = false;
bool loop_an = false;
//unsigned long int operate_start =0;
unsigned long int var_an = 0;
unsigned long int var_op = 0;
int keys = 0;
bool stlcd = false;
bool pause_ = false;

// variabel rtc
int startRTC;
int startAnRTC;
int flagSaveRTC = 0;
int flagSaveAnRTC = 0;
int savedOpTime = 0;
int savedAnTime = 0;

//variabel mp3
bool play = 0;

// variabel alarm
int alarmTimerArr[] = { 225, 450, 675, 1025, 1250, 2550, 2775, 3000, 3350, 3575, 7475 };
int alarmTimerCnt = 0;
int snoozeCount = 0;
int rst = 1;
int alarmEnableSet = 0;

float temp_c;
float humid_c;

float data_O2_c;
float data_N2O_c;
float data_Air_c;
float data_Vacuum_c;

//variabel voip
int voip_status;
int voip_volume;
bool voip_ethernet_connected = false;
bool voip_callTimer = false;
bool voip_callEnd = false;
int voip_callEnd_close = 0;
int voip_callTime = 0;
int voip_callTimejj = 0;
int voip_callTimemm = 0;
int voip_callTimedd = 0;
int voip_callReject = 0;
char voip_time[10];

// function declaration
void receive_raspi();
void Pressr_RS485();
void op_proc();
void an_proc();
void checkRTC();
void sendDataSensor();
void print_reset_reason(RESET_REASON reason);

void setup() {

  delay(8000);
  sdebug_println("getting started");
  delay(10);
  pin_setup();
  parse_begin();

  // allSensor();
  calibrationInit();
  // delay(1000);
  checkRTC();
  sdebug_println("setup done");

  waktu_update = millis();

  Serial2.println("ST<{\"cmd_code\":\"get_date\",\"type\":\"time_clock\",\"widget\":\"digit_clock4\"}>ET");
}

void loop() {

  serial_receive();
  // Serial.printf("state_timer op : %d\n pause : %d\n", dp.getState_timer(), pause_);
  if (dp.getState_timer() != cpy_stat) {
    if (dp.getState_timer() == 1) {
      if (cpy_stat != 2) timeout_op = millis();
      else if (cpy_stat == 2) {
        keys = 2;
        var_lock = second_of_timeOperation;
      }
      loop_op = true;
      //Serial.printf("state_timer op : %d\n", dp.getState_timer());
      //open view loading
      //Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"butt_a_str\",\"enable\":false}>ET"));
      Serial2.println(F("ST<{\"cmd_code\":\"set_xy\",\"type\":\"widget\",\"widget\":\"view_timeoutWait\",\"x\":555,\"y\":125}>ET"));
      if (pause_ == false) Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_timeoutWait\",\"visible\":true}>ET"));

      //Serial.printf("state : %d \t cpy stat = %d \t timeout_op = %ld\n", dp.getState_timer(), cpy_stat, timeout_op);
    } else if (dp.getState_timer() == 0) {
      loop_op = false;
      timeout_op = 0;
      second_of_timeOperation = 0;
      keys = 0;
      stlcd = false;
      dp.savestlcd(stlcd);
      var_op = 0;
      cnt = 0;
      _cnt = 0;
      pause_ = false;
      savedOpTime = 0;
      flagSaveRTC = 0;

      //timer stop rtc, reset all parameter
      pref.begin("timer", false);
      pref.putInt("isOpRun", 0);
      pref.putInt("raspiOp", 0);
      pref.putInt("RTCsavedTime", 0);
      pref.end();

    } else if (dp.getState_timer() == 2) {
      pause_ = true;

      //timer paused rtc, save paused time to memory
      pref.begin("timer", false);
      savedOpTime = second_of_timeOperation;  // second_of_timeOperation is current op timer

      Serial.print("saved op time  : ");
      Serial.println(savedOpTime);

      pref.putInt("RTCsavedTime", savedOpTime);
      pref.putInt("isOpRun", 0);
      pref.end();
      flagSaveRTC = 0;
    }
    if (dp.getState_timer() == 2 && raspi == false) loop_op = false;
    else if (dp.getState_timer() == 2 && raspi == false) loop_op = true;
  }
  cpy_stat = dp.getState_timer();

  yield();

  if (dp.getState_timer_an() != cpy_state) {
    if (dp.getState_timer_an() != 0) {
      first = 0;
      timeout_an = millis();
      //Serial.printf("timeout_an = %ld\n", timeout_an);
      loop_an = true;
      //open view loading
      Serial2.println(F("ST<{\"cmd_code\":\"set_xy\",\"type\":\"widget\",\"widget\":\"view_timeoutWait\",\"x\":41,\"y\":125}>ET"));
      Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_timeoutWait\",\"visible\":true}>ET"));

    } else {
      stlcd = false;
      dp.savestlcd(stlcd);
      loop_an = false;
      var_an = 0;
      savedAnTime = 0;

      pref.begin("timer", false);
      pref.putInt("isAnRun", 0);
      pref.putInt("raspiAn", 0);
      pref.end();
    }
  }
  cpy_state = dp.getState_timer_an();
  if (loop_op == true) {
    unsigned long int cek = millis() - timeout_op;
    //Serial.printf("check : %ld \n", cek);
    //Serial.printf("timeout_op : %ld, raspi : %d, stlcd : %d\n", timeout_op, raspi, stlcd);
    if ((timeout_op != 0 && cek >= 10000 && raspi == false) || stlcd == true) {
      if (cnt == 0) var_op = (millis() - dp.getOpVal()) / 1000;
      else if (cnt < 3) {
        dp.loadingReset();
      }

      stlcd = true;
      dp.savestlcd(stlcd);
      // Serial.printf("millis : %ld \t stat_miliis : %ld\n", millis(), dp.getOpVal());

      //start save rtc
      if (flagSaveRTC == 0) {  //jalan sekali
        flagSaveRTC++;

        pref.begin("timer", false);
        if (pref.getInt("isOpRun") == 0) {  //jika timer op sebelumnya mati
          DateTime now = RTC.now();
          startRTC = now.unixtime();
          pref.putInt("startRTC", startRTC);
          pref.putInt("isOpRun", 1);

          Serial.print("mulai op rtc  : ");
          Serial.println(startRTC);
        }

        pref.end();
      }

      //

      if (millis() - timer_Op_proc > 1000) {
        op_proc();
        timer_Op_proc = millis();
        //if (loop_an == false && _cnt <2) Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"butt_a_str\",\"enable\":true}>ET"));
        _cnt++;
      }
      cnt++;
    } else {
      stlcd = false;
      dp.savestlcd(stlcd);

      if (millis() - timer_Op_proc > 1800 && raspi == false && pause_ == false) {
        dp.timeoutLoading(int(cek / 1800));
        timer_Op_proc = millis();

      } else {
        //if(ans == false && _cnt != 0 && _cnt <3) Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"butt_a_str\",\"enable\":true}>ET"));
        _cnt++;
      }
      receive_raspi();
    }
    //Serial.printf("vtimeout : %ld \t timeout : %ld\traspi : %d\n", timeout_op, cek , raspi);
    // if (loop_an == false) {

    //}
  }
  yield();

  if (loop_an == true) {
    unsigned long int ceks = millis() - timeout_an;

    if ((timeout_an != 0 && ceks >= 10000 && raspi == false) || stlcd == true) {
      if (stlcd && first == 0) var_an = 0;
      // else if (!stlcd && first == 0) var_an = (timeout_an - dp.getAnVal()) / 1000;
      else if (!stlcd && first == 0) var_an = (millis() - dp.getAnVal()) / 1000;
      if (first < 3) dp.loadingReset();

      stlcd = true;
      dp.savestlcd(stlcd);

      //start save start an time rtc
      if (flagSaveAnRTC == 0) {
        flagSaveAnRTC++;

        pref.begin("timer", false);
        if (pref.getInt("isAnRun") == 0) {
          DateTime now = RTC.now();
          startAnRTC = now.unixtime();
          Serial.print("mulai an rtc  : ");
          Serial.println(startAnRTC);

          pref.putInt("startAnRTC", startAnRTC);
          pref.putInt("isAnRun", 1);
        }

        pref.end();
      }

      if (millis() - timer_An_proc > 1000) {
        an_proc();
        timer_An_proc = millis();
      }

      first++;

    } else {
      stlcd = false;
      dp.savestlcd(stlcd);
      receive_raspi();

      if (millis() - timer_Op_proc > 1800 && raspi == false && pause_ == false) {
        dp.timeoutLoading(int(ceks / 1800));
        timer_Op_proc = millis();
      }
    }
  }
  yield();
  if (loop_op == false && loop_an == false && raspi == true) {
    raspi = false;
  }


  //Tombol fisik kalibrasi
  if (digitalRead(5) == LOW && ref == false) {
    // digitalWrite(enPin, HIGH);
    // delay(10);
    // Serial.println("SIPS;");
    // delay(10);
    // digitalWrite(enPin, LOW);

    push_start = millis();
    ref = true;
  }
  if (push_start != 0 && millis() - push_start >= 3000 && digitalRead(5) == LOW) {
    push_start = 0;
    dp.openCalibrationPage();
  }
  if (digitalRead(5) == HIGH && ref == true) {
    ref = false;
  }
  delay(1);
  yield();
  //receive_raspi();
  Pressr_RS485();

  if (dp.isPopupMusic()) {
    //read current mp3 file when popup music open
    if (millis() - longTimer1 > 1000) {
      read_mplayers2();
      longTimer1 = millis();
    }
  }


  if (dp.isCalibrateSensor()) {
    if (millis() - longTimer2 > 500) {
      sendDataSensor();
      longTimer2 = millis();
    }
  }


  //alarm
  if (dp.isAlarmBip() && millis() > 180000) {
    //reset milis
    if (rst == 1) {
      dp.setAlarmDelayDone(1);
      longTimerBzr = millis();
      alarmTimerCnt = 0;
      labelAlarmUpdate();
      rst = 0;
      Serial.println("resetAwal");
    }

    //milis per 2 detik untuk label dan snooze counter
    if (millis() - longTimer3 > 2000) {
      if (dp.isSnooze()) {
        snoozeCount++;
        Serial.println("snooze count : " + String(snoozeCount));
        if (snoozeCount == 30) {
          checkAlarm();
          popupAlarm(1);
          snoozeCount = 0;
          rst = 1;
        }
      } else labelAlarmUpdate();
      longTimer3 = millis();
    }

    // buzzer alarm sesuai waktu
    if (millis() - longTimerBzr > alarmTimerArr[alarmTimerCnt]) {
      if (alarmTimerCnt == 10) {
        longTimerBzr = millis();
        alarmTimerCnt = 0;
      } else {
        if (!dp.isSnooze()) dp.setBip(150);
        alarmTimerCnt++;
      }
    }
  } else {
    rst = 1;
    alarmTimerCnt = 0;
  }
  yield();
  if (millis() - waktu_update >= interval_update) {
    check_gas(data_O2_c, data_N2O_c, data_Air_c, int(data_Vacuum_c), true);
    waktu_update = millis();
  }

  //timer voip
  if (voip_callTimer) {
    if (millis() - longTimerVoip > 1000) {
      if (voip_callEnd == false) {
        voip_callTime++;
        voip_callTimejj = voip_callTime / 3600;
        voip_callTimemm = (voip_callTime % 3600) / 60;
        voip_callTimedd = (voip_callTime % 3600) % 60;

        if (voip_callTimejj == 0) {
          sprintf(voip_time, "%02d:%02d", voip_callTimemm, voip_callTimedd);
        } else {
          sprintf(voip_time, "%02d:%02d:%02d", voip_callTimejj, voip_callTimemm, voip_callTimedd);
        }

        lib_set_text("label", "label_v_callTime", voip_time);
        longTimerVoip = millis();
      } else {
        if (voip_status == VOIP_RINGING) {  //jika menunggu menutup, terdapat panggilan masuk. paksa untuk reset variabel
          voip_callEnd_close = 4;
        } else voip_callEnd_close++;
        longTimerVoip = millis();
        if (voip_callEnd_close > 4) {
          if (voip_status == VOIP_IDLE || voip_status == VOIP_ENDED) {  //jika status berubah, maka tidak menutup popup.
            lib_open_win("popup_voip", 0);
            if (play) df_player("start");
          }
          voip_callTimer = false;
          voip_callEnd = false;
          voip_callEnd_close = 0;
        }
      }
    }
  } else voip_callTime = 0;
  //sini
  delay(1);
}

void receive_raspi() {
  if (Serial1.available() > 0) {
    String cmd_baru;
    String cmd_data = Serial1.readStringUntil('\n');
    int pjg = cmd_data.length();
    Serial.printf("pjg data :%d\n", pjg);
    Serial.println(cmd_data);
    String ck = cmd_data.substring(0, 3);
    if (pjg > 5 && ck != "Wop") cmd_baru = cmd_data.substring(pjg - 5);
    else if (pjg == 5) cmd_baru = cmd_data;
    Serial.print("cmd baru: ");
    Serial.println(cmd_baru);
    if (ck == "Wop") {
      ad = 1;
      int tim = (cmd_data.substring(3)).toInt();
      int hour_ = tim / 3600;
      int minute_ = (tim % 3600) / 60;
      int second_ = (tim % 3600) % 60;
      lib_set_value("label", "label1_jam_waktu_operasi", String(hour_), "%02d");
      lib_set_value("label", "label1_menit_waktu_operasi", String(minute_), "%02d");
      lib_set_value("label", "label1_detik_waktu_operasi", String(second_), "%02d");
    }
    if (cmd_baru == "AnDon") {
      ad = 1;
      ans = false;
      timeout_an = 0;
      loop_an = false;
      //raspi = false;
      set_state_anastesi(true);
      lib_set_value("label", "label1_jam_waktu_anestesi", String(0), "%02d");
      lib_set_value("label", "label1_menit_waktu_anestesi", String(0), "%02d");
      lib_set_value("label", "label1_detik_waktu_anstesi", String(0), "%02d");
      lib_set_enable("butt_a_str", 1);
      lib_set_enable("butt_c_edt", 1);
      dp.set_state_counter(1, 0);
      _cnt = 0;
      // reset_anastetion();
      pref.begin("timer", false);
      pref.putInt("raspiAn", 0);
      pref.end();
    } else if (cmd_baru == "AnOke") {
      ad = 1;
      raspi = true;
      dp.loadingReset();
      ans = true;
      lib_set_enable("butt_a_str", 0);
      lib_set_enable("butt_c_edt", 0);
      dp.set_state_counter(1, 1);
      pref.begin("timer", false);
      pref.putInt("raspiAn", 1);
      pref.end();
    } else if (cmd_baru == "OpOke") {
      ad = 1;
      raspi = true;
      dp.loadingReset();
      ops = true;
      dp.set_state_counter(0, 1);
      _cnt = 1;

      pref.begin("timer", false);
      pref.putInt("raspiOp", 1);
      pref.end();
    } else if (cmd_baru == "OpRst") ops = false;
    else if (cmd_baru == "AnRst") ans = false;
    if (ops == false && ans == false) {
      raspi = false;
      ad = 0;
    }
  }
}

void Pressr_RS485() {
  if (Serial.available()) {
    String dataIN = "";
    String dataIN_New = "";
    bool _add = false;
    int i;

    dataIN = Serial.readStringUntil('\n');

    //RS485 voip
    if (dataIN[0] == 'S' && dataIN[1] == 'I' && dataIN[2] == 'P') {
      switch (dataIN[3]) {
        case 'T':
          {
            if (dataIN[4] == '0') {
              (bahasa == "english") ? lib_set_text("label", "label_st_regist", "Ethernet Disconnected") : lib_set_text("label", "label_st_regist", "Ethernet tidak terhubung");

              lib_set_bg_color("label_st_regis", 4294901760);
              lib_set_bg_image("button_m_voip", "tombol_phone_slashed");
              lib_set_bg_image("button_s_voip", "tombol_phone_slashed");
              lib_set_bg_image("button_c_voip", "tombol_phone_slashed");
              voip_ethernet_connected = false;
              voip_status = VOIP_DISCONNECT;
            } else {
              voip_ethernet_connected = true;
            }
          }
          break;

        case 'S':
          {
            if (voip_ethernet_connected) {
              if (dataIN[4] == '0') {
                voip_status = VOIP_DISCONNECT;
                (bahasa == "english") ? lib_set_text("label", "label_st_regist", "VoIP Register Failed") : lib_set_text("label", "label_st_regist", "Registrasi VoIP Gagal");
                lib_set_bg_color("label_st_regis", 4294901760);
                lib_set_bg_image("button_m_voip", "tombol_phone_slashed");
                lib_set_bg_image("button_s_voip", "tombol_phone_slashed");
                lib_set_bg_image("button_c_voip", "tombol_phone_slashed");

                // lib_set_enaVisi("button_v_resetVoip", 1);
              } else {
                if (voip_status == VOIP_DISCONNECT) voip_status = VOIP_IDLE;
                char _text[40];
                char _user[10];
                i = 4;
                do {
                  _user[i - 4] = dataIN[i];
                  i++;
                } while (dataIN[i] != ';');
                _user[i - 4] = '\0';

                (bahasa == "english") ? sprintf(_text, "VoIP Registered - %s", _user) : sprintf(_text, "VoIP Teregistrasi - %s", _user);
                lib_set_text("label", "label_st_regist", _text);
                lib_set_bg_color("label_st_regis", 4278227762);
                lib_set_bg_image("button_m_voip", "tombol_phone");
                lib_set_bg_image("button_s_voip", "tombol_phone");
                lib_set_bg_image("button_c_voip", "tombol_phone");
              }
            }
          }
          break;

        case 'C':
          {
            voip_status = VOIP_CALLING;
            lib_open_win("popup_voip", 1);
            if (play) df_player("pause");
            if (bahasa == "english") {
              lib_set_text("label", "label_popup_voipSetting_copy1_copy1_copy1", "    Calls");
            } else {
              lib_set_text("label", "label_popup_voipSetting_copy1_copy1_copy1", "    Panggilan");
            }
            lib_set_enaVisi("view_v_callin", 0);
            lib_set_enaVisi("view_v_call", 1);

            if (voip_volume == NULL) {
              pref.begin("voipRegister", true);
              voip_volume = pref.getInt("voip_vol", 80);
              pref.end();
            }
            setVolumeVoip(voip_volume / 10);

            char _calling[10];
            i = 4;
            do {
              _calling[i - 4] = dataIN[i];
              i++;
            } while (dataIN[i] != ';');
            _calling[i - 4] = '\0';

            Serial.printf("calling : %s", _calling);
            String contact = addressBookCheck(_calling);
            lib_set_text("label", "label_v_callerID_copy1", _calling);
            lib_set_text("label", "label_v_callName", contact);
            if (bahasa == "english") {
              lib_set_text("label", "label_v_callTime", "Calling...");
            } else {
              lib_set_text("label", "label_v_callTime", "Memanggil...");
            }
            voip_callReject = millis();
          }
          break;

        case 'I':
          {
            if (voip_status != VOIP_RINGING) {
              lib_open_win("popup_voip", 0);
              delay(10);
              lib_open_win("popup_voip", 1);
              if (play) df_player("pause");
              if (bahasa == "english") {
                lib_set_text("label", "label_popup_voipSetting_copy1_copy1", "    Incoming Call");
                lib_set_text("label", "label_v_incomingCall", "Incoming Call...");
              } else {
                lib_set_text("label", "label_popup_voipSetting_copy1_copy1", "    Panggilan Masuk");
                lib_set_text("label", "label_v_incomingCall", "Panggilan Masuk...");
              }
              lib_set_enaVisi("view_v_callin", 1);
              lib_set_enaVisi("view_v_call", 0);

              char _caller[10];
              i = 4;
              do {
                _caller[i - 4] = dataIN[i];
                i++;
              } while (dataIN[i] != ';');
              _caller[i - 4] = '\0';

              Serial.printf("calling : %s", _caller);
              String contact = addressBookCheck(_caller);

              lib_set_text("label", "label_v_callerID", _caller);
              lib_set_text("label", "label_v_callerID_copy1", _caller);
              lib_set_text("label", "label_v_callName", contact);
              lib_set_text("label", "label_v_callName_I", contact);
            }
          }
          voip_status = VOIP_RINGING;
          break;

        case 'Q':
          {
            if (dataIN[4] == 'B') {
              if (voip_status == VOIP_RINGING) {
                lib_set_enaVisi("view_v_callin", 0);
                lib_set_enaVisi("view_v_call", 1);
              }
              voip_status = VOIP_INCALL;
              voip_callEnd = false;
              voip_callTimer = true;
              lib_set_visible("label_v_callTime", 1);

              if (voip_volume == NULL) {
                pref.begin("voipRegister", true);
                voip_volume = pref.getInt("voip_vol", 80);
                pref.end();
              }
              setVolumeVoip(voip_volume / 10);
              if (bahasa == "english") {
                lib_set_text("label", "label_popup_voipSetting_copy1_copy1_copy1", "    Calls");
              } else {
                lib_set_text("label", "label_popup_voipSetting_copy1_copy1_copy1", "    Panggilan");
              }
            } else if (dataIN[4] == 'E') {
              voip_status = VOIP_ENDED;
              voip_callEnd = true;
              (bahasa == "english") ? lib_set_text("label", "label_v_callStatus", "Call Ended") : lib_set_text("label", "label_v_callStatus", "Panggilan Berakhir");
              lib_set_visible("button_v_callHangup", 0);
              lib_set_visible("view_v_vol", 0);
            }
          }
          break;

        case 'H':
          {
            if (voip_status == VOIP_RINGING) {
              voip_callTimer = true;
              voip_callEnd = true;
              (bahasa == "english") ? lib_set_text("label", "label_v_incomingCall", "Incoming Call Canceled") : lib_set_text("label", "label_v_incomingCall", "Panggilan Masuk Dibatalkan");
              lib_set_visible("button_v_call_accept", 0);
              lib_set_visible("button_v_call_decline", 0);
              voip_status = VOIP_IDLE;
            } else if (voip_status == VOIP_CANCEL) {
              voip_callTimer = true;
              voip_callEnd = true;
              (bahasa == "english") ? lib_set_text("label", "label_v_incomingCall", "Call Declined") : lib_set_text("label", "label_v_incomingCall", "Panggilan Ditolak");
              lib_set_visible("button_v_call_accept", 0);
              lib_set_visible("button_v_call_decline", 0);
              voip_status = VOIP_IDLE;
            } else if (voip_status == VOIP_CALLING) {
              voip_callTimer = true;
              voip_callEnd = true;
              (bahasa == "english") ? lib_set_text("label", "label_v_callTime", "Call Canceled") : lib_set_text("label", "label_v_callTime", "Panggilan Dibatalkan");
              lib_set_visible("button_v_callHangup", 0);
              lib_set_visible("view_v_vol", 0);
              voip_status = VOIP_IDLE;
            } else if (voip_status == VOIP_ENDED) {
              voip_status = VOIP_IDLE;
            }
          }
          break;

        case 'V':
          {
            char _vol[10];
            i = 4;
            do {
              _vol[i - 4] = dataIN[i];
              i++;
            } while (dataIN[i] != ';');
            _vol[i - 4] = '\0';

            voip_volume = atoi(_vol);
            pref.begin("voipRegister", false);
            pref.putInt("voip_vol", voip_volume);
            Serial.println(voip_volume);

            setVolumeVoip(voip_volume / 10);
          }
          break;

        case 'X':
          {
            if (voip_status == VOIP_CALLING) {
              rs485Send("SIPE;");
              voip_callTimer = true;
              voip_callEnd = true;
              lib_set_visible("button_v_callHangup", 0);
              lib_set_visible("view_v_vol", 0);
              if (millis() - voip_callReject > 1000) {
                (bahasa == "english") ? lib_set_text("label", "label_v_callTime", "Call Rejected") : lib_set_text("label", "label_v_callTime", "Panggilan Ditolak");
              } else (bahasa == "english") ? lib_set_text("label", "label_v_callTime", "Unregistered Number") : lib_set_text("label", "label_v_callTime", "Nomor Tidak Terdaftar");
              voip_callReject = 0;
              voip_status = VOIP_IDLE;
            }
          }
          break;
      }
    }



    int long_str = dataIN.length();
    if (long_str > 5) {
      Serial.print("dataIN : ");
      Serial.println(dataIN);
      for (int p = 0; p < long_str; p++) {
        if (dataIN[p] == 'S' || dataIN[p] == 'A') _add = true;
        if (_add) dataIN_New += dataIN[p];
        if (dataIN[p] == 'E' || dataIN[p] == 'N') _add = false;
      }
      // Serial.print("dataIN : ");
      // Serial.println(dataIN_New);

      int index = dataIN_New.indexOf(';');
      int index2 = dataIN_New.indexOf(';', index + 1);
      int index3 = dataIN_New.indexOf(';', index2 + 1);

      String data1 = dataIN_New.substring(1, index);
      String data2 = dataIN_New.substring(index + 1, index2);
      String data3 = dataIN_New.substring(index2 + 1, index3);
      String data4 = dataIN_New.substring(index3 + 1, long_str - 1);

      if (dataIN[0] == 'S' && dataIN[long_str - 1] == 'E') {

        if (data1.toInt() == 0) data_O2 = 0;
        else data_O2 = data1.toInt() / 100.0;  //ADC Value from Pressure O2 Sensor
        if (data2.toInt() == 0) data_N2O = 0;
        else data_N2O = data2.toInt() / 100.0;  //ADC Value from Pressure N2O Sensor
        if (data3.toInt() == 0) data_Air = 0;
        else data_Air = data3.toInt() / 100.0;  //ADC Value from Pressure CO2 Sensor
        data_Vacuum = data4.toInt() * -1.00;    //ADC Value from Pressure udara Sensor


        data_O2_c = calibrationStart(1, data_O2 * 1.0);
        data_N2O_c = calibrationStart(0, data_N2O * 1.0);
        data_Air_c = calibrationStart(2, data_Air * 1.0);
        data_Vacuum_c = calibrationStart(3, data_Vacuum * 1.0);

        if (dp.getsTates() != 1) gas_update(data_O2_c, data_N2O_c, data_Air_c, data_Vacuum_c);
      }

      else if (dataIN[0] == 'A' && dataIN[long_str - 1] == 'N') {
        temp = data1.toInt() / 100.0;    //ADC Value from Pressure O2 Sensor
        humid = data2.toInt() / 100.0;   //ADC Value from Pressure N2O Sensor
        pressU = data3.toInt() / 100.0;  //ADC Value from Pressure CO2 Sensor
        co2_ = data4.toInt();            //ADC Value from Pressure udara Sensor

        temp_c = calibrationStart(4, temp);
        humid_c = calibrationStart(5, humid);

        if (dp.getsTates() != 1) ambient_update(temp_c * 1.0, humid_c * 1.0, pressU * 1.0, co2_ * 1.0);
      }
    }
  }
}

void op_proc() {
  //if(cpy_stat != 2)
  //Serial.printf("key : %d\n", keys);
  if (keys == 0) second_of_timeOperation = ((millis() - dp.getOpVal()) / 1000) - var_op;
  else if (keys == 2) {
    second_of_timeOperation += ((millis() - dp.getOpVal()) / 1000);
    keys = 1;
  } else {
    second_of_timeOperation = var_lock + ((millis() - dp.getOpVal()) / 1000);
    keys = 1;
  }
  int op_hour = second_of_timeOperation / 3600;
  int op_minute = (second_of_timeOperation % 3600) / 60;
  int op_second = (second_of_timeOperation % 3600) % 60;

  lib_set_value("label", "label1_jam_waktu_operasi", String(op_hour), "%02d");
  lib_set_value("label", "label1_menit_waktu_operasi", String(op_minute), "%02d");
  lib_set_value("label", "label1_detik_waktu_operasi", String(op_second), "%02d");

  if (op_hour >= 100) {
    timerOp_forceStop();
  }
}

void an_proc() {

  unsigned long int anastetion_start = dp.getAnVal();
  int anastetionTime = dp.getAnastetionTime() + var_an;
  second_of_Anastetion = (anastetionTime - (millis() - anastetion_start) / 1000) + savedAnTime;
  if (anastetionTime < (millis() - anastetion_start) / 1000) second_of_Anastetion = 0;
  int an_hour = second_of_Anastetion / 3600;
  int an_minute = (second_of_Anastetion % 3600) / 60;
  int an_second = (second_of_Anastetion % 3600) % 60;
  if (ct_an < 5) {
    Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"butt_a_str\",\"enable\":false}>ET"));
    delay(10);
    Serial.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"butt_a_str\",\"enable\":false}>ET"));
  }

  lib_set_value("label", "label1_jam_waktu_anestesi", String(an_hour), "%02d");
  lib_set_value("label", "label1_menit_waktu_anestesi", String(an_minute), "%02d");
  lib_set_value("label", "label1_detik_waktu_anstesi", String(an_second), "%02d");

  if (second_of_Anastetion <= 0) {
    ct_an = 0;
    Serial.printf("sm_tmr : %d\n", dp.getState_timer_an());
    // cpy_stat = 0;
    //second_of_Anastetion = 0;
    //anastetion_start =0;
    timeout_an = 0;
    an_hour = 0;
    an_minute = 0;
    an_second = 0;
    first = 0;

    savedAnTime = 0;
    pref.begin("timer", false);
    pref.putInt("isAnRun", 0);
    pref.putInt("raspiAn", 0);
    pref.end();

    lib_set_enable("butt_a_str", 1);
    delay(10);
    lib_set_value("edit", "edit_jams", String(an_hour), "%02d");
    lib_set_value("edit", "edit_fmnt", String(an_minute), "%02d");
    lib_set_value("edit", "edit_gdtk", String(an_second), "%02d");
    lib_set_enable("butt_c_edt", 1);
    stlcd = false;
    dp.savestlcd(stlcd);
    reset_anastetion();
    loop_an = false;
  }
  ct_an++;
}

void checkRTC(void) {
  pref.begin("timer", false);
  if (pref.getInt("isOpRun", 0) == 1) {  //jika kondisi saat booting timer berjalan
    int rtcStartTime = pref.getInt("startRTC");
    DateTime now = RTC.now();
    int rtcCurrentTime = now.unixtime();
    savedOpTime = pref.getInt("RTCsavedTime", 0);

    int selisih = rtcCurrentTime - rtcStartTime;
    savedOpTime = savedOpTime + selisih;
    var_lock = savedOpTime;

    pref.putInt("RTCsavedTime", savedOpTime);
    pref.putInt("startRTC", rtcCurrentTime);
    startRTC = rtcCurrentTime;

    setButtonOp();

    keys = 1;
    stlcd = true;
    dp.savestlcd(stlcd);

    Serial.print("saved operasi time   : ");
    Serial.println(savedOpTime);

  } else if (pref.getInt("RTCsavedTime", 0) > 0) {  //jika timer mati tapi ada waktu tersimpan (paused)
    var_lock = pref.getInt("RTCsavedTime", 0);
    keys = 1;
    stlcd = true;
    dp.savestlcd(stlcd);
    savevar_lock(var_lock);

    Serial.println("timer op paused");
    Serial.print("saved var_lock   : ");
    Serial.println(var_lock);

  } else Serial.println("no saved op time");

  if (pref.getInt("isAnRun", 0) == 1) {  //jika timer anastesi jalan saat boot
    int rtcStartTimeAn = pref.getInt("startAnRTC");
    DateTime now = RTC.now();
    int rtcCurrentTime = now.unixtime();
    savedAnTime = pref.getInt("RTCsavedTime", 0); //Tes

    savedAnTime = rtcStartTimeAn - rtcCurrentTime;
    pref.putInt("RTCsavedTime", savedAnTime);  // Simpan ke preferensi

    Serial.print("saved anastesi time  : ");
    Serial.println(savedAnTime);

    setButtonAn();

    stlcd = true;
    dp.savestlcd(stlcd);

  } else 
    Serial.println("no saved an time");

  if (pref.getInt("raspiOp", 0) == 1) {
    Serial.println("Op time Raspi : on");
    raspi = true;
    ops = true;
    //set button op
    setButtonOp();
  } else 
    Serial.println("Op time Raspi : off");

  if (pref.getInt("raspiAn", 0) == 1) {
    Serial.println("An time Raspi : on");
    raspi = true;
    ans = true;
    //set button an
    setButtonAn();
  } else 
    Serial.println("An time Raspi : off");

  if (pref.getInt("raspiOp", 0) == 0 && pref.getInt("raspiAn", 0) == 0) {
    raspi = false;
  }
  pref.end();
}

void sendDataSensor() {
  int sensorNumber = dp.getSensorNumber();
  switch (sensorNumber) {
    case 0:  //sensor tekanan N2O
      dp.saveSensorData(data_N2O);
      break;
    case 1:  //sensor tekanan 02
      dp.saveSensorData(data_O2);
      break;
    case 2:  //sensor tekanan udara
      // dp.saveSensorData(random(2100, 3100) / 100.00);
      dp.saveSensorData(data_Air);
      break;
    case 3:  //sensor vakum
      dp.saveSensorData(data_Vacuum);
      break;
    case 4:  //sensorSuhu
      dp.saveSensorData(temp);
      break;
    case 5:
      dp.saveSensorData(humid);
      break;
  }
}

void print_reset_reason(RESET_REASON reason) {
  switch (reason) {
    case 1: Serial.println("POWERON_RESET"); break;           /**<1, Vbat power on reset*/
    case 3: Serial.println("SW_RESET"); break;                /**<3, Software reset digital core*/
    case 4: Serial.println("OWDT_RESET"); break;              /**<4, Legacy watch dog reset digital core*/
    case 5: Serial.println("DEEPSLEEP_RESET"); break;         /**<5, Deep Sleep reset digital core*/
    case 6: Serial.println("SDIO_RESET"); break;              /**<6, Reset by SLC module, reset digital core*/
    case 7: Serial.println("TG0WDT_SYS_RESET"); break;        /**<7, Timer Group0 Watch dog reset digital core*/
    case 8: Serial.println("TG1WDT_SYS_RESET"); break;        /**<8, Timer Group1 Watch dog reset digital core*/
    case 9: Serial.println("RTCWDT_SYS_RESET"); break;        /**<9, RTC Watch dog Reset digital core*/
    case 10: Serial.println("INTRUSION_RESET"); break;        /**<10, Instrusion tested to reset CPU*/
    case 11: Serial.println("TGWDT_CPU_RESET"); break;        /**<11, Time Group reset CPU*/
    case 12: Serial.println("SW_CPU_RESET"); break;           /**<12, Software reset CPU*/
    case 13: Serial.println("RTCWDT_CPU_RESET"); break;       /**<13, RTC Watch dog Reset CPU*/
    case 14: Serial.println("EXT_CPU_RESET"); break;          /**<14, for APP CPU, reseted by PRO CPU*/
    case 15: Serial.println("RTCWDT_BROWN_OUT_RESET"); break; /**<15, Reset when the vdd voltage is not stable*/
    case 16: Serial.println("RTCWDT_RTC_RESET"); break;       /**<16, RTC Watch dog reset digital core and rtc module*/
    default: Serial.println("NO_MEAN");
  }
}