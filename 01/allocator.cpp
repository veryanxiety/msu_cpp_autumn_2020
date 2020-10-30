#include <cstddef>

class Allocator
{
	private:
		size_t	maxsize {0};
		size_t	shift {0};
		char*	ptr {nullptr};
//		bool	isexist {false};
	public:
		void	makeAllocator(size_t	maxSize)
		{
			if(ptr == nullptr)
			{
				maxsize = maxSize;
				if(maxsize)
					ptr = new char[maxsize];
			}
		}

		~Allocator()
		{
			if(ptr != nullptr)
				delete [] ptr;
		}

		char*	alloc(size_t	size)
		{
			if (ptr == nullptr || shift + size > maxsize)
				return nullptr;
			shift += size;
			return ptr + (shift - size);
		}

		void	reset()
		{
			shift = 0;
		}
};
