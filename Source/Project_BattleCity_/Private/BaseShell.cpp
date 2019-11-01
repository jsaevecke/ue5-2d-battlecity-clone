// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShell.h"

// Sets default values
ABaseShell::ABaseShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseShell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

