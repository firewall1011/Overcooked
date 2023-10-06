#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FOvercookedCore : public IModuleInterface
{
public:
    static inline FOvercookedCore& Get()
    {
        return FModuleManager::LoadModuleChecked<FOvercookedCore>("OvercookedCore");
    }
    
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("OvercookedCore");
    }
    
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};