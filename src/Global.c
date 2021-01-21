/*
This file contains all global variables
*/







/* 
General purpose function for ticking a value.
flag: 0 false, 1 true
a = reset holder once it reaches tick cap?
b = subtract cap from holder once cap is reached?
*/
int Tick(int *tick_holder, int tick_num, int tick_cap, char cap_reset, int holder_reset_val){

	*tick_holder += tick_num; 
	
	if(*tick_holder >= tick_cap && *tick_holder > 0)
	{
		if(cap_reset == 'Y')
		{
		*tick_holder = holder_reset_val;
		return 1;
		}
		else
		{
		*tick_holder -= tick_cap;	
		return 1;
		}
	}
	else if(*tick_holder <= -tick_cap && *tick_holder < 0)
	{
		if(cap_reset == 'Y')
		{
		*tick_holder = holder_reset_val;
		return -1;
		}
		else
		{
		*tick_holder -= tick_cap;	
		return -1;
		}		
	}
	else 
	{
	return 0;	
	}
}



/*
This function controls the main loop by capping its frame rate while optimizing time for intensive loading.
*/
void FrameControl() 
{
	static unsigned int previous_time;
	static unsigned int current_time;
	static unsigned int difference_time;
	static unsigned int compensation_time;	//NOTE: SDL ticks even while delaying. Must be compensated for.	
	static unsigned int two_thirds_counter; //Helps more accurately emulate 60 fps. Should be revised so any fps can be used.
	
	unsigned int frame_delay = (1000.f/TARGET_FPS); //The rounded amount of milliseconds between each frame. 16 at 60 fps.
	
	if(two_thirds_counter > 2)
	{
	frame_delay++;
	two_thirds_counter -= 3;	
	}
	
	current_time = SDL_GetTicks();
	
	difference_time = (current_time - previous_time - compensation_time);
		
	
	if(difference_time < frame_delay)
	{
	compensation_time = frame_delay - difference_time;	
	SDL_Delay(compensation_time);	
	}
	else
	{
	compensation_time = 0;	
	}
	
	previous_time = current_time;
	two_thirds_counter += 2;
}