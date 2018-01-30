/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a MIT-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//---------------------------------------------------------------------------
#ifndef DPXH
#define DPXH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Lib/FFV1/FFV1_Frame.h"
#include <cstdint>
//---------------------------------------------------------------------------

typedef void(*write_file_call)(uint8_t*, uint64_t, void*);

class dpx
{
public:
    dpx();

    uint8_t*                    Buffer;
    uint64_t                    Buffer_Size;

    bool                        Parse();

    frame                       Frame;

    write_file_call             WriteFileCall;
    void*                       WriteFileCall_Opaque;

    // Info
    uint64_t                    Style;

    // Error message
    const char*                 ErrorMessage();

    enum style
    {
        RGB_10_MethodA_LE,
        RGB_10_MethodA_BE,
        RGB_16_BE,
        RGBA_8,
        RGBA_16_BE,
        DPX_Style_Max,
    };

private:
    size_t                      Buffer_Offset;
    bool                        IsBigEndian;
    uint8_t                     Get_X1() { return Buffer[Buffer_Offset++]; }
    uint16_t                    Get_L2();
    uint16_t                    Get_B2();
    uint32_t                    Get_X2() { return IsBigEndian ? Get_B2() : Get_L2(); }
    uint32_t                    Get_L4();
    uint32_t                    Get_B4();
    uint32_t                    Get_X4() { return IsBigEndian ? Get_B4() : Get_L4(); }

    // Error message
    const char*                 error_message;
    bool                        Error(const char* Error) { error_message = Error; return true; }
};

//---------------------------------------------------------------------------
#endif