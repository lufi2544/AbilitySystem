// Fill out your copyright notice in the Description page of Project Settings.
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "AttributeSetBase.h"

UAttributeSetBase::UAttributeSetBase()

	:Health(200.0f),
	MaxHealth(200.0f)
	{


	}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) 
	{

	//Clampping the values
	Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetBaseValue()));
	Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));


	// If the property changed of any GE applied is Health Then...
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Health)))
	{

		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
		
	}

