// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank2D.h"
#include "BattleCityPlayerController.h"
#include "BaseTurret.h"
#include "PaperFlipbookComponent.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/TimelineComponent.h"

ABaseTank2D::ABaseTank2D() : APawn2D()
{
	Motor = CreateDefaultSubobject<UAudioComponent>(FName("MotorSFX"));
	MotorTimeline = CreateDefaultSubobject<UTimelineComponent>(FName("MotorTimeline"));
}

void ABaseTank2D::BeginPlay()
{
	Super::BeginPlay();

	SetupTurret();

	if (IsValid(MotorCue))
	{
		Motor->SetSound(MotorCue);

		if (IsValid(MotorPitchCurve))
		{
			MotorTimeline->SetFloatCurve(MotorPitchCurve, FName("Pitch"));

			float Min, Max;
			MotorPitchCurve->GetTimeRange(Min, Max);

			const auto TimelineLength = Max - Min;

			MotorTimeline->SetTimelineLength(TimelineLength);
		}

		Motor->Play();
	}
}

void ABaseTank2D::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Shoot", IE_Pressed, this, &ABaseTank2D::Shoot);
}

void ABaseTank2D::SetupTurret() 
{
	if (FlipbookComponent->DoesSocketExist(TurretSocket))
	{
		auto SocketLocation = FlipbookComponent->GetSocketLocation(TurretSocket);

		Turret = Cast<ABaseTurret>(GetWorld()->SpawnActor(TurretClass, &SocketLocation));

		if (IsValid(Turret))
		{
			const auto AttachmentRules = FAttachmentTransformRules(
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::KeepRelative,
				EAttachmentRule::KeepRelative,
				true);

			Turret->AttachToComponent(FlipbookComponent, AttachmentRules);
			Turret->SetActorRelativeLocation(FVector(0.f, 1.f, 0.f));
			Turret->UpdateStates(MovementState);
		}
	}
}

void ABaseTank2D::OnHealthIsDepleted()
{
	if (IsValid(ExplosionCue))
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionCue, GetActorLocation());
	}

	if (IsValid(Turret))
	{
		Turret->Destroy();
	}

	Destroy();
}

void ABaseTank2D::OnHealthModified(int CurrentHealthPoints, int MaxHealthPoints, EHealthModificationType Type) const
{
	if (Type != EHealthModificationType::Heal)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitCue, GetActorLocation());
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, RepairCue, GetActorLocation());
	}
}

auto ABaseTank2D::OnMovementStateChanged(const EMovementState NewMovementState) const -> void
{
	if (IsValid(Turret))
	{
		Turret->UpdateStates(NewMovementState);
	}

	if (IsMoving)
	{
		//TODO: MOTOR PITCH UPDATE
	}
}

void ABaseTank2D::Shoot()
{
	if (IsValid(Turret))
	{
		Turret->Shoot(ForwardDirection);
	}
}
