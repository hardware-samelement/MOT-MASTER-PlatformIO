#include "stone.h"

void lib_set_text(String type, String widget, String text) {
  char txtBUF[200];
  sprintf(txtBUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
          "\"" STR_SET_         //"set_
          STR_TEXT "\","        // text",
          "\"" STR_TYPE "\":"   //"type":
          "\"%s\","             //"...",
          "\"" STR_WIDGET "\":" //"widget":
          "\"%s\","             //"...",
          "\"" STR_TEXT "\":"   //"text":
          "\"%s\""              //"..."
          STR_END,
          type.c_str(), widget.c_str(), text.c_str());
  stone_print(F(txtBUF));
  stone_print(F(txtBUF));
  delay(1);
  Serial.printf("set text    \"%s\" with \"%s\"\n", widget.c_str(), text.c_str());
  stone_print(F(txtBUF));
}


void lib_set_value(String type, String widget, String _value, String format) {
  char valBUF[200];

  sprintf(valBUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
          "\"" STR_SET_         //"set_
          STR_VALUE "\","       // value",
          "\"" STR_TYPE "\":"   //"type":
          "\"%s\","             //"...",
          "\"" STR_WIDGET "\":" //"widget":
          "\"%s\","             //"...",
          "\"" STR_VALUE "\":"  //"value":
          "%s"
          ",\"" STR_FORMAT "\":\"" //"..."
          "%s\"" STR_END,
          type.c_str(), widget.c_str(), _value.c_str(), format.c_str());
  stone_print(F(valBUF));
  delay(1);
  stone_print(F(valBUF));

  Serial.printf("set value   \"%s\" with \"%s\"\n", widget.c_str(), _value.c_str());
}
/*void lib_set_color(char* type, char* widget, String color){
  char valBUF[200];
 
      sprintf(valBUF,STR_HEAD_CMD2             //"ST<{cmd_code:"
                          "\""STR_SET_                  //"set_
                              STR_COLOR"\","            //value",
                            "\""STR_TYPE"\":"           //"type":
                            "\"%s\","                   //"...",
                            "\""STR_WIDGET"\":"         //"widget":
                            "\"%s\","                   //"...",
                            "color_object\":\"bg_color\",\"color\":"
                            "%s"
                            STR_END
                            , type, widget, color); 
      stone_print(F(valBUF));
      //Serial.print(F(valBUF));
}
void lib_set_visible(char* type, char* widget, String en){
  char valBUF[200];
      sprintf(valBUF,STR_HEAD_CMD2             //"ST<{cmd_code:"
                          "\""STR_SET_                  //"set_
                              STR_VISIBLE"\","            //value",
                            "\""STR_TYPE"\":"           //"type":
                            "\"%s\","                   //"...",
                            "\""STR_WIDGET"\":"         //"widget":
                            "\"%s\","                   //"...",
                            "visible\":"            //"value":
                            "%s\"" 
                            STR_END
                            , type, widget, _value,format); 
      stone_print(F(valBUF));
      //Serial.print(F(valBUF));
}

void set_enable_(String type, String widget, String en){
  String dataEnable = "ST<{\"cmd_code\":\"set_enable\",\"type\":\"" + type + "\",\"widget:\"\"" + widget + "\",\"enable\":" + en + "}>ET";
  Serial2.println(dataEnable);
}*/
/*
void set_date_time(int years, int months, int date, int hours, int minutes){
  
  Serial2.print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock2\",\"date\":\""));
  Serial2.print(years); Serial2.print(F("-")); Serial2.print(months); Serial2.print(F("-")); Serial2.print(date); Serial2.print(F(" ")); Serial2.print(hours); Serial2.print(F(":")); Serial2.print(atur_menit); Serial2.println(F("\"}>ET"));
    
  Serial2.print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock4\",\"date\":\""));
  Serial2.print(years); Serial2.print(F("-")); Serial2.print(months); Serial2.print(F("-")); Serial2.print(date); Serial2.print(F(" ")); Serial2.print(hours); Serial2.print(F(":")); Serial2.print(atur_menit); Serial2.println(F("\"}>ET"));
    
  Serial2.print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock6\",\"date\":\""));
  Serial2.print(years); Serial2.print(F("-")); Serial2.print(months); Serial2.print(F("-")); Serial2.print(date); Serial2.print(F(" ")); Serial2.print(hours); Serial2.print(F(":")); Serial2.print(atur_menit); Serial2.println(F("\"}>ET"));
    
  Serial2.print(F("ST<{\"cmd_code\":\"set_date\",\"type\":\"digit_clock\",\"widget\":\"digit_clock7\",\"date\":\""));
  Serial2.print(years); Serial2.print(F("-")); Serial2.print(months); Serial2.print(F("-")); Serial2.print(date); Serial2.print(F(" ")); Serial2.print(hours); Serial2.print(F(":")); Serial2.print(atur_menit); Serial2.println(F("\"}>ET"));
}
*/


/*
void set_visible_(String type, String widget, String vis){
  String dataVisible = "ST<{\"cmd_code\":\"set_visible\",\"type\":\"" + type + "\",\"widget:\"\"" + widget + "\",\"visible\":" + vis + "}>ET";
  Serial2.println(dataVisible);
}*/

void lib_set_enable(String widget, bool _bool) {
  char buff[300];
  String _val = "";
  _val = _bool ? "true" : "false";
  sprintf(buff, "ST<{\"cmd_code\":\"set_enable\",\"type\":\"widget\",\"widget\":\"%s\",\"enable\":%s}>ET\n", widget.c_str(), _val);
  stone_print(F(buff));
  stone_print(F(buff));
  // delay(1);
  Serial.printf("set enable  \"%s\" to \"%s\"\n", widget.c_str(), _val);
  stone_print(F(buff));
}

void lib_set_visible(String widget, bool _bool) {
  char buff[300];
  String _val = "";
  _val = _bool ? "true" : "false";
  sprintf(buff, "ST<{\"cmd_code\":\"set_visible\",\"type\":\"widget\",\"widget\":\"%s\",\"visible\":%s}>ET\n", widget.c_str(), _val);
  stone_print(F(buff));
  stone_print(F(buff));
  // delay(1);
  Serial.printf("set visible \"%s\" to \"%s\"\n", widget.c_str(), _val);
  stone_print(F(buff));
}

void lib_set_enaVisi(String widget, bool _bool){
  lib_set_enable(widget, _bool);
  lib_set_visible(widget, _bool);
}

void lib_open_win(String widget, bool _bool) {
  char buff[300];
  if (_bool) {
    sprintf(buff, "ST<{\"cmd_code\":\"open_win\",\"type\":\"window\",\"widget\":\"%s\"}>ET\n", widget);
    Serial.printf("open win \"%s\"\n", widget);

  } else {
    sprintf(buff, "ST<{\"cmd_code\":\"close_win\",\"type\":\"window\",\"widget\":\"%s\"}>ET\n", widget);
    Serial.printf("close win \"%s\"\n", widget);
  }
  stone_print(F(buff));
  stone_print(F(buff));
  delay(1);
  stone_print(F(buff));
}

void lib_set_bg_image(String widget, String image){
  char buff[300];
  sprintf(buff, "ST<{\"cmd_code\":\"set_bg_image\",\"type\":\"widget\",\"widget\":\"%s\",\"bg_image\":\"%s\"}>ET", widget.c_str(), image.c_str());
  stone_print(F(buff));
  stone_print(F(buff));
  delay(1);
  stone_print(F(buff));
  Serial.printf("set bg image \"%s\" with \"%s\"\n", widget.c_str(), image.c_str());
}

void lib_set_bg_color(String widget, uint32_t color){
  char buff[300];
  sprintf(buff, "ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\"%s\",\"color_object\":\"bg_color\",\"color\":%s}>ET", widget.c_str(), String(color).c_str());
  stone_print(F(buff));
  stone_print(F(buff));
  delay(1);
  stone_print(F(buff));
  Serial.printf("set bg color \"%s\" to \"%s\"\n", widget.c_str(), String(color).c_str());
}

void lib_set_text_color(String widget, uint32_t color){
  char buff[300];
  sprintf(buff, "ST<{\"cmd_code\":\"set_color\",\"type\":\"widget\",\"widget\":\"%s\",\"color_object\":\"text_color\",\"color\":%s}>ET", widget.c_str(), String(color).c_str());
  stone_print(F(buff));
  stone_print(F(buff));
  delay(1);
  stone_print(F(buff));
  Serial.printf("set text color \"%s\" to \"%s\"\n", widget.c_str(), String(color).c_str());
}
