// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KillShotAnimInstance.generated.h"

class AKillShotCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class TPS_MP_KILLSHOT_API UKillShotAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateAnimProperties(float DeltaTime);
	
 
	
private:
	
	UPROPERTY(Transient, VisibleAnywhere,BlueprintReadOnly, Category= Player, meta=(AllowPrivateAccess="true"))	
	TObjectPtr<AKillShotCharacter>KillShotCharacter=nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent>MoveComp=nullptr;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Player, meta=(AllowPrivateAccess="true"))
	bool bIsInAir=false;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Player, meta=(AllowPrivateAccess="true"))
	bool bIsAccelerating=false;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Player, meta=(AllowPrivateAccess="true"))
	bool bIsMoving=false;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Player, meta=(AllowPrivateAccess="true"))
	float Speed=0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Player, meta=(AllowPrivateAccess="true"))
	float MovementDirection = 0.f;
};
