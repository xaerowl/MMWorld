// Fill out your copyright notice in the Description page of Project Settings.

#include "MMWorld.h"
#include "InventoryItem.h"
#include "MMWorldCharacter.h"

// Sets default values
AInventoryItem::AInventoryItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInventoryItem::EnterInventory(class AMMWorldCharacter* NewOwningPawn)
{
	ActiveTrigger->SetActive(false);
	SetOwner(NewOwningPawn);

	GetRootComponent()->SetHiddenInGame(true, true);

	NewOwningPawn->BindToItemsDummyNode(this);
	GetRootComponent()->SetRelativeTransform(FTransform::Identity);
}

void AInventoryItem::LeaveInventory(class AMMWorldCharacter* NewOwningPawn)
{
	ActiveTrigger->SetActive(true);
	SetOwner(nullptr);

	GetRootComponent()->SetHiddenInGame(false, true);

	NewOwningPawn->UnbindToItemsDummyNode(this);
}

void AInventoryItem::OnStartUse_Implementation()
{
	if (TouchedCharacter.IsValid())
	{
		TouchedCharacter->PickupItem(this);
	}
}
