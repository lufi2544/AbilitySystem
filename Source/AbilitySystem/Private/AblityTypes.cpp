// Fill out your copyright notice in the Description page of Project Settings.


#include "AblityTypes.h"


//Constructor 1
FGameplayAbilityInfo::FGameplayAbilityInfo() 
	:CoolDownDuration (0),
	Cost(0),
	CostType(EAbilityCostType::Mana),
	UIMaterial(nullptr),
	AbilityClass(nullptr)
	{

	}

//Construcotr 2
FGameplayAbilityInfo::FGameplayAbilityInfo(float InCoolDownDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMaterial, TSubclassOf<UGameplayAbilityBase>InAbilityClass) 
	:CoolDownDuration(InCoolDownDuration),
	Cost(InCost),
	CostType(InCostType),
	UIMaterial(InUIMaterial),
	AbilityClass(InAbilityClass)
{



}
