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
    display.setFont(FONT);
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
    display.setFont(FONT);
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
    String tempText = "Temperature: " + String(temp,1) + " degC";   // round to 1 decimal
    String humidText = "Humidity: " + String(humid,1) + "%";        // round to 1 decimal
    String pressText = "Pressure: " + String(press,1) + " hPa";     // round to 1 decimal

    String iaqText;
    String co2Text;
    String iaqStatusText;

    if (iaqStatus == 0) {
        iaqText = "IAQ: -";
        co2Text = "CO2: -" ;
        iaqStatusText = "Sensor starting...";    
    } else if (iaqStatus == 1 || iaqStatus == 2) {
        iaqText = "IAQ: " + String(iaq,0);                          // round to 1 decimal
        co2Text = "CO2: " + String(co2,0) + " ppm";                 // round to 1 decimal
        iaqStatusText = "IAQ calibrating... (" + String(iaqStatus) + ")";
    } else if (iaqStatus == 3) {
        iaqText = "IAQ: " + String(iaq,0);
        co2Text = "CO2: " + String(co2,0) + " ppm";
        switch (int(iaq)) {
            case 0 ... 50:
                iaqStatusText = "IAQ: Excellent :D";
                break;
            case 51 ... 100:
                iaqStatusText = "IAQ: Good :)";
                break;
            case 101 ... 150:
                iaqStatusText = "IAQ: Light pollution";
                break;
            case 151 ... 200:
                iaqStatusText = "IAQ: Moderate pollution - vent!";
                break;
            case 201 ... 250:
                iaqStatusText = "IAQ: Heavy pollution :(";
                break;
            case 251 ... 350:
                iaqStatusText = "IAQ: Severe pollution >:(";
                break;
            case 351 ... 500:
                iaqStatusText = "IAQ: Extreme pollution - rip";
                break;
        }
    }
    
    display.setRotation(1);    
    display.setFont(FONT);
    display.setTextColor(GxEPD_BLACK);  
    display.setPartialWindow(box_x, box_y, DISP_PIXEL_WIDTH, DISP_PIXEL_HEIGHT);

    display.firstPage();
    do
    {
        display.fillRect(0,0, 250, 122, GxEPD_WHITE);
        // temp
        display.setCursor(box_x, box_h);
        display.print(tempText);
        // humidity
        display.setCursor(box_x, box_h*2);
        display.print(humidText);
        // pressure
        display.setCursor(box_x, box_h*3);
        display.print(pressText);
        // iaq
        display.setCursor(box_x, box_h*4);
        display.print(iaqText);
        // co2
        display.setCursor(box_x, box_h*5);
        display.print(co2Text);
        // sensor status
        display.setCursor(box_x, box_h*6);
        display.print(iaqStatusText);
    }
    while (display.nextPage());
    display.hibernate();
}
