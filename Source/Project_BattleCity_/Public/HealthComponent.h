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
	void ModifyHealthpoints(int amount, EHealthModificationType type);
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Health")
	void SetCurrentHealthpoints(int healthpoints);

protected:
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Health")
	void CheckHealth();

protected:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Health")
	FHealthIsDepleted HealthIsDepletedDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Health")
	FHealthModification HealthModificationDelegate;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Health")
	int MaxHealthpoints = 1;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Health")
	int CurrentHealthpoints = 1;
	UPROPERTY(EditDefaultsOnly, Category = "BlackBox|Health")
	bool IsIndestructible = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BlackBox|Health")
	TSet<EHealthModificationType> ValidModificationTypes;
};
