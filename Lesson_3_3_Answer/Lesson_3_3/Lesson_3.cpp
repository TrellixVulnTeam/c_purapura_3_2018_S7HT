// Lesson2.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Player.h" //Playerクラスを使いたいので、ヘッダーファイルをインクルードする。
#include "Enemy.h"	//Enemyクラスを使いたいので、ヘッダーファイルをインクルードする。

//マップの高さ。
const int MAP_HEIGHT = 16;
//マップの幅。
const int MAP_WIDTH = 16;

//フレームバッファみたいなもの・・・
static char sFrameBuffer[MAP_HEIGHT][MAP_WIDTH];
//ゲームオーバーフラグ。
bool g_gameOverFlag = false;



////////////////////////////////////////
//フレームバッファに文字を描画。
////////////////////////////////////////
void DrawMoji(int posX, int posY, char moji)
{
	//フレームバッファの幅と高さを超えていないかチェック。
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
	//プレイヤーの初期化、。
	g_player.SetPos( 5, 5 );
	
	//エネミーのインスタンスを10個用意する。
	Enemy enemy[10];
	//初期座標を決めていく。
	enemy[0].SetPos( 2, 1 );
	enemy[1].SetPos( 3, 4 );
	enemy[2].SetPos( 3, 6 );
	enemy[3].SetPos( 6, 3 );
	enemy[4].SetPos( 2, 7 );
	enemy[5].SetPos( 9, 9 );
	enemy[6].SetPos(10, 14 );
	enemy[7].SetPos( 8, 6 );
	enemy[8].SetPos( 11, 4 );
	enemy[9].SetPos( 2, 15 );

	//ゲームループ。
	while (true) {
		//1フレームの開始。
		BeginFrame();
		
		if (g_gameOverFlag == false) {
			//プレイヤーの移動処理を実行。
			g_player.Move();
			//プレイヤーの描画処理を実行。
			g_player.Draw();

			//エネミーの移動処理を実行。
			for (int i = 0; i < 10; i++) {
				enemy[i].Move();
			}
			//エネミーの描画処理を実行。
			for (int i = 0; i < 10; i++) {
				enemy[i].Draw();
			}
		}
		else if (g_gameOverFlag == true) {
			//ゲームオーバー。
			DrawMoji(0, 4, 'G');
			DrawMoji(1, 4, 'A');
			DrawMoji(2, 4, 'M');
			DrawMoji(3, 4, 'E');
			DrawMoji(4, 4, ' ');
			DrawMoji(5, 4, 'O');
			DrawMoji(6, 4, 'V');
			DrawMoji(7, 4, 'E');
			DrawMoji(8, 4, 'R');
		}
		//フレームの終わり。
		EndFrame();
	}
    return 0;
}

