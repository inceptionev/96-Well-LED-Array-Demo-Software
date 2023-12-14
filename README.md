<p align="center">
  <img width="460" src="./CheckerboardTest.GIF">
</p>

This demo software was written to control the 96-Well LED board.
It was tested using an Arduino RP2040 Connect module.

 *  This sofware is based on and uses the TLC591x library by Andy4495: https://github.com/Andy4495/TLC591x
 *  To install this library in your Arduino IDE, go to Sketch -> Include Library -> Manage Libraries... -> Search for TL591x

To interface with the 96-Well LED Board:
 *  Write to the array state[], an array with bytes with length equal to the number of chips on the board
 *  The bottom-left cell of the board (well H1) is byte 0, bit 0.
 *  The next cell up (cell G1) is byte 0, bit 1.
 *  Cell H2 is byte 1, bit 0.
 *  Cell G2 is byte 1, bit 1.
 *  ...etc
 *  Cell A12 is byte 7, bit 7.
 *  When you have written your intended pattern, call myLED.printDirect(state) to send the pattern to the board at time you desire.
