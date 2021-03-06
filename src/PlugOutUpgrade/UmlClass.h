// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef UMLCLASS_H
#define UMLCLASS_H


//Added by qt3to4:
#include "misc/mystr.h"

#include "UmlBaseClass.h"
#include "aRelationKind.h"

class UmlPackage;
class UmlClass;
class UmlClassView;
class UmlArtifact;
class UmlDeploymentView;
class UmlOperation;
class UmlAttribute;
class UmlRelation;

// This class manages 'classes'
// You can modify it as you want (except the constructor)

class UmlClass : public UmlBaseClass
{
public:
    UmlClass(void * id, const WrapperStr & n)
        : UmlBaseClass(id, n) {};

    void made(UmlClassView * base_class_view, UmlClassView * user_class_view,
              UmlDeploymentView * base_depl_view, UmlDeploymentView * user_depl_view,
              UmlClass * base_item, WrapperStr s, UmlClass *& base,
              UmlClass *& user, UmlClass * user_interf = 0);

    void made(UmlClassView * base_class_view, UmlClassView * user_class_view,
              UmlArtifact * base_art, UmlArtifact * user_art,
              UmlClass * base_item, WrapperStr s, UmlClass *& base,
              UmlClass *& user, UmlClass * user_interf = 0);

    static UmlClass * made(UmlClassView * class_view,
                           UmlDeploymentView * depl_view,
                           WrapperStr s, bool interf = FALSE);

    static UmlClass * made(UmlClassView * class_view,
                           UmlArtifact * art,
                           WrapperStr s, bool interf = FALSE);

    void add_kind(const char * k);
    void add_default_base_op(UmlClass * super, UmlClass * user,
                             UmlClass * parent, WrapperStr s,
                             const char * k, bool unnamed = FALSE);
    UmlOperation * add_constr(UmlClass * super, aVisibility, bool unnamed = FALSE);
    UmlOperation * add_destr(aVisibility, const char * comment = 0);
    UmlOperation * add_op(const char * name, aVisibility,
                          UmlClass * return_type, bool excpt = FALSE);
    UmlOperation * add_op(const char * name, aVisibility,
                          const char * return_type, bool excpt = FALSE);
    UmlOperation * add_op(const char * name, aVisibility,
                          UmlTypeSpec & return_type, bool excpt = FALSE);
    UmlAttribute * add_attribute(const char * name, aVisibility v,
                                 UmlClass * type,
                                 const char * if_def, const char * end_if,
                                 const char * bitfield = 0);
    UmlAttribute * add_attribute(const char * name, aVisibility v,
                                 const char * type,
                                 const char * if_def, const char * end_if,
                                 const char * bitfield = 0);
    UmlAttribute * add_attribute(const char * name, aVisibility v,
                                 UmlTypeSpec & type,
                                 const char * if_def, const char * end_if,
                                 const char * bitfield = 0);
    UmlAttribute * add_enum_item(const char * name);
    UmlRelation * add_relation(aRelationKind k, const char * name,
                               aVisibility v, UmlClass * type,
                               const char * if_def, const char * end_if,
                               const char * bitfield = 0);
    UmlRelation * add_vect_assoc(const char * name, aVisibility v, UmlClass * type,
                                 const char * if_def, const char * end_if);
    UmlOperation * get_operation(const char *);
    UmlAttribute * get_attribute(const char *);
    UmlRelation * get_relation(const char * = 0);
    UmlRelation * get_relation(aRelationKind k, const char * = 0);

    virtual void replace_friend();
    void add_friend(const char *);
};

#endif
