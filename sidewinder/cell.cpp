/* Sidewinder - Portable library for spreadsheet 
   Copyright (C) 2003 Ariya Hidayat <ariya@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, US
*/

#include "cell.h"

#include "ustring.h"
#include "format.h"
#include "value.h"

#include <iostream>

namespace Sidewinder
{

class Cell::Private
{
public:
  Sheet* sheet;
  unsigned row;     
  unsigned column;  
  Value value;
  Format format;
  unsigned columnSpan;
  unsigned rowSpan;
  QVariant sender;
  
};

};

using namespace Sidewinder;

Cell::Cell( Sheet* sheet, unsigned column, unsigned row )
{
  d = new Cell::Private();
  d->sheet      = sheet;
  d->column     = column;
  d->row        = row;
  d->value      = Value::empty();
  d->columnSpan = 1;
  d->rowSpan    = 1;
  d->sender   = QVariant();
};

Cell::~Cell()
{
  delete d;
}

Sheet* Cell::sheet()
{
  return d->sheet;
}

unsigned Cell::column() const
{
  return d->column;
}

unsigned Cell::row() const
{
  return d->row;
}

UString Cell::name() const
{
  return name( column(), row() ); 
}

UString Cell::name( unsigned column, unsigned row )
{
  return columnLabel( column ) + UString::from( row );  
}

UString Cell::columnLabel() const
{
  return columnLabel( column() );
}

// FIXME be careful for integer overflow
UString Cell::columnLabel( unsigned column )
{
  UString str;
  unsigned digits = 1;
  unsigned offset = 0;
  
  for( unsigned limit = 26; column >= limit+offset; limit *= 26, digits++ )
    offset += limit;
      
  for( unsigned c = column - offset; digits; --digits, c/=26 )
    str = UString( UChar( 'A' + (c%26) ) ) + str;
    
  return str;
}

Value Cell::value() const
{
  return d->value;
}

QString Cell::sender() const
{
  return d->sender.value<QString>(); 
}

void Cell::setValue( const Value& value , QVariant v  )
{
  d->value = value;
  QString now = d->sender.value<QString>(); 
  QString s = v.value<QString>(); 
  now.append("/");
  now.append(s);
  d->sender = QVariant(now);
  // TODO mark the cell as dirty
}

Format Cell::format() const
{
  return d->format;
}

void Cell::setFormat( const Format& format )
{
  d->format = format;
  // TODO mark the cell as dirty
}

unsigned Cell::columnSpan() const
{
  return d->columnSpan;
}

void Cell::setColumnSpan( unsigned span )
{
  if( span < 1 ) return;
  d->columnSpan = span;
}

unsigned Cell::rowSpan() const
{
  return d->rowSpan;
}

void Cell::setRowSpan( unsigned span )
{
  if( span < 1 ) return;
  d->rowSpan = span;
}
