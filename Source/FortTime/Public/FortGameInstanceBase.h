

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "FortGameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class FORTTIME_API UFortGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
	TSharedPtr<IWebSocket> WebSocket;
	//TSharedPtr<IXmppConnection> XmppConnection;

	UFortGameInstanceBase();

	virtual void Init() override;
	virtual void Shutdown() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ReplaySystem")
		bool bReplayEnabled;

	UPROPERTY(EditDefaultsonly, Category = "ReplaySystem")
		FString RecordingName;

	UPROPERTY(EditDefaultsonly, Category = "ReplaySystem")
		FString FriendlyRecordingName;

	UFUNCTION(BlueprintCallable, Category = "ReplaySystem")
		void StartRecording();

	UFUNCTION(BlueprintCallable, Category = "ReplaySystem")
		void StopRecording();

	UFUNCTION(BlueprintCallable, Category = "RReplaySystem")
		void StartReplay();


	int SavedReplays;

};
