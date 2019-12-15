#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	CheckHealth();
}

void UHealthComponent::ModifyHealthpoints(int amount, EHealthModificationType type)
{
	if (!ValidModificationTypes.Contains(type) || amount == 0 || IsIndestructible)
		return;

	if (type == EHealthModificationType::Heal)
	{
		CurrentHealthpoints += amount;
	}
	else
	{
		CurrentHealthpoints -= amount;
	}

	HealthModificationDelegate.Broadcast(CurrentHealthpoints, MaxHealthpoints, type);

	CheckHealth();
}

void UHealthComponent::SetCurrentHealthpoints(int healthpoints)
{
	CurrentHealthpoints = healthpoints;

	CheckHealth();
}

void UHealthComponent::CheckHealth() {
	CurrentHealthpoints = FMath::Clamp(CurrentHealthpoints, 0, MaxHealthpoints);

	if (CurrentHealthpoints <= 0)
		HealthIsDepletedDelegate.Broadcast();
}




