#include <SPI.h>
#include <Ethernet.h>

#define LGFX_USE_V1
//#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI      _bus_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = SPI2_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;
      cfg.spi_3wire  = false;
      cfg.use_lock   = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      
      cfg.pin_sclk = 12; 
      cfg.pin_mosi = 11; 
      cfg.pin_miso = 13; 
      cfg.pin_dc   = 46; 
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }
    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs           = 45; 
      cfg.pin_rst          = 47; 
      cfg.pin_busy         = -1;
      cfg.panel_width      = 240;
      cfg.panel_height     = 320;
      cfg.offset_x         = 0;
      cfg.offset_y         = 0;
      cfg.offset_rotation  = 0;
      cfg.dummy_read_pixel = 8;
      cfg.dummy_read_bits  = 1;
      cfg.readable         = true;
      cfg.invert           = true; 
      cfg.rgb_order        = false;
      cfg.dlen_16bit       = false;
      cfg.bus_shared       = true; 
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance);
  }
};

LGFX tft; 

int counter = 0;

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  delay(2000); 
  
  Serial.println("\n--- NORVI XN STARTING ---");

  // Initialize Display
  tft.init();
  tft.setRotation(0); 
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2); 
  
  // Draw Static Header on TFT
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(20, 20);
  tft.println("NORVI XN MAIN");
  tft.drawFastHLine(0, 50, 240, TFT_WHITE);
}

void loop() {
  // 1. Print to Serial Monitor
  Serial.print("Hello Serial! Counter: ");
  Serial.println(counter);

  // 2. Print to TFT Display
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(20, 80);
  tft.print("Hello Display!");
  
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(20, 120);
  tft.print("Count: ");
  // Adding spaces after the counter ensures old digits are overwritten
  tft.print(counter); 
  tft.print("    "); 
  
  counter++;
  delay(1000);
}