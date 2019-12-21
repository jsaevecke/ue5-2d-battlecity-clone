// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTurret.h"
#include "PaperFlipbookComponent.h"

void ABaseTurret::Shoot(FVector direction)
{

}

void ABaseTurret::UpdateStates(EMovementState movementState)
{
	if (AnimationByMovementState.Contains(movementState))
	{
		FlipbookComponent->SetFlipbook(AnimationByMovementState[movementState]);
	}
}
