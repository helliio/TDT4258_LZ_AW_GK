#include <stdint.h>
#include <stdbool.h>

#ifndef test_extern_sound_h
#define test_extern_sound_h

	extern 		 int 		piano_position;
	extern 		 bool 		trigger_sound;
	extern 		 int 		base_sample_period;
	extern 		 int 		sample_period;	
	extern const int 		lenght_of_piano;
	extern const int const 	piano[];

	void lisa_gikk_til_skolen(void);
	void play_piano_sound(void);
	void mute(void);
	void set_tone(int tone);
	void sleep(void);

	void setupDAC(void);
	void setupNVIC(void);
	void setupGPIO(void);
	void setupTimer(uint16_t period);

	enum TONE
		{ C = 10000
	    , D = 8908
	    , E = 7937
	    , F = 7491
	    , G = 6673
	    , A = 5945
	    , B = 5296
	    , C2= 5000
		};

#endif