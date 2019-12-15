// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovementState.h"
#include "ForwardState.h"
#include "Pawn2D.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovementStateChangedDelegate, const EMovementState, MovementState);

UCLASS()
class PROJECT_BATTLECITY__API APawn2D : public APawn
{
	GENERATED_BODY()
public:
	APawn2D();

	UFUNCTION(BlueprintCallable, Category="BlackBox|Movement")
	void Move(const FVector direction, const float scale);

protected:
	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Movement")
	void UpdateStates();
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Movement")
	void Move_XAxis(float AxisValue);
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Movement")
	void Move_YAxis(float AxisValue);

protected:
	UPROPERTY()
	class UBoxComponent* BoxComponent = nullptr;
	UPROPERTY()
	class UPaperFlipbookComponent* FlipbookComponent = nullptr;
	UPROPERTY(VisibleAnywhere, meta = (ExposeFunctionCategories = "BlackBox|Health", AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent = nullptr;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Events")
	FMovementStateChangedDelegate MovementStateChangedDelegate;

	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Appearance")
	TMap<EMovementState, class UPaperFlipbook*> AnimationByMovementState;

	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Movement")
	float Speed = 50.f;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	bool IsMoving = false;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	bool IsHorizontalAxisProcessing = false;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	bool IsVerticalAxisProcessing = false;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	FVector ForwardDirection = FVector(0.f, 0.f, 1.f);
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	FVector Velocity = FVector(0.f, 0.f, 0.f);
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	EMovementState MovementState = EMovementState::UpIdle;
	UPROPERTY(BlueprintReadOnly, Category = "BlackBox|Movement")
	EForwardState ForwardState = EForwardState::Up;
};
