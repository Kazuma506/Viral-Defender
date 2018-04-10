// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "FirstPerson_Character.generated.h"

UCLASS()
class SNHU_FPS_API AFirstPerson_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPerson_Character();
	float walking = 800; //inializes walking speed
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value); // function to move forward or backwards
	void MoveRight(float Value); // function to move left or right
	int GetAmmo(); //returns ammo count
	float GetHealth(); //returns Health count
	bool GetAntibodiesActive(); //returns if antibodies are active


	UPROPERTY(EditAnywhere, Category = "Cameras") // creates spring arm
		USpringArmComponent* CameraSpringArm0;
	UPROPERTY(EditAnywhere, Category = "Cameras") // creates frist person camera
		UCameraComponent* FirstPersonCamera0;

	//UPROPERTY(EditAnywhere)


	UPROPERTY(EditAnywhere, Category = "Av")
		UCapsuleComponent* AvatarCollider;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vitals")
	float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vitals")
	float ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vitals")
	bool bAntibodiesActive;
	
};
