--- core/Common/3dParty/v8/v8/src/objects/js-list-format.cc.orig	2020-12-15 11:23:25 UTC
+++ core/Common/3dParty/v8/v8/src/objects/js-list-format.cc
@@ -29,46 +29,27 @@ namespace v8 {
 namespace internal {
 
 namespace {
-const char* kStandard = "standard";
-const char* kOr = "or";
-const char* kUnit = "unit";
-const char* kStandardShort = "standard-short";
-const char* kOrShort = "or-short";
-const char* kUnitShort = "unit-short";
-const char* kStandardNarrow = "standard-narrow";
-const char* kOrNarrow = "or-narrow";
-const char* kUnitNarrow = "unit-narrow";
 
-const char* GetIcuStyleString(JSListFormat::Style style,
-                              JSListFormat::Type type) {
+UListFormatterWidth GetIcuWidth(JSListFormat::Style style) {
+  switch (style) {
+    case JSListFormat::Style::LONG:
+      return ULISTFMT_WIDTH_WIDE;
+    case JSListFormat::Style::SHORT:
+      return ULISTFMT_WIDTH_SHORT;
+    case JSListFormat::Style::NARROW:
+      return ULISTFMT_WIDTH_NARROW;
+  }
+  UNREACHABLE();
+}
+
+UListFormatterType GetIcuType(JSListFormat::Type type) {
   switch (type) {
     case JSListFormat::Type::CONJUNCTION:
-      switch (style) {
-        case JSListFormat::Style::LONG:
-          return kStandard;
-        case JSListFormat::Style::SHORT:
-          return kStandardShort;
-        case JSListFormat::Style::NARROW:
-          return kStandardNarrow;
-      }
+      return ULISTFMT_TYPE_AND;
     case JSListFormat::Type::DISJUNCTION:
-      switch (style) {
-        case JSListFormat::Style::LONG:
-          return kOr;
-        case JSListFormat::Style::SHORT:
-          return kOrShort;
-        case JSListFormat::Style::NARROW:
-          return kOrNarrow;
-      }
+      return ULISTFMT_TYPE_OR;
     case JSListFormat::Type::UNIT:
-      switch (style) {
-        case JSListFormat::Style::LONG:
-          return kUnit;
-        case JSListFormat::Style::SHORT:
-          return kUnitShort;
-        case JSListFormat::Style::NARROW:
-          return kUnitNarrow;
-      }
+      return ULISTFMT_TYPE_UNITS;
   }
   UNREACHABLE();
 }
@@ -143,7 +124,7 @@ MaybeHandle<JSListFormat> JSListFormat::New(Isolate* i
   icu::Locale icu_locale = r.icu_locale;
   UErrorCode status = U_ZERO_ERROR;
   icu::ListFormatter* formatter = icu::ListFormatter::createInstance(
-      icu_locale, GetIcuStyleString(style_enum, type_enum), status);
+      icu_locale, GetIcuType(type_enum), GetIcuWidth(style_enum), status);
   if (U_FAILURE(status) || formatter == nullptr) {
     delete formatter;
     THROW_NEW_ERROR(isolate, NewRangeError(MessageTemplate::kIcuError),
