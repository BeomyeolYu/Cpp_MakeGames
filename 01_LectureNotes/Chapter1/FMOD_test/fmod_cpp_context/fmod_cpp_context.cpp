//#include "fmod.h"  // c-context
#include "fmod.hpp"
#include <iostream>
#include <conio.h>

/*
	fmod api documentation
	https://www.fmod.com/resources/documentation-api
*/

using namespace std;

int main()
{
	cout << "FMOD cpp conext example" << endl;

	/* System은 하나를 선언하는 것이 일반적이지만,
	Sound와 Channel은 array를 이용하여 복합 음향 효과를 재생할 수 있다. */
	FMOD::System     *system(nullptr);
	FMOD::Sound      *sound(nullptr);
	FMOD::Channel    *channel(nullptr);

	FMOD_RESULT       result;  /* 정상 작동을 체크하는 flag. */
	unsigned int      version; /* version check */
	void             *extradriverdata(nullptr);

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return -1; /* debugging을 위한 flag들. */
	
	result = system->getVersion(&version);
	if (result != FMOD_OK) return -1;
	else printf("FMOD version %08x\n", version);

	/* 32: channel을 32개를 사용하겠다는 의미. */
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK) return -1;

	/* 배경음악과 같은 경우에는 FMOD_LOOP_NORMAL로 설정. */
	//result = system->createSound("singing.wav", FMOD_LOOP_NORMAL, 0, &sound);
	result = system->createSound("singing.wav", FMOD_LOOP_OFF, 0, &sound); // .mp3 files work!
	if (result != FMOD_OK) return -1;

	/* 하나의 channel에서 여러 개의 sound를 재생할 수도 있음. */
	result = system->playSound(sound, 0, false, &channel);
	if (result != FMOD_OK) return -1;

	while (true)
	{
		/* 정상 작동을 체크하는 flag. */
		result = system->update();
		if (result != FMOD_OK) return -1;

		/* 현재 재생 중인지 아닌지 check 하여 종료하는 if 문. */
		//if (channel)
		//{
		//	bool playing = false;
		//	result = channel->isPlaying(&playing); // 재생 중이라면 &playing = true
		//	if (!playing) break; // 재생이 끝나 &playing = false이 되면 break.
		//}

		/* FMOD_LOOP_NORMAL일 때 일시정지 기능. */
		cout << "Press 0 to pause, 1 to resume, and x to exit" << endl;
		
		int i = getch(); // i is ASCII code

		if (i == '0')
			channel->setPaused(true);
		else if (i == '1')
			channel->setPaused(false);
		else if (i == 'x')
			break;
	}

	system->release(); // == "result = system->release();"
}
