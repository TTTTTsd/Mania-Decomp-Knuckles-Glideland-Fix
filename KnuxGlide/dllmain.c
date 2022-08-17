#include "../GameAPI/C/GameAPI/Game.h"
#include "Objects/Player.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void) { 
Player_Action_Spindash = Mod.GetPublicFunction(NULL, "Player_Action_Spindash");
Player_Action_Jump = Mod.GetPublicFunction(NULL, "Player_Action_Jump");
Player_State_Ground = Mod.GetPublicFunction(NULL, "Player_State_Ground");
Player_State_KnuxGlideDrop = Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideDrop");
Player_State_KnuxGlideLeft = Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideLeft");
Player_State_KnuxGlideRight = Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideRight");
Player_Input_P2_AI          = Mod.GetPublicFunction(NULL, "Player_Input_P2_AI");
Mod.RegisterStateHook(Player_State_KnuxGlideDrop,Player_State_KnuxGlideDrop_Hook, false);
MOD_REGISTER_OBJECT_HOOK(Player);
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif