// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor2D.generated.h"

UCLASS()
class PROJECT_BATTLECITY__API AActor2D : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor2D();

protected:
	UPROPERTY()
	class UBoxComponent* BoxComponent = nullptr;
	UPROPERTY()
	class UPaperFlipbookComponent* FlipBookComponent = nullptr;
};
