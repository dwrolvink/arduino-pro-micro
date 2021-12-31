
// Supported for Leonardo, Esplora, Zero, Due and MKR Family (incl Pro Micro)

// This is a "built-in" library no need to install on Windows
// On linux, I *did* have to install it, by doing:
// Tools > Manage Libraries > Search on Keyboard > Install "Keyboard by Arduino".
#include <Keyboard.h>   

// Set which pins correspond to which keys
// Be sure to route switches between pin and ground, as we do a pullup later on
// this doubles as the id in "previously_pressed"
// #define KEY1   9
// #define KEY2   8
// #define KEY3   7
// #define KEY4   6
// #define KEY5   5
// #define KEY6   4
// #define KEY7   3
// #define KEY8   2

// list of all keys for easy iteration
//int keys[] = { KEY1, KEY2, KEY3, KEY4, KEY5, KEY6, KEY7, KEY8 };

// keep track of which keys were pressed last cycle
bool previously_pressed[10];

//---------------------------------------------------------
//                           Setup
//---------------------------------------------------------

void setup() 
{
  
  /*  
   *  Pullup means that the keyboard switches must be routed from a pin to ground
   *  Default output of any pin will be 1, when the key is pressed, the pin registers
   *  0. This is to get rid of noise, mostly.
   */ 

  pinMode(8,INPUT);  // sets pin 8 to input & pulls it high w/ internal resistor
  
  Serial.begin(9600);          // begin serial comms for debugging
  Keyboard.begin();            // begin keyboard 
}

//---------------------------------------------------------
//                           Loop
//---------------------------------------------------------

void loop() 
{
   // check each defined key, and press/release virtual key if warranted
   //for (int i = 0; i <= sizeof(keys); i++) {  
      CheckKey(8);
   //}
    
   delay(1);
}

void CheckKey(int id)
{
  // check if the physical key is being pressed at the moment
  bool is_pressed_now = (digitalRead(id) == 1);
  
  // check if the physical key has been pressed during the last check
  bool active = previously_pressed[id];
  
  // update state for next check
  previously_pressed[id] = is_pressed_now;
  
  // press the virtual button
  if (is_pressed_now && !(active)){
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
  
  switch (id) {
    // case KEY1:    
    //   Keyboard.press('a');
    //   break;
    case KEY2:
      Serial.println("press");
      Keyboard.press('b');
      break;
    // case KEY3:    
    //   Keyboard.press('c');
    //   break;
    // case KEY4:    
    //   Keyboard.press('d');
    //   break;
    // case KEY5:    
    //   Keyboard.press('e');
    //   break;
    // case KEY6:    
    //   Keyboard.press('f');
    //   break;
    // case KEY7:    
    //   Keyboard.press('g');
    //   break;
    // case KEY8:    
    //   Keyboard.press('h');
    //   break;                       
  }  
}

// If you pressed multiple keys during the PressKey phase, be sure to release them all here
// You can also use Keyboard.releaseAll()
void ReleaseKey(int id)
{
  switch (id) {
    // case KEY1:    
    //   Keyboard.release('a');
    //   break;
    case KEY2:
      Serial.println("release");
      Keyboard.release('b');
      break;
    // case KEY3:    
    //   Keyboard.release('c');
    //   break;
    // case KEY4:    
    //   Keyboard.release('d');
    //   break;
    // case KEY5:    
    //   Keyboard.release('e');
    //   break;
    // case KEY6:    
    //   Keyboard.release('f');
    //   break;
    // case KEY7:    
    //   Keyboard.release('g');
    //   break;
    // case KEY8:    
    //   Keyboard.release('h');
    //   break;                       
  }  
}