//
// Created by robcholz on 9/22/23.
//
#pragma once

#ifndef RSL_INTERNAL_H
#define RSL_INTERNAL_H

#define RSL_DEBUG_ENABLE // TODO

#include <portable/Portable.hpp>
#include <log/Log.hpp>


#define RSL_ANNO_NODISCARD [[nodiscard]]
#define RSL_ANNO_UNUSED [[maybe_unused]]

#define RSL_UNUSED RSL_ANNO_UNUSED
#define RSL_NODISCARD RSL_ANNO_NODISCARD RSL_ANNO_UNUSED

#endif//RSL_INTERNAL_H
