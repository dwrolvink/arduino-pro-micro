
// Supported for Leonardo, Esplora, Zero, Due and MKR Family (incl Pro Micro)

// This is a "built-in" library no need to install on Windows
// On linux, I *did* have to install it, by doing:
// Tools > Manage Libraries > Search on Keyboard > Install "Keyboard by Arduino".
#include <Keyboard.h>
#include "private.h"

// macro's are defined below. set the key to a blank value ('!') when using a macro to skip the keypress/keyrelease functions.
const uint8_t key_values[3][81] = {
  {
    KEY_TAB, KEY_LEFT_SHIFT,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, '!', KEY_LEFT_GUI, '!', '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, '1', 'q', 'a', 'r', 'x', 'c', 'v', KEY_BACKSPACE, //9-17
    '3', '2', 'w', 'f', 's', 't', 'd', 'b', ' ', // 18-26
    '6', '5', '4', 'p', 'g', '`', '[', ']', KEY_LEFT_ALT, // 27-35
    KEY_INSERT, '\'', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, ',', '-', // 36-44
    KEY_F12, KEY_F11, ';', 'o', 'i', KEY_HOME, '/', 'm', '.', // 45-53
    '0', KEY_F5, 'y', 'u', 'e', 'n', 'h', 'k', KEY_RETURN, // 54-62
    '7', '8', '9', 'l', 'j', KEY_PRINT_SCREEN, '=', 'f', '!', // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  },
  {
    KEY_TAB, KEY_LEFT_SHIFT,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, '!', KEY_LEFT_GUI, '!', '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, '1', 'q', '!', 'r', 'x', 'c', 'v', KEY_DELETE, //9-17
    '3', '2', 'w', 'e', 's', 't', 'd', 'b', ' ', // 18-26
    '6', '5', '4', 'p', 'g', '`', '[', ']', KEY_LEFT_ALT, // 27-35
    KEY_INSERT, '\'', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, ',', '-', // 36-44
    KEY_F12, KEY_F11, ';', 'o', 'i', KEY_HOME, '/', 'm', '.', // 45-53
    '0', KEY_F5, 'y', 'u', 'e', 'n', 'h', 'k', KEY_RETURN, // 54-62
    '7', '8', '9', 'l', 'j', KEY_PRINT_SCREEN, '=', 'f', '!', // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  },
  {
    KEY_TAB, KEY_LEFT_SHIFT,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, '!', KEY_LEFT_GUI, '!', '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, '1', 'q', '!', 'r', 'x', 'c', 'v', KEY_BACKSPACE, //9-17
    '3', '2', 'w', 'e', 's', 't', 'd', 'b', ' ', // 18-26
    '6', '5', '4', 'p', 'g', '`', '[', ']', KEY_LEFT_ALT, // 27-35
    KEY_INSERT, '\'', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, ',', '-', // 36-44
    KEY_F12, KEY_F11, ';', 'o', 'i', KEY_HOME, '/', 'm', '.', // 45-53
    '3', '4', 'y', 'u', 'e', '0', 'h', 'k', KEY_RETURN, // 54-62
    '0', '1', '2', 'l', 'j', KEY_PRINT_SCREEN, '=', 'f', '!', // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  },
};
int layer = 0;
bool previously_pressed[3][81];
bool previously_pressed_global[81];
int cmd[3][81]; // 0 is normal keypress/keyrelease, nonzero is macros

const uint8_t KEYVALUE_BLANK = '!';

const int col_pins[8] = {21, 20, 19, 18, 14, 16, 10, 9}; // 9, 21, 20, 19 = left, rest is right
const int row_pins[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
// keep track of which keys were pressed last cycle


//---------------------------------------------------------
//                           Setup
//---------------------------------------------------------

void setup()
{
  // fail-safe, set to low to disable keyboard output
  pinMode(15, INPUT);
  
  // scan cols
  for (int c = 0; c < 8; c++) {
    pinMode(col_pins[c], OUTPUT);
  }    

  // read rows
  for (int r = 0; r < 9; r++) {
    pinMode(row_pins[r], INPUT);
  }  

  // set macros
  cmd[0][71] = 1;               // switch to layer 1
  cmd[1][71] = 1;               // switch to layer 1
  cmd[2][71] = 1;               // switch to layer 1
  cmd[0][7]  = 2;               // switch to layer 2
  cmd[1][7]  = 2;               // switch to layer 2
  cmd[2][7]  = 2;               // switch to layer 2
  cmd[1][12] = 3;               // ctrl+a (immediate release)
  cmd[2][63] = 4;               // print usernm1
  cmd[2][64] = 4;               // print passwd1
  cmd[2][65] = 4;               // print usernm2
  cmd[2][54] = 4;               // print passwd2
  cmd[2][55] = 4;               // print passwd3
  cmd[2][59] = 5;               // select current word
  
  Serial.begin(9600);           // begin serial comms for debugging
  Keyboard.begin();             // begin keyboard
}

//---------------------------------------------------------
//                           Loop
//---------------------------------------------------------

void loop()
{  
  // check each defined key, and press/release virtual key if warranted
  for (int c = 0; c < 8; c++) {
    digitalWrite(col_pins[c], HIGH);
    delay(1);
    for (int r = 0; r < 9; r++) {
      CheckKey(c, r);
    }
    digitalWrite(col_pins[c], LOW);
    delay(1);
  }
}

void CheckKey(int col, int row)
{
  int id = (col * 9) + row;

  // check if the physical key is being pressed at the moment
  bool is_pressed_now = (digitalRead(row_pins[row]) == 1);

  // check if the physical key has been pressed during the last check
  bool active = previously_pressed_global[id];

  // update state for next check
  previously_pressed_global[id] = is_pressed_now;

  // press the virtual button
  if (is_pressed_now && !(active)) {
    Serial.println("id:");
    Serial.println(id, DEC);
    KeyAction(id, 0);
  }
  // release the virtual button
  else if (!(is_pressed_now) && active) {
    KeyAction(id, 1);
  }
}

// See also https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
void KeyAction(int id, bool release)
{
  Serial.println("Keyaction:");
  Serial.println(id);

  if (digitalRead(15) == 0){      // only act if fail-safe pin is high
    return;
  }

  if (release){
    ReleaseKey(id);
  } else {
    KeyPress(id);
  }
}

void KeyPress(int id){
  previously_pressed[layer][id] = 1;
  
  const uint8_t _cmd = cmd[layer][id];
  if (_cmd == 0){
    
    // normal key press
    const uint8_t keyvalue = key_values[layer][id];  
    if (keyvalue != KEYVALUE_BLANK) {
      Keyboard.press(keyvalue);
    }
    
  } else {
    MacroAction(_cmd, id, 0);
  }
}

// If you pressed multiple keys during the PressKey phase, be sure to release them all here
// You can also use Keyboard.releaseAll()
void ReleaseKey(int id)
{
  // if the physical key was pressed last round, and is released now, then
  // go by each layer and find which virtual key was pressed, and release it
  for (int l = 0; l < 3; l++) {
    if (previously_pressed[l][id]){
      
      // deactivate previously_pressed
      previously_pressed[l][id] = 0;
      
      // check if macro
      const uint8_t _cmd = cmd[l][id];
      if (_cmd == 0){
        // normal key release
        if (key_values[l][id] != KEYVALUE_BLANK) {
          Keyboard.release(key_values[l][id]);
        }
      }
      else {
        MacroAction(_cmd, id, 1);
      }
    }
  }
}

void MacroAction(int _cmd, int id, bool release){
  if (_cmd == 0){
    Serial.println("Error: function MacroAction called with _cmd=0");
  } else if (_cmd == 1){
    Macro1(release);
  } else if (_cmd == 2){
    Macro2(release);
  } else if (_cmd == 3){
    Macro3(release);
  } else if (_cmd == 4){
    Macro4(release, id);
  } else if (_cmd == 5){
    Macro5(release, id);
  } else {
    Serial.println("CMD unknown");
  }
}

void Macro1(bool release){
  if (release){
    layer = 0;
  }
  else {
    layer = 1;
  }
}

void Macro2(bool release){
  if (release){
    layer = 0;
  }
  else {
    layer = 2;
  }
}

void Macro3(bool release){
  if (release){
    return;
  }
  else {
    Keyboard.press(KEY_LEFT_CTRL); delay(1);
    Keyboard.press('a'); delay(1);
    Keyboard.release('a'); delay(1);
    Keyboard.release(KEY_LEFT_CTRL);
  }
}

void Macro4(bool release, int id){
  Serial.println("macro4");
  Serial.println(PASSWD1);
  
  if (release){
    return;
  }
  else {
    const uint8_t keyvalue = key_values[layer][id]; 
    if (keyvalue == '0'){
      Keyboard.print(USERNM1);
    } else if (keyvalue == '1'){
      Keyboard.print(PASSWD1);
    } else if (keyvalue == '2'){
      Keyboard.print(USERNM2);
    } else if (keyvalue == '3'){
      Keyboard.print(PASSWD2);
    } else if (keyvalue == '4'){
      Keyboard.print(PASSWD3);
    }
  }
}

// select current word
void Macro5(bool release, int id){
  if (release){
    return;
  }
  else {
    Keyboard.press(KEY_LEFT_CTRL); delay(1);
    Keyboard.press(KEY_LEFT_ARROW); delay(1);
    Keyboard.release(KEY_LEFT_ARROW); delay(1);
    Keyboard.press(KEY_LEFT_SHIFT); delay(1);
    Keyboard.press(KEY_RIGHT_ARROW); delay(1);
    Keyboard.release(KEY_RIGHT_ARROW); delay(1);
    Keyboard.release(KEY_LEFT_SHIFT); delay(1);
    Keyboard.release(KEY_LEFT_CTRL);
  }
}
