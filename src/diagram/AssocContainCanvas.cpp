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





#include <qcursor.h>
//#include <q3popupmenu.h>
//Added by qt3to4:
#include <QTextStream>

#include "AssocContainCanvas.h"
#include "ArrowPointCanvas.h"
#include "ArtifactCanvas.h"
#include "UmlCanvas.h"
#include "LabelCanvas.h"
#include "StereotypeDialog.h"
#include "myio.h"
#include "ToolCom.h"
#include "Tool.h"
#include "ui/menufactory.h"
#include "DialogUtil.h"
#include "translate.h"

AssocContainCanvas::AssocContainCanvas(UmlCanvas * canvas, DiagramItem * b,
                                       DiagramItem * e, int id, float d_start, float d_end)
    : ArrowCanvas(canvas, b, e, UmlContain, id, TRUE, d_start, d_end)
{
    // note : can't be a self relation
}

AssocContainCanvas::~AssocContainCanvas()
{
}

void AssocContainCanvas::open()
{
    ArrowCanvas * plabel;
    ArrowCanvas * pstereotype;
    QStringList defaults;

    search_supports(plabel, pstereotype);

    if (edit(defaults, plabel, pstereotype)) {
        canvas()->update();
        package_modified();
    }
}

void AssocContainCanvas::menu(const QPoint &)
{
    QMenu m(0);
    QMenu geo(0);
    ArrowCanvas * aplabel;
    ArrowCanvas * apstereotype;

    search_supports(aplabel, apstereotype);

    AssocContainCanvas * plabel = (AssocContainCanvas *) aplabel;
    AssocContainCanvas * pstereotype = (AssocContainCanvas *) apstereotype;

    MenuFactory::createTitle(m, tr("Association"));
    m.addSeparator();
    MenuFactory::addItem(m, tr("Edit"), 1);

    if (pstereotype || plabel) {
        m.addSeparator();
        MenuFactory::addItem(m, tr("Select stereotype and label"), 2);
        MenuFactory::addItem(m, tr("Default stereotype and label position"), 3);

        if (plabel && (label == 0))
            MenuFactory::addItem(m, tr("Attach label to this segment"), 4);

        if (pstereotype && (stereotype == 0))
            MenuFactory::addItem(m, tr("Attach stereotype to this segment"), 5);
    }

    if (get_start() != get_end()) {
        m.addSeparator();
        init_geometry_menu(geo, 10);
        MenuFactory::insertItem(m, tr("Geometry (Ctrl+l)"), &geo);
    }

    m.addSeparator();
    MenuFactory::addItem(m, tr("Remove from diagram"), 6);
    MenuFactory::addItem(m, tr("Delete from model"), 7);

    QAction *retAction = m.exec(QCursor::pos());
    if(retAction)
    {
        int rank = retAction->data().toInt();

        switch (rank) {
        case 1:
            open();
            return;

        case 2:
            the_canvas()->unselect_all();

            if (plabel)
                the_canvas()->select(plabel->label);

            if (pstereotype)
                the_canvas()->select(pstereotype->stereotype);

            return;

        case 3:
            if (plabel)
                plabel->default_label_position();

            if (pstereotype)
                pstereotype->default_stereotype_position();

            break;

        case 4:
            label = plabel->label;
            plabel->label = 0;
            default_label_position();
            break;

        case 5:
            stereotype = pstereotype->stereotype;
            pstereotype->stereotype = 0;
            default_stereotype_position();
            break;

        case 6:
            // not removed from the model : just hide it
            remove(FALSE);
            break;

        case 7:
            get_start()->unassociate(get_end());	// line will be deleted
            break;

        default:
            if (rank >= 10) {
                rank -= 10;

                if (rank == RecenterBegin)
                    set_decenter(-1.0, decenter_end);
                else if (rank == RecenterEnd)
                    set_decenter(decenter_begin, -1.0);
                else if (rank != (int) geometry)
                    set_geometry((LineGeometry) rank, TRUE);
                else
                    return;
            }
            else
                return;
        }
    }

    package_modified();
}

void AssocContainCanvas::remove(bool from_model)
{
    if (!from_model) {
        if (the_canvas()->must_draw_all_relations()) {
            const AssocContainCanvas * a = this;

            while (a->begin->typeUmlCode() == UmlArrowPoint) {
                a = (AssocContainCanvas *)((ArrowPointCanvas *) a->begin)->get_other(a);

                if (a == 0)
                    break;
            }

            if (a && !a->begin->isSelected() && !a->begin->get_bn()->deletedp()) {
                a = this;

                while (a->end->typeUmlCode() == UmlArrowPoint) {
                    a = (AssocContainCanvas *)((ArrowPointCanvas *) a->end)->get_other(a);

                    if (a == 0)
                        break;
                }

                if (a && !a->end->isSelected() && !a->end->get_bn()->deletedp()) {
                    msg_warning("Douml", tr("<i>Draw all relations</i> forced to <i>no</i>"));
                    the_canvas()->dont_draw_all_relations();
                }
            }
        }

        delete_it();
    }
    else
        get_start()->unassociate(get_end());	// line will be deleted
}

void AssocContainCanvas::delete_available(BooL & in_model, BooL & out_model) const
{
    out_model |= TRUE;
    in_model |= TRUE;
}

ArrowPointCanvas * AssocContainCanvas::brk(const QPoint & p)
{
    ArrowPointCanvas * ap =
            new ArrowPointCanvas(the_canvas(), p.x(), p.y());

    ap->setZValue(zValue() + 1);

    AssocContainCanvas * other =
            new AssocContainCanvas(the_canvas(), ap, end, 0,
                                   decenter_begin, decenter_end);

    ap->add_line(this);
    end->remove_line(this, TRUE);
    end = ap;

    //update_pos();

    ap->show();
    other->show();

    modified();
    other->modified();

    return ap;
}

void AssocContainCanvas::save(QTextStream & st, bool ref, QString & warning) const
{
    if (ref)
        st << "containcanvas_ref " << get_ident();
    else if (begin->typeUmlCode() != UmlArrowPoint) {
        nl_indent(st);
        st << "containcanvas " << get_ident();

        if (geometry != NoGeometry) {
            st << " geometry " << stringify(geometry);

            if (!fixed_geometry)
                st << " unfixed";
        }

        if (decenter_begin >= 0) {
            // float output/input bugged
            st << "decenter_begin " << ((int)(decenter_begin * 1000));
        }

        if (decenter_end >= 0) {
            // float output/input bugged
            st << " decenter_end " << ((int)(decenter_end * 1000));
        }

        indent(+1);
        save_lines(st, TRUE, TRUE, warning);
        indent(-1);
    }
}

static ArrowCanvas * make(UmlCanvas * canvas, DiagramItem * b, DiagramItem * e,
                          UmlCode, float d_start, float d_end, int id)
{
    return new AssocContainCanvas(canvas, b, e, id, d_start, d_end);
}

AssocContainCanvas * AssocContainCanvas::read(char *& st, UmlCanvas * canvas, char * k)
{
    if (!strcmp(k, "containcanvas_ref"))
        return ((AssocContainCanvas *) dict_get(read_id(st), "contain canvas", canvas));
    else if (!strcmp(k, "containcanvas")) {
        int id = read_id(st);
        LineGeometry geo;
        bool fixed;

        k = read_keyword(st);	// may read id

        if (!strcmp(k, "geometry")) {
            geo = line_geometry(read_keyword(st));
            k = read_keyword(st);

            if (! strcmp(k, "unfixed")) {
                k = read_keyword(st);
                fixed = FALSE;
            }
            else
                fixed = TRUE;
        }
        else {
            geo = NoGeometry;
            fixed = FALSE;
        }

        float dbegin;
        float dend;

        if (! strcmp(k, "decenter_begin")) {
            dbegin = read_double(st) / 1000;
            k = read_keyword(st);
        }
        else
            dbegin = -1;

        if (! strcmp(k, "decenter_end")) {
            dend = read_double(st) / 1000;
            k = read_keyword(st);
        }
        else
            dend = -1;

        unread_keyword(k, st);

        AssocContainCanvas * r = (AssocContainCanvas *)
                read_list(st, canvas, UmlContain, geo, fixed, dbegin, dend, id, &make);

        // remove association between components available in the
        // 2.0 deployment diagrams
        if (r->begin->typeUmlCode() == UmlComponent)
            Undefined.append(r);
        else if (read_file_format() == 30)
            // to remove redondant transitions made by release 2.22
            RelsToCheck.append(r);

        return r;
    }
    else
        return 0;
}

