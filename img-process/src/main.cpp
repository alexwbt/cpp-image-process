#include <iostream>

#include "png/lodepng.h"

#include "util.h"
#include "kernel.h"

ImageData Read(const std::string& filename)
{
    auto data = std::make_shared<std::vector<unsigned char>>();
    uint32_t width, height;

    unsigned int error = lodepng::decode(*data, width, height, filename);
    if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return { filename, data, width, height };
}

void Write(const ImageData& img_data)
{
    auto error = lodepng::encode(img_data.filename, *img_data.data, img_data.width, img_data.height);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

int main()
{
    auto img = Read("testing.png");
    auto res = img;

    constexpr int kSize = 5;
    auto kernel = gaussian_blur_kernel<kSize>();

    Image& data = *res.data;
    // loop every pixel
    for (size_t i = 0; i < data.size(); i += 4)
    {
        auto coord = res.index_to_coord(i / 4);
        float r = 0, g = 0, b = 0, w = 0;

        // loop kernel
        for (int x = 0; x < kernel->size; x++)
        {
            for (int y = 0; y < kernel->size; y++)
            {
                Coord current{ coord.x + x, coord.y + y };
                if (!current.InBound(res.width, res.height)) continue;

                auto j = res.coord_to_index(current.x, current.y) * 4;
                w += kernel->grid[x][y];

                r += ((data[j] + data[j + 1] + data[j + 2]) / 3.0f) * kernel->grid[x][y];
            }
        }

        if (w == 0) w = 1;
        unsigned char value = (r / w);
        data[i] = value;
        data[i + 1] = value;
        data[i + 2] = value;
        //data[i + 3] = 255;

        //data[i] = 0; 
        //data[i + 1] = 0;
        //data[i + 2] = 0;
        //data[i + 3] = 255; // a
    }

    Write(res);
}


