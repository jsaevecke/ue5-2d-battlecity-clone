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
	BoxComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	BoxComponent->SetConstraintMode(EDOFMode::XZPlane);
	BoxComponent->SetCollisionProfileName(FName("BlockAllDynamic"));
	SetRootComponent(BoxComponent);
	
	FlipBookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("FlipBookComponent"));
	FlipBookComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	FlipBookComponent->SetupAttachment(GetRootComponent());
}

