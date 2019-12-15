// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank2D.h"

ABaseTank2D::ABaseTank2D() {
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ABaseTank2D::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}