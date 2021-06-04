# a1plus
A multi-basic implementation of an Apple I emulator that runs  on an Adafruit Trinket M0 or Neo Trinkey.

While working on a real 6502 I got sidetracked by a lonely Adafruit Trinket M0 sitting on my desk doing nothing. I wondered if I could get a working Apple I emulator onto it. If you're not familiar with the SAMD21 chip it is based on, it has a reasonably high clock rate and a fair amount of flash and ram space. I decided to throw in some extra goodies while I was at it to make it worthwhile (see video). It worked reasonably well. With maximum compiler optimizations turned on, it seems to be running at around the equivalent of a 0.8Mhz 6502. Not great, but very usable and you can still have a lot of fun with it. Encouraged by that minor success I wanted to see how small I could go. Adafruit also has even smaller boards that plug directly into a USB port.

The chip specs are the same as the Trinket M0, but the LED's are different. BTW, I use the LED's to change color when you switch "ROM" banks (not shown in video). See below for a video showing the system in action. There is no audio in the video, but some text in the upper right corner will let you know what's happening. BTW, the video is captured from "cool-retro-term" which has a very fun simulation of analog monitors.

![](https://user-images.githubusercontent.com/7751235/120817139-4b602580-c506-11eb-929c-2dcdd13d38c4.mp4)

You can have an Apple I (sort of) on your keychain! :D 

Here are the boards if you are interested:

Trinket M0 (https://www.adafruit.com/product/3500)

<img src="https://cdn-shop.adafruit.com/1200x900/3500-00.jpg" width=200>

Neo Trinket (https://www.adafruit.com/product/4870)

<img src="https://cdn-shop.adafruit.com/970x728/4870-03.jpg" width=200>
