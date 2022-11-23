/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   emoji_cry_png;
    const int            emoji_cry_pngSize = 55025;

    extern const char*   emoji_glass_png;
    const int            emoji_glass_pngSize = 46301;

    extern const char*   emoji_laugh_png;
    const int            emoji_laugh_pngSize = 53883;

    extern const char*   emoji_normal_png;
    const int            emoji_normal_pngSize = 50318;

    extern const char*   emoji_png;
    const int            emoji_pngSize = 50894;

    extern const char*   background_jpg;
    const int            background_jpgSize = 100726;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
