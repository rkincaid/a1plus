//////////////////////////////////////////////////////////////////
// 6/2021 R. Kincaid
// Emulator based on the arduino_6502 project from miker00lz (Mike Chambers)
// Link: http://forum.arduino.cc/index.php?topic=193216.0
// See also: http://rubbermallet.org/fake6502.c (c) 2011
// BCD math routines from Mike B.
// http://forum.6502.org/viewtopic.php?p=37758#p37758
// apple 1 roms are (c) Steve Wozniak / Apple Inc. Status is Freeware
// according to: http://www.callapple.org/soft/ap1/emul.html
//////////////////////////////////////////////////////////////////

#include "a1plus.h"

uint8_t curkey = 0;
uint8_t iskey = 0;

extern "C"
{
  void serout(uint8_t val)
  {
    // fix some CR/LF discrepencies between BASICs
    if (BASICID < 2 && val == 13) // Apple BASICs need LF after CR
    {
      Serial.println();
    }
    else
    {
      Serial.write(val);
    }
  }

  // default to dropping into Integer Basic
  uint8_t romid = IBASIC;
  void setrom(int id)
  {
    if (id == -1)
      id = romid = (romid + 1) % 4;
    write6502(0xD020, id);
    romid = id;
    set_led(id);
  }

  uint8_t isakey()
  {
    if (Serial.available())
      iskey = 0x80;
    else
      iskey = 0;
    return (iskey);
  }

  uint8_t getkey()
  {
    curkey = Serial.read();
    curkey &= 0x7F;
    // make a-z => A-Z
    if ((curkey >= 97) && (curkey <= 122))
      curkey = curkey - 0x20;
    curkey = process_cmd(curkey);
    return (curkey);
  }

  void clearkey()
  {
    curkey = 0;
  }
}

void setup()
{
  setup_led();
  Serial.begin(9600);
  reset6502();
  setrom(IBASIC);
}

void loop()
{
  exec6502(100); //if timing is enabled, this value is in 6502 clock ticks. otherwise, simply instruction count.
}
