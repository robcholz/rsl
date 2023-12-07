//
// Created by robcholz on 10/8/23.
//
#pragma once

#ifndef RSL_LOG_HPP
#define RSL_LOG_HPP


const char* GetFileNameFromPath(const char* filePath);

#ifdef RSL_DEBUG_ENABLE // TODO cross-platform and support redirect colored output to serial port

#define RSL_LOG_COLOR_INFO(arg, color) color + arg + "\033[0m"
#define RSL_LOG_COLOR_CYAN(arg) RSL_LOG_COLOR_INFO(arg,"\033[36m")
#define RSL_LOG_COLOR_GREEN(arg) RSL_LOG_COLOR_INFO(arg,"\033[32m")
#define RSL_LOG_COLOR_YELLOW(arg) RSL_LOG_COLOR_INFO(arg,"\033[33m")
#define RSL_LOG_COLOR_RED(arg) RSL_LOG_COLOR_INFO(arg,"\033[31m")

#else

#define RSL_LOG_COLOR_INFO(arg, color)
#define RSL_LOG_COLOR_CYAN(arg)
#define RSL_LOG_COLOR_GREEN(arg)
#define RSL_LOG_COLOR_YELLOW(arg)
#define RSL_LOG_COLOR_RED(arg)

#endif


#ifdef RSL_DEBUG_RICH_INFO

#define RSL_INFO_FILE (RSL_TO_STR_STR(__FILE__))
#define RSL_INFO_FUNCTION (RSL_TO_STR_STR(__PRETTY_FUNCTION__))
#define RSL_INFO_LINE (RSL_TO_STR_NUM(__LINE__))

#else

#define RSL_INFO_FILE (RSL_TO_STR_CHAR(__FILE_NAME__))
#define RSL_INFO_FUNCTION (RSL_TO_STR_CHAR(__func__))
#define RSL_INFO_LINE (RSL_TO_STR_NUM(__LINE__))

#endif


#ifdef RSL_DEBUG_ENABLE

#define RSL_LOG_INFO_FORMAT(reason) ("[" + RSL_INFO_FUNCTION + "@" + RSL_INFO_LINE + "] " \
                                + "ERROR: "+ reason + " (File: " + RSL_INFO_FILE + ")" )
#define RSL_RUNTIME_BOUND_CHECK_ARG(condition, arg, functionBody) if(condition) {RSL_LOG_ERROR(arg); functionBody;}
#define RSL_RUNTIME_BOUND_CHECK(condition, arg) if(condition) {RSL_LOG_ERROR(arg);}
#define RSL_COMPILETIME_BOUND_CHECK(condition, arg) static_assert((condition), arg)
#define RSL_LOG_INFO(arg) RSL_PRINTF(RSL_LOG_INFO_FORMAT(arg))
#define RSL_LOG_DEBUG(arg) RSL_PRINTF(RSL_LOG_INFO_FORMAT(arg)) // TODO
#define RSL_LOG_WARNING(arg) RSL_PRINTF(RSL_LOG_INFO_FORMAT(arg)) // TODO
#define RSL_LOG_ERROR(arg) RSL_PRINTF(RSL_LOG_INFO_FORMAT(arg))

#else // RSL_DEBUG_ENABLE

#define RSL_PRINT(arg)
#define RSL_PRINTF(arg)
#define RSL_RUNTIME_BOUND_CHECK_ARG(condition, arg, functionBody)
#define RSL_RUNTIME_BOUND_CHECK(condition, arg)
#define RSL_COMPILETIME_BOUND_CHECK(condition, arg)
#define RSL_LOG_INFO(arg)
#define RSL_LOG_DEBUG(arg)
#define RSL_LOG_WARNING(arg)
#define RSL_LOG_ERROR(arg)

#endif

#endif //RSL_LOG_HPP
