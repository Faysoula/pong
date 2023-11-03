
#include <iostream>
#include "raylib.h"



struct Ball {


	float x, y;
	float speedx, speedy;
	float radius;

	void Draw() {

		DrawCircle((int)x, (int)y, radius, WHITE);

	}

};

struct Paddle {

	float x, y;
	float width, height;
	float speed;

	Rectangle GetRect() {

		return Rectangle{x - width / 2, y - height / 2, 10, 100};

	}

	void Draw() {

		DrawRectangleRec(GetRect(), WHITE);
	}

};


int main()
{
	
	
	InitWindow(800, 600, "pong");
	SetWindowState(FLAG_VSYNC_HINT);
	

	const char* winner = nullptr;

	

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedx = 300;
	ball.speedy = 300;

	Paddle leftPaddle;

	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;

	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;

	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;
	while (!WindowShouldClose()) {

		ball.x += ball.speedx * GetFrameTime();
		ball.y += ball.speedy * GetFrameTime();


		if (ball.y >= GetScreenHeight()) {

			ball.y = GetScreenHeight();
			ball.speedy *= -1;
		}

		if (ball.y < 0) {


			ball.speedy *= -1;

		}

		if (ball.x < 0) {

			winner = "right player wins";
			ball.radius + 5;
		}

		if (ball.x > GetScreenWidth()) {

			winner = "left player wins";
			ball.radius + 5;
			
		}

		BeginDrawing();


		
		ClearBackground(BLACK);
		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		
		
		if (IsKeyDown(KEY_UP)) rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		if (IsKeyDown(KEY_DOWN)) rightPaddle.y += rightPaddle.speed * GetFrameTime();

		if (IsKeyDown(KEY_W)) leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		if (IsKeyDown(KEY_S)) leftPaddle.y += leftPaddle.speed * GetFrameTime();

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y },
			ball.radius, leftPaddle.GetRect())) {
			

			if (ball.speedx < 0) {

				ball.speedx *= -1.1f;
				ball.speedy = (((ball.y - leftPaddle.y) / (leftPaddle.height / 2)) * -ball.speedx);
			}


		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y },
			ball.radius, rightPaddle.GetRect())) {


			if (ball.speedx > 0) {

				ball.speedx *= -1.1f;
				ball.speedy = (((ball.y - rightPaddle.y) / (rightPaddle.height / 2)) * -ball.speedx);

			}

		}

		if (winner) {
			int txtwidth = MeasureText(winner, 60);
			DrawText(winner, GetScreenWidth() / 2 - txtwidth / 2
				    , GetScreenHeight() / 2 - 30, 60, GREEN);
		}

		if (winner && IsKeyPressed(KEY_SPACE)) {

			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenHeight() / 2.0f;
			
			ball.speedx = 300;
			ball.speedy = 300;
			winner = nullptr;

		}

		DrawFPS(10, 10);
		EndDrawing();


	}
	CloseWindow();

}


