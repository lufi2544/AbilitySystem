// Fill out your copyright notice in the Description page of Project Settings.
#include "AttributeSetBase.h"

#include "GameplayTagContainer.h"
#include "BasicChar.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"


UAttributeSetBase::UAttributeSetBase()

	:Health(200.0f),
	MaxHealth(200.0f),
	Mana(100.0f),
	MaxMana(150.0f),
	Strenght(250.0f),
	MaxStrenght(300.0f),
	Level(1.f),
	MaxLevel(5.f)
	{


	}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) 
	{

	// If the property changed of any GE applied is Health Then...
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase,Health)))
	{
		//Owner casted to BasicChar
		ABasicChar* OwnerCharacter = Cast<ABasicChar>(GetOwningActor());


		//Clamping the values
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetBaseValue()));
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));


		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		if (OwnerCharacter)
		{
			if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
			{

				OwnerCharacter->AddTag(OwnerCharacter->FullHealthTag);

				UE_LOG(LogTemp,Error,TEXT("Health = Max"));

			}
			else
			{
				OwnerCharacter->RemoveTag(OwnerCharacter->FullHealthTag);

			}
		}

		}

	// If the property changed of any GE applied is Mana Then...
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana))) 
		{

		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetBaseValue()));
		
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	
		}

	// If the property changed of any GE applied is Strenght Then...
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Strenght)))
		{

		Strenght.SetCurrentValue(FMath::Clamp(Strenght.GetCurrentValue(), 0.f, MaxStrenght.GetCurrentValue()));
		Strenght.SetBaseValue(FMath::Clamp(Strenght.GetBaseValue(), 0.f, MaxStrenght.GetBaseValue()));
	
		OnStrenghtChange.Broadcast(Strenght.GetCurrentValue(), MaxStrenght.GetCurrentValue());
	
		}

	// If the property changed of any GE applied is The Level Then...
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Level))) 
		{
	
		Level.SetCurrentValue(FMath::Clamp(Level.GetCurrentValue(), 0.f, MaxLevel.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Level.GetBaseValue(), 0.f, MaxLevel.GetBaseValue()));
	
		OnLevelUp.Broadcast(Level.GetCurrentValue());

	
		}


	

		
	}

