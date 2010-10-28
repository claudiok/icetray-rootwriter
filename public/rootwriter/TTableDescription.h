/**
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> Last changed by: $LastChangedBy$
 */

#ifndef ROOTWRITER_TTABLEDESCRIPTION_H_INCLUDED
#define ROOTWRITER_TTABLEDESCRIPTION_H_INCLUDED

#include <TObject.h>

#include <string>
#include <vector>


class TTableDescription : public TObject {
public:
  TTableDescription();
  TTableDescription(const std::string &tableName);

  void AddColumn(const std::string &title, const std::string &unit,
		 const std::string &description, unsigned long length = 1);

  void SetTableName(const std::string &name);
  const std::string& TableName() const;
  void SetCounterName(const std::string &name);
  const std::string& CounterName() const;
  bool isMultiRow() const;

  int NColumns() const;
  std::string GetTitle(unsigned column) const;
  std::string GetUnit(unsigned column) const;
  std::string GetDescription(unsigned column) const;
  unsigned long GetElementLength(unsigned column) const;

  void Print(Option_t* = "") const;

private:
  struct TableColumn {
    std::string title;
    std::string unit;
    std::string description;
    unsigned long length;
  };

  std::string tableName_;
  std::string counterName_;
  std::vector<TableColumn> columns_;

  void ReadFromBuffer(TBuffer &b);
  void SerializeToBuffer(TBuffer &b) const;

  ClassDef(TTableDescription, 1)
};

#endif // ROOTWRITER_TTABLEDESCRIPTION_H_INCLUDED
