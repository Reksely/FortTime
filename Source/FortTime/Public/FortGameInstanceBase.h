

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

	virtual void Init() override;
	virtual void Shutdown() override;
};
