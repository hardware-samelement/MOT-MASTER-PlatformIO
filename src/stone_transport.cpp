#include "stone.h"

char STONE_TX_BUF[TX_LEN];
int TX_CNT, TX1_CNT, TX2_CNT, TX3_CNT, TX4_CNT;
char transport_over_flage = 1;

/* 													Packet functions for the version that sends the command 											*/
/*	Packets are grouped once for each call and stored in the send buffer after the packet is completed,
 *	The first parameter is the name in JSON format, and the format is a character pointer
 * The second parameter is the value of the JSON format, and the second parameter should be noted that the type is also a character pointer
 * the third parameter is a variable parameter, if the current call is the last set of JSON format you need to add the macro definition parameter JSON_END at the end
 *
 *  For example, to send a command ST<{"cmd_code":"sys_reboot","type":"system"}>ET
 *	The using method is :
 *   STONE_JSON ("cmd_code", "sys_reboot");
 *   STONE_JSON ("type", 		 "system", 		JSON_END);
 *
 *	For example, to send a command ST<{"cmd_code":"set_value","type":"label","widget":"label2","value":1.23,"format":"%.2f"}>ET
 *	The using method is :
 *   STONE_JSON ("cmd_code", "set_value");
 *   STONE_JSON ("type", 		 "label");
 *   STONE_JSON ("widget", 	 "label2");
 *	 STONE_JSON ("value", 	 "1.23");
 *   STONE_JSON ("format", 	 "%.2f",			JSON_END);
 */
void STONE_JSON(char *name, char *value, ...) {

  va_list p_end;
  va_start(p_end, value);
  int end;
  end = va_arg(p_end, int);

  static char json_create;

  if (json_create == 0)
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD); // ST<{

  if (TX_CNT >= TX_LEN) {
    TX_CNT = json_create = 0;
    memset(STONE_TX_BUF, 0, 200);
    sprintf(STONE_TX_BUF, "Input out of range!"); // To prevent overflow
    tx_create();
    memset(STONE_TX_BUF, 0, 200);
  }

  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\"%s\"", name); //"..."

  STONE_TX_BUF[TX_CNT++] = ':';

  if (STR_TYPE_NUM)
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "%s", value); //...
  else
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\"%s\"", value); //...

  if (end == 1) {
    json_create = 0;
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_END); //}>ET
    tx_create();
  } else
    STONE_TX_BUF[TX_CNT++] = ',';

  json_create++;
  va_end(p_end);
}

/* Implementation functions for serial port sending */
void tx_create(void) {

  // stone_Transmit(STONE_TX_BUF, TX_CNT);
  Serial.println(STONE_TX_BUF);
  /*  #if MCU_ARDUINO || MCU_ESP || MCU_STM32
    uint8_t timeout;
    transport_over_flage = 0;
    while(transport_unfinished)
    {
      STONE_Delay(1);
      timeout++;
      if(timeout==10)transport_over_flage = 1;
    }
   #endif*/
}

/* command interface for setting the system-related commands */
// Call the example: set_sys("sys_reboot");
void set_sys(const char *_cmd) {
  if (strcmp(_cmd, STR_SYS_REBOOT) == 0 ||
      strcmp(_cmd, STR_SYS_HELLO) == 0 ||
      strcmp(_cmd, STR_SYS_VERSION) == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                     "\"%s\","                   //"...",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"" STR_SYSTEM "\""        //"system"
                     STR_END,
                     _cmd); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP // Can be used to see if the send format is correct when using the Arduino compiler
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for the command to set the screen backlight */
// Call the example: set_sleep("true");
void set_sleep(const char *_tf) {
  if (strcmp(_tf, "true") == 0 ||
      strcmp(_tf, "false") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                     "\"" STR_SET_               //"set_
                     STR_SLEEP "\","             // sleep",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"" STR_SYSTEM "\","       //"system",
                     "\"" STR_SLEEP "\":"        //"sleep":
                     "%s"                        //...
                     STR_END,
                     _tf); //}>ET

    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for setting the buzzer time,In milliseconds */
// Call the example: set_buzzer("100");
void set_buzzer(const char *_time) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                   "\"" STR_SET_               //"set_
                   STR_BUZZER "\","            // buzzer",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_SYSTEM "\","       //"system",
                   "\"" STR_TIME "\":"         //"time":
                   "%s"                        //...
                   STR_END,
                   _time); //}>ET

  tx_create();
}

// #define set_brightness(_value) set_buzzer(_value)
/* Command interface for setting backlight brightness, The value ranges from 0 to 100*/
// Call the example: set_brightness("100");
void set_brightness(const char *_value) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                   "\"" STR_SET_               //"set_
                   STR_BRIGHTNESS "\","        // brightness",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_SYSTEM "\","       //"system",
                   "\"" STR_BRIGHTNESS "\":"   //"brightness":
                   "%s"                        //...
                   STR_END,
                   _value); //}>ET

  tx_create();
}

/* Command interface for setting Touch screen calibration (for resistive screens) */
// Call the example: set_touch_cal();
void set_touch_cal(void) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                   "\"" STR_SET_               //"set_
                   STR_TOUCH_CAL "\","         // touch_cal",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_SYSTEM "\""        //"system"
                   STR_END);                   //}>ET

  tx_create();
}

/* Command interface for remove Touch screen calibration (for resistive screens) */
// Call the example: clear_touch_cal();
void clear_touch_cal(void) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                   "\"" STR_CLEAR_             //"clear_
                   STR_TOUCH_CAL "\","         // touch_cal",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_SYSTEM "\""        //"system"
                   STR_END);                   //}>ET

  tx_create();
}

/* Command interface for Touch screen test */
// Call the example: set_touch_test();
void set_touch_test(void) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                   "\"" STR_SET_               //"set_
                   STR_TOUCH_CAL "\","         // touch_cal",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_SYSTEM "\""        //"system"
                   STR_END);                   //}>ET

  tx_create();
}

/* Command interface for the command to set the enable state of the widget */
// Call the example: set_enable("switch1", "false");
void set_enable(const char *_name, const char *_tf, ...) {
  va_list p_end;
  va_start(p_end, _tf);
  int end;
  end = va_arg(p_end, int);
  if (strcmp(_tf, "true") == 0 || strcmp(_tf, "false") == 0) {

    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2);
    STONE_TX_BUF[TX_CNT++] = '"';
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_SET_);
    if (end == 1)
      TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_VISIBLE);
    else
      TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_ENABLE);
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\",\"");
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_TYPE);
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\":\"");
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_SYSTEM);
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\",\"");
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_SLEEP);
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\":");
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "%s", _tf);
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_END);

    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
  va_end(p_end);
}

/* Command interface for the command to set the visible state of the widget */
// Call the example: set_visible("switch1", "false");
#define set_visible(m_name, m_tf) set_enable(m_name, m_tf, 1)

/* Command interface for the command to set the coordinate position of the widget */
// Call the example: set_coordinate("switch1", "100", "200");
void set_coordinate(const char *_name, const char *_x, const char *_y) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{\"cmd_code\":"
                   "\"" STR_SET_               //"set_
                   STR_XY "\","                // xy",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_WIDGET "\","       //"widget",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\","                   //"...",
                   "\"x\":"                    //"x":
                   "%s,"                       //...,
                   "\"y\":"                    //"y":
                   "%s"                        //...
                   STR_END,
                   _name, _x, _y); //}>ET

  tx_create();
}

/* Command interface for the command Control state */
// Call the example: set_state("button1", "pressed");
void set_state(const char *_name, const char *_state) {

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 // ST<{"cmd_code":
                   "\"" STR_SET_               //"set_
                   STR_STATE "\","             // state",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_WIDGET "\","       //"widget",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\","                   //"...",
                   "\"" STR_STATE "\":"        //"state":
                   "\"%s\""                    //"..."
                   STR_END,
                   _name, _state); //}>ET

  tx_create();
}

/* Command interface for the Set the background image */
// Call the example: set_bg_image("button1", "guage_bg");
// void set_bg_image(char *_name, char *_image) {

//   int num = 0;
//   char *str = STR_HEAD_CMD2 // ST<{"cmd_code":
//       "\"" STR_SET_         //"set_
//       "bg_" STR_IMAGE "\"," // bg_image",
//       "\"" STR_TYPE "\":"   //"type":
//       "\"" STR_WIDGET "\"," //"widget",
//       "\"" STR_WIDGET "\":";
			
//   strcpy(STONE_TX_BUF, str);
//   while (*str++)
//     num++;
//   STONE_TX_BUF[num++] = '"';
//   str = _name;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;
//   str = "\",bg_" STR_IMAGE "\":\"";
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;
//   str = _image;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;
//   str = "\"" STR_END;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;
//   TX_CNT = num;
//   tx_create();
// }

/* Command interface for the Set the background color */
// Call the example: set_color("button1", "bg_color", "guage_bg");
// void set_color(char *_name, char *_object, char *_color) {

//   int num = 0;
//   char *str = STR_HEAD_CMD2 // ST<{"cmd_code":
//       "\"" STR_SET_         //"set_
//       STR_COLOR "\","       // color",
//       "\"" STR_TYPE "\":"   //"type":
//       "\"" STR_WIDGET "\"," //"widget",
//       "\"" STR_WIDGET "\":";
//   strcpy(STONE_TX_BUF, str);
//   while (*str++)
//     num++;
//   STONE_TX_BUF[num++] = '"';

//   str = _name;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;

//   str = "\",\"" STR_COLOR "_object\":\"";
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;

//   str = _object;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;

//   str = "\",\"" STR_COLOR "\":";
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;

//   str = _color;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;

//   str = STR_END;
//   strcpy(STONE_TX_BUF + num, str);
//   while (*str++)
//     num++;
//   TX_CNT = num;
//   tx_create();
// }

/* Command interface for the command to open a window */
// Call the example: open_win("window2");
void open_win(const char *_name, ...) {
  va_list p_end;
  va_start(p_end, _name);
  int end;
  end = va_arg(p_end, int);
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2);
  STONE_TX_BUF[TX_CNT++] = '"';
  if (end == 1)
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_CLOSE_WIN);
  else if (end == 2)
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_BACK_WIN_TO);
  else
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_OPEN_WIN);
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\",\"");
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_TYPE);
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\":\"");
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_WINDOW);
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\",\"");
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_WIDGET);
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "\":\"");
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "%s\"", _name);
  TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_END);

  tx_create();
  va_end(p_end);
}

/* Command interface for the command to close the window */
// Call the example: close_win("window1");
#define close_win(m_name) open_win(m_name, 1)

/* Command interface to return to the previous level of window */
// Call the example: back_win();
void back_win() {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_BACK_WIN "\","     //"back_win",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_WINDOW "\""        //"window"
                   STR_END);                   //}>ET
  tx_create();
}

/* Return to the command interface of the specified window */
// Call the example: back_win_to("window1");
#define back_win_to(m_name) open_win(m_name, 2)

/* Command interface for returning the main window command */
// Call the example: back_home();
void back_home() {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_BACK_HOME "\","    //"back_home",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_WINDOW "\""        //"window"
                   STR_END);                   //}>ET
  tx_create();
}

/* command interface for Setting the text commands */
// Call the example: set_text("label", "label5", "hello stone");
void set_text(const char *_type, const char *_name, const char *_text) {
  if (strcmp(_type, "label") == 0 || strcmp(_type, "edit") == 0 || strcmp(_type, "text_selector") == 0) {

    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_TEXT "\","              // text",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_TEXT "\":"         //"text":
                     "\"%s\""                    //"..."
                     STR_END,
                     _type, _name, _text); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}
/* CMD judgment function */
int set_get_value_type(const char *m_type) {
  if (strcmp(m_type, "label") == 0 ||
      strcmp(m_type, "edit") == 0 ||
      strcmp(m_type, "progress_bar") == 0 ||
      strcmp(m_type, "slider") == 0 ||
      strcmp(m_type, "image_value") == 0 ||
      strcmp(m_type, "text_selector") == 0 ||
      strcmp(m_type, "switch") == 0 ||
      strcmp(m_type, "check_button") == 0 ||
      strcmp(m_type, "radio_button") == 0) {
    return 1;
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
  return 0;
}

/* Command interface for the set value command */
// Call the example: set_value("slider", "slider2", "66");
//     ??2 set_value("label", "label5", "66.6", "%.2f");
void set_value(const char *_type, const char *_name, const char *_value, ...) {

  va_list p_format;
  char *_format;
  va_start(p_format, _value);

  if (set_get_value_type(_type)) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_VALUE "\","             // value",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_VALUE "\":"        //"value":
                     "%s"                        //"..."
                     ,
                     _type, _name, _value);
    _format = va_arg(p_format, char *);
    if (_format[0] == '%') {
      TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, ",\"" STR_FORMAT "\":\"");
      TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, "%s\"", _format);
    }
    TX_CNT += sprintf(STONE_TX_BUF + TX_CNT, STR_END);
    tx_create();
  }
  va_end(p_format);
}

/* Command interface for getting text commands */
// Call the example: get_text("edit", "edit1");
void get_text(const char *_type, const char *_name) {
  if (strcmp(_type, "label") == 0 || strcmp(_type, "edit") == 0 || strcmp(_type, "text_selector") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_GET_               //"get_
                     STR_TEXT "\","              // text",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\""                    //"..."
                     STR_END,
                     _type, _name); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for the Get Value command */
// Call the example: get_value("edit", "edit2");
void get_value(const char *_type, const char *_name) {
  if (set_get_value_type(_type)) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_GET_               //"get_
                     STR_VALUE "\","             // value",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\""                    //"..."
                     STR_END,
                     _type, _name); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for the set maximum command */
// Call the example: set_max("slider", "slider2", "500");
void set_max(const char *_type, const char *_name, const char *value) {
  if (strcmp(_type, "progress_bar") == 0 || strcmp(_type, "slider") == 0 || strcmp(_type, "image_value") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_MAX "\","               // max",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_MAX "\","          //"max":
                     "%s"                        //...
                     STR_END,
                     _type, _name, value); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for displaying text commands */
// Call the example: show_text("progress_bar1", "true");
void show_text(const char *_name, const char *_tf) {
  if (strcmp(_tf, "true") == 0 || strcmp(_tf, "false") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_SHOW_TEXT "\","         // show_text",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"" STR_PORGRESS_BAR "\"," //"progress_bar",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_SHOW_TEXT "\":"    //"show_text":
                     "%s"                        //...
                     STR_END,
                     _name, _tf); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for the Get Progress Bar Percentage command */
// Call the example: get_percent("progress_bar1");
void get_percent(const char *_name) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_GET_               //"get_
                   STR_PERCNET "\","           // percnet",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_PORGRESS_BAR "\"," //"progress_bar",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\""                    //"..."
                   STR_END,
                   _name); //}>ET
  tx_create();
}

/* Command interface for the set minimum command */
// Call the example: set_min("slider", "slider2", "1");
void set_min(const char *_type, const char *_name, const char *value) {
  if (strcmp(_type, "slider") == 0 || strcmp(_type, "image_value") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_MIN "\","               // min",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_MAX "\":"          //"max":
                     "%s"                        //...
                     STR_END,
                     _type, _name, value); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for setting slider step value command */
// Call the example: set_step("slider1", "1");
void set_step(const char *_name, const char *value) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_SET_               //"set_
                   STR_STEP "\","              // step",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_SLIDER "\","       //"slider",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\","                   //"...",
                   "\"" STR_STEP "\":"         //"step":
                   "%s"                        //...
                   STR_END,
                   _name, value); //}>ET
  tx_create();
}

/* Command interface for setting the picture animation playback command */
// Call the example: set_play("image_animation1");
void set_play(const char *_name, ...) {
  va_list p_end;
  va_start(p_end, _name);
  int end;
  end = va_arg(p_end, int);

  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_SET_);             //"set_
  if (end == 1)
    sprintf(STONE_TX_BUF + TX_CNT, STR_PAUSE);
  if (end == 2)
    sprintf(STONE_TX_BUF + TX_CNT, STR_STOP);
  else
    sprintf(STONE_TX_BUF + TX_CNT, STR_PLAY);
  sprintf(STONE_TX_BUF + TX_CNT,
          "\","                          //...",
          "\"" STR_TYPE "\":"            //"type":
          "\"" STR_IMAGE_ANIMATION "\"," //"image_animation",
          "\"" STR_WIDGET "\":"          //"widget":
          "\"%s\""                       //"..."
          STR_END,
          _name); //}>ET
  tx_create();
}

/* Command interface for setting the pause command for picture animation playback */
// Call the example: set_pause("image_animation1");
#define set_pause(m_name) set_play(m_name, 1)

/* Command interface for setting the picture animation stop command */
//// Call the example: set_stop("image_animation1");
#define set_stop(m_name) set_play(m_name, 2)

/* Command interface for setting format commands */
// Call the example: set_format("image_value", "iamge_value1", "%02.2f");
void set_format(const char *_type, const char *_name, const char *_format) {
  if (strcmp(_type, "image_animation") == 0 || strcmp(_type, "image_value") == 0 || strcmp(_type, "digit_clock") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_FORMAT "\","            // format",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_FORMAT "\":"       //"format":
                     "\"%s\""                    //...
                     STR_END,
                     _type, _name, _format); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for setting picture commands */
// Call the example: set_image("image_value", "iamge_value1", "light_on");
void set_image(const char *_type, const char *_name, const char *_image) {

  if (strcmp(_type, "image_animation") == 0 || strcmp(_type, "image") == 0 || strcmp(_type, "image_value") == 0 || strcmp(_type, "gauge") == 0 || strcmp(_type, "guage_pointer") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_IMAGE "\","             // iamge",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_IMAGE "\":"        //"iamge":
                     "\"%s\""                    //...
                     STR_END,
                     _type, _name, _image); //}>ET

    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for the set picture animation interval command */
// Call the example: set_interval("image_animation1", "100");
void set_interval(const char *_name, const char *_interval) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2    //"ST<{cmd_code:"
                   "\"" STR_SET_                  //"set_
                   STR_INTERVAL "\","             // interval",
                   "\"" STR_TYPE "\":"            //"type":
                   "\"" STR_IMAGE_ANIMATION "\"," //"image_animation",
                   "\"" STR_WIDGET "\":"          //"widget":
                   "\"%s\","                      //"...",
                   "\"" STR_INTERVAL "\":"        //"interval":
                   "%s"                           //...
                   STR_END,
                   _name, _interval); //}>ET
  tx_create();
}

/* Command interface for setting the loop command */
// Call the example: set_loop("image_animation1", "true");
void set_loop(const char *_name, const char *_tf) {
  if (strcmp(_tf, "true") == 0 || strcmp(_tf, "false") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2    //"ST<{cmd_code:"
                     "\"" STR_SET_                  //"set_
                     STR_LOOP "\","                 // loop",
                     "\"" STR_TYPE "\":"            //"type":
                     "\"" STR_IMAGE_ANIMATION "\"," //"image_animation",
                     "\"" STR_WIDGET "\":"          //"widget":
                     "\"%s\","                      //"...",
                     "\"" STR_LOOP "\":"            //"loop":
                     "%s"                           //...
                     STR_END,
                     _name, _tf); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for setting range commands */
// Call the example: set_range("image_animation1", "1" , "10");
void set_range(const char *_name, const char *start, const char *end) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2    //"ST<{cmd_code:"
                   "\"" STR_SET_                  //"set_
                   STR_RANGE "\","                // range",
                   "\"" STR_TYPE "\":"            //"type":
                   "\"" STR_IMAGE_ANIMATION "\"," //"image_animation",
                   "\"" STR_WIDGET "\":"          //"widget":
                   "\"%s\","                      //"...",
                   "\"" STR_START_INDEX "\":"     //"start_index":
                   "%s,"                          //...,
                   "\"" STR_END_INDEX "\":"       //"end_index":
                   "%s"                           //...
                   STR_END,
                   _name, start, end); //}>ET
  tx_create();
}

/* Command interface for the set picture display method command */
// Call the example: set_draw_type("image", "image1" , "2");
void set_draw_type(const char *_type, const char *_name, const char *draw_type) {
  if (strcmp(_type, "image") == 0 || strcmp(_type, "gauge") == 0) {
    TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                     "\"" STR_SET_               //"set_
                     STR_DRAW_TYPE "\","         // draw_type",
                     "\"" STR_TYPE "\":"         //"type":
                     "\"%s\","                   //"...",
                     "\"" STR_WIDGET "\":"       //"widget":
                     "\"%s\","                   //"...",
                     "\"" STR_DRAW_TYPE "\":"    //"draw_type":
                     "%s"                        //...
                     STR_END,
                     _type, _name, draw_type); //}>ET
    tx_create();
  }
#if MCU_ARDUINO || MCU_ESP
  else {
    stone_printf("input error!");
  }
#endif
}

/* Command interface for the set image scaling command */
// Call the example: set_scale("image2", "0.5" , "1");
void set_scale(const char *_name, const char *_x, const char *_y) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_SET_               //"set_
                   STR_SCALE "\","             // scale",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_IMAGE "\","        //"image",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\","                   //"...",
                   "\"" STR_SCALE "_x\":"      //"scale_x":
                   "%s,"                       //...,
                   "\"" STR_SCALE "_y\":"      //"scale_y":
                   "%s"                        //...
                   STR_END,
                   _name, _x, _y); //}>ET
  tx_create();
}

/* Command interface for the set picture rotation angle command */
// Call the example: set_rotation("image1", "180");
void set_rotation(const char *_name, const char *_rotation) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_SET_               //"set_
                   STR_ROTATION "\","          // rotation",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_IMAGE "\","        //"image",
                   "\"" STR_WIDGET "\","       //"widget":
                   "\"%s\","                   //"...",
                   "\"" STR_ROTATION "\":"     //"rotation":
                   "%s"                        //...
                   STR_END,
                   _name, _rotation); //}>ET
  tx_create();
}

/* Command interface for setting the current selector command of the text selector */
// Call the example: set_selected("text_selector1", "20");
void set_selected(const char *_name, const char *_selected) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2   //"ST<{cmd_code:"
                   "\"" STR_SET_                 //"set_
                   STR_SELECTED "\","            // selected",
                   "\"" STR_TYPE "\":"           //"type":
                   "\"" STR_IMAGE "\","          //"image",
                   "\"" STR_WIDGET "\","         //"widget":
                   "\"%s\","                     //"...",
                   "\"" STR_SELECTED "_index\":" //"selected_index":
                   "%s"                          //...
                   STR_END,
                   _name, _selected); //}>ET
  tx_create();
}

/* Command interface to get the current selector command of the text selector */
// Call the example: get_selected("text_selector1");
void get_selected(const char *_name) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_GET_               //"get_
                   STR_SELECTED "\","          // selected",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_IMAGE "\","        //"image",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\""                    //"..."
                   STR_END,
                   _name); //}>ET
  tx_create();
}

/* Command interface for the set date command */
// Call the example: set_date("2022-02-22 22:22:22");
void set_date(const char *_name, const char *_date) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_SET_               //"set_
                   STR_DATE "\","              // date",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_DIGIT_CLOCK "\","  //"digit_clock",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\","                   //"...",
                   "\"" STR_DATE "\":"         //"date":
                   "\"%s\""                    //"..."
                   STR_END,
                   _name, _date); //}>ET
  tx_create();
}

/* Command interface for the get date command */
// Call the example: get_date("clock1");
void get_date(const char *_name) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_GET_               //"get_
                   STR_DATE "\","              // date",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_DIGIT_CLOCK "\","  //"digit_clock",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\""                    //"..."
                   STR_END,
                   _name); //}>ET
  tx_create();
}

/* Command interface for the get checked command */
// Call the example: get_checked("check1");
void get_checked(const char *_name) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2 //"ST<{cmd_code:"
                   "\"" STR_GET_               //"get_
                   STR_CHECKED "\","           // checked",
                   "\"" STR_TYPE "\":"         //"type":
                   "\"" STR_CHECK_BUTTON "\"," //"check_button",
                   "\"" STR_WIDGET "\":"       //"widget":
                   "\"%s\""                    //"..."
                   STR_END,
                   _name); //}>ET
  tx_create();
}

/* Command interface for the set angle command */
// Call the example: set_angle("pointer1", "10");
void set_angle(const char *_name, const char *_angle) {
  TX_CNT = sprintf(STONE_TX_BUF, STR_HEAD_CMD2  //"ST<{cmd_code:"
                   "\"" STR_SET_                //"set_
                   STR_ANGLE "\","              // angle",
                   "\"" STR_TYPE "\":"          //"type":
                   "\"" STR_GAUGE_POINTER "\"," //"gauge_pointer",
                   "\"" STR_WIDGET "\":"        //"widget":
                   "\"%s\","                    //"...",
                   "\"" STR_ANGLE "\":"         //"angle":
                   "\"%s\""                     //"..."
                   STR_END,
                   _name, _angle); //}>ET
  tx_create();
}

// int stone_strcpy(char *dst, char *src, ...)
//{
//	va_list ap;
//	char *p, *str;
//	int cpy_cnt = 0;
//
//	va_start(ap, src);
//	for (*dst = *src; *dst; src++,dst++)
//	{
//		cpy_cnt++;
//		if(*(dst-1) == '%' && *dst == 's')
//		{
//			for (str = va_arg(ap, char *); *str; str++,dst++)
//			{
//				*(dst-1)=*str;
//			}
//		}
//	}
//	va_end(ap);
//	return cpy_cnt;
// }
