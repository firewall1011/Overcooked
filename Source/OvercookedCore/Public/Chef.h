// Copyright (c) 2023 Tiago Marino Silva

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Item.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Chef.generated.h"

UCLASS()
class OVERCOOKEDCORE_API AChef : public ACharacter
{
	GENERATED_BODY()

public:
	AChef();

protected:
	virtual void BeginPlay() override;

	virtual void SearchAndGrabItem();

	virtual void Move(const FInputActionValue& InputValue);

	virtual bool CanGrab(AItem* Item) const;

	UFUNCTION(Server, Reliable)
	virtual void ServerHandleGrab(AItem* Item);

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleGrab(AItem* Item);

	UFUNCTION(Server, Reliable)
	virtual void ServerReleaseItem();

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastReleaseItem();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* InputActionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* InputActionGrab;
	
	UPROPERTY(VisibleAnywhere, Category = "Item")
	AItem* HeldItem;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FName ItemSocketName;
};