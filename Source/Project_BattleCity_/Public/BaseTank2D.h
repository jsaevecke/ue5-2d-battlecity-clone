// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn2D.h"
#include "BaseTank2D.generated.h"

UCLASS(HideCategories=("Actor Tick", Pawn, Camera, Rendering, Replication, Input, Actor, Collision, Cooking, LOD))
class PROJECT_BATTLECITY__API ABaseTank2D : public APawn2D
{
	GENERATED_BODY()
public:
	ABaseTank2D();

protected:
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UPROPERTY()
	class UAudioComponent* Motor = nullptr;
	UPROPERTY()
	class UTimelineComponent* MotorTimeline = nullptr;

	UPROPERTY()
	class ABaseTurret* Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Turret")
	TSubclassOf<class ABaseTurret> TurretClass = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Turret")
	FString TurretSocket = "Turret";

	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|SoundEffects")
	class UCurveFloat* MotorPitchCurve = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|SoundEffects")
	class USoundCue* MotorCue = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|SoundEffects")
	class USoundCue* HitCue = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|SoundEffects")
	class USoundCue* ExplosionCue = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|SoundEffects")
	class USoundCue* RepairCue = nullptr;
};
