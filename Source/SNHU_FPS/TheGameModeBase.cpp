// Fill out your copyright notice in the Description page of Project Settings.

#include "SNHU_FPS.h"
#include "TheGameModeBase.h"
#include "FirstPerson_Character.h"
#include "Blueprint/UserWidget.h"



ATheGameModeBase::ATheGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	health = 100; // sets inital value

	ammo = 150; // sets inital value

}

void ATheGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Avatar = Cast<AFirstPerson_Character>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass); // creates widget

		if (CurrentWidget != nullptr) // adds widget to Viewport if it is not null
		{
			CurrentWidget->AddToViewport(); //adds to viewport
		}
	}
}

void ATheGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	health = Avatar->GetHealth(); //sets health

	ammo = Avatar->GetAmmo(); // sets ammo 
	


}
