// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "KillShotCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;


UCLASS()
class TPS_MP_KILLSHOT_API AKillShotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKillShotCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
protected:
	virtual void BeginPlay() override;

	// Default Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* IMC_Player;
	
	// Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_LookUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Turn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* IA_Jump;
	
	
	// Functions for Movement and look (keyboard,Mouse, and Gamepad, bindings are combined in IMC_Player)
	void MoveAction(const FInputActionValue& Value); 
	void LookUpAction(const FInputActionValue& Value);
	void TurnAction(const FInputActionValue& Value);
	
private: 
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;	
	
	
	
	//Getters and Setters
public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
