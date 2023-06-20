#pragma once
#include "GameEnumerations.h"
#include "GameException.h"
#include "../World/WorldHeaders.h"

// class Game is a main class that manages all game entities (Field, Snake, Apple, Walls, etc.).
// It handles user input, updates all entities and render them onto the screen.
class Game
{
public:
	~Game();

	// Main game cycle methods:
	bool IsRunning() const;
	void HandleInput();
	void Update(double deltaTime);
	void Render();

	void HandleException(const std::exception& exception);

	// Singlton pattern:
	static Game& GetInstance();
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

private:
	Game();

	void SetApplicationSettings();

	// -------------------------------------------------------------------------
	// ---------------------- MAIN HANDLE INPUT METHODS ------------------------

	void HandleInputStartScreen();
	void HandleInputMenu();
	void HandleInputGameScene();

	// -------------------------------------------------------------------------
	// ------------------------- MAIN UPDATE METHODS ---------------------------

	void UpdateMenu();
	void UpdateGameScene(double deltaTime);

	// -------------------------------------------------------------------------
	// ------------------------- MAIN RENDER METHODS ---------------------------

	void RenderStartScreen() const;
	void RenderMenu() const;
	void RenderGameScene() const;

	// -------------------------------------------------------------------------
	// ------------------- INITIAL READING ALL DATA METHOD ---------------------

	void ReadGameDataFromFiles();

	// -------------------------------------------------------------------------
	// --------------------- MENUS HANDLE INPUT METHODS ------------------------

	void HandleInputMainMenu();
	void HandleInputTutorialsMenu();
	void HandleInputOptionsMenu();
	void HandleInputGraphicsMenu();
	void HandleInputGameModesMenu();
	void HandleInputGameOverMenu();
	void HandleInputBestScoresMenu();
	void HandleInputConfirmationMenu();
	void HandleInputCompanyLevelsMenu();
	void HandleInputWinLevelMenu();
	void HandleInputCompanyGameOverMenu();

	// -------------------------------------------------------------------------
	// ------------------------ MENUS UPDATE METHODS ---------------------------

	void UpdateMainMenu();
	void UpdateOptionsMenu();
	void UpdateGraphicsMenu();
	void UpdateGameModesMenu();
	void UpdateConfirmationMenu();
	void UpdateCompanyLevelsMenu();

	// -------------------------------------------------------------------------
	// ---------------------- UPDATE GAME SCENE METHODS -------------------------

	void UpdateGameSceneClassic(double deltaTime);
	void UpdateGameSceneCompany(double deltaTime);

	// -------------------------------------------------------------------------
	// ---------------------- MEMORY MANAGEMENT METHODS ------------------------

	void AllocateGameObjects();
	void DeallocateGameObjects();

	// -------------------------------------------------------------------------
	// ---------------------- SCORE MANAGEMENT METHODS -------------------------

	void SetScoresOnGameOverMenu();
	void CheckScoreBeating();
	void SetScoresOnBestScoresMenu();

	// -------------------------------------------------------------------------
	// --------------------------- APPLICATION DATA ----------------------------
	bool isRunning = true;
	static constexpr unsigned WINDOW_WIDTH = 30, WINDOW_HEIGHT = 20;
	static constexpr short FONT_SIZE = 30;
	static const std::wstring FONT_NAME;

	// This field is mutable, because my 'Render...' methods are all const.
	// But after showing start screen game need to change this field
	// (switch to main menu). So method 'RenderStartScreen' changes this field.
	mutable GameWindow currentGameWindow = GameWindow::StartScreen;

	// -------------------------------------------------------------------------
	// ------------------------------- MENU DATA -------------------------------

	// - Current Menu Type - 
	MenuType currentMenu = MenuType::MainMenu;

	// - Company Logo -
	std::string companyLogoFilename = "Assets/Logos/CompanyLogo.txt";
	std::string companyLogoContent;

	// - Game Logo -
	std::string gameLogoFilename = "Assets/Logos/GameLogo.txt";
	std::string gameLogoContent;

	// - Main Menu -
	std::string mainMenuFilename = "Assets/Menus/MainMenu.txt";
	std::string mainMenuContent;
	MainMenuItem mainMenuSelectedItem = MainMenuItem::StartGame;

	// - Options Menu -
	std::string optionsMenuFilename = "Assets/Menus/OptionsMenu.txt";
	std::string optionsMenuContent;
	OptionsMenuItem optionsMenuSelectedItem = OptionsMenuItem::Graphics;

	// - Graphics Menu -
	std::string graphicsMenuFilename = "Assets/Menus/GraphicsMenu.txt";
	std::string graphicsMenuContent;
	GraphicsMenuItem graphicsMenuSelectedItem = GraphicsMenuItem::BackToOptionsMenu;

	// - Game Modes Menu -
	std::string gameModesMenuFilename = "Assets/Menus/GameModesMenu.txt";
	std::string gameModesMenuContent;
	GameModesMenuItem gameModesMenuSelectedItem = GameModesMenuItem::Classic;
	GameMode selectedGameMode = GameMode::None;

	// - Best Scores Menu -
	std::string bestScoresMenuFilename = "Assets/Menus/BestScoresMenu.txt";
	std::string bestScoresMenuContent;

	// - Company Levels Menu -
	std::string companyLevelsMenuFilename = "Assets/Menus/CompanyLevelsMenu.txt";
	std::string companyLevelsMenuContent;
	CompanyLevelsMenuItem companyLevelsMenuSelecetedItem = CompanyLevelsMenuItem::Level1;

	// - Win Level Menu -
	std::string winLevelMenuFilename = "Assets/Menus/WinLevelMenu.txt";
	std::string winLevelMenuContent;

	// - Confirmation Menu -
	std::string confirmationMenuFilename = "Assets/Menus/ConfirmationMenu.txt";
	std::string confirmationMenuContent;
	ConfirmationMenuItem confirmationMenuSelectedItem = ConfirmationMenuItem::No;
	OperationToConfirm operationToConfirm = OperationToConfirm::None;

	// - Classic Game Over Menu -
	std::string classicGameOverMenuFilename = "Assets/Menus/ClassicGameOverMenu.txt";
	std::string classicGameOverMenuContent;

	// - Company Game Over Menu -
	std::string companyGameOverMenuFilename = "Assets/Menus/CompanyGameOverMenu.txt";
	std::string companyGameOverMenuContent;

	// - Tutorials Pages -
	static const unsigned TUTORIAL_PAGES_COUNT = 3;
	std::string tutorialPagesNames[TUTORIAL_PAGES_COUNT] =
	{
		"Assets/Menus/TutorialPage1.txt",
		"Assets/Menus/TutorialPage2.txt",
		"Assets/Menus/TutorialPage3.txt"
	};
	std::string tutorialPagesContents[TUTORIAL_PAGES_COUNT];
	unsigned currentTutorialPageIndex = 0;

	// -------------------------------------------------------------------------
	// ------------------------------- GAME DATA -------------------------------

	// - Scores -
	std::string bestScoresFilename = "Data/BestScores.bin";
	static const unsigned BEST_SCORES_COUNT = 5;
	Score bestScoresTable[BEST_SCORES_COUNT];
	Score playerScore;

	// - Company Progress -
	std::string companyProgressFilename = "Data/CompanyProgress.bin";

	// - Color Scheme -
	std::string colorThemeFilename = "Data/ColorTheme.bin";
	ColorTheme currentColorTheme;

	// - Levels -
	std::string classicLevelFilename = "Assets/Levels/ClassicLevel.txt";
	static const unsigned COMPANY_LEVELS_COUNT = 5;
	Level companyLevels[COMPANY_LEVELS_COUNT] =
	{
		Level{ "Assets/Levels/CompanyLevel1.txt", "", true,  10 }, // first level is always open
		Level{ "Assets/Levels/CompanyLevel2.txt", "", false, 10 },
		Level{ "Assets/Levels/CompanyLevel3.txt", "", false, 10 },
		Level{ "Assets/Levels/CompanyLevel4.txt", "", false, 10 },
		Level{ "Assets/Levels/CompanyLevel5.txt", "", false, 10 }
	};
	unsigned currentCompanyLevelIndex;

	// - World Objects -
	mutable std::unique_ptr<Field> field;
	std::unique_ptr<Walls> walls;
	std::unique_ptr<Apple> apple;
	std::unique_ptr<Snake> snake;
};