// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn2D.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "BattleCityPlayerController.h"
#include "Engine/World.h"
#include "HealthComponent.h"

// Sets default values
APawn2D::APawn2D()
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	Body = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("Body"));
	Health = CreateDefaultSubobject<UHealthComponent>(FName("Health"));

	Body->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SetRootComponent(Collider);
}

void APawn2D::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAxis("Up&Down", this, &APawn2D::Move_YAxis);
	InputComponent->BindAxis("Left&Right", this, &APawn2D::Move_XAxis);
}

void APawn2D::Move(FVector direction, float scale)
{
	auto deltaSeconds = GetWorld()->GetDeltaSeconds();

	Velocity = direction * scale * Speed * deltaSeconds;
	IsMoving = Velocity.SizeSquared() > 0.f;

	auto newPosition = GetActorLocation() + Velocity;

	UpdateStates();

	SetActorLocation(newPosition, true);
}

void APawn2D::Move_XAxis(float AxisValue)
{
	auto roundedAxisValue = FMath::RoundToInt(AxisValue);

	if (!IsHorizontalAxisProcessing)
	{
		IsVerticalAxisProcessing = roundedAxisValue != 0;

		if (!IsHorizontalAxisProcessing)
		{ 
			Move(FVector(0.f, 0.f, 1.f), roundedAxisValue);
		}
	}
}

void APawn2D::Move_YAxis(float AxisValue)
{
	auto roundedAxisValue = FMath::RoundToInt(AxisValue);

	if (!IsVerticalAxisProcessing)
	{
		IsHorizontalAxisProcessing = roundedAxisValue != 0;

		if (!IsVerticalAxisProcessing)
		{
			Move(FVector(0.f, 0.f, 1.f), roundedAxisValue);
		}
	}
}

void APawn2D::UpdateStates()
{
	auto lastMovementState = MovementState;

	if (IsMoving)
	{
		if (Velocity.X > 0.f)
		{
			ForwardDirection = FVector(1.f, 0.f, 0.f);
			ForwardState = EForwardState::Right;
			MovementState = EMovementState::RightMovement;
		}
		else if (Velocity.X < 0.f)
		{
			ForwardDirection = FVector(-1.f, 0.f, 0.f);
			ForwardState = EForwardState::Left;
			MovementState = EMovementState::LeftMovement;
		}
		else if (Velocity.Z > 0.f)
		{
			ForwardDirection = FVector(0.f, 0.f, 1.f);
			ForwardState = EForwardState::Up;
			MovementState = EMovementState::UpMovement;
		}
		else if (Velocity.Z < 0.f)
		{
			ForwardDirection = FVector(0.f, 0.f, -1.f);
			ForwardState = EForwardState::Down;
			MovementState = EMovementState::DownMovement;
		}
	}
	else
	{
		switch (ForwardState)
		{
		case EForwardState::Right:
			MovementState = EMovementState::RightIdle;
			break;
		case EForwardState::Left:
			MovementState = EMovementState::LeftIdle;
			break;
		case EForwardState::Up:
			MovementState = EMovementState::UpIdle;
			break;
		case EForwardState::Down:
			MovementState = EMovementState::DownIdle;
			break;
		default:
			break;
		}
	}

	if (lastMovementState != MovementState)
		MovementStateChangedDelegate.Broadcast(MovementState);
}
