// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"






FGameplayAbilityInfo UGameplayAbilityBase::GetAbilityInfo() 
	{

	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();



	if (CoolDownEffect && CostEffect) 
		{

		float CoolDownDuration = 0;

		float Cost = 0;

		EAbilityCostType CostType;
			
		

		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CoolDownDuration);

		// In th9is case the costs can be more than one so they are on an array, if we have more than 1, we select the 1st
		if (CostEffect->Modifiers.Num() > 0) 
			{
		
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];

			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1,Cost);

			// Then We want to know in which attribute is the modifier applied

			FGameplayAttribute CostAttribute = EffectInfo.Attribute;

			FString AttributeName = CostAttribute.AttributeName;

			if (AttributeName == "Health") 
				{
			
				CostType = EAbilityCostType::Health;
			
			}
			else if (AttributeName == "Mana")	
				{
			
				CostType = EAbilityCostType::Mana;
			
			}
			else if (AttributeName == "Strenght") 
				{
			
		
				CostType = EAbilityCostType::Strenght;

				}


			UE_LOG(LogTemp, Error, TEXT("CD : %f ,Cost: %f "),CoolDownDuration,Cost);

			return FGameplayAbilityInfo(CoolDownDuration, Cost, CostType, UIMaterial, GetClass());
			
			}
			
		
		}

	
	return FGameplayAbilityInfo();
	}
