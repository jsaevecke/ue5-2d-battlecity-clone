// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn2D.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "BattleCityPlayerController.h"
#include "Engine/World.h"
#include "HealthComponent.h"

APawn2D::APawn2D()
{
	/* TESTING */
	AIControllerClass = nullptr;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	/////////////

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	BoxComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	BoxComponent->SetConstraintMode(EDOFMode::XZPlane);
	BoxComponent->SetCollisionProfileName(FName("BlockAllDynamic"));
	SetRootComponent(BoxComponent);

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("FlipBookComponent"));
	FlipbookComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	FlipbookComponent->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
}

void APawn2D::BeginPlay() 
{
	UpdateStates();
}

void APawn2D::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAxis("Up&Down", this, &APawn2D::Move_YAxis);
	InputComponent->BindAxis("Left&Right", this, &APawn2D::Move_XAxis);
}

void APawn2D::Move(const FVector Direction, const float Scale)
{
	const auto DeltaSeconds = GetWorld()->GetDeltaSeconds();

	Velocity = Direction * Scale * Speed * DeltaSeconds;
	IsMoving = Velocity.SizeSquared() > 0.f;

	const auto NewPosition = GetActorLocation() + Velocity;

	UpdateStates();

	SetActorLocation(NewPosition, true);
}

void APawn2D::Move_XAxis(const float AxisValue)
{
	const auto RoundedAxisValue = FMath::RoundToInt(AxisValue);

	if (!IsHorizontalAxisProcessing)
	{
		IsVerticalAxisProcessing = RoundedAxisValue != 0;

		if (!IsHorizontalAxisProcessing)
		{ 
			Move(FVector(1.f, 0.f, 0.f), RoundedAxisValue);
		}
	}
}

void APawn2D::Move_YAxis(const float AxisValue)
{
	const auto RoundedAxisValue = FMath::RoundToInt(AxisValue);

	if (!IsVerticalAxisProcessing)
	{
		IsHorizontalAxisProcessing = RoundedAxisValue != 0;

		if (!IsVerticalAxisProcessing)
		{
			Move(FVector(0.f, 0.f, 1.f), RoundedAxisValue);
		}
	}
}

void APawn2D::UpdateStates()
{
	const auto LastMovementState = MovementState;

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

	if (LastMovementState != MovementState)
		MovementStateChangedDelegate.Broadcast(MovementState);

	if (AnimationByMovementState.Contains(MovementState))
	{
		const auto Flipbook = AnimationByMovementState[MovementState];
		FlipbookComponent->SetFlipbook(Flipbook);
	}
}
