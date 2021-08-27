#pragma once

#define D3D_DEBUG_INFO
#define DIRECTINPUT_VERSION 0x0800

//Windows API
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"Imagehlp.lib")
#pragma comment(lib,"imm32.lib")
#pragma comment(lib,"shell32.lib")
#pragma comment(lib,"rpcrt4.lib")
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"Vfw32.lib")
//Network
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"wsock32.lib")

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")

//Directx
#pragma comment(lib,"d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif
#pragma comment(lib,"dsound.lib")

//STD
#include <vector>
#include <list>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>

//Windows_Header_Files
#include <windows.h>
#include <windowsx.h>
#include <Shlwapi.h>
#include <Tlhelp32.h>

//Socket
#include <Wininet.h>

#include <memory>
#include <stack>
#include <time.h>
//#include <Strsafe.h>
#include <stdio.h>
#include <math.h>
#include <regex>

#include <d3d9.h>
#include <d3dx9.h>
#include <d3d9types.h>
#include <dsound.h>

#include <sstream>
#include <fstream>

#include <cctype>
#include <functional>
#include <queue>
#include <Imagehlp.h>
#include <basetsd.h>
#include <rpc.h>
#include <assert.h>

#include "globals.h"

using namespace std;