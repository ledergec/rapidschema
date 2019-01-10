## Gson for C++

[Gson](https://github.com/google/gson) is a great java library for serializing struct and other data such as lists and
maps into json or parsing it from json. rapidschema is not quite as easy to use, but gets close. See below.

### Parsing

Consider the following simple example:

~~~~~~~~~~cpp
TODO
~~~~~~~~~~

It shows how to first parse a string into a C++ class and then serialize it again. The only difference to gson is
that we need to explicitly provide the information which member has which json property name in the CreateMemberMapping
function. This is not necessary in gson because gson uses java reflection to interfere the json property names based on 
the names of the members in the java struct.

### Error handling - best effort parsing

What if a given member is not present in the json string, the string does not have a valid json syntax or one of the 
properties in the json string has an unexpected type?

Rapidschema does a best effort parse. That is, it will not stop parsing after encountering the first error, but will
try to continue if possible. When done with parsing rapidschema reports a ParseResult. This contains a list of all
identified problems with the json string. See the example below:

~~~~~~~~~~cpp
TODO
~~~~~~~~~~

You can decide how to log or report the errors yourself.

### Serialization

It is also quite easy to assemble an object in C++ and then serialize it to a json string. See the following example:

~~~~~~~~~~cpp
TODO
~~~~~~~~~~

## That's all?

No, not at all. There are a number of other cool features in rapidschema which are absolutely worth exploring. Keep
reading on!

## Json schema validation

Ever heard that there is a json schema? A json schema is similar to an xml schema. It allows defining the structure 
and also some constraints on the content of json data. 
[Understanding JSON schema](https://json-schema.org/understanding-json-schema/) is a great resource if you want to get
a quick impression. The [JSON Schema Validator](https://www.jsonschemavalidator.net/) allows you to play with what you
can learn on the first tutorial page. The official json schema specification is currently at draft-07 and is actively
aiming at reaching the RFC status.

So why is this relevant? Rapidschema allows you to define a json schema in code. Parse a json string into the schema and
validate all the schema constraints. During schema validation as with parsing it again does a best effort validation.
In other words, if an error is encountered during validation it will continue and in the end report a list of
all errors encountered.

You can find the full list of examples of supported json schema features [here](TODO).

## Cross validation

NOT YET IMPLEMENTED...

Even though a json schema is quite flexible, you will not be able to express all the cross dependencies of a complex 
software configuration file. What if you have a list of persons, each of which must have a unique id? This kind of
constraint cannot be expressed in a json schema. During cross validation rapidschema allows you to express such 
complex cross dependencies in code. Here you have all the flexibility in the world.

## Hard shell

Cross validation combined with the json schema constraints allows you to build a hard shell for user or other external 
input. If done properly you can reject any invalid configuration right after parsing. Validating user and 
other external input at the boundary of your software will have a tremendous impact on the quality of your source code
as a whole. Since the configuration has been validated you will no longer need to handle any kind of exceptional 
conditions within the rest of the code base. You can simply assert and will not get slogged down by c-style error 
handling or complex exception handling.

## Schema evolution

Well, that's all great. But the real challenge comes over time! The client keeps changing his mind and therefore the
schema needs to change. However, unfortunately there is already a large base of complex configuration which need to 
be ported to the new schema. Rapidschema does not address this issue. However, there are a number of features already
present jsonschema which are therefore available in rapidschema which easy this pain to some degree. For example you
may appreciate that you can assign default values or you can make parts of the schema optional. For more complex 
structural schema changes you will need to write code transforming one into the other. However, this is of course a 
lot easier given a structure such as resulting after parsing with rapidschema rather than operating on the .json files
directly.

## Overlays

NOT YET IMPLEMENTED...

Rapidschema also provides config overlays. Simply put you can parse some kind of base configuration, and then parse
any number of overlay configurations which do not contain a complete configuration, but only part thereof. The values
contained in the overlay configuration will be overwritten. This may be extremly useful if you have a large number of 
very similar configurations.

## Performance

Show benchmark results....

## Advanced features

### Features inherited from rapidjson

Rapidschema is based on rapidjson - which is an extremely versatile and fast json parser. While rapidschema tries to
make the fact that its based on rapidjson transparent to the basic user, an advanced user needs to also read the 
rapidjson documentation. This will allow you to take full advantage of the underlying features and flexibility.

#### Different encodings

Rapidjson supports a number of different encodings: utf8, utf16, utf32. So does rapidschema.

TODO example

#### Pretty printing vs compressed printing

TODO example

### Custom types

Rapidschema already allows you to parse any of the basic types, including strings into objects. However, you wish
to parse the json int directly into an std::chrono::milliseconds. No problem, there is a way to extend rapidschema to 
allow you to do exactly this.

TODO example

