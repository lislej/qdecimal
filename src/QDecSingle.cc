/** \file QDecSingle.cc
 * Definitions for the class QDecSingle.
 *
 * (C) Copyright by Semih Cemiloglu
 * All rights reserved, see COPYRIGHT file for details.
 *
 * $Id$
 *
 *
 */

#include "QDecSingle.hh"
extern "C" {
 #include "decimal32.h"
}
#include <stdlib.h>
#include <QTextStream>
#include "QDecNumber.hh"
#include "QDecPacked.hh"
#include "QDecDouble.hh"


QDecSingle& QDecSingle::fromDouble(double d)
{
  char str[MaxStrSize] = {0};

  sprintf(str, "%f", d);
  return fromString(str);
}

QDecSingle& QDecSingle::fromQDecNumber(const QDecNumber& n, QDecContext* c)
{
  decSingleFromNumber(&m_data, n.data(), CXT(c));
  return *this;
}
  
QDecSingle& QDecSingle::fromQDecPacked(const QDecPacked& p)
{
  fromQDecNumber(p.toQDecNumber());
  return *this;
}
  
QDecSingle& QDecSingle::fromWider(const QDecDouble& d, QDecContext* c)
{
  decSingleFromWider(&m_data, d.data(), CXT(c));
  return *this;
}


double QDecSingle::toDouble() const
{
  char str[MaxStrSize] = {0};
  decSingleToString(&m_data, str);
  return atof(str);
}

QDecDouble QDecSingle::toQDecDouble() const
{
  return toWider();
}
  
QDecPacked QDecSingle::toQDecPacked() const
{
  return QDecPacked(toQDecNumber());
}
  
QDecNumber QDecSingle::toQDecNumber() const
{
  decNumber n;
  return decSingleToNumber(&m_data, &n);
}

QDecDouble QDecSingle::toWider() const
{
  decDouble d;
  return decSingleToWider(&m_data, &d);
}

QTextStream& operator<<(QTextStream& ts, const QDecSingle& d)
{
  ts << d.toString();
  return ts;
}