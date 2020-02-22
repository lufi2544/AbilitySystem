// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "AbilityCapsule.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UAbilityCapsule : public UCapsuleComponent
{
	GENERATED_BODY()

public:

	UAbilityCapsule();

	/*TArray<FHitResult>CheckCapsuleCollision(AActor* Actor);*/
	
};
