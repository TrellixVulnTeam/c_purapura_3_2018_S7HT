// Lesson_08_01.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//整数型の可変長配列。
class Vector {
	int* pArray = nullptr;	//配列の先頭アドレス。
	int size = 0;			//可変長配列のサイズ。
public:
	void PushBack(int v) 
	{
		int* pOld = pArray;
		//新しい領域を確保する。
		pArray = new int[size + 1];

		//古い内容を丸っとコピー。
		for (int i = 0; i < size; i++) {
			pArray[i] = pOld[i];
		}
		//配列の末尾に要素を追加。
		pArray[size] = v;
		//要素の数をインクリメント
		size++;
		//古い領域を削除。
		delete[] pOld;
	}

	//添え字演算子
	int& operator[](int index) 
	{
		return pArray[index];
	}
	//サイズを取得。
	int GetSize() const
	{
		return size;
	}
};

int main()
{
	Vector iArray;
	iArray.PushBack(10);
	iArray.PushBack(20);
	iArray.PushBack(30);
	for (int i = 0; i < iArray.GetSize(); i++) {
		cout << iArray[i] << "\n";
	}
    return 0;
}

