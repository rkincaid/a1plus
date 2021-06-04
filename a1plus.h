//////////////////////////////////////////////////////////////////
// 6/2021 R. Kincaid
// Some common references required by various routines
//////////////////////////////////////////////////////////////////

#include <arduino.h>
/*
 * CPU routines
 */
extern int BASICID;
extern uint8_t process_cmd(uint8_t curkey);

extern "C" {
  void setpc(uint16_t address);
  void write6502(uint16_t address, uint8_t value);
  void exec6502(int32_t tickcount);
  void reset6502();
  void serout(uint8_t val);
  void setrom(int id);
}

/*
 * LED routines
 */
extern void set_led(int color);
extern void setup_led();

/*
 * ROM identifiers
 */
enum ROMID { IBASIC = 0, ASOFT = 1, EBASIC = 2 };

/*
 * Table of programs
 */
struct proginfo {
  const char *name; /*readable name*/
  const char *bits; /*pointer to code*/
  const int romid;  /*rom id to use with this code*/
};

extern proginfo programs[9];
