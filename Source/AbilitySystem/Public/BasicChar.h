// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BasicChar.generated.h"


//Fwd Declarations
class UCharAbilitySystemComponent;
class UAttributeSetBase;
class UGameplayAbility;
class UAbilitySystemComponent;
class UCameraComponent;
class USpringArmComponent;




UCLASS()
class ABILITYSYSTEM_API ABasicChar : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicChar();

	
	UCharAbilitySystemComponent* AbilitySystemComponent;

	/*Function that Sets the Ability on the Character*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	virtual void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire, UCharAbilitySystemComponent* AbilitySystemComponentReference);

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="State")
	UAttributeSetBase* AttributeAsset;

	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
