

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <Runtime/Online/WebSockets/Public/IWebSocket.h>
#include "FortFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FORTTIME_API UFortFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "FortFunctions", meta = (DevelopmentOnly, WorldContext = "WorldContextObject", CallableWithoutWorldContext))
		void ConnectWebSocket();

	UFUNCTION(BlueprintCallable, Category = "FortFunctions", meta = (DevelopmentOnly, WorldContext = "WorldContextObject", CallableWithoutWorldContext))
		void DisconnectWebSocket();

public:
	TSharedPtr<IWebSocket> WebSocket;
};
