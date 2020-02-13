// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange,float, Health,float, MaxHealth);

/**
 *Class That Stores the Attribuites of the Characters like mana, Health...
 */
UCLASS()
class ABILITYSYSTEM_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:

    UAttributeSetBase();

   /* Health Amount*/
    UPROPERTY(BlueprintReadWrite, Category = "AttibuteSetBase")
        FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health)

   /* Max Character Health*/
	UPROPERTY(BlueprintReadWrite, Category = "AttibuteSetBase")
		FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth)

    void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    FOnHealthChange OnHealthChange;


protected:



private:
};
