// Supported for Leonardo, Esplora, Zero, Due and MKR Family (incl Pro Micro)

// This is a "built-in" library no need to install on Windows
// On linux, I *did* have to install it, by doing:
// Tools > Manage Libraries > Search on Keyboard > Install "Keyboard by Arduino".
#include <Keyboard.h>
#include "private.h"

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

// Used to see whether a key is being pressed or released
bool previously_pressed[5][72];
bool previously_pressed_global[72];
bool chord_invalidated[72];

// (Re)name bytes so we can have a nice key grid below
#define ESCAPE      0xB1
#define F1          0xC2
#define F2          0xC3
#define F5          0xC6
#define F11         0xCC
#define F12         0xCD
#define F13         0xF0
#define F14         0xF1
#define F15         0xF2
#define VOL_DOWN    0xF3  // F16
#define VOL_UP      0xF4  // F17
#define F20         0xF7
#define TAB         0xB3
#define INS         0xD1
#define BACKSP      0xB2
#define DEL         0xD4
#define LSHIFT      0x81
#define CTL         0x80
#define UP          0xDA
#define DOWN        0xD9
#define LEFT        0xD8
#define RIGHT       0xD7
#define HOME        0xD2
#define END         0xD5
#define ALT         0x82
#define GUI         0x83
#define RETURN      0xB0

#define FN1         '!'
#define OPTION      '!'
#define FN3         '!'
#define FN4         '!'
#define MAC         '!'

// Macro magic numbers
#define COM001      'd'  // ', '
#define SELECT2HOME '9'  // select + home
#define TERM_COPY   '1'
#define TERM_PASTE  '2'
#define MOVE_LIST_I 'h'

#define STR_KA_USER '0'
#define STR_KA_PWD  '1'
#define STR_ADM_USR '2'
#define STR_ADM_PWD '3'
#define STR_KP_PWD  '4'
#define STR_CD_GIT  '5'
#define STR_KCL_DES '6'
#define STR_KUBENS  '7'
#define STR_KUBECTL '8'
#define STR_KCL_APL '9'

// shift macros (be sure to set the keys where these are used to macro 7)
#define QUESTION_M  '/'
#define COLUMN      ';'
#define PLUS        '='
#define TILDE       '`'

String chord_str;
String print_str;

// This array is typeset to have the same layout as the keyboard
const PROGMEM uint8_t key_values[5][70] = {
  { // layer 0
    ESCAPE,       '1',             '2',           '3',           '4',       '5',         '6',                                 '7',          '8',          '9',          '-',          '-',          F11,          F12,
    TAB,          'q',             'w',           'f',           'p',       'g',        '\\',                                 ',',          'j',          'l',          'u',          'y',         '\'',          INS,
    BACKSP,       'a',             'r',           's',           't',       'd',         '[',                                 '`',          'h',          'n',          'e',          'i',          'o',         '\'',
    LSHIFT,       'z',             'x',           'c',           'v',       'b',         ']',                                 '0',          'k',          'm',          ',',         HOME,           UP,          END,
    CTL,          ALT,             GUI,        RETURN,        OPTION,       ' ',         FN3,                                 FN4,          FN1,       LSHIFT,          '.',         LEFT,         DOWN,        RIGHT,
  },
  { // layer 1 (right default)
    ESCAPE,         F1,             F2,           '3',         '4',         '5',         '6',                                 '7',          '8',          '9',          '-',           F5,          F11,          F12,
    TAB,    QUESTION_M,            '=',        COLUMN,         ';',         'g',        '\\',                                 ',',          'j',          'l',          '\'',         'y',         '\'',          INS,
    DEL,           ',',            '.',           '/',      COLUMN,         '9',         '=',                                 '`',          '0',          '.',          ',',   QUESTION_M,          '0',         '\'',
    LSHIFT,        'z',            'x',     TERM_COPY,  TERM_PASTE,         'b',        PLUS,                                 '0',          'k',          'm',       COM001,          '.',           UP,          END,
    CTL,           ALT,            GUI,        RETURN,      OPTION,         ' ',       TILDE,                              BACKSP,          FN1,       LSHIFT,         HOME,         LEFT,         DOWN,        RIGHT,
  },
  { // layer 2 (option)
    ESCAPE,        '1',             F2,           '3',         '4',         '5',         '6',                         STR_KA_USER,   STR_KA_PWD,  STR_ADM_USR,  STR_ADM_PWD,   STR_KP_PWD,          F11,          F12,
    TAB,           F14,            F13,           'f',        PLUS,         'g',        '\\',                                 ',',          'j',  SELECT2HOME,           UP,          'y',         '\'',          INS,
    DEL,           '[',            ']',           's',         TAB,         'd',         '[',                                 '`',         HOME,         LEFT,         DOWN,        RIGHT,          END,          FN3,
    LSHIFT,        'z',            'x',           'c',         'v',         'b',         ']',                                 '0',          'k',       RETURN,       COM001,          '.',           UP,          END,
    CTL,           ALT,            GUI,        RETURN,      OPTION,         ' ',         FN3,                              BACKSP,       RETURN,  MOVE_LIST_I,         HOME,         LEFT,         DOWN,        RIGHT,
  },
  { // layer 3 (pinky)
    ESCAPE,        '1',             F2,           '3',         '4',         '5',          '6',                                 '7',          '8',          '9',          '-',           F5,     VOL_DOWN,       VOL_UP,
    TAB,           'q',            'w',   STR_KCL_APL,         'p',         'g',         '\\',                                 ',',          'j',          'l',          'u',          'y',         '\'',          INS,
    DEL,           '[',            ']',          '\'',        '\'', STR_KCL_DES,          ',',                                 '`',          '3',   STR_KUBENS,          'e',          'i',          'o',          FN3,
    LSHIFT,        'z',            'x',   STR_KUBECTL,         'v',         'b',          '.',                                 '0',  STR_KUBECTL,          'm',   STR_CD_GIT,          '.',           UP,          END,
    CTL,           ALT,            GUI,        RETURN,      OPTION,         ' ',          FN3,                              BACKSP,       RETURN,  MOVE_LIST_I,         HOME,         LEFT,         DOWN,        RIGHT,
  },
  { // layer 4 (sticky)
    ESCAPE,        '1',           '2',           '3',         '4',         '5',          '6',                                 '7',          '8',          '9',          '-',         '\'',          F11,          F12,
    TAB,           'q',           'w',           'f',         'p',         'g',         '\\',                                 ',',          'j',          'l',          'u',          'y',         '\'',          INS,
    DEL,           'a',           'r',           's',         't',         'd',          '[',                                 '`',          'h',          'n',          'e',          'i',          'o',          FN3,
    LSHIFT,        'z',           'x',           'c',         'v',         'b',          ']',                                 '0',          'k',          'm',       COM001,          '.',           UP,          END,
    CTL,           ALT,           GUI,        RETURN,      OPTION,         ' ',          FN3,                              BACKSP,          FN1,       LSHIFT,         HOME,         LEFT,         DOWN,        RIGHT,
  }
};

#define SETLAYER1   1
#define SETLAYER2   2
#define SETLAYER3   3
#define SETLAYER4   4
#define KEYCOMBO    5
#define PRTSTRING   6
#define SHIFTKEYV   7
#define HYPER       8
#define SETLYR4_S   9

// This array lists which keys should be handled by macros, and if so by which one
// 0 is normal keypress/keyrelease, nonzero is macros
//int  cmd[5][72];

// This array lists which keys should be handled by macros, and if so by which one
// 0 is normal keypress/keyrelease, nonzero is macros
const PROGMEM byte cmd[5][70] = {
  { // layer 0
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,    SETLAYER2,            0,    SETLAYER3,                           SETLAYER4,    SETLAYER1,            0,            0,            0,            0,            0,
  },
  { // layer 1 (right default)
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,    SHIFTKEYV,            0,    SHIFTKEYV,            0,            0,    SHIFTKEYV,                                   0,            0,            0,            0,            0,            0,            0,
    0,    SHIFTKEYV,    SHIFTKEYV,            0,    SHIFTKEYV,    SHIFTKEYV,            0,                                   0,    SHIFTKEYV,            0,            0,    SHIFTKEYV,            0,    SHIFTKEYV,
    0,            0,            0,     KEYCOMBO,     KEYCOMBO,            0,    SHIFTKEYV,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,    SHIFTKEYV,                                   0,    SETLAYER1,            0,            0,            0,            0,            0,
  },
  { // layer 2 (option)
    0,    SETLYR4_S,            0,            0,            0,            0,            0,                           PRTSTRING,    PRTSTRING,    PRTSTRING,    PRTSTRING,    PRTSTRING,            0,            0,
    0,            0,            0,            0,    SHIFTKEYV,            0,            0,                                   0,            0,     KEYCOMBO,            0,            0,            0,            0,
    0,            0,            0,        HYPER,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,     KEYCOMBO,            0,            0,            0,            0,
  },
  { // layer 3 (pinky)
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,    PRTSTRING,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,    SHIFTKEYV,    SHIFTKEYV,            0,    SHIFTKEYV,    PRTSTRING,    SHIFTKEYV,                                   0,    SHIFTKEYV,    PRTSTRING,            0,            0,            0,            0,
    0,            0,            0,    PRTSTRING,            0,            0,    SHIFTKEYV,                                   0,    PRTSTRING,            0,    PRTSTRING,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,     KEYCOMBO,            0,            0,            0,            0,
  },
  { // layer 4 (sticky)
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,            0,            0,            0,            0,            0,            0,
    0,            0,            0,            0,            0,            0,            0,                                   0,    SETLAYER1,            0,            0,            0,            0,            0,
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
  const byte _cmd = GetCmd(id, layer);

  // press the virtual button
  if (is_pressed_now && !(active)) {
    Serial.println("Keyaction:");
    Serial.println(id, DEC);
    KeyPress(id, keyvalue, _cmd);
  }
  // release the virtual button
  else if (!(is_pressed_now) && active) {
    ReleaseKey(id, keyvalue);
  }
}

void KeyPress(int id, uint8_t keyvalue, byte _cmd) {
  const int current_layer = layer;
  if (keyvalue == KEY_ESC) {
    layer = 0;
    SetSticky(0);
  }
  if (layer == 4) {
    Chord(id, 0, keyvalue);
  }
  else if (_cmd == 0) {
    // normal key press
    if (keyvalue != KEYVALUE_BLANK) {
      Keyboard.press(keyvalue);
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
  if (layer == 4 && id != 71) {
    Serial.print("RELEASE ");
    Serial.println(id);
    Chord(id, 1, keyvalue);
    for (int i = 0; i < 72; i++) {
      if (previously_pressed_global[i]){
        chord_invalidated[i] = 1;
      }
    }
    chord_invalidated[id] = 0;
    previously_pressed[4][id] = 0;
  }
  else {
    // if the physical key was pressed last round, and is released now, then
    // go by each layer and find which virtual key was pressed, and release it
    for (int l = 0; l < 5; l++) {
      if (previously_pressed[l][id]) {
  
        // deactivate previously_pressed
        previously_pressed[l][id] = 0;
  
        const byte c_cmd = GetCmd(id, l);
  
        if (c_cmd == 0) {                    // check if macro
          // normal key release
          if (keyvalue != KEYVALUE_BLANK) {
            Keyboard.release(GetKeyVal(id, l));
          }
        }
        else {
          MacroAction(c_cmd, id, keyvalue, 1);
        }
      }
    }
  }
}

uint8_t GetKeyVal(int id, int l) {
  uint8_t key_value_index = key_lut[id];
  return pgm_read_byte(&(key_values[l][key_value_index]));
}

byte GetCmd(int id, int l) {
  byte key_value_index = key_lut[id];
  return pgm_read_byte(&(cmd[l][key_value_index]));
}

void SetSticky(bool state) {
  sticky = state;
  if (state) {
    digitalWrite(18, HIGH);
  }
  else {
    digitalWrite(18, LOW);
  }
}

void Chord(int id, bool release, uint8_t keyvalue) {
  if (release == 0){
    return;
  }
  Serial.print("Chord ");
  Serial.print(id);
  Serial.print(", ");
  Serial.print(release);
  Serial.println("");

  chord_str = String("");
  print_str = String("");

  char buffer[3];
  bool add_space = 1;
  bool capitalize = 0;

  for (int i = 0; i < 72; i++) {
    if ((i == id || previously_pressed_global[i]) && !chord_invalidated[i]) {
      if (i == 40) {
        continue;
      }
      if (i == 62) {
        add_space = 0;
        continue;
      }
      if (i == 71) {
        capitalize = 1;
        continue;
      }
      if (i < 10) {
        chord_str = chord_str + "0" + i;
        print_str = print_str + i;
      } else {
        chord_str = chord_str + i;
        print_str = print_str + i;
      }
    }
  }
  Serial.print("Chordstr ");
  Serial.println(chord_str);

  // t: 23
  // he: 60
  // re: 13
  // a: 12
  // y: 56
  // s(e): 22 
  // i: 49
  // A* --> homophones : 26
  
  if (chord_str == "23") { // t + he
    print_chord("the", add_space, capitalize);
  }
  else if (chord_str == "13222360") { // t + he + re + s
    print_chord("there's", add_space, capitalize);
  }
  else if (chord_str == "1322232660") { // t + he + re + s + A*
    print_chord("theirs", add_space, capitalize);
  }
  else if (chord_str == "132360") { // t + he + re
    print_chord("there", add_space, capitalize);
  }
  else if (chord_str == "235660") { // t + he + y
    print_chord("they", add_space, capitalize);
  }
  else if (chord_str == "1360") { // he + re
    print_chord("here", add_space, capitalize);
  }
  else if (chord_str == "1226") { // a + A*
    print_chord("a", add_space, capitalize);
  }
  else if (chord_str == "1213") { // a + re
    print_chord("are", add_space, capitalize);
  }
  else if (chord_str == "1222") { // a + s
    print_chord("as", add_space, capitalize);
  }
  else if (chord_str == "2249") { // i + s
    print_chord("is", add_space, capitalize);
  }  
  else if (chord_str == "1223") { // a + t
    print_chord("at", add_space, capitalize);
  }
  else if (chord_str == "5660") { // he + y
    print_chord("hey", add_space, capitalize);
  }
  else if (chord_str == "265660") { // he + y + A*
    print_chord("hay", add_space, capitalize);
  }
  else if (chord_str == "1356") { // re + y
    print_chord("ray", add_space, capitalize);
  }
}

void print_chord(char *str, bool add_space, bool capitalize) {

  if (add_space){ 
    Keyboard.write(' ');
  }

  int i=0;
  if (capitalize){      // Capitalize first char
    while(str[i]) { 
      if (i == 0){
        Keyboard.write(toupper((unsigned char) str[i]));
      }
      else {
        Keyboard.write(str[i]);
      }
      i++;
    }
  }
  else {                // normal print
    while(str[i]) { 
      Keyboard.write(str[i]);
      i++;
    }
  }
}

void MacroAction(int _cmd, int id, uint8_t keyvalue, bool release) {
  if (_cmd == 0) {
    Serial.println("Error: function MacroAction called with _cmd=0");
  }
  else if (_cmd == SETLAYER1 || _cmd == SETLAYER2 || _cmd == SETLAYER3 || _cmd == SETLAYER4 || _cmd == SETLYR4_S) {
    if (_cmd == SETLYR4_S) {
      MacroSetStickyLayer(release, _cmd);
    } else {
      MacroSetLayer(release, _cmd);
    }
  }
  else if (_cmd == PRTSTRING) {
    MacroPrintString(release, id, keyvalue);
  } else if (_cmd == KEYCOMBO) {
    MacroKeyCombo(release, id, keyvalue);
  } else if (_cmd == SHIFTKEYV) {
    MacroShiftKeyValue(release, id, keyvalue);
  } else if (_cmd == HYPER) {
    MacroHyperKeyValue(release, id, keyvalue);
  } else {
    Serial.println("CMD unknown @MacroAction");
    Serial.println(_cmd, DEC);
  }
}

// Switch layers
void MacroSetLayer(bool release, int layer_id) {
  if (release) {
    if (sticky == 0) {
      layer = 0;
    }
  }
  else {
    layer = layer_id;
  }
}

// Switch layers (sticky)
void MacroSetStickyLayer(bool release, int layer_id) {
  if (release) {

  }
  else {
    Serial.println("CMD sticky4 - 0");
    layer = layer_id;
    SetSticky(1);
  }
}

// Print strings
void MacroPrintString(bool release, int id, uint8_t keyvalue) {
  if (release) {
    return;
  }

  //const uint8_t keyvalue = key_values[layer][id];
  if (keyvalue == STR_ADM_USR)
  {
    Keyboard.print(USERNM1);
    Keyboard.write(KEY_TAB);
  }

  else if (keyvalue == STR_ADM_PWD)
  {
    //Keyboard.print(PASSWD1);
    for (int i = 0; i < strlen(PASSWD1); i++ ) {
      char c = PASSWD1[i];
      if (i == 0 || i == 10) {
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

  else if (keyvalue == STR_KA_USER)
  {
    Keyboard.print(USERNM2);
    Keyboard.write(KEY_TAB);
  }

  else if (keyvalue == STR_KA_PWD)
  {
    //Keyboard.print(PASSWD2);
    for (int i = 0; i < strlen(PASSWD2); i++ ) {
      char c = PASSWD2[i];
      if (i == 0 || i == 10) {
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

  else if (keyvalue == STR_KP_PWD)
  {
    //Keyboard.print(PASSWD3);
    for (int i = 0; i < strlen(PASSWD3); i++ ) {
      char c = PASSWD3[i];
      if (i == 1 || i == 4 || i == 7 || i == 10 || i == 12 || i == 14 || i == 15 || i == 17) {
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
  else if (keyvalue == STR_KUBECTL)
  {
    Keyboard.print("kubectl "); 
  }
  else if (keyvalue == STR_KCL_DES)
  {
    Keyboard.print("kubectl describe "); 
  }
  else if (keyvalue == STR_KUBENS)
  {
    Keyboard.print("kubens "); 
  }
  else if (keyvalue == STR_KCL_APL)
  {
    Keyboard.print("kubectl apply -f "); 
  }
  else if (keyvalue == STR_CD_GIT)
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
void MacroKeyCombo(bool release, int id, uint8_t keyvalue) {
  if (release) {
    return;
  }
  else {
    //const uint8_t keyvalue = key_values[layer][id];
    if (keyvalue == '0') {                         // select inner word
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.press(KEY_LEFT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_ARROW); delay(1);
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.press(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == '5') {                         // select inner word + one to the left
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write(KEY_LEFT_ARROW); delay(1);
      Keyboard.write(KEY_LEFT_ARROW); delay(1);
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.press(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_RIGHT_ARROW); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == '6') {                         // select inner word + one to the right
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
    else if (keyvalue == TERM_COPY) {                    // ctrl+insert        1
      Keyboard.press(KEY_LEFT_CTRL); delay(5);
      Keyboard.write(KEY_INSERT); delay(5);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == TERM_PASTE) {                    // shift+insert      2
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write(KEY_INSERT); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == '3') {                    // <
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.write('<'); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == '4') {                    // >
      Keyboard.press(KEY_LEFT_SHIFT); delay(1);
      Keyboard.write('>'); delay(1);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == '7') {                    // ctrl+s
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write('s'); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == '8') {                    // ctrl+return
      Keyboard.press(KEY_LEFT_CTRL); delay(1);
      Keyboard.write(KEY_RETURN); delay(1);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == SELECT2HOME) {                    // select home
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write(KEY_HOME); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == 'a') {                    // (
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write('9'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == 'b') {                    // (
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write('0'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == 'c') {                    // :
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write(';'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == COM001) {                    // ', '
      Keyboard.write(','); delay(5);
      Keyboard.write(' '); delay(5);
    }
    else if (keyvalue == 'e') {                    // :
      Keyboard.press(KEY_LEFT_SHIFT); delay(5);
      Keyboard.write('`'); delay(5);
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    else if (keyvalue == 'f') {                    // :
      Keyboard.press(KEY_LEFT_CTRL); delay(5);
      Keyboard.write('a'); delay(5);
      Keyboard.release(KEY_LEFT_CTRL);
    }
    else if (keyvalue == 'h') {                    // :
      Keyboard.write(KEY_HOME); delay(5);
      Keyboard.write(BACKSP); delay(5);
      Keyboard.write(KEY_END); delay(5);
      Keyboard.write(KEY_RETURN); delay(5);
      Keyboard.write(DOWN); delay(5);
    }
    else {
      Serial.println("CMD unknown @macro5");
    }
  }
}

// press shift before and after the keystroke
void MacroShiftKeyValue(bool release, int id, uint8_t keyvalue) {
  if (release) {
    return;
  }
  else {
    WriteShiftedValue(keyvalue); 
  }
}

void WriteShiftedValue(uint8_t keyvalue){
    Keyboard.press(KEY_LEFT_SHIFT); delay(5);
    Keyboard.write(keyvalue); delay(5);
    Keyboard.release(KEY_LEFT_SHIFT);
}

// press ctrl + shift + gui + alt before and after the keystroke
void MacroHyperKeyValue(bool release, int id, uint8_t keyvalue) {
  if (release) {
    return;
  }
  else {
    //const uint8_t keyvalue = key_values[layer][id];
    Keyboard.press(CTL); delay(5);
    Keyboard.press(LSHIFT); delay(5);
    Keyboard.press(GUI); delay(5);
    Keyboard.write(keyvalue); delay(5);
    Keyboard.release(GUI); delay(5);
    Keyboard.release(LSHIFT); delay(5);
    Keyboard.release(CTL); delay(5);
  }
}
