// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AblityTypes.generated.h"


//Fwd Declarations

class UGameplayAbilityBase;
class UMaterialInstance;


// The possible costs for an Ability to be used
UENUM(BlueprintType)
enum class EAbilityCostType : uint8 
{

	Health,
	Mana,
	Strenght


};


USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		float CoolDownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		EAbilityCostType CostType;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		UMaterialInstance* UIMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		TSubclassOf<UGameplayAbilityBase> AbilityClass;


	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float InCoolDownDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMaterial, TSubclassOf<UGameplayAbilityBase>InAbilityClass);

		
};