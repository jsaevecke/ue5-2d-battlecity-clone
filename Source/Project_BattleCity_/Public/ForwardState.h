#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EForwardState : uint8
{
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};