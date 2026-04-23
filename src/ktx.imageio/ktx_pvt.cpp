#include "ktx_pvt.h"

OIIO_PLUGIN_NAMESPACE_BEGIN

bool
extract_info_from_format(VkFormat vkformat, FormatInfo& formatinfo)
{
    // clang-format off
    switch (vkformat) {

    case VK_FORMAT_R8_UNORM:
    case VK_FORMAT_R8_SNORM:
    case VK_FORMAT_R8_UINT:
    case VK_FORMAT_R8_SINT: formatinfo = { 1, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::NONE }; return true;
    case VK_FORMAT_R8_SRGB: formatinfo = { 1, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R8G8_UNORM:
    case VK_FORMAT_R8G8_SNORM:
    case VK_FORMAT_R8G8_UINT:
    case VK_FORMAT_R8G8_SINT: formatinfo = { 2, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::NONE }; return true;
    case VK_FORMAT_R8G8_SRGB: formatinfo = { 2, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R8G8B8_UNORM:
    case VK_FORMAT_R8G8B8_SNORM:
    case VK_FORMAT_R8G8B8_UINT:
    case VK_FORMAT_R8G8B8_SINT: formatinfo = { 3, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::NONE }; return true;
    case VK_FORMAT_R8G8B8_SRGB: formatinfo = { 3, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_B8G8R8_UNORM:
    case VK_FORMAT_B8G8R8_SNORM:
    case VK_FORMAT_B8G8R8_UINT:
    case VK_FORMAT_B8G8R8_SINT: formatinfo = { 3, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::NONE, {"B", "G", "R"} }; return true;
    case VK_FORMAT_B8G8R8_SRGB: formatinfo = { 3, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::NONE, {"B", "G", "R"} }; return true;

    case VK_FORMAT_R8G8B8A8_UNORM:
    case VK_FORMAT_R8G8B8A8_SNORM:
    case VK_FORMAT_R8G8B8A8_UINT:
    case VK_FORMAT_R8G8B8A8_SINT: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::NONE }; return true;
    case VK_FORMAT_R8G8B8A8_SRGB: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_B8G8R8A8_UNORM:
    case VK_FORMAT_B8G8R8A8_SNORM:
    case VK_FORMAT_B8G8R8A8_UINT:
    case VK_FORMAT_B8G8R8A8_SINT: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::NONE, {"B", "G", "R", "A"} }; return true;
    case VK_FORMAT_B8G8R8A8_SRGB: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::NONE, {"B", "G", "R", "A"} }; return true;

    // TODO: add support for PACK32 Vulkan formats
    case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
    case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
    case VK_FORMAT_A8B8G8R8_UINT_PACK32:
    case VK_FORMAT_A8B8G8R8_SINT_PACK32:
    case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
    case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
    case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
    case VK_FORMAT_A2R10G10B10_UINT_PACK32:
    case VK_FORMAT_A2R10G10B10_SINT_PACK32:
    case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
    case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
    case VK_FORMAT_A2B10G10R10_UINT_PACK32:
    case VK_FORMAT_A2B10G10R10_SINT_PACK32: return false;

    case VK_FORMAT_R16_UNORM:
    case VK_FORMAT_R16_SNORM:
    case VK_FORMAT_R16_UINT:
    case VK_FORMAT_R16_SINT:
    case VK_FORMAT_R16_SFLOAT: formatinfo = { 1, TypeDesc::HALF, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R16G16_UNORM:
    case VK_FORMAT_R16G16_SNORM:
    case VK_FORMAT_R16G16_UINT:
    case VK_FORMAT_R16G16_SINT:
    case VK_FORMAT_R16G16_SFLOAT: formatinfo = { 2, TypeDesc::HALF, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R16G16B16_UNORM:
    case VK_FORMAT_R16G16B16_SNORM:
    case VK_FORMAT_R16G16B16_UINT:
    case VK_FORMAT_R16G16B16_SINT:
    case VK_FORMAT_R16G16B16_SFLOAT: formatinfo = { 3, TypeDesc::HALF, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R16G16B16A16_UNORM:
    case VK_FORMAT_R16G16B16A16_SNORM:
    case VK_FORMAT_R16G16B16A16_UINT:
    case VK_FORMAT_R16G16B16A16_SINT:
    case VK_FORMAT_R16G16B16A16_SFLOAT: formatinfo = { 4, TypeDesc::HALF, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R32_UINT:
    case VK_FORMAT_R32_SINT:
    case VK_FORMAT_R32_SFLOAT: formatinfo = { 1, TypeDesc::FLOAT, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R32G32_UINT:
    case VK_FORMAT_R32G32_SINT:
    case VK_FORMAT_R32G32_SFLOAT: formatinfo = { 2, TypeDesc::FLOAT, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R32G32B32_UINT:
    case VK_FORMAT_R32G32B32_SINT:
    case VK_FORMAT_R32G32B32_SFLOAT: formatinfo = { 3, TypeDesc::FLOAT, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R32G32B32A32_UINT:
    case VK_FORMAT_R32G32B32A32_SINT:
    case VK_FORMAT_R32G32B32A32_SFLOAT: formatinfo = { 4, TypeDesc::FLOAT, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R64_UINT:
    case VK_FORMAT_R64_SINT:
    case VK_FORMAT_R64_SFLOAT: formatinfo = { 1, TypeDesc::DOUBLE, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R64G64_UINT:
    case VK_FORMAT_R64G64_SINT:
    case VK_FORMAT_R64G64_SFLOAT: formatinfo = { 2, TypeDesc::DOUBLE, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R64G64B64_UINT:
    case VK_FORMAT_R64G64B64_SINT:
    case VK_FORMAT_R64G64B64_SFLOAT: formatinfo = { 3, TypeDesc::DOUBLE, "lin_rec709_scene", BlockCompression::NONE }; return true;

    case VK_FORMAT_R64G64B64A64_UINT:
    case VK_FORMAT_R64G64B64A64_SINT:
    case VK_FORMAT_R64G64B64A64_SFLOAT: formatinfo = { 4, TypeDesc::DOUBLE, "lin_rec709_scene", BlockCompression::NONE }; return true;

         /* ETC2 RGB still decompresses to RGBA with alpha set to 1 (i.e., opaque texture) */
    case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::ETC2_RGB }; return true;
    case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::ETC2_RGB }; return true;
    case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::ETC2_RGB_A1 }; return true;
    case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::ETC2_RGB_A1 }; return true;
    case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::ETC2_RGBA }; return true;
    case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::ETC2_RGBA }; return true;

    case VK_FORMAT_EAC_R11_UNORM_BLOCK: formatinfo = { 1, TypeDesc::UINT16, "lin_rec709_scene", BlockCompression::EAC_R11 }; return true;
    case VK_FORMAT_EAC_R11_SNORM_BLOCK: formatinfo = { 1, TypeDesc::UINT16, "srgb_rec709_scene", BlockCompression::EAC_R11 }; return true;
    case VK_FORMAT_EAC_R11G11_UNORM_BLOCK: formatinfo = { 2, TypeDesc::UINT16, "lin_rec709_scene", BlockCompression::EAC_RG11 }; return true;
    case VK_FORMAT_EAC_R11G11_SNORM_BLOCK: formatinfo = { 2, TypeDesc::UINT16, "srgb_rec709_scene", BlockCompression::EAC_RG11 }; return true;

    case VK_FORMAT_BC1_RGB_UNORM_BLOCK: formatinfo = { 3, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC1 }; return true;
    case VK_FORMAT_BC1_RGB_SRGB_BLOCK: formatinfo = { 3, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::BC1 }; return true;
    case VK_FORMAT_BC1_RGBA_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC1 }; return true;
    case VK_FORMAT_BC1_RGBA_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::BC1 }; return true;

    case VK_FORMAT_BC2_UNORM_BLOCK: formatinfo = { 3, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC2 }; return true;
    case VK_FORMAT_BC2_SRGB_BLOCK: formatinfo = { 3, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::BC2 }; return true;

    case VK_FORMAT_BC3_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC3 }; return true;
    case VK_FORMAT_BC3_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::BC3 }; return true;

    case VK_FORMAT_BC5_UNORM_BLOCK:
    case VK_FORMAT_BC5_SNORM_BLOCK: formatinfo = { 2, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC5 }; return true;

    case VK_FORMAT_BC6H_UFLOAT_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC6HU }; return true;
    case VK_FORMAT_BC6H_SFLOAT_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC6HS }; return true;

    case VK_FORMAT_BC7_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::BC7 }; return true;
    case VK_FORMAT_BC7_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::BC7 }; return true;

    case VK_FORMAT_ASTC_4x4_UNORM_BLOCK:
    case VK_FORMAT_ASTC_5x4_UNORM_BLOCK:
    case VK_FORMAT_ASTC_5x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_6x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_6x6_UNORM_BLOCK:
    case VK_FORMAT_ASTC_8x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_8x6_UNORM_BLOCK:
    case VK_FORMAT_ASTC_8x8_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x5_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x6_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x8_UNORM_BLOCK:
    case VK_FORMAT_ASTC_10x10_UNORM_BLOCK:
    case VK_FORMAT_ASTC_12x10_UNORM_BLOCK: 
    case VK_FORMAT_ASTC_12x12_UNORM_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "lin_rec709_scene", BlockCompression::ASTC }; return true;

    case VK_FORMAT_ASTC_4x4_SRGB_BLOCK:
    case VK_FORMAT_ASTC_5x4_SRGB_BLOCK:
    case VK_FORMAT_ASTC_5x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_6x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_6x6_SRGB_BLOCK:
    case VK_FORMAT_ASTC_8x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_8x6_SRGB_BLOCK:
    case VK_FORMAT_ASTC_8x8_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x5_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x6_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x8_SRGB_BLOCK:
    case VK_FORMAT_ASTC_10x10_SRGB_BLOCK:
    case VK_FORMAT_ASTC_12x10_SRGB_BLOCK:
    case VK_FORMAT_ASTC_12x12_SRGB_BLOCK: formatinfo = { 4, TypeDesc::UINT8, "srgb_rec709_scene", BlockCompression::ASTC }; return true;

        /* TODO: handle unknown vkformats */
    default: break;
    }
    return false;
    // clang-format on
}

OIIO_PLUGIN_NAMESPACE_END
