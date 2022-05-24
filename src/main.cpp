#include <Adafruit_GFX.h>
#include <Adafruit_SSD1327.h>

// Adafruit_SSD1327 display(SCREEN_WIDTH, SCREEN_HEIGHT, MOSI, CLK, DC, RESET, CS);
Adafruit_SSD1327 display(128, 128, 23, 18, 25, -1, 26);

#include "eyes.h"

int centerX = 16;
int mood = 1;
static int twitch, waiting, step;

// eyes struct
struct Eye
{
  int x, y, w, h, pos, offsetX, offsetY;
  uint16_t Color;
};

// define the eyes
Eye eyes[] = {
    {0, 8, 32, 32, 0, 0, 0, 0xFFFF},
    {0, 8, 32, 32, 0, 64, 0, 0xFFFF}};

// adjusts the size of the eyes when looking to the side
void adjustEyeSize()
{
  if (centerX < 6)
  {
    eyes[0].pos = 2;
    eyes[1].pos = 1;
  }
  else if (centerX < 26)
  {
    eyes[0].pos = 0;
    eyes[1].pos = 0;
  }
  else
  {
    eyes[0].pos = 1;
    eyes[1].pos = 2;
  }
}

// draws the eyes
void drawEyes()
{
  display.clearDisplay();
  display.drawBitmap(eyes[0].x, eyes[0].y, moods[mood][eyes[0].pos][0], eyes[0].w, eyes[0].h, eyes[0].Color);
  display.drawBitmap(eyes[1].x, eyes[1].y, moods[mood][eyes[1].pos][1], eyes[1].w, eyes[1].h, eyes[1].Color);
  display.display();
}

// make eyes blink
void blink()
{
  int oldMood = mood;
  mood = 0;
  drawEyes();

  delay(100);
  mood = oldMood;

  drawEyes();
}

// lets the eyes look around
void generateTwitch()
{
  if (random(0, 10) < 5)
    twitch--;
  else
    twitch++;

  if (twitch < -4)
    twitch = -3;
  else if (twitch > 4)
    twitch = 3;
}

// set new center for eyes
void newCenterX(int newX)
{
  centerX = newX;
  eyes[0].x = twitch + (newX > 16 ? (16 + 2 * (newX - 16)) : newX);
  eyes[1].x = 64 + twitch + (newX < 16 ? (-16 + (newX * 2)) : newX);

  adjustEyeSize();
}

// evaluate commands from the console
unsigned char readConsole(void)
{
  unsigned char ret = 0;

  if (Serial.available())
  {
    String incomingString = Serial.readString();
    incomingString.trim();

    if (incomingString.equals("look right"))
    {
      newCenterX(1);
      drawEyes();
      Serial.println("right success");
    }
    else if (incomingString.equals("look left"))
    {
      newCenterX(32);
      drawEyes();
      Serial.println("left success");
    }
    else if (incomingString.equals("look center"))
    {
      newCenterX(16);
      drawEyes();
      Serial.println("center success");
    }
    else if (incomingString.equals("mood neutral"))
    {
      mood = 1;
      drawEyes();
      Serial.println("mood neutral success");
    }
    else if (incomingString.equals("mood happy"))
    {
      mood = 2;
      drawEyes();
      Serial.println("mood happy success");
    }
    else if (incomingString.equals("mood angry"))
    {
      mood = 3;
      drawEyes();
      Serial.println("mood angry success");
    }
    else if (incomingString.equals("mood annoyed"))
    {
      mood = 4;
      drawEyes();
      Serial.println("mood annoyed success");
    }
    else if (incomingString.equals("mood scared"))
    {
      mood = 5;
      drawEyes();
      Serial.println("mood scared success");
    }
    else if (incomingString.equals("mood sleep"))
    {
      mood = 0;
      drawEyes();
      Serial.println("mood sleep success");
    }
    else
    {
      Serial.printf("unknown command %s\r\n", incomingString);
    }
  }

  return (ret);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting");

  if (!display.begin(0x3C))
  {
    Serial.println("Unable to initialize OLED");
    while (1)
      yield();
  }

  // Clear the display
  display.clearDisplay();
  display.display();
}

void loop()
{
  if (waiting > 0)
  {
    waiting--;
    delay(1);
  }
  else
  {
    newCenterX(centerX);

    switch (step)
    {
    case 0:
      drawEyes();
      waiting = random(250, 1000);
      step = (random(0, 7) == 6) ? 1 : 2;
      break;
    case 1:
      blink();
      waiting = 0;
      step = 0;
      break;
    case 2:
      generateTwitch();
      waiting = 0;
      step = 0;
      break;
    }
  }

  readConsole();
}