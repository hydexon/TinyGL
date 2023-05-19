#pragma once
#ifndef _tgl_fixed_h_
#define _tgl_fixed_h_

#ifdef TGL_FIXED
#include "fix16.h"
typedef fix16_t scalar_t;
typedef fix16_t dscalar_t;
#else
typedef float scalar_t;
typedef double dscalar_t;
#endif


#endif /* _tgl_fixed_h_ */
