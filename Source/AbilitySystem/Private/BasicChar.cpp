// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicChar.h"
#include "AbilitySystemComponent.h"
#include "CharAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"

#include "AttributeSetBase.h"

#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasicChar::ABasicChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AbilitySystemComponent = CreateDefaultSubobject<UCharAbilitySystemComponent>(TEXT("AbilitySystemComponenet"));

	AttributeAsset = CreateDefaultSubobject<UAttributeSetBase>(FName("Attribute Asset"));
	
	
	
	
}



// Called when the game starts or when spawned
void ABasicChar::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent= FindComponentByClass<UCharAbilitySystemComponent>();
	

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

void ABasicChar::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire,UCharAbilitySystemComponent* AbilitySystemComponentReference)
{
	if (AbilitySystemComponentReference)
	{
		if (HasAuthority() && AbilityToAquire)
		{

			AbilitySystemComponentReference->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));

		}
		AbilitySystemComponentReference->InitAbilityActorInfo(this, this);


	}

	

}





