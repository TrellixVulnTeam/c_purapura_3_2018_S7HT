// Lesson_08_01.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

/*!
 *@brief	二つの引数を受け取って大きいほうの値を返す。
 */
template< class T >
T Max( T x, T y )
{
	if( x > y ){
		return x;
	}
	return y;
}
/*!
*@brief	二つの引数を受け取って大きいほうの値を返す。
*/
template< class T >
T Min(T x, T y)
{
	if (x < y) {
		return x;
	}
	return y;
}

/*!
*@brief	二つの引数を受け取って大きいほうの値を返す。
*/
template< class T >
void Swap(T& x, T& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}
int main()
{
	int ia, ib;
	ia = 10;
	ib = 20;

	short sa, sb;
	sa = 10;
	sb = 20;

	char ca, cb;
	ca = 10;
	cb = 20;

	float fa, fb;
	fa = 10.2f;
	fb = 20.1f;

	int		ic = Max(ia, ib);	//32bit整数版のMax関数が呼ばれる。
	short	sc = Max(sa, sb);	//16bit整数版のMax関数が呼ばれる。
	char	cc = Max(ca, cb);	//8bit整数版のMax関数が呼ばれる。
	float	fc = Max(fa, fb);	//32bit浮動小数点版が呼ばれる。
#if 1 //実習 1 小さいほうの値を返してくるMin関数を作成しなさい。
	cout << "実習１　小さいほうの値を表示\n";
	ic = Min(ia, ib);
	sc = Min(sa, sb);
	cc = Min(ca, cb);
	fc = Min(fa, fb);
	cout << "icの値は : " <<	  ic << "\n";   //10と表示されたらOK
	cout << "scの値は : " <<      sc << "\n";	//10と表示されたらOK
	cout << "ccの値は : " << (int)cc << "\n";	//10と表示されたらOK
	cout << "fcの値は : " <<      fc << "\n";	//10.2と表示されたらOK
#endif

#if 1 //実習 2 値を入れ替えるSwap関数を実装しなさい。
	cout << "実習２　値の入れ替え\n";

	Swap(ia, ib);
	Swap(sa, sb);
	Swap(ca, cb);
	Swap(fa, fb);

	//私たち入れ替わってる？
	cout << "iaの値は : " <<	  ia << "\n"; //20と表示されたらOK
	cout << "saの値は : " <<	  sa << "\n"; //20と表示されたらOK
	cout << "caの値は : " << (int)ca << "\n"; //20と表示されたらOK
	cout << "faの値は : " <<	  fa << "\n"; //20.2と表示されたらOK
#endif
    return 0;
}

