// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurret.h"
#include "PaperFlipbookComponent.h"

ABaseTurret::ABaseTurret() : AActor2D()
{
}

void ABaseTurret::Shoot(FVector Direction)
{

}

void ABaseTurret::UpdateStates(const EMovementState MovementState)
{
	if (AnimationByMovementState.Contains(MovementState))
	{
		FlipBookComponent->SetFlipbook(AnimationByMovementState[MovementState]);
	}
}
