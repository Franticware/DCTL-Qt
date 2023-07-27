#ifndef DCTL_PARTB_H
#define DCTL_PARTB_H

extern "C"
{

void* DCTL_getParam(int index)
{
    if (index < int(dctlUiVect.size()))
    {
        return dctlUiVect[index];
    }
    else
    {
        return 0;
    }
}

void DCTL_transform(unsigned char* result, int p_Width, int p_Height, int p_X, int p_Y, const unsigned char* p_tex, int p_texW, int p_texH)
{
    Texture txr(p_texW, p_texH, p_tex + 2);
    Texture txg(p_texW, p_texH, p_tex + 1);
    Texture txb(p_texW, p_texH, p_tex + 0);
    float3 color = ::transform(p_Width, p_Height, p_X, p_Y, txr, txg, txb);
    int rc = color.z * 255;
    int gc = color.y * 255;
    int bc = color.x * 255;
    result[0] = std::clamp(rc, 0, 255);
    result[1] = std::clamp(gc, 0, 255);
    result[2] = std::clamp(bc, 0, 255);
    result[3] = 255;
}

}

#endif // DCTL_PARTB_H
