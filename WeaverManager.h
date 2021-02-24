#ifndef WEAVERMANAGER_INCLUDED
#define WEAVERMANAGER_INCLUDED

# include "WeaverUtils.h"

# define OUTPUT_BUFFER_SIZE 1024
# define NOTHING 0
# define SINE 1
# define HALFSINE 2
# define SQUARE 3
# define SAW 4
# define TRIANGLE 5

# define TABLE_SIZE 32768
# define CH_TABLE_SIZE 16384
# define PI 3.14159265
unsigned short table[32768] = {0};

// 0: Ch; 1: Ch1; 2: Ch2; 3:Ch1Wave; 4:Ch1Freq; 5:Ch1Ampl; 6:Ch2Wave; 7:Ch2Freq; 8:Ch2Ampl
const int MAX_SELECTIONS_IN_MENU[9] ={2,4,4,3,3,3,3,3,3};

# define FREQ_SEQ_MAX 12
const int OMEGA_SEQ[FREQ_SEQ_MAX] = {1, 2, 5, 10, 20, 24, 49, 73, 98, 195, 488, 733};
# define DIV_MIN 4
# define DIV_MAX 63
const int DIV_SEQ[FREQ_SEQ_MAX] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};

# define WAVE_SEQ_MAX 6
const int WAVE_SEQ[WAVE_SEQ_MAX] = {NOTHING, SINE, HALFSINE, SQUARE, SAW, TRIANGLE};

# define AMPL_SEQ_MAX 6
# define AMP_MAX 3.3
const float AMPL_SEQ[AMPL_SEQ_MAX] = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0};

class WeaverManager
{
	public:
	WeaverUI * artist;
	int menuSelectState;
	int buttonSelectState;
	
	int buttonSelectPrevious;
	int buttonSelectRead;
	int buttonConfirmPrevious;
	int buttonConfirmRead;
	
	int waveIndex[2];
	int divIndex;
	int omegaIndex[2];
	int amplIndex[2];
	
	int div;
	int wave[2];
	float omega[2];
	int freq[2];
	float ampl[2];
	float DCOffset[2];
	
	WeaverManager(WeaverUI* p);
	void Init();
	void DoHouseKeeping();
	void ButtonInputHandler();
	void ButtonConfirmHandler(int menu, int selected);
	void CommandInputHandler();
	
	void PreviousWave(int ch);
	void NextWave(int ch);
	void DecreaseFreq(int ch);
	void IncreaseFreq(int ch);
	void DecreaseAmpl(int ch);
	void IncreaseAmpl(int ch);
	
	void SetWave(int ch, int w);
	void SetOmega(int ch, float o);
	void SetAmpl(int ch, float a);
	void SetThreshold(int ch, float th);
	void SetDC(int ch, float dc);
	
	float threshold[2];
	void UpdateTable(int ch, int waveform, float omega, float amp);
	void UpdateDiv(int div);
	void ShowHelper();
	void ShowKnownBugs();
};

void WeaverManager::DoHouseKeeping()
{
	ButtonInputHandler();
	CommandInputHandler();
	return;
}

void WeaverManager::ShowKnownBugs()
{
	Serial.println("Known Bugs:");
	Serial.println("- Yes. We have noticed these bugs, but we have not fixed them, and we will not fix them.");
	Serial.println("- Output frequency can only be a multiple of 26Hz.");
	Serial.println("  This is not a bug, but rather it is a feature.");
	Serial.println("- SineWeaver randomly reboots for unknown reasons.");
	Serial.println("  We will not fix it because the bug lies deep inside the CPU.");
	Serial.println("- Negative DC offsets causes problems.");
	Serial.println("  We will not fix it because it is restricted by the DACs, whose output voltage is 0-3.3V.");
	Serial.println("- Output voltage is lower than expected.");
	Serial.println("  We will not fix it because it is again restricted by the DACs. Ask those who made this dirt-cheap chip to fix this.");
	
	return;
}

void WeaverManager::ShowHelper()
{
	Serial.println("-===========Two-Channel Multipurpose Function Generator===========-");
	Serial.println("-===========                Sine Weaver                ===========-");
	Serial.println("-===========               EE235 Group22               ===========-");
	Serial.println("Helper File:");
	Serial.println("- Command format: 'Weaver + cmd + param1 + param2'.");
	Serial.println("- Commands are case-insensitive.");
	Serial.println("- List of available commands:");
	Serial.println("	- SetOmega + [Channel] + [Value]: Set the angular frequency.");
	Serial.println("	- SetAmpl + [Channel] + [Value]: Set the amplitude.");
	Serial.println("	- SetWave +[Channel] + [Value]: Set waveforms.");
	Serial.println("	  0:No Output; 1:Sine; 2:Half-Sine; 3:Square; 4:Saw; 5:Triangle");
	Serial.println("	- SetDiv + [Value]: Set clock divisor of DAC output pin.");
	Serial.println("	  Combine this with SetOmega to control output frequency.");
	Serial.println("	- SetDC + [Channel] + [Value]: Set DC Offset.");
	Serial.println("	- SetThreshold + [Channel] + [Value]: Set duty ratio");
	Serial.println("	  Threshold only affects square waves.");
	
	return;
}

void WeaverManager::CommandInputHandler()
{
	String cmdBlock1;
	String cmdBlock2;
	float cmdParam;
	int cmdCh;
	
	if(Serial.available())
	{
		// Parse first commmand string
		cmdBlock1 = Serial.readStringUntil(' ');
		cmdBlock1.toLowerCase();
		if(cmdBlock1 != "weaver" || !Serial.available())
		{
			Serial.println("WeaverConsoleError: Invalid or Incomplete Command.");
			Serial.println("Use <Weaver Help> for help.");
			Serial.println();
			return;
		}
		
		// Parse second command string
		cmdBlock2 = Serial.readStringUntil(' ');
		cmdBlock2.toLowerCase();
		
		if(cmdBlock2 == "help")
		{
			ShowHelper();
			return;
		}
		if(cmdBlock2 == "stupid")
		{
			ShowKnownBugs();
			return;
		}
		
		// Parse channel parameters
		if(!Serial.available())
		{
			Serial.println("WeaverConsoleError: Incomplete Command.");
			Serial.println();
			return;
		}
		cmdCh = Serial.parseInt();
		if(cmdCh != 0 && cmdCh != 1 && cmdBlock2 != "setdiv")
		{
			Serial.println("WeaverValueError: Channel should be either 0 or 1.");
			Serial.println();
			return;
		}
		
		// Parse command parameters
		if(!Serial.available() && cmdBlock2 != "setdiv")
		{
			Serial.println("WeaverConsoleError: Incomplete Command.");
			Serial.println();
			return;
		}
		cmdParam = Serial.parseFloat();
		
		// Execute commands
		if(cmdBlock2 == "setomega")
		{
			if(cmdParam <= 0.0)
			{
				Serial.println("WeaverValueError: Omega should be positive.");
				Serial.println();
				return;
			}
			SetOmega(cmdCh, cmdParam);
			return;
		}
		else
		if(cmdBlock2 == "setampl")
		{
			if(cmdParam < 0.0 || cmdParam > 3.3)
			{
				Serial.println("WeaverValueError: Amplitude should be between 0.0 and 3.3.");
				Serial.println();
				return;
			}
			SetAmpl(cmdCh, cmdParam);
			return;
		}
		else
		if(cmdBlock2 == "setwave")
		{
			if(cmdParam < 0.0 || cmdParam > 5.0)
			{
				Serial.println("WeaverValueError: Wave Selection Parameter should be an interger between 0 and 5.");
				Serial.println();
				return;
			}
			SetWave(cmdCh, int(cmdParam));
			return;
		}
		else
		if(cmdBlock2 == "setdiv")
		{
			if(cmdCh < 2.0 || cmdCh > 63.0)
			{
				Serial.println("WeaverValueError: ClockDiv should be between 2 and 63.");
				Serial.println();
				return;
			}
			Serial.println("WeaverWarning: Manually setting ClockDiv may lead to stupid behaviors.");
			Serial.println("			   You should know what you are doing when setting this.");
			Serial.println();
			UpdateDiv(int(cmdCh));
			return;
		}
		else
		if(cmdBlock2 == "setthreshold")
		{
			if(cmdParam < 0.0 || cmdParam > 100.0)
			{
				Serial.println("WeaverValueError: Threshold must be between 0.0 and 100.0.");
				Serial.println();
				return;
			}
			SetThreshold(cmdCh, cmdParam);
		}
		else
		if(cmdBlock2 == "setdc")
		{
			if(cmdParam < 0.0 || cmdParam > 3.3)
			{
				Serial.println("WeaverWarning: DC Offset out of bound. This may lead to errors.");
			}
			SetDC(cmdCh, cmdParam);
		}
		else
		{
			Serial.println("WeaverConsoleError: Unknown command.");
			Serial.println("Use <Weaver Help> for help.");
			Serial.println();
			return;
		}
		// Execute Command
		

	}
	
	return;
}

WeaverManager::WeaverManager(WeaverUI* p)
{
	menuSelectState = 0;
	buttonSelectState = 0;
	
	buttonSelectPrevious = HIGH;
	buttonSelectRead = HIGH;
	buttonConfirmPrevious = HIGH;
	buttonConfirmRead = HIGH;
	
	divIndex = 3;
	div = 16;
	waveIndex[0] = 1;
	waveIndex[1] = 0;
	wave[0] = WAVE_SEQ[waveIndex[0]];
	wave[1] = WAVE_SEQ[waveIndex[1]];
	omegaIndex[0] = 3;
	omegaIndex[1] = 0;
	amplIndex[0] = amplIndex[1] = AMPL_SEQ_MAX-1;
	ampl[0] = ampl[1] = AMPL_SEQ[amplIndex[0]];
	omega[0] = OMEGA_SEQ[omegaIndex[0]];
	omega[1] = OMEGA_SEQ[omegaIndex[1]];
	freq[0] = 25 * omega[0] * (63/div);
	freq[1] = 25 * omega[0] * (63/div);

	threshold[0] = threshold[1] = 50.0;
	DCOffset[0] = DCOffset[1] = 0.0;
	
	artist = p;
}

void WeaverManager::Init()
{		
	UpdateDiv(div);
	artist->chUI[0].UI[0].DrawParameter("SINE");
	artist->chUI[1].UI[0].DrawParameter("DC");
	artist->chUI[1].UI[2].DrawParameter(ampl[1]);
	artist->chUI[0].UI[2].DrawParameter(ampl[0]);
	artist->chUI[0].UI[1].DrawParameter(freq[0]);
	artist->chUI[1].UI[1].DrawParameter(freq[1]);
	SetWave(0, wave[0]);
	SetWave(1, wave[1]);
	
	return;
}

// {NOTHING, SINE, HALFSINE, SQUARE, SAW, TRIANGLE};
void WeaverManager::UpdateTable(int ch, int waveform, float omega, float amp)
{
	float frequency = 16384 / omega;
	switch(waveform)
	{
	case NOTHING:
		for(int i = 0; i < CH_TABLE_SIZE; ++i)
			table[2*i + ch] = (unsigned short)(0 + (DCOffset[ch] / 3.3 * 255)) << 8;
	break;
	
	case SINE:
		for(int i = 0; i < CH_TABLE_SIZE; ++i)
			table[2*i + ch] = (unsigned short)(((sin(2 * PI * omega * i / 16384.0)+1) * (amp / 3.3) + DCOffset[ch]/3.3 * 2) * 127) << 8;
	break;
	
	case HALFSINE:
		for(int i = 0; i < CH_TABLE_SIZE; ++i)
			table[2*i + ch] = (unsigned short)((abs(sin(PI * omega * i / 16384.0)) * (amp / 3.3) + DCOffset[ch]/3.3) * 255) << 8;
	break;
	
	case SQUARE:
		for(int i = 0; i < CH_TABLE_SIZE; ++i)
		{
			float val = (i % int(frequency)) / frequency;
			table[2*i + ch] = (unsigned short)(((val < (threshold[ch] / 100.0) ? 1 : 0) * (amp / 3.3) + DCOffset[ch]/3.3) * 255) << 8;
		}
	break;
	
	case SAW:
		for(int i = 0; i < CH_TABLE_SIZE; ++i)
			table[2*i + ch] = (unsigned short)(((i % int(frequency)) / frequency * (amp / 3.3) + DCOffset[ch]/3.3) * 255) << 8;
	break;
	
	case TRIANGLE:
		for(int i = 0; i < CH_TABLE_SIZE; ++i)
			table[2*i + ch] = (unsigned short)((abs(((i % int(frequency) - frequency/2) / frequency)) * (amp / 3.3) + DCOffset[ch]/3.3/2) * 510) << 8;
	break;
	}
	
	size_t bytesWritten;
	i2s_write(I2S_NUM_0, table, sizeof(table), &bytesWritten, portMAX_DELAY);
	i2s_write(I2S_NUM_0, table, sizeof(table), &bytesWritten, portMAX_DELAY);
	Serial.println("Output has been updated.");
	
	return;
}

void WeaverManager::UpdateDiv(int d)
{
	div = d;
	SET_PERI_REG_BITS(I2S_CLKM_CONF_REG(0), I2S_CLKM_DIV_A_V, 1, I2S_CLKM_DIV_A_S);
	SET_PERI_REG_BITS(I2S_CLKM_CONF_REG(0), I2S_CLKM_DIV_B_V, 1, I2S_CLKM_DIV_B_S);
	SET_PERI_REG_BITS(I2S_CLKM_CONF_REG(0), I2S_CLKM_DIV_NUM_V, 2, I2S_CLKM_DIV_NUM_S); 
	SET_PERI_REG_BITS(I2S_SAMPLE_RATE_CONF_REG(0), I2S_TX_BCK_DIV_NUM_V, div, I2S_TX_BCK_DIV_NUM_S);
	
	Serial.println("Clockrate Divisor Updated.");
	Serial.println();
	for(int i = 0; i < 2; ++i)
	{
		freq[i] = 26 * omega[i] * (63.0/div);
		artist->chUI[i].UI[1].DrawParameter(freq[i]);
	}
	
	return;
};

void WeaverManager::SetWave(int ch, int w)
{
	String waveform;
	switch(w)
	{
		case NOTHING:
		waveform = "DC";
		break;
		
		case SINE:
		waveform = "SINE";
		break;
		
		case HALFSINE:
		waveform = "ABS_SINE";
		break;
		
		case SQUARE:
		waveform = "SQUARE";
		break;
		
		case SAW:
		waveform = "SAW";
		break;
		
		case TRIANGLE:
		waveform = "TRIANGLE";
		break;
	}
	wave[ch] = w;
	UpdateTable(ch, wave[ch], omega[ch], ampl[ch]);
	artist->chUI[ch].UI[0].DrawParameter(waveform);
	Serial.println("Waveform Updated.");
	Serial.println();
	
	return;
}

void WeaverManager::SetAmpl(int ch, float a)
{
	ampl[ch] = a;
	UpdateTable(ch, wave[ch], omega[ch], ampl[ch]);
	artist->chUI[ch].UI[2].DrawParameter(a);
	Serial.println("Amplitude Updated.");
	Serial.println();
	
	return;
}

void WeaverManager::SetOmega(int ch, float o)
{
	omega[ch] = o;
	freq[ch] = 26.0 * omega[ch] * (63.0/div);
	UpdateTable(ch, wave[ch], omega[ch], ampl[ch]);
	Serial.println("Omega Updated.");
	Serial.println();
	artist->chUI[ch].UI[1].DrawParameter(freq[ch]);
	
	return;
}

void WeaverManager::SetThreshold(int ch, float th)
{
	threshold[ch] = th;
	UpdateTable(ch, wave[ch], omega[ch], ampl[ch]);
	Serial.println("Threshold Updated. Note that this only affects square waves.");
	
	return;
}

void WeaverManager::SetDC(int ch, float dc)
{
	DCOffset[ch] = dc;
	UpdateTable(ch, wave[ch], omega[ch], ampl[ch]);
	Serial.println("DC Offset Updated.");
	
	return;
}

void WeaverManager::PreviousWave(int ch)
{
	waveIndex[ch] = (waveIndex[ch]+(WAVE_SEQ_MAX-1)) % WAVE_SEQ_MAX;
	wave[ch] = WAVE_SEQ[waveIndex[ch]];
	SetWave(ch, wave[ch]);
	
	return;
}

void WeaverManager::NextWave(int ch)
{
	waveIndex[ch] = (waveIndex[ch]+1) % WAVE_SEQ_MAX;
	wave[ch] = WAVE_SEQ[waveIndex[ch]];
	SetWave(ch, wave[ch]);
	
	return;
}

void WeaverManager::DecreaseFreq(int ch)
{
	omegaIndex[ch] = (omegaIndex[ch]+(FREQ_SEQ_MAX-1)) % FREQ_SEQ_MAX;
	divIndex = omegaIndex[ch];
	omega[ch] = OMEGA_SEQ[omegaIndex[ch]];
	div = DIV_SEQ[divIndex];
	
	UpdateDiv(div);
	SetOmega(ch, omega[ch]);
	
	return;
}

void WeaverManager::IncreaseFreq(int ch)
{
	omegaIndex[ch] = (omegaIndex[ch]+1) % FREQ_SEQ_MAX;
	divIndex = omegaIndex[ch];
	omega[ch] = OMEGA_SEQ[omegaIndex[ch]];
	div = DIV_SEQ[divIndex];
	
	UpdateDiv(div);
	SetOmega(ch, omega[ch]);
}

void WeaverManager::DecreaseAmpl(int ch)
{
	amplIndex[ch] = (amplIndex[ch]+(AMPL_SEQ_MAX-1)) % AMPL_SEQ_MAX;
	ampl[ch] = AMPL_SEQ[amplIndex[ch]];
	SetAmpl(ch, ampl[ch]);
	
	return;
}

void WeaverManager::IncreaseAmpl(int ch)
{
	amplIndex[ch] = (amplIndex[ch]+1) % AMPL_SEQ_MAX;
	ampl[ch] = AMPL_SEQ[amplIndex[ch]];
	SetAmpl(ch, ampl[ch]);
	
	return;
}

void WeaverManager::ButtonInputHandler()
{
	bool changed = false;
	buttonSelectRead = digitalRead(BUTTON_SELECT);
	if(buttonSelectPrevious != buttonSelectRead && buttonSelectRead == LOW) // SELECT button has been pressed
	{
		buttonSelectState = (buttonSelectState+1) % MAX_SELECTIONS_IN_MENU[menuSelectState]; // Update Button Selection State
		changed = true;
	}
	buttonSelectPrevious = buttonSelectRead; // Update SELECT button status
	
	buttonConfirmRead = digitalRead(BUTTON_CONFIRM);
	if(buttonConfirmPrevious != buttonConfirmRead && buttonConfirmRead == LOW) // CONFIRM button has been pressed
	{
		ButtonConfirmHandler(menuSelectState, buttonSelectState); // Handle CONFIRM Operations
		changed = true;
	}
	buttonConfirmPrevious = buttonConfirmRead; // Update CONFIRM button status

	if(changed)
		artist->UpdateUI(menuSelectState, buttonSelectState);
	
	return;
}

// 0: Ch; 1: Ch1; 2: Ch2; 3:Ch1Wave; 4:Ch1Freq; 5:Ch1Ampl; 6:Ch2Wave; 7:Ch2Freq; 8:Ch2Ampl
void WeaverManager::ButtonConfirmHandler(int menu, int selected)
{
	bool isReset = true;
	switch(menu)
	{
	case 0: // Now at Ch1/Ch2 selection state
		menuSelectState = selected + 1;
		break;
		
	case 1: // Now at WAVE/FREQ/AMPL selection state
	case 2:
		if(selected == 3) // <Back
			menuSelectState = 0;
		else if(menu == 1)// WAVE/FREQ/AMPL
			menuSelectState = selected + 3;
		else if(menu == 2)
			menuSelectState = selected + 6;
		break;
	case 3: // Ch1 Wave
		switch(selected)
		{
		case 0: // Decr
			PreviousWave(0);
			break;
		case 1: // Incr
			NextWave(0);
			isReset = false;
			break;
		case 2: // <BACK
			menuSelectState = 1;
			break;
		}
		break;
	case 4:
		switch(selected)
		{
		case 0: // Decr
			DecreaseFreq(0);
			break;
		case 1: // Incr
			IncreaseFreq(0);
			isReset = false;
			break;
		case 2: // <BACK
			menuSelectState = 1;
			break;
		}
		break;
	case 5:
		switch(selected)
		{
		case 0: // Decr
			DecreaseAmpl(0);
			break;
		case 1: // Incr
			IncreaseAmpl(0);
			isReset = false;
			break;
		case 2: // <BACK
			menuSelectState = 1;
			break;
		}
		break;
	case 6:
		switch(selected)
		{
		case 0: // Decr
			PreviousWave(1);
			break;
		case 1: // Incr
			NextWave(1);
			isReset = false;
			break;
		case 2: // <BACK
			menuSelectState = 2;
			break;
		}
		break;
	case 7:
		switch(selected)
		{
		case 0: // Decr
			DecreaseFreq(1);
			break;
		case 1: // Incr
			IncreaseFreq(1);
			isReset = false;
			break;
		case 2: // <BACK
			menuSelectState = 2;
			break;
		}
		break;
	case 8:
		switch(selected)
		{
		case 0: // Decr
			DecreaseAmpl(1);
			break;
		case 1: // Incr
			IncreaseAmpl(1);
			isReset = false;
			break;
		case 2: // <BACK
			menuSelectState = 2;
			break;
		}
		break;
	}
	if(isReset)
		buttonSelectState = 0;
}

#endif
