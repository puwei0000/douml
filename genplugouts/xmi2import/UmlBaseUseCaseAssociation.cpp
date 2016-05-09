
#include "UmlCom.h"
#include "UmlBaseUseCaseAssociation.h"
#include "UmlUseCaseReference.h"
#include "UmlClass.h"

void UmlBaseUseCaseAssociation::read_(const QHash<void*,UmlUseCaseReference*> & useCases)
{
    _use_case = (UmlUseCaseReference *) useCases[reinterpret_cast<void*>(uintptr_t(UmlCom::read_unsigned()))];
    _actor = (UmlClass *) UmlBaseItem::read_();
    _primary = UmlCom::read_bool();
    _name = UmlCom::read_string();
    _stereotype = UmlCom::read_string();
}
