// Fill out your copyright notice in the Description page of Project Settings.


#include "RoboBallGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RoboBall/PickUps.h"
#include "RoboBall/RoboBallWidget.h"

void ARoboBallGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APickUps::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass)
	{
		GameWidget = Cast<URoboBallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARoboBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARoboBallGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}

