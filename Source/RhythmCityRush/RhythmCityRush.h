// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Helper Macros
#if 0
float MacroDuration = 5.f;
#define SCREENPRINT(x) GEngine->AddOnScreenDebugMEssage(-1, MacroDuration ? MacroDuration : -1.0f, FColor::Black, x);
#else
#define SCREENPRINT(x)
#endif

// Character Classes
class ARhythmCityRushCharacter;
class URCRCharacterMovementComponent;