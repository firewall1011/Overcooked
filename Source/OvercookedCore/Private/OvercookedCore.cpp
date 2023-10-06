#include "OvercookedCore.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FOvercookedCore::StartupModule()
{
    UE_LOG(LogOvercookedCore, Log, TEXT("Overcooked module starting up"));
}

void FOvercookedCore::ShutdownModule()
{
    UE_LOG(LogOvercookedCore, Log, TEXT("Overcooked module shuting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FOvercookedCore, OvercookedCore, "OvercookedCore");
