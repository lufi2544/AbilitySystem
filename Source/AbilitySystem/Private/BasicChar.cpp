// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicChar.h"
#include "AbilitySystemComponent.h"
#include "CharAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerControllerBase.h"
#include "AIController.h"
#include "BrainComponent.h"


#include "AttributeSetBase.h"

#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasicChar::ABasicChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AbilitySystemComponent = CreateDefaultSubobject<UCharAbilitySystemComponent>(TEXT("AbilitySystemComponenet"));

	AttributeAsset = CreateDefaultSubobject<UAttributeSetBase>(FName("Attribute Asset"));

	AbilitySystemComponent = CreateDefaultSubobject<UCharAbilitySystemComponent>(FName("CharacterAbilitySystemComponent"));

	AttributeAsset->OnHealthChange.AddDynamic(this, &ABasicChar::OnHealthChange);

	bIsCharacterAlive = true;

	TeamID = 255;
	
}



// Called when the game starts or when spawned
void ABasicChar::BeginPlay()
{
	Super::BeginPlay();

	AutoDeterminTeamIDbyControllerType();
	
}

// Called every frame
void ABasicChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

bool ABasicChar::IsAlive() 
	{
	if (AttributeAsset->GetHealth() <= 0) {
		return false;
	}
	else
	{
		return true;
	}

	}

UAbilitySystemComponent* ABasicChar::GetAbilitySystemComponent() const
{

	return AbilitySystemComponent;

}

void ABasicChar::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && AbilityToAquire)
		{

			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));

		}
		AbilitySystemComponent->InitAbilityActorInfo(this, this);


	}
}


bool ABasicChar::ActiveAbilitybyClass(TSubclassOf<UGameplayAbility>Ability, bool RemoteActivation) 
	{

	if (!ensure(AbilitySystemComponent)) { return false; }
	else
	{
		return AbilitySystemComponent->TryActivateAbilityByClass(Ability, RemoteActivation);
	}

	}

void ABasicChar::OnHealthChange(float Health, float MaxHealth) 
	{

	if (!IsAlive() && bIsCharacterAlive)
	{
		DisableController();
		BP_OnHealthChange(Health, MaxHealth);
		BP_OnDeath();
		bIsCharacterAlive = false;
		
		return;
	}

	BP_OnHealthChange(Health, MaxHealth);
	UE_LOG(LogTemp, Error, TEXT("%f"), Health);
	}


bool ABasicChar::IsOtherHostile(ABasicChar* Other)
{

	return TeamID != Other->GetTeamID();

}

void ABasicChar::AutoDeterminTeamIDbyControllerType() 
	{
	if (GetController() && GetController()->IsPlayerController())
	{

		TeamID = 0;

	}


	}

uint8 ABasicChar::GetTeamID() const
{

	return TeamID;

}

void ABasicChar::DisableController() 
	{
	APlayerControllerBase* PlayerController = Cast<APlayerControllerBase>(GetController());

	if (PlayerController)
	{

		PlayerController->DisableInput(PlayerController);

	}

	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController)
	{

		AIController->GetBrainComponent()->StopLogic("Dead");

	}


	}

