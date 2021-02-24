#ifndef WEAVERUI_INCLUDED
#define WEAVERUI_INCLUDED
#include "WeaverUIConfig.h"

class WeaverSubSubUI
{
	public:
	String title;
	SubSubUIConfig config;
	WeaverSubSubUI(String title, SubSubUIConfig config);
	void DrawTitle();
	void DrawButtons();
	void DrawParameter(int parameter);
	void DrawParameter(float parameter);
	void DrawParameter(String parameter);
	void Render();
	void UpdateUI(int menu, int selected);
	void ReverseTitleColor();
	void ReverseDecrColor();
	void ReverseIncrColor();
};

class WeaverSubUI
{
  public:
  WeaverSubSubUI UI[3];
  
  chButtonConfig config;
  String chText;
  char chNum;
  
  WeaverSubUI(String chT, char chN, chButtonConfig config, SubSubUIConfig waveCfg, SubSubUIConfig freqCfg, SubSubUIConfig amplCfg);

  void DrawButton();
  void Render();
  void UpdateUI(int menu, int selected);
  void ReverseChColor();
};

class WeaverUI
{
  public:
  WeaverSubUI chUI[2];
  UIConfig config;
  
  WeaverUI(UIConfig, chButtonConfig, chButtonConfig, SubSubUIConfig, SubSubUIConfig, SubSubUIConfig, SubSubUIConfig, SubSubUIConfig, SubSubUIConfig);
  void DrawButton();
  void DrawTitle();
  void DrawFrameWork();
  void Render();
  void UpdateUI(int menu, int selected);
  void ReverseBackColor();
};

// Ch1 SubUI: menu = 1, 3,4,5 mapped to 6,7,8
// Ch2 SubUI: menu = 2, 6,7,8
void WeaverSubSubUI::UpdateUI(int menu, int selected)
{
	if(menu==1 || menu==2) // Update WAVE/FREQ/AMPL
		ReverseTitleColor();
	else if(selected == 0)
		ReverseDecrColor();
	else if(selected == 1)
		ReverseIncrColor();
	
	return;
}

// Ch1 SubUI: menu = 0, 1, 3,4,5
// Ch2 SubUI: menu = 0, 2, 6,7,8

void WeaverSubUI::UpdateUI(int menu, int selected)
{
	if(menu == 0) // CH
		ReverseChColor();
	else if(menu == 1 || menu == 2)
		UI[selected].UpdateUI(menu, selected);
	else if(3 <= menu && menu <= 5)
		UI[menu-3].UpdateUI(menu+3, selected);
	else
		UI[menu-6].UpdateUI(menu, selected);

	return;
}

void WeaverUI::UpdateUI(int menu, int selected)
{
	Render();
	if(((menu==1 || menu==2) && selected==3) || ((menu>=3) && selected==2)) // <BACK
		ReverseBackColor();
		
	else if(menu==1 || menu==3 || menu==4 || menu==5 || (menu==0 && selected==0)) // Ch1 SubUI
		chUI[0].UpdateUI(menu, selected);
		
	else // Ch2 SubUI
		chUI[1].UpdateUI(menu, selected);
		
	return;
}

void WeaverSubSubUI::ReverseDecrColor()
{
	// Decrement Button
	tft.fillRect(config.dcrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.drawRect(config.dcrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_BLACK, TFT_WHITE);
	tft.setTextSize(config.buttonTextFontSize);
	tft.drawString("<", config.dcrTextX, config.buttonTextY);
	
	return;
}

void WeaverSubSubUI::ReverseIncrColor()
{
	// Increment Button
	tft.fillRect(config.icrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.drawRect(config.icrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_BLACK, TFT_WHITE);
	tft.setTextSize(config.buttonTextFontSize);
	tft.drawString(">", config.icrTextX, config.buttonTextY);
	
	return;
}

void WeaverSubSubUI::ReverseTitleColor()
{
	tft.fillRect(config.titleX, config.titleY, config.titleWidth, config.titleHeight, TFT_WHITE);
	tft.drawRect(config.titleX, config.titleY, config.titleWidth, config.titleHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_BLACK, TFT_WHITE);
	tft.setTextSize(config.titleFontSize);
	tft.drawString(title, config.titleXCenter, config.titleYCenter);
	
	return;
}

void WeaverSubUI::ReverseChColor()
{
	tft.fillRect(config.buttonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.drawRect(config.buttonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_BLACK, TFT_WHITE);
	int bias = tft.fontHeight(config.textFontSize)/2;
	tft.setTextSize(config.textFontSize);
	tft.drawString(chText, config.textX, config.textY - bias - 1);
	tft.drawString(String(chNum), config.textX, config.textY + bias + 1);
	
	return;
}

WeaverSubSubUI::WeaverSubSubUI(String t, SubSubUIConfig cfg)
{
	title = t;
	config = cfg;
}

void WeaverSubSubUI::DrawTitle()
{
	tft.fillRect(config.titleX, config.titleY, config.titleWidth, config.titleHeight, config.titleBGColor);
	tft.drawRect(config.titleX, config.titleY, config.titleWidth, config.titleHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(config.titleTextColor, config.titleBGColor);
	tft.setTextSize(config.titleFontSize);
	tft.drawString(title, config.titleXCenter, config.titleYCenter);
	
	return;
}

void WeaverSubSubUI::DrawButtons()
{
	// Increment Button
	tft.fillRect(config.icrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, config.icrButtonColor);
	tft.drawRect(config.icrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(config.icrTextColor, config.icrButtonColor);
	tft.setTextSize(config.buttonTextFontSize);
	tft.drawString(">", config.icrTextX, config.buttonTextY);
	
	// Decrement Button
	tft.fillRect(config.dcrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, config.dcrButtonColor);
	tft.drawRect(config.dcrButtonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(config.dcrTextColor, config.dcrButtonColor);
	tft.setTextSize(config.buttonTextFontSize);
	tft.drawString("<", config.dcrTextX, config.buttonTextY);
	
	return;
}

void WeaverSubSubUI::DrawParameter(int parameter)
{
	tft.fillRect(config.paramX, config.paramY, config.paramWidth, config.paramHeight, TFT_BLACK);
	tft.drawRect(config.paramX, config.paramY, config.paramWidth, config.paramHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawNumber(parameter, config.paramTextX, config.buttonTextY, config.paramFontSize);
	
	return;
}

void WeaverSubSubUI::DrawParameter(float parameter)
{
	tft.fillRect(config.paramX, config.paramY, config.paramWidth, config.paramHeight, TFT_BLACK);
	tft.drawRect(config.paramX, config.paramY, config.paramWidth, config.paramHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawFloat(parameter, 2, config.paramTextX, config.buttonTextY, config.paramFontSize);
	
	return;
}

void WeaverSubSubUI::DrawParameter(String parameter)
{
	tft.fillRect(config.paramX, config.paramY, config.paramWidth, config.paramHeight, TFT_BLACK);
	tft.drawRect(config.paramX, config.paramY, config.paramWidth, config.paramHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(config.paramFontSize);
	tft.drawString(parameter, config.paramTextX, config.buttonTextY);
	
	return;
}

void WeaverSubSubUI::Render()
{
	tft.drawRect(config.frameX, config.frameY, config.frameWidth, config.frameHeight, TFT_WHITE);
	DrawTitle();
	DrawButtons();
};

WeaverSubUI::WeaverSubUI(String chT, char chN, chButtonConfig cfg, SubSubUIConfig waveCfg, SubSubUIConfig freqCfg, SubSubUIConfig amplCfg): UI{WeaverSubSubUI("WAVE", waveCfg), WeaverSubSubUI("FREQ", freqCfg), WeaverSubSubUI("AMPL", amplCfg)}
{
	chText = chT;
	chNum = chN;
	config = cfg;
}

void WeaverSubUI::DrawButton()
{
	tft.fillRect(config.buttonX, config.buttonY, config.buttonWidth, config.buttonHeight, config.buttonColor);
	tft.drawRect(config.buttonX, config.buttonY, config.buttonWidth, config.buttonHeight, TFT_WHITE);
	tft.setTextDatum(MC_DATUM);
	tft.setTextColor(config.textColor, config.buttonColor);
	int bias = tft.fontHeight(config.textFontSize)/2;
	tft.setTextSize(config.textFontSize);
	tft.drawString(chText, config.textX, config.textY - bias - 1);
	tft.drawString(String(chNum), config.textX, config.textY + bias + 1);
	
	return;
}

void WeaverSubUI::Render()
{
	DrawButton();
	UI[0].Render();
	UI[1].Render();
	UI[2].Render();
	
	return;
}

WeaverUI::WeaverUI(UIConfig cfg, chButtonConfig ch1Cfg, chButtonConfig ch2Cfg, 
	SubSubUIConfig ch1WaveCfg, SubSubUIConfig ch1FreqCfg, SubSubUIConfig ch1AmplCfg, 
		SubSubUIConfig ch2WaveCfg, SubSubUIConfig ch2FreqCfg, SubSubUIConfig ch2AmplCfg): chUI{WeaverSubUI("CH", '1', ch1Cfg, ch1WaveCfg, ch1FreqCfg, ch1AmplCfg), WeaverSubUI("CH", '2', ch2Cfg, ch2WaveCfg, ch2FreqCfg, ch2AmplCfg)}
{
	config = cfg;
}

void WeaverUI::DrawButton()
{
	tft.setTextDatum(MR_DATUM);
	tft.setTextColor(config.textColor, config.buttonColor);
	tft.setTextSize(config.textFontSize);
	tft.drawString("<BACK", config.textX, config.textY);
	
	return;
}

void WeaverUI::DrawTitle()
{
	tft.setTextDatum(ML_DATUM);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(config.titleFontSize);
	tft.drawString("SINEWEAVER", config.titleX, config.titleY);
	
	return;
}

void WeaverUI::DrawFrameWork()
{
	tft.drawLine(0,9,239,9, TFT_WHITE);
	
	return;
}

void WeaverUI::Render()
{
	DrawButton();
	DrawTitle();
	DrawFrameWork();
	chUI[0].Render();
	chUI[1].Render();
	
	return;
}

void WeaverUI::ReverseBackColor()
{
	tft.setTextDatum(MR_DATUM);
	tft.setTextColor(config.buttonColor, config.textColor);
	tft.setTextSize(config.textFontSize);
	tft.drawString("<BACK", config.textX, config.textY);
	
	return;
}

#endif
