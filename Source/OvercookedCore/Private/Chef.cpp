// Copyright (c) 2023 Tiago Marino Silva


#include "Chef.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


AChef::AChef(): InputMapping(nullptr), InputActionMove(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AChef::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChef::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChef::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AChef::Move);
}

void AChef::Move(const FInputActionValue& InputValue)
{
	if (Controller == nullptr)
		return;
	
	const FVector2D MoveValue = InputValue.Get<FVector2D>();
	const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
 
	MoveVertically(MoveValue.Y, MovementRotation);
	MoveHorizontally(MoveValue.X, MovementRotation);
}

void AChef::MoveVertically(const double MoveValue, const FRotator& MovementRotation)
{
	if (MoveValue != 0.f)
	{
		const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
 
		AddMovementInput(Direction, MoveValue);
	}
}

void AChef::MoveHorizontally(const double MoveValue, const FRotator& MovementRotation)
{
	if (MoveValue != 0.f)
	{
		const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
	
		AddMovementInput(Direction, MoveValue);
	}
}

