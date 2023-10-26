// Copyright (c) 2023 Tiago Marino Silva


#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
	SetReplicatingMovement(true);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::Grab(USkeletalMeshComponent* ParentMesh, const FName& SocketName)
{
	const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(ParentMesh, AttachmentTransformRules, SocketName);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem::Release()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

