#ifndef _DCT_H
#define _DCT_H

#include <map>
#include <vector>

namespace Capture
{
	class DCT
	{
	public:
        DCT()
			:cosineCache()
		{}

        ~DCT()
        {
            ClearCosineCache();
        }

        std::vector<double> ApplyDCT(const std::vector<double>& data, std::size_t outputLength);

    private:
        typedef std::pair<std::size_t, std::size_t> cosineCacheKeyType;

        typedef std::map<cosineCacheKeyType, double**> cosineCacheType;

        cosineCacheType cosineCache;

        double** GetCachedCosines(std::size_t inputLength, std::size_t outputLength);

        void ClearCosineCache();
	};
}

#endif
