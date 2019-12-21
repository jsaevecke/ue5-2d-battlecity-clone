// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor2D.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AActor2D::AActor2D()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("FlipbookComponent"));

	BoxComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	FlipbookComponent->PrimaryComponentTick.bStartWithTickEnabled = false;

	SetRootComponent(BoxComponent);

	FlipbookComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

