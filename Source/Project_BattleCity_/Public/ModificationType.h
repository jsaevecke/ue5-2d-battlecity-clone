#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHealthModificationType : uint8
{
	Damage,
	Heal,
	PenetrationDamage
};