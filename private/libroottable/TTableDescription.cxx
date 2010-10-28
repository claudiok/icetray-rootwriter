/*
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> Last changed by: $LastChangedBy$
 */

#include "rootwriter/TTableDescription.h"

#include <boost/foreach.hpp>

#include <iomanip>
#include <iostream>


namespace {

  std::string readString(TBuffer &b);

}


ClassImp(TTableDescription)


TTableDescription::TTableDescription()
  : tableName_(""), counterName_(""), columns_()
{}

TTableDescription::TTableDescription(const std::string &tableName)
  : tableName_(tableName), counterName_(""), columns_()
{}

void TTableDescription::AddColumn(const std::string &title, const std::string &unit,
		 const std::string &description, unsigned long length)
{
  TableColumn column = { title, unit, description, length };
  columns_.push_back(column);
}

void TTableDescription::SetTableName(const std::string &name)
{
  tableName_ = name;
}

const std::string& TTableDescription::TableName() const
{
  return tableName_;
}

void TTableDescription::SetCounterName(const std::string &name)
{
  counterName_ = name;
}

const std::string& TTableDescription::CounterName() const
{
  return counterName_;
}

bool TTableDescription::isMultiRow() const
{
  return !counterName_.empty();
}

int TTableDescription::NColumns() const
{
  return columns_.size();
}

std::string TTableDescription::GetTitle(unsigned column) const
{
  if (column < columns_.size()) return columns_[column].title;
  return "";
}

std::string TTableDescription::GetUnit(unsigned column) const
{
  if (column < columns_.size()) return columns_[column].unit;
  return "";
}

std::string TTableDescription::GetDescription(unsigned column) const
{
  if (column < columns_.size()) return columns_[column].description;
  return "";
}

unsigned long TTableDescription::GetElementLength(unsigned column) const
{
  if (column < columns_.size()) return columns_[column].length;
  return 0;
}

void TTableDescription::Print(Option_t*) const
{
  std::cout << "Table: " << tableName_;
  if (!counterName_.empty()) {
    std::cout << " (multi row), Counter: " << counterName_;
  }
  std::cout << '\n';

  static const std::string TITLE = "Title";
  static const size_t TITLE_LENGTH = 20;
  static const std::string UNIT = "Unit";
  static const size_t UNIT_LENGTH = 8;
  static const std::string LENGTH = "Length";
  static const size_t LENGTH_LENGTH = 6;
  static const std::string DESCRIPTION = "Description";

  std::cout << std::setw(TITLE_LENGTH) << TITLE << '\t'
	    << std::setw(UNIT_LENGTH) << UNIT << '\t'
	    << std::setw(LENGTH_LENGTH) << LENGTH << '\t'
	    << DESCRIPTION << '\n';

  BOOST_FOREACH(const TableColumn &column, columns_) {
    std::string title_label = column.title.substr(0, TITLE_LENGTH);
    std::cout << std::setw(TITLE_LENGTH) << title_label << '\t'
	      << std::setw(UNIT_LENGTH) << column.unit << '\t'
	      << std::setw(LENGTH_LENGTH) << column.length << '\t'
	      << column.description << '\n';
  }
  std::cout << std::flush;
}

void TTableDescription::Streamer(TBuffer &b)
{
  if (b.IsReading()) {
    ReadFromBuffer(b);
  } else {
    SerializeToBuffer(b);
  }
}


void TTableDescription::ReadFromBuffer(TBuffer &b)
{
  Version_t version = b.ReadVersion();
  if (version > TTableDescription::Class_Version()) {
    Fatal(__PRETTY_FUNCTION__, "Cannot read TTableDescription Version %d", version);
  }

  tableName_ = readString(b);
  counterName_ = readString(b);
  ULong64_t nColumn;
  b >> nColumn;
  for (ULong64_t i = 0; i < nColumn; ++i) {
    TableColumn column;
    column.title = readString(b);
    column.unit = readString(b);
    column.description = readString(b);
    ULong64_t column_length;
    b >> column_length;
    column.length = column_length;
    columns_.push_back(column);
  }
}

void TTableDescription::SerializeToBuffer(TBuffer &b) const
{
  b.WriteVersion(TTableDescription::IsA());
  b << tableName_.c_str();
  b << counterName_.c_str();
  b << (ULong64_t)columns_.size();
  BOOST_FOREACH(const TableColumn &column, columns_) {
    b << column.title.c_str();
    b << column.unit.c_str();
    b << column.description.c_str();
    b << (ULong64_t)column.length;
  }
}


namespace {

  std::string readString(TBuffer &b)
  {
    std::string result;
    char c;
    for (;;) {
      b >> c;
      if (c == 0) break;
      result.push_back(c);
    }

    return result;
  }

}
