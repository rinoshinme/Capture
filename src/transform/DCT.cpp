#include "DCT.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Capture
{
	std::vector<double> DCT::ApplyDCT(const std::vector<double>& data, std::size_t outputLength)
    {
        // zero-initialize output vector
        std::vector<double> output(outputLength, 0.0);
        std::size_t inputLength = data.size();

        // DCT scaling factor
        double c0 = std::sqrt(1.0 / inputLength);
        double cn = std::sqrt(2.0 / inputLength);
        // cached cosine values
        double** cosines = GetCachedCosines(inputLength, outputLength);

        for (std::size_t n = 0; n < outputLength; ++n)
        {
            for (std::size_t k = 0; k < inputLength; ++k)
            {
                output[n] += data[k] * cosines[n][k];
            }
            output[n] *= (0 == n) ? c0 : cn;
        }

        return output;
    }

    double** DCT::GetCachedCosines(std::size_t inputLength, std::size_t outputLength)
    {
        auto key = std::make_pair(inputLength, outputLength);

        // if we have that key cached, return immediately
        if (cosineCache.find(key) != cosineCache.end())
        {
            return cosineCache[key];
        }

        // nothing in cache for that pair, calculate cosines
        double** cosines = new double*[outputLength];
        for (std::size_t n = 0; n < outputLength; ++n)
        {
            cosines[n] = new double[inputLength];
            for (std::size_t k = 0; k < inputLength; ++k)
            {
                // from the definition of DCT-II
                cosines[n][k] = std::cos((M_PI * (2 * k + 1) * n) /
                                         (2.0 * inputLength));
            }
        }
        cosineCache[key] = cosines;

        return cosines;
    }

    /**
     * Deletes all the memory used by cache.
     */
    void DCT::ClearCosineCache()
    {
        for (auto it = std::begin(cosineCache); it != std::end(cosineCache); it++)
        {
            auto key = it->first;
            double** cosines = it->second;
            std::size_t outputLength = key.second;
            for (std::size_t i = 0; i < outputLength; ++i)
            {
                delete [] cosines[i];
            }
            delete [] cosines;
        }
    }
}
