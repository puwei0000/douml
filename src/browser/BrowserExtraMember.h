//Added by qt3to4:
#include <QPixmap>
#include <QDropEvent>
#include <QTextStream>
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

#ifndef BROWSER_EXTRAMEMBER_H
#define BROWSER_EXTRAMEMBER_H

class QPixmap;
class ExtraMemberData;

#include "BrowserNode.h"
#include "Labeled.h"

class BrowserExtraMember : public BrowserNode, public Labeled<BrowserExtraMember>
{
protected:
    static IdDict<BrowserExtraMember> all;

    ExtraMemberData * def;

protected:
    BrowserExtraMember(int id);

    void exec_menu_choice(int rank);

public:
    BrowserExtraMember(const QString & s, BrowserNode * p, ExtraMemberData * d, int id = 0);
    BrowserExtraMember(const BrowserExtraMember * model, BrowserNode * p);
    virtual ~BrowserExtraMember();

    virtual BrowserNode * duplicate(BrowserNode * p,
                                    const QString & name = QString()) override;

    virtual const QPixmap * pixmap(int) const override;

    virtual void menu() override;
    virtual void apply_shortcut(const QString & s) override;
    virtual void open(bool) override;
    virtual UmlCode get_type() const override;
    virtual QString get_stype() const override;
    virtual int get_identifier() const override;
    virtual const char * help_topic() const override;
    virtual void modified() override;
    virtual BasicData * get_data() const override;
    virtual void set_name(const QString & s) override;
    virtual bool same_name(const QString & s, UmlCode type) const override;
    virtual QString full_name(bool rev = FALSE, bool itself = TRUE) const override;
    virtual void member_cpp_def(const QString & prefix, const QString &,
                                QString & s, bool templ) const override;
    virtual bool allow_empty() const override;

    virtual void save(QTextStream &, bool ref, QString & warning) override;
    static BrowserExtraMember * read(char *& , char *, BrowserNode *);
    static BrowserNode * get_it(const char * k, int id);

    static BrowserExtraMember * new_one(const QString & s, BrowserNode * p);

    static void clear(bool old);
    static void update_idmax_for_root();
    virtual void renumber(int phase) override;
    virtual void prepare_update_lib() const override;

    virtual bool tool_cmd(ToolCom * com, const char * args) override;

    virtual void DropAfterEvent(QDropEvent * e, BrowserNode * after) override;
};

#endif

