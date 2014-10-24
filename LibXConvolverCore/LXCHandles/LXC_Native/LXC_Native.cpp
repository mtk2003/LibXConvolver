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



#include "LXC_Native.h"
#include "LXC_Native_types.h"
#include "LXC_NativeBuffer.h"
#include "LXC_NativeRingBuffer.h"

#include "../../include/LXC_Core_types.h"
#include "../../include/common_types.h"
#include "LXC_Native_types.h"

#include "LXC_NativeBuffer.h"

LXC_ERROR_CODE LXC_get_NativeCallbacks(LXC_HANDLE *LXCHandle)
{
	if(!LXCHandle)
	{
		// ToDo: show some error message
		return LXC_ERR_INVALID_INPUT;
	}

	// get LXC callbacks
	LXCHandle->LXC_callbacks.LXC_CpxMul = LXC_NativeCpxMul;
	LXCHandle->LXC_callbacks.LXC_CpxAdd = LXC_NativeCpxAdd;
	LXCHandle->LXC_callbacks.LXC_FreqCombine2Ch = LXC_NativeFreqCombine2Ch;
	LXCHandle->LXC_callbacks.LXC_FreqSplit2Ch = LXC_NativeFreqSplit2Ch;

	// get buffer callbacks
	LXCHandle->LXCHandle.bufferCallbacks.LXC_Buffer_getPart = LXC_NativeBuffer_getPart;
	LXCHandle->LXCHandle.bufferCallbacks.LXC_Buffer_create = LXC_NativeBuffer_create;
	LXCHandle->LXCHandle.bufferCallbacks.LXC_Buffer_destroy = LXC_NativeBuffer_destroy;

	// get ringbuffer callbacks
	LXCHandle->LXCHandle.ringbufferCallbacks.LXC_Ringbuffer_getPart = LXC_NativeRingbuffer_getPart;
	LXCHandle->LXCHandle.ringbufferCallbacks.LXC_Ringbuffer_getNextPart = LXC_NativeRingbuffer_getNextPart;
	LXCHandle->LXCHandle.ringbufferCallbacks.LXC_Ringbuffer_create = LXC_NativeRingbuffer_create;
	LXCHandle->LXCHandle.ringbufferCallbacks.LXC_Ringbuffer_destroy = LXC_NativeRingbuffer_destroy;

	return LXC_NO_ERR;
}

LXC_ERROR_CODE LXC_NativeCpxMul(uint Size, void *X, void *H, void *Y)
{
	if(!X || !H || !Y)
	{
		return LXC_ERR_INVALID_INPUT;
	}

	LXC_cpxFloat *m_X = (LXC_cpxFloat*)X;
	LXC_cpxFloat *m_H = (LXC_cpxFloat*)H;
	LXC_cpxFloat *m_Y = (LXC_cpxFloat*)Y;
	for(uint ii=0; ii < Size; ii++)
	{
		m_Y[ii][0] = m_X[ii][0]*m_H[ii][0] - m_X[ii][1]*m_H[ii][1];
		m_Y[ii][1] = m_X[ii][1]*m_H[ii][0] + m_X[ii][0]*m_H[ii][1];
	}

	return LXC_NO_ERR;
}

LXC_ERROR_CODE LXC_NativeCpxAdd(LXC_BUFFER *ResultBuffer, char Scale)
{
	if(!ResultBuffer)
	{
		return LXC_ERR_INVALID_INPUT;
	}

	const uint partSize = ResultBuffer->maxFilterPartLength;
	const uint maxParts = ResultBuffer->maxFilterParts;

	LXC_cpxFloat *Z0 = (LXC_cpxFloat*)LXC_NativeBuffer_getPart(ResultBuffer, 0);
	for(uint part=1; part < maxParts; part++)
	{
		LXC_cpxFloat *Zi = (LXC_cpxFloat*)LXC_NativeBuffer_getPart(ResultBuffer, part);
		for(uint ii=0; ii < partSize; ii++)
		{
			Z0[ii][0] += Zi[ii][0];
			Z0[ii][1] += Zi[ii][1];
		}
	}

	if(Scale)
	{
		const float scaleFactor = 1.0f / ((float)partSize);
		for(uint ii=0; ii < partSize; ii++)
		{
			Z0[ii][0] *= scaleFactor;
			Z0[ii][1] *= scaleFactor;
		}
	}

	return LXC_NO_ERR;
}


LXC_ERROR_CODE LXC_NativeFreqCombine2Ch(uint Size, void *X, void *Y, void *Z)
{
	if(!Size || !X || !Y || !Z)
	{
		return LXC_ERR_INVALID_INPUT;
	}

	LXC_cpxFloat *m_X = (LXC_cpxFloat*)X;
	LXC_cpxFloat *m_Y = (LXC_cpxFloat*)Y;
	LXC_cpxFloat *m_Z = (LXC_cpxFloat*)Z;

	const float scaleFactor = 1.0f / ((float)Size);

	for(uint ii = 0; ii < Size; ii++)
	{
		m_Z[ii][0] = (m_X[ii][0] - m_Y[ii][1])*scaleFactor;
		m_Z[ii][1] = (m_X[ii][1] + m_Y[ii][0])*scaleFactor;
	}

	return LXC_NO_ERR;
}


LXC_ERROR_CODE LXC_NativeFreqSplit2Ch(uint Size, void *Z, void *X, void *Y)
{
	if(!Size || !Z || !X || !Y)
	{
		return LXC_ERR_INVALID_INPUT;
	}

	LXC_cpxFloat *m_X = (LXC_cpxFloat*)X;
	LXC_cpxFloat *m_Y = (LXC_cpxFloat*)Y;
	LXC_cpxFloat *m_Z = (LXC_cpxFloat*)Z;

	m_X[0][0] = m_Z[0][0];
	m_X[0][1] = 0.0f;

	m_Y[0][0] = m_Z[0][1];
	m_Y[0][1] = 0.0f;

	for(uint kk = 1; kk < Size; kk++)
	{
		const uint L_minus_K = Size - kk;
		m_X[kk][0] = 0.5f*(m_Z[kk][0] + m_Z[L_minus_K][0]);
		m_X[kk][1] = 0.5f*(m_Z[kk][1] - m_Z[L_minus_K][1]);

		m_Y[kk][0] = 0.5f*(m_Z[kk][1] + m_Z[L_minus_K][1]);
		m_Y[kk][1] = 0.5f*(m_Z[L_minus_K][0] - m_Z[kk][0]);
	}

	return LXC_NO_ERR;
}