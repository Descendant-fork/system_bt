/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fields/reserved_field.h"
#include "util.h"

int ReservedField::unique_id_ = 0;

ReservedField::ReservedField(int size, ParseLocation loc)
    : PacketField(loc, "ReservedScalar" + std::to_string(unique_id_++)), type_(PacketField::Type::RESERVED_SCALAR),
      size_(size) {}

PacketField::Type ReservedField::GetFieldType() const {
  return type_;
}

Size ReservedField::GetSize() const {
  return size_;
}

std::string ReservedField::GetType() const {
  return util::GetTypeForSize(size_);
}

void ReservedField::GenGetter(std::ostream&, Size, Size) const {
  // There is no Getter for a reserved field
}

bool ReservedField::GenBuilderParameter(std::ostream&) const {
  // There is no builder parameter for a reserved field
  return false;
}

bool ReservedField::HasParameterValidator() const {
  return false;
}

void ReservedField::GenParameterValidator(std::ostream&) const {
  // There is no builder parameter for a reserved field
}

void ReservedField::GenInserter(std::ostream& s) const {
  s << "insert(static_cast<" << util::GetTypeForSize(GetSize().bits()) << ">(0) /* Reserved */, i, " << GetSize().bits()
    << " );\n";
}

void ReservedField::GenValidator(std::ostream&) const {
  // There is no need to validate the value of a reserved field
}