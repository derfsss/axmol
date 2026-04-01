/*
 * GL-amigaos4.h — GLES2 header for AmigaOS4
 *
 * GL functions come from clean Khronos GLES2 headers (axmol/shim/),
 * linked against libGLESv2.a at build time.
 *
 * Extension functions (VAO, instancing) are NOT available in libGLESv2.a.
 * axmol's AX_GLES_PROFILE=200 code paths already skip these.
 */
#pragma once

#include "platform/PlatformConfig.h"

#include "glad/gl.h"

/* Map GL constants to GLES2 OES equivalents */
#define GL_DEPTH_STENCIL GL_DEPTH_STENCIL_OES
#define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#define GL_UNSIGNED_INT_24_8 GL_UNSIGNED_INT_24_8_OES
#define glClearDepth glClearDepthf

/* Constants not in GLES2 core but referenced by axmol */
#ifndef GL_RGBA8
#define GL_RGBA8 0x8058
#endif
#ifndef GL_COMPRESSED_RGB8_ETC2
#define GL_COMPRESSED_RGB8_ETC2             0x9274
#define GL_COMPRESSED_SRGB8_ETC2            0x9275
#define GL_COMPRESSED_RGBA8_ETC2_EAC        0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#endif
#ifndef GL_VERTEX_ARRAY_BINDING
#define GL_VERTEX_ARRAY_BINDING 0x85B5
#endif
