// Supported for Leonardo, Esplora, Zero, Due and MKR Family (incl Pro Micro)

// This is a "built-in" library no need to install on Windows
// On linux, I *did* have to install it, by doing:
// Tools > Manage Libraries > Search on Keyboard > Install "Keyboard by Arduino".
#include <Keyboard.h>
#include "private.h"

// macro's are defined below. when a key is defined as a macro the default keystroke will not be executed.
const PROGMEM uint8_t key_values[5][81] = {
  { // layer 0
    KEY_TAB, KEY_BACKSPACE,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_RETURN, '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, '1', 'q', 'a', 'r', 'x', 'c', 'v', '!', //9-17
    '3', '2', 'w', 'f', 's', 't', 'd', 'b', ' ', // 18-26
    '6', '5', '4', 'p', 'g', '\\', '[', ']', KEY_BACKSPACE, // 27-35
    KEY_INSERT, '\"', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_HOME, '-', // 36-44
    KEY_F12, KEY_F11, ';', 'o', 'i', '.', 'd', 'm', KEY_LEFT_SHIFT, // 45-53
    '-', '\'', 'y', 'u', 'e', 'n', 'h', 'k', '!', // 54-62
    '7', '8', '9', 'l', 'j', 44, '`', '0', KEY_BACKSPACE, // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  }, 
  { // layer 1 (right default)
    KEY_TAB, KEY_DELETE,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, '.', '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, '1', '?', 'f', KEY_DELETE, 'x', '1', '2', '\'', //9-17
    '5', KEY_F2, '=', 'c', '/', KEY_TAB, 'a', '\'', ' ', // 18-26
    '6', '5', '4', ';', '_', '`', '3', '4', 'e', // 27-35
    KEY_INSERT, '\'', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, '`', '-', // 36-44
    KEY_F12, KEY_F11, ';', KEY_BACKSPACE, KEY_RIGHT_ARROW, '`', ',', '0', KEY_LEFT_SHIFT, // 45-53
    '-', KEY_F5, KEY_END, KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, 'b', '_', '!', // 54-62
    '7', '8', '9', KEY_HOME, 'j', KEY_PRINT_SCREEN, '=', '0', KEY_BACKSPACE, // 63-71  -_
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  },
  { // layer 2 (option)
    KEY_TAB, KEY_DELETE,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, '!', '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, '.', KEY_F14, '!', 'r', 'x', 'c', 'v', KEY_BACKSPACE, //9-17
    '3', KEY_F2, KEY_F13, 'e', 's', 't', 'd', 'b', KEY_RETURN, // 18-26
    '6', '5', '4', '+', 'g', '`', '[', ']', '.', // 27-35
    '|', '\'', KEY_PAGE_DOWN, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, '`', '-', // 36-44
    KEY_F12, KEY_F11, ';', KEY_BACKSPACE, 'i', KEY_PAGE_UP, '\\', KEY_F20, KEY_LEFT_SHIFT, // 45-53
    '1', '4', 'y', 'u', '6', '0', '5', 'k', 'k', // 54-62
    '2', '3', '0', '9', 'j', KEY_PRINT_SCREEN, '-', '0', KEY_DELETE, // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  },
  { // layer 3 (pinky)
    KEY_TAB, KEY_DELETE,  KEY_LEFT_SHIFT, '9', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_RETURN, '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, ',', 'q', KEY_RETURN, 'r', '0', ',', '.', '!', //9-17
    '3', '.', '[', ']', '\'', '\'', 'd', 'b', ' ', // 18-26
    '6', '5', '4', '.', '/', '\\', '[', ']', KEY_BACKSPACE, // 27-35
    KEY_INSERT, '\"', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, '0', '-', // 36-44
    KEY_F12, KEY_F11, ';', '0', '6', '9', '8', '7', KEY_LEFT_SHIFT, // 45-53
    '-', KEY_F5, '3', '2', '5', '4', 'h', 'k', KEY_RETURN, // 54-62
    '7', '8', '9', '1', 'j', 44, '`', '0', KEY_BACKSPACE, // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  }, 
  { // layer 4 (sticky)
    KEY_TAB, KEY_BACKSPACE,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, KEY_RETURN, '!', //0-8   KEY_LEFT_CTRL
    KEY_ESC, 's', 'q', 'a', 'r', 'x', 'c', 'v', '!', //9-17
    '3', '2', 'w', 'f', 's', 't', 'd', 'b', ' ', // 18-26
    '6', '5', '4', 'p', 'g', '\\', '[', ']', KEY_BACKSPACE, // 27-35
    KEY_INSERT, '\"', KEY_END, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_HOME, '-', // 36-44
    KEY_F12, KEY_F11, ';', 'o', 'i', '.', 'd', 'm', KEY_LEFT_SHIFT, // 45-53
    '-', '\'', 'y', 'u', 'e', 'n', 'h', 'k', '!', // 54-62
    '7', '8', '9', 'l', 'j', 44, '`', '0', KEY_BACKSPACE, // 63-71
    '!', '!', '!', '!', '!', '!', '!', '!', '!', //  72-80
  }, 
};
int layer = 0;
bool previously_pressed[5][81];
bool previously_pressed_global[81];
bool sticky = 0;
int cmd[5][81]; // 0 is normal keypress/keyrelease, nonzero is macros

const uint8_t KEYVALUE_BLANK = '!';

const int col_pins[8] = {21, 20, 19, 15, 14, 16, 10, 9}; // 9, 21, 20, 19 = left, rest is right
const int row_pins[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
// keep track of which keys were pressed last cycle


//---------------------------------------------------------
//                           Setup
//---------------------------------------------------------

void setup()
{
  // fail-safe, set to low to disable keyboard output
  //pinMode(18, INPUT);

  // sticky led
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  
  // scan cols
  for (int c = 0; c < 8; c++) {
    pinMode(col_pins[c], OUTPUT);
  }    

  // read rows
  for (int r = 0; r < 9; r++) {
    pinMode(row_pins[r], INPUT);
  }  

  // set macros
  cmd[0][62] = 1;               // switch to layer 1
  cmd[0][17] = 2;               // switch to layer 2
  cmd[0][35] = 6;               // switch to layer 3
  cmd[0][37] = 6;               // switch to layer 3
  cmd[2][10] = 8;               // switch to layer 4 (sticky)
  
  cmd[1][62] = 1;               // switch to layer 1
  //cmd[1][17]  = 2;               // switch to layer 2
  cmd[1][12] = 4;               // ctrl+a (immediate release)

  cmd[1][15] = 5;               // ctrl+c
  cmd[1][16] = 5;               // ctrl+v    
  cmd[1][33] = 5;               // <
  cmd[1][34] = 5;               // >
  cmd[1][35] = 5;               // ~
  //cmd[1][22] = 5;               // ctrl+s
  //cmd[1][26] = 5;               // ctrl+return
  cmd[1][18] = 4;               // print cd ~/git <return>
  cmd[1][24] = 5;               // (
  cmd[1][60] = 5;               // )
  cmd[1][21] = 5;               // :
  cmd[0][51] = 5;               // ", "
  cmd[3][24] = 5;               // ", "
  
  //cmd[2][62] = 1;               // switch to layer 1
  cmd[2][17]  = 2;               // switch to layer 2
  cmd[2][63] = 4;               // print usernm1
  cmd[2][64] = 4;               // print passwd1
  cmd[2][65] = 4;               // print usernm2
  cmd[2][54] = 4;               // print passwd2
  cmd[2][55] = 4;               // print passwd3
  
  cmd[2][59] = 5;               // select current word
  cmd[2][60] = 5;               // select current word (one to the left)
  cmd[2][58] = 5;               // select current word (one to the right)
  cmd[2][66] = 5;               // select to home

  cmd[3][15] = 7;               // shift of what is at that slot
  cmd[3][16] = 7;               // shift of what is at that slot
  cmd[3][20] = 7;               // shift of what is at that slot
  cmd[3][21] = 7;               // shift of what is at that slot
  cmd[3][23] = 7;               // shift of what is at that slot
  cmd[3][3] = 7;               // shift of what is at that slot
  cmd[3][14] = 7;               // shift of what is at that slot
    
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
  delay(5);
}

void SetSticky(bool state){
  sticky = state;
  if (state){
    digitalWrite(18, HIGH);
  }
  else {
    digitalWrite(18, LOW);
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
  Serial.println(id, DEC);

  //if (digitalRead(18) == 0){      // only act if fail-safe pin is high
  //  return;
  //}

  const uint8_t keyvalue = pgm_read_byte(&(key_values[layer][id]));

  if (release){
    ReleaseKey(id, keyvalue);
  } else {
    KeyPress(id, keyvalue);
  }
}

void KeyPress(int id, uint8_t keyvalue){
  const uint8_t _cmd = cmd[layer][id];
  const int current_layer = layer;

  if (_cmd == 0){
    // normal key press
    if (keyvalue != KEYVALUE_BLANK) {
      Keyboard.press(keyvalue);
    }
    if (keyvalue == KEY_ESC){
      layer = 0;
      SetSticky(0);
    }
  } else {
    MacroAction(_cmd, id, keyvalue, 0);
  }

  previously_pressed[current_layer][id] = 1;
}

// If you pressed multiple keys during the PressKey phase, be sure to release them all here
// You can also use Keyboard.releaseAll()
void ReleaseKey(int id, uint8_t keyvalue)
{
  // if the physical key was pressed last round, and is released now, then
  // go by each layer and find which virtual key was pressed, and release it
  for (int l = 0; l < 5; l++) {
    if (previously_pressed[l][id]){
      
      // deactivate previously_pressed
      previously_pressed[l][id] = 0;
      
      // check if macro
      const uint8_t _cmd = cmd[l][id];
      if (_cmd == 0){
        // normal key release
        if (keyvalue != KEYVALUE_BLANK) {
          Keyboard.release(keyvalue);
        }
      }
      else {
        MacroAction(_cmd, id, keyvalue, 1);
      }
    }
  }
}

void MacroAction(int _cmd, int id, uint8_t keyvalue, bool release){
  if (_cmd == 0){
    Serial.println("Error: function MacroAction called with _cmd=0");
  } 
  else if (_cmd == 1){
    Macro1(release, 1);
  } else if (_cmd == 2){
    Macro1(release, 2);
  } else if (_cmd == 6){
    Macro1(release, 3);
  } 
  else if (_cmd == 4){
    Macro4(release, id, keyvalue);
  } else if (_cmd == 5){
    Macro5(release, id, keyvalue);
  } else if (_cmd == 7){
    Macro7(release, id, keyvalue);
  } else if (_cmd == 8){
    MacroSetStickyLayer(release, 4);
  } else {
    Serial.println("CMD unknown");
  }
}

// Switch layers
void Macro1(bool release, int layer_id){
  if (release){
    if (sticky == 0){
      layer = 0;
    }
  }
  else {
    layer = layer_id;
  }
}

// Switch layers (sticky)
void MacroSetStickyLayer(bool release, int layer_id){
  if (release){
   
  }
  else {
    Serial.println("CMD sticky4 - 0");
    layer = layer_id;
    SetSticky(1);
  }
}

// Print strings
void Macro4(bool release, int id, uint8_t keyvalue){
  if (release){
    return;
  }

  //const uint8_t keyvalue = key_values[layer][id]; 
  if (keyvalue == '0')
  {
    Keyboard.print(USERNM1);
    Keyboard.write(KEY_TAB);
  } 
  
  else if (keyvalue == '1')
  {
    //Keyboard.print(PASSWD1);
    for(int i =0; i < strlen(PASSWD1); i++ ) {
      char c = PASSWD1[i];
      if (i == 0 || i == 8){
        Keyboard.press(KEY_LEFT_SHIFT); delay(10);
        Keyboard.write(c); delay(10);
        Keyboard.release(KEY_LEFT_SHIFT); delay(10);
      }
      else {
        Keyboard.write(c); delay(10);
      }
    }
    Keyboard.write(KEY_RETURN);
  } 
  
  else if (keyvalue == '2')
  {
    Keyboard.print(USERNM2);
    Keyboard.write(KEY_TAB);
  } 
  
  else if (keyvalue == '3')
  {
    //Keyboard.print(PASSWD2);
    for(int i =0; i < strlen(PASSWD2); i++ ) {
      char c = PASSWD2[i];
      if (i == 0 || i == 8){
        Keyboard.press(KEY_LEFT_SHIFT); delay(10);
        Keyboard.write(c); delay(10);
        Keyboard.release(KEY_LEFT_SHIFT); delay(10);
      }
      else {
        Keyboard.write(c); delay(10);
      }
    }
    Keyboard.write(KEY_RETURN);
  } 
  
  else if (keyvalue == '4')
  {
    //Keyboard.print(PASSWD3);
    for(int i =0; i < strlen(PASSWD3); i++ ) {
      char c = PASSWD3[i];
      if (i == 1 || i == 4 || i == 7 || i == 10 || i == 12 || i == 14 || i == 15 || i == 17){
        Keyboard.press(KEY_LEFT_SHIFT); delay(10);
        Keyboard.write(c); delay(10);
        Keyboard.release(KEY_LEFT_SHIFT); delay(10);
      }
      else {
        Keyboard.write(c); delay(10);
      }
    }
    Keyboard.write(KEY_RETURN);
  } 

  if (keyvalue == '5')
  {
    Keyboard.print("cd "); delay(5);
    
    Keyboard.press(KEY_LEFT_SHIFT); delay(5);
    Keyboard.write('`'); delay(5);
    Keyboard.release(KEY_LEFT_SHIFT); delay(5);
    
    Keyboard.print("/git"); delay(5);
    Keyboard.write(KEY_RETURN);
  } 
}

// Key combos
void Macro5(bool release, int id, uint8_t keyvalue){
  if (release){
    return;
  }
  else {
    //const uint8_t keyvalue = key_values[layer][id]; 
    if (keyvalue == '0'){                          // select inner word
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.press(KEY_LEFT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_ARROW); delay(1);
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.press(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    } 
    else if (keyvalue == '5'){                          // select inner word + one to the left
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write(KEY_LEFT_ARROW); delay(1);
      Keyboard.write(KEY_LEFT_ARROW); delay(1);
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.press(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    } 
    else if (keyvalue == '6'){                          // select inner word + one to the right
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_CTRL); delay(1);
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write(KEY_LEFT_ARROW); delay(1);
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.press(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == '1'){                     // ctrl+insert        
      Keyboard.press(KEY_LEFT_CTRL); delay(5);
      Keyboard.write(KEY_INSERT); delay(5);
      Keyboard.release(KEY_LEFT_CTRL);
    } 
    else if (keyvalue == '2'){                     // shift+insert
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write(KEY_INSERT); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    } 
    else if (keyvalue == '3'){                     // <
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.write('<'); delay(1);                 
      Keyboard.release(KEY_LEFT_SHIFT);
    } 
    else if (keyvalue == '4'){                     // >
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.write('>'); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == '7'){                     // ctrl+s
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write('s'); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == '8'){                     // ctrl+return
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write(KEY_RETURN); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    } 
    else if (keyvalue == '9'){                     // select home
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write(KEY_HOME); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    } 
    else if (keyvalue == 'a'){                     // (
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write('9'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    } 
    else if (keyvalue == 'b'){                     // (
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write('0'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    } 
    else if (keyvalue == 'c'){                     // :
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write(';'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == 'd'){                     // ', '
      Keyboard.write(','); delay(5);
      Keyboard.write(' '); delay(5);
    }
    else if (keyvalue == 'e'){                     // :
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write('`'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == 'f'){                     // :
      Keyboard.press(KEY_LEFT_CTRL); delay(5);
      Keyboard.write('a'); delay(5);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else {
      Serial.println("CMD unknown");
    }
  }
}

// press shift before and after the keystroke
void Macro7(bool release, int id, uint8_t keyvalue){
  if (release){
    return;
  }
  else {
    //const uint8_t keyvalue = key_values[layer][id]; 
    Keyboard.press(KEY_LEFT_SHIFT); delay(5);
    Keyboard.write(keyvalue); delay(5);
    Keyboard.release(KEY_LEFT_SHIFT);
  }
}
