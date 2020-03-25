/***************************************************************/
//LED Strip driver with adjustable brightness knob and
//configurable color switches and speed
//Hardware: LED Strip Driver, some LED Strip, Open-Smart Rotary Angle Sensor
//Board: Ardunio
/***************************************************************/

#include <RichUNOKitCKnob.h>
#include <RGBdriver.h>


//pins definitions for the driver        
#define DIO 2 //DIO pin on arduino
#define CLK 3 //CLK pin on arduino
#define KNOB_PIN A0 //SIG pin of Rotary Angle Sensor module

#define NUM_COLORS 3 //Number of colors we define for the LED Strip
//#define CYCLE_TIME (30*60) // Time for an entire cycle in seconds
#define CYCLE_TIME float(30*60) // Time for an entire cycle in seconds
#define COLOR_CHANGE_STEPS 5000 //Number of steps for a single transition between colors
#define DELAY_TIME CYCLE_TIME/(NUM_COLORS*COLOR_CHANGE_STEPS)*1000
#define MAX_BRIGHTNESS 1 //Maximum brightness allowed to set (between 0 and 1)
#define OFF_ANGLE 20 //Angle below which we want to be in an off-state
#define MAX_ANGLE 280 //Maximum angle of the Rotary Angle Sensor

Knob knob(KNOB_PIN); //Initialize the Rotary Angle Sensor
RGBdriver Driver(CLK,DIO); //Initialize the RGBDriver for our LED Strip

// Defines a struct for Colors (int red, green, blue between 0 and 255)
struct Color {
  int red;
  int green;
  int blue;
};

// Defines the colors the LED Strip should show
struct Color colors[NUM_COLORS] = {
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255}
};

// Initialize all utility variables used later
float brightness;
Color color1;
Color color2;
Color mixedColor;

void setup()
{ 
  //No setup needed
}  

void loop()  
{
  for (int color_ind = 0; color_ind < NUM_COLORS; color_ind++) {
    //Iterates through all colors in colors
    
    //Determine the previous color in colors    
    color1 = colors[(color_ind - 1 + NUM_COLORS) % NUM_COLORS];

    //Determine the color to fade-to in colors
    color2 = colors[color_ind];
    for (float color_step = COLOR_CHANGE_STEPS; color_step > 0; color_step--) {
      //Fades from color1 to color2 in COLOR_CHANGE_STEPS steps
      brightness = getBrightness();
      mixedColor = mixColors(color1, color2, color_step/COLOR_CHANGE_STEPS);
      setColor(mixedColor, brightness);
      delay(DELAY_TIME);
    }
  }  
}

float getBrightness() {
  float angle = knob.getAngle();
  float brightness; //Must be a float to return a non-int value in division
  if (angle <= OFF_ANGLE) {
    // For values below OFF_ANGLE the LED Strip should be off
    brightness = 0;
  } else {
    // Values between OFF_ANGLE and MAX_ANGLE are mapped from 0 to MAX_BRIGHTNESS
    brightness = (angle-OFF_ANGLE)/(MAX_ANGLE-OFF_ANGLE) * MAX_BRIGHTNESS;
  }
  return brightness;
}

void setColor(Color color, float brightness) {
  //Sets a color, using a brightness value between 0 and 1
  Driver.begin();
  Driver.SetColor(int(brightness*color.red), int(brightness*color.green), int(brightness*color.blue));
  Driver.end();
}

Color mixColors(Color color1, Color color2, float ratio) {
  //Linearly mixes two colors
  Color mixedColor = {
    ratio * color1.red + (1-ratio) * color2.red,
    ratio * color1.green + (1-ratio) * color2.green,
    ratio * color1.blue + (1-ratio) * color2.blue
  };
  return mixedColor;
}
