# About

This KTX plugin support obviously nulifies the benefits of using KTX in the
first place. That being said, this plugin is still useful so that end users
don't have to convert back and forth between KTX <-> support format (e.g., PNG).

An example usecase would be Blender and its glTf import/export plugin.

Ideally, at some point in the future, OIIO may introduce a new API to accomodate
texture formats that are mainly used for fast texture uploads to GPUs.

Below you will find a set of notes about why this plugin is implemented the way
it is. It took me some time to understand how libktx works and what it provides
(and why). Some terminology is also defined here.

## Super Compression

**supercompression**: a compression on top of another compression (i.e., layered
compression).

## Compressed Textures

As opposed to compressed images, compressed textures refer to GPU
block-compressed textures. Compressed textures have the following requirements:

### BCn

All BCn formats decode a 4x4 block into a fixed-bit

#### BC1/DXT1

64 bytes (4x4 block) => 8 bytes
alpha channed is encoded using 1 bit

### ASTC


## KTX Supercompression

### KTS\_SS\_BASIS\_LZ

This is the intended supercompression to be used within KTX. The expected
workflow is as follows:

```
Basis LZ -> transcode -> BCn (GPU-native - usually BC7)
```

For OIIO usecase, we have to decode BCn blocks:

```
Basis → transcode (using ktxTexture2_TranscodeBasis) → raw RGBA
```

The `ktxTexture2_TranscodeBasis` function provided by libktx can transcode
directly into raw RGBA values which is handy.

## Limitations

As stated in the comments in ktxinput.cpp, if given ktx texture is
supercompressed then it has to be all decompressed (i.e., NOT the decompression
of the underlying GPU texture format but rather the supercompression). This
means that if you need just a particular subimage, you pay the memory price of
loading the whole KTX texture (which might be very large for 3D textures and
texture arrays).

KTX1 format is not yet supported. Adding support for it after finishing KTX2
*should be* relatively straightforward.

## 3rd Party Credits Licenses

libktx: for general KTX format support
dec: for BCn format decoding
