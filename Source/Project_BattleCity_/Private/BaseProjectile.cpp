// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "HealthComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

ABaseProjectile::ABaseProjectile() : AActor2D()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	BoxComponent->SetEnableGravity(false);
	BoxComponent->SetConstraintMode(EDOFMode::XZPlane);
	BoxComponent->SetCollisionProfileName(FName("BlockAllDynamic"));
}
