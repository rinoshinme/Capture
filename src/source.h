#ifndef _SOURCE_H
#define _SOURCE_H

// sound object
#include "source\simple_wav.h"
#include "source\wav_header.h"

// signal generators
#include "source\generator\SineGenerator.h"
#include "source\generator\SquareGenerator.h"
#include "source\generator\WhiteNoiseGenerator.h"

// window functions
#include "source\window\RectangularWindow.h"
#include "source\window\GaussianWindow.h"
#include "source\window\HannWindow.h"
#include "source\window\HammingWindow.h"

// misc utility functions
#include "source\functions.h"

#endif
