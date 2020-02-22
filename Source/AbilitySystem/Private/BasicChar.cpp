// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicChar.h"


#include "AbilitySystemComponent.h"
#include "CharAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerControllerBase.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components/CapsuleComponent.h"
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

	Capsule = GetCapsuleComponent();

	AttributeAsset->OnHealthChange.AddDynamic(this, &ABasicChar::OnHealthChange);

	AttributeAsset->OnManaChange.AddDynamic(this, &ABasicChar::OnManaChange);

	AttributeAsset->OnStrenghtChange.AddDynamic(this, &ABasicChar::OnStrenghtChange);

	AttributeAsset->OnLevelUp.AddDynamic(this, &ABasicChar::OnLevelUp);

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ABasicChar::OnCapsuleBeginOverlap);


	bIsCharacterAlive = true;

	TeamID = 255;
	
}



// Called when the game starts or when spawned
void ABasicChar::BeginPlay()
{
	Super::BeginPlay();

	AddTag(FullHealthTag);

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

UAbilitySystemComponent* ABasicChar::GetAbilitySystemComponent() const
{

	return AbilitySystemComponent;

}



///// GETTERS AND STATE FUNCTIONS ////

float ABasicChar::GetHealth() 
	{
	return AttributeAsset->GetHealth();
	}

float ABasicChar::GetMana() 
{
	return AttributeAsset->GetMana();
}

float ABasicChar::GetStrenght()
{
	return AttributeAsset->GetStrenght();
}

float ABasicChar::GetLevel()
{
	return AttributeAsset->GetLevel();
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

uint8 ABasicChar::GetTeamID() const
{

	return TeamID;

}

bool ABasicChar::IsOtherHostile(ABasicChar* Other)
{
	bool bDifferentTeams = false;

	if (!ensure(Other)) { return false; }

	if (this->GetTeamID() != Other->GetTeamID()) 
		{
		bDifferentTeams = true;
	}
	else
	{
		bDifferentTeams = false;
	}

	return bDifferentTeams;

}

void ABasicChar::AutoDeterminTeamIDbyControllerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{

		TeamID = 0;

	}


}

void ABasicChar::GetDashedEnemies(TArray<ABasicChar*>& DashedEnemies) 
	{
		
	DashedEnemies = DashOverlappedActors;

	

	}


//////// FUNCTIONS ////////

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


bool ABasicChar::CharacterActivateAbilityByClass(TSubclassOf<UGameplayAbility>Ability, bool RemoteActivation)
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

void ABasicChar::AddTag(FGameplayTag& GivenTag)
	{

	GetAbilitySystemComponent()->AddLooseGameplayTag(GivenTag);
	GetAbilitySystemComponent()->SetTagMapCount(GivenTag, 1);


	}

void ABasicChar::RemoveTag(FGameplayTag& TagToRemove) 
	{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);

	}

void ABasicChar::DashCollisionEnemies(ABasicChar*OverlappedActor) 

	{

	if (IsOtherHostile(OverlappedActor)) {

		if (DashOverlappedActors.Contains(nullptr))
		{

			UE_LOG(LogTemp, Error, TEXT("Empty Enemies Dash Array"))
		}

		if (!DashOverlappedActors.Contains(OverlappedActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("%i"),OverlappedActor->GetTeamID());
			DashOverlappedActors.AddUnique(OverlappedActor);
			BP_DashCollisionEnemies();

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Already Added!!"));


		}
	}

	}

void ABasicChar::CleanEnemiesArray()
{

	DashOverlappedActors.Empty();


}



//////// DELEGATES ////////

void ABasicChar::OnManaChange(float Mana, float MaxMana) 
	{

	BP_OnManaChange(Mana, MaxMana);


	}

void ABasicChar::OnStrenghtChange(float Strenght, float MaxStrenght) 
	{

	BP_OnStrenghtChange(Strenght, MaxStrenght);

	}

void ABasicChar::OnLevelUp(float Level) 
	{

	BP_OnLevelUp(Level);

	}

void ABasicChar::OnCapsuleBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
	{

	auto ActorOverlapped = Cast<ABasicChar>(OtherActor);

	DashCollisionEnemies(ActorOverlapped);


	}

