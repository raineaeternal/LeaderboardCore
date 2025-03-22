#pragma once

#define LBCORE_EXPORT __attribute__((visibility("default")))
#define LBCORE_EXPORT_FUNC extern "C" LBCORE_EXPORT