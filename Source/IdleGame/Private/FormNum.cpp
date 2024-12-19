// FormNum.cpp

#include "FormNum.h"

FString UFormNum::FormatNumber(float NumberToFormat)
{
    FString Result;
    const TArray<FString> FormatSymbols = { "", "K", "M", "B", "T", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p" }; // Add more symbols as needed
    const int32 FormatThreshold = 1000; // Change this threshold as needed

    int32 FormatIndex = 0;
    while (NumberToFormat >= FormatThreshold && FormatIndex < FormatSymbols.Num())
    {
        NumberToFormat /= FormatThreshold;
        FormatIndex++;
    }

    Result = FString::Printf(TEXT("%.1f%s"), NumberToFormat, *FormatSymbols[FormatIndex]);
    return Result;
}
