// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor2D.h"
#include "MovementState.h"
#include "BaseTurret.generated.h"

UCLASS(HideCategories=("Actor Tick", Rendering, Replication, Input, Actor, Collision, LOD, Cooking))
class PROJECT_BATTLECITY__API ABaseTurret : public AActor2D
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category="BlackBox|Appearance")
	TMap<EMovementState, class UPaperFlipBook*> AnimationByMovementState;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|SoundEffects")
	class USoundCue* ShootingCue = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Projectile")
	float ProjectileSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Projectile")
	TSubclassOf<class ABaseProjectile> ProjectileClass = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Projectile")
	FString ProjectileSocketName = "Shell";
};
