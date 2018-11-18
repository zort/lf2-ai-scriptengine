#include <assert.h>
#include <string.h> // strstr
#include <new> // new()
#include <math.h>
#include "scriptmath3d.h"

BEGIN_AS_NAMESPACE

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(const Vector3 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3::Vector3(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

bool operator==(const Vector3 &a, const Vector3 &b)
{
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

bool operator!=(const Vector3 &a, const Vector3 &b)
{
	return !(a == b);
}

Vector3 &Vector3::operator=(const Vector3 &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector3 &Vector3::operator+=(const Vector3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(double s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3 &Vector3::operator/=(double s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

double Vector3::length() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
	// Return a new object as a script handle
	Vector3 res(a.x + b.x, a.y + b.y, a.z + b.z);
	return res;
}

Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	// Return a new object as a script handle
	Vector3 res(a.x - b.x, a.y - b.y, a.z - b.z);
	return res;
}

Vector3 operator*(double s, const Vector3 &v)
{
	// Return a new object as a script handle
	Vector3 res(v.x * s, v.y * s, v.z * s);
	return res;
}

Vector3 operator*(const Vector3 &v, double s)
{
	// Return a new object as a script handle
	Vector3 res(v.x * s, v.y * s, v.z * s);
	return res;
}

Vector3 operator/(const Vector3 &v, double s)
{
	// Return a new object as a script handle
	Vector3 res(v.x / s, v.y / s, v.z / s);
	return res;
}

//-----------------------
// Swizzle operators
//-----------------------

Vector3 Vector3::get_xyz() const
{
	return Vector3(x,y,z);
}
Vector3 Vector3::get_yzx() const
{
	return Vector3(y,z,x);
}
Vector3 Vector3::get_zxy() const
{
	return Vector3(z,x,y);
}
Vector3 Vector3::get_zyx() const
{
	return Vector3(z,y,x);
}
Vector3 Vector3::get_yxz() const
{
	return Vector3(y,x,z);
}
Vector3 Vector3::get_xzy() const
{
	return Vector3(x,z,y);
}
void Vector3::set_xyz(const Vector3 &v)
{
	x = v.x; y = v.y; z = v.z;
}
void Vector3::set_yzx(const Vector3 &v)
{
	y = v.x; z = v.y; x = v.z;
}
void Vector3::set_zxy(const Vector3 &v)
{
	z = v.x; x = v.y; y = v.z;
}
void Vector3::set_zyx(const Vector3 &v)
{
	z = v.x; y = v.y; x = v.z;
}
void Vector3::set_yxz(const Vector3 &v)
{
	y = v.x; x = v.y; z = v.z;
}
void Vector3::set_xzy(const Vector3 &v)
{
	x = v.x; z = v.y; y = v.z;
}

//-----------------------
// AngelScript functions
//-----------------------

static void Vector3DefaultConstructor(Vector3 *self)
{
	new(self) Vector3();
}

static void Vector3CopyConstructor(const Vector3 &other, Vector3 *self)
{
	new(self) Vector3(other);
}

static void Vector3InitConstructor(double x, double y, double z, Vector3 *self)
{
	new(self) Vector3(x,y,z);
}

//-----------------------
// Generic calling convention
//-----------------------

static void Vector3DefaultConstructor_Generic(asIScriptGeneric *gen)
{
	Vector3 *self = (Vector3*)gen->GetObject();
	new(self) Vector3();
}

static void Vector3CopyConstructor_Generic(asIScriptGeneric *gen)
{
	Vector3 *other = (Vector3*)gen->GetArgObject(0);
	Vector3 *self = (Vector3*)gen->GetObject();
	Vector3CopyConstructor(*other, self);
}

static void Vector3InitConstructor_Generic(asIScriptGeneric *gen)
{
	double x = gen->GetArgDouble(0);
	double y = gen->GetArgDouble(1);
	double z = gen->GetArgDouble(2);
	Vector3 *self = (Vector3*)gen->GetObject();
	Vector3InitConstructor(x,y,z,self);
}

static void Vector3Equal_Generic(asIScriptGeneric *gen)
{
	Vector3 *a = (Vector3*)gen->GetObject();
	Vector3 *b = (Vector3*)gen->GetArgAddress(0);
	bool r = *a == *b;
    *(bool*)gen->GetAddressOfReturnLocation() = r;
}

static void Vector3Length_Generic(asIScriptGeneric *gen)
{
	Vector3 *s = (Vector3*)gen->GetObject();
	gen->SetReturnDouble(s->length());
}

static void Vector3AddAssign_Generic(asIScriptGeneric *gen)
{
	Vector3 *a = (Vector3*)gen->GetArgAddress(0);
	Vector3 *thisPointer = (Vector3*)gen->GetObject();
	*thisPointer += *a;
	gen->SetReturnAddress(thisPointer);
}

static void Vector3SubAssign_Generic(asIScriptGeneric *gen)
{
	Vector3 *a = (Vector3*)gen->GetArgAddress(0);
	Vector3 *thisPointer = (Vector3*)gen->GetObject();
	*thisPointer -= *a;
	gen->SetReturnAddress(thisPointer);
}

static void Vector3MulAssign_Generic(asIScriptGeneric *gen)
{
	double s = gen->GetArgDouble(0);
	Vector3 *thisPointer = (Vector3*)gen->GetObject();
	*thisPointer *= s;
	gen->SetReturnAddress(thisPointer);
}

static void Vector3DivAssign_Generic(asIScriptGeneric *gen)
{
	double s = gen->GetArgDouble(0);
	Vector3 *thisPointer = (Vector3*)gen->GetObject();
	*thisPointer /= s;
	gen->SetReturnAddress(thisPointer);
}

static void Vector3Add_Generic(asIScriptGeneric *gen)
{
	Vector3 *a = (Vector3*)gen->GetObject();
	Vector3 *b = (Vector3*)gen->GetArgAddress(0);
	Vector3 res = *a + *b;
	gen->SetReturnObject(&res);
}

static void Vector3Sub_Generic(asIScriptGeneric *gen)
{
	Vector3 *a = (Vector3*)gen->GetObject();
	Vector3 *b = (Vector3*)gen->GetArgAddress(0);
	Vector3 res = *a - *b;
	gen->SetReturnObject(&res);
}

static void Vector3doubleMulVector3_Generic(asIScriptGeneric *gen)
{
	double s = gen->GetArgDouble(0);
	Vector3 *v = (Vector3*)gen->GetObject();
	Vector3 res = s * *v;
	gen->SetReturnObject(&res);
}

static void Vector3Vector3MulDouble_Generic(asIScriptGeneric *gen)
{
	Vector3 *v = (Vector3*)gen->GetObject();
	double s = gen->GetArgDouble(0);
	Vector3 res = *v * s;
	gen->SetReturnObject(&res);
}

static void Vector3Vector3DivDouble_Generic(asIScriptGeneric *gen)
{
	Vector3 *v = (Vector3*)gen->GetObject();
	double s = gen->GetArgDouble(0);
	Vector3 res = *v / s;
	gen->SetReturnObject(&res);
}

//--------------------------------
// Registration
//-------------------------------------

void RegisterScriptMath3D_Native(asIScriptEngine *engine)
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK | asOBJ_APP_CLASS_ALLFLOATS); assert( r >= 0 );

	// Register the object properties
	r = engine->RegisterObjectProperty("vector3", "double x", asOFFSET(Vector3, x)); assert( r >= 0 );
	r = engine->RegisterObjectProperty("vector3", "double y", asOFFSET(Vector3, y)); assert( r >= 0 );
	r = engine->RegisterObjectProperty("vector3", "double z", asOFFSET(Vector3, z)); assert( r >= 0 );

	// Register the constructors
	r = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT,  "void f()",                     asFUNCTION(Vector3DefaultConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT,  "void f(const vector3 &in)",    asFUNCTION(Vector3CopyConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT,  "void f(double, double y = 0, double z = 0)",  asFUNCTION(Vector3InitConstructor), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	// Register the operator overloads
	r = engine->RegisterObjectMethod("vector3", "vector3 &opAddAssign(const vector3 &in)", asMETHODPR(Vector3, operator+=, (const Vector3 &), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 &opSubAssign(const vector3 &in)", asMETHODPR(Vector3, operator-=, (const Vector3 &), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 &opMulAssign(double)", asMETHODPR(Vector3, operator*=, (double), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 &opDivAssign(double)", asMETHODPR(Vector3, operator/=, (double), Vector3&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "bool opEquals(const vector3 &in) const", asFUNCTIONPR(operator==, (const Vector3&, const Vector3&), bool), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opAdd(const vector3 &in) const", asFUNCTIONPR(operator+, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opSub(const vector3 &in) const", asFUNCTIONPR(operator-, (const Vector3&, const Vector3&), Vector3), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opMul(double) const", asFUNCTIONPR(operator*, (const Vector3&, double), Vector3), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opMul_r(double) const", asFUNCTIONPR(operator*, (double, const Vector3&), Vector3), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opDiv(double) const", asFUNCTIONPR(operator/, (const Vector3&, double), Vector3), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	// Register the object methods
	r = engine->RegisterObjectMethod("vector3", "double length() const", asMETHOD(Vector3,length), asCALL_THISCALL); assert( r >= 0 );

	// Register the swizzle operators
	r = engine->RegisterObjectMethod("vector3", "vector3 get_xyz() const", asMETHOD(Vector3, get_xyz), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_yzx() const", asMETHOD(Vector3, get_yzx), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_zxy() const", asMETHOD(Vector3, get_zxy), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_zyx() const", asMETHOD(Vector3, get_zyx), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_yxz() const", asMETHOD(Vector3, get_yxz), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_xzy() const", asMETHOD(Vector3, get_xzy), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_xyz(const vector3 &in)", asMETHOD(Vector3, set_xyz), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_yzx(const vector3 &in)", asMETHOD(Vector3, set_yzx), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_zxy(const vector3 &in)", asMETHOD(Vector3, set_zxy), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_zyx(const vector3 &in)", asMETHOD(Vector3, set_zyx), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_yxz(const vector3 &in)", asMETHOD(Vector3, set_yxz), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_xzy(const vector3 &in)", asMETHOD(Vector3, set_xzy), asCALL_THISCALL); assert( r >= 0 );
}

void RegisterScriptMath3D_Generic(asIScriptEngine *engine)
{
	int r;

	// Register the type
	r = engine->RegisterObjectType("vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CAK); assert( r >= 0 );

	// Register the object properties
	r = engine->RegisterObjectProperty("vector3", "double x", asOFFSET(Vector3, x)); assert( r >= 0 );
	r = engine->RegisterObjectProperty("vector3", "double y", asOFFSET(Vector3, y)); assert( r >= 0 );
	r = engine->RegisterObjectProperty("vector3", "double z", asOFFSET(Vector3, z)); assert( r >= 0 );

	// Register the constructors
	r = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT, "void f()",                    asFUNCTION(Vector3DefaultConstructor_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT, "void f(const vector3 &in)",   asFUNCTION(Vector3CopyConstructor_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT, "void f(double, double y = 0, double z = 0)", asFUNCTION(Vector3InitConstructor_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Register the operator overloads
	r = engine->RegisterObjectMethod("vector3", "vector3 &opAddAssign(const vector3 &in)", asFUNCTION(Vector3AddAssign_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 &opSubAssign(const vector3 &in)", asFUNCTION(Vector3SubAssign_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 &opMulAssign(double)", asFUNCTION(Vector3MulAssign_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 &opDivAssign(double)", asFUNCTION(Vector3DivAssign_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "bool opEquals(const vector3 &in) const", asFUNCTION(Vector3Equal_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opAdd(const vector3 &in) const", asFUNCTION(Vector3Add_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opSub(const vector3 &in) const", asFUNCTION(Vector3Sub_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opMul_r(double) const", asFUNCTION(Vector3doubleMulVector3_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opMul(double) const", asFUNCTION(Vector3Vector3MulDouble_Generic), asCALL_GENERIC); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 opDiv(double) const", asFUNCTION(Vector3Vector3DivDouble_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Register the object methods
	r = engine->RegisterObjectMethod("vector3", "double length() const", asFUNCTION(Vector3Length_Generic), asCALL_GENERIC); assert( r >= 0 );

	// Register the swizzle operators
/*
	r = engine->RegisterObjectMethod("vector3", "vector3 get_xyz() const", asFUNCTION(Vector3_get_xyz_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_yzx() const", asFUNCTION(Vector3_get_yzx_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_zxy() const", asFUNCTION(Vector3_get_zxy_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_zyx() const", asFUNCTION(Vector3_get_zyx_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_yxz() const", asFUNCTION(Vector3_get_yxz_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "vector3 get_xzy() const", asFUNCTION(Vector3_get_xzy_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_xyz(const vector3 &in)", asFUNCTION(Vector3_set_xyz_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_yzx(const vector3 &in)", asFUNCTION(Vector3_set_yzx_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_zxy(const vector3 &in)", asFUNCTION(Vector3_set_zxy_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_zyx(const vector3 &in)", asFUNCTION(Vector3_set_zyx_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_yxz(const vector3 &in)", asFUNCTION(Vector3_set_yxz_Generic), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("vector3", "void set_xzy(const vector3 &in)", asFUNCTION(Vector3_set_xzy_Generic), asCALL_THISCALL); assert( r >= 0 );
*/
}

void RegisterScriptMath3D(asIScriptEngine *engine)
{
	if( strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY") )
		RegisterScriptMath3D_Generic(engine);
	else
		RegisterScriptMath3D_Native(engine);
}

END_AS_NAMESPACE


