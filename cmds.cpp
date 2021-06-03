//////////////////////////////////////////////////////////////////
// 6/2021 R. Kincaid
// Routines for the hacked-in command processor
//////////////////////////////////////////////////////////////////

#include "a1plus.h"

/*
 * general help text
 */
static char* helpstring PROGMEM = R"(
Ctrl-Z prompts for these commands:
  BASIC....Apple I Integer BASIC
  ASOFT....Applesoft Lite
  EBASIC...EhBasic
  WOZMON...Apple I monitor w/BASIC
  LOAD.....Load built-in programs
  HELP.....Display this help
Ctrl-B fast switch between:
  Integer BASIC >, Applesoft ], 
  EhBasic and Wozmon \
  Apple BASICs can enter WozMon
  'with: Call -256'.
  WozMon can start Apple BASICs with:
  E000R restarts BASIC"
  E2B3R warmstarts Apple BASICs
Ctrl-D clears screen)";

/*
 * command help text
 * TODO: avoid the duplicate strings...
 */
static char* cmdstring PROGMEM = R"(
ERROR! Available commands are:
  BASIC....Apple I Integer BASIC
  ASOFT....Applesoft Lite
  EBASIC...EhBasic
  WOZMON...Apple I monitor w/IBASIC
  LOAD.....Load built-in programs
  HELP.....Display full help)";

/*
 * helper routine to add CR to help text
 */
void printhelp(char* s) {
  for(int i=0, l=strlen(s); s[i]; ++i) {
    if(s[i]=='\n') Serial.print('\r');
    Serial.print(s[i]);
  }
}

/*
 * Help prompt
 */

void help() {
  printhelp(helpstring);
}

/*
 * ANSI clear/home screen
 */
void clearscreen() { Serial.print("\x1B[H\x1B[2J"); }

/*
 * reset 6502
 */
void reset() {
  clearscreen();
  reset6502();
}

/*
 * process keystroke before passing to emulator
 */
char process_key(char key) {
  key = Serial.read() & 0x7f;
  if (key == 0x03)
    reset();
  if ((key >= 97) && (key <= 122)) // make uppercase
    key = key - 0x20;
  Serial.print(key); // echo key
  return key;
}
/*
 * Prompt and read line of input for program menu
 */
String *readline() {
  Serial.print("?");
  char key = 0;
  String *cmd = new String("");
  while (key != 0x0D) {
    while (Serial.available()) {
      delay(5);
      if (Serial.available()) {
        key = process_key(key);
        if (key != 0x0D) {
          *cmd += key;
        }
      }
    }
  }
  return cmd;
}

/*
 * Load a program with some animation
 */
static char *spinner = "|/-\\|/-\\"; // for spinner animation
void loadprog(proginfo prog) {
  char token[10];
  char *pptr = (char *)prog.bits;
  char *tptr = token;
  uint16_t load_addr = 0; // where program should load
  uint16_t prog_addr = 0; /// where program should begin execution
  int tick = -1;
  Serial.print("\r\nLoading...\r\n");
  while (*pptr != 0) {
    tptr = token;
    *tptr = 0;
    while (*pptr != ' ' && *pptr != ':' && *pptr != '\n') {
      *tptr++ = *pptr++;
    }
    if ((int)pptr % 200 == 0) {
      Serial.print("\r");
      Serial.print(spinner[tick = (++tick % 8)]);
      delay(50);
    }
    *tptr = 0;
    if (strlen(token) > 0) {
      uint16_t data = strtoul(token, NULL, 16);
      // this test is a bit fragile, but works for now
      // TODO: make this more robust
      if (data > 0xFF || load_addr == 0) {
        load_addr = data;
        prog_addr = data;
      } else if (load_addr > 0) {
        write6502(load_addr++, (uint8_t)data);
      }
    }
    ++pptr;
  }
  clearscreen();
  if (prog_addr != 0xFFFF)
    run6502(prog_addr);
}

/*
 * Process a command
 */
uint8_t process_cmd(uint8_t key) {
  switch(key) {
    case 26: /*ctrl z*/
    {
      Serial.print("\r\nCMD?");
      String cmd = "";
      char key = 0;
      while (key != 0x0D) {
        while (Serial.available()) {
          delay(5);
          if (Serial.available()) {
            key = process_key(key);
            if (key != 0x0D)
              cmd += key;
          }
        }
      }
      if (cmd.compareTo("BASIC") == 0) {
        setrom(IBASIC);
      } else if (cmd.compareTo("ASOFT") == 0) {
        setrom(ASOFT);
      } else if (cmd.compareTo("EBASIC") == 0) {
        setrom(EBASIC);
      } else if (cmd.compareTo("HELP") == 0) {
        help();
      } else if (cmd.compareTo("WOZMON") == 0) {
        Serial.println();
        setrom(3);
      } else if (cmd.compareTo("LOAD") == 0) {
        clearscreen();
        Serial.println("Enter number to load:");
        int nprogs = sizeof(programs) / sizeof(proginfo);
        for (int i = 0; i < nprogs; ++i) {
          Serial.print("    ");
          Serial.print(i + 1);
          Serial.print(" ");
          Serial.println(programs[i].name);
        }
        String *s = readline();
        int selection = s->toInt();
        if (selection > 0 && selection <= nprogs)
          loadprog(programs[selection - 1]);
        clearscreen();
        return '\r';
      } else {
        printhelp(cmdstring);
      }
      return ('\r');
      break;
    }
    case 0x02: /* CTRL-B Toggle ROM*/ 
    {
      setrom(-1);
      return 0;
    }
    case 0x03: /* CTRL-C RESET */
    { reset();
      break;
    }
    case 0x04: /* CTRL-C RESET */
    {
      clearscreen();
      break;
    }
    default:
      break;
  }
  return key;
}
