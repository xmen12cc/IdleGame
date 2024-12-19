#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NumberFormatter.generated.h"

UCLASS()
class IDLEGAME_API UNumberFormatter : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Number Formatting")
        static FString FormatNumber(TArray<int32> NumberArray, const FString& Suffix);

    UFUNCTION(BlueprintCallable, Category = "Number Formatting")
        static FString AddFormattedNumbers(const FString& A, const FString& B);

    UFUNCTION(BlueprintCallable, Category = "Number Formatting")
        static FString SubtractFormattedNumbers(const FString& A, const FString& B);

private:
    static void ParseFormattedNumber(const FString& FormattedNumber, TArray<int32>& ValueArray, FString& Suffix);

    static int32 FindSuffixIndex(const FString& Suffix);

    static FString GetSuffixForIndex(int32 Index);

    static int32 GetIndexForSuffix(const FString& Suffix);
};
