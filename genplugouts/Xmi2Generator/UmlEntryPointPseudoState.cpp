
#include "UmlEntryPointPseudoState.h"
#include "FileOut.h"

void UmlEntryPointPseudoState::write(FileOut & out)
{
    UmlEntryPointPseudoState * ref = reference();

    out.indent();

    if (ref != 0)
        out << "<connection";
    else
        out << "<subvertex xmi:type=\"uml:Pseudostate\"";

    out.id(this);

    if (! name().isEmpty()) {
        out << " name=\"";
        out.quote(name());
        out << '"';
    }

    if (ref != 0) {
        out.ref(ref, "entry");
        out << ">\n";
    }
    else
        out << " kind=\"entryPoint\">\n";

    out.indent(+1);

    write_description_properties(out);

    while (! _incoming_trans.isEmpty())
        _incoming_trans.takeAt(0)->write_in(out);

    const QVector<UmlItem*> ch = children();
    unsigned n = ch.size();
    unsigned i;

    for (i = 0; i != n; i += 1)
        ch[i]->write(out);

    out.indent(-1);
    out.indent();

    if (ref != 0)
        out << "</connection>\n";
    else
        out << "</subvertex>\n";

    unload();
}

const char * UmlEntryPointPseudoState::sKind() const
{
    return "entryPoint";
}
