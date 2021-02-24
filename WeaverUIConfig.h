#ifndef WEAVERUICFG_INCLUDED
#define WEAVERUICFG_INCLUDED

struct SubSubUIConfig
{
	int frameX;
	int frameY;
	int frameWidth;
	int frameHeight;
	
	int titleX;
	int titleY;
	int titleWidth;
	int titleHeight;
	
	int titleXCenter;
	int titleYCenter;
	int titleTextColor;
	int titleBGColor;
	int titleFontSize;
	
	int dcrButtonX;
	int icrButtonX;
	int buttonY;
	int icrButtonColor;
	int dcrButtonColor;
	int buttonWidth;
	int buttonHeight;
	
	int dcrTextX;
	int icrTextX;
	int buttonTextY;
	int buttonTextFontSize;
	
	int paramX;
	int paramY;
	int paramWidth;
	int paramHeight;
	int paramTextX;
	int paramFontSize;
	
	int icrTextColor;
	int icrBGColor;
	int dcrTextColor;
	int dcrBGColor;
};

struct chButtonConfig
{
	int buttonX;
	int buttonY;
	int buttonWidth;
	int buttonHeight;
	int buttonColor;
	
	int textX;
	int textY;
	int textColor;
	int textFontSize;
};

struct UIConfig
{
	int buttonX;
	int buttonY;
	int buttonWidth;
	int buttonHeight;
	int buttonColor;
	
	int textX;
	int textY;
	int textColor;
	int textFontSize;
	
	int titleX;
	int titleY;
	int titleFontSize;
};

SubSubUIConfig ch1WaveCfg=
{
	.frameX = 25,
	.frameY = 10,
	.frameWidth = 45,
	.frameHeight = 20,
	
	.titleX = 25,
	.titleY = 10,
	.titleWidth = 45,
	.titleHeight = 20,
	
	.titleXCenter = 47,
	.titleYCenter = 20,
	.titleTextColor = TFT_WHITE,
	.titleBGColor = TFT_BLACK,
	.titleFontSize = 1,
	
	.dcrButtonX = 70,
	.icrButtonX = 225,
	.buttonY = 10,
	.icrButtonColor = TFT_BLACK,
	.dcrButtonColor = TFT_BLACK,
	.buttonWidth = 15,
	.buttonHeight = 20,
	
	.dcrTextX = 77,
	.icrTextX = 232,
	.buttonTextY = 20,
	.buttonTextFontSize = 1,
	
	.paramX = 85,
	.paramY = 10,
	.paramWidth = 140,
	.paramHeight = 20,
	.paramTextX = 155,
	.paramFontSize = 1,
	
	.icrTextColor = TFT_WHITE,
	.icrBGColor = TFT_BLACK,
	.dcrTextColor = TFT_WHITE,
	.dcrBGColor = TFT_BLACK
};

SubSubUIConfig ch2WaveCfg=
{
	.frameX = 25,
	.frameY = 73,
	.frameWidth = 45,
	.frameHeight = 20,
	
	.titleX = 25,
	.titleY = 73,
	.titleWidth = 45,
	.titleHeight = 20,
	
	.titleXCenter = 47,
	.titleYCenter = 83,
	.titleTextColor = TFT_WHITE,
	.titleBGColor = TFT_BLACK,
	.titleFontSize = 1,
	
	.dcrButtonX = 70,
	.icrButtonX = 225,
	.buttonY = 73,
	.icrButtonColor = TFT_BLACK,
	.dcrButtonColor = TFT_BLACK,
	.buttonWidth = 15,
	.buttonHeight = 20,
	
	.dcrTextX = 77,
	.icrTextX = 232,
	.buttonTextY = 83,
	.buttonTextFontSize = 1,
	
	.paramX = 85,
	.paramY = 73,
	.paramWidth = 140,
	.paramHeight = 20,
	.paramTextX = 155,
	.paramFontSize = 1,
	
	.icrTextColor = TFT_WHITE,
	.icrBGColor = TFT_BLACK,
	.dcrTextColor = TFT_WHITE,
	.dcrBGColor = TFT_BLACK
};

SubSubUIConfig ch1FreqCfg=
{
	.frameX = 25,
	.frameY = 31,
	.frameWidth = 45,
	.frameHeight = 20,
	
	.titleX = 25,
	.titleY = 31,
	.titleWidth = 45,
	.titleHeight = 20,
	
	.titleXCenter = 47,
	.titleYCenter = 41,
	.titleTextColor = TFT_WHITE,
	.titleBGColor = TFT_BLACK,
	.titleFontSize = 1,
	
	.dcrButtonX = 70,
	.icrButtonX = 225,
	.buttonY = 31,
	.icrButtonColor = TFT_BLACK,
	.dcrButtonColor = TFT_BLACK,
	.buttonWidth = 15,
	.buttonHeight = 20,
	
	.dcrTextX = 77,
	.icrTextX = 232,
	.buttonTextY = 41,
	.buttonTextFontSize = 1,
	
	.paramX = 85,
	.paramY = 31,
	.paramWidth = 140,
	.paramHeight = 20,
	.paramTextX = 155,
	.paramFontSize = 1,
	
	.icrTextColor = TFT_WHITE,
	.icrBGColor = TFT_BLACK,
	.dcrTextColor = TFT_WHITE,
	.dcrBGColor = TFT_BLACK
};

SubSubUIConfig ch2FreqCfg=
{
	.frameX = 25,
	.frameY = 94,
	.frameWidth = 45,
	.frameHeight = 20,
	
	.titleX = 25,
	.titleY = 94,
	.titleWidth = 45,
	.titleHeight = 20,
	
	.titleXCenter = 47,
	.titleYCenter = 104,
	.titleTextColor = TFT_WHITE,
	.titleBGColor = TFT_BLACK,
	.titleFontSize = 1,
	
	.dcrButtonX = 70,
	.icrButtonX = 225,
	.buttonY = 94,
	.icrButtonColor = TFT_BLACK,
	.dcrButtonColor = TFT_BLACK,
	.buttonWidth = 15,
	.buttonHeight = 20,
	
	.dcrTextX = 77,
	.icrTextX = 232,
	.buttonTextY = 104,
	.buttonTextFontSize = 1,
	
	.paramX = 85,
	.paramY = 94,
	.paramWidth = 140,
	.paramHeight = 20,
	.paramTextX = 155,
	.paramFontSize = 1,
	
	.icrTextColor = TFT_WHITE,
	.icrBGColor = TFT_BLACK,
	.dcrTextColor = TFT_WHITE,
	.dcrBGColor = TFT_BLACK
};

SubSubUIConfig ch1AmplCfg=
{
	.frameX = 25,
	.frameY = 52,
	.frameWidth = 45,
	.frameHeight = 20,
	
	.titleX = 25,
	.titleY = 52,
	.titleWidth = 45,
	.titleHeight = 20,
	
	.titleXCenter = 47,
	.titleYCenter = 62,
	.titleTextColor = TFT_WHITE,
	.titleBGColor = TFT_BLACK,
	.titleFontSize = 1,
	
	.dcrButtonX = 70,
	.icrButtonX = 225,
	.buttonY = 52,
	.icrButtonColor = TFT_BLACK,
	.dcrButtonColor = TFT_BLACK,
	.buttonWidth = 15,
	.buttonHeight = 20,
	
	.dcrTextX = 77,
	.icrTextX = 232,
	.buttonTextY = 62,
	.buttonTextFontSize = 1,
	
	.paramX = 85,
	.paramY = 52,
	.paramWidth = 140,
	.paramHeight = 20,
	.paramTextX = 155,
	.paramFontSize = 1,
	
	.icrTextColor = TFT_WHITE,
	.icrBGColor = TFT_BLACK,
	.dcrTextColor = TFT_WHITE,
	.dcrBGColor = TFT_BLACK
};

SubSubUIConfig ch2AmplCfg=
{
	.frameX = 25,
	.frameY = 115,
	.frameWidth = 45,
	.frameHeight = 20,
	
	.titleX = 25,
	.titleY = 115,
	.titleWidth = 45,
	.titleHeight = 20,
	
	.titleXCenter = 47,
	.titleYCenter = 125,
	.titleTextColor = TFT_WHITE,
	.titleBGColor = TFT_BLACK,
	.titleFontSize = 1,
	
	.dcrButtonX = 70,
	.icrButtonX = 225,
	.buttonY = 115,
	.icrButtonColor = TFT_BLACK,
	.dcrButtonColor = TFT_BLACK,
	.buttonWidth = 15,
	.buttonHeight = 20,
	
	.dcrTextX = 77,
	.icrTextX = 232,
	.buttonTextY = 125,
	.buttonTextFontSize = 1,
	
	.paramX = 85,
	.paramY = 115,
	.paramWidth = 140,
	.paramHeight = 20,
	.paramTextX = 155,
	.paramFontSize = 1,
	
	.icrTextColor = TFT_WHITE,
	.icrBGColor = TFT_BLACK,
	.dcrTextColor = TFT_WHITE,
	.dcrBGColor = TFT_BLACK
};

chButtonConfig ch1ButtonCfg=
{
	.buttonX = 0,
	.buttonY = 10,
	.buttonWidth = 25,
	.buttonHeight = 62,
	.buttonColor = TFT_BLACK,
	
	.textX = 12,
	.textY = 40,
	.textColor = TFT_WHITE,
	.textFontSize = 1
};

chButtonConfig ch2ButtonCfg=
{
	.buttonX = 0,
	.buttonY = 73,
	.buttonWidth = 25,
	.buttonHeight = 62,
	.buttonColor = TFT_BLACK,
	
	.textX = 12,
	.textY = 103,
	.textColor = TFT_WHITE,
	.textFontSize = 1
};

UIConfig overallCfg=
{
	.buttonX = 210,
	.buttonY = 1,
	.buttonWidth = 29,
	.buttonHeight = 7,
	.buttonColor = TFT_BLACK,
	
	.textX = 239,
	.textY = 4,
	.textColor = TFT_WHITE,
	.textFontSize = 1,
	
	.titleX = 0,
	.titleY = 4,
	.titleFontSize = 1
};

#endif