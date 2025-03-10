#include "stone.h"
#include "stone_config.h"
#include "data_parse.h"
#include "pin_config.h"
#include "update_halaman.h"
#include <Preferences.h>
#include "Wire.h"

Preferences preferences;
stone_data dta;
edit_data ed;
int vol_music = 50;
int js = 0;
int jeda = 0;
bool isPopup = 0;

int slidvalue;
int volume_music;
int stat_player;
int track = 1;
int count_play = 0;
extern bool play;
String bahasa_c;
String bahasa_c_cpy;
String bahasa_d;
String bahasa_d_cpy;
int st_tmr;
int st_tmr_an;
int day_;
int hour_;
int minute_;
int second_;
unsigned long int start_waktu = 0;
unsigned char times;
unsigned int password = 123456;
unsigned int password_calibration = 654321;
String bhs;
String bhs_cpy;
int jam_anastesi;
int menit_anastesi;
int detik_anastesi;
bool state_start_op = false;
unsigned long val_start_op = 0;
unsigned long val_start_op_rtc = 0;
unsigned long int op_detik = 0;
int jam_op = 0;
int menit_op = 0;
int detik_op = 0;
String title = "";
String title_cpy = "Track";
char t_music[10];
uint32_t kuning = 4293579568;
uint32_t hijau = 4278227762;
uint32_t merah = 4294901760;

int inc = 0;
int c_op = 0;

int atur_tanggal = 0;
int atur_bulan = 0;
int atur_tahun = 0;
int atur_jam = 0;
int atur_menit = 0;
int atur_kode = 0;
int t_mode = 0;

int status_temperature;
int status_humidity;
int status_co2;
int status_temperature_cpy = 3;
int status_humidity_cpy = 3;
int status_co2_cpy = 3;

float g_o2;
float g_n2o;
float g_air;
float g_vacum;

float g_o2_cpy;
float g_n2o_cpy;
float g_air_cpy;
float g_vacum_cpy;

float ambient_temp = 0;
float ambient_humid = 0;
float ambient_press = 0;
int ambient_co2 = 0;

float ambient_temp_cpy = 0;
float ambient_humid_cpy = 0;
float ambient_press_cpy = 0;
int ambient_co2_cpy = 0;

int min_N2O;
int max_N2O;
int min_O2;
int max_O2;
int min_Air;
int max_Air;
int min_Vacum = 0;
int max_Vacum = 0;
int min_Vacums = 0;
int max_Vacums = 0;

int min_Temp;

int max_Temp;

int min_Humid = 0;
int max_Humid = 0;
int kecerahan;

int volume;
int DFVolume = 15;
unsigned long int timerUpdateVolume = 0;

int stat_O2;
int stat_N2O;
int stat_Udara;
int stat_Vakum;

int stat_O2_cpy = 3;
int stat_N2O_cpy = 3;
int stat_Udara_cpy = 3;
int stat_Vakum_cpy = 3;

extern String bahasa;
String bahasa_cpy;
String room;
String room_cpy;

String str_jamAn;
String str_menAn;
String str_detAn;

int hal1 = 0;
int halCtr = 0;
int halSett = 0;

bool state_start_an = false;
bool st_ctrl = false;
unsigned long val_start_an = 0;
unsigned long int anes_detik = 0;
unsigned long int an_detik = 0;
int jam_an = 0;
int menit_an = 0;
int detik_an = 0;

//variabel RTC
int RTCsavedTime = 0;
int opVarLock = 0;

int data;

bool sw1, sw2, sw3, sw4, sw5, sw6, sw7;

//variabel voip
String numberKey = "";
bool voip_viewConfig = false;
int voip_callNumber;
extern int voip_status;
extern int voip_volume;
char voip_register_uri[100];
String voip_register_id = "";
String voip_register_pass = "";
String voip_register_serverIp = "";
String voip_addressBook[20][2] = { { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" }, { "", "" } };
bool addcontact = false;
bool deleteMode = false;
bool addMode = false;
bool contactEdited = true;
int contactIdx[20];
int voip_editIdx;

//variabel iot
int iotStatus = 0;
int iotStatus_cpy = 0;
String wifiSsid;
String wifiPass;
int passVisible = 0;
unsigned long int iotStatusUpdate_startMillis = 0;
int iotStatusUpdate_once = 0;
int wiredata1;

//variabel alarm
bool isAlarm = 0;
bool snooze = 0;
bool alarmEnable;
bool alarmDelayDone = false;
String labelPopupAlarm1[7] = { "", "", "", "", "", "", "" };
String labelPopupAlarm2[7] = { "", "", "", "", "", "", "" };
int idxLabelAlarm = 0;
int idxLabelAlarmNow = 0;

//variabel untuk kalibrasi
int sensorID;
int jumlahSample;
int kalibrasiState = 0;
bool isCalibrate = 0;
float currentSensorRead;
float inpRef;
float refTolerance;
String labelSatuan;

float refDataArr[11];
float senDataArr[11];

String labelReferensi11[] = { "label_ref0_copy1", "label_ref1_copy1", "label_ref2_copy1", "label_ref3_copy1", "label_ref4_copy1", "label_ref5_copy1", "label_ref6_copy1", "label_ref7_copy1", "label_ref8_copy1", "label_ref9_copy1", "label_ref10_copy1" };
String labelSensor11[] = { "label_nilaiSensor0_copy1", "label_nilaiSensor1_copy1", "label_nilaiSensor2_copy1", "label_nilaiSensor3_copy1", "label_nilaiSensor4_copy1", "label_nilaiSensor5_copy1", "label_nilaiSensor6_copy1", "label_nilaiSensor7_copy1", "label_nilaiSensor8_copy1", "label_nilaiSensor9_copy1", "label_nilaiSensor10_copy1" };
String labelReferensi4[] = { "label_ref0_copy2", "label_ref1_copy2", "label_ref2_copy2", "label_ref3_copy2" };
String labelSensor4[] = { "label_nilaiSensor0_copy2", "label_nilaiSensor1_copy2", "label_nilaiSensor2_copy2", "label_nilaiSensor3_copy2" };
String labelReferensi6[] = { "label_ref0", "label_ref1", "label_ref2", "label_ref3", "label_ref4", "label_ref5" };
String labelSensor6[] = { "label_nilaiSensor0", "label_nilaiSensor1", "label_nilaiSensor2", "label_nilaiSensor3", "label_nilaiSensor4", "label_nilaiSensor5" };

String labelReferensi11e[] = { "label_11ref0", "label_11ref1", "label_11ref2", "label_11ref3", "label_11ref4", "label_11ref5", "label_11ref6", "label_11ref7", "label_11ref8", "label_11ref9", "label_11ref10" };
String labelSensor11e[] = { "label_11sensor0", "label_11sensor1", "label_11sensor2", "label_11sensor3", "label_11sensor4", "label_11sensor5", "label_11sensor6", "label_11sensor7", "label_11sensor8", "label_11sensor9", "label_11sensor10" };
String labelReferensi4e[] = { "label_4ref0", "label_4ref1", "label_4ref2", "label_4ref3" };
String labelSensor4e[] = { "label_4sensor0", "label_4sensor1", "label_4sensor2", "label_4sensor3" };
String labelReferensi6e[] = { "label_6ref0", "label_6ref1", "label_6ref2", "label_6ref3", "label_6ref4", "label_6ref5" };
String labelSensor6e[] = { "label_6sensor0", "label_6sensor1", "label_6sensor2", "label_6sensor3", "label_6sensor4", "label_6sensor5" };

int sampleN2O;
float refDataN2O[11];
float senDataN2O[11];

int sampleO2;
float refDataO2[11];
float senDataO2[11];

int sampleAIR;
float refDataAIR[11];
float senDataAIR[11];

int sampleVakum;
float refDataVakum[11];
float senDataVakum[11];

int sampleSuhu;
float refDataSuhu[11];
float senDataSuhu[11];

int sampleHumidity;
float refDataHumidity[11];
float senDataHumidity[11];

bool statelcd = false;
extern bool raspi;

void parse_begin() {
  preferences.begin("setting", false);
  bahasa = preferences.getString("bahasa", "indonesia");
  kecerahan = preferences.getInt("Kecerahan", 20);
  volume = preferences.getInt("Volume", 20);
  room = preferences.getString("room", "");
  preferences.end();
  room_cpy = room;
  bahasa_cpy = bahasa;
  bhs = bahasa;
  bhs_cpy = bahasa;
  (bahasa == "english") ? lib_set_text("label", "label_hal_login", "Home Page") : lib_set_text("label", "label_hal_login", "Halaman Depan");
  if (bahasa == "english") stone_println(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"radio_button\",\"widget\":\"rdio_eng_\",\"value\":true}>ET"));
  else stone_println(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"radio_button\",\"widget\":\"rdio_indo\",\"value\":true}>ET"));
  if (halCtr < 1) set_bahasa(bahasa);
  lib_set_text("edit", "editroom", room);
  setkecerahan(kecerahan);
  iotStatusUpdate();

  stone_print(F("ST<{\"cmd_code\":\"set_brightness\",\"type\":\"system\",\"brightness\":"));
  stone_print(kecerahan);
  stone_println(F("}>ET"));
  stone_print(F("ST<{\"cmd_code\":\"set_vol\",\"type\":\"system\",\"vol\":"));
  stone_print(volume);
  stone_println(F("}>ET"));
  sdebug_print(F("ST<{\"cmd_code\":\"set_brightness\",\"type\":\"system\",\"brightness\":"));
  sdebug_print(kecerahan);
  sdebug_println(F("}>ET"));
  sdebug_print(F("ST<{\"cmd_code\":\"set_vol\",\"type\":\"system\",\"vol\":"));
  sdebug_print(volume);
  sdebug_println(F("}>ET"));

  preferences.begin("control", false);
  sw1 = preferences.getBool("SW1", false);
  sw2 = preferences.getBool("SW2", false);
  sw3 = preferences.getBool("SW3", false);
  sw4 = preferences.getBool("SW4", false);
  sw5 = preferences.getBool("SW5", false);
  sw6 = preferences.getBool("SW6", false);
  sw7 = preferences.getBool("SW7", false);

  alarmEnable = preferences.getBool("alarmEnable", false);
  Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch8000000\",\"value\":"));
  Serial2.print(alarmEnable ? "true" : "false");
  Serial2.println(F("}>ET"));

  //preferences.putInt("minVacum", -100);
  // preferences.putInt("minVacum", max_Vacum);
  max_N2O = preferences.getInt("maxN2O", 5);
  min_N2O = preferences.getInt("minN2O", 2);
  max_O2 = preferences.getInt("maxO2", 5);
  min_O2 = preferences.getInt("minO2", 2);
  max_Air = preferences.getInt("maxAir", 5);
  min_Air = preferences.getInt("minAir", 2);
  max_Vacum = preferences.getInt("maxVacum", -400);
  min_Vacum = preferences.getInt("minVacum", -200);
  max_Temp = preferences.getInt("maxTemp", 24);
  min_Temp = preferences.getInt("minTemp", 19);
  max_Humid = preferences.getInt("maxHumid", 60);
  min_Humid = preferences.getInt("minHumid", 50);
  Serial.printf("max_N2O : %d, max_N2O : %d\nmaxO2 : %d, min_O2 ; %d\nmax_Air : %d, min_Air : %d\nmin_Vacum : %d,max_Vacum : %d\nmax_Temp : %d, min_Temp : %d\n max_Humid : %d, min_Humid : %d\n", max_N2O, min_N2O, max_O2, min_O2, max_Air, min_Air, min_Vacum, max_Vacum, max_Temp, min_Temp, max_Humid, min_Humid);
  preferences.end();
  delay(100);

  relay_setup();
  addressBookLoad();
}

void pref_send(bool pref) {
  //switch alarm
  if (pref) {
    delay(50);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch8000000\",\"value\":"));
    Serial2.print(alarmEnable ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);

    //switch relay
    delay(20);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch1000000\",\"value\":"));
    Serial2.print(sw1 ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch2000000\",\"value\":"));
    Serial2.print(sw2 ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch3000000\",\"value\":"));
    Serial2.print(sw3 ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch4000000\",\"value\":"));
    Serial2.print(sw4 ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch5000000\",\"value\":"));
    Serial2.print(sw5 ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch6000000\",\"value\":"));
    Serial2.print(sw6 ? "true" : "false");
    Serial2.println(F("}>ET"));
    delay(200);
    Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"switch\",\"widget\":\"swtch7000000\",\"value\":"));
    Serial2.print(sw7 ? "true" : "false");
    Serial2.println(F("}>ET"));
  }
  delay(20);
  lib_set_value("label", "label_min_N2O", String(min_N2O), "%d");
  delay(100);
  lib_set_value("label", "label_max_N2O", String(max_N2O), "%d");
  delay(100);
  lib_set_value("label", "label_min_o2", String(min_O2), "%d");
  delay(100);
  lib_set_value("label", "label_max_o2", String(max_O2), "%d");
  delay(100);
  lib_set_value("label", "label_min_air", String(min_Air), "%d");
  delay(100);
  lib_set_value("label", "label_max_air", String(max_Air), "%d");
  delay(100);
  lib_set_value("label", "label_min_vakum", String(min_Vacum), "%d");
  delay(100);
  lib_set_value("label", "label_max_vakum", String(max_Vacum), "%d");
  delay(100);
  lib_set_value("label", "label_min_temp", String(min_Temp), "%d");
  delay(100);
  lib_set_value("label", "label_max_temp", String(max_Temp), "%d");
  delay(100);
  lib_set_value("label", "label_min_humidity", String(min_Humid), "%d");
  delay(100);
  lib_set_value("label", "label_max_humidity", String(max_Humid), "%d");
  delay(100);
  lib_set_value("label", "label_min_N2O", String(min_N2O), "%d");
  delay(100);
  lib_set_value("label", "label_max_N2O", String(max_N2O), "%d");
  delay(100);
  lib_set_value("label", "label_min_o2", String(min_O2), "%d");
  delay(100);
  lib_set_value("label", "label_max_o2", String(max_O2), "%d");
  delay(100);
  lib_set_value("label", "label_min_air", String(min_Air), "%d");
  delay(100);
  lib_set_value("label", "label_max_air", String(max_Air), "%d");
  delay(100);
  lib_set_value("label", "label_min_vakum", String(min_Vacum), "%d");
  delay(100);
  lib_set_value("label", "label_max_vakum", String(max_Vacum), "%d");
  delay(100);
  lib_set_value("label", "label_min_temp", String(min_Temp), "%d");
  delay(100);
  lib_set_value("label", "label_max_temp", String(max_Temp), "%d");
  delay(100);
  lib_set_value("label", "label_min_humidity", String(min_Humid), "%d");
  delay(100);
  lib_set_value("label", "label_max_humidity", String(max_Humid), "%d");
  /* yield();

    lib_set_value("edit", "edit_0N2O", String(min_N2O), "%d");
    delay(200);
    lib_set_value("edit", "edit_1N2O", String(max_N2O), "%d");
    delay(200);
    lib_set_value("edit", "edit_2O2_", String(min_O2), "%d");
    delay(200);
    lib_set_value("edit", "edit_3O2_", String(max_O2), "%d");
    delay(200);
    lib_set_value("edit", "edit_4air", String(min_Air), "%d");
    delay(200);
    lib_set_value("edit", "edit_5air", String(max_Air), "%d");
    delay(200);
    lib_set_value("edit", "edit_6Vkm", String(min_Vacum), "%d");
    delay(200);
    lib_set_value("edit", "edit_7Vkm", String(max_Vacum), "%d");
    delay(200);
    lib_set_value("edit", "edit_8tem", String(min_Temp), "%d");
    delay(200);
    lib_set_value("edit", "edit_9tem", String(max_Temp), "%d");
    delay(200);
    lib_set_value("edit", "edit_bhum", String(max_Humid), "%d");
    delay(200);
    lib_set_value("edit", "edit_ahum", String(min_Humid), "%d");*/
}

void do_parse() {
  String type__ = dta.getType();
  String widget = dta.getWidget();
  String vals = dta.getValue();
  String TimeVal = dta.getTime();
  String editTextData = ed.getEditTextData();
  int val_int = vals.toInt();
  float val_float = atof(vals.c_str());

  Serial.printf("type = %s widget = %s vals = %s val_int = %d val_float = %f\n", type__.c_str(), widget.c_str(), vals.c_str(), val_int, val_float);


  if (type__ == "button") {
    if (widget == "button_login1") {
      if (hal1 < 1) {
        // update_monitor_page(bahasa);
        set_bahasa(bahasa);
        // lib_set_text("label", "label1_sub_hal1", "Ruang Operasi " + room);
        lib_set_value("label", "label1_nilai_tekanan_o2", String(g_o2), "%.2f");
        lib_set_value("label", "label1_nilai_tekanan_n2o", String(g_n2o), "%.2f");
        lib_set_value("label", "label1_nilai_tekanan_udara", String(g_air), "%.2f");
        lib_set_value("label", "label1_nilai_tekanan_vacuum", String(g_vacum), "%d");
        lib_set_value("label", "label1_nilai_suhu", String(ambient_temp), "%.2f");
        lib_set_value("label", "label_nilai_tekanan_ruangan", String(ambient_press), "%.2f");
        lib_set_value("label", "label1_nilai_kelembapan", String(ambient_humid), "%.2f");
        lib_set_value("label", "label_nilai_co2", String(ambient_co2), "%d");
        status_update();
        button_timer_update();
        iotStatusUpdate(1);
        //read_allSensor();
      }
      hal1++;
    } else if (widget == "button_m_set2" || widget == "button_c_set2") {
      jeda = 0;
      iotStatusUpdate(1);
      lib_set_text("edit", "editroom", room);
      if (bahasa == "english") stone_println(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"radio_button\",\"widget\":\"rdio_eng_\",\"value\":true}>ET"));
      else stone_println(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"radio_button\",\"widget\":\"rdio_indo\",\"value\":true}>ET"));
      if (halSett < 1) {
        setkecerahan(kecerahan);
        update_setting_page(bahasa.c_str());
      }
      halSett++;
    } else if (widget == "butt_Gsav") {
      if (jam_anastesi < 10) str_jamAn = "0" + String(jam_anastesi);
      else str_jamAn = String(jam_anastesi);
      if (menit_anastesi < 10) str_menAn = "0" + String(menit_anastesi);
      else str_menAn = String(menit_anastesi);
      if (detik_anastesi < 10) str_detAn = "0" + String(detik_anastesi);
      else str_detAn = String(detik_anastesi);
      String torp = "An" + str_jamAn + "j" + str_menAn + "m" + str_detAn + "d";
      Serial1.print(torp.c_str());
      lib_set_value("label", "label1_jam_waktu_anestesi", String(jam_anastesi), "%02d");
      lib_set_value("label", "label1_menit_waktu_anestesi", String(menit_anastesi), "%02d");
      lib_set_value("label", "label1_detik_waktu_anstesi", String(detik_anastesi), "%02d");
      an_detik = jam_anastesi * 3600 + menit_anastesi * 60 + detik_anastesi;
      preferences.begin("timer", false);
      preferences.putInt("anSavedTime", an_detik);
      preferences.end();

    } else if (widget == "butt_a_str") {
      if (state_start_an == false) {
        lib_set_enable("butt_a_str", 0);
        lib_set_enable("butt_c_edt", 0);
        st_tmr_an = 1;
        val_start_an = millis();
        state_start_an = true;

        if (statelcd == false) Serial1.print("AnStart");
        lib_set_enable("butt_a_str", 0);
        lib_set_enable("butt_c_edt", 0);

      } else {
        lib_set_enable("butt_a_str", 1);
        lib_set_enable("butt_c_edt", 1);

        state_start_an = false;
      }
    } else if (widget == "butt_b_rst") {
      st_tmr_an = 0;
      val_start_an = 0;
      jam_anastesi = 0;
      menit_anastesi = 0;
      detik_anastesi = 0;

      preferences.begin("timer, false");
      preferences.putInt("raspiAn", 0);
      preferences.end();

      lib_set_enable("butt_a_str", 1);
      lib_set_enable("butt_c_edt", 1);

      if (statelcd == false) Serial1.print("AnReset");

      lib_set_value("label", "label1_jam_waktu_anestesi", String(jam_anastesi), "%02d");
      lib_set_value("label", "label1_menit_waktu_anestesi", String(menit_anastesi), "%02d");
      lib_set_value("label", "label1_detik_waktu_anstesi", String(detik_anastesi), "%02d");

      lib_set_value("edit", "edit_jams", String(jam_anastesi), "%02d");
      lib_set_value("edit", "edit_fmnt", String(menit_anastesi), "%02d");
      lib_set_value("edit", "edit_gdtk", String(detik_anastesi), "%02d");

      preferences.begin("timer", false);
      preferences.putInt("state_an", 0);
      preferences.end();

    } else if (widget == "butt_c_edt") {
      if (bahasa == "english") update_anastesi_pop_up(bahasa.c_str());
    } else if (widget == "butt_d_str") {
      if (state_start_op == false) {  //tombol start

        set_button_startstop("stop");
        lib_set_enable("butt_e_rst", 0);

        st_tmr = 1;
        val_start_op = millis();

        state_start_op = true;
        /*if(c_op <1 || t_mode == 1)*/
        if (statelcd == false) {
          Serial1.print("OpStart");
          lib_set_value("label", "label1_jam_waktu_operasi", "0", "%02d");
          lib_set_value("label", "label1_menit_waktu_operasi", "0", "%02d");
          lib_set_value("label", "label1_detik_waktu_operasi", "0", "%02d");
        }
      }


    } else if (widget == "butt_d_stp") {
      if (state_start_op == true) {  //tombol stop
        val_start_op = 0;
        st_tmr = 2;

        set_button_startstop("start");
        bahasa == "english" ? lib_set_text("button", "butt_d_str", "START") : lib_set_text("button", "butt_d_str", "MULAI");

        lib_set_enable("butt_e_rst", 1);

        state_start_op = false;

        if (statelcd == false) {
          Serial1.print("OpStop");
          Serial.println("OpStop");
          delay(1000);

          if (!Serial1.available()) {  // if no response, reset
            Serial.println("no resp");
            st_tmr = 0;
            val_start_op = 0;
            jam_op = 0;
            menit_op = 0;
            detik_op = 0;

            preferences.begin("timer, false");
            preferences.putInt("raspiOp", 0);
            preferences.end();

            lib_set_value("label", "label1_jam_waktu_operasi", String(jam_op), "%02d");
            lib_set_value("label", "label1_menit_waktu_operasi", String(menit_op), "%02d");
            lib_set_value("label", "label1_detik_waktu_operasi", String(detik_op), "%02d");
          }
          // raspi = false;
        }
      }
    } else if (widget == "butt_e_rst") {
      if (state_start_op == true) {
        set_button_startstop("start");
        bahasa == "english" ? lib_set_text("button", "butt_d_str", "START") : lib_set_text("button", "butt_d_str", "MULAI");
        state_start_op = false;
      }

      st_tmr = 0;
      val_start_op = 0;
      jam_op = 0;
      menit_op = 0;
      detik_op = 0;

      preferences.begin("timer, false");
      preferences.putInt("raspiOp", 0);
      preferences.end();

      if (statelcd == false) Serial1.print("OpReset");
      lib_set_value("label", "label1_jam_waktu_operasi", String(jam_op), "%02d");
      lib_set_value("label", "label1_menit_waktu_operasi", String(menit_op), "%02d");
      lib_set_value("label", "label1_detik_waktu_operasi", String(detik_op), "%02d");

      //close loading view
      lib_set_visible("view_timeoutWait", 0);
      lib_set_visible("loading1", 0);
      lib_set_visible("loading2", 0);
      lib_set_visible("loading3", 0);
      lib_set_visible("loading4", 0);
      lib_set_visible("loading5", 0);
    } else if (widget == "butt_Jsav") {
      if (atur_tanggal > 30) {
        if (atur_bulan == 4 || atur_bulan == 6 || atur_bulan == 9 || atur_bulan == 11) atur_tanggal = 30;
        else if (atur_bulan == 2 && atur_tahun % 4 == 0) atur_tanggal = 29;
        else if (atur_bulan == 2 && atur_tahun % 4 != 0) atur_tanggal = 28;
      }
      lib_set_value("edit", "edit_date", String(atur_tanggal), "%d");
      lib_set_value("edit", "edit_mont", String(atur_bulan), "%d");
      lib_set_value("edit", "edit_year", String(atur_tahun), "%d");

      set_date_time(atur_tahun, atur_bulan, atur_tanggal, atur_jam, atur_menit);
    } else if (widget == "butt_g_sv") {
      lib_open_win("popup4", 1);
      if (bahasa == "english") lib_set_text("label", "label16", "Please Wait");
      else lib_set_text("label", "label16", "Silahkan Tunggu");
      lib_set_visible("label17", 1);
      lib_set_visible("label17_copy3", 1);
      preferences.begin("setting", false);
      if (bahasa_cpy != bahasa) {
        bhs = bahasa;
        bahasa_c = bhs;
        bahasa_d = bhs;
        set_bahasa(bahasa);
        delay(100);
        set_bahasa(bahasa);
        //preferences.begin("setting", false);
        preferences.putString("bahasa", bahasa);
        //preferences.end();
      }
      room = ed.getRoom();
      Serial.println(room);
      if (room != room_cpy) {
        lib_set_text("edit", "editroom", room);
        bahasa == "english" ? lib_set_text("label", "label1_sub_hal1", room + " Operating Room") : lib_set_text("edit", "label1_sub_hal1", "Ruang Operasi " + room);

        preferences.putString("room", room);
      }
      if (room != room_cpy || bahasa_cpy != bahasa) {
        lib_set_visible("label17", 0);
        lib_set_visible("label17_copy3", 0);
        if (bahasa == "english") lib_set_text("label", "label16", "Sucessfully Update");
        else lib_set_text("label", "label16", "Berhasil Memperbarui");
        delay(3000);
      }

      room_cpy = room;
      bahasa_cpy = bahasa;
      preferences.end();
      lib_open_win("popup4", 0);
    } else if (widget == "butt_Oke") {
      String s_atur_kode = ed.getPass();
      atur_kode = s_atur_kode.toInt();
      lib_set_value("edit", "edit_kode", String(atur_kode), "%d");
      if (atur_kode == password) {
        lib_set_visible("labelverif", 0);
        lib_open_win("hal_control1", 1);

        //preferences.begin("control", false);
        iotStatusUpdate(1);
        st_ctrl = true;
        if (halCtr < 2) {
          jeda = 1;
          //delay(1000);
          pref_send(true);
          delay(100);
          update_control_page(bahasa.c_str());
          //set_bahasa(bahasa);
          pref_send(false);
          delay(20);
          //jeda = 0;
        } else {
          if (bahasa_c != bahasa_c_cpy) update_control_page(bahasa_c.c_str());
          bahasa_c_cpy = bahasa_c;
        }
        halCtr++;
        atur_kode = 0;
        lib_set_value("edit", "edit_kode", String(atur_kode), "%d");
      } else if (atur_kode == password_calibration) {
        if (bahasa == "english") {
          lib_open_win("hal_kalibrasi_eng", 1);
        } else {
          lib_open_win("hal_kalibrasi", 1);
        }
      } else {
        Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"labelverif\",\"visible\":true}>ET"));
      }
    }
    //button + - ctrl not yet
    //setting Threshold
    /*
      else if (widget == "butt_hN2O") {
      min_N2O--;
      if (min_N2O < 0) min_N2O = 0;
      lib_set_value("edit", "edit_0N2O", String(min_N2O), "%d");
      preferences.putInt("minN2O", min_N2O);
      } else if (widget == "butt_iN2O") {
      min_N2O++;
      if (min_N2O >= max_N2O) min_N2O = max_N2O - 1;
      lib_set_value("edit", "edit_0N2O", String(min_N2O), "%d");
      preferences.putInt("minN2O", min_N2O);
      } else if (widget == "butt_jN2O") {
      max_N2O--;
      if (max_N2O <= min_N2O) max_N2O = min_N2O + 1;
      lib_set_value("edit", "edit_1N2O", String(max_N2O), "%d");
      preferences.putInt("maxN2O", max_N2O);
      } else if (widget == "butt_kN2O") {
      max_N2O++;
      lib_set_value("edit", "edit_1N2O", String(max_N2O), "%d");
      preferences.putInt("maxN2O", max_N2O);
      sdebug_print("Max N2O :");
      sdebug_println(preferences.getInt("maxN2O", max_N2O));

      } else if (widget == "butt_l_O2") {
      min_O2--;
      if (min_O2 < 0) min_O2 = 0;
      lib_set_value("edit", "edit_2O2_", String(min_O2), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minO2", min_O2);
      //preferences.end();
      } else if (widget == "butt_m_O2") {
      min_O2++;
      if (min_O2 >= max_O2) min_O2 = max_O2 - 1;
      lib_set_value("edit", "edit_2O2_", String(min_O2), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minO2", min_O2);
      //preferences.end();
      } else if (widget == "butt_o_O2") {
      max_O2--;
      if (max_O2 <= min_O2) max_O2 = min_O2 + 1;
      lib_set_value("edit", "edit_3O2_", String(max_O2), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxO2", max_O2);
      //preferences.end();
      } else if (widget == "butt_p_O2") {
      max_O2++;
      lib_set_value("edit", "edit_3O2_", String(max_O2), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxO2", max_O2);
      //preferences.end();
      } else if (widget == "butt_qAir") {
      min_Air--;
      lib_set_value("edit", "edit_4air", String(min_Air), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minAir", min_Air);
      //preferences.end();
      } else if (widget == "butt_rAir") {
      min_Air++;
      if (min_Air >= max_Air) min_Air = max_Air - 1;
      lib_set_value("edit", "edit_4air", String(min_Air), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minAir", min_Air);
      //preferences.end();
      } else if (widget == "butt_sAir") {
      max_Air--;
      if (max_Air <= min_Air) max_Air = min_Air + 1;
      lib_set_value("edit", "edit_5air", String(max_Air), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxAir", max_Air);
      //preferences.end();
      } else if (widget == "butt_tAir") {
      max_Air++;
      lib_set_value("edit", "edit_5air", String(max_Air), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxAir", max_Air);
      //preferences.end();
      } else if (widget == "butt_uVkm") {
      min_Vacum--;
      lib_set_value("edit", "edit_6Vkm", String(min_Vacum), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minVacum", min_Vacum);
      //preferences.end();
      } else if (widget == "butt_vVkm") {
      min_Vacum++;
      //if(min_Vacum >= max_Vacum) min_Vacum = max_Vacum -1;
      lib_set_value("edit", "edit_6Vkm", String(min_Vacum), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minVacum", min_Vacum);
      //preferences.end();
      } else if (widget == "butt_wVkm") {
      max_Vacum--;
      // if(max_Vacum <= min_Vacum) max_Vacum = min_Vacum + 1;
      lib_set_value("edit", "edit_7Vkm", String(max_Vacum), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxVacum", max_Vacum);
      //preferences.end();
      } else if (widget == "butt_xVkm") {
      max_Vacum++;
      lib_set_value("edit", "edit_7Vkm", String(max_Vacum), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxVacum", max_Vacum);
      //preferences.end();
      } else if (widget == "butt_yTem") {
      min_Temp--;
      lib_set_value("edit", "edit_8tem", String(min_Temp), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minTemp", min_Temp);
      //preferences.end();
      } else if (widget == "butt_zTem") {
      min_Temp++;
      if (min_Temp >= max_Temp) min_Temp = max_Temp - 1;
      lib_set_value("edit", "edit_8tem", String(min_Temp), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minTemp", min_Temp);
      //preferences.end();
      } else if (widget == "butt_ATem") {
      max_Temp--;
      if (max_Temp <= min_Temp) max_Temp = min_Temp + 1;
      lib_set_value("edit", "edit_9tem", String(max_Temp), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxTemp", max_Temp);
      //preferences.end();
      } else if (widget == "butt_BTem") {
      max_Temp++;
      lib_set_value("edit", "edit_9tem", String(max_Temp), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxTemp", max_Temp);
      //preferences.end();
      } else if (widget == "butt_CHum") {
      min_Humid--;
      lib_set_value("edit", "edit_ahum", String(min_Humid), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minHumid", min_Humid);
      //preferences.end();
      } else if (widget == "butt_DHum") {
      min_Humid++;
      //if(min_Humid >= max_Humid) min_Humid = max_Humid -1;
      lib_set_value("edit", "edit_ahum", String(min_Humid), "%d");
      //preferences.begin("control", false);
      preferences.putInt("minHumid", min_Humid);
      //preferences.end();
      } else if (widget == "butt_EHum") {
      max_Humid--;
      // if(max_Humid <= min_Humid) max_Humid = min_Humid + 1;
      lib_set_value("edit", "edit_bhum", String(max_Humid), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxHumid", max_Humid);
      //preferences.end();
      } else if (widget == "butt_FHum") {
      max_Humid++;
      lib_set_value("edit", "edit_bhum", String(max_Humid), "%d");
      //preferences.begin("control", false);
      preferences.putInt("maxHumid", max_Humid);
      //preferences.end();
      }*/

    else if (widget == "butt_editN2O") {
      sensorID = 0;
      stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup3\"}>ET"));
      delay(100);
      lib_set_value("edit", "edit_sensor_min", String(min_N2O), "%d");
      lib_set_value("edit", "edit_sensor_max", String(max_N2O), "%d");
      lib_set_text("label", "label_satuan_min", "BAR");
      lib_set_text("label", "label_satuan_max", "BAR");
      delay(10);
      if (bahasa == "english") {
        lib_set_text("label", "label_sensor_min", "Min N2O Pressure");
        lib_set_text("label", "label_sensor_max", "Max N2O Pressure");
        lib_set_text("button", "button_save_sensor", "Save");
      } else {
        lib_set_text("label", "label_sensor_min", "Min Tekanan N2O");
        lib_set_text("label", "label_sensor_max", "Max Tekanan N2O");
        lib_set_text("button", "button_save_sensor", "Simpan");
      }
    } else if (widget == "butt_editO2") {
      sensorID = 1;
      stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup3\"}>ET"));
      delay(100);
      lib_set_value("edit", "edit_sensor_min", String(min_O2), "%d");
      lib_set_value("edit", "edit_sensor_max", String(max_O2), "%d");
      lib_set_text("label", "label_satuan_min", "BAR");
      lib_set_text("label", "label_satuan_max", "BAR");
      delay(10);
      if (bahasa == "english") {
        lib_set_text("label", "label_sensor_min", "Min O2 Pressure");
        lib_set_text("label", "label_sensor_max", "Max O2 Pressure");
        lib_set_text("button", "button_save_sensor", "Save");
      } else {
        lib_set_text("label", "label_sensor_min", "Min Tekanan O2");
        lib_set_text("label", "label_sensor_max", "Max Tekanan O2");
        lib_set_text("button", "button_save_sensor", "Simpan");
      }
    } else if (widget == "butt_editAir") {
      sensorID = 2;
      stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup3\"}>ET"));
      delay(100);
      lib_set_value("edit", "edit_sensor_min", String(min_Air), "%d");
      lib_set_value("edit", "edit_sensor_max", String(max_Air), "%d");
      lib_set_text("label", "label_satuan_min", "BAR");
      lib_set_text("label", "label_satuan_max", "BAR");
      delay(10);
      if (bahasa == "english") {
        lib_set_text("label", "label_sensor_min", "Min Air Pressure");
        lib_set_text("label", "label_sensor_max", "Max Air Pressure");
        lib_set_text("button", "button_save_sensor", "Save");
      } else {
        lib_set_text("label", "label_sensor_min", "Min Tekanan Udara");
        lib_set_text("label", "label_sensor_max", "Max Tekanan Udara");
        lib_set_text("button", "button_save_sensor", "Simpan");
      }
    } else if (widget == "butt_editVkm") {
      sensorID = 3;
      stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup3\"}>ET"));
      delay(100);
      lib_set_value("edit", "edit_sensor_min", String(min_Vacum), "%d");
      lib_set_value("edit", "edit_sensor_max", String(max_Vacum), "%d");
      lib_set_text("label", "label_satuan_min", "mmHg");
      lib_set_text("label", "label_satuan_max", "mmHg");
      delay(10);
      if (bahasa == "english") {
        lib_set_text("label", "label_sensor_min", "Min Vacuum Pressure");
        lib_set_text("label", "label_sensor_max", "Max Vacuum Pressure");
        lib_set_text("button", "button_save_sensor", "Save");
      } else {
        lib_set_text("label", "label_sensor_min", "Min Tekanan Vakum");
        lib_set_text("label", "label_sensor_max", "Max Tekanan Vakum");
        lib_set_text("button", "button_save_sensor", "Simpan");
      }
    } else if (widget == "butt_editTem") {
      sensorID = 4;
      stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup3\"}>ET"));
      delay(100);
      lib_set_value("edit", "edit_sensor_min", String(min_Temp), "%d");
      lib_set_value("edit", "edit_sensor_max", String(max_Temp), "%d");
      lib_set_text("label", "label_satuan_min", "˚C");
      lib_set_text("label", "label_satuan_max", "˚C");
      delay(10);
      if (bahasa == "english") {
        lib_set_text("label", "label_sensor_min", "Min Temperature");
        lib_set_text("label", "label_sensor_max", "Max Temperature");
        lib_set_text("button", "button_save_sensor", "Save");
      } else {
        lib_set_text("label", "label_sensor_min", "Min Suhu");
        lib_set_text("label", "label_sensor_max", "Max Suhu");
        lib_set_text("button", "button_save_sensor", "Simpan");
      }
    } else if (widget == "butt_editHum") {
      sensorID = 5;
      stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup3\"}>ET"));
      delay(100);
      lib_set_value("edit", "edit_sensor_min", String(min_Humid), "%d");
      lib_set_value("edit", "edit_sensor_max", String(max_Humid), "%d");
      lib_set_text("label", "label_satuan_min", "%");
      lib_set_text("label", "label_satuan_max", "%");
      delay(10);
      if (bahasa == "english") {
        lib_set_text("label", "label_sensor_min", "Min Humidity");
        lib_set_text("label", "label_sensor_max", "Max Humidity");
        lib_set_text("button", "button_save_sensor", "Save");
      } else {
        lib_set_text("label", "label_sensor_min", "Min Kelembapan");
        lib_set_text("label", "label_sensor_max", "Max Kelembapan");
        lib_set_text("button", "button_save_sensor", "Simpan");
      }
    } else if (widget == "button_save_sensor") {
      switch (sensorID) {
        case 0:
          preferences.begin("control", false);
          preferences.putInt("minN2O", min_N2O);
          preferences.putInt("maxN2O", max_N2O);
          preferences.end();
          lib_set_value("label", "label_min_N2O", String(min_N2O), "%d");
          lib_set_value("label", "label_max_N2O", String(max_N2O), "%d");
          break;
        case 1:
          preferences.begin("control", false);
          preferences.putInt("minO2", min_O2);
          preferences.putInt("maxO2", max_O2);
          preferences.end();
          lib_set_value("label", "label_min_o2", String(min_O2), "%d");
          lib_set_value("label", "label_max_o2", String(max_O2), "%d");
          break;
        case 2:
          preferences.begin("control", false);
          preferences.putInt("minAir", min_Air);
          preferences.putInt("maxAir", max_Air);
          preferences.end();
          lib_set_value("label", "label_min_air", String(min_Air), "%d");
          lib_set_value("label", "label_max_air", String(max_Air), "%d");
          break;
        case 3:
          preferences.begin("control", false);
          preferences.putInt("minVacum", min_Vacum);
          preferences.putInt("maxVacum", max_Vacum);
          preferences.end();
          lib_set_value("label", "label_min_vakum", String(min_Vacum), "%d");
          lib_set_value("label", "label_max_vakum", String(max_Vacum), "%d");
          break;
        case 4:
          preferences.begin("control", false);
          preferences.putInt("minTemp", min_Temp);
          preferences.putInt("maxTemp", max_Temp);
          preferences.end();
          lib_set_value("label", "label_min_temp", String(min_Temp), "%d");
          lib_set_value("label", "label_max_temp", String(max_Temp), "%d");
          break;
        case 5:
          preferences.begin("control", false);
          preferences.putInt("maxHumid", max_Humid);
          preferences.putInt("minHumid", min_Humid);
          preferences.end();
          lib_set_value("label", "label_min_humidity", String(min_Humid), "%d");
          lib_set_value("label", "label_max_humidity", String(max_Humid), "%d");
          break;
      }
    } else if (widget == "button_lyr_down") {
      kecerahan -= 10;
      if (kecerahan < 10) kecerahan = 10;
      setkecerahan(kecerahan);
    } else if (widget == "button_lyr_up") {
      kecerahan += 10;
      if (kecerahan > 100) kecerahan = 100;
      setkecerahan(kecerahan);
    } else if (widget == "butt_1_play") {
      read_mplayers2();
      title = "Track " + String(track);
      strcpy(t_music, title.c_str());
      if (title != title_cpy) lib_set_text("label", "label_judul_lagu", t_music);

      if (play == false) {
        df_player("start");
        play = true;
        lib_set_bg_image("butt_1_play", "resume");

      } else if (play == true) {
        play = false;
        df_player("pause");
        lib_set_bg_image("butt_1_play", "play");
      }
      title_cpy = title;

    } else if (widget == "butt_2_next") {
      read_mplayers2();
      play = true;
      df_player("next");  //play lagu selanjutnya

      title = "Track " + String(track + 1);
      strcpy(t_music, title.c_str());
      lib_set_text("label", "label_judul_lagu", t_music);
      lib_set_bg_image("butt_1_play", "resume");

    } else if (widget == "butt_3_prev") {
      read_mplayers2();
      play = true;
      df_player("prev");  //play lagu sebelumnya
      title = "Track " + String(track - 1);

      strcpy(t_music, title.c_str());
      lib_set_text("label", "label_judul_lagu", t_music);
      lib_set_bg_image("butt_1_play", "resume");

    } else if (widget == "butt_0_close") {
      isPopup = 0;
      jeda = 0;
    } else if (widget == "button_vol_up") {
      vol_music = vol_music + 10;
      if (vol_music > 100) vol_music = 100;
      DFVolume = map(vol_music, 0, 100, 0, 30);
      df_player("volume", DFVolume);
      Serial.printf("vol_music : %d, vol df : %d\n", vol_music, DFVolume);
      setvolume(vol_music / 10);
      delay(10);
    } else if (widget == "button_vol_down") {
      vol_music = vol_music - 10;
      if (vol_music < 0) vol_music = 0;
      DFVolume = map(vol_music, 0, 100, 0, 30);
      df_player("volume", DFVolume);
      Serial.printf("vol_music : %d, vol df : %d\n", vol_music, DFVolume);
      //Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"progress_bar\",\"widget\":\"progress_bar1\",\"value\":"));
      //Serial2.print(F(vol_music));
      //Serial2.println(F("}>ET"));
      //lib_set_value("progress_bar", "progress_bar1", String(vol_music), "%d");
      setvolume(vol_music / 10);
      delay(10);
    } else if (widget == "button_m_inf0" || widget == "button_s_inf0" || widget == "button_c_inf0") {
      /*if (st_ctrl == true) {
        preferences.end();
        st_ctrl = false;
        }*/
      update_details_popup(bahasa.c_str());
    } else if (widget == "button_m_ctr1" || widget == "button_s_ctr1") {
      /* if (st_ctrl == true) {
        preferences.end();
        st_ctrl = false;
        }*/
      update_password_popup(bahasa.c_str());
    } else if (widget == "button_m_music" || widget == "button_s_music" || widget == "button_c_music") {
      // read_mplayers2();   //read track nummber
      // delay(10);
      // readVolume = df_player("readVolume");
      isPopup = 1;
      //jeda = 1;
      df_player("volume", DFVolume);
      sdebug_println("oke");
      volume_music = map(DFVolume, 0, 30, 0, 100);
      Serial.printf("vol_music : %d, vol df : %d\n", vol_music, DFVolume);
      setvolume(vol_music / 10);
      //lib_set_value("progress_bar", "progress_bar1", String(vol_music), "%d");
      //Serial2.print(F("ST<{\"cmd_code\":\"set_value\",\"type\":\"progress_bar\",\"widget\":\"progress_bar1\",\"value\":"));
      //Serial2.print(F(vol_music));
      //Serial2.println(F("}>ET"));

      if (play == true) {
        lib_set_bg_image("butt_1_play", "resume");
      } else {
        lib_set_bg_image("butt_1_play", "play");
      }

      //lib_set_value("slider", "slider4", String(volume_music), "%d");

      title = "Track " + String(track);
      strcpy(t_music, title.c_str());
      lib_set_text("label", "label_judul_lagu", t_music);
    }

    else if (widget == "button_c_bck4" || widget == "button_s_bck4" || widget == "button_k_bck" || widget == "button_k_bck_e") {
      if (bahasa_d != bahasa_d_cpy) update_monitor_page(bahasa_d.c_str());
      bahasa_d_cpy = bahasa_d;
      if (st_ctrl == true) {
        //preferences.end();
        st_ctrl = false;
        jeda = 0;
      }


      status_update();
    } else if (widget == "button_c_out3") {
      //preferences.end();
      st_ctrl = false;
      jeda = 0;
    }


    else if (widget == "butt_k_N2O") {
      lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Gas N2O");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "N2O Gas Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Gas N2O");
      labelSatuan = "Bar";
      sensorID = 0;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_N2O_e") {
      lib_set_text("label", "label_k_namaSensor_e", "N2O Gas Pressure Sensor");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "N2O Gas Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Gas N2O");
      labelSatuan = "Bar";
      sensorID = 0;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup_eng();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_O2") {
      lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Gas O2");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "O2 Gas Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Gas O2");
      labelSatuan = "Bar";
      sensorID = 1;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup();
      //update_kalibrasi_popup(bahasa.c_str());
    } else if (widget == "butt_k_O2_e") {
      lib_set_text("label", "label_k_namaSensor_e", "O2 Gas Pressure Sensor");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "O2 Gas Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Gas O2");
      labelSatuan = "Bar";
      sensorID = 1;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup_eng();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_air") {
      lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Udara");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Air Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Udara");
      labelSatuan = "Bar";
      sensorID = 2;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_air_e") {
      lib_set_text("label", "label_k_namaSensor_e", "Air Pressure Sensor");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Air Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Udara");
      labelSatuan = "Bar";
      sensorID = 2;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup_eng();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_vakum") {
      lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Vakum");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Vacuum Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Vakum");
      labelSatuan = "mmHg";
      lib_set_enaVisi("view_info_1", 1);
      sensorID = 3;
      kalibrasiState = 0;
      refTolerance = 25;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup();
      //update_kalibrasi_popup(bahasa.c_str());
    } else if (widget == "butt_k_vakum_e") {
      lib_set_text("label", "label_k_namaSensor_e", "Vacuum Pressure Sensor");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Vacuum Pressure Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Tekanan Vakum");
      labelSatuan = "mmHg";
      lib_set_enaVisi("view_info_1e", 1);
      sensorID = 3;
      kalibrasiState = 0;
      refTolerance = 25;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup_eng();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_suhu") {
      lib_set_text("label", "label_k_namaSensor", "Sensor Suhu");
      // bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Temperature Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Suhu");
      labelSatuan = "°C";
      sensorID = 4;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup();
      //update_kalibrasi_popup(bahasa.c_str());
    } else if (widget == "butt_k_suhu_e") {
      lib_set_text("label", "label_k_namaSensor_e", "Temperature Sensor");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Temperature Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Suhu");
      labelSatuan = "°C";
      sensorID = 4;
      kalibrasiState = 0;
      refTolerance = 0.5;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup_eng();
      //update_kalibrasi_popup(bahasa.c_str());
    }

    else if (widget == "butt_k_Humidity") {
      lib_set_text("label", "label_k_namaSensor", "Sensor Kelembapan");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Humidity Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Kelembapan");
      labelSatuan = "%";
      sensorID = 5;
      kalibrasiState = 0;
      refTolerance = 1.0;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup();
      //update_kalibrasi_popup(bahasa.c_str());
    } else if (widget == "butt_k_Humidity_e") {
      lib_set_text("label", "label_k_namaSensor_e", "Humidity Sensor");
      //bahasa == "english" ? lib_set_text("label", "label_k_namaSensor", "Humidity Sensor") : lib_set_text("label", "label_k_namaSensor", "Sensor Kelembapan");
      labelSatuan = "%";
      sensorID = 5;
      kalibrasiState = 0;
      refTolerance = 1.0;
      //update_kalibrasi_popup(bahasa.c_str());
      calibrationPopup_eng();
      //update_kalibrasi_popup(bahasa.c_str());
    } else if (widget == "button_k_4sample" || widget == "button_k_4sample_e") {
      jumlahSample = 4;
      Serial.println("jumlah Sample: " + String(jumlahSample));
      kalibrasiState += 1;
      bahasa == "english" ? calibrationPopup_eng() : calibrationPopup();
    }

    else if (widget == "button_k_6sample" || widget == "button_k_6sample_e") {
      jumlahSample = 6;
      Serial.println("jumlah Sample: " + String(jumlahSample));
      kalibrasiState += 1;
      bahasa == "english" ? calibrationPopup_eng() : calibrationPopup();
    }

    else if (widget == "button_k_11sample" || widget == "button_k_11sample_e") {
      jumlahSample = 11;
      Serial.println("jumlah Sample: " + String(jumlahSample));
      kalibrasiState += 1;
      bahasa == "english" ? calibrationPopup_eng() : calibrationPopup();
    }

    else if (widget == "button_k_next_copy1") {
      // kalibrasiState += 1;
      lib_set_enaVisi("view_info_1", 0);
      lib_set_enaVisi("view_k_sample", 1);

      // calibrationPopup();
    } else if (widget == "button_k_next_copy1e") {
      // kalibrasiState += 1;
      lib_set_enaVisi("view_info_1e", 0);
      lib_set_enaVisi("view_k_sample_e", 1);
      // calibrationPopup();
    }


    else if (widget == "button_k_next" || widget == "button_k_next_e") {
      if (bahasa == "english") Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"label_k_errorInput_e\",\"visible\":false}>ET"));
      else Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"label_k_errorInput\",\"visible\":false}>ET"));

      float refValue;  //nilai referensi yang harus dimasukkan

      if (sensorID == 0 || sensorID == 1 || sensorID == 2) {  //sensor tekanan
        if (jumlahSample == 11) {
          refValue = jumlahSample - kalibrasiState + 1;
        } else if (jumlahSample == 6) {
          refValue = ((jumlahSample - kalibrasiState + 1) * 2) - 1;
        } else if (jumlahSample == 4) {
          refValue = (jumlahSample - kalibrasiState + 1) + ((jumlahSample - kalibrasiState) * 2);
        }
      } else if (sensorID == 3) {  //sensor vakum
        if (jumlahSample == 11) {
          refValue = (((jumlahSample - kalibrasiState + 1) * -10) + 10) * 7.501;
        } else if (jumlahSample == 6) {
          refValue = (((jumlahSample - kalibrasiState + 1) * -20) + 20) * 7.501;
        } else if (jumlahSample == 4) {
          refValue = (((jumlahSample - kalibrasiState + 1) * -30) + 30) * 7.501;
        }
      } else if (sensorID == 4) {  //sensor suhu
        if (jumlahSample == 11) {
          refValue = (jumlahSample - kalibrasiState + 1) + 15;
        } else if (jumlahSample == 6) {
          refValue = ((jumlahSample - kalibrasiState + 1) * 2) - 1 + 15;
        } else if (jumlahSample == 4) {
          refValue = (jumlahSample - kalibrasiState + 1) + (((jumlahSample - kalibrasiState + 1) - 1) * 2) + 15;
        }
      } else if (sensorID == 5) {  // sensor kelembaban
        if (jumlahSample == 11) {
          refValue = (jumlahSample - kalibrasiState) * 4 + 30;
        } else if (jumlahSample == 6) {
          refValue = (jumlahSample - kalibrasiState) * 8 + 30;
        } else if (jumlahSample == 4) {
          refValue = (jumlahSample - kalibrasiState) * 12 + 30;
        }
      }

      Serial.println("refValue : " + String(refValue));
      Serial.println("state : " + String(kalibrasiState));


      if (inpRef > refValue - refTolerance && inpRef <= refValue + refTolerance) {  //simpan data jika referensi Â± dari toleransi yang ditentukan.
        refDataArr[kalibrasiState - 1] = inpRef;
        senDataArr[kalibrasiState - 1] = currentSensorRead;
        // senDataArr[kalibrasiState - 1] = inpRef + (random(0, 400) / 1000.00) - 0.20;

        if (kalibrasiState == jumlahSample) {  //lompat ke laporan jika selesai.
          kalibrasiState = 12;
        } else kalibrasiState += 1;

        //display referensi yang harus dimasukkan
        String refValueLabel;
        if (sensorID == 0 || sensorID == 1 || sensorID == 2) {  //sensor tekanan
          if (jumlahSample == 11) {
            refValue = jumlahSample - kalibrasiState + 1;
          } else if (jumlahSample == 6) {
            refValue = ((jumlahSample - kalibrasiState + 1) * 2) - 1;
          } else if (jumlahSample == 4) {
            refValue = (jumlahSample - kalibrasiState + 1) + ((jumlahSample - kalibrasiState) * 2);
          }
          refValueLabel = "Range : " + String(refValue - refTolerance + 0.01) + " - " + String(refValue + refTolerance) + " Bar";

        } else if (sensorID == 3) {  //sensor vakum
          if (jumlahSample == 11) {
            refValue = (((jumlahSample - kalibrasiState + 1) * -10) + 10) * 7.501;
          } else if (jumlahSample == 6) {
            refValue = (((jumlahSample - kalibrasiState + 1) * -20) + 20) * 7.501;
          } else if (jumlahSample == 4) {
            refValue = (((jumlahSample - kalibrasiState + 1) * -30) + 30) * 7.501;
          }
          refValueLabel = "Range : " + String(int(refValue - refTolerance + 1)) + " mmHg s/d " + String(int(refValue + refTolerance)) + " mmHg";

        } else if (sensorID == 4) {  //sensor suhu
          if (jumlahSample == 11) {
            refValue = (jumlahSample - kalibrasiState + 1) + 15;
          } else if (jumlahSample == 6) {
            refValue = ((jumlahSample - kalibrasiState + 1) * 2) - 1 + 15;
          } else if (jumlahSample == 4) {
            refValue = (jumlahSample - kalibrasiState + 1) + (((jumlahSample - kalibrasiState + 1) - 1) * 2) + 15;
          }
          refValueLabel = "Range : " + String(refValue - refTolerance + 0.01) + " °C” " + String(refValue + refTolerance) + " °C";

        } else if (sensorID == 5) {  // sensor kelembaban
          if (jumlahSample == 11) {
            refValue = (jumlahSample - kalibrasiState) * 4 + 30;
          } else if (jumlahSample == 6) {
            refValue = (jumlahSample - kalibrasiState) * 8 + 30;
          } else if (jumlahSample == 4) {
            refValue = (jumlahSample - kalibrasiState) * 12 + 30;
          }
          refValueLabel = "Range : " + String(refValue - refTolerance + 0.01) + " %” " + String(refValue + refTolerance) + " %";
        }

        delay(1);
        if (bahasa == "english") {
          lib_set_text("label", "label_referensiValue_e", refValueLabel);
          delay(10);
          lib_set_text("label", "label_referensiValue_e", refValueLabel);
        } else {
          lib_set_text("label", "label_referensiValue", refValueLabel);
          delay(10);
          lib_set_text("label", "label_referensiValue", refValueLabel);
        }
      } else {
        if (bahasa == "english") lib_set_visible("label_k_errorInput_e", 1);
        else lib_set_visible("label_k_errorInput", 1);
      }

      bahasa == "english" ? calibrationPopup_eng() : calibrationPopup();
    }


    else if (widget == "button_k_kalibrasi" || widget == "button_k_kalibrasi_copy1" || widget == "button_k_kalibrasi_copy2") {
      saveCalibration();
      lib_set_enaVisi("view_k_konfirmasi", 1);
    } else if (widget == "button_k_kalibrasi_e" || widget == "button_k_kalibrasi_copy1e" || widget == "button_k_kalibrasi_copy2e") {
      saveCalibration();
      lib_set_enaVisi("view_k_konfirmasi_e", 1);
    }


    else if (widget == "button_k_resetKalibrasi") {
      Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"view_k_konfirmasi_reset\",\"enable\":true}>ET"));
      Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_k_konfirmasi_reset\",\"visible\":true}>ET"));

      /*if (sensorID == 0) {
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "N2O Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan N2O?");
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "N2O Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan N2O?");
        } else if (sensorID == 1) {
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "O2 Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan O2?");
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "O2 Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan O2?");
        } else if (sensorID == 2) {
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Air Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan udara?");
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Air Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan udara?");
        } else if (sensorID == 3) {
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Vacuum Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan Vakum?");
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Vacuum Pressure Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Tekanan Vakum?");
        } else if (sensorID == 4) {
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Temperature Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Suhu?");
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Temperature Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Suhu?");
        } else if (sensorID == 5) {
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Humidity Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Kelembapan?");
        bahasa == "english" ? lib_set_text("label", "label_k_resetKalibrasi", "Humidity Sensor Calibration Data Reset?") : lib_set_text("label", "label_k_resetKalibrasi", "Reset Data Kalibrasi Sensor Kelembapan?");
        }*/
    } else if (widget == "button_k_resetKalibrasi_e") {
      lib_set_enaVisi("view_k_konfirmasi_reset_e", 1);
    }

    else if (widget == "button_k_okReset") {
      calibrationReset(sensorID);
      lib_set_enaVisi("view_k_konfirmasi_reset_ok", 1);

      calibrationInit();
    } else if (widget == "button_k_okReset_e") {
      calibrationReset(sensorID);
      lib_set_enaVisi("view_k_konfirmasi_reset_oke", 1);

      calibrationInit();
    }


    else if (widget == "butt_k_close" || widget == "button_k_tutup" || widget == "button_k_tutup_copy1" || widget == "button_k_batal" || widget == "butt_k_close_e" || widget == "button_k_tutup_e" || widget == "button_k_tutup_copy1_e" || widget == "button_k_batal_e") {
      isCalibrate = 0;
      preferences.begin("control", false);
      alarmEnable = preferences.getBool("alarmEnable", false);
      preferences.end();
      kalibrasiState = 0;
      Serial.println("close");
    }
    //tombol tunda
    else if (widget == "butt_a_close" || widget == "button_a_tutup") {
      snooze = 1;
      Serial.println("alarm snooze");
    }

    // tombol matikan
    else if (widget == "button_a_mati") {
      isAlarm = 0;
    }

    else if (widget == "button1") {
      update_kalibrasi_page(bahasa.c_str());
    }

    else if (widget == "button_m_wifi" || widget == "button_s_wifi" || widget == "button_c_wifi") {
      if (bahasa == "english") {
        lib_set_text("label", "label_popup_wifi", "    Configure Wifi");
        lib_set_text("button", "button_wifi_save", "Save");
      } else {
        lib_set_text("label", "label_popup_wifi", "    Konfigurasi Wifi");
        lib_set_text("button", "button_wifi_save", "Simpan");
      }
      iotStatusUpdate(1);

      preferences.begin("loginWifi", false);
      wifiSsid = preferences.getString("ssid");
      wifiPass = preferences.getString("pass");
      preferences.end();

      lib_set_text("edit", "edit_ssid", wifiSsid);
      lib_set_text("edit", "edit_pass", wifiPass);
    }

    else if (widget == "button_wifi_reset") {
      iotStatus = 0;
      iotStatusUpdate();
      iotReset();
    }

    else if (widget == "button_wifi_save") {
      iotStatus = 2;
      iotStatusUpdate();
      iotStatusUpdate_startMillis = millis();
      iotStatusUpdate_once = 0;

      wifiSsid = ed.getWifiSsid();
      wifiPass = passVisible ? ed.getWifiPas2() : ed.getWifiPass();
      iotSendConfig(wifiSsid, wifiPass);

      preferences.begin("loginWifi", false);
      preferences.putString("ssid", wifiSsid);
      preferences.putString("pass", wifiPass);
      preferences.end();
    }

    else if (widget == "button_showPass") {
      if (passVisible == 0) {
        lib_set_bg_image("button_showPass", "eye_noslash");
        Serial.println("pass set to show");

        lib_set_enaVisi("edit_pass", 0);
        lib_set_enaVisi("edit_pas2", 1);
        lib_set_text("edit", "edit_pas2", ed.getWifiPass());
        passVisible = 1;
      } else if (passVisible == 1) {
        lib_set_bg_image("button_showPass", "eye_slash");
        Serial.println("pass set to hide");

        lib_set_enaVisi("edit_pass", 1);
        lib_set_enaVisi("edit_pas2", 0);

        lib_set_text("edit", "edit_pass", ed.getWifiPas2());
        passVisible = 0;
      }
    }

    //tombol voip
    else if (widget == "button_m_voip" || widget == "button_s_voip" || widget == "button_c_voip") {
      delay(10);
      lib_set_text("label", "label_st_regist", "Registering");
      lib_set_bg_color("label_st_regis", 0xFFFFFF00);
      rs485Send("SIPS;");
      update_voip_page(bahasa.c_str());
      yield();

      numberKey = "";
      lib_set_text("label", "label_in_keypad", numberKey);
      lib_set_enaVisi("viewKeypad", 1);
      lib_set_bg_color("buttonAddrs", 0xFFD9D9D9);

      preferences.begin("voipRegister", false);
      voip_register_id = preferences.getString("vr_id");
      voip_register_pass = preferences.getString("vr_pass");
      voip_register_serverIp = preferences.getString("vr_serverIp");
      preferences.end();

      lib_set_text("edit", "edit_v_id", voip_register_id);
      lib_set_text("edit", "edit_v_password", voip_register_pass);
      lib_set_text("edit", "edit_v_serverIp", voip_register_serverIp);
      delay(10);
      addressBookShow();
    }


    else if (widget == "button_v_setting") {
      if (voip_viewConfig) {
        lib_set_enaVisi("viewConfig", 0);
        voip_viewConfig = false;
      } else {
        lib_set_enaVisi("viewConfig", 1);
        voip_viewConfig = true;
      }
      lib_set_visible("label_v_contactFull", 0);
    }

    else if (widget == "button_v_saveSetting") {
      voip_register_id = ed.getVoipId();
      voip_register_pass = ed.getVoipPass();
      voip_register_serverIp = ed.getVoipServer();

      preferences.begin("voipRegister", false);
      preferences.putString("vr_id", voip_register_id);
      preferences.putString("vr_pass", voip_register_pass);
      preferences.putString("vr_serverIp", voip_register_serverIp);
      preferences.end();

      sprintf(voip_register_uri, "SIPRudp://%s:%s@%s:5060;", voip_register_id.c_str(), voip_register_pass.c_str(), voip_register_serverIp.c_str());
      rs485Send(voip_register_uri);

      lib_set_text("label", "label_st_regist", "Registering");
      lib_set_bg_color("label_st_regis", 0xFFFFFF00);
    }

    else if (widget == "key1") {
      keypadPressed(1);
    } else if (widget == "key2") {
      keypadPressed(2);
    } else if (widget == "key3") {
      keypadPressed(3);
    } else if (widget == "key4") {
      keypadPressed(4);
    } else if (widget == "key5") {
      keypadPressed(5);
    } else if (widget == "key6") {
      keypadPressed(6);
    } else if (widget == "key7") {
      keypadPressed(7);
    } else if (widget == "key8") {
      keypadPressed(8);
    } else if (widget == "key9") {
      keypadPressed(9);
    } else if (widget == "key0") {
      keypadPressed(0);
    } else if (widget == "button_bksp") {
      keypadPressed(99);
    }

    else if (widget == "button_v_call") {
      if (voip_status != VOIP_DISCONNECT) {
        if (numberKey != "") {
          rs485Send("SIPC" + numberKey + ";");
          numberKey = "";
          lib_set_text("label", "label_in_keypad", numberKey);
        } else {
          lib_set_enable("label_in_keypad", 0);
          if (bahasa == "english") lib_set_text("label", "label_in_keypad", "Enter Phone Number!");
          else lib_set_text("label", "label_in_keypad", "Masukkan Nomor Telepon!");
          delay(1500);
          lib_set_text("label", "label_in_keypad", "");
          lib_set_enable("label_in_keypad", 1);
        }
      } else {
        lib_set_enable("label_in_keypad", 0);
        if (bahasa == "english") lib_set_text("label", "label_in_keypad", "VoIP Not Connected!");
        else lib_set_text("label", "label_in_keypad", "VoIP Tidak Terhubung!");
        delay(1500);
        numberKey = "";
        lib_set_text("label", "label_in_keypad", "");
        lib_set_enable("label_in_keypad", 1);
      }
    }

    else if (widget == "buttonAddrs") {
      lib_set_enaVisi("viewKeypad", 0);
      lib_set_enaVisi("viewAddrs", 1);
      lib_set_enaVisi("button_dlt_all", 1);
      lib_set_enaVisi("button_v_addAddrs", 1);
      lib_set_visible("label_v_contactFull", 0);

      lib_set_bg_color("buttonKeypad", 0xFFD9D9D9);
      lib_set_bg_color("buttonAddrs", 0xFF537FE7);

      lib_set_enaVisi("viewListAddr", 1);
      lib_set_enaVisi("view_contact_detail", 0);
      lib_set_enaVisi("view_dlt_all", 0);
      addressBookShow();
    } else if (widget == "buttonKeypad") {
      lib_set_enaVisi("viewAddrs", 0);
      lib_set_enaVisi("viewKeypad", 1);
      lib_set_bg_color("buttonAddrs", 0xFFD9D9D9);
      lib_set_bg_color("buttonKeypad", 0xFF537FE7);
    }


    else if (widget == "button_v_call_accept") {
      rs485Send("SIPA;");
    } else if (widget == "button_v_call_decline") {
      voip_status = VOIP_CANCEL;
      rs485Send("SIPE;");
    } else if (widget == "button_v_callHangup") {
      rs485Send("SIPE;");
    }

    else if (widget == "button_dlt_all") {
      lib_set_enaVisi("viewListAddr", 0);
      lib_set_enaVisi("view_contact_detail", 0);
      lib_set_visible("label_v_contactFull", 0);
      lib_set_enaVisi("view_dlt_all", 1);
    } else if (widget == "button_y_dltAll") {  //delete all delete
      lib_set_enaVisi("view_dlt_all", 0);
      lib_set_enaVisi("viewListAddr", 1);
      Serial.println("delete all contact");
      addressBookDelete();
    } else if (widget == "button_n_dltAll") {  //delete all batal
      lib_set_enaVisi("view_dlt_all", 0);
      lib_set_enaVisi("viewListAddr", 1);
    }

    else if (widget == "button_v_addAddrs") {
      if (!addressBookFullCheck()) {
        addMode = true;
        lib_set_enaVisi("button_dlt_all", 0);
        lib_set_enaVisi("button_v_addAddrs", 0);

        lib_set_enaVisi("viewListAddr", 0);
        lib_set_enaVisi("view_contact_detail", 1);
        lib_set_enaVisi("view_contact_edit", 1);

        lib_set_text("edit", "edit_ID", "");
        lib_set_text("edit", "edit_Name", "");
      }
    }

    else if (widget == "button_lv0") {
      contactDetail(0);
    } else if (widget == "button_lv1") {
      contactDetail(1);
    } else if (widget == "button_lv2") {
      contactDetail(2);
    } else if (widget == "button_lv3") {
      contactDetail(3);
    } else if (widget == "button_lv4") {
      contactDetail(4);
    } else if (widget == "button_lv5") {
      contactDetail(5);
    } else if (widget == "button_lv6") {
      contactDetail(6);
    } else if (widget == "button_lv7") {
      contactDetail(7);
    } else if (widget == "button_lv8") {
      contactDetail(8);
    } else if (widget == "button_lv9") {
      contactDetail(9);
    } else if (widget == "button_lv10") {
      contactDetail(10);
    } else if (widget == "button_lv11") {
      contactDetail(11);
    } else if (widget == "button_lv12") {
      contactDetail(12);
    } else if (widget == "button_lv13") {
      contactDetail(13);
    } else if (widget == "button_lv14") {
      contactDetail(14);
    } else if (widget == "button_lv15") {
      contactDetail(15);
    } else if (widget == "button_lv16") {
      contactDetail(16);
    } else if (widget == "button_lv17") {
      contactDetail(17);
    } else if (widget == "button_lv18") {
      contactDetail(18);
    } else if (widget == "button_lv19") {
      contactDetail(19);
    }

    else if (widget == "button_li_delete") {
      lib_set_enaVisi("view_conf_del", 1);

    } else if (widget == "button_dlt_s") {  //hapus
      voip_addressBook[contactIdx[voip_editIdx]][0] = "";
      voip_addressBook[contactIdx[voip_editIdx]][1] = "";

      contactEdited = true;
      addressBookSavetoMemory();
      delay(100);
      addressBookShow();
      closeContactDetail();

    } else if (widget == "button_ccl_s") {  //batal hapus
      lib_set_enaVisi("view_conf_del", 0);

    }

    else if (widget == "button_li_edit") {
      lib_set_enaVisi("view_contact_edit", 1);

      lib_set_text("edit", "edit_ID", voip_addressBook[contactIdx[voip_editIdx]][0]);
      lib_set_text("edit", "edit_Name", voip_addressBook[contactIdx[voip_editIdx]][1]);

      addMode = false;
      lib_set_enaVisi("button_dlt_all", 0);
      lib_set_enaVisi("button_v_addAddrs", 0);
      // lib_set_visible("image_iEdit", 1);

    } else if (widget == "button10") {  //simpan edit
      if (addMode) {                    //simpan new contact
        for (int i = 0; i < 20; i++) {
          if (voip_addressBook[i][0] == "") {
            voip_addressBook[i][0] = ed.getContactId();
            voip_addressBook[i][1] = ed.getContactName();
            lib_set_enaVisi("view_contact_edit", 0);
            voip_editIdx = 0;
            contactIdx[0] = i;
            break;
          }
        }
        lib_set_text("label", "label_nmr_s", voip_addressBook[contactIdx[voip_editIdx]][0]);
        lib_set_text("label", "label_n_slctd", "  " + voip_addressBook[contactIdx[voip_editIdx]][1]);

      } else {  //simpan edit mode
        voip_addressBook[contactIdx[voip_editIdx]][0] = ed.getContactId();
        voip_addressBook[contactIdx[voip_editIdx]][1] = ed.getContactName();

        lib_set_enaVisi("view_contact_edit", 0);
        lib_set_text("label", "label_nmr_s", voip_addressBook[contactIdx[voip_editIdx]][0]);
        lib_set_text("label", "label_n_slctd", "  " + voip_addressBook[contactIdx[voip_editIdx]][1]);
      }

      lib_set_enaVisi("button_dlt_all", 0);
      lib_set_enaVisi("button_v_addAddrs", 0);
      // lib_set_visible("image_iEdit", 0);

      addressBookPrint();

      addressBookSavetoMemory();
      contactEdited = true;
    } else if (widget == "button10_copy1") {  //batal edit
      lib_set_enaVisi("view_contact_edit", 0);
      if (addMode) {
        lib_set_enaVisi("view_contact_detail", 0);
        lib_set_enaVisi("viewListAddr", 1);
        lib_set_enaVisi("button_dlt_all", 1);
        lib_set_enaVisi("button_v_addAddrs", 1);
      } else {
        lib_set_enaVisi("button_dlt_all", 0);
        lib_set_enaVisi("button_v_addAddrs", 0);
      }

      // lib_set_visible("image_iEdit", 0);  //pensil
    }

    else if (widget == "button_li_call") {
      if (voip_status != VOIP_DISCONNECT) {
        rs485Send("SIPC" + voip_addressBook[contactIdx[voip_editIdx]][0] + ";");
      }
    }

    else if (widget == "button_bck_cdetail") {
      closeContactDetail();
      addressBookShow();
    }

    else if (widget == "button_v_volUp") {
      rs485Send("SIPU;");
    } else if (widget == "button_v_volDown") {
      rs485Send("SIPD;");
    }


    else if (widget == "button_refresh") {
      lib_set_text("label", "label_st_regist", "Registering");
      lib_set_bg_color("label_st_regis", 0xFFFFFF00);
      rs485Send("SIPO;");
    }

    else if (widget == "button_close_popup_voip") {
      lib_open_win("popup_voip", 0);
      rs485Send("SIPE;");
    }

    //end button voip
  }


  else if (type__ == "edit_float") {
    if (widget == "edit_inputRef" || widget == "edit_inputRef_e") {
      inpRef = val_float;
    }
  } else if (type__ == "edit_int") {
    if (widget == "edit_jams") {
      jam_anastesi = val_int;
    } else if (widget == "edit_fmnt") {
      menit_anastesi = val_int;
    } else if (widget == "edit_gdtk") {
      detik_anastesi = val_int;
    } else if (widget == "edit_date") {
      atur_tanggal = val_int;
    } else if (widget == "edit_mont") {
      atur_bulan = val_int;
    } else if (widget == "edit_year") {
      atur_tahun = val_int;
    } else if (widget == "edit_time") {
      atur_jam = val_int;
    } else if (widget == "edit_inut") {
      atur_menit = val_int;
    }

    else if (widget == "edit_pass2") {
    }

    //edit voip
    else if (widget == "edit_v_callNumber") {
      voip_callNumber = val_int;
    } else if (widget == "edit_v_id") {
      // voipSettingId == val_int;
    }

    else if (widget == "edit_sensor_min") {
      switch (sensorID) {
        case 0:
          min_N2O = val_int;
          if (min_N2O < 0) {
            min_N2O = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe 0 until 11");
            else lib_set_text("label", "label_warn_min", "Nilai harus 0 sampai 11");
            lib_set_enable("label_warn_min", 1);
            lib_set_value("edit", "edit_sensor_min", "0", "%d");
          }
          if (min_N2O >= max_N2O) {
            min_N2O = max_N2O - 1;
            lib_set_value("edit", "edit_sensor_min", String(min_N2O), "%d");
          }
          break;
        case 1:
          min_O2 = val_int;
          if (min_O2 < 0) {
            min_O2 = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe 0 until 11");
            else lib_set_text("label", "label_warn_min", "Nilai harus 0 sampai 11");
            lib_set_enable("label_warn_min", 1);
            lib_set_value("edit", "edit_sensor_min", "0", "%d");
          }
          if (min_O2 >= max_O2) {
            min_O2 = max_O2 - 1;
            lib_set_value("edit", "edit_sensor_min", String(min_O2), "%d");
          }
          break;
        case 2:
          min_Air = val_int;
          if (min_Air < 0) {
            min_O2 = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe 0 until 11");
            else lib_set_text("label", "label_warn_min", "Nilai harus 0 sampai 11");
            lib_set_enable("label_warn_min", 1);
            lib_set_value("edit", "edit_sensor_min", "0", "%d");
          }
          if (min_Air >= max_Air) {
            min_Air = max_Air - 1;
            lib_set_value("edit", "edit_sensor_min", String(min_Air), "%d");
          }
          break;
        case 3:
          min_Vacums = val_int;
          if (min_Vacums > 0) {
            min_Vacums = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe -750 until 0");
            else lib_set_text("label", "label_warn_min", "Nilai harus -750 sampai 0");
            lib_set_enable("label_warn_min", 1);
            lib_set_value("edit", "edit_sensor_min", "0", "%d");
          }
          if (min_Vacums <= max_Vacum) {
            min_Vacums = max_Vacum + 1;
            lib_set_value("edit", "edit_sensor_min", String(min_Vacums), "%d");
          }
          min_Vacum = min_Vacums;
          break;
        case 4:
          min_Temp = val_int;
          if (min_Temp < 0) {
            min_Temp = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe 0 until 85");
            else lib_set_text("label", "label_warn_min", "Nilai harus 0 sampai 85");
            lib_set_enable("label_warn_min", 1);
            lib_set_value("edit", "edit_sensor_min", "0", "%d");
          }
          if (min_Temp >= max_Temp) {
            min_Temp = max_Temp - 1;
            lib_set_value("edit", "edit_sensor_min", String(min_Temp), "%d");
          }
          break;
        case 5:
          min_Humid = val_int;
          if (min_Humid < 0) {
            min_Humid = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe 0 until 100");
            else lib_set_text("label", "label_warn_min", "Nilai harus 0 sampai 100");
            lib_set_enable("label_warn_min", 1);
            lib_set_value("edit", "edit_sensor_min", "0", "%d");
          }
          if (min_Humid >= max_Humid) {
            min_Humid = max_Humid - 1;
            lib_set_value("edit", "edit_sensor_min", String(min_Humid), "%d");
          }
          break;
      }
    }

    else if (widget == "edit_sensor_max") {
      switch (sensorID) {
        case 0:
          max_N2O = val_int;
          if (max_N2O > 11) {
            max_O2 = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_max", "Value mustbe 0 until 11");
            else lib_set_text("label", "label_warn_max", "Nilai harus 0 sampai 11");
            lib_set_enable("label_warn_max", 1);
            lib_set_value("edit", "edit_sensor_max", "11", "%d");
          }
          if (max_N2O <= min_N2O) {
            max_N2O = min_N2O + 1;
            lib_set_value("edit", "edit_sensor_max", String(max_N2O), "%d");
          }
          break;
        case 1:
          max_O2 = val_int;
          if (max_O2 > 11) {
            max_O2 = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_max", "Value mustbe 0 until 11");
            else lib_set_text("label", "label_warn_max", "Nilai harus 0 sampai 11");
            lib_set_enable("label_warn_max", 1);
            lib_set_value("edit", "edit_sensor_max", "11", "%d");
          }
          if (max_O2 <= min_O2) {
            max_O2 = min_O2 + 1;
            lib_set_value("edit", "edit_sensor_max", String(max_O2), "%d");
          }
          break;
        case 2:
          max_Air = val_int;
          if (max_Air > 11) {
            max_Air = 0;
            if (bahasa == "english") lib_set_text("label", "label_warn_max", "Value mustbe 0 until 11");
            else lib_set_text("label", "label_warn_max", "Nilai harus 0 sampai 11");
            lib_set_enable("label_warn_max", 1);
            lib_set_value("edit", "edit_sensor_max", "11", "%d");
          }
          if (max_Air <= min_Air) {
            max_Air = min_Air + 1;
            lib_set_value("edit", "edit_sensor_max", String(max_Air), "%d");
          }
          break;
        case 3:
          max_Vacums = val_int;
          if (max_Vacums < -750) {
            max_Vacums = -750;
            if (bahasa == "english") lib_set_text("label", "label_warn_max", "Value mustbe -750 until 0");
            else lib_set_text("label", "label_warn_max", "Nilai harus -750 sampai 0");
            lib_set_enable("label_warn_max", 1);
            lib_set_value("edit", "edit_sensor_max", "-750", "%d");
          }
          if (max_Vacums >= min_Vacum) {
            max_Vacums = min_Vacum - 1;
            lib_set_value("edit", "edit_sensor_max", String(max_Vacums), "%d");
          }
          max_Vacum = max_Vacums;
          break;
        case 4:
          max_Temp = val_int;
          if (max_Temp > 85) {
            max_Temp = 85;
            if (bahasa == "english") lib_set_text("label", "label_warn_max", "Value mustbe 0 until 85");
            else lib_set_text("label", "label_warn_max", "Nilai harus 0 sampai 85");
            lib_set_enable("label_warn_max", 1);
            lib_set_value("edit", "edit_sensor_max", "85", "%d");
          }
          if (max_Temp <= min_Temp) {
            max_Temp = min_Temp + 1;
            lib_set_value("edit", "edit_sensor_max", String(max_Temp), "%d");
          }
          break;
        case 5:
          if (max_Humid > 100) {
            max_Humid = 100;
            if (bahasa == "english") lib_set_text("label", "label_warn_min", "Value mustbe 0 until 100");
            else lib_set_text("label", "label_warn_max", "Nilai harus 0 sampai 100");
            lib_set_enable("label_warn_max", 1);
            lib_set_value("edit", "edit_sensor_max", "100", "%d");
          }
          max_Humid = val_int;
          if (max_Humid <= min_Humid) {
            max_Humid = min_Humid + 1;
            lib_set_value("edit", "edit_sensor_max", String(max_Humid), "%d");
          }
          break;
      }
    }
    //edit room not yet
  }

  else if (type__ == "switch") {
    int sw_val = val_int;
    if (widget == "swtch1000000") {
      preferences.begin("control", false);
      preferences.putBool("SW1", (sw_val == 1) ? true : false);
      sw1 = sw_val;
      if (sw_val == 1) digitalWrite(lampu1, LOW);
      else digitalWrite(lampu1, HIGH);
      preferences.end();
    } else if (widget == "swtch2000000") {
      preferences.begin("control", false);
      preferences.putBool("SW2", (sw_val == 1) ? true : false);
      if (sw_val == 1) digitalWrite(lampu2, LOW);
      else digitalWrite(lampu2, HIGH);
      sw2 = sw_val;
      preferences.end();
    } else if (widget == "swtch3000000") {
      preferences.begin("control", false);
      preferences.putBool("SW3", (sw_val == 1) ? true : false);
      if (sw_val == 1) digitalWrite(lampu3, LOW);
      else digitalWrite(lampu3, HIGH);
      sw3 = sw_val;
      preferences.end();
    } else if (widget == "swtch4000000") {
      preferences.begin("control", false);
      preferences.putBool("SW4", (sw_val == 1) ? true : false);
      if (sw_val == 1) digitalWrite(lampu4, LOW);
      else digitalWrite(lampu4, HIGH);
      sw4 = sw_val;
      preferences.end();
    } else if (widget == "swtch5000000") {
      preferences.begin("control", false);
      preferences.putBool("SW5", (sw_val == 1) ? true : false);
      if (sw_val == 1) digitalWrite(lampu5, LOW);
      else digitalWrite(lampu5, HIGH);
      sw5 = sw_val;
      preferences.end();
    } else if (widget == "swtch6000000") {
      preferences.begin("control", false);
      preferences.putBool("SW6", (sw_val == 1) ? true : false);
      if (sw_val == 1) digitalWrite(fog, LOW);
      else digitalWrite(fog, HIGH);
      sw6 = sw_val;
      preferences.end();
    } else if (widget == "swtch7000000") {
      preferences.begin("control", false);
      preferences.putBool("SW7", (sw_val == 1) ? true : false);
      if (sw_val == 1) digitalWrite(hvac, LOW);
      else digitalWrite(hvac, HIGH);
      sw7 = sw_val;
      preferences.end();
    } else if (widget == "swtch8000000") {
      preferences.begin("control", false);
      alarmEnable = (sw_val == 1) ? true : false;
      preferences.putBool("alarmEnable", alarmEnable);
      alarmEnable = sw_val;
      preferences.end();
    }
  }

  else if (type__ == "radio_button") {
    if (widget == "rdio_indo" && val_int == 1) {
      bahasa = "indonesia";
      hal1 = 0;
      halCtr = 0;
    } else if (widget == "rdio_eng_" && val_int == 1) {
      bahasa = "english";
      hal1 = 0;
      halCtr = 0;
    }
  } else if (type__ == "slider") {
    if (widget == "slider1") {
      kecerahan = val_int;
      if (kecerahan < 10) kecerahan = 10;
      lib_set_value("slider", "slider1", String(kecerahan), "%d");
      Serial2.print(F("ST<{\"cmd_code\":\"set_brightness\",\"type\":\"system\",\"brightness\":"));
      Serial2.print(kecerahan);
      Serial2.println(F("}>ET"));

      Serial.print(F("ST<{\"cmd_code\":\"set_brightness\",\"type\":\"system\",\"brightness\":"));
      Serial.print(kecerahan);
      Serial.println(F("}>ET"));

      preferences.begin("setting", false);
      preferences.putInt("Kecerahan", kecerahan);
      preferences.end();
    } else if (widget == "slider2") {
      volume = val_int;
      Serial.println("vlume : " + String(volume));
      // Serial2.println(F("ST<{\"cmd_code\":\"set_vol\",\"type\":\"system\",\"" + String(volume) + "\":50}>ET"));
      // ST<{ "cmd_code": "set_vol", "type": "system", "vol": 50 }>
      //   ET
      lib_set_value("slider", "slider2", String(volume), "%d");
      Serial2.print(F("ST<{\"cmd_code\":\"set_vol\",\"type\":\"system\",\"vol\":"));
      Serial2.print(volume);
      Serial2.println(F("}>ET"));
      delay(10);

      Serial2.print(F("ST<{\"cmd_code\":\"set_vol\",\"type\":\"system\",\"vol\":"));
      Serial2.print(volume);
      Serial2.println(F("}>ET"));

      Serial.print(F("ST<{\"cmd_code\":\"set_vol\",\"type\":\"system\",\"vol\":"));
      Serial.print(volume);
      Serial.println(F("}>ET"));
      preferences.begin("setting", false);
      preferences.putInt("Volume", volume);
      preferences.end();

      // } else if (widget == "slider4" && ed.getslidFix() == true) {

    } else if (widget == "slider4") {

      vol_music = map(val_int, 0, 100, 0, 30);
      DFVolume = vol_music;

      if (millis() - timerUpdateVolume > 500) {
        df_player("volume", DFVolume);
        timerUpdateVolume = millis();
      }

      volume_music = val_int;
      lib_set_value("slider", "slider4", String(volume_music), "%d");
      setSlid(false);
    }
  } else if (type__ == "time_clock" && widget == "digit_clock4") {
    // ntime = val_int;
  }
}

void set_date_time(int years, int months, int date, int hours, int minutes) {

  stone_print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock2\",\"date\":\""));
  stone_print(years);
  stone_print(F("-"));
  stone_print(months);
  stone_print(F("-"));
  stone_print(date);
  stone_print(F(" "));
  stone_print(hours);
  stone_print(F(":"));
  stone_print(minutes);
  stone_println(F("\"}>ET"));

  stone_print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock4\",\"date\":\""));
  stone_print(years);
  stone_print(F("-"));
  stone_print(months);
  stone_print(F("-"));
  stone_print(date);
  stone_print(F(" "));
  stone_print(hours);
  stone_print(F(":"));
  stone_print(minutes);
  stone_println(F("\"}>ET"));

  stone_print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock6\",\"date\":\""));
  stone_print(years);
  stone_print(F("-"));
  stone_print(months);
  stone_print(F("-"));
  stone_print(date);
  stone_print(F(" "));
  stone_print(hours);
  stone_print(F(":"));
  stone_print(minutes);
  stone_println(F("\"}>ET"));

  stone_print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock7\",\"date\":\""));
  stone_print(years);
  stone_print(F("-"));
  stone_print(months);
  stone_print(F("-"));
  stone_print(date);
  stone_print(F(" "));
  stone_print(hours);
  stone_print(F(":"));
  stone_print(minutes);
  stone_println(F("\"}>ET"));
}

void set_bahasa(String _bahasa) {
  if (_bahasa == "english") {
    lib_set_text("label", "label1_sub_hal1", room + " Operating Room");
    lib_set_text("label", "label1_text_waktu_anestesi", "ANESTHESIA TIME");
    lib_set_text("label", "label1_text_waktu_operasi", "OPERATING TIME");
    lib_set_text("label", "label1_gas_medik", "MEDICAL GAS PRESSURE STATUS");
    lib_set_text("label", "label_ambient", "ROOM AMBIENT");
    lib_set_text("label", "label1_temperatur", "TEMPERATURE (˚C)");
    lib_set_text("label", "label1_kelembapan", "HUMIDITY (%)");
    lib_set_text("label", "label_tittle_tekanan", "PRESSURE (kPa)");
    lib_set_text("label", "label1_gas_udara", "AIR");
    lib_set_text("label", "label1_vacuum", "VACUUM");
    lib_set_text("button", "butt_d_str", "START");
    lib_set_text("button", "butt_a_str", "START");
    lib_set_text("label", "label_timeoutWait", "PLEASE WAIT ...");
    lib_set_text("label", "label1_sub_hal1", room + " Operating Room");
    lib_set_text("label", "label1_text_waktu_anestesi", "ANESTHESIA TIME");
    lib_set_text("label", "label1_text_waktu_operasi", "OPERATING TIME");
    lib_set_text("label", "label1_gas_medik", "MEDICAL GAS PRESSURE STATUS");
    lib_set_text("label", "label_ambient", "ROOM AMBIENT");
    lib_set_text("label", "label1_temperatur", "TEMPERATURE (˚C)");
    lib_set_text("label", "label1_kelembapan", "HUMIDITY (%)");
    lib_set_text("label", "label_tittle_tekanan", "PRESSURE (kPa)");
    lib_set_text("label", "label1_gas_udara", "AIR");
    lib_set_text("label", "label1_vacuum", "VACUUM");
    lib_set_text("button", "butt_d_str", "START");
    lib_set_text("button", "butt_a_str", "START");
    lib_set_text("label", "label_timeoutWait", "PLEASE WAIT ...");
    delay(10);
    lib_set_text("label", "label_atur_bahasa", "Language");
    lib_set_text("label", "labelctrl_kecerahan_layar", "Display Brightness");
    lib_set_text("label", "label1_atur_tanggal_waktu", "Date and Time Setting");
    lib_set_text("label", "labelset_atur_volume", "Volume Setting");
    lib_set_text("label", "labelset_nama_ruangan", "Room");
    lib_set_text("label", "label_atur_bahasa", "Language");
    lib_set_text("label", "labelctrl_kecerahan_layar", "Display Brightness");
    lib_set_text("label", "label1_atur_tanggal_waktu", "Date and Time Setting");
    lib_set_text("label", "labelset_atur_volume", "Volume Setting");
    lib_set_text("label", "labelset_nama_ruangan", "Room");
    delay(10);
    lib_set_text("label", "label_min_pressr_n2o", "Min N2O Pressure");
    lib_set_text("label", "label_max_pressr_n2o", "Max N2O Pressure");
    lib_set_text("label", "label_min_pressr_o2", "Min O2 Pressure");
    lib_set_text("label", "label_max_O2", "Max O2 Pressure");
    lib_set_text("label", "Udaraa", "Air (BAR)");
    lib_set_text("label", "Vakum", "Vacuum (mmHg)");
    lib_set_text("label", "label_min_udaraa", "Min Air Pressure");
    lib_set_text("label", "label1_max_udaara", "Max Air Pressure");
    lib_set_text("label", "label_min_pressr_n2o", "Min N2O Pressure");
    lib_set_text("label", "label_max_pressr_n2o", "Max N2O Pressure");
    lib_set_text("label", "label_min_pressr_o2", "Min O2 Pressure");
    lib_set_text("label", "label_max_O2", "Max O2 Pressure");
    lib_set_text("label", "Udaraa", "Air (BAR)");
    lib_set_text("label", "Vakum", "Vacuum (mmHg)");
    lib_set_text("label", "label_min_udaraa", "Min Air Pressure");
    lib_set_text("label", "label1_max_udaara", "Max Air Pressure");
    delay(10);
    lib_set_text("label", "label1_min_vakum", "Min Vacuum Pressure");
    lib_set_text("label", "label1_max_vakum", "Max Vacuum Pressure");
    lib_set_text("label", "Suhu", "Temperature (˚C)");
    lib_set_text("label", "label1_max_suhu", "Max Temperature");
    lib_set_text("label", "label1_min_suhu", "Min Temperature");
    lib_set_text("label", "Kelembapan", "Humidity (%)");
    lib_set_text("label", "label_max_kelembapan", "Max Humidity");
    lib_set_text("label", "label1_min_kelembapan_copy1", "Min Humidity");
    lib_set_text("label", "labelKodeKeamanan", "Security Code");
    lib_set_text("label", "label1_min_vakum", "Min Vacuum Pressure");
    lib_set_text("label", "label1_max_vakum", "Max Vacuum Pressure");
    lib_set_text("label", "Suhu", "Temperature (˚C)");
    lib_set_text("label", "label1_max_suhu", "Max Temperature");
    lib_set_text("label", "label1_min_suhu", "Min Temperature");
    lib_set_text("label", "Kelembapan", "Humidity (%)");
    lib_set_text("label", "label_max_kelembapan", "Max Humidity");
    lib_set_text("label", "label1_min_kelembapan_copy1", "Min Humidity");
    lib_set_text("label", "labelKodeKeamanan", "Security Code");

    delay(10);
    lib_set_text("edit", "edit_kode", "Enter Security Code");
    lib_set_text("button", "button_Bataal", "Cancel");
    lib_set_text("label", "labelverif", "Incorrect Code!");
    lib_set_text("label", "label_bg_settinganes", "    Set Anaesthesia Time");
    lib_set_text("label", "label_jam_anestesi", "Hours");
    lib_set_text("label", "label_menit_anestesi", "Minutes");
    lib_set_text("label", "label_detik_anestesi", "Seconds");
    lib_set_text("edit", "edit_kode", "Enter Security Code");
    lib_set_text("button", "button_Bataal", "Cancel");
    lib_set_text("label", "labelverif", "Incorrect Code!");
    lib_set_text("label", "label_bg_settinganes", "    Set Anaesthesia Time");
    lib_set_text("label", "label_jam_anestesi", "Hours");
    lib_set_text("label", "label_menit_anestesi", "Minutes");
    lib_set_text("label", "label_detik_anestesi", "Seconds");

    delay(10);
    lib_set_text("button", "butt_Jsav", "Save");
    lib_set_text("button", "butt_g_sv", "Save");
    lib_set_text("button", "butt_Gsav", "Save");
    lib_set_text("label", "label1_lampu1_", "Light 1");
    lib_set_text("label", "label1_lampu2_", "Light 2");
    lib_set_text("label", "label_lampu3", "Light 3");
    lib_set_text("label", "label_lampu4", "Light 4");
    lib_set_text("label", "label_lampu5", "Light 5");
    lib_set_text("button", "butt_Jsav", "Save");
    lib_set_text("button", "butt_g_sv", "Save");
    lib_set_text("button", "butt_Gsav", "Save");
    lib_set_text("label", "label1_lampu1_", "Light 1");
    lib_set_text("label", "label1_lampu2_", "Light 2");
    lib_set_text("label", "label_lampu3", "Light 3");
    lib_set_text("label", "label_lampu4", "Light 4");
    lib_set_text("label", "label_lampu5", "Light 5");
  } else {
    lib_set_text("label", "label1_sub_hal1", "Ruang Operasi " + room);
    lib_set_text("label", "label1_text_waktu_anestesi", "WAKTU ANASTESI");
    lib_set_text("label", "label1_text_waktu_operasi", "WAKTU OPERASI");
    lib_set_text("label", "label1_gas_medik", "STATUS TEKANAN GAS MEDIS");
    lib_set_text("label", "label_ambient", "AMBIENT RUANGAN");
    lib_set_text("label", "label1_temperatur", "SUHU (˚C)");
    lib_set_text("label", "label1_kelembapan", "KELEMBAPAN (%)");
    lib_set_text("label", "label_tittle_tekanan", "TEKANAN (kPa)");
    lib_set_text("label", "label1_gas_udara", "UDARA");
    lib_set_text("label", "label1_vacuum", "VAKUM");
    lib_set_text("button", "butt_d_str", "MULAI");
    lib_set_text("button", "butt_a_str", "MULAI");
    lib_set_text("label", "label_timeoutWait", "SILAHKAN TUNGGU ...");
    lib_set_text("label", "label1_sub_hal1", "Ruang Operasi " + room);
    lib_set_text("label", "label1_text_waktu_anestesi", "WAKTU ANASTESI");
    lib_set_text("label", "label1_text_waktu_operasi", "WAKTU OPERASI");
    lib_set_text("label", "label1_gas_medik", "STATUS TEKANAN GAS MEDIS");
    lib_set_text("label", "label_ambient", "AMBIENT RUANGAN");
    lib_set_text("label", "label1_temperatur", "SUHU (˚C)");
    lib_set_text("label", "label1_kelembapan", "KELEMBAPAN (%)");
    lib_set_text("label", "label_tittle_tekanan", "TEKANAN (kPa)");
    lib_set_text("label", "label1_gas_udara", "UDARA");
    lib_set_text("label", "label1_vacuum", "VAKUM");
    lib_set_text("button", "butt_d_str", "MULAI");
    lib_set_text("button", "butt_a_str", "MULAI");
    lib_set_text("label", "label_timeoutWait", "SILAHKAN TUNGGU ...");
    delay(10);
    lib_set_text("label", "label_atur_bahasa", "Bahasa");
    lib_set_text("label", "labelctrl_kecerahan_layar", "Kecerahan Layar");
    lib_set_text("label", "label1_atur_tanggal_waktu", "Atur Tanggal dan Waktu");
    lib_set_text("label", "labelset_atur_volume", "Atur Suara");
    lib_set_text("label", "labelset_nama_ruangan", "Nama Ruangan");
    lib_set_text("label", "label_atur_bahasa", "Bahasa");
    lib_set_text("label", "labelctrl_kecerahan_layar", "Kecerahan Layar");
    lib_set_text("label", "label1_atur_tanggal_waktu", "Atur Tanggal dan Waktu");
    lib_set_text("label", "labelset_atur_volume", "Atur Suara");
    lib_set_text("label", "labelset_nama_ruangan", "Nama Ruangan");
    delay(10);
    lib_set_text("label", "label_min_pressr_n2o", "Min Tekanan N2O");
    lib_set_text("label", "label_max_pressr_n2o", "Max Tekanan N2O");
    lib_set_text("label", "label_min_pressr_o2", "Min Tekanan O2");
    lib_set_text("label", "label_max_O2", "Max Tekanan O2");
    lib_set_text("label", "Udaraa", "Udara (BAR)");
    lib_set_text("label", "Vakum", "Vakum (mmHg)");
    lib_set_text("label", "label_min_udaraa", "Min Tekanan Udara");
    lib_set_text("label", "label1_max_udaara", "Max Tekanan Udara");
    lib_set_text("label", "label_min_pressr_n2o", "Min Tekanan N2O");
    lib_set_text("label", "label_max_pressr_n2o", "Max Tekanan N2O");
    lib_set_text("label", "label_min_pressr_o2", "Min Tekanan O2");
    lib_set_text("label", "label_max_O2", "Max Tekanan O2");
    lib_set_text("label", "Udaraa", "Udara (BAR)");
    lib_set_text("label", "Vakum", "Vakum (mmHg)");
    lib_set_text("label", "label_min_udaraa", "Min Tekanan Udara");
    lib_set_text("label", "label1_max_udaara", "Max Tekanan Udara");
    delay(10);
    lib_set_text("label", "label1_min_vakum", "Min Tekanan Vakum");
    lib_set_text("label", "label1_max_vakum", "Max Tekanan Vakum");
    lib_set_text("label", "Suhu", "Suhu (˚C)");
    lib_set_text("label", "label1_max_suhu", "Max Suhu");
    lib_set_text("label", "label1_min_suhu", "Min Suhu");
    lib_set_text("label", "Kelembapan", "Kelembapan (%)");
    lib_set_text("label", "label_max_kelembapan", "Max Kelembapan");
    lib_set_text("label", "label1_min_kelembapan_copy1", "Min Kelembapan");
    lib_set_text("label", "labelKodeKeamanan", "Kode Keamanan");
    lib_set_text("label", "label1_min_vakum", "Min Tekanan Vakum");
    lib_set_text("label", "label1_max_vakum", "Max Tekanan Vakum");
    lib_set_text("label", "Suhu", "Suhu (˚C)");
    lib_set_text("label", "label1_max_suhu", "Max Suhu");
    lib_set_text("label", "label1_min_suhu", "Min Suhu");
    lib_set_text("label", "Kelembapan", "Kelembapan (%)");
    lib_set_text("label", "label_max_kelembapan", "Max Kelembapan");
    lib_set_text("label", "label1_min_kelembapan_copy1", "Min Kelembapan");
    lib_set_text("label", "labelKodeKeamanan", "Kode Keamanan");
    delay(10);
    lib_set_text("edit", "edit_kode", "Masukkan Kode Keamanan");
    lib_set_text("button", "button_Bataal", "Batal");
    lib_set_text("label", "labelverif", "Kode Salah!");
    lib_set_text("label", "label_bg_settinganes", "Atur Waktu Anastesi");
    lib_set_text("label", "label_jam_anestesi", "Jam");
    lib_set_text("label", "label_menit_anestesi", "Menit");
    lib_set_text("label", "label_detik_anestesi", "Detik");
    lib_set_text("label", "labelKodeKeamanan", "Security Code");
    lib_set_text("edit", "edit_kode", "Masukkan Kode Keamanan");
    lib_set_text("button", "button_Bataal", "Batal");
    lib_set_text("label", "labelverif", "Kode Salah!");
    lib_set_text("label", "label_bg_settinganes", "Atur Waktu Anastesi");
    lib_set_text("label", "label_jam_anestesi", "Jam");
    lib_set_text("label", "label_menit_anestesi", "Menit");
    lib_set_text("label", "label_detik_anestesi", "Detik");
    lib_set_text("label", "labelKodeKeamanan", "Security Code");

    delay(10);
    lib_set_text("button", "butt_Jsav", "Simpan");
    lib_set_text("button", "butt_g_sv", "Simpan");
    lib_set_text("button", "butt_Gsav", "Simpan");
    lib_set_text("label", "label1_lampu1_", "Lampu 1");
    lib_set_text("label", "label1_lampu2_", "Lampu 2");
    lib_set_text("label", "label_lampu3", "Lampu 3");
    lib_set_text("label", "label_lampu4", "Lampu 4");
    lib_set_text("label", "label_lampu5", "Lampu 5");
  }
}

void check_gas(float _data_O2, float _data_N2O, float _data_Air, int _data_Vacuum, bool upt) {
  //N2O
  if (_data_N2O < min_N2O * 1.0 || upt) stat_N2O = 0;
  else if (_data_N2O > max_N2O * 1.0) stat_N2O = 2;
  else stat_N2O = 1;

  if (stat_N2O != stat_N2O_cpy || upt) {
    status_pressure(stat_N2O, "label_status_n2o");
    delay(10);
    status_pressure(stat_N2O, "label_status_n2o");
    checkAlarm();
  }
  stat_N2O_cpy = stat_N2O;

  //O2
  if (_data_O2 < min_O2 * 1.0 || upt) stat_O2 = 0;
  else if (_data_O2 > max_O2 * 1.0) stat_O2 = 2;
  else stat_O2 = 1;

  if (stat_O2 != stat_O2_cpy || upt) {
    status_pressure(stat_O2, "label_status_o2");
    delay(10);
    status_pressure(stat_O2, "label_status_o2");
    checkAlarm();
  }
  stat_O2_cpy = stat_O2;


  // Air
  if (_data_Air < min_Air * 1.0) stat_Udara = 0;
  else if (_data_Air > max_Air * 1.0) stat_Udara = 2;
  else stat_Udara = 1;

  if (stat_Udara != stat_Udara_cpy) {
    status_pressure(stat_Udara, "label_status_udara");
    delay(10);
    status_pressure(stat_Udara, "label_status_udara");
    checkAlarm();
  }
  stat_Udara_cpy = stat_Udara;

  // vakum
  if (abs(_data_Vacuum) < abs(min_Vacum)) stat_Vakum = 0;
  else if (abs(_data_Vacuum) > abs(max_Vacum)) stat_Vakum = 2;
  else stat_Vakum = 1;

  if (stat_Vakum != stat_Vakum_cpy) {
    status_pressure(stat_Vakum, "label_status_vakum");
    delay(10);
    status_pressure(stat_Vakum, "label_status_vakum");
    checkAlarm();
  }
  stat_Vakum_cpy = stat_Vakum;
}

void check_temp(int ch_temp) {
  if (ch_temp < min_Temp) status_temperature = 0;
  else if (ch_temp > max_Temp) status_temperature = 2;
  else status_temperature = 1;

  if (status_temperature != status_temperature_cpy) {
    status_ambient(status_temperature, "label_status_suhu");
    delay(10);
    status_ambient(status_temperature, "label_status_suhu");
    checkAlarm();
  }
  status_temperature_cpy = status_temperature;
}

void check_humid(int ch_hum) {
  if (ch_hum < min_Humid) status_humidity = 0;
  else if (ch_hum > max_Humid) status_humidity = 2;
  else status_humidity = 1;
  if (status_humidity != status_humidity_cpy) {
    status_ambient(status_humidity, "label_status_kelembapan");
    delay(10);
    status_ambient(status_humidity, "label_status_kelembapan");
    checkAlarm();
  }
  status_humidity_cpy = status_humidity;
}
void check_press(float ch_press) {
}
void check_co2(int ch_co2) {
  if (ch_co2 > 1000) status_co2 = 2;
  else status_co2 = 1;
  if (status_co2 != status_co2_cpy) {
    status_ambient(status_co2, "label_status_co2");
    delay(10);
    status_ambient(status_co2, "label_status_co2");
  }
  status_co2_cpy = status_co2;
}

void status_update(void) {
  Serial.println("update status Start");
  status_pressure(stat_O2, "label_status_o2");
  status_pressure(stat_N2O, "label_status_n2o");
  status_pressure(stat_Udara, "label_status_udara");
  status_pressure(stat_Vakum, "label_status_vakum");
  status_ambient(status_temperature, "label_status_suhu");
  status_ambient(status_humidity, "label_status_kelembapan");
  status_ambient(status_co2, "label_status_co2");
  Serial.println("update status done");
}

void status_pressure(int stat, String label_gas) {
  char* cstr = new char[label_gas.length() + 1];
  strcpy(cstr, label_gas.c_str());

  if (bahasa == "english") {
    switch (stat) {
      case 0:

        lib_set_text("label", cstr, "LOW");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_gas);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(merah);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_gas);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(merah);
        sdebug_println(F("}>ET"));
        break;
      case 1:
        lib_set_text("label", cstr, "NORMAL");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_gas);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(hijau);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_gas);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(hijau);
        sdebug_println(F("}>ET"));
        break;
      case 2:
        lib_set_text("label", cstr, "HIGH");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_gas);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(kuning);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_gas);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(kuning);
        sdebug_println(F("}>ET"));
        break;
    }
  } else {
    switch (stat) {
      case 0:
        lib_set_text("label", cstr, "RENDAH");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_gas);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(merah);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_gas);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(merah);
        sdebug_println(F("}>ET"));
        break;
      case 1:
        lib_set_text("label", cstr, "NORMAL");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_gas);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(hijau);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_gas);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(hijau);
        sdebug_println(F("}>ET"));
        break;
      case 2:
        lib_set_text("label", cstr, "TINGGI");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_gas);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(kuning);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_gas);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(kuning);
        sdebug_println(F("}>ET"));
        break;
    }
  }
}

void status_ambient(int stat_, String label_sensor) {
  char* cstr = new char[label_sensor.length() + 1];
  strcpy(cstr, label_sensor.c_str());

  // checkAlarm();

  if (bahasa == "english") {
    switch (stat_) {
      case 0:
        lib_set_text("label", cstr, "LOW");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_sensor);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(merah);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_sensor);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(merah);
        sdebug_println(F("}>ET"));

        break;
      case 1:
        lib_set_text("label", cstr, "NORMAL");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_sensor);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(hijau);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_sensor);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(hijau);
        sdebug_println(F("}>ET"));

        break;
      case 2:
        lib_set_text("label", cstr, "HIGH");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_sensor);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(kuning);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_sensor);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(kuning);
        sdebug_println(F("}>ET"));

        break;
    }
  } else {
    switch (stat_) {
      case 0:
        lib_set_text("label", cstr, "RENDAH");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_sensor);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(merah);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_sensor);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(merah);
        sdebug_println(F("}>ET"));

        break;
      case 1:
        lib_set_text("label", cstr, "NORMAL");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_sensor);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(hijau);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_sensor);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(hijau);
        sdebug_println(F("}>ET"));

        break;
      case 2:
        lib_set_text("label", cstr, "TINGGI");
        //lib_set_text("label", label_sensor, "TINGGI");
        stone_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        stone_print(label_sensor);
        stone_print("\",\"color_object\":\"bg_color\",\"color\":");
        stone_print(kuning);
        stone_println(F("}>ET"));
        sdebug_print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\""));
        sdebug_print(label_sensor);
        sdebug_print("\",\"color_object\":\"bg_color\",\"color\":");
        sdebug_print(kuning);
        sdebug_println(F("}>ET"));

        break;
    }
  }
}

void checkAlarm(void) {
  if (alarmEnable == true) {
    if (stat_O2 == 1 && stat_N2O == 1 && stat_Udara == 1 && stat_Vakum == 1 && status_temperature == 1 && status_humidity == 1) {  //normal semua
      isAlarm = 0;
      popupAlarm(0);
    } else {

      idxLabelAlarm = 0;

      if (stat_O2 == 0) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "O2 Pressure" : "Tekanan O2";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Below Threshold" : "Kurang dari Ambang Batas";
        idxLabelAlarm++;
      } else if (stat_O2 == 2) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "O2 Pressure" : "Tekanan O2";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Above Threshold" : "Lebih dari Ambang Batas";
        idxLabelAlarm++;
      }
      if (stat_N2O == 0) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "N2O Pressure" : "Tekanan N2O";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Below Threshold" : "Kurang dari Ambang Batas";
        idxLabelAlarm++;
      } else if (stat_N2O == 2) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "N2O Pressure" : "Tekanan N2O ";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Above Threshold" : "Lebih dari Ambang Batas";
        idxLabelAlarm++;
      }

      if (stat_Udara == 0) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "AIR Pressure" : "Tekanan Udara";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Below Threshold" : "Kurang dari Ambang Batas";
        idxLabelAlarm++;
      } else if (stat_Udara == 2) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "AIR Pressure" : "Tekanan Udara";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Above Threshold" : "Lebih dari Ambang Batas";
        idxLabelAlarm++;
      }

      if (stat_Vakum == 0) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "VACUUM Pressure" : "Tekanan Vakum";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Below Threshold" : "Kurang dari Ambang Batas";
        idxLabelAlarm++;
      } else if (stat_Vakum == 2) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "VACUUM Pressure" : "Tekanan Vakum";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Above Threshold" : "Lebih dari Ambang batas";
        idxLabelAlarm++;
      }

      if (status_temperature == 0) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "Room Temperature" : "Suhu Ruangan";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Below Threshold" : "Lebih Rendah dari Ambang Batas";
        idxLabelAlarm++;
      } else if (status_temperature == 2) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "Room Temperature" : "Suhu Ruangan";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Above Threshold" : "Lebih Tinggi dari Ambang Batas";
        idxLabelAlarm++;
      }

      if (status_humidity == 0) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "Room Humidity" : "Kelembapan Ruangan";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Below Threshold" : "Lebih Rendah dari Ambang Batas";
        idxLabelAlarm++;
      } else if (status_humidity == 2) {
        labelPopupAlarm1[idxLabelAlarm] = (bahasa == "english") ? "Room Humidity" : "Kelembapan Ruangan";
        labelPopupAlarm2[idxLabelAlarm] = (bahasa == "english") ? "Above Threshold" : "Lebih Tinggi dari Ambang Batas";
        idxLabelAlarm++;
      }

      isAlarm = 1;
      if (alarmDelayDone == true) {
        popupAlarm(1);
      }

      labelAlarmUpdate();
    }
  } else isAlarm = 0;
  Serial.println("is Alarm state : " + String(isAlarm));
}

void popupAlarm(int status) {
  if (status == 1) {
    delay(100);
    stone_print(F("ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"popup_alarm\"}>ET"));
    if (bahasa == "english") {
      lib_set_text("label", "button_a_tutup", "Snooze");
      lib_set_text("label", "button_a_mati", "Stop");
    } else {
      lib_set_text("label", "button_a_tutup", "Tunda");
      lib_set_text("label", "button_a_mati", "Matikan");
    }
    Serial.println("popup alarm open");
    snooze = 0;
  } else if (status == 0) {

    stone_print(F("ST<{\"cmd_code\":\"close_win\",\"type\":\"window\",\"widget\":\"popup_alarm\"}>ET"));
    Serial.println("popup alarm close");
  }
}

void labelAlarmUpdate(void) {
  delay(100);
  lib_set_text("label", "label_alarm_1", labelPopupAlarm1[idxLabelAlarmNow]);
  lib_set_text("label", "label_alarm_2", labelPopupAlarm2[idxLabelAlarmNow]);
  idxLabelAlarmNow++;
  if (idxLabelAlarmNow >= idxLabelAlarm) idxLabelAlarmNow = 0;
}


void calibrationPopup(void) {
  Serial.println(kalibrasiState);

  switch (kalibrasiState) {
    case 0:
      Serial.println("case 0");
      lib_set_enaVisi("view_info_1", 1);
      delay(100);
      if (sensorID == 0 || sensorID == 1 || sensorID == 2) {
        lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Tekanan:");
        lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 1 hingga 10 Bar. Untuk 6 dan 11");
        lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 1 hingga 11 Bar.");
        //lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Tekanan:");
      } else if (sensorID == 3) {
        lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Vakum:");
        lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada -675 hingga 0 mmHg. Untuk 6 dan 11");
        lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada -750 hingga 0 mmHg.");
      } else if (sensorID == 4) {
        lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Suhu:");
        lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 16 hingga 25 °C. Untuk 6 dan 11");
        lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 16 hingga 26 °C.");
      }

      else if (sensorID == 5) {
        lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Kelembapan:");
        lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 30 hingga 66 % . Dan untuk 6 dan 11");
        lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 30 hingga 70 %.");
      }
      /*if (sensorID == 0 || sensorID == 1 || sensorID == 2) {
        if (bahasa == "english") {
          lib_set_text("label", "label2_copy1", "Pressure Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 1 to 10 Bar. For 6 and 11");
          lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from 1 to 11 Bar.");
          lib_set_text("label", "label2_copy1", "Pressure Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 1 to 10 Bar. For 6 and 11");
          lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from 1 to 11 Bar.");
        } else {
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Tekanan:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 1 hingga 10 Bar. Untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 1 hingga 11 Bar.");
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Tekanan:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 1 hingga 10 Bar. Untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 1 hingga 11 Bar.");
        }
        } else if (sensorID == 3) {
        if (bahasa == "english") {
          lib_set_text("label", "label2_copy1", "Vacuum Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from -675 to 0 mmHg. For 6 and 11");
          lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from -750 to 0 mmHg.");
          lib_set_text("label", "label2_copy1", "Vacuum Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from -675 to 0 mmHg. For 6 and 11");
          lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from -750 to 0 mmHg.");
        } else {
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Vakum:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada -675 hingga 0 mmHg. Untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada -750 hingga 0 mmHg.");
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Vakum:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada -675 hingga 0 mmHg. Untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada -750 hingga 0 mmHg.");
        }
        } else if (sensorID == 4) {
        if (bahasa == "english") {
          lib_set_text("label", "label2_copy1", "Temperature Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 16 to 25 Â°C. For 6 and 11");
          lib_set_text("label", "label_baris4_copy1", " sample points, the data range is from 16 to 26 Â°C.");
          lib_set_text("label", "label2_copy1", "Temperature Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 16 to 25 Â°C. For 6 and 11");
          lib_set_text("label", "label_baris4_copy1", " sample points, the data range is from 16 to 26 Â°C.");
        } else {
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Suhu:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 16 hingga 25 Â°C. Untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 16 hingga 26 Â°C.");
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Suhu:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 16 hingga 25 Â°C. Untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 16 hingga 26 Â°C.");
        }
        } else if (sensorID == 5) {
        if (bahasa == "english") {
          lib_set_text("label", "label2_copy1", "Humidity Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 30 to 66 %. And for 6 and 11");
          lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from 30 to 70 %.");
          lib_set_text("label", "label2_copy1", "Humidity Sensor Calibration Instruction:");
          lib_set_text("label", "label_baris3_copy1", "2. For 4 sample points, the data range is from 30 to 66 %. And for 6 and 11");
          lib_set_text("label", "label_baris4_copy1", "sample points, the data range is from 30 to 70 %.");
        } else {
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Kelembapan:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 30 hingga 66 % . Dan untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 30 hingga 70 %.");
          lib_set_text("label", "label2_copy1", "Petunjuk Kalibrasi Sensor Kelembapan:");
          lib_set_text("label", "label_baris3_copy1", "2. Untuk 4 titik sample, range data ada pada 30 hingga 66 % . Dan untuk 6 dan 11");
          lib_set_text("label", "label_baris4_copy1", "titik sample, range data pada 30 hingga 70 %.");
        }
        }*/



      for (int i = 0; i < 11; i++) {  //reset array data sementara.
        refDataArr[i] = 0.0;
        senDataArr[i] = 0.0;
      }

      break;

    case 1:
      lib_set_enaVisi("view_k_sample", 0);
      lib_set_enaVisi("view_k_input", 1);

      isCalibrate = 1;
      alarmEnable = false;

      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 1") : lib_set_text("label", "label_referensi", "Nilai Referensi 1");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      lib_set_text("label", "label_k_satuan", labelSatuan);
      lib_set_text("label", "label_k_satuan_copy", labelSatuan);

      if (sensorID == 0 || sensorID == 1 || sensorID == 2) {
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue", "Range : 9.51 - 10.50 Bar");
        } else lib_set_text("label", "label_referensiValue", "Range : 10.51 - 11.50 Bar");
      }

      if (sensorID == 3) {  //vakum
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue", "Range : -700 mmHg s/d -650 mmHg");
        } else lib_set_text("label", "label_referensiValue", "Range : -775 mmHg s/d -725 mmHg");
      }

      if (sensorID == 4) {
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue", "Range : 24.51 - 25.50 °C");

        } else lib_set_text("label", "label_referensiValue", "Range : 25.51 - 26.50 °C");
      }

      if (sensorID == 5) {
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue", "Range : 65.01 - 67.00 %");

        } else lib_set_text("label", "label_referensiValue", "Range : 69.01 - 71.00 %");
      }

      break;

    case 2:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 2") : lib_set_text("label", "label_referensi", "Nilai Referensi 2");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");

      break;

    case 3:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 3") : lib_set_text("label", "label_referensi", "Nilai Referensi 3");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;

    case 4:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 4") : lib_set_text("label", "label_referensi", "Nilai Referensi 4");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 5:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 5") : lib_set_text("label", "label_referensi", "Nilai Referensi 5");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 6:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 6") : lib_set_text("label", "label_referensi", "Nilai Referensi 6");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 7:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 7") : lib_set_text("label", "label_referensi", "Nilai Referensi 7");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 8:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 8") : lib_set_text("label", "label_referensi", "Nilai Referensi 8");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 9:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 9") : lib_set_text("label", "label_referensi", "Nilai Referensi 9");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 10:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 10") : lib_set_text("label", "label_referensi", "Nilai Referensi 10");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 11:
      bahasa == "english" ? lib_set_text("label", "label_referensi", "Reference Value 11") : lib_set_text("label", "label_referensi", "Nilai Referensi 11");
      lib_set_value("edit", "edit_inputRef", "0.00", "%.2f");
      break;
    case 12:
      isCalibrate = 0;

      preferences.begin("control", false);
      alarmEnable = preferences.getBool("alarmEnable", false);
      preferences.end();

      Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"view_k_input\",\"enable\":false}>ET"));
      Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_k_input\",\"visible\":false}>ET"));

      if (jumlahSample == 4) {
        //print data for report view, referens and sensor
        for (int i = 0; i < jumlahSample; i++) {
          if (sensorID == 3) {
            delay(1);
            lib_set_text("label", labelReferensi4[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4[i], String((int)senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi4[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4[i], String((int)senDataArr[i]));
          } else {
            delay(1);
            lib_set_text("label", labelReferensi4[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4[i], String(senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi4[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4[i], String(senDataArr[i]));
          }
        }

        Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"view_k_report4\",\"enable\":true}>ET"));
        Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_k_report4\",\"visible\":true}>ET"));

      } else if (jumlahSample == 6) {
        //print data for report view, referens and sensor
        for (int i = 0; i < jumlahSample; i++) {
          if (sensorID == 3) {
            delay(1);
            lib_set_text("label", labelReferensi6[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6[i], String((int)senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi6[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6[i], String((int)senDataArr[i]));
          } else {
            delay(1);
            lib_set_text("label", labelReferensi6[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6[i], String(senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi6[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6[i], String(senDataArr[i]));
          }
        }

        Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"view_k_report6\",\"enable\":true}>ET"));
        Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_k_report6\",\"visible\":true}>ET"));
      } else if (jumlahSample == 11) {

        //print data for report view, referens and sensor
        for (int i = 0; i < jumlahSample; i++) {
          if (sensorID == 3) {
            delay(1);
            lib_set_text("label", labelReferensi11[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11[i], String((int)senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi11[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11[i], String((int)senDataArr[i]));
          } else {
            delay(1);
            lib_set_text("label", labelReferensi11[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11[i], String(senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi11[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11[i], String(senDataArr[i]));
          }
        }

        Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"view_k_report11\",\"enable\":true}>ET"));
        Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_k_report11\",\"visible\":true}>ET"));
      }
      break;
  }
}
void calibrationPopup_eng(void) {
  Serial.println(kalibrasiState);

  switch (kalibrasiState) {
    case 0:
      Serial.println("case 0");
      lib_set_enaVisi("view_info_1e", 1);
      delay(100);
      if (sensorID == 0 || sensorID == 1 || sensorID == 2) {
        lib_set_text("label", "label2_copy1e", "Pressure Sensor Calibration Instruction:");
        lib_set_text("label", "label_baris3_copy1e", "2. For 4 sample points, the data range is from 1 to 10 Bar. For 6 and 11");
        lib_set_text("label", "label_baris4_copy1e", "sample points, the data range is from 1 to 11 Bar.");

      } else if (sensorID == 3) {
        lib_set_text("label", "label2_copy1e", "Vacuum Sensor Calibration Instruction:");
        lib_set_text("label", "label_baris3_copy1e", "2. For 4 sample points, the data range is from -675 to 0 mmHg. For 6 and 11");
        lib_set_text("label", "label_baris4_copy1e", "sample points, the data range is from -750 to 0 mmHg.");

      } else if (sensorID == 4) {
        lib_set_text("label", "label2_copy1e", "Temperature Sensor Calibration Instruction:");
        lib_set_text("label", "label_baris3_copy1e", "2. For 4 sample points, the data range is from 16 to 25 °C. For 6 and 11");
        lib_set_text("label", "label_baris4_copy1e", " sample points, the data range is from 16 to 26 °C.");
      }

      else if (sensorID == 5) {
        lib_set_text("label", "label2_copy1e", "Humidity Sensor Calibration Instruction:");
        lib_set_text("label", "label_baris3_copy1e", "2. For 4 sample points, the data range is from 30 to 66 %. And for 6 and 11");
        lib_set_text("label", "label_baris4_copy1e", "sample points, the data range is from 30 to 70 %.");
      }

      for (int i = 0; i < 11; i++) {  //reset array data sementara.
        refDataArr[i] = 0.0;
        senDataArr[i] = 0.0;
      }

      break;

    case 1:
      lib_set_enaVisi("view_k_sample_e", 0);
      lib_set_enaVisi("view_k_input_e", 1);

      isCalibrate = 1;
      alarmEnable = false;

      lib_set_text("label", "label_referensi_e", "Reference Value 1");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      lib_set_text("label", "label_k_satuan_e", labelSatuan);
      lib_set_text("label", "label_k_satuan_copy_e", labelSatuan);

      if (sensorID == 0 || sensorID == 1 || sensorID == 2) {
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue_e", "Range : 9.51 - 10.50 Bar");
        } else lib_set_text("label", "label_referensiValue_e", "Range : 10.51 - 11.50 Bar");
      }

      if (sensorID == 3) {  //vakum
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue_e", "Range : -700 mmHg to -650 mmHg");
        } else lib_set_text("label", "label_referensiValue_e", "Range : -775 mmHg to -725 mmHg");
      }

      if (sensorID == 4) {
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue_e", "Range : 24.51 - 25.50 °C");

        } else lib_set_text("label", "label_referensiValue_e", "Range : 25.51 - 26.50 °C");
      }

      if (sensorID == 5) {
        if (jumlahSample == 4) {
          lib_set_text("label", "label_referensiValue_e", "Range : 65.01 - 67.00 %");

        } else lib_set_text("label", "label_referensiValue_e", "Range : 69.01 - 71.00 %");
      }

      break;

    case 2:
      lib_set_text("label", "label_referensi_e", "Reference Value 2");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");

      break;

    case 3:
      lib_set_text("label", "label_referensi_e", "Reference Value 3");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;

    case 4:
      lib_set_text("label", "label_referensi_e", "Reference Value 4");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 5:
      lib_set_text("label", "label_referensi_e", "Reference Value 5");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 6:
      lib_set_text("label", "label_referensi_e", "Reference Value 6");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 7:
      lib_set_text("label", "label_referensi_e", "Reference Value 7");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 8:
      lib_set_text("label", "label_referensi_e", "Reference Value 8");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 9:
      lib_set_text("label", "label_referensi_e", "Reference Value 9");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 10:
      lib_set_text("label", "label_referensi_e", "Reference Value 10");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 11:
      lib_set_text("label", "label_referensi_e", "Reference Value 11");
      lib_set_value("edit", "edit_inputRef_e", "0.00", "%.2f");
      break;
    case 12:
      isCalibrate = 0;

      preferences.begin("control", false);
      alarmEnable = preferences.getBool("alarmEnable", false);
      preferences.end();

      lib_set_enaVisi("view_k_input_e", 0);

      if (jumlahSample == 4) {
        //print data for report view, referens and sensor
        for (int i = 0; i < jumlahSample; i++) {
          if (sensorID == 3) {
            delay(1);
            lib_set_text("label", labelReferensi4e[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4e[i], String((int)senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi4e[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4e[i], String((int)senDataArr[i]));
          } else {
            delay(1);
            lib_set_text("label", labelReferensi4e[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4e[i], String(senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi4e[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor4e[i], String(senDataArr[i]));
          }
        }

        Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"view_k_report4e\",\"enable\":true}>ET"));
        Serial2.println(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"view_k_report4e\",\"visible\":true}>ET"));

      } else if (jumlahSample == 6) {
        //print data for report view, referens and sensor
        for (int i = 0; i < jumlahSample; i++) {
          if (sensorID == 3) {
            delay(1);
            lib_set_text("label", labelReferensi6e[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6e[i], String((int)senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi6e[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6e[i], String((int)senDataArr[i]));
          } else {
            delay(1);
            lib_set_text("label", labelReferensi6e[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6e[i], String(senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi6e[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor6e[i], String(senDataArr[i]));
          }
        }
        lib_set_enaVisi("view_k_report6e", 1);
      } else if (jumlahSample == 11) {

        //print data for report view, referens and sensor
        for (int i = 0; i < jumlahSample; i++) {
          if (sensorID == 3) {
            delay(1);
            lib_set_text("label", labelReferensi11e[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11e[i], String((int)senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi11e[i], String((int)refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11e[i], String((int)senDataArr[i]));
          } else {
            delay(1);
            lib_set_text("label", labelReferensi11e[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11e[i], String(senDataArr[i]));
            delay(1);
            lib_set_text("label", labelReferensi11e[i], String(refDataArr[i]));
            delay(1);
            lib_set_text("label", labelSensor11e[i], String(senDataArr[i]));
          }
        }
        lib_set_enaVisi("view_k_report11e", 1);
      }
      break;
  }
}

float calibrationStart(int sensorNumber, float inp) {
  if (inp == 0) {
    return 0;
  }

  if (sensorNumber == 0) {       //N2O
    if (inp >= senDataN2O[1]) {  //area pertama
      return (inp - senDataN2O[0]) * (refDataN2O[1] - refDataN2O[0]) / (senDataN2O[1] - senDataN2O[0]) + refDataN2O[0];
    }

    for (int i = 2; i < sampleN2O - 1; i++) {  //area kedua sampai terakhir-1
      if (inp >= senDataN2O[i] && inp < senDataN2O[i - 1]) {
        return ((inp - senDataN2O[i - 1]) * (refDataN2O[i] - refDataN2O[i - 1]) / (senDataN2O[i] - senDataN2O[i - 1])) + refDataN2O[i - 1];
      }
    }

    if (inp < senDataN2O[sampleN2O - 2]) {  //area terakhir
      return (inp - senDataN2O[sampleN2O - 2]) * (refDataN2O[sampleN2O - 1] - refDataN2O[sampleN2O - 2]) / (senDataN2O[sampleN2O - 1] - senDataN2O[sampleN2O - 2]) + refDataN2O[sampleN2O - 2];
    }

    return inp;

  }

  else if (sensorNumber == 1) {  //O2
    if (inp >= senDataO2[1]) {   //area pertama
      return (inp - senDataO2[0]) * (refDataO2[1] - refDataO2[0]) / (senDataO2[1] - senDataO2[0]) + refDataO2[0];
    }

    for (int i = 2; i < sampleO2 - 1; i++) {  //area kedua sampai terakhir-1
      if (inp >= senDataO2[i] && inp < senDataO2[i - 1]) {
        return (inp - senDataO2[i - 1]) * (refDataO2[i] - refDataO2[i - 1]) / (senDataO2[i] - senDataO2[i - 1]) + refDataO2[i - 1];
      }
    }

    if (inp < senDataO2[sampleO2 - 2]) {  //area terakhir
      return (inp - senDataO2[sampleO2 - 2]) * (refDataO2[sampleO2 - 1] - refDataO2[sampleO2 - 2]) / (senDataO2[sampleO2 - 1] - senDataO2[sampleO2 - 2]) + refDataO2[sampleO2 - 2];
    }
    return inp;
  }

  else if (sensorNumber == 2) {  //AIR
    if (inp >= senDataAIR[1]) {  //area pertama
      return (inp - senDataAIR[0]) * (refDataAIR[1] - refDataAIR[0]) / (senDataAIR[1] - senDataAIR[0]) + refDataAIR[0];
    }

    for (int i = 2; i < sampleAIR - 1; i++) {  //area kedua sampai terakhir-1
      if (inp >= senDataAIR[i] && inp < senDataAIR[i - 1]) {
        return (inp - senDataAIR[i - 1]) * (refDataAIR[i] - refDataAIR[i - 1]) / (senDataAIR[i] - senDataAIR[i - 1]) + refDataAIR[i - 1];
      }
    }

    if (inp < senDataAIR[sampleAIR - 2]) {  //area terakhir
      return (inp - senDataAIR[sampleAIR - 2]) * (refDataAIR[sampleAIR - 1] - refDataAIR[sampleAIR - 2]) / (senDataAIR[sampleAIR - 1] - senDataAIR[sampleAIR - 2]) + refDataAIR[sampleAIR - 2];
    }
    return inp;
  }

  else if (sensorNumber == 3) {    //Vakum
    if (inp <= senDataVakum[1]) {  //area pertama
      return (inp - senDataVakum[0]) * (refDataVakum[1] - refDataVakum[0]) / (senDataVakum[1] - senDataVakum[0]) + refDataVakum[0];
    }

    for (int i = 2; i < sampleVakum - 1; i++) {  //area kedua sampai terakhir-1
      if (inp <= senDataVakum[i] && inp > senDataVakum[i - 1]) {
        return (inp - senDataVakum[i - 1]) * (refDataVakum[i] - refDataVakum[i - 1]) / (senDataVakum[i] - senDataVakum[i - 1]) + refDataVakum[i - 1];
      }
    }

    if (inp > senDataVakum[sampleVakum - 2]) {  //area terakhir
      return (inp - senDataVakum[sampleVakum - 2]) * (refDataVakum[sampleVakum - 1] - refDataVakum[sampleVakum - 2]) / (senDataVakum[sampleVakum - 1] - senDataVakum[sampleVakum - 2]) + refDataVakum[sampleVakum - 2];
    }
    return inp;
  }

  else if (sensorNumber == 4) {   //suhu
    if (inp >= senDataSuhu[1]) {  //area pertama
      return (inp - senDataSuhu[0]) * (refDataSuhu[1] - refDataSuhu[0]) / (senDataSuhu[1] - senDataSuhu[0]) + refDataSuhu[0];
    }

    for (int i = 2; i < sampleSuhu - 1; i++) {  //area kedua sampai terakhir-1
      if (inp >= senDataSuhu[i] && inp < senDataSuhu[i - 1]) {
        return ((inp - senDataSuhu[i - 1]) * (refDataSuhu[i] - refDataSuhu[i - 1]) / (senDataSuhu[i] - senDataSuhu[i - 1])) + refDataSuhu[i - 1];
      }
    }

    if (inp < senDataSuhu[sampleSuhu - 2]) {  //area terakhir
      return (inp - senDataSuhu[sampleSuhu - 2]) * (refDataSuhu[sampleSuhu - 1] - refDataSuhu[sampleSuhu - 2]) / (senDataSuhu[sampleSuhu - 1] - senDataSuhu[sampleSuhu - 2]) + refDataSuhu[sampleSuhu - 2];
    }
    return inp;
  }

  else if (sensorNumber == 5) {       //Humidity
    if (inp >= senDataHumidity[1]) {  //area pertama
      return (inp - senDataHumidity[0]) * (refDataHumidity[1] - refDataHumidity[0]) / (senDataHumidity[1] - senDataHumidity[0]) + refDataHumidity[0];
    }

    for (int i = 2; i < sampleHumidity - 1; i++) {  //area kedua sampai terakhir-1
      if (inp >= senDataHumidity[i] && inp < senDataHumidity[i - 1]) {
        return ((inp - senDataHumidity[i - 1]) * (refDataHumidity[i] - refDataHumidity[i - 1]) / (senDataHumidity[i] - senDataHumidity[i - 1])) + refDataHumidity[i - 1];
      }
    }

    if (inp < senDataHumidity[sampleHumidity - 2]) { // area terakhir
      return (inp - senDataHumidity[sampleHumidity - 2]) * (refDataHumidity[sampleHumidity - 1] - refDataHumidity[sampleHumidity - 2]) / (senDataHumidity[sampleHumidity - 1] - senDataHumidity[sampleHumidity - 2]) + refDataHumidity[sampleHumidity - 2];
    }
    return inp;
  }
  return 0;
}

void calibrationInit() {
  //coba ambil data dari memori N2O
  preferences.begin("kalibrasi", false);
  sampleN2O = preferences.getInt("sampleDataN2O", 11);
  for (int i = 0; i < sampleN2O; i++) {
    String namespaceRef = "refDataN2O" + String(i);
    String namespaceSen = "senDataN2O" + String(i);
    float refn2otemp = float(preferences.getInt(namespaceRef.c_str(), i * 100)) / 100.0;
    float senn2otemp = float(preferences.getInt(namespaceSen.c_str(), i * 100)) / 100.0;
    refDataN2O[i] = refn2otemp;
    senDataN2O[i] = senn2otemp;
  }
  //preferences.end();

  //coba ambil data dari memori O2
  //preferences.begin("kalibrasi", false);
  sampleO2 = preferences.getInt("sampleDataO2", 11);
  for (int i = 0; i < sampleO2; i++) {
    String namespaceRef = "refDataO2" + String(i);
    String namespaceSen = "senDataO2" + String(i);
    float refo2temp = float(preferences.getInt(namespaceRef.c_str(), i * 100)) / 100.0;
    float seno2temp = float(preferences.getInt(namespaceSen.c_str(), i * 100)) / 100.0;
    refDataO2[i] = refo2temp;
    senDataO2[i] = seno2temp;
  }
  //preferences.end();

  //coba ambil data dari memori Air
  //preferences.begin("kalibrasi", false);
  sampleAIR = preferences.getInt("sampleDataAIR", 11);
  for (int i = 0; i < sampleAIR; i++) {
    String namespaceRef = "refDataAIR" + String(i);
    String namespaceSen = "senDataAIR" + String(i);
    float refAIRtemp = float(preferences.getInt(namespaceRef.c_str(), i * 100)) / 100.0;
    float senAIRtemp = float(preferences.getInt(namespaceSen.c_str(), i * 100)) / 100.0;
    refDataAIR[i] = refAIRtemp;
    senDataAIR[i] = senAIRtemp;
  }
  //preferences.end();

  //coba ambil data dari memori Vakum
  //preferences.begin("kalibrasi", false);
  sampleVakum = preferences.getInt("sampleDataVakum", 11);
  for (int i = 0; i < sampleVakum; i++) {
    String namespaceRef = "refDataVakum" + String(i);
    String namespaceSen = "senDataVakum" + String(i);
    float refVakumtemp = float(preferences.getInt(namespaceRef.c_str(), i)) / 1.0;
    float senVakumtemp = float(preferences.getInt(namespaceSen.c_str(), i)) / 1.0;
    refDataVakum[i] = refVakumtemp;
    senDataVakum[i] = senVakumtemp;
  }
  //preferences.end();

  //coba ambil data dari memori Suhu
  //preferences.begin("kalibrasi", false);
  sampleSuhu = preferences.getInt("sampleDataSuhu", 11);
  for (int i = 0; i < sampleSuhu; i++) {
    String namespaceRef = "refDataSuhu" + String(i);
    String namespaceSen = "senDataSuhu" + String(i);
    float refSuhutemp = float(preferences.getInt(namespaceRef.c_str(), i * 100)) / 100.0;
    float senSuhutemp = float(preferences.getInt(namespaceSen.c_str(), i * 100)) / 100.0;
    refDataSuhu[i] = refSuhutemp;
    senDataSuhu[i] = senSuhutemp;
  }
  //preferences.end();


  //ambil data dari memori Humidity
  //preferences.begin("kalibrasi", false);
  // sampleHumidity = preferences.getInt("sampleDataHumidity", 11);
  sampleHumidity = preferences.getInt("sampleDataHumi", 11);
  // Serial.println("sampleHumidity : " + String(sampleHumidity));
  for (int i = 0; i < sampleHumidity; i++) {
    String namespaceRef = "refDataHumi" + String(i);
    String namespaceSen = "senDataHumi" + String(i);
    float refHumidtemp = float(preferences.getInt(namespaceRef.c_str(), i * 100)) / 100.0;
    float senHumidtemp = float(preferences.getInt(namespaceSen.c_str(), i * 100)) / 100.0;
    refDataHumidity[i] = refHumidtemp;
    senDataHumidity[i] = senHumidtemp;
  }
  preferences.end();


  //print data
  //print N2O
  Serial.print("Data Ref N2O : ");
  for (int i = 0; i < sampleN2O; i++) {
    Serial.print(refDataN2O[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.print("Data Sen N2O : ");
  for (int i = 0; i < sampleN2O; i++) {
    Serial.print(senDataN2O[i]);
    Serial.print(" ");
  }
  Serial.println("\n");

  //printO2
  Serial.print("Data Ref O2 : ");
  for (int i = 0; i < sampleO2; i++) {
    Serial.print(refDataO2[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.print("Data Sen O2 : ");
  for (int i = 0; i < sampleO2; i++) {
    Serial.print(senDataO2[i]);
    Serial.print(" ");
  }
  Serial.println("\n");

  //print air
  Serial.print("Data Ref Air : ");
  for (int i = 0; i < sampleAIR; i++) {
    Serial.print(refDataAIR[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.print("Data Sen Air : ");
  for (int i = 0; i < sampleAIR; i++) {
    Serial.print(senDataAIR[i]);
    Serial.print(" ");
  }
  Serial.println("\n");

  // print vakum
  Serial.print("Data Ref Vakum : ");
  for (int i = 0; i < sampleVakum; i++) {
    Serial.print(refDataVakum[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.print("Data Sen Vakum : ");
  for (int i = 0; i < sampleVakum; i++) {
    Serial.print(senDataVakum[i]);
    Serial.print(" ");
  }
  Serial.println("\n");

  // print Suhu
  Serial.print("Data Ref Suhu : ");
  for (int i = 0; i < sampleSuhu; i++) {
    Serial.print(refDataSuhu[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.print("Data Sen Suhu : ");
  for (int i = 0; i < sampleSuhu; i++) {
    Serial.print(senDataSuhu[i]);
    Serial.print(" ");
  }
  Serial.println("\n");

  // print Humidity
  Serial.print("Data Ref Humidity : ");
  for (int i = 0; i < sampleHumidity; i++) {
    Serial.print(refDataHumidity[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.print("Data Sen Humidity : ");
  for (int i = 0; i < sampleHumidity; i++) {
    Serial.print(senDataHumidity[i]);
    Serial.print(" ");
  }
  Serial.println("\n");
}

void calibrationReset(int sensorNumber) {
  if (sensorNumber == 0) {  //N2O
    //simpan data ke memori
    preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataN2O", 11);
    for (int i = 0; i < 11; i++) {
      String namespaceRef = "refDataN2O" + String(i);
      String namespaceSen = "senDataN2O" + String(i);
      preferences.putInt(namespaceRef.c_str(), float(1100 - i * 100));
      preferences.putInt(namespaceSen.c_str(), float(1100 - i * 100));
    }
    preferences.end();

  } else if (sensorNumber == 1) {  //O2
    //simpan data ke memori
    preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataO2", 11);
    for (int i = 0; i < 11; i++) {
      String namespaceRef = "refDataO2" + String(i);
      String namespaceSen = "senDataO2" + String(i);
      preferences.putInt(namespaceRef.c_str(), float(1100 - i * 100));
      preferences.putInt(namespaceSen.c_str(), float(1100 - i * 100));
    }
    preferences.end();
  } else if (sensorNumber == 2) {  //Air
    //simpan data ke memori
    preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataAIR", 11);
    for (int i = 0; i < 11; i++) {
      String namespaceRef = "refDataAIR" + String(i);
      String namespaceSen = "senDataAIR" + String(i);
      preferences.putInt(namespaceRef.c_str(), float(1100 - i * 100));
      preferences.putInt(namespaceSen.c_str(), float(1100 - i * 100));
    }
    preferences.end();
  } else if (sensorNumber == 3) {  //Vakum
    //simpan data ke memori
    preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataVakum", 11);
    for (int i = 0; i < 11; i++) {
      String namespaceRef = "refDataVakum" + String(i);
      String namespaceSen = "senDataVakum" + String(i);
      preferences.putInt(namespaceRef.c_str(), int((((11 - i) * -10) + 10) * 7.501));
      preferences.putInt(namespaceSen.c_str(), int((((11 - i) * -10) + 10) * 7.501));
    }
    preferences.end();
  } else if (sensorNumber == 4) {  //Suhu
    //simpan data ke memori
    preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataSuhu", 11);
    for (int i = 0; i < 11; i++) {
      String namespaceRef = "refDataSuhu" + String(i);
      String namespaceSen = "senDataSuhu" + String(i);
      preferences.putInt(namespaceRef.c_str(), (11 - i + 15) * 100);
      preferences.putInt(namespaceSen.c_str(), (11 - i + 15) * 100);
    }
    preferences.end();
  } else if (sensorNumber == 5) {  //Kelembapan
    //simpan data ke memori
    Serial.println("reset humidity");
    preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataHumi", 11);
    for (int i = 0; i < 11; i++) {
      String namespaceRef = "refDataHumi" + String(i);
      String namespaceSen = "senDataHumi" + String(i);
      preferences.putInt(namespaceRef.c_str(), ((11 - i - 1) * 4 + 30) * 100);
      preferences.putInt(namespaceSen.c_str(), ((11 - i - 1) * 4 + 30) * 100);
    }
    preferences.end();
  }
}

int data_parse::getOpVal(void) {
  int state_of_operation = val_start_op;
  return state_of_operation;
}
int data_parse::getAnVal(void) {
  int state_of_anastetion = val_start_an;
  return state_of_anastetion;
}

int data_parse::getAnastetionTime(void) {
  int time_anastetion = an_detik;
  return time_anastetion;
}
String data_parse::getLanguage(void) {
  String _language = bahasa;
  return _language;
}

void reset_anastetion(void) {
  st_tmr_an = 0;
  val_start_an = 0;
  an_detik = 0;
  state_start_an = false;
  lib_set_value("label", "label1_jam_waktu_anestesi", "0", "%02d");
  lib_set_value("label", "label1_menit_waktu_anestesi", "0", "%02d");
  lib_set_value("label", "label1_detik_waktu_anstesi", "0", "%02d");
}

int data_parse::getTrack(void) {
  if (track < 255 && track > 0)
    return track;
  return 0;
}

int data_parse::getsTates(void) {
  return jeda;
}

bool data_parse::isPopupMusic(void) {
  return isPopup;
}

bool data_parse::isPlayMusic(void) {
  return play;
}

long int data_parse::get_mill_an(void) {
  return val_start_an;
}

long int data_parse::get_mill_op(void) {
  return val_start_op;
}

int data_parse::getState_timer(void) {
  return st_tmr;
}

int data_parse::getState_timer_an(void) {
  return st_tmr_an;
}

void setTrack(int Trek) {
  track = Trek;
}

void setPlay(bool play_, int cmd) {
  play = play_;
  if (cmd == 0) {
    track = 1;
    count_play = 0;
  } else track = cmd;
}
void set_state_anastesi(bool stan) {
  state_start_an = stan;
  val_start_an = 0;
  st_tmr_an = 0;
}
void set_mode_timer(int _mode) {
  t_mode = _mode;
}

void gas_update(float o2_g, float n2o_g, float air_g, float vacum_g) {
  bool dataUpdated = false;
  g_o2 = o2_g;
  g_n2o = n2o_g;
  g_air = air_g;
  g_vacum = vacum_g;
  if (g_o2 != g_o2_cpy) {
    lib_set_value("label", "label1_nilai_tekanan_o2", String(g_o2), "%.2f");
    delay(1);
    g_o2_cpy = g_o2;
    dataUpdated = true;
  }
  if (g_n2o != g_n2o_cpy) {
    lib_set_value("label", "label1_nilai_tekanan_n2o", String(g_n2o), "%.2f");
    delay(1);
    g_n2o_cpy = g_n2o;
    dataUpdated = true;
  }
  if (g_air != g_air_cpy) {
    lib_set_value("label", "label1_nilai_tekanan_udara", String(g_air), "%.2f");
    delay(1);
    g_air_cpy = g_air;
    dataUpdated = true;
  }
  if (g_vacum != g_vacum_cpy) {
    lib_set_value("label", "label1_nilai_tekanan_vacuum", String(g_vacum), "%.0f");
    delay(1);
    g_vacum_cpy = g_vacum;
    dataUpdated = true;
  }
  Serial.printf("min_Vacum : %d\n max_Vacum : %d\n now_vacum = %d", min_Vacum, max_Vacum, g_vacum);
  check_gas(g_o2, g_n2o, g_air, int(g_vacum), false);
  if (dataUpdated) {
    iotSendData();
  }
}

void ambient_update(float temp_a, float humid_a, float press_a, int co2_a) {
  bool dataUpdated = false;
  ambient_temp = temp_a;
  ambient_humid = humid_a;
  ambient_press = press_a;
  ambient_co2 = co2_a;
  if (abs(ambient_temp_cpy - ambient_temp) >= 0.05) {
    lib_set_value("label", "label1_nilai_suhu", String(ambient_temp), "%.2f");
    delay(1);
    check_temp(ambient_temp);
    ambient_temp_cpy = ambient_temp;
    dataUpdated = true;
  }
  if (abs(ambient_press_cpy - ambient_press) >= 0.01) {
    // set_value_int("label", "label_nilai_tekanan_ruangan", Pressure, "");
    lib_set_value("label", "label_nilai_tekanan_ruangan", String(ambient_press), "%.2f");
    delay(1);
    ambient_press_cpy = ambient_press;
    dataUpdated = true;
  }
  if (abs(ambient_humid_cpy - ambient_humid) >= 1) {
    //set_value_int("label", "label1_nilai_kelembapan", Humidity, "");
    lib_set_value("label", "label1_nilai_kelembapan", String(ambient_humid), "%.2f");
    delay(1);
    check_humid(ambient_humid);
    ambient_humid_cpy = ambient_humid;
    dataUpdated = true;
  }
  if (abs(ambient_co2_cpy - ambient_co2) >= 5) {
    lib_set_value("label", "label_nilai_co2", String(ambient_co2), "%d");
    delay(1);
    check_co2(ambient_co2);
    ambient_co2_cpy = ambient_co2;
    dataUpdated = true;
  }

  if (dataUpdated) {
    iotSendData();
  }
}

void relay_setup(void) {
  digitalWrite(lampu1, (sw1 == true) ? LOW : HIGH);
  delay(100);
  digitalWrite(lampu2, (sw2 == true) ? LOW : HIGH);
  delay(100);
  digitalWrite(lampu3, (sw3 == true) ? LOW : HIGH);
  delay(100);
  digitalWrite(lampu4, (sw4 == true) ? LOW : HIGH);
  delay(100);
  digitalWrite(lampu5, (sw5 == true) ? LOW : HIGH);
  delay(100);
  digitalWrite(fog, (sw6 == true) ? LOW : HIGH);
  delay(100);
  digitalWrite(hvac, (sw7 == true) ? LOW : HIGH);
  delay(100);
}


//for calibration
bool data_parse::isCalibrateSensor(void) {
  return isCalibrate;
}

int data_parse::getSensorNumber(void) {
  return sensorID;
}

void data_parse::saveSensorData(float data) {
  currentSensorRead = data;
  if (bahasa == "english") lib_set_value("label", "label_nilaiSensor_e", String(data), "%.2f");
  else lib_set_value("label", "label_nilaiSensor", String(data), "%.2f");
}

bool data_parse::isAlarmBip(void) {
  return isAlarm;
}

bool data_parse::isSnooze(void) {
  return snooze;
}

void data_parse::setAlarmDelayDone(int en) {
  if (en == 1) {
    alarmDelayDone = true;
    if (isAlarm == 1) {
      popupAlarm(1);
    }
  }
}

void data_parse::setBip(int duration) {
  Serial2.println(F("ST<{\"cmd_code\":\"set_buzzer\",\"type\":\"system\",\"time\":"));
  Serial2.println(duration);
  Serial2.println(F("}>ET"));
}

void data_parse::openCalibrationPage(void) {
  if (bahasa == "english") {
    lib_open_win("hal_kalibrasi_eng", 1);
  } else {
    lib_open_win("hal_kalibrasi", 1);
  }
}

void data_parse::savestlcd(bool state) {
  statelcd = state;
}

void data_parse::timeoutLoading(int progres) {
  //disable button for safety
  lib_set_enable("butt_a_str", 0);
  lib_set_enable("butt_b_rst", 0);
  lib_set_enable("butt_c_edt", 0);
  if (state_start_op == true) lib_set_enable("butt_d_stp", 0);
  else lib_set_enable("butt_d_str", 0);
  lib_set_enable("butt_e_rst", 0);
  delay(1);


  if (progres > 0) {
    lib_set_visible("loading1", 1);
  }
  if (progres > 1) {
    lib_set_visible("loading2", 1);
  }
  if (progres > 2) {
    lib_set_visible("loading3", 1);
  }
  if (progres > 3) {
    lib_set_visible("loading4", 1);
  }
  if (progres > 4) {
    lib_set_visible("loading5", 1);
  }
}

void data_parse::loadingReset(void) {
  //disable button for safety

  if (st_tmr_an == 0) lib_set_enable("butt_a_str", 1);
  else lib_set_enable("butt_a_str", 0);
  lib_set_enable("butt_b_rst", 1);

  if (state_start_op == true) lib_set_enable("butt_d_stp", 1);
  else lib_set_enable("butt_d_str", 1);

  if (st_tmr == 1) lib_set_enable("butt_e_rst", 0);
  else lib_set_enable("butt_e_rst", 1);
  delay(1);
  if (st_tmr_an == 0) {
    lib_set_enable("butt_a_str", 1);
    lib_set_enable("butt_c_edt", 1);
  } else {
    lib_set_enable("butt_a_str", 0);
    lib_set_enable("butt_c_edt", 0);
  }
  //Serial2.println(F("ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"butt_a_str\",\"enable\":true}>ET"));
  lib_set_enable("butt_b_rst", 1);

  if (state_start_op == true) lib_set_enable("butt_d_stp", 1);
  else lib_set_enable("butt_d_str", 1);

  if (st_tmr == 1) lib_set_enable("butt_e_rst", 0);
  else lib_set_enable("butt_e_rst", 1);
  delay(1);

  //close view loading
  lib_set_visible("view_timeoutWait", 0);
  lib_set_visible("loading1", 0);
  lib_set_visible("loading2", 0);
  lib_set_visible("loading3", 0);
  lib_set_visible("loading4", 0);
  lib_set_visible("loading5", 0);
}

void data_parse::set_state_counter(int counters, int val_counter) {
  preferences.begin("timer", false);
  if (counters == 0) preferences.putInt("state_op", val_counter);
  else if (counters == 1) preferences.putInt("state_an", val_counter);
  preferences.end();
}
void data_parse::set_rtc_time(int dys, int hr, int mnt, int dtk) {
  day_ = dys;
  hour_ = hr;
  minute_ = mnt;
  second_ = dtk;
}
void saveCalibration(void) {
  preferences.begin("kalibrasi", false);
  if (sensorID == 0) {  //N2O
    //simpan data ke memori
    //preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataN2O", jumlahSample);
    for (int i = 0; i < jumlahSample; i++) {
      int tempFloat = int(senDataArr[i] * 100);
      float senFloat = tempFloat / 100.0;
      senFloat = senDataArr[i];
      int tempRef = int(refDataArr[i] * 100.0);
      String namespaceRef = "refDataN2O" + String(i);
      String namespaceSen = "senDataN2O" + String(i);
      preferences.putInt(namespaceRef.c_str(), tempRef);
      preferences.putInt(namespaceSen.c_str(), tempFloat);
      //preferences.putFloat(namespaceRef.c_str(), refDataArr[i]);
      //preferences.putFloat(namespaceSen.c_str(), senFloat);
      Serial.printf("%s : %f, %s : %f\n", namespaceRef.c_str(), refDataArr[i], namespaceSen.c_str(), senFloat);
      delay(10);
    }
    //preferences.end();

  } else if (sensorID == 1) {  //O2
    //preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataO2", jumlahSample);
    for (int i = 0; i < jumlahSample; i++) {
      int tempFloat = int(senDataArr[i] * 100);
      float senFloat = tempFloat / 100.0;
      senFloat = senDataArr[i];
      int tempRef = int(refDataArr[i] * 100.0);
      String namespaceRef = "refDataO2" + String(i);
      String namespaceSen = "senDataO2" + String(i);
      preferences.putInt(namespaceRef.c_str(), tempRef);
      preferences.putInt(namespaceSen.c_str(), tempFloat);
      //preferences.putFloat(namespaceRef.c_str(), refDataArr[i]);
      //preferences.putFloat(namespaceSen.c_str(), senFloat);
      Serial.printf("%s : %f, %s : %f\n", namespaceRef.c_str(), refDataArr[i], namespaceSen.c_str(), senFloat);
      delay(10);
    }
    //preferences.end();


  } else if (sensorID == 2) {  //Air (udara)
    //preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataAIR", jumlahSample);
    for (int i = 0; i < jumlahSample; i++) {
      int tempFloat = int(senDataArr[i] * 100);
      float senFloat = tempFloat / 100.0;
      senFloat = senDataArr[i];
      int tempRef = int(refDataArr[i] * 100.0);
      String namespaceRef = "refDataAIR" + String(i);
      String namespaceSen = "senDataAIR" + String(i);
      preferences.putInt(namespaceRef.c_str(), tempRef);
      preferences.putInt(namespaceSen.c_str(), tempFloat);
      //preferences.putFloat(namespaceRef.c_str(), refDataArr[i]);
      //preferences.putFloat(namespaceSen.c_str(), senFloat);
      Serial.printf("%s : %f, %s : %f\n", namespaceRef.c_str(), refDataArr[i], namespaceSen.c_str(), senFloat);
      delay(10);
    }
    //preferences.end();


  } else if (sensorID == 3) {  //vakum

    preferences.putInt("sampleDataVakum", jumlahSample);
    for (int i = 0; i < jumlahSample; i++) {
      int tempFloat = int(senDataArr[i] * 100);
      float senFloat = tempFloat / 100.0;
      senFloat = senDataArr[i];
      int tempRef = int(refDataArr[i] * 1.0);
      String namespaceRef = "refDataVakum" + String(i);
      String namespaceSen = "senDataVakum" + String(i);
      preferences.putInt(namespaceRef.c_str(), tempRef);
      preferences.putInt(namespaceSen.c_str(), senFloat);
      //preferences.putFloat(namespaceRef.c_str(), refDataArr[i]);
      //preferences.putFloat(namespaceSen.c_str(), senFloat);
      Serial.printf("%s : %f, %s : %f\n", namespaceRef.c_str(), refDataArr[i], namespaceSen.c_str(), senFloat);
      delay(10);
    }
    //preferences.end();

  } else if (sensorID == 4) {  //Suhu
    //preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataSuhu", jumlahSample);
    for (int i = 0; i < jumlahSample; i++) {
      int tempFloat = int(senDataArr[i] * 100);
      float senFloat = tempFloat / 100.0;
      senFloat = senDataArr[i];
      int tempRef = int(refDataArr[i] * 100.0);
      String namespaceRef = "refDataSuhu" + String(i);
      String namespaceSen = "senDataSuhu" + String(i);
      preferences.putInt(namespaceRef.c_str(), tempRef);
      preferences.putInt(namespaceSen.c_str(), tempFloat);
      //preferences.putFloat(namespaceRef.c_str(), refDataArr[i]);
      //preferences.putFloat(namespaceSen.c_str(), senFloat);
      Serial.printf("%s : %f, %s : %f\n", namespaceRef.c_str(), refDataArr[i], namespaceSen.c_str(), senFloat);
      delay(10);
    }
    //preferences.end();

  } else if (sensorID == 5) {  //Humidity
    //preferences.begin("kalibrasi", false);
    preferences.putInt("sampleDataHumi", jumlahSample);
    for (int i = 0; i < jumlahSample; i++) {
      int tempFloat = int(senDataArr[i] * 100);
      float senFloat = tempFloat / 100.0;
      senFloat = senDataArr[i];
      int tempRef = int(refDataArr[i] * 100.0);
      String namespaceRef = "refDataHumi" + String(i);
      String namespaceSen = "senDataHumi" + String(i);
      preferences.putInt(namespaceRef.c_str(), tempRef);
      preferences.putInt(namespaceSen.c_str(), tempFloat);
      //preferences.putFloat(namespaceRef.c_str(), refDataArr[i]);
      //preferences.putFloat(namespaceSen.c_str(), senFloat);
      Serial.printf("%s : %f, %s : %f\n", namespaceRef.c_str(), refDataArr[i], namespaceSen.c_str(), senFloat);
      delay(10);
    }
    //preferences.end();
  }
  preferences.end();
  delay(1000);
  calibrationInit();
}
void setvolume(int _vol) {
  String labels = "label18_";
  for (int y = 1; y <= 10; y++) {
    labels = labels + String(y);
    if (y <= _vol) {
      lib_set_visible(labels, 1);
    } else {
      lib_set_visible(labels, 0);
    }
    labels = "label18_";
    delay(2);
  }
}


void setkecerahan(int _brg) {
  preferences.begin("setting", false);
  preferences.putInt("Kecerahan", _brg);
  preferences.end();
  delay(10);
  String labels_ = "label19_";
  for (int y = 1; y <= 10; y++) {
    labels_ = labels_ + String(y);
    if (y * 10 <= _brg) {
      Serial2.print(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\""));
      Serial2.print(labels_);
      Serial2.println(F("\",\"visible\":true}>ET"));
      Serial.print(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\""));
      Serial.print(labels_);
      Serial.println(F("\",\"visible\":true}>ET"));
    } else {
      Serial2.print(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\""));
      Serial2.print(labels_);
      Serial2.println(F("\",\"visible\":false}>ET"));
      Serial.print(F("ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\""));
      Serial.print(labels_);
      Serial.println(F("\",\"visible\":false}>ET"));
    }
    labels_ = "label19_";
    delay(2);
  }
  Serial2.print(F("ST<{\"cmd_code\":\"set_brightness\",\"type\":\"system\",\"brightness\":"));
  Serial2.print(_brg);
  Serial2.println(F("}>ET"));
}

void setButtonOp(void) {
  st_tmr = 1;
  val_start_op = millis();
  state_start_op = true;
}

void setButtonAn() {
  preferences.begin("timer", false);
  an_detik = preferences.getInt("anSavedTime");
  preferences.end();

  st_tmr_an = 1;
  val_start_an = millis();
  state_start_an = true;
}

void button_timer_update() {
  if (state_start_op == true) {  //timer jalan
    set_button_startstop("stop");
    lib_set_enable("butt_e_rst", 0);

  } else {  //timer mati, saved time
    int op_hour = opVarLock / 3600;
    int op_minute = (opVarLock % 3600) / 60;
    int op_second = (opVarLock % 3600) % 60;

    lib_set_value("label", "label1_jam_waktu_operasi", String(op_hour), "%02d");
    lib_set_value("label", "label1_menit_waktu_operasi", String(op_minute), "%02d");
    lib_set_value("label", "label1_detik_waktu_operasi", String(op_second), "%02d");
  }

  if (state_start_an) {  //timer jalan
    lib_set_enable("butt_a_str", 0);
    lib_set_enable("butt_c_edt", 0);
    if (statelcd == false) {  //jika run raspi print set value
      int an_hour = an_detik / 3600;
      int an_minute = (an_detik % 3600) / 60;
      int an_second = (an_detik % 3600) % 60;
      lib_set_value("label", "label1_jam_waktu_anestesi", String(an_hour), "%02d");
      lib_set_value("label", "label1_menit_waktu_anestesi", String(an_minute), "%02d");
      lib_set_value("label", "label1_detik_waktu_anstesi", String(an_second), "%02d");

      Serial1.print("AnStatus");
    }
  }
}

void savevar_lock(int varlock) {
  opVarLock = varlock;
}

void iotSendData() {
  byte dataHeader;
  Wire.beginTransmission(9);
  String dataSendi2c = "IOT" + String(g_o2) + ";" + String(g_n2o) + ";" + String(g_air) + ";" + String(g_vacum) + ";" + String(ambient_temp_cpy) + ";" + String(ambient_humid_cpy) + ";" + String(ambient_co2_cpy) + ";" + String(ambient_press_cpy);
  Wire.write(dataSendi2c.c_str());
  delay(1);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(9, 2);
  delay(1);

  if (Wire.available() >= 1) {
    if (wiredata1 == 0) {
      Wire.read();
      wiredata1++;
    } else {
      dataHeader = Wire.read();
      if (dataHeader == 'S') {
        iotStatus = Wire.read();
      } else Wire.read();
    }
  } else {
    iotStatus = 2;
    wiredata1 = 0;
  }
  iotStatusUpdate();
}

void iotReset() {
  Wire.beginTransmission(9);
  Wire.write("RESET");
  Wire.endTransmission();
}

void iotSendConfig(String ssid, String password) {
  if (ssid == NULL) ssid = "0";
  if (password == NULL) password = "0";
  String data = "SP" + ssid + ";" + password;

  Wire.beginTransmission(9);
  Wire.write(data.c_str());
  Wire.endTransmission();
}

void iotStatusUpdate(int flag) {
  Serial.print("iotStatus : ");
  Serial.println(iotStatus);

  if (millis() - iotStatusUpdate_startMillis > 10000) {
    if (iotStatusUpdate_once == 0) {
      iotStatusUpdate_once++;
      iotStatusUpdate(1);
    }

    if (iotStatus != iotStatus_cpy || flag) {
      if (iotStatus == 1) {
        lib_set_bg_image("button_m_wifi", "tombol_wifi");
        lib_set_bg_image("button_s_wifi", "tombol_wifi");
        lib_set_bg_image("button_c_wifi", "tombol_wifi");
        lib_set_text("label", "label_iotStatus", "Connected");
        lib_set_text("label", "label_iotStatus", "Connected");
        lib_set_text_color("label_iotStatus", hijau);
        // Serial2.print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\"label_iotStatus\",\"color_object\":\"text_color\",\"color\":4278227762}>ET"));  //green
        // Serial2.print(F("ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\"label_iotStatus\",\"color_object\":\"text_color\",\"color\":4278227762}>ET"));  //green
      } else if (iotStatus == 0) {
        lib_set_bg_image("button_m_wifi", "tombol_wifi_slash");
        lib_set_bg_image("button_s_wifi", "tombol_wifi_slash");
        lib_set_bg_image("button_c_wifi", "tombol_wifi_slash");
        lib_set_text("label", "label_iotStatus", "Disconnected");
        lib_set_text("label", "label_iotStatus", "Disconnected");
        lib_set_text_color("label_iotStatus", merah);
      } else {  //status 2
        lib_set_bg_image("button_m_wifi", "tombol_wifi_slash");
        lib_set_bg_image("button_s_wifi", "tombol_wifi_slash");
        lib_set_bg_image("button_c_wifi", "tombol_wifi_slash");
        lib_set_text("label", "label_iotStatus", "Connecting...");
        lib_set_text("label", "label_iotStatus", "Connecting...");
        lib_set_text_color("label_iotStatus", 4278190080);  //black
      }
      iotStatus_cpy = iotStatus;
    }
  }
}


void timerOp_forceStop(void) {
  if (state_start_op == true) {  //tombol stop
    val_start_op = 0;
    // st_tmr = 2;

    set_button_startstop("start");
    bahasa == "english" ? lib_set_text("button", "butt_d_str", "START") : lib_set_text("button", "butt_d_str", "MULAI");

    lib_set_enable("butt_e_rst", 1);

    state_start_op = false;
    Serial.println("timer op force stop");
  }

  opVarLock = 0;
  st_tmr = 0;
  val_start_op = 0;
  jam_op = 0;
  menit_op = 0;
  detik_op = 0;

  preferences.begin("timer, false");
  preferences.putInt("raspiOp", 0);
  preferences.end();

  if (statelcd == false) Serial1.print("OpReset");
  lib_set_value("label", "label1_jam_waktu_operasi", String(jam_op), "%02d");
  lib_set_value("label", "label1_menit_waktu_operasi", String(menit_op), "%02d");
  lib_set_value("label", "label1_detik_waktu_operasi", String(detik_op), "%02d");

  //close loading view
  lib_set_visible("view_timeoutWait", 0);
  lib_set_visible("loading1", 0);
  lib_set_visible("loading2", 0);
  lib_set_visible("loading3", 0);
  lib_set_visible("loading4", 0);
  lib_set_visible("loading5", 0);
}



//fungsi voip
void addressBookSort(void) {
  String nameCopy[20][2];
  String temp[2];
  int length = 20;
  bool match = 0;

  for (int i = 0; i < 20; i++) {
    nameCopy[i][0] = voip_addressBook[i][0];
    nameCopy[i][1] = voip_addressBook[i][1];
    nameCopy[i][1].toLowerCase();
  }

  for (int i = 0; i < (length - 1); i++) {
    int j_min = i;
    for (int j = i + 1; j < length; j++)
      if (nameCopy[j][1] < nameCopy[j_min][1])
        j_min = j;

    // if necessary, swap the minimum string with the string at index i
    if (j_min != i) {
      temp[0] = nameCopy[i][0];
      temp[1] = nameCopy[i][1];
      nameCopy[i][0] = nameCopy[j_min][0];
      nameCopy[i][1] = nameCopy[j_min][1];
      nameCopy[j_min][0] = temp[0];
      nameCopy[j_min][1] = temp[1];
    }
  }

  //back if uppercase
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      if (nameCopy[i][0] == voip_addressBook[j][0]) {
        nameCopy[i][1] = voip_addressBook[j][1];
        match = 1;
        break;
      }
      if (match) {
        match = 0;
        break;
      }
    }
  }

  //copy back
  Serial.println("sorted array");
  for (int i = 0; i < 20; i++) {
    voip_addressBook[i][0] = nameCopy[i][0];
    voip_addressBook[i][1] = nameCopy[i][1];
  }
}

void addressBookShow(void) {
  int liIdx = 0;
  String labelNama = "list_item";
  String temp = "";
  String space = "          ";
  bool addressBookNull = true;

  if (contactEdited) {
    addressBookLoad();
    addressBookSort();
    Serial.println("address book sorted");
    contactEdited = false;
  }

  for (int i = 0; i < 20; i++) {
    if (voip_addressBook[i][0] != "") {
      contactIdx[liIdx] = i;
      temp = labelNama + String(liIdx + 10);
      lib_set_text("label", temp.c_str(), space + voip_addressBook[i][1]);
      temp = "list_item" + String(liIdx + 10);
      lib_set_enaVisi(temp, 1);

      liIdx++;
      addressBookNull = false;
      delay(1);
    }
  }

  for (int i = liIdx; i < 20; i++) {
    //contactIdx[i] = NULL;
    contactIdx[i] = i;
    temp = "list_item" + String(i + 10);
    lib_set_enaVisi(temp, 0);
  }

  if (addressBookNull == true) {
    lib_set_visible("list_view2", 0);
    lib_set_visible("label_nocontact", 1);
  } else {
    lib_set_visible("label_nocontact", 0);
    lib_set_visible("list_view2", 1);
  }
}

String addressBookCheck(String number) {
  for (int i = 0; i < 20; i++) {
    if (voip_addressBook[i][0] == number) {
      return voip_addressBook[i][1];
    }
  }
  return "No Name";
}

void addressBookSavetoMemory(void) {
  preferences.begin("contacts", false);
  String key;
  for (int i = 0; i < 20; i++) {
    key = "cId" + String(i);
    preferences.putString(key.c_str(), voip_addressBook[i][0]);
    key = "cName" + String(i);
    preferences.putString(key.c_str(), voip_addressBook[i][1]);
  }
  preferences.end();
}

void addressBookLoad(void) {
  preferences.begin("contacts", true);
  String key;
  for (int i = 0; i < 20; i++) {
    key = "cId" + String(i);
    voip_addressBook[i][0] = preferences.getString(key.c_str(), "");
    key = "cName" + String(i);
    voip_addressBook[i][1] = preferences.getString(key.c_str(), "");
  }
  preferences.end();
}

int addressBookFullCheck(void) {
  for (int i = 0; i < 20; i++) {
    if (voip_addressBook[i][0] == "") {
      lib_set_enaVisi("label_v_contactFull", 0);
      return 0;
    }
  }
  lib_set_enaVisi("label_v_contactFull", 1);
  return 1;
}

void addressBookDelete(void) {
  for (int i = 0; i < 20; i++) {
    voip_addressBook[i][0] = "";
    voip_addressBook[i][1] = "";
  }

  contactEdited = true;
  addressBookSavetoMemory();
  addressBookShow();
}


void contactDetail(int i) {
  voip_editIdx = i;

  lib_set_enaVisi("button_dlt_all", 0);
  lib_set_enaVisi("button_v_addAddrs", 0);
  lib_set_visible("label_v_contactFull", 0);

  lib_set_enaVisi("viewListAddr", 0);
  lib_set_enaVisi("viewAddrs", 1);
  lib_set_enaVisi("view_contact_detail", 1);
  lib_set_enaVisi("view_conf_del", 0);
  lib_set_enaVisi("view_contact_edit", 0);


  lib_set_text("label", "label_nmr_s", voip_addressBook[contactIdx[i]][0]);
  lib_set_text("label", "label_n_slctd", "  " + voip_addressBook[contactIdx[i]][1]);
}

void closeContactDetail(void) {
  // lib_set_enaVisi("viewAddrs", 0);
  lib_set_enaVisi("view_contact_detail", 0);
  lib_set_enaVisi("view_conf_del", 0);
  lib_set_enaVisi("view_contact_edit", 0);

  lib_set_enaVisi("button_dlt_all", 1);
  lib_set_enaVisi("button_v_addAddrs", 1);

  lib_set_enaVisi("viewListAddr", 1);
}

void keypadPressed(int key) {
  int len = numberKey.length();

  if (key == 99) {
    numberKey.remove(len - 1);
  } else numberKey = numberKey + String(key);

  lib_set_text("label", "label_in_keypad", numberKey);
}

void addressBookPrint(void) {
  for (int i = 0; i < 20; i++) {
    Serial.printf("index ke %d : %s - %s \n", i, voip_addressBook[i][1], voip_addressBook[i][0]);
  }
}


void setVolumeVoip(int _vol) {
  String labels = "label_vol_";
  for (int y = 1; y <= 10; y++) {
    labels = labels + String(y);
    if (y <= _vol) {
      lib_set_visible(labels, 1);
    } else {
      lib_set_visible(labels, 0);
    }
    labels = "label_vol_";
    delay(2);
  }
}

