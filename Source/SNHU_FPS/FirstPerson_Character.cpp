// Fill out your copyright notice in the Description page of Project Settings.

#include "SNHU_FPS.h"
#include "FirstPerson_Character.h"


// Sets default values
AFirstPerson_Character::AFirstPerson_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false; // disable controller rotation pitch
	bUseControllerRotationYaw = false; //disable controller rotation yaw
	bUseControllerRotationRoll = false; // disable controller rotation roll

	GetCharacterMovement()->bOrientRotationToMovement = true; // sets Orientation Rotation To Movement to true

	AutoPossessPlayer = EAutoReceiveInput::Player0; //auto posses player 0

	CameraSpringArm0 = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm0")); // creates spring arm componenet
	CameraSpringArm0->SetupAttachment(RootComponent); //attaches CameraSpringArm0 to RootComponent
	CameraSpringArm0->TargetArmLength = 300.f; // sets CameraSpringArmComponenet
	CameraSpringArm0->bUsePawnControlRotation = true; // enables pawn control rotation 

	FirstPersonCamera0 = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera0")); // creates the component FirstPersonCamera0
	FirstPersonCamera0->SetupAttachment(CameraSpringArm0, USpringArmComponent::SocketName); // attaches FirstPersonCamera0 to ThirdPersonCamera0
	FirstPersonCamera0->bUsePawnControlRotation = false; // disables pawn control rotation
	FirstPersonCamera0->SetRelativeLocation(FVector(320.f, 0.f, 70.f)); //sets postion for first person camera


	AvatarCollider = GetCapsuleComponent(); //sets capsule component to AvatarCollider

	AvatarCollider->SetSimulatePhysics(false); // turns physics off
	AvatarCollider->bGenerateOverlapEvents = true;
	AvatarCollider->SetCollisionProfileName(TEXT("Pawn")); // Sets collision Profile name
	AvatarCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Sets type of Collisions
	AvatarCollider->SetCollisionObjectType(ECollisionChannel::ECC_Pawn); // Set the object type
	AvatarCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block); // Sets to block pawns

	AvatarCollider->OnComponentHit.AddDynamic(this, &AFirstPerson_Character::OnHit); //calls OnHit when there is an Hit

}

// Called when the game starts or when spawned
void AFirstPerson_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPerson_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPerson_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward_Key", this, &AFirstPerson_Character::MoveForward); // when w or s are pressed the MoveForawd function is called
	PlayerInputComponent->BindAxis("MoveRight_Key", this, &AFirstPerson_Character::MoveRight); // when a or d are pressed the MoveRight function is called

	PlayerInputComponent->BindAction("Jump_Key", IE_Pressed, this, &ACharacter::Jump); // when spacebar is pressed the character jumps
	PlayerInputComponent->BindAction("Jump_Key", IE_Released, this, &ACharacter::StopJumping); // when the spacebar is released the character stops jumping


	PlayerInputComponent->BindAxis("Asnuma_Key", this, &APawn::AddControllerYawInput); // allows the mouse to control yaw roation 
	PlayerInputComponent->BindAxis("Altitude_Key", this, &APawn::AddControllerPitchInput); // allows the mouse to control pitch rotation

}

void AFirstPerson_Character::MoveForward(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT(("W or S key pressed"));

	const FRotator Rotation = Controller->GetControlRotation(); // gets the control roation from the character controller
	const FRotator YawRoation(0, Rotation.Yaw, 0); // stores  the Yaw Roation
	const FVector Direction = FRotationMatrix(YawRoation).GetUnitAxis(EAxis::X);  // stores the direction that the user is inputing

	AddMovementInput(Direction, Value); // allows the character to move
}

void AFirstPerson_Character::MoveRight(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT(("A or D key pressed"));

	const FRotator Rotation = Controller->GetControlRotation(); // gets the control rotation from the character controller
	const FRotator YawRotation(0, Rotation.Yaw, 0); // stores  the Yaw Roation
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // stores the direction that the user is inputing

	AddMovementInput(Direction, Value); // allows the character to move 
}


void AFirstPerson_Character::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	if (OtherActor->ActorHasTag(FName(TEXT("HealthPickUp"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit"));
		if (health < 100)
		{
			AvatarCollider->SetCollisionProfileName("BlockAll");
			if (health < 100)
				health += 20;

			if (health > 100)
				health = 100;

			OtherActor->Destroy();

			UE_LOG(LogTemp, Warning, TEXT("Health %d"), health);
		}

	}

	if (OtherActor->ActorHasTag(FName(TEXT("AmmoPickUp"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit"));
		if (ammo < 100)
		{
			AvatarCollider->SetCollisionProfileName("BlockAll");
			if (ammo < 100)
				ammo += 20;

			if (ammo > 100)
				ammo = 100;

			OtherActor->Destroy();

			UE_LOG(LogTemp, Warning, TEXT("Ammo %d"), ammo);
		}

	}

	if (OtherActor->ActorHasTag(FName(TEXT("PillPickUp"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit"));
		if (bAntibodiesActive == false)
		{
			AvatarCollider->SetCollisionProfileName("BlockAll");
			
			bAntibodiesActive = true;

			OtherActor->Destroy();

			UE_LOG(LogTemp, Warning, TEXT("Antibodies activated"));
		}

	}

}
UFUNCTION(BlueprintCallable)
int AFirstPerson_Character::GetAmmo()
{
	return ammo;
}
UFUNCTION(BlueprintCallable)
float AFirstPerson_Character::GetHealth()
{
	return health;
}
UFUNCTION(BlueprintCallable)
bool AFirstPerson_Character::GetAntibodiesActive()
{
	return bAntibodiesActive;
}