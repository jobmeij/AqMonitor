#include "epdisplay.hpp"

EpDisplay::EpDisplay() : display(GxEPD2_213_BN(PIN_EPD_CS, PIN_EPD_DC, PIN_EPD_RES, PIN_EPD_BUSY)) {

}

bool EpDisplay::init()
{
    Serial.println("Initializing EPD...");
    display.init(115200,true,50,false);

    printTextDoubleRow("Initializing", "Please wait...");

    Serial.println("EPD initialized.");
    printTextDoubleRow("Done", ":D");
    clearFullDisplay();
    return true;
}


void EpDisplay::printTextDoubleRow(String topText, String botText)
{
    display.setRotation(1);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    int16_t tbx, tby; 
    uint16_t tbw, tbh;
    display.getTextBounds(topText.c_str(), 0, 0, &tbx, &tby, &tbw, &tbh);
    // center the bounding box by transposition of the origin:
    uint16_t x = ((display.width() - tbw) / 2) - tbx;
    uint16_t y = ((display.height() - tbh) / 2) - tby;
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(x, y-tbh);
        display.print(topText);
        display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
        display.getTextBounds(botText, 0, 0, &tbx, &tby, &tbw, &tbh);
        x = ((display.width() - tbw) / 2) - tbx;
        display.setCursor(x, y+tbh);
        display.print(botText);
    }
    while (display.nextPage());

    display.hibernate();
}

void EpDisplay::clearFullDisplay()
{
    display.setRotation(1);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    int16_t tbx, tby; 
    uint16_t tbw, tbh;  
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
    }
    while (display.nextPage());

    display.hibernate();
}


void EpDisplay::updateData(float temp, float humid, float press, float iaq, float co2, uint8_t iaqStatus)
{
    String tempText = "Temperature: " + String(temp,1) + " deg";      // round to 1 decimal
    String humidText = "Humidity: " + String(humid,1) + "%";        // round to 1 decimal
    String pressText = "Pressure: " + String(press,1) + " hPa";      // round to 1 decimal
    String iaqText = "IAQ: " + String(iaq,0);                       // round to 1 decimal
    String co2Text = "CO2: " + String(co2,0) + " ppm";               // round to 1 decimal
    String iaqStatusText = "IAQ calibrating...";
    if (iaqStatus == 3) {
        String iaqStatusText = "IAQ calibrated :D";
    } 
    
    display.setRotation(1);
    uint16_t cursor_y = box_y + box_h - 6;
    //if (display.epd2.WIDTH < 104) cursor_y = box_y + 6;    
    //uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
    display.setFont(&FreeMonoBold9pt7b);
    //if (display.epd2.WIDTH < 104) display.setFont(0);
    display.setTextColor(GxEPD_BLACK);  
    display.setPartialWindow(0, 0, 250, 122);

    display.firstPage();
    do
    {
        display.fillRect(0,0, 250, 122, GxEPD_WHITE);
        // temp
        display.setCursor(box_x, cursor_y);
        display.print(tempText);
        // humidity
        display.setCursor(box_x, cursor_y*2);
        display.print(humidText);
        // pressure
        display.setCursor(box_x, cursor_y*3);
        display.print(pressText);
        // iaq
        display.setCursor(box_x, cursor_y*4);
        display.print(iaqText);
        // co2
        display.setCursor(box_x, cursor_y*5);
        display.print(co2Text);
        // sensor status
        display.setCursor(box_x, cursor_y*6);
        display.print(iaqStatusText);
    }
    while (display.nextPage());
    display.hibernate();
}
