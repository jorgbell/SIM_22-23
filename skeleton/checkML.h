#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC_
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW_ new ( _NORMAL_BLOCK , FILE , LINE )
#define new DBG_NEW_
#endif
#endif