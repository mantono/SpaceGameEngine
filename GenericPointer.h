#ifndef ENGINE_GENERICPOINTER_H_
#define ENGINE_GENERICPOINTER_H_

namespace engine
{
	template < class T >
	class GenericPointer
	{

	public:
		GenericPointer(T* pValue) :pData(pValue), references(1)
		{
		}

		GenericPointer(const GenericPointer<T>& genPointer)
		:references(genPointer.references), pData(genPointer.pData)
		{
			references++;
		}

		~GenericPointer()
		{
			std::cout << "destruktor generic pointer\n";
			std::cout << references;
			if (--references == 0)
				delete pData;
		}

		T& operator* ()
		{
			return *pData;
		}

		T* operator-> ()
		{
			return pData;
		}

		GenericPointer<T>& operator = (const GenericPointer<T>& gp)
		{
			if (this != &gp)
			{
				if(--references == 0)
				{
					delete pData;
				}
				pData = gp.pData;
				references = gp.references;
				references++;
			}
			return *this;
		}

	private:
		// Still private because we have not created GenericPointer<T>& operator = (const T& p)
		GenericPointer()
		:pData(nullptr), references(0)
		{
		}

		T* pData;
		unsigned int references;


	};
}
#endif
