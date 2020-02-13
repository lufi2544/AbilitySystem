// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicChar.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "PlayerChar.generated.h"


class UAttributeSetBase;

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API APlayerChar : public ABasicChar
{
	GENERATED_BODY()

public:

	APlayerChar();
	virtual void BeginPlay() override;

	




protected:



		

private:

	


	
};
