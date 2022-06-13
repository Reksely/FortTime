


#include "FortGameInstanceBase.h"
#include "WebSocketsModule.h"

UFortGameInstanceBase::UFortGameInstanceBase()
{

	RecordingName = "FortReplay" + SavedReplays;
	FriendlyRecordingName = "Test Replay";
}

void UFortGameInstanceBase::Init()
{
	Super::Init();

	/*if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://localhost:8080");

	WebSocket->OnConnected().AddLambda([]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully connected");
		});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
		});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
		});

	WebSocket->OnMessage().AddLambda([](const FString& MessageString)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);
		});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);
		});

		WebSocket->Connect();*/

	if (!FModuleManager::Get().IsModuleLoaded("XMPP"))
	{
		FModuleManager::Get().LoadModule("XMPP");
	}

	//XmppConnection = FXmppServer
}

void UFortGameInstanceBase::Shutdown()
{
	/*if (WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
	Super::Shutdown();*/
}

void UFortGameInstanceBase::StartRecording()
{

	if (bReplayEnabled == true)
	{
		StartRecordingReplay(RecordingName, FriendlyRecordingName);
	}
}

void UFortGameInstanceBase::StopRecording()
{
	
	StopRecordingReplay();
	SavedReplays = SavedReplays + 1;
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, TEXT("Saved Replay: %lld"));
}

void UFortGameInstanceBase::StartReplay()
{
	PlayReplay(RecordingName, nullptr);
}
