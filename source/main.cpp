#include "game.h"
#include "util.h"
#include "SDL_mixer.h"
GameState currentGameState;
bool muted;
int finalScore;

void gameLoop(Util util)
{
	Tetromino tetro;
	Board gameBoard;

	bool gameOver = false;
	bool moveDownCell = false;
	bool alreadyHeld = false;

	int currentX = (BOARD_WIDTH / 2) - 2;
	int currentY = 0;
	int currentRotation = 0;
	int nextTetro;
	int heldPiece = 8;
	int fallSpeed = 20;
	int speedCounter = 0;
	int level = 21 - fallSpeed;
	int score = 0;
	int lineCounter = 0;
	vector<int> lineStored;

	string scoreText = "Score: " + to_string(score);
	string levelText = "Level: " + to_string(level);

	time_t t;
    srand((unsigned)time(&t));
	tetro.currentTetro = rand() % 7;
	nextTetro = rand() % 7;

	SDL_Event e;

    util.BGM();

	while (!gameOver)
	{
	    // Kiem soat toc do di chuyen cua cac khoi hinh
		this_thread::sleep_for(chrono::milliseconds(50));
		speedCounter++;
		moveDownCell = (speedCounter == fallSpeed);

		while (SDL_PollEvent(&e) != 0)
        {
        if (e.type == SDL_QUIT)
        {
            gameOver = true;
            currentGameState = GameState::QUIT;
        }
    if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_UP)
    {
        if (checkCollision(tetro, gameBoard, currentRotation + 1, currentX, currentY))
        {
            currentRotation++;
        }
    }
    else if (e.key.keysym.sym == SDLK_DOWN)
    {
        if (checkCollision(tetro, gameBoard, currentRotation, currentX, currentY + 1))
        {
            currentY++;
        }
    }
    else if (e.key.keysym.sym == SDLK_RIGHT)
    {
        if (checkCollision(tetro, gameBoard, currentRotation, currentX + 1, currentY))
        {
            currentX++;
        }
    }
    else if (e.key.keysym.sym == SDLK_LEFT)
    {
        if (checkCollision(tetro, gameBoard, currentRotation, currentX - 1, currentY))
        {
            currentX--;
        }
    }
    else if (e.key.keysym.sym == SDLK_SPACE)
    {
        moveDownCell = executeHardDrop(tetro, gameBoard, currentRotation, currentX, currentY);
    }
    else if (e.key.keysym.sym == SDLK_m)
    {
        if (muted)
        {
            util.BGM();
            muted = false;
        }
        else
        {
            Mix_HaltMusic();
            muted = true;
        }
    }
    else if (e.key.keysym.sym == SDLK_c)
    {
        if (!alreadyHeld)
        {
            if (heldPiece == 8)
            {
                heldPiece = tetro.currentTetro;
                tetro.currentTetro = nextTetro;
                nextTetro = rand() % 7;
            }
            else
            {
                int tempPiece = tetro.currentTetro;
                tetro.currentTetro = heldPiece;
                heldPiece = tempPiece;
            }
            currentX = (BOARD_WIDTH / 2) - 2;
            currentY = 0;
            currentRotation = 0;
            alreadyHeld = true;
        }
    }
        else if (e.key.keysym.sym == SDLK_ESCAPE)
        {
        gameOver = true;
        }
    }

}

		if (moveDownCell)
		{
			speedCounter = 0;

			if (checkCollision(tetro, gameBoard, currentRotation, currentX, currentY + 1))
			{
				currentY++;
			}
			else
			{
 				gameBoard.addNewPiece(tetro, currentRotation, currentX, currentY);

				checkLines(gameBoard, lineStored, lineCounter, fallSpeed, level, tetro.currIndex(), currentY);

				if (!lineStored.empty())
                    score += ( pow( 2 , lineStored.size())) * 100;


				if (!lineStored.empty())
				{
					// Animation xoa hang
					util.drawPlayBoard(gameBoard);
					util.UpdateRender();
					this_thread::sleep_for(chrono::milliseconds(100));
					eraseLines(gameBoard, lineStored);
					util.soundEffect("sounds_clear.wav");
				}

				// Lay khoi hinh tiep theo
				currentX = (BOARD_WIDTH / 2) - 2;
				currentRotation = 0;
				tetro.currentTetro = nextTetro;
				currentY = (tetro.currIndex() == 4) ? -1 : 0;
				nextTetro = rand() % 7;

				gameOver = !checkCollision(tetro, gameBoard, currentRotation, currentX, currentY);
                alreadyHeld = false;
			}
		}

		util.clearRenderer();
		util.drawPlayBoard(gameBoard);
		util.drawShadowPiece(tetro, gameBoard, currentX, currentY, currentRotation);
		util.drawCurrentPiece(tetro, currentX, currentY, currentRotation);
		util.drawNextPiece(nextTetro);
		if (heldPiece < 7) util.drawHeldPiece(heldPiece);
		util.TopScreen();

 		scoreText = "Score: " + to_string(score);
		levelText = "Level: " + to_string(level);
		util.writeText(scoreText, 10, 10, strlen(scoreText.c_str()) * GRID_SIZE, 40);
		util.writeText(levelText, 10, GRID_SIZE * 2, strlen(levelText.c_str()) * GRID_SIZE, 40);
		util.writeText("Next Piece", BOARD_WIDTH * GRID_SIZE - 15, GRID_SIZE * 2 + TOP_SPACE + 10, GRID_SIZE * 4, GRID_SIZE);
		util.writeText("Held Piece", BOARD_WIDTH* GRID_SIZE - 15, GRID_SIZE * 2 + TOP_SPACE * 2.5 + 10, GRID_SIZE * 4, GRID_SIZE);
		util.UpdateRender();
	}
	finalScore = score;
	if (currentGameState != GameState::QUIT) currentGameState = GameState::GAME_OVER;
}

void menu(Util util)
{
	util.clearRenderer();
	SDL_Texture* IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
	util.writeText("Tetris!!!", SCREEN_WIDTH / 8, GRID_SIZE, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 10);
	util.writeText("Controls:", SCREEN_WIDTH / 8, 200, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 20);
	util.writeText("Arrow keys to move pieces", SCREEN_WIDTH / 6, 250, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 25);
	util.writeText("Upward arrow key to rotate", SCREEN_WIDTH / 6, GRID_SIZE * 10, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 25);
	util.writeText("Spacebar to 'hard drop' a piece", SCREEN_WIDTH / 6, 350, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 25);
	util.writeText("C to hold a piece", SCREEN_WIDTH / 6, 400, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 25);
	util.writeText("M to mute/unmute background music", SCREEN_WIDTH / 6, 450, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 25);
	util.writeText("Esc to quit the game", SCREEN_WIDTH / 6, 500, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 25);
	util.writeText("Press enter to start", SCREEN_WIDTH / 8, 600, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 15);
	util.UpdateRender();
	while (currentGameState == GameState::START_MENU)
	{

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
            if (e.type == SDL_QUIT)
            {
                currentGameState = GameState::QUIT;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    currentGameState = GameState::IN_GAME;
                }
                else if (e.key.keysym.sym == SDLK_m)
                {
                    muted = true;
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    currentGameState = GameState::QUIT;
                }
            }
		}
	}
}

void gameOver(Util util)
{
    Mix_VolumeMusic(0);
	while (currentGameState == GameState::GAME_OVER)
	{
		util.clearRenderer();

		util.writeText("GAME OVER", SCREEN_WIDTH / 8, GRID_SIZE, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 10);
		string scoreText = "Final Score: " + to_string(finalScore);
		util.writeText(scoreText, SCREEN_WIDTH / 4, 200, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 20);
		util.writeText("Press Esc to exit", SCREEN_WIDTH / 8, GRID_SIZE * 10, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 15);
		util.writeText("Press Enter to restart", SCREEN_WIDTH / 8, 400, SCREEN_WIDTH / 1.25, SCREEN_HEIGHT / 15);
		util.UpdateRender();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
            if (e.type == SDL_QUIT)
            {
                currentGameState = GameState::QUIT;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    currentGameState = GameState::IN_GAME;
                }
                else if (e.key.keysym.sym == SDLK_m)
                {
                    muted = true;
                }
                else if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                currentGameState = GameState::QUIT;
                }
            }
		}
	}
}

void Loop()
{
	Tetromino tetro;
	Board gameBoard;
	Util util;

	while (currentGameState != GameState::QUIT)
	{
		if (currentGameState == GameState::START_MENU)
        {
            menu(util);
        }
        else if (currentGameState == GameState::IN_GAME)
        {
            gameLoop(util);
        }
        else if (currentGameState == GameState::GAME_OVER)
        {
            gameOver(util);
        }
	}
	util.destroy();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

int main(int argc, char* argv[])
{
	Loop();
	return 0;
}

