// Lesson2.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


//マップの高さ。
const int MAP_HEIGHT = 16;
//マップの幅。
const int MAP_WIDTH = 16;

//フレームバッファみたいなもの・・・
static char sFrameBuffer[MAP_HEIGHT][MAP_WIDTH];

////////////////////////////////////////
//フレームバッファに描画。
////////////////////////////////////////
void DrawMoji(int posX, int posY, char moji)
{
	//フレームバッファの幅と高さを超えていないかチェーック。
	if (posX < MAP_WIDTH && posY < MAP_HEIGHT) {
		sFrameBuffer[posY][posX] = moji;
	}
}
////////////////////////////////////////
//1フレームの最初に呼ばれる関数。
////////////////////////////////////////
void BeginFrame()
{
	//フレームバッファをクリア。
	memset(sFrameBuffer, 0, sizeof(sFrameBuffer));
}
////////////////////////////////////////
//1フレームの終わりに呼ばれる関数。
////////////////////////////////////////
void EndFrame()
{
	//フレームバッファの内容を画面に表示する。
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			std::cout << sFrameBuffer[i][j];
		}
		std::cout << "\n";
	}

	//100ミリ秒眠る。
	Sleep(100);

	//標準出力コンソールのハンドルを取得。
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;
	//標準コンソールのカーソルを0行目、0列に戻す。
	SetConsoleCursorPosition(hCons, pos);
	
}

////////////////////////////////////////
// メイン関数。
////////////////////////////////////////
int main()
{
	//プレイヤーの座標
	int playerPosX = 0;
	int playerPosY = 0;
	//ゲームループ。
	while (true) {
		//1フレームの開始。
		BeginFrame();
		//プレイヤーの移動処理。
		if (GetAsyncKeyState(VK_UP)) {
			playerPosY--;
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			playerPosY++;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			playerPosX++;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			playerPosX--;
		}
		//プレイヤーをフレームバッファに描画。
		DrawMoji(playerPosX, playerPosY, 'P');

		//フレームの終わり。
		EndFrame();
	}
    return 0;
}

