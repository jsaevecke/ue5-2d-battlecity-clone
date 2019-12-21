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

	SetupEvents();

	if (IsValid(MotorCue))
	{
		Motor->SetSound(MotorCue);

		if (IsValid(MotorPitchCurve))
		{
			MotorTimeline->SetFloatCurve(MotorPitchCurve, FName("Pitch"));

			float min, max;
			MotorPitchCurve->GetTimeRange(min, max);

			auto timelineLength = max - min;

			MotorTimeline->SetTimelineLength(timelineLength);
		}

		Motor->Play();
	}
}

void ABaseTank2D::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ABaseTank2D::Shoot);
}

void ABaseTank2D::SetupTurret() 
{
	if (FlipbookComponent->DoesSocketExist(TurretSocket))
	{
		auto socketLocation = FlipbookComponent->GetSocketLocation(TurretSocket);

		Turret = Cast<ABaseTurret>(GetWorld()->SpawnActor(TurretClass, &socketLocation));

		if (IsValid(Turret))
		{
			auto attachementRules = FAttachmentTransformRules(
				EAttachmentRule::SnapToTarget,
				EAttachmentRule::KeepRelative,
				EAttachmentRule::KeepRelative,
				true);

			Turret->AttachToComponent(FlipbookComponent, attachementRules);
		}
	}
}

void ABaseTank2D::SetupEvents()
{
	//MovementStateChangedDelegate.AddDynamic(this, &ABaseTank2D::OnMovementStateChanged);
	
	//HealthComponent->HealthIsDepletedDelegate.AddDynamic(this, &ABaseTank2D::OnHealthIsDepleted);
	//HealthComponent->HealthModificationDelegate.AddDynamic(this, &ABaseTank2D::OnHealthModified);
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

void ABaseTank2D::OnHealthModified(int currentHealthpoints, int maxHealthpoints, EHealthModificationType type)
{
	if (type != EHealthModificationType::Heal)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitCue, GetActorLocation());
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(this, RepairCue, GetActorLocation());
	}
}

void ABaseTank2D::OnMovementStateChanged(const EMovementState newMovementState)
{
	if (IsValid(Turret))
	{
		Turret->UpdateStates(newMovementState);
	}

	if (IsMoving)
	{
		//Motor->
	}
}

void ABaseTank2D::Shoot()
{
	if (IsValid(Turret))
	{
		Turret->Shoot(ForwardDirection);
	}
}