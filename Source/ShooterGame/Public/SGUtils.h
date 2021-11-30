#pragma once

namespace SGUtils
{
    template<typename T>
    T* GetPlayerComponentByClass(const APawn* Player)
    {
        UActorComponent* Component = Player ? Player->GetComponentByClass(T::StaticClass()) : nullptr;
        return Cast<T>(Component);
    }
}
