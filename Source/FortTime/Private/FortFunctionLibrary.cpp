


#include "FortFunctionLibrary.h"
#include <Runtime/Online/WebSockets/Public/WebSocketsModule.h>

void UFortFunctionLibrary::ConnectWebSocket()
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://localhost:8080");
	WebSocket->Connect();

}

void UFortFunctionLibrary::DisconnectWebSocket()
{
	if (WebSocket->IsConnected())
	{
		WebSocket->Close();
	}
}
