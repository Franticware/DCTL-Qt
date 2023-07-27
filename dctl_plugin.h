#ifndef DCTL_PLUGIN_H
#define DCTL_PLUGIN_H

#include "dctl_struct.h"

typedef void* (*DCTL_getParam_t)(int index);
typedef void (*DCTL_transform_t)(unsigned char* result, int p_Width, int p_Height, int p_X, int p_Y, const unsigned char* p_tex, int p_texW, int p_texH);

extern DCTL_getParam_t DCTL_getParam;
extern DCTL_transform_t DCTL_transform;

bool DCTL_loadPlugin(const char* path);

#endif // DCTL_PLUGIN_H
