// Copyright (c) 2023 Tiago Marino Silva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class OVERCOOKEDCORE_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Grab(USkeletalMeshComponent* ParentMesh, const FName& SocketName);
	virtual void Release();
};
