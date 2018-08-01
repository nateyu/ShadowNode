#include "iotjs_def.h"

JS_FUNCTION(StartProfiling) {
  if (!jerry_enable_cpu_profiling())
    return JS_CREATE_ERROR(COMMON, "cpu profiling is not enabled.");
  if (!jerry_value_is_number(jargv[0]))
    return JS_CREATE_ERROR(COMMON, "profiler type should be required.");
  if (!jerry_value_is_string(jargv[1]))
    return JS_CREATE_ERROR(COMMON, "filepath should be required.");
  if (!jerry_value_is_number(jargv[2]))
    return JS_CREATE_ERROR(COMMON, "duration should be number.");

  int type = JS_GET_ARG(0, number);
  printf ("cpu profiler type = %d\n", type);
  iotjs_string_t filepath = JS_GET_ARG(1, string);
  double duration = JS_GET_ARG(2, number);
  bool res =
      jerry_start_cpu_profiling(type, (const char*)iotjs_string_data(&filepath),
                                duration);
  // iotjs_string_destroy(&filepath);
  return jerry_create_boolean(res);
}

JS_FUNCTION(StopProfiling) {
  if (!jerry_enable_cpu_profiling())
    return JS_CREATE_ERROR(COMMON, "cpu profiling is not enabled.");
  bool res = jerry_stop_cpu_profiling();
  if (!res)
    return JS_CREATE_ERROR(COMMON, "profiling is not started.");
  return jerry_create_boolean(res);
}

jerry_value_t InitProfiler() {
  jerry_value_t profiler = jerry_create_object();
  iotjs_jval_set_method(profiler, "startProfiling", StartProfiling);
  iotjs_jval_set_method(profiler, "stopProfiling", StopProfiling);
  return profiler;
}
