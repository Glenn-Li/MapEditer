#include "stdafx.h"
#include "comlib.h"

CString nTos(int n)
{
	static CString str = _T("");
	if (n < 10)
	{
		str = (char)(n % 10 + '0');
		return str;
	}
	else
	{
		str = nTos(n / 10) + (char)(n % 10 + '0');
		return str;
	}
}