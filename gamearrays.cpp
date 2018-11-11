#include "gamearrays.h"

template <int offset> 
void *get_property(void *self){//AngelScript does not support offsets larger than 0x7fff, and when that is the case we use this function instead
	return (void*)((char*)self+offset);
}

char CharArray::opIndex(unsigned int x){
	return *(((char*)this)+x);
}

template <int size>
CharArray *CharArrayArray::opIndex(unsigned int x){
	return (CharArray*)(((char*)this)+x*size);
}

int IntArray::opIndex(unsigned int x){
	return *(((int*)this)+x);
}

bool BoolArray::opIndex(unsigned int x){
	return *(((bool*)this)+x);
}

sItr *ItrArray::opIndex(unsigned int x){
	return ((sItr*)this)+x;
}

sBdy *BdyArray::opIndex(unsigned int x){
	return ((sBdy*)this)+x;
}

sDataFile *DataFileArray::opIndex(unsigned int x){
	return *(((sDataFile**)this)+x);
}

sObject *ObjectArray::opIndex(unsigned int x){
	return *(((sObject**)this)+x);
}

sFrame *FrameArray::opIndex(unsigned int x){
	return ((sFrame*)this)+x;
}

sBackground *BackgroundArray::opIndex(unsigned int x){
	return ((sBackground*)this)+x;
}

sSpawn *SpawnArray::opIndex(unsigned int x){
	return ((sSpawn*)this)+x;
}

sPhase *PhaseArray::opIndex(unsigned int x){
	return ((sPhase*)this)+x;
}

sStage *StageArray::opIndex(unsigned int x){
	return ((sStage*)this)+x;
}

void RegisterGameArrays(asIScriptEngine *ScriptEngine){
	ScriptEngine->RegisterObjectType("BoolArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("CharArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("CharArrayArray30",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("CharArrayArray40",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("IntArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("ItrArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("BdyArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("DataFileArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("ObjectArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("FrameArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("BackgroundArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("SpawnArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("PhaseArray",0,asOBJ_REF|asOBJ_NOCOUNT);
	ScriptEngine->RegisterObjectType("StageArray",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectType("Opoint",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Opoint","const int kind",asOFFSET(sOpoint,kind));
	ScriptEngine->RegisterObjectProperty("Opoint","const int x",asOFFSET(sOpoint,x));
	ScriptEngine->RegisterObjectProperty("Opoint","const int y",asOFFSET(sOpoint,y));
	ScriptEngine->RegisterObjectProperty("Opoint","const int action",asOFFSET(sOpoint,action));
	ScriptEngine->RegisterObjectProperty("Opoint","const int dvx",asOFFSET(sOpoint,dvx));
	ScriptEngine->RegisterObjectProperty("Opoint","const int dvy",asOFFSET(sOpoint,dvy));
	ScriptEngine->RegisterObjectProperty("Opoint","const int oid",asOFFSET(sOpoint,oid));
	ScriptEngine->RegisterObjectProperty("Opoint","const int facing",asOFFSET(sOpoint,facing));
    
	ScriptEngine->RegisterObjectType("Bpoint",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Bpoint","const int x",asOFFSET(sBpoint,x));
	ScriptEngine->RegisterObjectProperty("Bpoint","const int y",asOFFSET(sBpoint,y));

	ScriptEngine->RegisterObjectType("Cpoint",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Cpoint","const int kind",asOFFSET(sCpoint,kind));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int x",asOFFSET(sCpoint,x));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int y",asOFFSET(sCpoint,y));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int injury",asOFFSET(sCpoint,injury)); //if its kind 2 this is fronthurtact
	ScriptEngine->RegisterObjectProperty("Cpoint","const int cover",asOFFSET(sCpoint,cover)); // if its kind 2 this is backhurtact
	ScriptEngine->RegisterObjectProperty("Cpoint","const int vaction",asOFFSET(sCpoint,vaction));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int aaction",asOFFSET(sCpoint,aaction));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int jaction",asOFFSET(sCpoint,jaction));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int daction",asOFFSET(sCpoint,daction));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int throwvx",asOFFSET(sCpoint,throwvx));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int throwvy",asOFFSET(sCpoint,throwvy));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int hurtable",asOFFSET(sCpoint,hurtable));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int decrease",asOFFSET(sCpoint,decrease));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int dircontrol",asOFFSET(sCpoint,dircontrol));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int taction",asOFFSET(sCpoint,taction));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int throwinjury",asOFFSET(sCpoint,throwinjury));
	ScriptEngine->RegisterObjectProperty("Cpoint","const int throwvz",asOFFSET(sCpoint,throwvz));

	ScriptEngine->RegisterObjectType("Wpoint",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Wpoint","const int kind",asOFFSET(sWpoint,kind));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int x",asOFFSET(sWpoint,x));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int y",asOFFSET(sWpoint,y));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int weaponact",asOFFSET(sWpoint,weaponact));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int attacking",asOFFSET(sWpoint,attacking));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int cover",asOFFSET(sWpoint,cover));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int dvx",asOFFSET(sWpoint,dvx));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int dvy",asOFFSET(sWpoint,dvy));
	ScriptEngine->RegisterObjectProperty("Wpoint","const int dvz",asOFFSET(sWpoint,dvz));

	ScriptEngine->RegisterObjectType("Itr",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Itr","const int kind",asOFFSET(sItr,kind));
	ScriptEngine->RegisterObjectProperty("Itr","const int x",asOFFSET(sItr,x));
	ScriptEngine->RegisterObjectProperty("Itr","const int y",asOFFSET(sItr,y));
	ScriptEngine->RegisterObjectProperty("Itr","const int w",asOFFSET(sItr,w));
	ScriptEngine->RegisterObjectProperty("Itr","const int h",asOFFSET(sItr,h));
	ScriptEngine->RegisterObjectProperty("Itr","const int dvx",asOFFSET(sItr,dvx));
	ScriptEngine->RegisterObjectProperty("Itr","const int dvy",asOFFSET(sItr,dvy));
	ScriptEngine->RegisterObjectProperty("Itr","const int fall",asOFFSET(sItr,fall));
	ScriptEngine->RegisterObjectProperty("Itr","const int arest",asOFFSET(sItr,arest));
	ScriptEngine->RegisterObjectProperty("Itr","const int vrest",asOFFSET(sItr,vrest));
	ScriptEngine->RegisterObjectProperty("Itr","const int unkwn1",asOFFSET(sItr,unkwn1));
	ScriptEngine->RegisterObjectProperty("Itr","const int effect",asOFFSET(sItr,effect));
	ScriptEngine->RegisterObjectProperty("Itr","const int catchingact1",asOFFSET(sItr,catchingact1));
	ScriptEngine->RegisterObjectProperty("Itr","const int catchingact2",asOFFSET(sItr,catchingact2));
	ScriptEngine->RegisterObjectProperty("Itr","const int caughtact1",asOFFSET(sItr,caughtact1));
	ScriptEngine->RegisterObjectProperty("Itr","const int caughtact2",asOFFSET(sItr,caughtact2));
	ScriptEngine->RegisterObjectProperty("Itr","const int bdefend",asOFFSET(sItr,bdefend));
	ScriptEngine->RegisterObjectProperty("Itr","const int injury",asOFFSET(sItr,injury));
	ScriptEngine->RegisterObjectProperty("Itr","const int zwidth",asOFFSET(sItr,zwidth));
	ScriptEngine->RegisterObjectProperty("Itr","const int unkwn2",asOFFSET(sItr,unkwn2));

	ScriptEngine->RegisterObjectType("Bdy",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Bdy","const int kind",asOFFSET(sBdy,kind));
	ScriptEngine->RegisterObjectProperty("Bdy","const int x",asOFFSET(sBdy,x));
	ScriptEngine->RegisterObjectProperty("Bdy","const int y",asOFFSET(sBdy,y));
	ScriptEngine->RegisterObjectProperty("Bdy","const int w",asOFFSET(sBdy,w));
	ScriptEngine->RegisterObjectProperty("Bdy","const int h",asOFFSET(sBdy,h));
	ScriptEngine->RegisterObjectProperty("Bdy","const int unkwn1",asOFFSET(sBdy,unkwn1));
	ScriptEngine->RegisterObjectProperty("Bdy","const int unkwn2",asOFFSET(sBdy,unkwn2));
	ScriptEngine->RegisterObjectProperty("Bdy","const int unkwn3",asOFFSET(sBdy,unkwn3));
	ScriptEngine->RegisterObjectProperty("Bdy","const int unkwn4",asOFFSET(sBdy,unkwn4));
	ScriptEngine->RegisterObjectProperty("Bdy","const int unkwn5",asOFFSET(sBdy,unkwn5));

	ScriptEngine->RegisterObjectType("Frame",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Frame","const bool exists",asOFFSET(sFrame,exists));
	ScriptEngine->RegisterObjectProperty("Frame","const int pic",asOFFSET(sFrame,pic));
	ScriptEngine->RegisterObjectProperty("Frame","const int state",asOFFSET(sFrame,state));
	ScriptEngine->RegisterObjectProperty("Frame","const int wait",asOFFSET(sFrame,wait));
	ScriptEngine->RegisterObjectProperty("Frame","const int next",asOFFSET(sFrame,next));
	ScriptEngine->RegisterObjectProperty("Frame","const int dvx",asOFFSET(sFrame,dvx));
	ScriptEngine->RegisterObjectProperty("Frame","const int dvy",asOFFSET(sFrame,dvy));
	ScriptEngine->RegisterObjectProperty("Frame","const int dvz",asOFFSET(sFrame,dvz));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn1",asOFFSET(sFrame,unkwn1));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_a",asOFFSET(sFrame,hit_a));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_d",asOFFSET(sFrame,hit_d));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_j",asOFFSET(sFrame,hit_j));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_Fa",asOFFSET(sFrame,hit_Fa));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_Ua",asOFFSET(sFrame,hit_Ua));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_Da",asOFFSET(sFrame,hit_Da));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_Fj",asOFFSET(sFrame,hit_Fj));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_Uj",asOFFSET(sFrame,hit_Uj));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_Dj",asOFFSET(sFrame,hit_Dj));
	ScriptEngine->RegisterObjectProperty("Frame","const int hit_ja",asOFFSET(sFrame,hit_ja));
	ScriptEngine->RegisterObjectProperty("Frame","const int mp",asOFFSET(sFrame,mp));
	ScriptEngine->RegisterObjectProperty("Frame","const int centerx",asOFFSET(sFrame,centerx));
	ScriptEngine->RegisterObjectProperty("Frame","const int centery",asOFFSET(sFrame,centery));
	ScriptEngine->RegisterObjectProperty("Frame","const Opoint opoint",asOFFSET(sFrame,opoint));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn2",asOFFSET(sFrame,unkwn2));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn3",asOFFSET(sFrame,unkwn3));
	ScriptEngine->RegisterObjectProperty("Frame","const Bpoint bpoint",asOFFSET(sFrame,bpoint));
	ScriptEngine->RegisterObjectProperty("Frame","const Cpoint cpoint",asOFFSET(sFrame,cpoint));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn4",asOFFSET(sFrame,unkwn4));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn5",asOFFSET(sFrame,unkwn5));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn6",asOFFSET(sFrame,unkwn6));
	ScriptEngine->RegisterObjectProperty("Frame","const Wpoint wpoint",asOFFSET(sFrame,wpoint));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn7",asOFFSET(sFrame,unkwn7));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn8",asOFFSET(sFrame,unkwn8));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn9",asOFFSET(sFrame,unkwn9));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn10",asOFFSET(sFrame,unkwn10));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn11",asOFFSET(sFrame,unkwn11));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn12",asOFFSET(sFrame,unkwn12));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn13",asOFFSET(sFrame,unkwn13));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn14",asOFFSET(sFrame,unkwn14));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn15",asOFFSET(sFrame,unkwn15));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn16",asOFFSET(sFrame,unkwn16));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn17",asOFFSET(sFrame,unkwn17));
	ScriptEngine->RegisterObjectProperty("Frame","const int itr_count",asOFFSET(sFrame,itr_count));
	ScriptEngine->RegisterObjectProperty("Frame","const int bdy_count",asOFFSET(sFrame,bdy_count));
	ScriptEngine->RegisterObjectProperty("Frame","const ItrArray @itrs",asOFFSET(sFrame,itrs));
	ScriptEngine->RegisterObjectProperty("Frame","const BdyArray @bdys",asOFFSET(sFrame,bdys));
	ScriptEngine->RegisterObjectProperty("Frame","const int itr_x",asOFFSET(sFrame,itr_x));
	ScriptEngine->RegisterObjectProperty("Frame","const int itr_y",asOFFSET(sFrame,itr_y));
	ScriptEngine->RegisterObjectProperty("Frame","const int itr_w",asOFFSET(sFrame,itr_w));
	ScriptEngine->RegisterObjectProperty("Frame","const int itr_h",asOFFSET(sFrame,itr_h));
	ScriptEngine->RegisterObjectProperty("Frame","const int bdy_x",asOFFSET(sFrame,bdy_x));
	ScriptEngine->RegisterObjectProperty("Frame","const int bdy_y",asOFFSET(sFrame,bdy_y));
	ScriptEngine->RegisterObjectProperty("Frame","const int bdy_w",asOFFSET(sFrame,bdy_w));
	ScriptEngine->RegisterObjectProperty("Frame","const int bdy_h",asOFFSET(sFrame,bdy_h));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn18",asOFFSET(sFrame,unkwn18));
	ScriptEngine->RegisterObjectProperty("Frame","const CharArray fname",asOFFSET(sFrame,fname));
	ScriptEngine->RegisterObjectProperty("Frame","const CharArray @sound",asOFFSET(sFrame,sound));
	ScriptEngine->RegisterObjectProperty("Frame","const int unkwn19",asOFFSET(sFrame,unkwn19));

	ScriptEngine->RegisterObjectType("DataFile",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("DataFile","const int walking_frame_rate",asOFFSET(sDataFile,walking_frame_rate));
	ScriptEngine->RegisterObjectProperty("DataFile","const int unkwn1",asOFFSET(sDataFile,unkwn1));
	ScriptEngine->RegisterObjectProperty("DataFile","const double walking_speed",asOFFSET(sDataFile,walking_speed));
	ScriptEngine->RegisterObjectProperty("DataFile","const double walking_speedz",asOFFSET(sDataFile,walking_speedz));
	ScriptEngine->RegisterObjectProperty("DataFile","const int running_frame_rate",asOFFSET(sDataFile,running_frame_rate));
	ScriptEngine->RegisterObjectProperty("DataFile","const double running_speed",asOFFSET(sDataFile,running_speed));
	ScriptEngine->RegisterObjectProperty("DataFile","const double running_speedz",asOFFSET(sDataFile,running_speedz));
	ScriptEngine->RegisterObjectProperty("DataFile","const double heavy_walking_speed",asOFFSET(sDataFile,heavy_walking_speed));
	ScriptEngine->RegisterObjectProperty("DataFile","const double heavy_walking_speedz",asOFFSET(sDataFile,heavy_walking_speedz));
	ScriptEngine->RegisterObjectProperty("DataFile","const double heavy_running_speed",asOFFSET(sDataFile,heavy_running_speed));
	ScriptEngine->RegisterObjectProperty("DataFile","const double heavy_running_speedz",asOFFSET(sDataFile,heavy_running_speedz));
	ScriptEngine->RegisterObjectProperty("DataFile","const double jump_height",asOFFSET(sDataFile,jump_height));
	ScriptEngine->RegisterObjectProperty("DataFile","const double jump_distance",asOFFSET(sDataFile,jump_distance));
	ScriptEngine->RegisterObjectProperty("DataFile","const double jump_distancez",asOFFSET(sDataFile,jump_distancez));
	ScriptEngine->RegisterObjectProperty("DataFile","const double dash_height",asOFFSET(sDataFile,dash_height));
	ScriptEngine->RegisterObjectProperty("DataFile","const double dash_distance",asOFFSET(sDataFile,dash_distance));
	ScriptEngine->RegisterObjectProperty("DataFile","const double dash_distancez",asOFFSET(sDataFile,dash_distancez));
	ScriptEngine->RegisterObjectProperty("DataFile","const double rowing_height",asOFFSET(sDataFile,rowing_height));
	ScriptEngine->RegisterObjectProperty("DataFile","const double rowing_distance",asOFFSET(sDataFile,rowing_distance));
	ScriptEngine->RegisterObjectProperty("DataFile","const int weapon_hp",asOFFSET(sDataFile,weapon_hp));
	ScriptEngine->RegisterObjectProperty("DataFile","const int weapon_drop_hurt",asOFFSET(sDataFile,weapon_drop_hurt));
	ScriptEngine->RegisterObjectProperty("DataFile","const CharArray unkwn2",asOFFSET(sDataFile,unkwn2));
	ScriptEngine->RegisterObjectProperty("DataFile","const int pic_count",asOFFSET(sDataFile,pic_count));
	ScriptEngine->RegisterObjectProperty("DataFile","const CharArrayArray40 pic_bmps",asOFFSET(sDataFile,pic_bmps));
	ScriptEngine->RegisterObjectProperty("DataFile","const IntArray pic_index",asOFFSET(sDataFile,pic_index));
	ScriptEngine->RegisterObjectProperty("DataFile","const IntArray pic_width",asOFFSET(sDataFile,pic_width));
	ScriptEngine->RegisterObjectProperty("DataFile","const IntArray pic_height",asOFFSET(sDataFile,pic_height));
	ScriptEngine->RegisterObjectProperty("DataFile","const IntArray pic_row",asOFFSET(sDataFile,pic_row));
	ScriptEngine->RegisterObjectProperty("DataFile","const IntArray pic_col",asOFFSET(sDataFile,pic_col));
	ScriptEngine->RegisterObjectProperty("DataFile","const int id",asOFFSET(sDataFile,id));
	ScriptEngine->RegisterObjectProperty("DataFile","const int type",asOFFSET(sDataFile,type));
	ScriptEngine->RegisterObjectProperty("DataFile","const int unkwn3",asOFFSET(sDataFile,unkwn3));
	ScriptEngine->RegisterObjectProperty("DataFile","const CharArray small_bmp",asOFFSET(sDataFile,small_bmp));
	ScriptEngine->RegisterObjectProperty("DataFile","const int unkwn4",asOFFSET(sDataFile,unkwn4));
	ScriptEngine->RegisterObjectProperty("DataFile","const CharArray face_bmp",asOFFSET(sDataFile,face_bmp));
	ScriptEngine->RegisterObjectProperty("DataFile","const IntArray unkwn5",asOFFSET(sDataFile,unkwn5));
	ScriptEngine->RegisterObjectProperty("DataFile","const FrameArray frames",asOFFSET(sDataFile,frames));
	ScriptEngine->RegisterObjectMethod  ("DataFile","const CharArray &get_name() const",asFUNCTION(get_property<asOFFSET(sDataFile,name)>),asCALL_CDECL_OBJLAST);

	ScriptEngine->RegisterObjectType("Object",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Object","const int move_counter",asOFFSET(sObject,move_counter));
	ScriptEngine->RegisterObjectProperty("Object","const int run_counter",asOFFSET(sObject,run_counter));
	ScriptEngine->RegisterObjectProperty("Object","const int blink",asOFFSET(sObject,blink));
	ScriptEngine->RegisterObjectProperty("Object","const int unkwn1",asOFFSET(sObject,unkwn1));
	ScriptEngine->RegisterObjectProperty("Object","const int x",asOFFSET(sObject,x));
	ScriptEngine->RegisterObjectProperty("Object","const int y",asOFFSET(sObject,y));
	ScriptEngine->RegisterObjectProperty("Object","const int z",asOFFSET(sObject,z));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn2",asOFFSET(sObject,unkwn2));
	ScriptEngine->RegisterObjectProperty("Object","const double x_acceleration",asOFFSET(sObject,x_acceleration));
	ScriptEngine->RegisterObjectProperty("Object","const double y_acceleration",asOFFSET(sObject,y_acceleration));
	ScriptEngine->RegisterObjectProperty("Object","const double z_acceleration",asOFFSET(sObject,z_acceleration));
	ScriptEngine->RegisterObjectProperty("Object","const double x_velocity",asOFFSET(sObject,x_velocity));
	ScriptEngine->RegisterObjectProperty("Object","const double y_velocity",asOFFSET(sObject,y_velocity));
	ScriptEngine->RegisterObjectProperty("Object","const double z_velocity",asOFFSET(sObject,z_velocity));
	ScriptEngine->RegisterObjectProperty("Object","const double x_real",asOFFSET(sObject,x_real));
	ScriptEngine->RegisterObjectProperty("Object","const double y_real",asOFFSET(sObject,y_real));
	ScriptEngine->RegisterObjectProperty("Object","const double z_real",asOFFSET(sObject,z_real));
	ScriptEngine->RegisterObjectProperty("Object","const int frame1",asOFFSET(sObject,frame1));
	ScriptEngine->RegisterObjectProperty("Object","const int frame2",asOFFSET(sObject,frame2));
	ScriptEngine->RegisterObjectProperty("Object","const int frame3",asOFFSET(sObject,frame3));
	ScriptEngine->RegisterObjectProperty("Object","const int frame4",asOFFSET(sObject,frame4));
	ScriptEngine->RegisterObjectProperty("Object","const bool facing",asOFFSET(sObject,facing));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn3",asOFFSET(sObject,unkwn3));
	ScriptEngine->RegisterObjectProperty("Object","const int wait_counter",asOFFSET(sObject,wait_counter));
	ScriptEngine->RegisterObjectProperty("Object","const int ccatcher",asOFFSET(sObject,ccatcher));
	ScriptEngine->RegisterObjectProperty("Object","const int ctimer",asOFFSET(sObject,ctimer));
	ScriptEngine->RegisterObjectProperty("Object","const int weapon_type",asOFFSET(sObject,weapon_type));
	ScriptEngine->RegisterObjectProperty("Object","const int weapon_held",asOFFSET(sObject,weapon_held));
	ScriptEngine->RegisterObjectProperty("Object","const int weapon_holder",asOFFSET(sObject,weapon_holder));
	ScriptEngine->RegisterObjectProperty("Object","const int unkwn4",asOFFSET(sObject,unkwn4));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn5",asOFFSET(sObject,unkwn5));
	ScriptEngine->RegisterObjectProperty("Object","const int fall",asOFFSET(sObject,fall));
	ScriptEngine->RegisterObjectProperty("Object","const int shake",asOFFSET(sObject,shake));
	ScriptEngine->RegisterObjectProperty("Object","const int bdefend",asOFFSET(sObject,bdefend));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn6",asOFFSET(sObject,unkwn6));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_up",asOFFSET(sObject,holding_up));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_down",asOFFSET(sObject,holding_down));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_left",asOFFSET(sObject,holding_left));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_right",asOFFSET(sObject,holding_right));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_a",asOFFSET(sObject,holding_a));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_j",asOFFSET(sObject,holding_j));
	ScriptEngine->RegisterObjectProperty("Object","const bool holding_d",asOFFSET(sObject,holding_d));
	ScriptEngine->RegisterObjectProperty("Object","const bool up",asOFFSET(sObject,up));
	ScriptEngine->RegisterObjectProperty("Object","const bool down",asOFFSET(sObject,down));
	ScriptEngine->RegisterObjectProperty("Object","const bool left",asOFFSET(sObject,left));
	ScriptEngine->RegisterObjectProperty("Object","const bool right",asOFFSET(sObject,right));
	ScriptEngine->RegisterObjectProperty("Object","const bool A",asOFFSET(sObject,A));
	ScriptEngine->RegisterObjectProperty("Object","const bool J",asOFFSET(sObject,J));
	ScriptEngine->RegisterObjectProperty("Object","const bool D",asOFFSET(sObject,D));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DrA",asOFFSET(sObject,DrA));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DlA",asOFFSET(sObject,DlA));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DuA",asOFFSET(sObject,DuA));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DdA",asOFFSET(sObject,DdA));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DrJ",asOFFSET(sObject,DrJ));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DlJ",asOFFSET(sObject,DlJ));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DuJ",asOFFSET(sObject,DuJ));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DdJ",asOFFSET(sObject,DdJ));
	ScriptEngine->RegisterObjectProperty("Object","const int8 DJA",asOFFSET(sObject,DJA));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn7",asOFFSET(sObject,unkwn7));
	ScriptEngine->RegisterObjectProperty("Object","const int arest",asOFFSET(sObject,arest));
	ScriptEngine->RegisterObjectProperty("Object","const int vrest",asOFFSET(sObject,vrest));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn8",asOFFSET(sObject,unkwn8));
	ScriptEngine->RegisterObjectProperty("Object","const int attacked_object_num",asOFFSET(sObject,attacked_object_num));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn9",asOFFSET(sObject,unkwn9));
	ScriptEngine->RegisterObjectProperty("Object","const int clone",asOFFSET(sObject,clone));
	ScriptEngine->RegisterObjectProperty("Object","const int weapon_thrower",asOFFSET(sObject,weapon_thrower));
	ScriptEngine->RegisterObjectProperty("Object","const int hp",asOFFSET(sObject,hp));
	ScriptEngine->RegisterObjectProperty("Object","const int dark_hp",asOFFSET(sObject,dark_hp));
	ScriptEngine->RegisterObjectProperty("Object","const int max_hp",asOFFSET(sObject,max_hp));
	ScriptEngine->RegisterObjectProperty("Object","const int mp",asOFFSET(sObject,mp));
	ScriptEngine->RegisterObjectProperty("Object","const int reserve",asOFFSET(sObject,reserve));
	ScriptEngine->RegisterObjectProperty("Object","const int unkwn10",asOFFSET(sObject,unkwn10));
	ScriptEngine->RegisterObjectProperty("Object","const int unkwn11",asOFFSET(sObject,unkwn11));
	ScriptEngine->RegisterObjectProperty("Object","const int pic_gain",asOFFSET(sObject,pic_gain));
	ScriptEngine->RegisterObjectProperty("Object","const int bottle_hp",asOFFSET(sObject,bottle_hp));
	ScriptEngine->RegisterObjectProperty("Object","const int throwinjury",asOFFSET(sObject,throwinjury));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn12",asOFFSET(sObject,unkwn12));
	ScriptEngine->RegisterObjectProperty("Object","const int firzen_counter",asOFFSET(sObject,firzen_counter));
	ScriptEngine->RegisterObjectProperty("Object","const int unkwn13",asOFFSET(sObject,unkwn13));
	ScriptEngine->RegisterObjectProperty("Object","const int armour_multiplier",asOFFSET(sObject,armour_multiplier));
	ScriptEngine->RegisterObjectProperty("Object","const int unkwn14",asOFFSET(sObject,unkwn14));
	ScriptEngine->RegisterObjectProperty("Object","const int total_attack",asOFFSET(sObject,total_attack));
	ScriptEngine->RegisterObjectProperty("Object","const int hp_lost",asOFFSET(sObject,hp_lost));
	ScriptEngine->RegisterObjectProperty("Object","const int mp_usage",asOFFSET(sObject,mp_usage));
	ScriptEngine->RegisterObjectProperty("Object","const CharArray unkwn15",asOFFSET(sObject,unkwn15));
	ScriptEngine->RegisterObjectProperty("Object","const int kills",asOFFSET(sObject,kills));
	ScriptEngine->RegisterObjectProperty("Object","const int weapon_picks",asOFFSET(sObject,weapon_picks));
	ScriptEngine->RegisterObjectProperty("Object","const int enemy",asOFFSET(sObject,enemy));
	ScriptEngine->RegisterObjectProperty("Object","const int team",asOFFSET(sObject,team));
	ScriptEngine->RegisterObjectProperty("Object","const DataFile @data",asOFFSET(sObject,data));
	
	ScriptEngine->RegisterObjectType("Spawn",0,asOBJ_REF|asOBJ_NOCOUNT);
	
	ScriptEngine->RegisterObjectProperty("Spawn","const IntArray unkwn1",asOFFSET(sSpawn,unkwn1));
	ScriptEngine->RegisterObjectProperty("Spawn","const int id",asOFFSET(sSpawn,id));
	ScriptEngine->RegisterObjectProperty("Spawn","const int x",asOFFSET(sSpawn,x));
	ScriptEngine->RegisterObjectProperty("Spawn","const int hp",asOFFSET(sSpawn,hp));
	ScriptEngine->RegisterObjectProperty("Spawn","const int times",asOFFSET(sSpawn,times));
	ScriptEngine->RegisterObjectProperty("Spawn","const int reserve",asOFFSET(sSpawn,reserve));
	ScriptEngine->RegisterObjectProperty("Spawn","const int join",asOFFSET(sSpawn,join));
	ScriptEngine->RegisterObjectProperty("Spawn","const int join_reserve",asOFFSET(sSpawn,join_reserve));
	ScriptEngine->RegisterObjectProperty("Spawn","const int act",asOFFSET(sSpawn,act));
	ScriptEngine->RegisterObjectProperty("Spawn","const int unkwn2",asOFFSET(sSpawn,unkwn2));
	ScriptEngine->RegisterObjectProperty("Spawn","const double ratio",asOFFSET(sSpawn,ratio));
	ScriptEngine->RegisterObjectProperty("Spawn","const int role",asOFFSET(sSpawn,role));
	ScriptEngine->RegisterObjectProperty("Spawn","const int unkwn3",asOFFSET(sSpawn,unkwn3));
		
	ScriptEngine->RegisterObjectType("Phase",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Phase","const int bound",asOFFSET(sPhase,bound));
	ScriptEngine->RegisterObjectProperty("Phase","const CharArray music",asOFFSET(sPhase,music));
	ScriptEngine->RegisterObjectProperty("Phase","const SpawnArray spawns",asOFFSET(sPhase,spawns));
	ScriptEngine->RegisterObjectProperty("Phase","const int when_clear_goto_phase",asOFFSET(sPhase,when_clear_goto_phase));
		
	ScriptEngine->RegisterObjectType("Stage",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Stage","const int phase_count",asOFFSET(sStage,phase_count));
	ScriptEngine->RegisterObjectProperty("Stage","const PhaseArray phases",asOFFSET(sStage,phases));

	ScriptEngine->RegisterObjectType("Background",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Background","const int bg_width",asOFFSET(sBackground,bg_width));
	ScriptEngine->RegisterObjectProperty("Background","const int bg_zwidth1",asOFFSET(sBackground,bg_zwidth1));
	ScriptEngine->RegisterObjectProperty("Background","const int bg_zwidth2",asOFFSET(sBackground,bg_zwidth2));
	ScriptEngine->RegisterObjectProperty("Background","const int perspective1",asOFFSET(sBackground,perspective1));
	ScriptEngine->RegisterObjectProperty("Background","const int perspective2",asOFFSET(sBackground,perspective2));
	ScriptEngine->RegisterObjectProperty("Background","const int shadow1",asOFFSET(sBackground,shadow1));
	ScriptEngine->RegisterObjectProperty("Background","const int shadow2",asOFFSET(sBackground,shadow2));
	ScriptEngine->RegisterObjectProperty("Background","const int layer_count",asOFFSET(sBackground,layer_count));
	ScriptEngine->RegisterObjectProperty("Background","const CharArrayArray30 layer_bmps",asOFFSET(sBackground,layer_bmps));
	ScriptEngine->RegisterObjectProperty("Background","const CharArray shadow_bmp",asOFFSET(sBackground,shadow_bmp));
	ScriptEngine->RegisterObjectProperty("Background","const CharArray name",asOFFSET(sBackground,name));
	ScriptEngine->RegisterObjectProperty("Background","const IntArray transparency",asOFFSET(sBackground,transparency));
	ScriptEngine->RegisterObjectProperty("Background","const IntArray layer_width",asOFFSET(sBackground,layer_width));
	ScriptEngine->RegisterObjectProperty("Background","const IntArray layer_x",asOFFSET(sBackground,layer_x));
	ScriptEngine->RegisterObjectProperty("Background","const IntArray layer_y",asOFFSET(sBackground,layer_y));
	ScriptEngine->RegisterObjectProperty("Background","const IntArray layer_height",asOFFSET(sBackground,layer_height));
	ScriptEngine->RegisterObjectProperty("Background","const CharArray unkwn1",asOFFSET(sBackground,unkwn1));

	ScriptEngine->RegisterObjectType("FileManager",0,asOBJ_REF|asOBJ_NOCOUNT);
	
	ScriptEngine->RegisterObjectProperty("FileManager","const DataFileArray datas",asOFFSET(sFileManager,datas));
	ScriptEngine->RegisterObjectProperty("FileManager","const IntArray data_ptrs",asOFFSET(sFileManager,datas));//allows to check whether or not a datafile exists
	ScriptEngine->RegisterObjectProperty("FileManager","const StageArray stages",asOFFSET(sFileManager,stages));
	ScriptEngine->RegisterObjectMethod  ("FileManager","const BackgroundArray &get_backgrounds() const",asFUNCTION(get_property<asOFFSET(sFileManager,backgrounds)>),asCALL_CDECL_OBJLAST);

	ScriptEngine->RegisterObjectType("Game",0,asOBJ_REF|asOBJ_NOCOUNT);

	ScriptEngine->RegisterObjectProperty("Game","const int state",asOFFSET(sGame,state));
	ScriptEngine->RegisterObjectProperty("Game","const BoolArray exists",asOFFSET(sGame,exists));
	ScriptEngine->RegisterObjectProperty("Game","const ObjectArray objects",asOFFSET(sGame,objects));
	ScriptEngine->RegisterObjectProperty("Game","const FileManager @files",asOFFSET(sGame,files));
	
	ScriptEngine->RegisterObjectMethod("IntArray","const int opIndex(uint x) const",asMETHOD(IntArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("BoolArray","const bool opIndex(uint x) const",asMETHOD(BoolArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("CharArray","const int8 opIndex(uint x) const",asMETHOD(CharArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("CharArrayArray30","const CharArray &opIndex(uint x) const",asMETHOD(CharArrayArray,opIndex<30>),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("CharArrayArray40","const CharArray &opIndex(uint x) const",asMETHOD(CharArrayArray,opIndex<40>),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("DataFileArray","const DataFile &opIndex(uint x) const",asMETHOD(DataFileArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("ObjectArray","const Object &opIndex(uint x) const",asMETHOD(ObjectArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("FrameArray","const Frame &opIndex(uint x) const",asMETHOD(FrameArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("BackgroundArray","const Background &opIndex(uint x) const",asMETHOD(BackgroundArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("SpawnArray","const Spawn &opIndex(uint x) const",asMETHOD(SpawnArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("PhaseArray","const Phase &opIndex(uint x) const",asMETHOD(PhaseArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("StageArray","const Stage &opIndex(uint x) const",asMETHOD(StageArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("ItrArray","const Itr &opIndex(uint x) const",asMETHOD(ItrArray,opIndex),asCALL_THISCALL);
	ScriptEngine->RegisterObjectMethod("BdyArray","const Bdy &opIndex(uint x) const",asMETHOD(BdyArray,opIndex),asCALL_THISCALL);
}