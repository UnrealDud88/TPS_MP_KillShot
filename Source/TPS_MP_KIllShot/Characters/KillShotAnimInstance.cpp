// Fill out your copyright notice in the Description page of Project Settings.


#include "KillShotAnimInstance.h"
#include "KillShotCharacter.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UKillShotAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (APawn* PlayerPawn= TryGetPawnOwner())
	{
		KillShotCharacter= Cast<AKillShotCharacter>(PlayerPawn);
		MoveComp= KillShotCharacter ? KillShotCharacter->GetCharacterMovement() : nullptr;
	}
}

void UKillShotAnimInstance::UpdateAnimProperties(float DeltaTime)
{
	APawn* CurrentOwner= TryGetPawnOwner();
	if (CurrentOwner != KillShotCharacter)
	{
		KillShotCharacter= Cast<AKillShotCharacter>(CurrentOwner);
		MoveComp= KillShotCharacter ? KillShotCharacter->GetCharacterMovement() : nullptr;
	}
	
	if (!KillShotCharacter || !MoveComp) return;
	
	const FVector Velocity= KillShotCharacter->GetVelocity();
	Speed= Velocity.Size2D(); 
	
	bIsInAir= MoveComp->IsFalling();
	
	// Is the player actively providing movement input?
	bIsAccelerating= MoveComp->GetCurrentAcceleration().SizeSquared() > KINDA_SMALL_NUMBER;

	// Is the player moving (use a small threshold to avoid jitter)?
	bIsMoving = Speed > 5.f;

	// Calculate movement direction for AnimBP
	MovementDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, KillShotCharacter->GetActorRotation());
}
