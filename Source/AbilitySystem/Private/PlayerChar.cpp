// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerChar.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AttributeSetBase.h"


APlayerChar::APlayerChar() 
	{
	
		


	}

void APlayerChar::BeginPlay() 
	{

	Super::BeginPlay();
	
	if (AbilitySystemComponent) { UE_LOG(LogTemp, Error, TEXT("GOOOOO")); }

	}




