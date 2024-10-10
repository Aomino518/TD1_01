#include <Novice.h>

const char kWindowTitle[] = "TD1_1125_06_katou_14_daido_26_mori";

//ブロックの種類
typedef enum Block {
	BLOCK_AIR,
	BLOCK_BOX,
	BLOCK_WALL,
	STAGE_WALL,
}Block;

//プレイヤーやロボットの向き
typedef enum Direction {
	FRONT,
	BACK,
	LEFT,
	RIGHT,
}Direction;

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Player {
	Vector2 pos;
	float speed;
	float width;
	float height;
	int direction;
}Player;

typedef struct Robot {
	Vector2 pos;
	float speed;
	float width;
	float height;
}Robot;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	///===========================
	/// ↓ 変数の宣言と初期化 ここから
	///===========================

	//map
	int map[8][8] = { 0 };
	float blockSize = 32.0f;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//マップの外枠
			map[i][0] = { STAGE_WALL };
			map[i][7] = { STAGE_WALL };
			map[0][j] = { STAGE_WALL };
			map[7][j] = { STAGE_WALL };

			//マップの内側
			if (map[i][j] == BLOCK_AIR) {
				map[i][1] = { BLOCK_WALL };
				map[1][j] = { BLOCK_WALL };
				map[2][3] = { BLOCK_BOX };
			}
		}
	}

	//player
	Player player;
	player.pos.x = 2.0f;
	player.pos.y = 2.0f;
	player.width = blockSize;
	player.height = blockSize;
	player.speed = 1.0f;
	player.direction = FRONT;

	//robot
	Robot robot;
	robot.pos.x = 1.0f;
	robot.pos.y = 1.0f;
	robot.width = blockSize;
	robot.height = blockSize;
	robot.speed = 1.0f;

	//リソース
	int ghBLOCK_WALL = Novice::LoadTexture("./Resources/Images/block.png");

	///===========================
	/// ↑ 変数の宣言と初期化 ここまで
	///===========================

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//移動の更新処理
		if (keys[DIK_W] && !preKeys[DIK_W]) {
			//player
			player.direction = BACK;
			player.pos.y -= player.speed;
			if (map[static_cast<int>(player.pos.y)][static_cast<int>(player.pos.x)] != BLOCK_AIR) {
				player.pos.y += player.speed;
				robot.pos.y += robot.speed;
			}

			//robot
			robot.pos.y -= robot.speed;
			if (map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == BLOCK_AIR ||
				map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == STAGE_WALL) {
				robot.pos.y += robot.speed;
			}
		}

		if (keys[DIK_A] && !preKeys[DIK_A]) {
			//player
			player.direction = LEFT;
			player.pos.x -= player.speed;
			if (map[static_cast<int>(player.pos.y)][static_cast<int>(player.pos.x)] != BLOCK_AIR) {
				player.pos.x += player.speed;
				robot.pos.x += robot.speed;
			}

			//robot
			robot.pos.x -= robot.speed;
			if (map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == BLOCK_AIR ||
				map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == STAGE_WALL) {
				robot.pos.x += robot.speed;
			}
		}

		if (keys[DIK_S] && !preKeys[DIK_S]) {
			//player
			player.direction = FRONT;
			player.pos.y += player.speed;
			if (map[static_cast<int>(player.pos.y)][static_cast<int>(player.pos.x)] != BLOCK_AIR) {
				player.pos.y -= player.speed;
				robot.pos.y -= robot.speed;
			}

			//robot
			robot.pos.y += robot.speed;
			if (map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == BLOCK_AIR ||
				map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == STAGE_WALL) {
				robot.pos.y -= robot.speed;
			}
		}

		if (keys[DIK_D] && !preKeys[DIK_D]) {
			//player
			player.direction = RIGHT;
			player.pos.x += player.speed;
			if (map[static_cast<int>(player.pos.y)][static_cast<int>(player.pos.x)] != BLOCK_AIR) {
				player.pos.x -= player.speed;
				robot.pos.x -= robot.speed;
			}

			//robot
			robot.pos.x += robot.speed;
			if (map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == BLOCK_AIR ||
				map[static_cast<int>(robot.pos.y)][static_cast<int>(robot.pos.x)] == STAGE_WALL) {
				robot.pos.x -= robot.speed;
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//debug
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Novice::DrawLine(i * static_cast<int>(blockSize), 0,
					i * static_cast<int>(blockSize), 8 * static_cast<int>(blockSize),
					0xFFFFFFFF);

				Novice::DrawLine(0, j * static_cast<int>(blockSize),
					8 * static_cast<int>(blockSize), j * static_cast<int>(blockSize),
					0xFFFFFFFF);
			}
		}

		//map
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				//壁ブロック
				if (map[i][j] == BLOCK_WALL) {
					Novice::DrawBox(j * static_cast<int>(blockSize), i * static_cast<int>(blockSize),
						static_cast<int>(blockSize), static_cast<int>(blockSize),
						0.0f, 0xFFFF005F, kFillModeSolid);
				}

				//箱ブロック
				if (map[i][j] == BLOCK_BOX) {
					Novice::DrawBox(j * static_cast<int>(blockSize), i * static_cast<int>(blockSize),
						static_cast<int>(blockSize), static_cast<int>(blockSize),
						0.0f, 0xFF00FF5F, kFillModeSolid);
				}

				//マップの外枠
				if (map[i][j] == STAGE_WALL) {
					Novice::DrawSprite(j * static_cast<int>(blockSize), i * static_cast<int>(blockSize),
						ghBLOCK_WALL, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
				}
			}
		}

		//player
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Novice::DrawBox(static_cast<int>(player.pos.x * blockSize), static_cast<int>(player.pos.y * blockSize),
					static_cast<int>(player.width), static_cast<int>(player.height), 0.0f, 0xFF0000FF, kFillModeSolid);
			}
		}

		//robot
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Novice::DrawBox(static_cast<int>(robot.pos.x * blockSize), static_cast<int>(robot.pos.y * blockSize),
					static_cast<int>(robot.width), static_cast<int>(robot.height), 0.0f, 0xFFFF00FF, kFillModeSolid);
			}
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
