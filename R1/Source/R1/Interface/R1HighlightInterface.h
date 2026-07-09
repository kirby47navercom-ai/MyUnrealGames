

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "R1HighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UR1HighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class R1_API IR1HighlightInterface
{
	GENERATED_BODY()

public:
	virtual void Highlight() = 0;
	virtual void UnHighlight() = 0;
};
