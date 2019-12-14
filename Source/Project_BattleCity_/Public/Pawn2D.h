// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pawn2D.generated.h"

//Description(Tooltip), Category, ReadWritePermission
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

UENUM(BlueprintType)
enum class EForwardState : uint8
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovementStateChangedDelegate, const EMovementState, MovementState);

UCLASS()
class PROJECT_BATTLECITY__API APawn2D : public APawn
{
	GENERATED_BODY()
public:
	APawn2D();

	UFUNCTION(BlueprintCallable, Category="BlackBox|Pawn2d|Movement")
	void Move(const FVector direction, const float scale);

protected:
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Pawn2d|Movement")
	void UpdateStates();
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Pawn2d|Movement")
	void Move_XAxis(float AxisValue);
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Pawn2d|Movement")
	void Move_YAxis(float AxisValue);

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Pawn2D|Events")
	FMovementStateChangedDelegate MovementStateChangedDelegate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBox|Pawn2D|Movement")
	float Speed = 50.f;

protected:
	//UPROPERTIES + Categories
	UPROPERTY(BlueprintReadWrite, Category = "BlackBox|Pawn2D|Appearance")
	class UBoxComponent* Collider = nullptr;
	UPROPERTY(BlueprintReadWrite, Category="BlackBox|Pawn2D|Appearance")
	class UPaperFlipbookComponent* Body = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "BlackBox|Pawn2D|Health")
	class UHealthComponent* Health = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	bool IsMoving = false;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	bool IsHorizontalAxisProcessing = false;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	bool IsVerticalAxisProcessing = false;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	FVector ForwardDirection = FVector(0.f, 0.f, 1.f);
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	FVector Velocity = FVector(0.f, 0.f, 0.f);
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	EMovementState MovementState = EMovementState::UpIdle;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Pawn2D|Movement")
	EForwardState ForwardState = EForwardState::Up;

};
