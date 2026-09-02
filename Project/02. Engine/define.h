#pragma once
#include "SimpleMath.h"

#define SINGLE(className) public: \
						static className* GetInst() \
						{\
							static className mgr;\
							return &mgr;\
						}\
						private:\
							className();\
							~className();

#define DT CTimeMgr::GetInst()->DeltaTime()

#define CLONE(type) virtual type* Clone(){return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone(){assert(nullptr); return nullptr;}

#define RET_SUCCESS 1
#define RET_FAILED  -1

#define SAFE_DELETE(p) if(NULL != p){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(NULL != p){p->Release(); p = NULL;}

#define WINCX	1280.f
#define WINCY	720.f

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define RENDERTARGET_NUM 1

#define PI  3.141592
#define RAD PI/180


#define KEY(type, state) CKeyMgr::GetInst()->GetKeyState(type, state)
#define KEYHOLD(type) CKeyMgr::GetInst()->GetKeyState(type, KEY_STATE::HOLD)
#define KEYAWAY(type) CKeyMgr::GetInst()->GetKeyState(type, KEY_STATE::AWAY)
#define KEYTAB(type) CKeyMgr::GetInst()->GetKeyState(type, KEY_STATE::TAB)

#define MAX_LAYER 32

typedef DirectX::SimpleMath::Vector2 Vec2;
typedef DirectX::SimpleMath::Vector3 Vec3;
typedef DirectX::SimpleMath::Vector4 Vec4;

using namespace DirectX::SimpleMath;

enum class BUTTON_CHAPTER
{
	NONE,
	NEXUS,
	GATEWAY,
	ROBOTICS,
	STARGATE,
	PROBE_BASE,
	PROBE_LBUILD,
	PROBE_HBUILD,
	ATT_UNIT,
	NATT_UNIT,
	NORMAL_BASE,
	END,
};

enum class BUILD_LEVEL
{
	GATEWAY_LEVEL,
	FORGE_LEVEL,
	ROBOTICS_LEVEL,
	STARGATE_LEVEL,
	ADUN_LEVEL,
	OBSERVATORY_LEVEL,
	SUPPORTBAY_LEVEL,
	BEACON_LEVEL,
	ARBITER_LEVEL,
	CORE_LEVEL,
	ARCHIEVE_LEVEL,
};

enum class NUMBER_TYPE
{
	NONE,
	GAS,
	MINERAL,
	HP,
	SHIELD,
	MP,
};

enum class SKILL
{
	NONE,
	WAP,
	CONFUSION,
	FEEDBACK,
	MINDCONTROL,
	STORM,
	RECALL,
	STASISFIELD,
	DARKARCHONCOALESCENCE,
	ARCHONCOALESCENCE,
	ILLUSION,
};

enum class UNIT_TYPE
{
	PROBE,
	ZEALOT,
	DRAGOON,
	HIGHTEMPLAR,
	DARKTEMPLAR,
	ARCHON,
	DARKARCHON,
	SHUTTLE,
	OBSERVER,
	REAVER,
	CORSAIR,
	CARRIER,
	ARBITER,
	SCOUT,
	INTERCEPTOR,
	END,
};


// 유닛 상태
enum class UNIT_STATUS
{
	IDLE,
	MOVE,
	MINING,
	ATTACK,
	DIE,
	STORM,
	RECALL,
	FROZEN,
	END,
};

enum class ANIMATION_TYPE
{
	UINT,
	BUINDING,
	GAUGE,
	EFFECT,
	END,
};

enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
	END,
};

enum class BULLET_TYPE
{
	NORMAL,
	GUIDED,
	TARGETING,
	END,

};

enum class MONSTER_DIR
{
	LEFT,
	RIGHT,
	END,
};

enum class KEY_TYPE
{
	KEY_1 = 0,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,

	KEY_CTRL,
	KEY_ALT,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_TAB,
	KEY_CAP,
	KEY_ENTER,
	KEY_ESC,
	KEY_SPACE,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,

	KEY_NUM1,
	KEY_NUM2,
	KEY_NUM3,
	KEY_NUM4,
	KEY_NUM5,
	KEY_NUM6,
	KEY_NUM7,
	KEY_NUM8,
	KEY_NUM9,
	KEY_NUM0,

	KEY_LBTN,
	KEY_RBTN,

	END,
};

enum class OBJ_TYPE
{
	NONE,
	UI,
	AIRUNIT,
	GROUNDUNIT,
	RESOURCE,
	BUILDING,
	END,
};

enum class KEY_STATE
{
	TAB,	// 최초 눌린 시점
	HOLD,   // 누르고 있는 중
	AWAY,   // 키를 막 뗀 시점
	NONE,   // 안눌림	
};

enum class COMPONENT_TYPE
{
	TRANSFORM,
	MESHRENDER,
	COLLIDER,
	CAMERA,
	ANIMATOR2D,
	ANIMATOR3D,
	GRID,
	//LIGHT,
	//
	END,
	SCRIPT,
};

enum class COMPONENT_DLG
{
	TRANSFORM,
	MESHRENDER,
	COLLIDER,
	CAMERA,
	ANIMATOR2D,
	ANIMATOR3D,
	//
	GRID,
	SCRIPT,
	LAYER,
	END,
};

enum SHADER_TYPE
{
	ST_VERTEX = 0x01,
	ST_HULL = 0x02,
	ST_DOMAIN = 0x04,
	ST_GEOMETRY = 0x08,
	ST_COMPUTE = 0x10,
	ST_PIXEL = 0x20,
};

enum class RESOURCE_TYPE
{
	MESH,
	TEXTURE,
	MATERIAL,
	SOUND,
	PREFAB,
	END,
};

enum class EVENT_TYPE
{
	ADD_CHILD,
	DISCONNECT_PARENT,
	DELETE_OBJECT,
	CREATE_OBJECT,
	CHANGE_RESOLUTION, // 카메라 컴포넌트
	RENEWAL,
	END,
};

enum class BLEND_TYPE
{
	NONE, // 기본
	ALPHABLEND,
	ALPHA_TO_COVERAGE, // 나뭇잎, 나무가지 같은 것들
	END,
};

enum class DEPTH_STENCIL_TYPE
{
	LESS, // 기본
	LESS_EQUAL,
	END,
};

enum class SHADER_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,
	INT_END,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,
	FLOAT_END,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,
	VEC2_END,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,
	VEC4_END,

	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,
	TEX_END,

	END,
};

enum class COLLIDER_TYPE
{
	COLLIDER_2D_BOX,
	COLLIDER_2D_CIRCLE,
	COLLIDER_3D_CUBE,
	COLLIDER_3D_SPHERE,
	END,
};

// 시계방향 -> 전면
// 반시계 방향 -> 후면
enum class RASTERIZER_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIREFRAME, // CULL_NONE 상태에서 해야 물체의 모든것이 보임
	END,
};


enum class LIGHT_TYPE
{
	DIRECTION,
	POINT,
	SPOT,
	END,
};
