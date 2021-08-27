#pragma once

#define MEMEMPTY(dest)		ZeroMemory(dest,sizeof(dest))
#define MEMCOPY(dest,src)	CopyMemory(dest,src,sizeof(dest))