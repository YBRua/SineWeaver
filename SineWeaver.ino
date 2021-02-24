# include <TFT_eSPI.h>
# include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

# include <driver/i2s.h>
# include <driver/dac.h>
# include "WeaverUIConfig.h"
# include "WeaverUI.h"
# include "WeaverManager.h"
# include "WeaverUtils.h"

WeaverUI weaverArtist(overallCfg, ch1ButtonCfg, ch2ButtonCfg, ch1WaveCfg, ch1FreqCfg, ch1AmplCfg, ch2WaveCfg, ch2FreqCfg, ch2AmplCfg);
WeaverManager weaverManager(&weaverArtist);

void setup() {
	Serial.begin(115200);
	tft.init();
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);
	pinMode(BUTTON_CONFIRM, INPUT_PULLUP);
	pinMode(BUTTON_SELECT, INPUT_PULLUP);
	pinMode(DAC1, OUTPUT);
	pinMode(DAC2, OUTPUT);
	goingFancy();
	tft.fillScreen(TFT_BLACK);

	weaverArtist.Render();
	dac_output_enable(DAC_CHANNEL_2);

	weaverArtist.UpdateUI(0,0);
	WeaverInit();
	weaverManager.Init();
	weaverManager.ShowHelper();

}

void loop() {
    weaverManager.DoHouseKeeping();
	delay(25);
}
