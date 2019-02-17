// Copyright (C) 2019 Christian Ledergerber

#ifndef INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_H_
#define INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_H_

#ifdef RAPIDSCHEMA_WITH_SCHEMA_GENERATION

#include "rapidschema/schema/object_schema_interface.h"

namespace rapidschema {
namespace schema {

class SubSchema;


class PropertiesSchema : public NoAdditionalProperties<Object> {
 public:
  PropertiesSchema();

  std::shared_ptr<PatternProperty<SubSchema>> properties;

 protected:
  PatternPropertyList CreatePatternPropertyList() const override;
};


class PatternPropertiesSchema : public NoAdditionalProperties<Object> {
 public:
  PatternPropertiesSchema();

  std::shared_ptr<PatternProperty<SubSchema>> pattern_properties;

 protected:
  PatternPropertyList CreatePatternPropertyList() const override;
};

class ObjectSchema : public TypeSchema ,
                     public ObjectSchemaInterface {
 public:
  ObjectSchema();

  std::shared_ptr<OptionalConfig<PropertiesSchema>> properties;

  std::shared_ptr<OptionalConfig<PatternPropertiesSchema>> pattern_properties;

  OptionalConfig<Value<bool>> additional_properties;

  OptionalConfig<Array<Value<std::string>>> required;

  void AddProperty(const std::string& name, std::shared_ptr<SubSchema> schema) override;
  void AddPatternProperty(const std::string& regex, std::shared_ptr<SubSchema> schema) override;

  void SetAdditionalProperties(bool additional_props) override;

  void AddRequired(const std::string & required_property) override;

  std::shared_ptr<SubSchema> CreateSubSchema() const override;

 protected:
  PropertyMapping CreatePropertyMapping() const override;
};

}  // namespace schema
}  // namespace rapidschema

#endif

#endif  // INCLUDE_RAPIDSCHEMA_SCHEMA_OBJECT_SCHEMA_H_
