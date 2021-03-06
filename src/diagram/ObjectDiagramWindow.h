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

#ifndef OBJECTDIAGRAMWINDOW_H
#define OBJECTDIAGRAMWINDOW_H

#include "DiagramWindow.h"

class QToolButton;
class QSpinBox;

class ObjectDiagramView;
class BrowserObjectDiagram;

class ObjectDiagramWindow : public DiagramWindow
{
    Q_OBJECT

protected:
    ObjectDiagramView * view;
    QToolButton * addClass;
    QToolButton * addClassInstance;
    QToolButton * addPackage;
    QToolButton * addFragment;
    QToolButton * addLink;
    QToolButton * note;
    QToolButton * anchor;
    QToolButton * text;
    QToolButton * image;

public:
    ObjectDiagramWindow(const QString & s, BrowserObjectDiagram *, int id = -1);
    virtual ~ObjectDiagramWindow();

    virtual DiagramView * get_view() const override;

    virtual void hit_button(UmlCode, QToolButton *) override;

protected slots:
    void hit_class();
    void hit_classinstance();
    void hit_package();
    void hit_fragment();
    void hit_link();
    void hit_note();
    void hit_anchor();
    void hit_text();
    void hit_image();
};

#endif
