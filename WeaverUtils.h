#ifndef WEAVERCOMMON_INCLUDED
#define WEAVERCOMMON_INCLUDED

# define I2S_SAMPLE_RATE 100000
# define BUTTON_SELECT 35
# define BUTTON_CONFIRM 0
# define DAC1 25
# define DAC2 26

void WeaverInit()
{
	i2s_config_t i2s_config = {
	.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
	.sample_rate = I2S_SAMPLE_RATE,
	.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
	.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
	.communication_format = I2S_COMM_FORMAT_I2S_MSB,
	.intr_alloc_flags = ESP_INTR_FLAG_LEVEL2,
	.dma_buf_count = 16,
	.dma_buf_len = 1024,
	};
	i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
	i2s_set_pin(I2S_NUM_0, NULL);
	
	return;
}

void goingFancy()
{
	tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(BC_DATUM);
    tft.fillScreen(TFT_BLACK);
    tft.drawString("Sine Weaver", 120, 50, 4);
    tft.drawString("EE235 Grp 22", 120, 75, 2);
    tft.drawRect(68, 90, 102, 17, TFT_WHITE); // From 68 to 169;
    tft.drawRect(69, 91, 100, 15, TFT_BLACK); // From 69 to 168;
    
	for(int j = 0; j <= 100; ++j)
    {
			tft.drawLine(69+j, 91, 69+j, 105, TFT_WHITE);
			// Pretend to be doing some difficult initializations
			delay(12);
    }
	delay(500);
}

#endif
