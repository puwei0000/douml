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

#ifndef _UTIL_H
#define _UTIL_H

#include "misc/mystr.h"

extern WrapperStr capitalize(const WrapperStr & s);
extern bool need_equal(const char * p, const char * v);
extern WrapperStr current_indent(const char * p, const char * begin);

extern void set_verbose();
extern bool verbose();
extern void set_trace_header(WrapperStr s);
extern WrapperStr get_trace_header();
extern void write_trace_header();

extern void incr_error();
extern void incr_warning();
extern int n_errors();
extern int n_warnings();

#endif