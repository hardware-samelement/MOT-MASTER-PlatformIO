#include "stone.h"
#include "data_parse.h"

unsigned char STONE_RX_BUF[RX_LEN];
unsigned short STONE_RX_CNT = 0;
const unsigned char frame_head[3] = { 'S', 'T', '<' };  //Frame header flag data
const unsigned char frame_end[3] = { '>', 'E', 'T' };   //End of frame flag data
unsigned char receive_over_flage = 0;
String _atur_kode;
String _room = "";
String _pass = "";
String _ssid = "";
String _pas2 = ";";
String _editTextData = "";
String voip_id = "";
String voip_pass = "";
String voip_server = "";
String contact_id = "";
String contact_name = "";
bool val1 = false;
bool val2 = false;
bool val3 = false;
bool ck1 = false;
int stat_crc = false;
bool slid_fix = false;
int volume_track;

void serial_receive() {

  if (stone_uart_get_flag(USER_UART))  //Check whether the serial port reads data
  {
#if MCU_ARDUINO || MCU_ESP || MCU_Raspberry_Pi
    stone_uart_read(USER_UART);                    //Read a byte and store it in the STONE_RX_BUF buffer
    stone_print(STONE_RX_BUF[STONE_RX_CNT], HEX);  //Print a byte of data in hexadecimal format
    stone_print(" ");                              //Print a space for easy viewing
    //sdebug_print(STONE_RX_BUF[STONE_RX_CNT],HEX);   //Print a byte of data in hexadecimal format
    //sdebug_print(" ");
    if (STONE_RX_BUF[STONE_RX_CNT] == 69) val1 = true;
    if (val1 == true && STONE_RX_BUF[STONE_RX_CNT] == 84) val2 = true;
    else val1 = false;
    if (val2 == true && STONE_RX_BUF[STONE_RX_CNT] == 62) val3 = true;
    else {
      val1 = false;
      val2 = false;
    }
#endif
    STONE_RX_CNT++;
    //Serial.print(STONE_RX_BUF[]);
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    STONE_Delay(1);  //Maximum timeout for serial reading the data is 1ms
    if (stone_uart_get_flag(USER_UART)) return;
  }
#endif
  if (STONE_RX_CNT == 1 && STONE_RX_BUF[STONE_RX_CNT - 1] != 'S') {
    illegal_date();
    ck1 = false;
  }  //Make a judgment when there is only 1 data in the buffer
  else if (STONE_RX_CNT == 2 && STONE_RX_BUF[STONE_RX_CNT - 2] != 'S' && STONE_RX_BUF[STONE_RX_CNT - 1] != 'T') {
    illegal_date();
    ck1 = false;
  }  //Make a judgment when there are only 2 data in the buffer
  else if (STONE_RX_CNT == 3 && memcmp(STONE_RX_BUF, frame_head, 3) != 0) {
    illegal_date();
    ck1 = false;
  }                                                                                                                                     //Make a judgment when there are only 3 data in the buffer
  else if (STONE_RX_CNT > 11 && memcmp(STONE_RX_BUF + STONE_RX_CNT - 5, frame_end, 3) == 0 && do_crc(STONE_RX_BUF, STONE_RX_CNT) == 0)  //STONE_RX_CNT>13 The legal instruction length is at least 14, and the last two expressions verify the end of the frame and CRC checksum
  {
    ck1 = true;
#if MCU_ARDUINO
    if (STONE_RX_BUF[4] == 0x70) {
      _editTextData = "";
      char edit_text_data[50] = "";
      char _test[200] = "";
      int indeks = 0;
      int dataStart;

      for (int i = 15; i < 50; i++) {
        if (STONE_RX_BUF[i] == 0x3A) {
          dataStart = i + 1;
          break;
        }
      }

      for (int i = dataStart; i < 50; i++) {
        if (STONE_RX_BUF[i] == 62) {
          indeks = i;
          i = 50; /*illegal_date ();*/
        }
      }
      int k = 0;
      for (int j = dataStart; j < indeks; j++) {
        edit_text_data[k] = STONE_RX_BUF[j];
        k++;
      }
      _editTextData = String(edit_text_data);



      if (STONE_RX_BUF[13] == 118) {    //edit_v
        if (STONE_RX_BUF[15] == 105) {  //edit_v_id
          voip_id = _editTextData;
        } else if (STONE_RX_BUF[15] == 112) {  // edit_v_pass
          voip_pass = _editTextData;
        } else if (STONE_RX_BUF[15] == 115) {  // edit_v_serverIp
          voip_server = _editTextData;
        }
        // else if (STONE_RX_BUF[15] == 'a' && STONE_RX_BUF[18] == 'I') {  // edit_v_addId
        //   contact_id = _editTextData;
        // } else if (STONE_RX_BUF[15] == 'a' && STONE_RX_BUF[18] == 'N') {  // edit_v_addName
        //   contact_name = _editTextData;
        // }
      }

      if (STONE_RX_BUF[13] == 'I' && STONE_RX_BUF[14] == 'D') {  // edit_v_addId
        contact_id = _editTextData;
      }
      if (STONE_RX_BUF[13] == 'N' && STONE_RX_BUF[14] == 'a' && STONE_RX_BUF[15] == 'm') {  // edit_v_addId
        contact_name = _editTextData;
      }
    }

    if (STONE_RX_BUF[4] == 0x70 && STONE_RX_BUF[13] == 115) {  //s 112p
      _ssid = "";
      char ssid[50] = "";
      int indeks = 0;
      for (int i = 19; i < 50; i++) {
        if (STONE_RX_BUF[i] == 62) {
          indeks = i;
          i = 50; /*illegal_date ();*/
        }
      }
      int k = 0;
      for (int j = 19; j < indeks; j++) {
        ssid[k] = STONE_RX_BUF[j];
        k++;
      }
      _ssid = String(ssid);
      Serial.println(_ssid);
    }

    if (STONE_RX_BUF[4] == 0x70 && STONE_RX_BUF[13] == 112 && STONE_RX_BUF[16] == 115) {  //s 112p
      _pass = "";
      char pass[50] = "";
      int indeks = 0;
      for (int i = 19; i < 50; i++) {
        if (STONE_RX_BUF[i] == 62) {
          indeks = i;
          i = 50; /*illegal_date ();*/
        }
      }
      int k = 0;
      for (int j = 19; j < indeks; j++) {
        pass[k] = STONE_RX_BUF[j];
        k++;
      }
      _pass = String(pass);
      Serial.println(_pass);
    }

    if (STONE_RX_BUF[4] == 0x70 && STONE_RX_BUF[13] == 112 && STONE_RX_BUF[16] == 50) {
      _pas2 = "";
      char pas2[50] = "";
      int indeks = 0;
      for (int i = 19; i < 50; i++) {
        if (STONE_RX_BUF[i] == 62) {
          indeks = i;
          i = 50; /*illegal_date ();*/
        }
      }
      int k = 0;
      for (int j = 19; j < indeks; j++) {
        pas2[k] = STONE_RX_BUF[j];
        k++;
      }
      _pas2 = String(pas2);
      Serial.println(_pas2);
    }

    if (STONE_RX_BUF[4] == 113 && STONE_RX_BUF[12] == 107) {
      _atur_kode = String(STONE_RX_BUF[17], HEX) + String(STONE_RX_BUF[18], HEX) + String(STONE_RX_BUF[19], HEX);
      _atur_kode = strtoul(_atur_kode.c_str(), NULL, 16);
    } else if (STONE_RX_BUF[4] == 112 && STONE_RX_BUF[12] == 114) {
      _room = "";
      char rooms[50] = "";
      int indeks = 0;
      for (int i = 18; i < 50; i++) {
        if (STONE_RX_BUF[i] == 62) {
          indeks = i;
          i = 50; /*illegal_date ();*/
        }
      }
      int k = 0;
      for (int j = 18; j < indeks; j++) {
        rooms[k] = STONE_RX_BUF[j];
        k++;
      }
      _room = String(rooms);
      Serial.println(_room);
    }
    //else if(STONE_RX_BUF[4]== 1 && STONE_RX_BUF[12] == 50){
    //  lib_set_value("slider", "slider4", String(volume_track), "%d");
    // }
    if (STONE_RX_BUF[4] == 65) slid_fix = true;
    sdebug_println("legitimate");
#endif
    receive_over_flage = 1;
#if MCU_ARDUINO && Instruction_parsing
    receive_parse();
    do_parse();
#endif
    STONE_RX_CNT = 0;  //Data legal counter is cleared
  }
  if (ck1 == true && val3 == true) {
    val3 = false;
    ck1 = false;
    illegal_date();
  }
}

unsigned short illegal_date() {

#if MCU_ARDUINO
  sdebug_println("illegal");
#endif
  receive_over_flage = 0;
  STONE_RX_CNT = 0;
  STONE_RX_BUF[0] = '\0';
  return 0;
}

unsigned short do_crc(unsigned char *ptr, int len)  //CRC16_MODBUS calculation
{
  stat_crc = true;
  unsigned int i;
  unsigned short crc = 0xFFFF;
  unsigned char *crc_idx = ptr + len - 2;
  unsigned char CRC_BUF[2];
  len = len - 2;

  while (len--) {
    crc ^= *ptr++;
    for (i = 0; i < 8; ++i) {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xA001;
      else
        crc = (crc >> 1);
    }
  }
  CRC_BUF[0] = crc >> 8;
  CRC_BUF[1] = crc & 0xFF;
  return memcmp(crc_idx, CRC_BUF, 2);
  stat_crc = false;
}

void setSlid(bool slide) {
  slid_fix = slide;
}

String edit_data::getEditTextData(void) {
  String data = _editTextData;
  return data;
}

String edit_data::getPass(void) {
  String data_pass = _atur_kode;
  return data_pass;
}

String edit_data::getWifiPass(void) {
  String data_wifiPass = _pass;
  return data_wifiPass;
}

String edit_data::getWifiPas2(void) {
  String data_wifiPass = _pas2;
  return data_wifiPass;
}

String edit_data::getWifiSsid(void) {
  String data_ssid = _ssid;
  return data_ssid;
}

String edit_data::getRoom(void) {
  String data_room = _room;
  return data_room;
}

String edit_data::getVoipId(void) {
  String ret = voip_id;
  return ret;
}

String edit_data::getVoipPass(void) {
  String ret = voip_pass;
  return ret;
}

String edit_data::getVoipServer(void) {
  String ret = voip_server;
  return ret;
}

String edit_data::getContactId(void) {
  String ret = contact_id;
  return ret;
}
String edit_data::getContactName(void) {
  String ret = contact_name;
  return ret;
}

bool edit_data::getCRCstat(void) {
  return stat_crc;
}
bool edit_data::getslidFix(void) {
  return slid_fix;
}
void setVolM(int vols) {
  volume_track = vols;
}
