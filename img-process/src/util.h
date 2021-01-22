#pragma once

struct Coord
{
    uint32_t x;
    uint32_t y;

    bool InBound(uint32_t width, uint32_t height) const
    {
        return x >= 0 && y >= 0 && x < width && y < height;
    }
};

using Image = std::vector<unsigned char>;
using ImagePtr = std::shared_ptr<Image>;

struct ImageData
{
    std::string filename;
    ImagePtr data;
    uint32_t width;
    uint32_t height;

    ImageData(const std::string& filename, ImagePtr data, uint32_t width, uint32_t height)
        : filename(filename), data(std::move(data)), width(width), height(height)
    {}

    ImageData(const ImageData& img)
        : filename("result.png"), data(std::make_shared<Image>(*img.data)),
        width(img.width), height(img.height)
    {}

    Coord index_to_coord(size_t i) const
    {
        return { (uint32_t)(i % (size_t)width), (uint32_t)(i / (size_t)width) };
    }

    size_t coord_to_index(uint32_t x, uint32_t y) const
    {
        return (size_t)y * (size_t)width + (size_t)x;
    }
};
