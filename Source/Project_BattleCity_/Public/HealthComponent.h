#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ModificationType.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthIsDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthModification, int, CurrentHealthpoints, int, MaxHealthpoints, EHealthModificationType, ModificationType);

UCLASS(ClassGroup=(Health), meta=(BlueprintSpawnableComponent), HideCategories=(Tags, Activation, ComponentReplication, Variable, AssetUserData, ComponentTick))
class PROJECT_BATTLECITY__API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "BlackBox|Health")
	void ModifyHealthPoints(int Amount, EHealthModificationType Type);
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Health")
	void SetCurrentHealthPoints(int HealthPoints);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Health")
	FHealthIsDepleted HealthIsDepletedDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Health")
	FHealthModification HealthModificationDelegate;
protected:
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Health")
	void CheckHealth();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Health")
	int MaxHealthPoints = 1;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Health")
	int CurrentHealthPoints = 1;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Health")
	bool IsIndestructible = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BlackBox|Health")
	TSet<EHealthModificationType> ValidModificationTypes;
};
