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



#include "LXC_CException.h"


LXC_CException::LXC_CException(string strError, string strFilename, string strFunction, int iLine, void *vPointer )
{
	str_errorModule = "";
	v_pointer = vPointer;

	str_error = strError;
	str_errorFilename = strFilename;
	str_errorFunction = strFunction;
	i_errorLine = iLine;
}

LXC_CException::LXC_CException( string strError, string strErrorModule, string strFilename, string strFunction, int iLine, void *vPointer )
{
	v_pointer = vPointer;

	str_error = strError;
	str_errorModule = strErrorModule;
	str_errorFilename = strFilename;
	str_errorFunction = strFunction;
	i_errorLine = iLine;
}

LXC_CException::~LXC_CException(void)
{
}
