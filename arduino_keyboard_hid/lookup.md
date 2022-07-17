``` cpp
const PROGMEM uint8_t key_values[5][72] = {
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
   '7', '8', '9', KEY_HOME, 'j', KEY_PRINT_SCREEN, '=', '0', KEY_BACKSPACE, // 63-71 
 },
 { // layer 2 (option)
   KEY_TAB, KEY_DELETE,  KEY_LEFT_SHIFT, 'z', KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_LEFT_GUI, '!', '!', //0-8   KEY_LEFT_CTRL
   KEY_ESC, '.', KEY_F14, '!', 'r', 'x', 'c', 'v', KEY_BACKSPACE, //9-17
   '3', KEY_F2, KEY_F13, 'e', 's', 't', 'd', 'b', KEY_RETURN, // 18-26
   '6', '5', '4', '=', 'g', '`', '[', ']', '.', // 27-35
   '|', '\'', KEY_PAGE_DOWN, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, '`', '-', // 36-44
   KEY_F12, KEY_F11, ';', KEY_BACKSPACE, 'i', KEY_PAGE_UP, '\\', KEY_F20, KEY_LEFT_SHIFT, // 45-53
   '1', '4', 'y', 'u', '6', '0', '5', 'k', 'k', // 54-62
   '2', '3', '0', '9', 'j', KEY_PRINT_SCREEN, '-', '0', KEY_DELETE, // 63-71
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
 }, 
};
```