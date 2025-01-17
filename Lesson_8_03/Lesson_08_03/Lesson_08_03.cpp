// Lesson_08_01.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//整数型のUniquePtr
class UniquePtr {
	int* m_p = nullptr;
public:
	UniquePtr(int* p)
	{
		m_p = p;
	}
	~UniquePtr()
	{
		delete m_p;
	}
	//アロー演算子。
	int* operator->()
	{
		return m_p;
	}
	//参照外し
	int& operator*()
	{
		return *m_p;
	}
	//代入演算子とコピーコンストラクタはNG
	/*UniquePtr& operator=(UniquePtr& ptr) = delete;
	UniquePtr(UniquePtr& ptr) = delete;*/
};

int main()
{
#if 1
	UniquePtr ptr(new int);
	*ptr = 10;
	cout << *ptr;
	{
		UniquePtr ptr2(new int);
		*ptr2 = 20;
		cout << *ptr2;
		//ここを抜けるとptr2のデストラクタが呼ばれて、動的に確保されたメモリは解放される。
		//この下を実行したらクラッシュする->なので、代入演算子とコピーコンストラクタは削除。
		//ptr = ptr2;
	}
#else
	UniquePtr<int> iPtr(new int);
	UniquePtr<float> fPtr(new float);
	*iPtr = 10;
	*fPtr = 20.2f;
	cout << *iPtr << "\n";
	cout << *fPtr << "\n";
#endif
    return 0;
}

