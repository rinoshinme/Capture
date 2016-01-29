#ifndef _SOUND_EFFECT_H
#define _SOUND_EFFECT_H

#include "../source.h"

namespace Capture
{
	/*
	 * Vocal removing by substracting one channel from the other 
	 * and divide by 2. (phase cancellation)
	 * actually the acapella track should be substracted, but in reality, well...
	 */
	SimpleSound VocalRemoving(SimpleSound channelLeft, SimpleSound channelRight);

	/*
	 * Mixing two sounds with equal length
	 * add them sample-by-sample and clipping
	 */
	SimpleSound Mix(SimpleSound sound1, SimpleSound sound2);
}

#endif
