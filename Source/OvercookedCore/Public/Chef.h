// Copyright (c) 2023 Tiago Marino Silva

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "Chef.generated.h"

UCLASS()
class OVERCOOKEDCORE_API AChef : public ACharacter
{
	GENERATED_BODY()

public:
	AChef();

protected:
	virtual void BeginPlay() override;
	virtual void Move(const FInputActionValue& InputValue);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputActionMove;

private:
	void MoveVertically(const double MoveValue, const FRotator& MovementRotation);
	void MoveHorizontally(const double MoveValue, const FRotator& MovementRotation);
};