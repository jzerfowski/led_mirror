# LED Mirror
This is the repository for a project I started in March 2020. I had this strip with a broken LED Driver that I replaced with an arduino, connected to an RGB LED Strip driver and a knob to set the brightness.

## Material
- RGB LED strip (12v, 3 channels, RGB)
- Arduino Nano ([arduino.cc](https://store.arduino.cc/arduino-nano))
- RGB LED strip controller ([aliexpress.com](https://www.aliexpress.com/item/32837018261.html))
- 280° potentiometer knob ([aliexpress.com](https://www.aliexpress.com/item/1831856039.html))

## Code
### Required libraries
- RichUNOKitCKnob [Rich UNO R3 Kit C on Google Drive](https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U)
- [LEDStripDriver](https://github.com/letsgoING/Libraries/tree/master/LEDStripDriver)

### Description
The code is in [MirrorLEDStrip/MirrorLEDStrip.ino](MirrorLEDStrip/MirrorLEDStrip.ino). It reads the brightness from a knob on the specified pins and sends colors to the RGB LED strip controller on the specified pins.

## Images
tbd...
