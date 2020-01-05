#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	CheckHealth();
}

void UHealthComponent::ModifyHealthPoints(const int Amount, const EHealthModificationType Type)
{
	if (!ValidModificationTypes.Contains(Type) || Amount == 0 || IsIndestructible)
		return;

	if (Type == EHealthModificationType::Heal)
	{
		CurrentHealthPoints += Amount;
	}
	else
	{
		CurrentHealthPoints -= Amount;
	}

	HealthModificationDelegate.Broadcast(CurrentHealthPoints, MaxHealthPoints, Type);

	CheckHealth();
}

void UHealthComponent::SetCurrentHealthPoints(const int HealthPoints)
{
	CurrentHealthPoints = HealthPoints;

	CheckHealth();
}

void UHealthComponent::CheckHealth() {
	CurrentHealthPoints = FMath::Clamp(CurrentHealthPoints, 0, MaxHealthPoints);

	if (CurrentHealthPoints <= 0)
		HealthIsDepletedDelegate.Broadcast();
}




