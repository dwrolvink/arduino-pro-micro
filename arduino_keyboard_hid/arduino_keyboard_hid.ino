// Supported for Leonardo, Esplora, Zero, Due and MKR Family (incl Pro Micro)

// This is a "built-in" library no need to install on Windows
// On linux, I *did* have to install it, by doing:
// Tools > Manage Libraries > Search on Keyboard > Install "Keyboard by Arduino".
#include <Keyboard.h>
#include "private.h"

// (Re)name bytes so we can have a nice key grid below
#define ESC     0xB1
#define F11     0xCC
#define F12     0xCD
#define F13     0xF0
#define F14     0xF1
#define F20     0xF7
#define TAB     0xB3
#define INS     0xD1
#define BSP     0xB2
#define DEL     0xD4
#define KLS     0x81
#define CTL     0x80
#define KUA     0xDA
#define KDA     0xD9
#define KLA     0xD8
#define KRA     0xD7
#define HOM     0xD2
#define END     0xD5
#define ALT     0x82
#define GUI     0x83
#define RET     0xB0

#define FN1    '!'
#define OPT    '!'
#define FN3    '!'
#define MAC    '!' 

// Macro magic numbers
#define MC1    'd'  // ', '
#define S2H    '9'  // select + home

// shift macros (be sure to set the keys where these are used to macro 7)
#define QUE    '/'
#define COL    ';'
#define PLS    '='
#define TIL    '`'

// The lookup table is used to convert custom scancodes to key values 
// A scancode of a key (named "id" in code) is (col * 9) + row;
// E.g.:  uint8_t key_value = key_value[key_lut[scancode]] (simplified)
const  uint8_t key_lut[72] = {
   14, 28, 42, 43, 56, 57,         58, 59,  0,  0,  1,         15, 29, 30, 44, 45,         46, 60,  3,  2, 16,          // 0 - 20
       17, 31, 32, 33, 47,         61,  6,  5,  4, 18,         19, 20, 34, 48, 62,         27, 41, 55, 54, 69,          // 21 - 40
       68, 67, 66,  0, 13,         12, 26, 40, 39, 53,         52, 51, 65, 10, 11,         25, 24, 38, 37, 36,          // 41 - 60
       50, 64,  7,  8,  9,         23, 22, 21, 35, 49,         63            // 61 - 71
};

const uint8_t KEYVALUE_BLANK = '!';

// This array lists which keys should be handled by macros, and if so by which one
// 0 is normal keypress/keyrelease, nonzero is macros
int  cmd[5][72];    

// Used to see whether a key is being pressed or released
bool previously_pressed[5][72];
bool previously_pressed_global[72]; 

// This array is typeset to have the same layout as the keyboard
const PROGMEM uint8_t key_values[5][70] = {
  { // layer 0
    ESC,    '1',    '2',    '3',    '4',    '5',    '6',                           '7',    '8',    '9',    '-',   '\'',    F11,    F12, 
    TAB,    'q',    'w',    'f',    'p',    'g',   '\\',                           ',',    'j',    'l',    'u',    'y',   '\'',    INS,  
    BSP,    'a',    'r',    's',    't',    'd',    '[',                           '`',    'h',    'n',    'e',    'i',    'o',    FN3, 
    KLS,    'z',    'x',    'c',    'v',    'b',    ']',                           '0',    'k',    'm',    MC1,    '.',    KUA,    END, 
    CTL,    ALT,    GUI,    RET,    OPT,    ' ',    FN3,                           BSP,    FN1,    KLS,    HOM,    KLA,    KDA,    KRA, 
  }, 
  { // layer 1 (right default)
    ESC,    '1',    '2',    '3',    '4',    '5',    '6',                           '7',    '8',    '9',    '-',   '\'',    F11,    F12, 
    TAB,    QUE,    '=',    COL,    ';',    'g',   '\\',                           ',',    'j',    'l',    'u',    'y',   '\'',    INS,  
    DEL,    'a',    'r',    '/',    TAB,    '9',    '[',                           '`',    '0',    'n',    'e',    'i',    'o',    FN3, 
    KLS,    'z',    'x',    'c',    'v',    'b',    ']',                           '0',    'k',    'm',    MC1,    '.',    KUA,    HOM, 
    CTL,    ALT,    GUI,    RET,    OPT,    ' ',    TIL,                           BSP,    FN1,    KLS,    HOM,    KLA,    KDA,    KRA, 
  },
  { // layer 2 (option)
    ESC,    '1',    '2',    '3',    '4',    '5',    '6',                           '7',    '8',    '9',    '-',   '\'',    F11,    F12, 
    TAB,    F14,    F13,    'f',    PLS,    'g',   '\\',                           ',',    'j',    S2H,    'u',    'y',   '\'',    INS,  
    DEL,    'a',    'r',    's',    't',    'd',    '[',                           '`',    'h',    'n',    'e',    'i',    'o',    FN3, 
    KLS,    'z',    'x',    'c',    'v',    'b',    ']',                           '0',    'k',    F20,    MC1,    '.',    KUA,    END, 
    CTL,    ALT,    GUI,    RET,    OPT,    ' ',    FN3,                           BSP,    FN1,    KLS,    HOM,    KLA,    KDA,    KRA, 
  }, 
  { // layer 3 (pinky)
    ESC,    '1',    '2',    '3',    '4',    '5',    '6',                           '7',    '8',    '9',    '-',   '\'',    F11,    F12, 
    TAB,    'q',    'w',    'f',    'p',    'g',   '\\',                           ',',    'j',    'l',    'u',    'y',   '\'',    INS,  
    DEL,    'a',    'r',    '\'',    '\'',    'd',    '[',                           '`',    'h',    'n',    'e',    'i',    'o',  FN3, 
    KLS,    'z',    'x',    'c',    'v',    'b',    ']',                           '0',    'k',    'm',    MC1,    '.',    KUA,    END, 
    CTL,    ALT,    GUI,    RET,    OPT,    ' ',    FN3,                           BSP,    FN1,    KLS,    HOM,    KLA,    KDA,    KRA, 
  }, 
  { // layer 4 (sticky)
    ESC,    '1',    '2',    '3',    '4',    '5',    '6',                           '7',    '8',    '9',    '-',   '\'',    F11,    F12, 
    TAB,    'q',    'w',    'f',    'p',    'g',   '\\',                           ',',    'j',    'l',    'u',    'y',   '\'',    INS,  
    DEL,    'a',    'r',    's',    't',    'd',    '[',                           '`',    'h',    'n',    'e',    'i',    'o',    FN3, 
    KLS,    'z',    'x',    'c',    'v',    'b',    ']',                           '0',    'k',    'm',    MC1,    '.',    KUA,    END, 
    CTL,    ALT,    GUI,    RET,    OPT,    ' ',    FN3,                           BSP,    FN1,    KLS,    HOM,    KLA,    KDA,    KRA, 
  }
};

// The layer that we are currently in
int layer = 0;

// When in a sticky layer (layer 4) we don't want to go back to layer zero after releasing a layer key
// This is default behavior so this variable turns that off. Escape turns sticky mode off.
bool sticky = 0;


//---------------------------------------------------------
//                           Setup
//---------------------------------------------------------
// The physical pins that the cols and rows are attached to.
// 9, 21, 20, 19 = left side of the board, rest is right
const int col_pins[8] = {21, 20, 19, 15, 14, 16, 10, 9}; 
const int row_pins[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};

void setup()
{
  // sticky led, turns on when layer 4 (sticky layer) is active
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
  cmd[2][17]  = 2;              // switch to layer 2
  cmd[1][62] = 1;               // switch to layer 1

  cmd[1][12] = 4;               // ctrl+a (immediate release)
  cmd[1][18] = 4;               // print cd ~/git <return>
  
  cmd[2][63] = 4;               // print usernm1
  cmd[2][64] = 4;               // print passwd1
  cmd[2][65] = 4;               // print usernm2
  cmd[2][54] = 4;               // print passwd2
  cmd[2][55] = 4;               // print passwd3
  
  cmd[1][15] = 5;               // ctrl+c
  cmd[1][16] = 5;               // ctrl+v    
  cmd[1][33] = 5;               // <
  cmd[1][34] = 5;               // >
  cmd[2][59] = 5;               // select current word
  cmd[2][60] = 5;               // select current word (one to the left)
  cmd[2][58] = 5;               // select current word (one to the right)
  cmd[2][66] = 5;               // select to home
  cmd[0][51] = 5;               // ", "

  // shift of what is at that slot
  cmd[1][21] = 7;               
  cmd[1][11] = 7;               
  cmd[1][24] = 7;              
  cmd[1][60] = 7;             
  cmd[2][30] = 7;               
  cmd[3][15] = 7;               
  cmd[3][16] = 7;               
  cmd[3][20] = 7;               
  cmd[3][21] = 7;               
  cmd[3][23] = 7;               
  cmd[3][3] = 7;                
  cmd[3][14] = 7;    
  cmd[1][35] = 7;               // ~           
  
  Serial.begin(9600);           // begin serial comms for debugging
  Keyboard.begin();             // begin keyboard
}
      
//---------------------------------------------------------
//                           Loop
//---------------------------------------------------------

void loop()
{  
  // loop through each key in the matrix and check whether it is pressed
  // based on the combinations of the key being pressed or not and the state of the button in the previous iteration a release or press will be executed
  // this can either be a normal key action or a macro.
  for (int c = 0; c < 8; c++) 
  {
    digitalWrite(col_pins[c], HIGH);
    delay(1);
    for (int r = 0; r < 9; r++) 
    {
      CheckKey(c, r);
    }
    digitalWrite(col_pins[c], LOW);
    delay(1);
  }
  delay(5);
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

  // get the key value
  uint8_t keyvalue = GetKeyVal(id, layer);

  // press the virtual button
  if (is_pressed_now && !(active)) {
    Serial.println("Keyaction:");
    Serial.println(id, DEC);
    KeyPress(id, keyvalue);
  }
  // release the virtual button
  else if (!(is_pressed_now) && active) {
    ReleaseKey(id, keyvalue);
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

uint8_t GetKeyVal(int id, int l){
  uint8_t key_value_index = key_lut[id];
  return pgm_read_byte(&(key_values[l][key_value_index]));
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
          Keyboard.release(GetKeyVal(id, l));
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
    Serial.println("CMD unknown @MacroAction");
    Serial.println(_cmd, DEC);
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
    else if (keyvalue == S2H){                     // select home
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
    else if (keyvalue == MC1){                     // ', '
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
      Serial.println("CMD unknown @macro5");
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
