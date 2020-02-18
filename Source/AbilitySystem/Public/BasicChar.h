// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
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


	/*	Multicast Delegate Functions	*/

	UFUNCTION()
		void OnHealthChange(float Health, float MaxHealth);

	UFUNCTION()
		void OnManaChange(float Mana, float MaxMana);

	UFUNCTION()
		void OnStrenghtChange(float Strengh, float MaxStrenght);

	UFUNCTION()
		void OnLevelUp(float Level);





	// Sets default values for this character's properties
	ABasicChar();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY()
		UCharAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		UAttributeSetBase* AttributeAsset;





	/*Function that Sets the Ability on the Character*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	virtual void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	/*Activate the current ability*/
	UFUNCTION(BlueprintCallable, Category = "Abilities")
		bool PlayerActivateAbilitybyClass(TSubclassOf<UGameplayAbility>Ability, bool RemoteActivation);


	/*Returns true if the Character is still Alive*/
	UFUNCTION(BlueprintPure, Category = "State")
		bool IsAlive();

	UFUNCTION(BlueprintPure, Category = "CharacterBase")
		uint8 GetTeamID() const;
	




	/*	Event called when the health has changed and it shows the Max Health too.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnHealthChange"))
		void BP_OnHealthChange(float Health, float MaxHealth);

	/*	Event called when the Character dies.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnDeath"))
		void BP_OnDeath();

	/*	Event called when the Mana changes.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnManaChange"))
		void BP_OnManaChange(float Mana, float MaxMana);

	/*	Event called when the Mana changes.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnStrenghtChange"))
		void BP_OnStrenghtChange(float Strenght, float MaxStrenght);

	/*	Event called when the Character levels up.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnLevelUp"))
		void BP_OnLevelUp(float Level);

	/*Checks if other Character is an enemy.
		@param ABasicChar Other Character.
	*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		bool IsOtherHostile( ABasicChar* Other);

	//Add a certain Tag to the Character
	UFUNCTION(BlueprintCallable, Category = "AbilityTags")
		void AddTag(FGameplayTag& GivenTag);

	//Remove a certain Tag from the character
	UFUNCTION(BlueprintCallable, Category = "AbilitiesTags")
		void RemoveTag(FGameplayTag& TagToRemove);

	
	/*Determine the team Id for the character*/
	void AutoDeterminTeamIDbyControllerType();

	/*Unposses the controller from the character*/
	void DisableController();



	//Tag that determines if the player is full health
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AbilityTags")
	FGameplayTag FullHealthTag;


	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Member variable to store if The character is alive
	bool bIsCharacterAlive;



	//The integer that determines the character team
	uint8 TeamID;
	
private:





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
