#include "NumberFormatter.h"
#include <cmath>

FString UNumberFormatter::FormatNumber(TArray<int32> NumberArray, const FString& Suffix)
{
    FString formattedNumber;
    if (NumberArray.Num() == 0) {
        formattedNumber = TEXT("0");
    }
    else {
        formattedNumber = FString::FromInt(NumberArray[0]);
    }

    if (Suffix.IsEmpty()) {
        return formattedNumber;
    }

    static const FString Suffixes[] = { TEXT(""), TEXT("k"), TEXT("m"), TEXT("b"), TEXT("a"), TEXT("z") };
    int32 suffixIndex = -1;

    for (int32 i = 0; i < UE_ARRAY_COUNT(Suffixes); ++i) {
        if (Suffixes[i] == Suffix) {
            suffixIndex = i;
            break;
        }
    }

    if (suffixIndex == -1) {
        return TEXT("InvalidSuffix");
    }

    if (suffixIndex >= NumberArray.Num()) {
        return formattedNumber + Suffixes[suffixIndex];
    }

    float restValue = 0.0f;
    for (int32 i = suffixIndex; i < NumberArray.Num(); ++i) {
        restValue += NumberArray[i] * FMath::Pow(1000.0f, i - suffixIndex);
    }

    FString restValueStr = FString::Printf(TEXT("%.4g"), restValue);
    return restValueStr + Suffixes[suffixIndex];
}

FString UNumberFormatter::AddFormattedNumbers(const FString& A, const FString& B)
{
    TArray<int32> AValueArray;
    FString ASuffix;
    ParseFormattedNumber(A, AValueArray, ASuffix);

    TArray<int32> BValueArray;
    FString BSuffix;
    ParseFormattedNumber(B, BValueArray, BSuffix);

    int32 commonSize = FMath::Max(AValueArray.Num(), BValueArray.Num());

    for (int32 i = AValueArray.Num(); i < commonSize; ++i) {
        AValueArray.Add(0);
    }

    for (int32 i = BValueArray.Num(); i < commonSize; ++i) {
        BValueArray.Add(0);
    }

    int32 carry = 0;
    TArray<int32> resultArray;

    for (int32 i = 0; i < commonSize; ++i) {
        int32 sum = AValueArray[i] + BValueArray[i] + carry;
        resultArray.Add(sum % 1000);
        carry = sum / 1000;
    }

    if (carry > 0) {
        resultArray.Add(carry);
    }

    return FormatNumber(resultArray, ASuffix);
}

FString UNumberFormatter::SubtractFormattedNumbers(const FString& A, const FString& B)
{
    TArray<int32> AValueArray;
    FString ASuffix;
    ParseFormattedNumber(A, AValueArray, ASuffix);

    TArray<int32> BValueArray;
    FString BSuffix;
    ParseFormattedNumber(B, BValueArray, BSuffix);

    int32 commonSize = FMath::Max(AValueArray.Num(), BValueArray.Num());

    for (int32 i = AValueArray.Num(); i < commonSize; ++i) {
        AValueArray.Add(0);
    }

    for (int32 i = BValueArray.Num(); i < commonSize; ++i) {
        BValueArray.Add(0);
    }

    int32 borrow = 0;
    TArray<int32> resultArray;

    for (int32 i = 0; i < commonSize; ++i) {
        int32 diff = AValueArray[i] - BValueArray[i] - borrow;

        if (diff < 0) {
            diff += 1000;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        resultArray.Add(diff);
    }

    return FormatNumber(resultArray, ASuffix);
}

void UNumberFormatter::ParseFormattedNumber(const FString& FormattedNumber, TArray<int32>& ValueArray, FString& Suffix)
{
    static const FString Suffixes[] = { TEXT(""), TEXT("k"), TEXT("m"), TEXT("b"), TEXT("a"), TEXT("z") };
    FString ValueStr = TEXT("");
    Suffix = TEXT("");

    for (TCHAR Char : FormattedNumber)
    {
        if (FChar::IsDigit(Char) || Char == TEXT('.'))
        {
            ValueStr.AppendChar(Char);
        }
        else
        {
            Suffix.AppendChar(Char);
        }
    }

    if (Suffix.IsEmpty())
    {
        Suffix = TEXT("");
    }
    else if (!Suffixes[0].Equals(Suffix) && !Suffixes[1].Equals(Suffix) && !Suffixes[2].Equals(Suffix) &&
        !Suffixes[3].Equals(Suffix) && !Suffixes[4].Equals(Suffix) && !Suffixes[5].Equals(Suffix))
    {
        Suffix = TEXT("InvalidSuffix");
        return;
    }

    ValueArray.Empty();

    int32 intValue = FCString::Atoi(*ValueStr);
    while (intValue > 0) {
        ValueArray.Add(intValue % 1000);
        intValue /= 1000;
    }
}
