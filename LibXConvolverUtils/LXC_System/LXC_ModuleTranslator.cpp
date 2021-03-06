/*	
 *		Copyright (C) 2014 Achim Turan, Achim.Turan@o2online.de
 *		https://github.com/AchimTuran/LibXConvolver
 *
 *	This file is part of LibXConvolver
 *
 *	LibXConvolver is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	LibXConvolver is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with LibXConvolver.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>

#include "LXC_ModuleTranslator.h"
using namespace std;

std::string LXC_optModuleToString(LXC_OPTIMIZATION_MODULE OptModule)
{
  string optString = "";
  switch(OptModule)
  {
    case LXC_OPT_NATIVE:
      optString = "LXC_Native";
    break;

    case LXC_OPT_SSE2:
      optString = "LXC_SSE2";
    break;

    case LXC_OPT_SSE3:
      optString = "LXC_SSE3";
    break;

    case LXC_OPT_AVX:
      optString = "LXC_AVX";
    break;

    case LXC_OPT_NEON:
      optString = "LXC_NEON";
    break;

    case LXC_OPT_CUDA:
      optString = "LXC_CUDA";
    break;

    case LXC_OPT_OPENCL:
      optString = "LXC_OpenCL";
    break;

    default:
      optString = "LXC_UNKNOWN";
    break;
  }

  return optString;
}

std::string LXC_fftModuleToString(LXC_FFT_MODULE fftModule)
{
  string fftString = "";
  switch(fftModule)
  {
    case LXC_fftModule_fftwf:
      fftString = "fftwf";
    break;

    case LXC_fftModule_KissFFT:
      fftString = "KissFFT";
    break;

    default:
      fftString = "UNKNOWN_fftModule";
    break;
  }

  return fftString;
}
