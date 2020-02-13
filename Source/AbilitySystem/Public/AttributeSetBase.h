// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"



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

   /* Max Character Health*/
	UPROPERTY(BlueprintReadWrite, Category = "AttibuteSetBase")
		FGameplayAttributeData MaxHealth;

    void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    FOnHealthChange OnHealthChange;


protected:



private:
};
