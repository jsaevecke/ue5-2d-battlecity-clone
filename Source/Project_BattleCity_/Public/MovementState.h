// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	UpIdle UMETA(DisplayName = "UpIdle"),
	DownIdle UMETA(DisplayName = "DownIdle"),
	LeftIdle UMETA(DisplayName = "LeftIdle"),
	RightIdle UMETA(DisplayName = "RightIdle"),
	UpMovement UMETA(DisplayName = "UpMovement"),
	DownMovement UMETA(DisplayName = "DownMovement"),
	LeftMovement UMETA(DisplayName = "LeftMovement"),
	RightMovement UMETA(DisplayName = "RightMovement")
};
