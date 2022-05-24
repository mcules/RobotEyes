# RobotEyes
Animated robotic eyes

In this PlatformIO project, a SSD1327 128x128 pixel grayscale OLED with an ESP32 is used.

Only the upper half of the display is used at the moment. In the lower part, texts should be able to be displayed later.

## Connect the Hardware:
Display|ESP32|Type
---|---|---
VCC|3v3|VCC
GND|GND|GND
DIN|G23|DIN/MOSI
CLK|G18|CLK/SCK
CS|G26|CS
DC|G25|DC
RST|G33|Reset

## Serial console
The eyes can be controlled via the serial console.

- mood
  - neutral
  - happy
  - angry
  - annoyed
  - scared
  - sleep
- look
  - left
  - right
  - center

Example:
```
mood angry
look left
```

## Images
<img src="https://user-images.githubusercontent.com/5315463/169717310-a40d3c82-a0b7-4cc4-8c9e-1a2052281bb6.jpg" alt="mood neutral; look center" data-canonical-src="https://user-images.githubusercontent.com/5315463/169717310-a40d3c82-a0b7-4cc4-8c9e-1a2052281bb6.jpg" width="200" /> <img src="https://user-images.githubusercontent.com/5315463/169717313-96819c65-1275-4dce-a514-4ca167dded51.jpg" alt="mood angry; look left" data-canonical-src="https://user-images.githubusercontent.com/5315463/169717313-96819c65-1275-4dce-a514-4ca167dded51.jpg" width="200" />
