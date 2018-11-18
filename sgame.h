#ifndef _SGAME_H_
    #define _SGAME_H_

typedef struct {
    int kind;
    int x;
    int y;
    int action;
    int dvx;
    int dvy;
    int oid;
    int facing;
} sOpoint;

typedef struct {
    int x;
    int y;
} sBpoint;

typedef struct {
    int kind;
    int x;
    int y;
    int injury; //if its kind 2 this is fronthurtact
    int cover; // if its kind 2 this is backhurtact
    int vaction;
    int aaction;
    int jaction;
    int daction;
    int throwvx;
    int throwvy;
    int hurtable;
    int decrease;
    int dircontrol;
    int taction;
    int throwinjury;
    int throwvz;
} sCpoint;

typedef struct {
    int kind;
    int x;
    int y;
    int weaponact;
    int attacking;
    int cover;
    int dvx;
    int dvy;
    int dvz;
} sWpoint;

typedef struct {
    int kind;
    int x;
    int y;
    int w;
    int h;
    int dvx;
    int dvy;
    int fall;
    int arest;
    int vrest;
    int unkwn1;
    int effect;
    int catchingact1;
    int catchingact2;
    int caughtact1;
    int caughtact2;
    int bdefend;
    int injury;
    int zwidth;
    int unkwn2;
} sItr;

typedef struct {
    int kind;
    int x;
    int y;
    int w;
    int h;
    int unkwn1;
    int unkwn2;
    int unkwn3;
    int unkwn4;
    int unkwn5;
} sBdy;

typedef struct {
    char exists;
    int pic;
    int state;
    int wait;
    int next;
    int dvx;
    int dvy;
    int dvz;
    int unkwn1;
    int hit_a;
    int hit_d;
    int hit_j;
    int hit_Fa;
    int hit_Ua;
    int hit_Da;
    int hit_Fj;
    int hit_Uj;
    int hit_Dj;
    int hit_ja;
    int mp;
    int centerx;
    int centery;
    sOpoint opoint;
    int unkwn2;
    int unkwn3;
    sBpoint bpoint;
    sCpoint cpoint;
    int unkwn4;
    int unkwn5;
    int unkwn6;
    sWpoint wpoint;
    int unkwn7;
    int unkwn8;
    int unkwn9;
    int unkwn10;
    int unkwn11;
    int unkwn12;
    int unkwn13;
    int unkwn14;
    int unkwn15;
    int unkwn16;
    int unkwn17;
    int itr_count;
    int bdy_count;
    //vv these are pointers to arrays
    sItr *itrs;
    sBdy *bdys;
    //vv these values form a rectangle that holds all itrs/bdys within it
    int itr_x;
    int itr_y;
    int itr_w;
    int itr_h;
    int bdy_x;
    int bdy_y;
    int bdy_w;
    int bdy_h;
    //----------------------------------------
    int unkwn18;
    char fname[20];
    char (*sound)[20]; // maximum sound path is unknown actually
    int unkwn19;
} sFrame;

typedef struct {
    int walking_frame_rate;
    int unkwn1;
    double walking_speed;
    double walking_speedz;
    int running_frame_rate;
    double running_speed;
    double running_speedz;
    double heavy_walking_speed;
    double heavy_walking_speedz;
    double heavy_running_speed;
    double heavy_running_speedz;
    double jump_height;
    double jump_distance;
    double jump_distancez;
    double dash_height;
    double dash_distance;
    double dash_distancez;
    double rowing_height;
    double rowing_distance;
    int weapon_hp;
    int weapon_drop_hurt;
    char unkwn2[1024];
    int pic_count;
    char pic_bmps[40][10];
    int pic_index[10];
    int pic_width[10];
    int pic_height[10];
    int pic_row[10];
    int pic_col[10];
    int id;
    int type;
    int unkwn3;
    char small_bmp[40]; //I believe at least some of this has to do with small image
    int unkwn4;
    char face_bmp[40]; //I believe at least some of this has to do with small image
    int unkwn5[20];
    sFrame frames[400];
    char name[12]; //not actually certain that the length is 12, seems like voodoo magic
} sDataFile;

typedef struct {
    int move_counter;
    int run_counter;
    int blink;
    int unkwn1;
    int x;
    int y;
    int z;
    char unkwn2[12];
    double x_acceleration;
    double y_acceleration;
    double z_acceleration;
    double x_velocity;
    double y_velocity;
    double z_velocity;
    double x_real;
    double y_real;
    double z_real;
    int frame1;
    int frame2;
    int frame3;
    int frame4;
    char facing;
    char unkwn3[11];
    int wait_counter;
    int ccatcher;
    int ctimer;
    int weapon_type;
    int weapon_held;
    int weapon_holder;
    int unkwn4;
    char unkwn5[8];
    int fall;
    int shake;
    int bdefend;
    char unkwn6[10];
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
    char unkwn7[15];
    int arest;
    int vrest;
    char unkwn8[396];
    int attacked_object_num;
    char unkwn9[112];
    int clone;
    int weapon_thrower;
    int hp;
    int dark_hp;
    int max_hp;
    int mp;
    int reserve;
    int unkwn10;
    int unkwn11;
    int pic_gain;
    int bottle_hp;
    int throwinjury;
    char unkwn12[20];
    int firzen_counter;
    int unkwn13;
    int armour_multiplier;
    int unkwn14;
    int total_attack;
    int hp_lost;
    int mp_usage;
    int unkwn15; // "owner" according to xsoameix
    int kills;
    int weapon_picks;
    int enemy;
    int team;
    sDataFile *data;
} sObject;

typedef struct {
    int unkwn1[43];//seems to have something to do with bosses, is changed during game so I believe it keeps track of whether or not soldiers should respawn
    int id;
    int x;
    int hp;
    int times;
    int reserve;
    int join;
    int join_reserve;
    int act;
    int unkwn2;
    double ratio;
    int role; // 0 = normal, 1 = soldier, 2 = boss
    int unkwn3;
} sSpawn;

typedef struct {
    int bound;
    char music[52];
    sSpawn spawns[60];
    int when_clear_goto_phase;
} sPhase;

typedef struct {
    int phase_count;
    sPhase phases[100];
} sStage;

typedef struct {
    int bg_width; //0x0
    int bg_zwidth1; //0x4
    int bg_zwidth2; // 0x8
    int perspective1; //0xC
    int perspective2; //0x10
    int shadow1; //0x14
    int shadow2; //0x18
    int layer_count; //0x1c
    char layer_bmps[30][30]; //0x20
    char shadow_bmp[30]; //0x3a4
    char name[30]; //0x3c2
    int transparency[30]; //0x3e0
    int layer_width[30]; // 0x458
    int layer_x[30]; // 0x4d0
    int layer_y[30]; // 0x548
    int layer_height[30]; // 0x5c0
    char unkwn1[856];
} sBackground;

typedef struct {
    sDataFile *datas[500];
    sStage stages[60];
    sBackground backgrounds[50];
} sFileManager;

typedef struct {
    int state; // 0x4
    char exists[400]; // 0x194
    sObject *objects[400]; // 0x7d4
    sFileManager *files; //FA4
} sGame;

#endif // _SGAME_H_
