#ifndef _INCLUDE_ALL_H
#define _INCLUDE_ALL_H

// include files for testing

// source
#include "source.h"

// filter
#include "filter\FirFilter.h"
#include "filter\IirFilter.h"
#include "filter\auxiliary\Delay.h"
#include "filter\auxiliary\Allpass.h"
#include "filter\auxiliary\NestedAllpass.h"
#include "filter\auxiliary\GardnerReverb.h"

// transform
#include "transform\TransformTypes.h"
#include "transform\FFTBase.h"
#include "transform\OouraFFT.h"
#include "transform\DFT.h"
#include "transform\DCT.h"
// FFT object should always be generated using factory method
#include "transform\FFTFactory.h"
#include "transform\mfcc\MelFilter.h"
#include "transform\mfcc\MelFilterBank.h"
#include "transform\mfcc\MFCC.h"

// voila
#include "voila\SoundEffect.h"

#endif
