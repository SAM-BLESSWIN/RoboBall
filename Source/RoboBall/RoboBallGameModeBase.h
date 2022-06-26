// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "RoboBallGameModeBase.generated.h"

class URoboBallWidget;
/**
 * 
 */
UCLASS()
class ROBOBALL_API ARoboBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;

	UPROPERTY(EditAnywhere,Category="Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;

	UPROPERTY()
	URoboBallWidget* GameWidget;

	virtual void BeginPlay() override;

	void UpdateItemText();

public:
	void ItemCollected();
	
};
