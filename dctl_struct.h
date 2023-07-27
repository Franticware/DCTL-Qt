#ifndef DCTL_STRUCT_H
#define DCTL_STRUCT_H

#define DCTL_CHECKBOX 0
#define DCTL_SLIDER 1

struct DCTL_generic
{
    int type;
    const char* name;
    const char* label;
};

struct DCTL_slider
{
    int type;
    const char* name;
    const char* label;
    float val, def, lo, hi, step;
};

struct DCTL_checkBox
{
    int type;
    const char* name;
    const char* label;
    int val, def;
};

#endif // DCTL_STRUCT_H
