#include "pch.h"
#include "Event.h"

namespace Ash
{
    bool Event::HasType(EventType mask)
    {
        return mask & (1 << GetType());
    }
}