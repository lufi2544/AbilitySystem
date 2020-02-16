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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChange, float, Mana, float, MaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStrenghtChange, float, Strenght, float, MaxStrenght);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, float, Level);

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

     /* Mana Amount*/
    UPROPERTY(BlueprintReadWrite, Category = "AttibuteSetBase")
        FGameplayAttributeData  Mana;
        ATTRIBUTE_ACCESSORS(UAttributeSetBase,Mana)

     /* Max Character Mana*/
    UPROPERTY(BlueprintReadWrite,Category="AttributeSetBase")
        FGameplayAttributeData  MaxMana;
        ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxMana)

     /* Strenght Amount*/
    UPROPERTY(BlueprintReadWrite, Category = "AttributeSetBase")
        FGameplayAttributeData Strenght;
        ATTRIBUTE_ACCESSORS(UAttributeSetBase, Strenght)
        
     /* Max Character Strenght*/
     UPROPERTY(BlueprintReadWrite, Category = "AttributeSetBase")
        FGameplayAttributeData MaxStrenght;
        ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxStrenght)
      /* Character Level */
      UPROPERTY(BlueprintReadWrite,Category="AttibuteSetBase")
         FGameplayAttributeData  Level;
         ATTRIBUTE_ACCESSORS(UAttributeSetBase, Level)

       /* Max Character Level*/
       UPROPERTY(BlueprintReadWrite, Category = "AttributeSetBase")
         FGameplayAttributeData MaxLevel;
         ATTRIBUTE_ACCESSORS(UAttributeSetBase,MaxLevel)








    void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    FOnHealthChange OnHealthChange;
    
    FOnManaChange OnManaChange;

    FOnStrenghtChange OnStrenghtChange;

    FOnLevelUp OnLevelUp;


protected:



private:
};
