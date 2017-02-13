#pragma once

#include "stdafx.h"
#include <Windows.h>


CString Unicode_URLDecode(CString strEncodedText)
{
	CString strResult;
	wchar_t ch0, ch1, ch2;
	wchar_t wch;
	TCHAR tch;
	int i = 0;
	while (i<strEncodedText.GetLength())
	{
		tch = strEncodedText.GetAt(i);
		if (tch != _T('%'))
		{
			// a character not encoded
			strResult += tch;
			i++;
		}
		else
		{
			// a character encoded !!
			ch0 = _tcstol(strEncodedText.Mid(i + 1, 2), NULL, 16);
			i += 3;
			if (ch0 < 0x80)
				// 1 byte for UTF-8
				// 0xxx xxxx
				wch = ch0;
			else
			{
				if (strEncodedText.GetAt(i) != _T('%')) // Error!
					continue;
				ch1 = _tcstol(strEncodedText.Mid(i + 1, 2), NULL, 16);
				i += 3;
				if (ch0 < 0xe0)
				{
					// 2 byte for UTF-8
					// 110x xxxx 10xx xxxx
					wch = ((ch0 & 0x1f) << 6)
						| (ch1 & 0x3f);
				}
				else
				{
					// 3 byte for UTF-8
					if (strEncodedText.GetAt(i) != _T('%')) // Error!
						continue;
					ch2 = _tcstol(strEncodedText.Mid(i + 1, 2), NULL, 16);
					i += 3;
					// 1110 xxxx 10xx xxxx 10xx xxxx
					wch = ((ch0 & 0x0f) << 12)
						| ((ch1 & 0x3f) << 6)
						| (ch2 & 0x3f);
				}
			}
			strResult += wch;
		}
	}
	return strResult;
}
