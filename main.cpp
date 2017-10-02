/*
 * A Real-time Multi-Threaded Graphics Library
 * for STM32F429 DISCO based on mbedOS.
 * author: Mostafa Ayesh
 * email: mostafaayesh@outlook.com
*/

#include "mbed.h"
#include "TS_DISCO_F429ZI.h"
#include "LCD_DISCO_F429ZI.h"
#include "rtos.h"
#include "View.cpp"

LCD_DISCO_F429ZI lcd;
TS_DISCO_F429ZI ts;
DigitalIn UB(USER_BUTTON);
Serial pc(USBTX,USBRX);
View* Hello = new View(lcd);
DigitalOut r1(PA_3);
PwmOut r2(PA_5);
DigitalOut r3(PB_1);
AnalogIn ain(PA_0);

/* Thread reading touch input*/
void touch_thread()
{
  TS_StateTypeDef TS_State;
  uint16_t x, y;
  uint8_t text[30];
  uint8_t status;
  uint8_t detected;
  while(1)
  {
    ts.GetState(&TS_State);
    if (TS_State.TouchDetected)
    {
      if (detected == 0)
      {
        detected = 1;

      }
      x = TS_State.X;
      y = TS_State.Y;
      sprintf((char*)text, "x=%d y=%d    ", x, y);
      // lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);
      // lcd.DrawPixel(x,y,LCD_COLOR_WHITE);
      Hello->Touch(x, y);
    }
    Thread::wait(20);
  }
}

/* Creates grid layout */
void grid(int rows, int columns)
{
  uint16_t x, y;
  int counter = 1;
  uint8_t text;
  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < columns; col++)
    {
      // lcd.FillRect(x,y,20,20);
      x = ((col * lcd.GetXSize() / columns) + ((col + 1) * lcd.GetXSize() / columns)) /2;
      y = ((row * lcd.GetYSize() / rows) + ((row + 1) * lcd.GetYSize() / rows)) /2;
      lcd.SetTextColor(0xFF000000);
      lcd.FillCircle(x, y, 37);
      lcd.SetTextColor(0xBF00FFFF);
      lcd.FillCircle(x, y, 35);
      sprintf((char*)text, "%d", counter);
      lcd.SetTextColor(0xFF000000);
      lcd.SetBackColor(0xBF00FFFF);
      lcd.DisplayChar(x-6, y-6, 48);
      counter++;
    }
  }
}

int main()
{
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t detected;


    pc.baud(9600);
    BSP_LCD_SetFont(&Font20);

    lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN", CENTER_MODE);
    lcd.DisplayStringAt(0, LINE(6), (uint8_t *)"DEMO", CENTER_MODE);
    wait(1);

    status = ts.Init(lcd.GetXSize(), lcd.GetYSize()); // Initializes touch

    if (status != TS_OK)
    {
      lcd.Clear(LCD_COLOR_RED);
      lcd.SetBackColor(LCD_COLOR_RED);
      lcd.SetTextColor(LCD_COLOR_WHITE);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(6), (uint8_t *)"INIT FAIL", CENTER_MODE);
    }
    else
    {
      lcd.Clear(LCD_COLOR_GREEN);
      lcd.SetBackColor(LCD_COLOR_GREEN);
      lcd.SetTextColor(LCD_COLOR_WHITE);
      lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN", CENTER_MODE);
      lcd.DisplayStringAt(0, LINE(6), (uint8_t *)"INIT OK", CENTER_MODE);
    }

    wait(1);
    detected = 0;

    lcd.Clear(LCD_COLOR_WHITE);
    lcd.SetBackColor(LCD_COLOR_WHITE);
    lcd.SetTextColor(LCD_COLOR_BLACK);
    Thread thread(touch_thread);
    // grid(4,3);
    Hello->Draw();

    while(1)
    {
      Thread::wait(OS_WAIT_FOREVER);
    }
}
