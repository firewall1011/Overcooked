// Copyright (c) 2023 Tiago Marino Silva

#include "Chef.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

AChef::AChef(): InputMapping(nullptr), InputActionMove(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	
	UCharacterMovementComponent* const CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->SetMovementMode(MOVE_Walking);
	CharacterMovementComponent->bOrientRotationToMovement = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AChef::BeginPlay()
{
	Super::BeginPlay();
}

void AChef::SearchAndGrabItem()
{
	TArray<AActor*> OverlappingItems;
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	const TArray<AActor*> ActorsToIgnore;

	const bool bHasOverlapItem = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),GetActorLocation(), 100.f,
		ObjectTypes, AItem::StaticClass(), ActorsToIgnore, OverlappingItems);

	if (bHasOverlapItem)
	{
		AItem* Item = Cast<AItem>(OverlappingItems[0]);
		if (CanGrab(Item))
		{
			HandleGrab(Item);
		}
		else if (Item == HeldItem)
		{
			Release();
		}
	}
	else
	{
		Release();
	}
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
	Input->BindAction(InputActionGrab, ETriggerEvent::Triggered, this, &AChef::SearchAndGrabItem);
}

void AChef::Move(const FInputActionValue& InputValue)
{
	if (Controller == nullptr)
		return;
	
	const FVector2D MoveValue = InputValue.Get<FVector2D>();

	if (MoveValue.Y != 0.f)
	{
		const FVector Direction = FVector::ForwardVector;
		AddMovementInput(Direction, MoveValue.Y);
	}
	
	if (MoveValue.X != 0.f)
	{
		const FVector Direction = FVector::RightVector;
		AddMovementInput(Direction, MoveValue.X);
	}
}

bool AChef::CanGrab(AItem* Item) const
{
	return !HeldItem;
}

void AChef::HandleGrab(AItem* Item)
{
	HeldItem = Item;
	HeldItem->Grab(GetMesh(), ItemSocketName);
}

void AChef::Release()
{
	if (!HeldItem)
	{
		return;
	}

	HeldItem->Release();
	HeldItem = nullptr;
}
