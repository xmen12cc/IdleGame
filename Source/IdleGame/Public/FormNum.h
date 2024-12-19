// FormNum.h
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FormNum.generated.h"

UCLASS()
class IDLEGAME_API UFormNum : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Custom Utils")
        static FString FormatNumber(float NumberToFormat);
};
