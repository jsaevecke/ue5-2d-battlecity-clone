// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor2D.h"
#include "BaseProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_BATTLECITY__API ABaseProjectile : public AActor2D
{
	GENERATED_BODY()
public:
	ABaseProjectile();

protected:
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, meta = (ExposeFunctionCategories = "BlackBox|Health", AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent = nullptr;
};
