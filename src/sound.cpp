#include "sound.h"
#include <stdlib.h>

int Sound::init_count = 0;

void Sound::init()
{
	Sound::init_count++;
	if(Sound::init_count == 1)
	{
		FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);      // DirectSound
		FSOUND_SetDriver(0);                         // Sound Driver (default 0)
		FSOUND_SetMixer(FSOUND_MIXER_AUTODETECT);    // Mixer
		FSOUND_Init(44100, 32, 0);                   // 44.1 kHz and 32 channels
	}
}

void Sound::quit()
{
	Sound::init_count++;
	if(Sound::init_count == 0)
	{
		FSOUND_Close();
	}
}

Sound::Sound()
{
	channel = -1;
	son = NULL;
	Sound::init();
}

Sound::~Sound()
{
	Sound::quit();
}

void Sound::load(std::string file)
{
	son = FSOUND_Sample_Load(FSOUND_FREE, file.c_str(), FSOUND_NORMAL, 0, 0);
	if(son == NULL)
		exit(-1);
}

void Sound::setLoop(int loopstart, int loopend)
{
	if(loopend == -1)
		loopend = getLength();
	FSOUND_Sample_SetLoopPoints(son, loopstart, loopend);
}

void Sound::play(int loops)
{
	if(loops == -1)
		FSOUND_Sample_SetMode(son, FSOUND_LOOP_NORMAL);
	else
	{
		FSOUND_Sample_SetMode(son, FSOUND_LOOP_OFF);
		FSOUND_Sample_SetMaxPlaybacks(son, loops);
	}
	stop();
	channel = FSOUND_PlaySound(FSOUND_FREE, son);
}

void Sound::stop()
{
	if(channel == -1)
		return;
	FSOUND_StopSound(channel);
}

unsigned int Sound::getLength()
{
	return FSOUND_Sample_GetLength(son);
}


