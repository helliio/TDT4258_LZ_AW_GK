#ifndef test_extern_sound_c
#define test_extern_sound_c

#include <stdint.h>
#include "efm32gg.h"
#include "defines.h"

int sound = 0;
int sound_value = 0;

void lisa_gikk_til_skolen(void)
{	// TPlay a simple song
	play_tone(C);
    play_tone(D);
    play_tone(E);
    play_tone(F);
    play_tone(G);
    play_tone(G);
    play_tone(A);
    play_tone(A);
    play_tone(A);
    play_tone(A);
    play_tone(G);
    play_tone(F);
    play_tone(F);
    play_tone(F);
    play_tone(F);
    play_tone(E);
    play_tone(E);
    play_tone(D);
    play_tone(D);
    play_tone(D);
    play_tone(D);
    play_tone(C);
}

void play_tone(int tone)
{	
	// Play a tone based on the enum type tone

	set_tone(tone);

	trigger_sound = true;
	
	while(trigger_sound);
}

void play_piano_sound()
{
    sound = piano[piano_position];
    piano_position++;

    *DAC0_CH0DATA = sound;
    *DAC0_CH1DATA = sound;


    if (piano_position >= lenght_of_piano)
    {
        trigger_sound = false;
        piano_position = 0;
    }
}

void mute(void)
{
	*DAC0_CH0DATA = 0;
    *DAC0_CH1DATA = 0;
}

void set_tone(int tone)
{
    setupTimer((base_sample_period * tone) / 10000);
}

#endif