/*  DirectDraw Wrapper
 *  version 1.0, August 6th, 2010
 *
 *  Copyright (C) 2010 Jari Komppa
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 *
 * Jari Komppa http://iki.fi/sol/
 *
 *************************************
 *
 * Based on a zlib/libpng licensed source code found on the net,
 * http://www.mikoweb.eu/index.php?node=28
 * re-worked so much that there's fairly little left of the original.
 *
 *************************************
 * Modified by Doix - not the original wrapper
 * More modifications made by Someone else
 */

#include "stdafx.h"
#include <varargs.h>
#include "detours.h"
#include <sys/stat.h>
#include <sstream>
#include <windows.h>

#include "add_on\scriptmath\scriptmath.h"
#include "add_on\scriptmath\scriptmathcomplex.h"
#include "add_on\scriptmath3d\scriptmath3d.h"
#include "add_on\scriptarray\scriptarray.h"
#include "add_on\scriptbuilder\scriptbuilder.h"
#include "add_on\scriptstdstring\scriptstdstring.h"

#include "gameenums.h"
#include "gamearrays.h"

// global variables
#pragma data_seg (".ddraw_shared")
HINSTANCE           gl_hOriginalDll;
HINSTANCE           gl_hThisInstance;
#pragma data_seg ()

int mode;
int difficulty;
int elapsed_time;
int background = -1;
int bg_width;
int bg_zwidth1;
int bg_zwidth2;
int stage_bound;
int current_phase;
int current_phase_count;
int current_stage;
char stage_clear;

sGame *game = (sGame*)0x458b00;

class Info {
	public:
		int x;
		int y;
		int z;
		double x_real;
		double y_real;
		double z_real;
		char facing;
		char holding_up;
		char holding_down;
		char holding_left;
		char holding_right;
		char holding_a;
		char holding_j;
		char holding_d;
		char up;
		char down;
		char left;
		char right;
		char A;
		char J;
		char D;
		char DrA;
		char DlA;
		char DuA;
		char DdA;
		char DrJ;
		char DlJ;
		char DuJ;
		char DdJ;
		char DJA;
		int hp;
		int dark_hp;
		int max_hp;
		int mp;
		int frame;
		int bdefend;
		int fall;
		int team;
		int id;
		int blink;
		int state;
		int weapon_type;
		int weapon_held;
		int shake;
		int wait_counter;
		int num;
		int ctimer;
		int arest;
		int vrest;
		double x_velocity;
		double y_velocity;
		double z_velocity;
		int clone;
		int type;
		int reserve;
		sDataFile *data;

		Info() {
			num = -1;
			type = -1;
			RefCount = 1;
		}

		Info(int object_num) {
			Info();
			operator=(object_num);
		}

		Info(const Info &info) {
			Info();
			operator=(info.num);
		}

		void AddRef(){
			RefCount++;
		}
		void RelRef(){
			if(--RefCount == 0) delete this;
		}

		int operator=(int object_num){
			if(object_num<0 || object_num >= 400 || !game->exists[object_num]) return -1;

			x = game->objects[object_num]->x;
			y = game->objects[object_num]->y;
			z = game->objects[object_num]->z;
			x_real = game->objects[object_num]->x_real;
			y_real = game->objects[object_num]->y_real;
			z_real = game->objects[object_num]->z_real;
			facing = game->objects[object_num]->facing;
			holding_up = game->objects[object_num]->holding_up;
			holding_down = game->objects[object_num]->holding_down;
			holding_left = game->objects[object_num]->holding_left;
			holding_right = game->objects[object_num]->holding_right;
			holding_a = game->objects[object_num]->holding_a;
			holding_j = game->objects[object_num]->holding_j;
			holding_d = game->objects[object_num]->holding_d;
			up = game->objects[object_num]->up;
			down = game->objects[object_num]->down;
			left = game->objects[object_num]->left;
			right = game->objects[object_num]->right;
			A = game->objects[object_num]->A;
			J = game->objects[object_num]->J;
			D = game->objects[object_num]->D;
			DrA = game->objects[object_num]->DrA;
			DlA = game->objects[object_num]->DlA;
			DuA = game->objects[object_num]->DuA;
			DdA = game->objects[object_num]->DdA;
			DrJ = game->objects[object_num]->DrJ;
			DlJ = game->objects[object_num]->DlJ;
			DuJ = game->objects[object_num]->DuJ;
			DdJ = game->objects[object_num]->DdJ;
			DJA = game->objects[object_num]->DJA;
			hp = game->objects[object_num]->hp;
			dark_hp = game->objects[object_num]->dark_hp;
			max_hp = game->objects[object_num]->max_hp;
			mp = game->objects[object_num]->mp;
			frame = game->objects[object_num]->frame1;
			fall = game->objects[object_num]->fall;
			bdefend = game->objects[object_num]->bdefend;
			team = game->objects[object_num]->team;
			id = game->objects[object_num]->data->id;
			blink = game->objects[object_num]->blink;
			state = game->objects[object_num]->data->frames[frame].state;
			weapon_type = game->objects[object_num]->weapon_type;
			if(weapon_type == 0){
				weapon_held = -1;
			}else{
				weapon_held = game->objects[object_num]->weapon_held;
			}
			shake = game->objects[object_num]->shake;
			wait_counter = game->objects[object_num]->wait_counter;
			num = object_num;
			ctimer = game->objects[object_num]->ctimer;
			arest = game->objects[object_num]->arest;
			vrest = (int)(*(char*)(*(int*)(0x458c94+object_num*4)+0xF0));
			if(vrest < (int)(*(char*)(*(int*)(0x458c94+object_num*4)+0xF3)))
				vrest = (int)(*(char*)(*(int*)(0x458c94+object_num*4)+0xF3));
			x_velocity = game->objects[object_num]->x_velocity;
			y_velocity = game->objects[object_num]->y_velocity;
			z_velocity = game->objects[object_num]->z_velocity;
			clone = game->objects[object_num]->clone;
			type = game->objects[object_num]->data->type;
			reserve = game->objects[object_num]->reserve;
			data = game->objects[object_num]->data;

			return type;
		}

		int operator=(const Info &info){
			return operator=(info.num);
		}

		int operator+=(int object_num){
			return operator=(num+object_num);
		}

		int operator+=(const Info &info){
			return operator=(num+info.num);
		}

		int operator-=(int object_num){
			return operator=(num-object_num);
		}

		int operator-=(const Info &info){
			return operator=(num-info.num);
		}

		int operator++(){
			return operator=(num+1);
		}

		int operator--(){
			return operator=(num-1);
		}

	private:
		unsigned int RefCount;
};

Info *Info_Factory(){
	return new Info();
}

Info *Info_Factory(int object_num){
	return new Info(object_num);
}

Info *Info_Factory(const Info &info){
	return new Info(info);
}

Info self;
Info target;
asIScriptModule *ScriptModule;
asIScriptEngine *ScriptEngine;
asIScriptContext *ScriptContext;

#ifdef DEBUG_VERSION
	#include <map>

	std::map<int,FILETIME> ModuleTimes;
#endif

void startup();
void cleanup();

typedef enum {
	INVALID,
	VALID,
	MODULE
} FileValidity;

int (__stdcall *AI_o )(int target_num, int object_num, int x, int y, int z, int a, int b);
int (__stdcall *AIa_o)(int object_num, int unkwn1);

int random(int max){//random function that works with replays
	int result; // eax@2
	signed int v3; // eax@3

	DWORD &dword_450C34 = *((DWORD *)0x450C34);
	DWORD &dword_450BCC = *((DWORD *)0x450BCC);

	if ( max > 0 ){
	dword_450C34 = (dword_450C34 + 1) % 1234;
	v3 = dword_450C34 + (unsigned __int8)*(((BYTE *)0x44FF90) + (dword_450BCC + 1) % 3000);
	dword_450BCC = (dword_450BCC + 1) % 3000;
	result = v3 % max;
	}else{
		result = 0;
	}

	return result;
}

int loadTarget(int target_num)
{
	return target = target_num;
}

int setEnemy(int object_num)
{
	if (object_num < 0 || object_num >= 400 || !game->exists[object_num]) return -1;

	return game->objects[self.num]->enemy = object_num;
}

void up(char key, char holding)
{
	game->objects[self.num]->up = key;
	game->objects[self.num]->holding_up = holding;

	self.up = key;
	self.holding_up = holding;
}

void down(char key, char holding)
{
	game->objects[self.num]->down = key;
	game->objects[self.num]->holding_down = holding;

	self.down = key;
	self.holding_down = holding;
}

void left(char key, char holding)
{
	game->objects[self.num]->left = key;
	game->objects[self.num]->holding_left = holding;

	self.left = key;
	self.holding_left = holding;
}

void right(char key, char holding)
{
	game->objects[self.num]->right = key;
	game->objects[self.num]->holding_right = holding;

	self.right = key;
	self.holding_right = holding;
}

void A(char key,char holding)
{
	game->objects[self.num]->A = key;
	game->objects[self.num]->holding_a = holding;

	self.A = key;
	self.holding_a = holding;
}

void J(char key,char holding)
{
	game->objects[self.num]->J = key;
	game->objects[self.num]->holding_j = holding;

	self.J = key;
	self.holding_j = holding;
}

void D(char key,char holding)
{
	game->objects[self.num]->D = key;
	game->objects[self.num]->holding_d = holding;

	self.D = key;
	self.holding_d = holding;
}

void DrA()
{
	game->objects[self.num]->DrA = 3;
	self.DrA = 3;
}

void DlA()
{
	game->objects[self.num]->DlA = 3;
	self.DlA = 3;
}

void DuA()
{
	game->objects[self.num]->DuA = 3;
	self.DuA = 3;
}

void DdA()
{
	game->objects[self.num]->DdA = 3;
	self.DdA = 3;
}

void DrJ()
{
	game->objects[self.num]->DrJ = 3;
	self.DrJ = 3;
}

void DlJ()
{
	game->objects[self.num]->DlJ = 3;
	self.DlJ = 3;
}

void DuJ()
{
	game->objects[self.num]->DuJ = 3;
	self.DuJ = 3;
}

void DdJ()
{
	game->objects[self.num]->DdJ = 3;
	self.DdJ = 3;
}

void DJA()
{
	game->objects[self.num]->DJA = 3;
	self.DJA = 3;
}

void clr(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hConsole == INVALID_HANDLE_VALUE) return;

	COORD coordScreen = {0,0};
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if(!GetConsoleScreenBufferInfo(hConsole,&csbi)){
		return;
	}

	dwConSize = csbi.dwSize.X*csbi.dwSize.Y;

	if(!FillConsoleOutputCharacter(hConsole,' ',dwConSize,coordScreen,&cCharsWritten)){
		return;
	}

	if(!GetConsoleScreenBufferInfo(hConsole,&csbi)){
		return;
	}

	if(!FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten)){
		return;
	}

	SetConsoleCursorPosition(hConsole,coordScreen);
}

void printAddr(void *Addr){
	printf("%p",Addr);
}

void print(bool p){
	if(p){
		printf("true");
	}else{
		printf("false");
	}
}

void print(char p){
	printf("%d",p);
}
void print(short p){
	printf("%d",p);
}
void print(int p){
	printf("%d",p);
}
void print(long long p){
	printf("%ld",p);
}

void print(unsigned char p){
	printf("%u",p);
}
void print(unsigned short p){
	printf("%u",p);
}
void print(unsigned int p){
	printf("%u",p);
}
void print(unsigned long long p){
	printf("%lu",p);
}

void print(float p){
	printf("%f",p);
}
void print(double p){
	printf("%Lf",p);
}

void print(const std::string &p){
	printf("%s",p.c_str());
}

std::string getFileName(int object_num)
{
	std::ostringstream oss;
	oss << "ai\\" << object_num << ".as";
	return oss.str();
}

FileValidity isValidFileName(std::string file)
{
	if(file.length()<7) return INVALID;

	for(unsigned int i = 0;i<file.length();i++){
		if(file.at(i) >= 'A' && file.at(i) <= 'Z') file.at(i) += 'a'-'A';
	}

	if(file.substr(0,3) != "ai\\") return INVALID;

	if(file.at(3) == '_') return MODULE;

	size_t i = 3;

	if(file.at(i) == '-'){
		i = 4;
	}

	bool zeros = true;

	while(i<file.length()-2){
		if(zeros && file.at(i) == '0'){
			if(file.substr(i) == "0.as") return VALID;
			return INVALID;
		}

		if(file.at(i) == '.'){
			if(file.substr(i) == ".as") return VALID;

			return INVALID;
		}

		if(file.at(i) >= '0' && file.at(i) <= '9'){
			zeros = INVALID;

			i += 1;
			continue;
		}

		return INVALID;
	}

	return INVALID;
}

std::string getModuleName(const std::string &file){
	return file.substr(3,file.length()-3);
}

#ifdef DEBUG_VERSION
	bool hasFileTimeChanged(const char *File,FILETIME *Time){
		HANDLE hFile;

		hFile = CreateFile(File,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);

		FILETIME ftWrite;

		if(hFile == INVALID_HANDLE_VALUE){
			ftWrite.dwLowDateTime = 0;
			ftWrite.dwHighDateTime = 0;
		}else{
			if(!GetFileTime(hFile,NULL,NULL,&ftWrite)){
				CloseHandle(hFile);
				return false;
			}
			CloseHandle(hFile);
		}

		if(CompareFileTime(&ftWrite,Time) != 0){
			(*Time) = ftWrite;
			return true;
		}

		return false;
	}

	void rebuildIfUpdated(int id_int,const std::string &fileName){
		if(ModuleTimes.count(id_int)){
			if(hasFileTimeChanged(fileName.c_str(),&(ModuleTimes[id_int]))){
				CScriptBuilder Builder;
				Builder.DefineWord("debug");

				if(fileName.at(0) == '_'){
					Builder.DefineWord("module");
				}else{
					Builder.DefineWord("character");
				}

				ScriptEngine->WriteMessage(fileName.c_str(),0,0,asMSGTYPE_INFORMATION,"Rebuilding.");

				Builder.StartNewModule(ScriptEngine,getModuleName(fileName).c_str());

				int r = Builder.AddSectionFromFile(fileName.c_str());
				if(r<0){
					ScriptEngine->WriteMessage(fileName.c_str(),0,0,asMSGTYPE_ERROR,"Unable to load file.");
					ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
					return;
				}

				r = Builder.BuildModule();
				if(r<0){
					ScriptEngine->WriteMessage(fileName.c_str(),0,0,asMSGTYPE_ERROR,"Unable to build module.");
					ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
					return;
				}
			}
		}else{
			FILETIME Time = {0,0};
			if(hasFileTimeChanged(fileName.c_str(),&Time)){
				ModuleTimes.insert(std::pair<int,FILETIME>(id_int,Time));

				CScriptBuilder Builder;
				Builder.DefineWord("debug");

				ScriptEngine->WriteMessage(fileName.c_str(),0,0,asMSGTYPE_INFORMATION,"Building.");

				Builder.StartNewModule(ScriptEngine,getModuleName(fileName).c_str());

				int r = Builder.AddSectionFromFile(fileName.c_str());
				if(r<0){
					ScriptEngine->WriteMessage(fileName.c_str(),0,0,asMSGTYPE_ERROR,"Unable to load file.");
					ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
					return;
				}

				r = Builder.BuildModule();
				if(r<0){
					ScriptEngine->WriteMessage(fileName.c_str(),0,0,asMSGTYPE_ERROR,"Unable to build module.");
					ScriptEngine->DiscardModule(getModuleName(fileName).c_str());
					return;
				}
			}
		}
	}

	int getIdFromFileName(const std::string &file){
		int x;

		std::stringstream(getModuleName(file)) >> x;

		return x;
	}
#endif

int callEgo(int object_num,int target_num,asIScriptFunction *Function){
	elapsed_time = *(int *)0x450b8c;
	difficulty = *(int *)0x450c30;
	mode = *(int *)0x451160;
	if(background != *(int *)0x44d024){
		background = *(int *)0x44d024;
		bg_width = game->files->backgrounds[background].bg_width;
		bg_zwidth1 = game->files->backgrounds[background].bg_zwidth1;
		bg_zwidth2 = game->files->backgrounds[background].bg_zwidth2;

		stage_bound = bg_width;
		stage_clear = false;
	}
	if(mode == 1){//stage
		stage_bound = *(int *)0x450bb4;
		stage_clear = stage_bound == 0;
	}
	current_phase = *(int *)0x44fb6c;
	current_phase_count = *(int *)0x44f880;
	current_stage = *(int *)0x450b94;

	if((self = object_num) == -1){
		#ifdef DEBUG_VERSION
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to prepare self.");
		#endif
	}

	if((target = target_num) == -1){
		#ifdef DEBUG_VERSION
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to prepare target.");
		#endif
	}

	int r = ScriptContext->Prepare(Function);

	if(r<0){
		#ifdef DEBUG_VERSION
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to prepare the context.");
		#endif
		return 0;
	}

	r = ScriptContext->Execute();

	if(r<0){
		#ifdef DEBUG_VERSION
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to execute the context.");
		#endif
		return 0;
	}

	return ScriptContext->GetReturnDWord();
}

void callId(int object_num,asIScriptFunction *Function){
	elapsed_time = *(int *)0x450b8c;
	difficulty = *(int *)0x450c30;
	mode = *(int *)0x451160;
	if(background != *(int *)0x44d024){
		background = *(int *)0x44d024;
		bg_width = game->files->backgrounds[background].bg_width;
		bg_zwidth1 = game->files->backgrounds[background].bg_zwidth1;
		bg_zwidth2 = game->files->backgrounds[background].bg_zwidth2;

		stage_bound = bg_width;
		stage_clear = false;
	}
	if(mode == 1){//stage
		stage_bound = *(int *)0x450bb4;
		stage_clear = stage_bound == 0;
	}
	current_phase = *(int *)0x44fb6c;
	current_phase_count = *(int *)0x44f880;
	current_stage = *(int *)0x450b94;

	if((self = object_num) == -1){
		#ifdef DEBUG_VERSION
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to prepare self.");
		#endif
	}

	int r = ScriptContext->Prepare(Function);

	if(r<0){
		#ifdef DEBUG_VERSION
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to prepare the context.");
		#endif
		return;
	}

	r = ScriptContext->Execute();

	#ifdef DEBUG_VERSION
		if(r<0){
			ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Unable to execute the context.");
		}
	#endif
}

int __stdcall AI(int target_num, int object_num, int unkwn1, int unkwn2, int unkwn3, int unkwn4, int unkwn5)
{
	DWORD return_value;
	DWORD unkwn6;
	__asm
	{
		mov dword ptr ds:[unkwn6],ecx;
	}
	int id_int = game->objects[object_num]->data->id;

	std::string fileName = getFileName(id_int);

	ScriptModule = ScriptEngine->GetModule(getModuleName(fileName).c_str());

	if(ScriptModule){
		asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("int ego()");

		if(Function){
			return callEgo(object_num,target_num,Function);
		}
	}

	__asm
	{
		mov ecx, dword ptr ds:[unkwn5];
		push ecx;
		mov ecx, dword ptr ds:[unkwn4];
		push ecx;
		mov ecx, dword ptr ds:[unkwn3];
		push ecx;
		mov ecx, dword ptr ds:[unkwn2];
		push ecx;
		mov ecx, dword ptr ds:[unkwn1];
		push ecx;
		mov ecx, dword ptr ds:[object_num];
		push ecx;
		mov ecx, dword ptr ds:[target_num];
		push ecx;
		mov ecx, dword ptr ds:[unkwn6];
		call AI_o;
		mov dword ptr ds:[return_value], eax;
	}

	return return_value;
}

void __stdcall AIa( int object_num,int unkwn1)
{
	DWORD unkwn2;
	_asm
	{
		mov dword ptr ds:[unkwn2],ecx;
	}
	int id_int = game->objects[object_num]->data->id;

	std::string fileName = getFileName(id_int);

	#ifdef DEBUG_VERSION
		rebuildIfUpdated(id_int,fileName);
	#endif

	ScriptModule = ScriptEngine->GetModule(getModuleName(fileName).c_str());

	if(ScriptModule){
		asIScriptFunction *Function = ScriptModule->GetFunctionByDecl("void id()");

		if(Function){
			callId(object_num,Function);

			return;
		}
		#ifdef DEBUG_VERSION
			else{
				if(!ScriptModule->GetFunctionByDecl("int ego()")){
					ScriptEngine->WriteMessage(getFileName(game->objects[object_num]->data->id).c_str(),0,0,asMSGTYPE_ERROR,"Neither 'void id()' nor 'int ego()' are defined.");
				}
			}
		#endif
	}

	_asm
	{
		mov ecx, dword ptr ds:[unkwn1];
		push ecx;
		mov ecx, dword ptr ds:[object_num];
		push ecx;
		mov ecx, dword ptr ds:[unkwn2];
		call AIa_o;
	}
}

#ifdef DEBUG_VERSION
	void MessageCallback(const asSMessageInfo *msg,void *){
		if(msg->section[0] == '\0'){
			printf("%s: %s\n",msg->type == asMSGTYPE_ERROR?"ERROR":msg->type == asMSGTYPE_WARNING?"WARNING":"INFORMATION",msg->message);
		}else if(msg->row == 0 && msg->col == 0){
			printf("%s: %s : %s\n",msg->section,msg->type == asMSGTYPE_ERROR?"ERROR":msg->type == asMSGTYPE_WARNING?"WARNING":"INFORMATION",msg->message);
		}else{
			printf("%s(%d, %d): %s : %s\n",msg->section,msg->row,msg->col,msg->type == asMSGTYPE_ERROR?"ERROR":msg->type == asMSGTYPE_WARNING?"WARNING":"INFORMATION",msg->message);
		}
	}
#endif

void RegisterScriptFunctions(){
	RegisterScriptMath(ScriptEngine);
	RegisterScriptMathComplex(ScriptEngine);
	RegisterScriptMath3D(ScriptEngine);
	RegisterStdString(ScriptEngine);
	RegisterScriptArray(ScriptEngine,true);
	RegisterStdStringUtils(ScriptEngine);
	RegisterGameEnums(ScriptEngine);
	RegisterGameArrays(ScriptEngine);

	ScriptEngine->RegisterGlobalFunction("void clr()",asFUNCTION(clr),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void print(bool p)",asFUNCTIONPR(print,(bool p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int8 p)",asFUNCTIONPR(print,(char p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int16 p)",asFUNCTIONPR(print,(short p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int32 p)",asFUNCTIONPR(print,(int p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(int64 p)",asFUNCTIONPR(print,(long long p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint8 p)",asFUNCTIONPR(print,(unsigned char p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint16 p)",asFUNCTIONPR(print,(unsigned short p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint32 p)",asFUNCTIONPR(print,(unsigned int p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(uint64 p)",asFUNCTIONPR(print,(unsigned long long p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(float p)",asFUNCTIONPR(print,(float p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(double p)",asFUNCTIONPR(print,(double p),void),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void print(const string &in p)",asFUNCTIONPR(print,(const std::string &p),void),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("int loadTarget(int object_num)",asFUNCTION(loadTarget),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("int setEnemy(int object_num)",asFUNCTION(setEnemy),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void up(int8 key = 1,int8 holding = 0)",asFUNCTION(up),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void up(bool key,int8 holding = 0)",asFUNCTION(up),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void up(int8 key,bool holding)",asFUNCTION(up),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void up(bool key,bool holding)",asFUNCTION(up),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void down(int8 key = 1,int8 holding = 0)",asFUNCTION(down),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void down(bool key,int8 holding = 0)",asFUNCTION(down),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void down(int8 key,bool holding)",asFUNCTION(down),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void down(bool key,bool holding)",asFUNCTION(down),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void left(int8 key = 1,int8 holding = 0)",asFUNCTION(left),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void left(bool key,int8 holding = 0)",asFUNCTION(left),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void left(int8 key,bool holding)",asFUNCTION(left),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void left(bool key,bool holding)",asFUNCTION(left),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void right(int8 key = 1,int8 holding = 0)",asFUNCTION(right),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void right(bool key,int8 holding = 0)",asFUNCTION(right),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void right(int8 key,bool holding)",asFUNCTION(right),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void right(bool key,bool holding)",asFUNCTION(right),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void A(int8 key = 1,int8 holding = 0)",asFUNCTION(A),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void A(bool key,int8 holding = 0)",asFUNCTION(A),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void A(int8 key,bool holding)",asFUNCTION(A),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void A(bool key,bool holding)",asFUNCTION(A),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void J(int8 key = 1,int8 holding = 0)",asFUNCTION(J),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void J(bool key,int8 holding = 0)",asFUNCTION(J),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void J(int8 key,bool holding)",asFUNCTION(J),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void J(bool key,bool holding)",asFUNCTION(J),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void D(int8 key = 1,int8 holding = 0)",asFUNCTION(D),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void D(bool key,int8 holding = 0)",asFUNCTION(D),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void D(int8 key,bool holding)",asFUNCTION(D),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void D(bool key,bool holding)",asFUNCTION(D),asCALL_CDECL);

	ScriptEngine->RegisterGlobalFunction("void DrA()",asFUNCTION(DrA),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DlA()",asFUNCTION(DlA),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DuA()",asFUNCTION(DuA),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DdA()",asFUNCTION(DdA),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DrJ()",asFUNCTION(DrJ),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DlJ()",asFUNCTION(DlJ),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DuJ()",asFUNCTION(DuJ),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DdJ()",asFUNCTION(DdJ),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void DJA()",asFUNCTION(DJA),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("int rand(int n)",asFUNCTION(random),asCALL_CDECL);

	ScriptEngine->RegisterGlobalProperty("const int mode",&mode);
	ScriptEngine->RegisterGlobalProperty("const int difficulty",&difficulty);
	ScriptEngine->RegisterGlobalProperty("const int elapsed_time",&elapsed_time);
	ScriptEngine->RegisterGlobalProperty("const int background",&background);
	ScriptEngine->RegisterGlobalProperty("const int bg_width",&bg_width);
	ScriptEngine->RegisterGlobalProperty("const int bg_zwidth1",&bg_zwidth1);
	ScriptEngine->RegisterGlobalProperty("const int bg_zwidth2",&bg_zwidth2);
	ScriptEngine->RegisterGlobalProperty("const int stage_bound",&stage_bound);
	ScriptEngine->RegisterGlobalProperty("const bool stage_clear",&stage_clear);
	ScriptEngine->RegisterGlobalProperty("const int current_phase",&current_phase);
	ScriptEngine->RegisterGlobalProperty("const int current_phase_count",&current_phase_count);
	ScriptEngine->RegisterGlobalProperty("const int current_stage",&current_stage);

	ScriptEngine->RegisterObjectType("Info",0,asOBJ_REF);
	ScriptEngine->RegisterObjectBehaviour("Info",asBEHAVE_ADDREF,"void f()",asMETHOD(Info,AddRef),asCALL_THISCALL);
	ScriptEngine->RegisterObjectBehaviour("Info",asBEHAVE_RELEASE,"void f()",asMETHOD(Info,RelRef),asCALL_THISCALL);
	ScriptEngine->RegisterObjectBehaviour("Info",asBEHAVE_FACTORY,"Info @f()",asFUNCTIONPR(Info_Factory,(),Info*),asCALL_CDECL);
	ScriptEngine->RegisterObjectBehaviour("Info",asBEHAVE_FACTORY,"Info @f(int)",asFUNCTIONPR(Info_Factory,(int object_num),Info*),asCALL_CDECL);
	ScriptEngine->RegisterObjectBehaviour("Info",asBEHAVE_FACTORY,"Info @f(const Info &in info)",asFUNCTIONPR(Info_Factory,(const Info &info),Info*),asCALL_CDECL);

	ScriptEngine->RegisterObjectMethod("Info","int opAssign(int object_num)",asMETHODPR(Info,operator=,(int object_num),int),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info","int opAssign(const Info &in info)",asMETHODPR(Info,operator=,(const Info &info),int),asCALL_THISCALL);

	ScriptEngine->RegisterObjectMethod("Info","int opAddAssign(int object_num)",asMETHODPR(Info,operator+=,(int object_num),int),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info","int opAddAssign(const Info &in info)",asMETHODPR(Info,operator+=,(const Info &info),int),asCALL_THISCALL);

	ScriptEngine->RegisterObjectMethod("Info","int opSubAssign(int object_num)",asMETHODPR(Info,operator-=,(int object_num),int),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info","int opSubAssign(const Info &in info)",asMETHODPR(Info,operator-=,(const Info &info),int),asCALL_THISCALL);

	ScriptEngine->RegisterObjectMethod("Info","int opPreInc()",asMETHODPR(Info,operator++,(),int),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info","int opPreSub()",asMETHODPR(Info,operator--,(),int),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info","int opPostInc()",asMETHODPR(Info,operator++,(),int),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("Info","int opPostSub()",asMETHODPR(Info,operator--,(),int),asCALL_THISCALL);

	ScriptEngine->RegisterObjectProperty("Info","int x",asOFFSET(Info,x));
	ScriptEngine->RegisterObjectProperty("Info","int y",asOFFSET(Info,y));
	ScriptEngine->RegisterObjectProperty("Info","int z",asOFFSET(Info,z));
	ScriptEngine->RegisterObjectProperty("Info","double x_real",asOFFSET(Info,x_real));
	ScriptEngine->RegisterObjectProperty("Info","double y_real",asOFFSET(Info,y_real));
	ScriptEngine->RegisterObjectProperty("Info","double z_real",asOFFSET(Info,z_real));
	ScriptEngine->RegisterObjectProperty("Info","bool facing",asOFFSET(Info,facing));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_up",asOFFSET(Info,holding_up));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_down",asOFFSET(Info,holding_down));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_left",asOFFSET(Info,holding_left));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_right",asOFFSET(Info,holding_right));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_a",asOFFSET(Info,holding_a));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_j",asOFFSET(Info,holding_j));
	ScriptEngine->RegisterObjectProperty("Info","bool holding_d",asOFFSET(Info,holding_d));
	ScriptEngine->RegisterObjectProperty("Info","bool up",asOFFSET(Info,up));
	ScriptEngine->RegisterObjectProperty("Info","bool down",asOFFSET(Info,down));
	ScriptEngine->RegisterObjectProperty("Info","bool left",asOFFSET(Info,left));
	ScriptEngine->RegisterObjectProperty("Info","bool right",asOFFSET(Info,right));
	ScriptEngine->RegisterObjectProperty("Info","bool A",asOFFSET(Info,A));
	ScriptEngine->RegisterObjectProperty("Info","bool J",asOFFSET(Info,J));
	ScriptEngine->RegisterObjectProperty("Info","bool D",asOFFSET(Info,D));
	ScriptEngine->RegisterObjectProperty("Info","int8 DrA",asOFFSET(Info,DrA));
	ScriptEngine->RegisterObjectProperty("Info","int8 DlA",asOFFSET(Info,DlA));
	ScriptEngine->RegisterObjectProperty("Info","int8 DuA",asOFFSET(Info,DuA));
	ScriptEngine->RegisterObjectProperty("Info","int8 DdA",asOFFSET(Info,DdA));
	ScriptEngine->RegisterObjectProperty("Info","int8 DrJ",asOFFSET(Info,DrJ));
	ScriptEngine->RegisterObjectProperty("Info","int8 DlJ",asOFFSET(Info,DlJ));
	ScriptEngine->RegisterObjectProperty("Info","int8 DuJ",asOFFSET(Info,DuJ));
	ScriptEngine->RegisterObjectProperty("Info","int8 DdJ",asOFFSET(Info,DdJ));
	ScriptEngine->RegisterObjectProperty("Info","int8 DJA",asOFFSET(Info,DJA));
	ScriptEngine->RegisterObjectProperty("Info","int hp",asOFFSET(Info,hp));
	ScriptEngine->RegisterObjectProperty("Info","int dark_hp",asOFFSET(Info,dark_hp));
	ScriptEngine->RegisterObjectProperty("Info","int max_hp",asOFFSET(Info,max_hp));
	ScriptEngine->RegisterObjectProperty("Info","int mp",asOFFSET(Info,mp));
	ScriptEngine->RegisterObjectProperty("Info","int frame",asOFFSET(Info,frame));
	ScriptEngine->RegisterObjectProperty("Info","int bdefend",asOFFSET(Info,bdefend));
	ScriptEngine->RegisterObjectProperty("Info","int fall",asOFFSET(Info,fall));
	ScriptEngine->RegisterObjectProperty("Info","int team",asOFFSET(Info,team));
	ScriptEngine->RegisterObjectProperty("Info","int id",asOFFSET(Info,id));
	ScriptEngine->RegisterObjectProperty("Info","int blink",asOFFSET(Info,blink));
	ScriptEngine->RegisterObjectProperty("Info","int state",asOFFSET(Info,state));
	ScriptEngine->RegisterObjectProperty("Info","int weapon_type",asOFFSET(Info,weapon_type));
	ScriptEngine->RegisterObjectProperty("Info","int weapon_held",asOFFSET(Info,weapon_held));
	ScriptEngine->RegisterObjectProperty("Info","int shake",asOFFSET(Info,shake));
	ScriptEngine->RegisterObjectProperty("Info","int wait_counter",asOFFSET(Info,wait_counter));
	ScriptEngine->RegisterObjectProperty("Info","int num",asOFFSET(Info,num));
	ScriptEngine->RegisterObjectProperty("Info","int ctimer",asOFFSET(Info,ctimer));
	ScriptEngine->RegisterObjectProperty("Info","int arest",asOFFSET(Info,arest));
	ScriptEngine->RegisterObjectProperty("Info","int vrest",asOFFSET(Info,vrest));
	ScriptEngine->RegisterObjectProperty("Info","double x_velocity",asOFFSET(Info,x_velocity));
	ScriptEngine->RegisterObjectProperty("Info","double y_velocity",asOFFSET(Info,y_velocity));
	ScriptEngine->RegisterObjectProperty("Info","double z_velocity",asOFFSET(Info,z_velocity));
	ScriptEngine->RegisterObjectProperty("Info","int clone",asOFFSET(Info,clone));
	ScriptEngine->RegisterObjectProperty("Info","int type",asOFFSET(Info,type));
	ScriptEngine->RegisterObjectProperty("Info","int reserve",asOFFSET(Info,reserve));
	ScriptEngine->RegisterObjectProperty("Info","DataFile @data",asOFFSET(Info,data));

	ScriptEngine->RegisterGlobalFunction("void printAddr(const IntArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const BoolArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArrayArray30 @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const CharArrayArray40 @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const DataFileArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const ObjectArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const FrameArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const BackgroundArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const SpawnArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const PhaseArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const StageArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const ItrArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const BdyArray @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Game @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const FileManager @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Stage @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Phase @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Spawn @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Background @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Object @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const DataFile @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Frame @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Bdy @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Itr @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Wpoint @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Cpoint @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Bpoint @addr)",asFUNCTION(printAddr),asCALL_CDECL);
	ScriptEngine->RegisterGlobalFunction("void printAddr(const Opoint @addr)",asFUNCTION(printAddr),asCALL_CDECL);

	ScriptEngine->RegisterGlobalProperty("const Info self",&self);
	ScriptEngine->RegisterGlobalProperty("Info target",&target);
	ScriptEngine->RegisterGlobalProperty("const Game game",game);
}

void startup()
{
	#ifdef DEBUG_VERSION
		AllocConsole();
		freopen("CONIN$","rb",stdin);   // reopen stdin handle as console window input
		freopen("CONOUT$","wb",stdout);  // reopen stout handle as console window output
		freopen("CONOUT$","wb",stderr); // reopen stderr handle as console window output
	#endif

	ScriptModule = NULL;

	ScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

	if(!ScriptEngine){
		::ExitProcess(0);
	}

	#ifdef DEBUG_VERSION
		ScriptEngine->SetMessageCallback(asFUNCTION(MessageCallback),NULL,asCALL_CDECL);
	#endif

	ScriptContext = ScriptEngine->CreateContext();

	RegisterScriptFunctions();

	AI_o = (int (__stdcall *)(int, int, int ,int ,int ,int ,int))DetourFunction((PBYTE)0x00403a40,(PBYTE)AI);
	AIa_o = (int (__stdcall *)(int, int))DetourFunction((PBYTE)0x004094b0,(PBYTE)AIa);

	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	char DirPath[MAX_PATH] = "ai\\*.as";
	char FileName[MAX_PATH] = "ai\\";

	hFind = FindFirstFile(DirPath,&FindFileData);
	if(hFind == INVALID_HANDLE_VALUE) return;

	strcpy(DirPath,FileName);

	do {
		strcpy(FileName,DirPath);
		strcat(FileName,FindFileData.cFileName);

		if(!(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)){
			FileValidity Validity = isValidFileName(FileName);
			if(Validity){
				#ifdef DEBUG_VERSION
					FILETIME Time;
					hasFileTimeChanged(FileName,&Time);
					ModuleTimes.insert(std::pair<int,FILETIME>(getIdFromFileName(FileName),Time));
				#endif

				CScriptBuilder Builder;
				#ifdef DEBUG_VERSION
					Builder.DefineWord("debug");

					ScriptEngine->WriteMessage(FileName,0,0,asMSGTYPE_INFORMATION,"Building.");
				#else
					Builder.DefineWord("release");
				#endif

				if(Validity == MODULE){
					Builder.DefineWord("module");
				}else{
					Builder.DefineWord("character");
				}

				Builder.StartNewModule(ScriptEngine,getModuleName(FileName).c_str());

				int r = Builder.AddSectionFromFile(FileName);
				if(r<0){
					#ifdef DEBUG_VERSION
						ScriptEngine->WriteMessage(FileName,0,0,asMSGTYPE_ERROR,"Unable to load file.");
					#endif
					ScriptEngine->DiscardModule(getModuleName(FileName).c_str());
					continue;
				}

				r = Builder.BuildModule();
				if(r<0){
					#ifdef DEBUG_VERSION
						ScriptEngine->WriteMessage(FileName,0,0,asMSGTYPE_ERROR,"Unable to build module.");
					#endif
					ScriptEngine->DiscardModule(getModuleName(FileName).c_str());
					continue;
				}
			}
		}
	}while(FindNextFile(hFind,&FindFileData));

	FindClose(hFind);
}

void cleanup()
{
	if(ScriptContext) ScriptContext->Release();
	if(ScriptEngine) ScriptEngine->Release();
}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	LPVOID lpDummy = lpReserved;
	lpDummy = NULL;

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			startup();
			InitInstance(hModule); break;
		case DLL_PROCESS_DETACH:
			cleanup();
			ExitInstance(); break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;

	}
	return(true);
}


HRESULT WINAPI DirectDrawCreate(GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter)
{

	if (!gl_hOriginalDll) LoadOriginalDll(); // looking for the "right ddraw.dll"

	// Hooking DDRAW interface from Original Library IDirectDraw *pDD;

	typedef HRESULT (WINAPI* DirectDrawCreate_Type)(GUID FAR *, LPVOID *, IUnknown FAR *);

	DirectDrawCreate_Type DirectDrawCreate_fn = (DirectDrawCreate_Type) GetProcAddress( gl_hOriginalDll, _T("DirectDrawCreate"));

	if (!DirectDrawCreate_fn)
	{
		::ExitProcess(0);
	}

	LPDIRECTDRAW7 FAR dummy;
	HRESULT h = DirectDrawCreate_fn(lpGUID, (LPVOID*) &dummy, pUnkOuter);
	*lplpDD = (LPDIRECTDRAW) new myIDDraw7(dummy);


	return (h);
}

void InitInstance(HANDLE hModule)
{

	// Initialisation
	gl_hOriginalDll        = NULL;
	gl_hThisInstance       = NULL;

	// Storing Instance handle into global var
	gl_hThisInstance = (HINSTANCE)  hModule;
}

void LoadOriginalDll(void)
{

	char buffer[MAX_PATH];

	// Getting path to system dir and to d3d9.dll
	::GetSystemDirectory(buffer,MAX_PATH);

	// Append dll name
	strcat(buffer,"\\ddraw.dll");

	if (!gl_hOriginalDll) gl_hOriginalDll = ::LoadLibrary(buffer);

	// Debug
	if (!gl_hOriginalDll)
	{
		::ExitProcess(0); // exit the hard way
	}
}

void ExitInstance()
{
	if (gl_hOriginalDll)
	{
		::FreeLibrary(gl_hOriginalDll);
		gl_hOriginalDll = NULL;
	}
}