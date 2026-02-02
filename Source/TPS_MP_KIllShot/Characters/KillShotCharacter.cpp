// Fill out your copyright notice in the Description page of Project Settings.


#include "KillShotCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AKillShotCharacter::AKillShotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), FName());
	CameraBoom->TargetArmLength = 250.f;
	CameraBoom->bUsePawnControlRotation = false; 
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraLagSpeed = 20.f;
	CameraBoom->CameraRotationLagSpeed = 50.f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;	
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.3f;
	
	
}

// Called when the game starts or when spawned // ** THIS IF CHECK MAY BEED TO BE CHANGED FOR MULTIPLAYER **//
void AKillShotCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Player, 0);
		}
	}
}

// Movement Action WASD, Left Stick
void AKillShotCharacter::MoveAction(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// Look Up Action Mouse Y, Right Stick Y
void AKillShotCharacter::LookUpAction(const FInputActionValue& Value)
{
	const FVector2D LookUpVector = Value.Get<FVector2D>();
	const float LookUpScaleFactor = 1.0f;
	AddControllerPitchInput(LookUpVector.Y * LookUpScaleFactor);
}

// Turn Action Mouse X, Right Stick X
void AKillShotCharacter::TurnAction(const FInputActionValue& Value)
{
	const FVector2D TurnVector = Value.Get<FVector2D>();
	const float TurnScaleFactor = 1.0f;
	AddControllerYawInput(TurnVector.X * TurnScaleFactor);
}


// Called every frame
void AKillShotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKillShotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	 
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AKillShotCharacter::MoveAction);
		EnhancedInputComponent->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &AKillShotCharacter::LookUpAction);
		EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &AKillShotCharacter::TurnAction);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AKillShotCharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AKillShotCharacter::StopJumping);
		
	}	

}

