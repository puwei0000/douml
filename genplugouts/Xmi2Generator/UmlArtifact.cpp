
#include "UmlArtifact.h"
#include "FileOut.h"
#include "UmlItem.h"

#include "UmlNcRelation.h"
void UmlArtifact::write(FileOut & out)
{
    const char * k = (_uml_20) ? "ownedMember" : "packagedElement";

    out.indent();
    out << "<" << k << " xmi:type=\"uml:Artifact\"";
    out.id(this);
    out << " name=\"";
    out.quote((const char *)name()); //[jasa] ambiguous call
    out << "\">\n";
    out.indent(+1);

    write_description_properties(out);

    const QVector<UmlItem*> ch = children();
    unsigned i;
    unsigned n = ch.size();
    unsigned rank = 0;

    for (i = 0; i != n; i += 1) {
        UmlItem * x = ch[i];

        if ((x->kind() == aNcRelation) &&
            (x->stereotype() == "manifest") &&
            (((UmlNcRelation *) x)->relationKind() == aDependency))
            write_manifest(out, ((UmlNcRelation *) x)->target(), "dependency", ++rank);
        else
            ch[i]->write(out);
    }

    if (stereotype() == "source") {
        const QVector<UmlClass*> & cls = associatedClasses();

        n = cls.size();

        for (i = 0; i != n; i += 1)
            write_manifest(out, cls[i], "source", ++rank);
    }
    else {
        const QVector<UmlArtifact*> & arts = associatedArtifacts();

        n = arts.size();

        for (i = 0; i != n; i += 1)
            write_manifest(out, arts[i], 0, ++rank);
    }

    out.indent(-1);
    out.indent();
    out << "</" << k << ">\n";

    unload();

}

void UmlArtifact::write_manifest(FileOut & out, UmlItem * x, const char * name, unsigned rank)
{
    out.indent();
    out << "<manifestation xmi:type=\"uml:Manifestation\"";
    out.id_prefix(this, "MANIFESTATION", rank);
    out.ref(this, "client");
    out.ref(x, "supplier");
    out.ref(x, "utilizedElement");

    if (name != 0)
        out << " name=\"" << name << '"';

    out << "/>\n";
}

