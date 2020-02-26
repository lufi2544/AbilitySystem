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
class UGameplayAbilityBase;






UCLASS()
class ABILITYSYSTEM_API ABasicChar : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:


	/*	MultiCast Delegate Functions	*/

	UFUNCTION()
		void OnHealthChange(float Health, float MaxHealth);

	UFUNCTION()
		void OnManaChange(float Mana, float MaxMana);

	UFUNCTION()
		void OnStrenghtChange(float Strengh, float MaxStrenght);

	UFUNCTION()
		void OnLevelUp(float Level);

	UFUNCTION()
		void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);





	// Sets default values for this character's properties
	ABasicChar();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY()
		UCharAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		UAttributeSetBase* AttributeAsset;





	/*Returns true if the Character is still Alive*/
	UFUNCTION(BlueprintPure, Category = "CharacterBaseState")
		bool IsAlive();

	UFUNCTION(BlueprintPure, Category = "CharacterBase")
		uint8 GetTeamID() const;
	
	UFUNCTION(BlueprintPure, Category = "CharacterBaseState")
		float GetHealth();

	UFUNCTION(BlueprintPure, Category = "CharacterBaseState")
		float GetMana();

	UFUNCTION(BlueprintPure, Category = "CharacterBaseState")
		float GetStrenght();

	UFUNCTION(BlueprintPure, Category = "CharacterBaseState")
		float GetLevel();



	/*Function that Sets the Ability on the Character*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		virtual void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities);

	/*Activate the current ability*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		bool CharacterActivateAbilityByClass(TSubclassOf<UGameplayAbility>Ability, bool RemoteActivation);

	/*Event that give us a reference of the dashed enemies by the dash ability*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void GetDashedEnemies(TArray<ABasicChar*>& DashedEnemies);

	/*Clear the dashed enemies array*/
	UFUNCTION(BlueprintCallable, Category="CharacterBase")
		void CleanEnemiesArray();

	/*The controller repossess the character (IA and Player)*/
	UFUNCTION(BlueprintCallable, Category ="CharacterBase")
		void EnableController();

	/*Unposses the controller from the character*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void DisableController();
	
	/*Applies a Stun State to the character*/
	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void HitStun(float StunDuration);


	

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnBeginStun"))
		void BP_OnStun();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnEndStun"))
		void BP_OnEndStun();

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnDashHitEnemy"))
		void BP_DashCollisionEnemies();

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

	
	


	//Tag that determines if the player is full health
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AbilityTags")
	FGameplayTag FullHealthTag;





	/*Determine the team Id for the character*/
	void AutoDeterminTeamIDbyControllerType();

	


	
	




	// Array of the Actors that we collide with the capsule while dashing
	TArray<ABasicChar*>DashOverlappedActors;

	/**Function that checks if the dashed enemies by the dash
	 ability are indeed enemies, and if so we add them to the dashed enemies array.

	   @param OverlappedCharacters enemy to check

	**/
	void DashCollisionEnemies(ABasicChar* OverlappedCharacters);

	


	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> AbilityToAdd);

	//Member variable to store if The character is alive
	bool bIsCharacterAlive;



	//The integer that determines the character team
	uint8 TeamID;

	// Character CapsuleComponent
	UCapsuleComponent* Capsule;

	//Timer handler for a function
	FTimerHandle StunTimeHandle;




	



private:






public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
