#pragma once

#include "CoreMinimal.h"

class IDLEGAME_API FBigNumber
{
public:
    FBigNumber();
    void Add(int32 Value);
    void Subtract(int32 Value);
    FString ToString() const;

private:
    TArray<int32> Groups;
};
