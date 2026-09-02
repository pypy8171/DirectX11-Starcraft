#pragma once

#define _XM_NO_INTRINSICS_

#include <d3d11.h>
//#include <d3d11_1.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <list>
#include <vector>
#include <map>

using std::list;
using std::vector;
using std::map;

#include <array>
#include "SimpleMath.h"

#include <string>
#include <typeinfo>

using namespace std;
using namespace DirectX;

#include "define.h"
#include "struct.h"
#include "func.h"

#include "extern.h"
#include "well512.h"
