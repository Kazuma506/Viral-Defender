// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "FirstPerson_Character.h"
#include "TheGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SNHU_FPS_API ATheGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATheGameModeBase();

	virtual void BeginPlay() override; //initalizes BeginPlay	

	virtual void Tick(float DeltaTime) override; //initalize Tick

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere)
		class UUserWidget* CurrentWidget; // Current Widget variable

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health; // declares variable Score

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ammo; // declares variable Time

	AFirstPerson_Character* Avatar;

};
