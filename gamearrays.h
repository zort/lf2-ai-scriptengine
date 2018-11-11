#ifndef _GAMEARRAYS_H_
    #define _GAMEARRAYS_H_

#include "sgame.h"
#include <angelscript.h>

class CharArray {
	public:
		char opIndex(unsigned int x);
};

class CharArrayArray {
	public:
		template <int size>
		CharArray *opIndex(unsigned int x);
};

class IntArray {
	public:
		int opIndex(unsigned int x);
};

class BoolArray {
	public:
		bool opIndex(unsigned int x);
};

class ItrArray {
	public:
		sItr *opIndex(unsigned int x);
};

class BdyArray {
	public:
		sBdy *opIndex(unsigned int x);
};

class DataFileArray {
	public:
		sDataFile *opIndex(unsigned int x);
};

class ObjectArray {
	public:
		sObject *opIndex(unsigned int x);
};

class FrameArray {
	public:
		sFrame *opIndex(unsigned int x);
};

class BackgroundArray {
	public:
		sBackground *opIndex(unsigned int x);
};

class SpawnArray {
	public:
		sSpawn *opIndex(unsigned int x);
};

class PhaseArray {
	public:
		sPhase *opIndex(unsigned int x);
};

class StageArray {
	public:
		sStage *opIndex(unsigned int x);
};

void RegisterGameArrays(asIScriptEngine *ScriptEngine);

#endif // _GAMEARRAYS_H_