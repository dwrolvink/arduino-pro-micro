
// Supported for Leonardo, Esplora, Zero, Due and MKR Family (incl Pro Micro)

// This is a "built-in" library no need to install on Windows
// On linux, I *did* have to install it, by doing:
// Tools > Manage Libraries > Search on Keyboard > Install "Keyboard by Arduino".
#include <Keyboard.h>


const uint8_t key_values[81] = {
  '6', '5', '4', 'p', '!', '!', '!', '!', KEY_LEFT_ALT, //0-8
  '3', '2', 'w', 'f', '!', '!', '!', '!', ' ', //9-17
  KEY_ESC, '1', 'q', 'a', '!', '!', '!', '!', KEY_LEFT_SHIFT, // 18-26
  't', KEY_DELETE, KEY_LEFT_CTRL, 'z', '!', '!', '!', '!', '!', // 27-35
  '!', '!', '!', '!', '!', '!', '!', '!', '!', // 36-44
  '!', '!', '!', '!', '!', '!', '!', '!', '!', // 45-53
  '!', '!', '!', '!', '!', '!', '!', '!', '!', // 53-62
  '!', '!', '!', '!', '!', '!', '!', '!', '!', // 63-71
  '!', '!', '!', '!', '!', '!', '!', '!', '!', // 71-80
};
const char* key_labels[81] = {
  "6", "5", "4", "p", "!", "!", "!", "!", "KEY_LEFT_ALT", //0-8
  "3", "2", "w", "f", "!", "!", "!", "!", "KEY_SPACE", //9-17
  "Esc", "1", "q", "a", "!", "!", "!", "!", "KEY_LEFT_SHIFT", // 18-26
  "t", "del", "KEY_LEFT_CTRL", "z", "!", "!", "!", "!", "!", // 27-35
  "!", "!", "!", "!", "!", "!", "!", "!", "!", // 36-44
  "!", "!", "!", "!", "!", "!", "!", "!", "!", // 45-53
  "!", "!", "!", "!", "!", "!", "!", "!", "!", // 53-62
  "!", "!", "!", "!", "!", "!", "!", "!", "!", // 63-71
  "!", "!", "!", "!", "!", "!", "!", "!", "!" // 71-80
};
const uint8_t KEYVALUE_BLANK = '!';

const int col_pins[4] = {9, 21, 20, 19};
const int row_pins[9] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
// keep track of which keys were pressed last cycle
bool previously_pressed[81];

//---------------------------------------------------------
//                           Setup
//---------------------------------------------------------

void setup()
{
  // scan cols
  for (int c = 0; c < 4; c++) {
    pinMode(col_pins[c], OUTPUT);
  }    

  // read rows
  for (int r = 0; r < 9; r++) {
    pinMode(row_pins[r], INPUT);
  }  

  Serial.begin(9600);          // begin serial comms for debugging
  Keyboard.begin();            // begin keyboard
}

//---------------------------------------------------------
//                           Loop
//---------------------------------------------------------

void loop()
{
  // check each defined key, and press/release virtual key if warranted
  for (int c = 0; c < 4; c++) {
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
  bool active = previously_pressed[id];

  // update state for next check
  previously_pressed[id] = is_pressed_now;

  // press the virtual button
  if (is_pressed_now && !(active)) {
    Serial.println(id, DEC);
    PressKey(id);
  }

  // release the virtual button
  else if (!(is_pressed_now) && active) {
    ReleaseKey(id);
  }
}

// See also https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
void PressKey(int id)
{
  const uint8_t keyvalue = key_values[id];
  if (keyvalue != KEYVALUE_BLANK) {
    Serial.println("press:");
    Serial.println(key_labels[id]);
    Keyboard.press(keyvalue);
  }
}

// If you pressed multiple keys during the PressKey phase, be sure to release them all here
// You can also use Keyboard.releaseAll()
void ReleaseKey(int id)
{
  const uint8_t keyvalue = key_values[id];
  if (keyvalue != KEYVALUE_BLANK) {
    Serial.println("release:");
    Serial.println(key_labels[id]);
    Keyboard.release(keyvalue);
  }
}
