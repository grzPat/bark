py_test(
  name = "py_runtime_tests",
  srcs = ["py_runtime_tests.py"],
  data = ['//python:bark.so'],
  imports = ['../../../python/'],
  deps = ["//modules/runtime/commons:parameters",
          "//modules/runtime/commons:roadgraph_generator",
          "//modules/runtime:runtime"],
)

filegroup(
   name="xodr_data",
   srcs=glob(["data/**"]),
   visibility = ["//visibility:public"],
)

py_test(
  name = "py_importer_tests",
  srcs = ["py_importer_tests.py"],
  data = ['//python:bark.so',
          ':xodr_data'],
  imports = ['../../../python/'],
  deps = ["//modules/runtime/commons:parameters",
          "//modules/runtime/commons:xodr_parser",
          "//modules/runtime/commons:roadgraph_generator",
          "//modules/runtime:runtime"],
)