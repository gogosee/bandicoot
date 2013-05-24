#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#define Whb_NAMESPACE_START namespace whb {
#define Whb_NAMESPACE_END	}


Whb_NAMESPACE_START

template <typename T>
class Singleton
{
public:
	static T* Instance(void)
	{
		if (cpoInstance == NULL)
		{
			cpoInstance = new(T);
		}

		return cpoInstance;
	}

	static void Release()
	{
		delete(cpoInstance);
	}

private:
	static T* cpoInstance;
};

template<typename T>
T* Singleton<T>::cpoInstance = NULL;

template<typename T>
T* Instance(void)
{
	return Singleton<T>::Instance();
}

template<typename T>
void Release(void)
{
	return Singleton<T>::Release();
}

Whb_NAMESPACE_END

//////////////////////////////////////////////////////////////



class test
{
public:
	test(){}
	~test(){}

	void Startup()
	{
		printf("startup.\n");
	}
};


int main()
{
	whb::Instance<test>()->Startup();
	sleep(1);
	return 0;
}

