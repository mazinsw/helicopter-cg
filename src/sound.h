#ifndef _SOUND_H_
#define _SOUND_H_
#include <fmod/fmod.h>
#include <string>

class Sound
{
private:
	int channel;
	FSOUND_SAMPLE * son;
	static int init_count;
	static void init();
	static void quit();
public:
	Sound();
	~Sound();
	void load(std::string file);
	void setLoop(int loopstart, int loopend = - 1);
	void play(int loops = -1);
	void stop();
	unsigned int getLength();
};

#endif /* _SOUND_H_ */