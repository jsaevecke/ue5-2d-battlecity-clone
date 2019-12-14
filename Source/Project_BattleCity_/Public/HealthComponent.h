#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UENUM(BlueprintType)
enum class EHealthModificationType : uint8
{
	Damage,
	Heal,
	PenetrationDamage
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthIsDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthModification, int, CurrentHealthpoints, int, MaxHealthpoints, EHealthModificationType, ModificationType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_BATTLECITY__API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "BlackBox|Components|Health")
	void ModifyHealthpoints(int amount, EHealthModificationType type);
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Components|Health")
	void SetCurrentHealthpoints(int healthpoints);

protected:
	UFUNCTION(BlueprintCallable, Category = "BlackBox|Components|Health")
	void CheckHealth();
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Components|Health")
	FHealthIsDepleted HealthIsDepletedDelegate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "BlackBox|Components|Health")
	FHealthModification HealthModificationDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBox|Components|Health")
	int MaxHealthpoints = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBox|Components|Health")
	int CurrentHealthpoints = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BlackBox|Components|Health")
	TSet<EHealthModificationType> ValidModificationTypes;
};
