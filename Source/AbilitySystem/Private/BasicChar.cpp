// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicChar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasicChar::ABasicChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	

}

// Called when the game starts or when spawned
void ABasicChar::BeginPlay()
{
	Super::BeginPlay();
	
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

void ABasicChar::FloatHello() {  }

