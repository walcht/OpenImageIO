#pragma once

#include "vkformat.h"
#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/fmath.h>
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/strutil.h>
#include <OpenImageIO/tiffutils.h>

OIIO_PLUGIN_NAMESPACE_BEGIN

// this is: "«KTX 20»\r\n\x1A\n"
static const uint8_t KTX2_IDENTIFIER[12] { 0xAB, 0x4B, 0x54, 0x58, 0x20, 0x32,
                                           0x30, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A };

enum class TextureKind : uint32_t {
    SINGLE_TEXTURE_1D,
    SINGLE_TEXTURE_2D,
    SINGLE_TEXTURE_3D,
    CUBEMAP_TEXTURE,
    ARRAY_TEXTURE_1D,
    ARRAY_TEXTURE_2D,
    ARRAY_TEXTURE_3D,
    ARRAY_TEXTURE_CUBEMAP,
};

enum class BlockCompression : uint8_t {
    NONE  = 0,
    BC1   = 1,  ///< aka DXT1
    BC2   = 2,  ///< aka DXT3
    BC3   = 3,  ///< aka DXT5
    BC4   = 4,
    BC5   = 5,
    BC6HU = 6,
    BC6HS = 7,
    BC7   = 8,
    ETC2  = 9,
    EAC   = 10,
    ASTC  = 11,
};

struct FormatInfo {
    int nbrchannels;
    TypeDesc typedesc;
    std::vector<std::string> channelnames;
    std::string colorspace;
    BlockCompression compression { BlockCompression::NONE };
};

struct KTXglFormat {
    uint32_t glInternalformat;
    uint32_t glFormat;
    uint32_t glType;
};

inline bool
extract_info_from_format(VkFormat vkformat, FormatInfo& formatinfo)
{
    switch (vkformat) {
        /* R */
    case VK_FORMAT_R8_UNORM:
    case VK_FORMAT_R8_SNORM:
    case VK_FORMAT_R8_UINT:
    case VK_FORMAT_R8_SINT:
    case VK_FORMAT_R8_SRGB:
        formatinfo = {
            .nbrchannels  = 1,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        break;

        /* RG (1 byte each) */
    case VK_FORMAT_R8G8_UNORM:
    case VK_FORMAT_R8G8_SNORM:
    case VK_FORMAT_R8G8_UINT:
    case VK_FORMAT_R8G8_SINT:
    case VK_FORMAT_R8G8_SRGB:
        formatinfo = {
            .nbrchannels  = 2,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

        /* BGR (1 byte each) */
    case VK_FORMAT_R8G8B8_UNORM:
    case VK_FORMAT_R8G8B8_SNORM:
    case VK_FORMAT_R8G8B8_UINT:
    case VK_FORMAT_R8G8B8_SINT:
    case VK_FORMAT_R8G8B8_SRGB:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_B8G8R8_UNORM:
    case VK_FORMAT_B8G8R8_SNORM:
    case VK_FORMAT_B8G8R8_UINT:
    case VK_FORMAT_B8G8R8_SINT:
    case VK_FORMAT_B8G8R8_SRGB:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "B", "G", "R" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    /* RGBA (1 byte each) */
    case VK_FORMAT_R8G8B8A8_UNORM:
    case VK_FORMAT_R8G8B8A8_SNORM:
    case VK_FORMAT_R8G8B8A8_UINT:
    case VK_FORMAT_R8G8B8A8_SINT:
    case VK_FORMAT_R8G8B8A8_SRGB:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_B8G8R8A8_UNORM:
    case VK_FORMAT_B8G8R8A8_SNORM:
    case VK_FORMAT_B8G8R8A8_UINT:
    case VK_FORMAT_B8G8R8A8_SINT:
    case VK_FORMAT_B8G8R8A8_SRGB:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "B", "G", "R", "A" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    /* ABGR (1 byte each) */
    case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
    case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
    case VK_FORMAT_A8B8G8R8_UINT_PACK32:
    case VK_FORMAT_A8B8G8R8_SINT_PACK32:
    case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "A", "B", "G", "R" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
    case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
    case VK_FORMAT_A2R10G10B10_UINT_PACK32:
    case VK_FORMAT_A2R10G10B10_SINT_PACK32:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "A", "R", "G", "B" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
    case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
    case VK_FORMAT_A2B10G10R10_UINT_PACK32:
    case VK_FORMAT_A2B10G10R10_SINT_PACK32:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "A", "B", "G", "R" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R16_UNORM:
    case VK_FORMAT_R16_SNORM:
    case VK_FORMAT_R16_UINT:
    case VK_FORMAT_R16_SINT:
    case VK_FORMAT_R16_SFLOAT:
        formatinfo = {
            .nbrchannels  = 1,
            .typedesc     = TypeDesc::UINT16,
            .channelnames = { "R" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R16G16_UNORM:
    case VK_FORMAT_R16G16_SNORM:
    case VK_FORMAT_R16G16_UINT:
    case VK_FORMAT_R16G16_SINT:
    case VK_FORMAT_R16G16_SFLOAT:
        formatinfo = {
            .nbrchannels  = 2,
            .typedesc     = TypeDesc::UINT16,
            .channelnames = { "R", "G" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R16G16B16_UNORM:
    case VK_FORMAT_R16G16B16_SNORM:
    case VK_FORMAT_R16G16B16_UINT:
    case VK_FORMAT_R16G16B16_SINT:
    case VK_FORMAT_R16G16B16_SFLOAT:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT16,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R16G16B16A16_UNORM:
    case VK_FORMAT_R16G16B16A16_SNORM:
    case VK_FORMAT_R16G16B16A16_UINT:
    case VK_FORMAT_R16G16B16A16_SINT:
    case VK_FORMAT_R16G16B16A16_SFLOAT:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT16,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R32_UINT:
    case VK_FORMAT_R32_SINT:
    case VK_FORMAT_R32_SFLOAT:
        formatinfo = {
            .nbrchannels  = 1,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "R" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_R32G32_UINT:
    case VK_FORMAT_R32G32_SINT:
    case VK_FORMAT_R32G32_SFLOAT:
        formatinfo = {
            .nbrchannels  = 2,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "R", "G" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R32G32B32_UINT:
    case VK_FORMAT_R32G32B32_SINT:
    case VK_FORMAT_R32G32B32_SFLOAT:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_R32G32B32A32_UINT:
    case VK_FORMAT_R32G32B32A32_SINT:
    case VK_FORMAT_R32G32B32A32_SFLOAT:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_R64_UINT:
    case VK_FORMAT_R64_SINT:
    case VK_FORMAT_R64_SFLOAT:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT32,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_R64G64_UINT:
    case VK_FORMAT_R64G64_SINT:
    case VK_FORMAT_R64G64_SFLOAT:
        formatinfo = {
            .nbrchannels  = 2,
            .typedesc     = TypeDesc::UINT64,
            .channelnames = { "R", "G" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_R64G64B64_UINT:
    case VK_FORMAT_R64G64B64_SINT:
    case VK_FORMAT_R64G64B64_SFLOAT:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT64,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;

    case VK_FORMAT_R64G64B64A64_UINT:
    case VK_FORMAT_R64G64B64A64_SINT:
    case VK_FORMAT_R64G64B64A64_SFLOAT:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT64,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::NONE,
        };
        return true;


    case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK:
    case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::ETC2,
        };
        return true;

    case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK:
    case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::ETC2,
        };
        return true;

    case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK:
    case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::ETC2,
        };
        return true;

    case VK_FORMAT_BC1_RGB_UNORM_BLOCK:
    case VK_FORMAT_BC1_RGB_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::BC1,
        };
        return true;

    case VK_FORMAT_BC1_RGBA_UNORM_BLOCK:
    case VK_FORMAT_BC1_RGBA_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::BC1,
        };
        return true;

    case VK_FORMAT_BC2_UNORM_BLOCK:
        formatinfo = {
            .nbrchannels  = 1,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::BC2,
        };
        return true;

    case VK_FORMAT_BC2_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::BC2,
        };
        return true;


    case VK_FORMAT_BC3_UNORM_BLOCK:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::BC3,
        };
        return true;
    case VK_FORMAT_BC3_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::BC3,
        };
        return true;

    case VK_FORMAT_BC7_UNORM_BLOCK:
        formatinfo = {
            .nbrchannels  = 1,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R" },
            .colorspace   = "lin_rec709_scene",
            .compression  = BlockCompression::BC7,
        };
        return true;

    case VK_FORMAT_BC7_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 3,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::BC7,
        };
        return true;

    case VK_FORMAT_ASTC_4x4_UNORM_BLOCK:
    case VK_FORMAT_ASTC_4x4_SRGB_BLOCK:
    case VK_FORMAT_ASTC_5x4_UNORM_BLOCK:
    case VK_FORMAT_ASTC_5x4_SRGB_BLOCK:
    case VK_FORMAT_ASTC_5x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_5x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_6x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_6x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_6x6_UNORM_BLOCK:
    case VK_FORMAT_ASTC_6x6_SRGB_BLOCK:
    case VK_FORMAT_ASTC_8x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_8x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_8x6_UNORM_BLOCK:
    case VK_FORMAT_ASTC_8x6_SRGB_BLOCK:
    case VK_FORMAT_ASTC_8x8_UNORM_BLOCK:
    case VK_FORMAT_ASTC_8x8_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x6_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x6_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x8_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x8_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x10_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x10_SRGB_BLOCK:
    case VK_FORMAT_ASTC_12x10_UNORM_BLOCK:
    case VK_FORMAT_ASTC_12x10_SRGB_BLOCK:
    case VK_FORMAT_ASTC_12x12_UNORM_BLOCK:
    case VK_FORMAT_ASTC_12x12_SRGB_BLOCK:
        formatinfo = {
            .nbrchannels  = 4,
            .typedesc     = TypeDesc::UINT8,
            .channelnames = { "R", "G", "B", "A" },
            .colorspace   = "srgb_rec709_scene",
            .compression  = BlockCompression::ASTC,
        };
        return true;

        /* TODO: handle unknown vkformats */
    default: break;
    }
    return false;
}

inline void
gl_to_vkformat()
{
}

OIIO_PLUGIN_NAMESPACE_END
