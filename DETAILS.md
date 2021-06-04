### Building a1plus ###

Building the system is pretty straightforward. You need to make sure to do the following:
1. Install the necessary board definitions for the Trinket M0 or Neo Trinket. Check the Adafruit
website for instructions for your board.
3. Load the a1plus.ino file into the Arduino IDE (or whatever arduino IDE you use).
4. Configure the IDE to use your board and the appropriate USB serial port.
6. For best results set the compiler optimzations for "Fastest (-Ofast)" or "Here be dragons..."
7. Compile and upload the binary to your board.
8. Use a terminal emulator like Putty, TerraTerm or minicom to access the board, type commands in, and
get a response back.

### Using a1plus ###

The system emulates an Apple I with a number of extra features thrown in. The code initially lands
in Integer BASIC (thanks WOZ!). However, you can access a stripped down version of Applesoft (the
floating point basic on the Apple II+, etc.) and Lee Davison's Enhanced Basic. 

You can find out what's available by typing Control-Z. At the prompt type HELP and press enter/return.
You should see the following summary:
<pre>
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
Ctrl-D clears screen
</pre>
If you enter LOAD you can choose from the following programs to run:
<pre>
Enter number to load:
    1 30th Anniversary
    2 Fig-Forth
    3 Microchess
    4 21
    5 Life
    6 Lunar Lander
    7 Star Trek
    8 Little Tower
    9 15 Puzzle
?
</pre>
Simply, enter the number you chose and type enter/return. The program should then load and automatically start running.

You may notice the LEDs on the board changing color. For lack of anything better to do, I wrote some code (in leds.cpp) that changes the color to indicate which flavor of BASIC or WozMon you are currently in. It doesn't change if you just do CALL-256 or E000R, but if you use the command process to essentially switch ROM's it will change color to indicate that.

**IMPORTANT NOTES:** Since both Integer Basic and Applesoft Lite operate using the Apple I monitor (aka WozMon), it behaves very much like a real Apple I. So this has the following limitations:
1. **All text is uppercase**.
2. **Backspace does not work** (except in EhBasic). The original Apple I keyboard did not have a backspace key and Woz used the uderscore key to function as an old style "RUBOUT". You can essentially erase characters by typing the underscore which will show on the screen but it cancels the previous character.

**TIPS:** 
1. You can copy and paste code into the system and it will behave as if you typed it in. This works for BASIC programs as well as properly formatted hex data to enter into WozMon. Depending on your setup, your board may be able to catch up. If you have problems with this, many terminal emulators have settings to let you specify a per character and per line delay. You can use these to slow down the paste operation so that it does not overrun the inpute buffer of the board.
2. The code has very few dependencies on the board. If you want to try this on another Arduino-style system you simply need to modify as follows:
a. Change the memory size in cpu.c as appopriate for your board
b. Implement the appropriate LED's if any in leds.cpp. However, you can just ignore this if you don't care about the LED's since I check for the two boards I implemented and essentially make the led calls do nothing if it isn't the correct board.
c. If you have less program space than the SAMD21 you may need to remove some of the built-in program code and maybe even remove one or more of the ROM's.

