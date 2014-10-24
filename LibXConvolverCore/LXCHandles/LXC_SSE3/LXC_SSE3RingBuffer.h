#pragma once

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



#include "../../include/common_types.h"
#include "../../include/LXC_Core_types.h"

void* LXC_SSE3Ringbuffer_getPart(LXC_RINGBUFFER *Ringbuffer, uint Element);
void* LXC_SSE3Ringbuffer_getNextPart(LXC_RINGBUFFER *Ringbuffer);
LXC_ERROR_CODE LXC_SSE3Ringbuffer_create(LXC_RINGBUFFER *Ringbuffer);
LXC_ERROR_CODE LXC_SSE3Ringbuffer_destroy(LXC_RINGBUFFER *Ringbuffer);