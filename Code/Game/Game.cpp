#include "Game.h"

#include <fstream>
#include <iostream>
#include "../Tools/Console.h"
#include "../Tools/InputManager.h"
#include "../Tools/FileManager.h"

const std::wstring Game::FONT_NAME = L"Consolas";

Game::~Game()
{
	Console::ClearScreen();
}

bool Game::IsRunning() const
{
	return isRunning;
}

void Game::HandleInput()
{
	switch (currentGameWindow)
	{
	case GameWindow::StartScreen:
		HandleInputStartScreen();
		break;

	case GameWindow::Menu:
		HandleInputMenu();
		break;

	case GameWindow::GameScene:
		HandleInputGameScene();
		break;

	default:
		throw GameException("Incorrect 'currentGameWindow' value", __func__, __LINE__);
	}
}

void Game::Update(double deltaTime)
{
	switch (currentGameWindow)
	{
	case GameWindow::StartScreen:
		// No code
		break;

	case GameWindow::Menu:
		UpdateMenu();
		break;

	case GameWindow::GameScene:
		UpdateGameScene(deltaTime);
		break;

	default:
		throw GameException("Incorrect 'currentGameWindow' value", __func__, __LINE__);
	}
}

void Game::Render()
{
	switch (currentGameWindow)
	{
	case GameWindow::StartScreen:
		RenderStartScreen();
		break;

	case GameWindow::Menu:
		RenderMenu();
		break;

	case GameWindow::GameScene:
		RenderGameScene();
		break;

	default:
		throw GameException("Incorrect 'currentGameWindow' value", __func__, __LINE__);
	}
}

void Game::HandleException(const std::exception& exception)
{
	isRunning = false;

	const GameException* gameException = dynamic_cast<const GameException*>(&exception);

	Console::ClearScreen();
	if (gameException != nullptr)
	{
		std::cout << "Game exception was thrown!\n";
		std::cout << "Message:  " << gameException->GetErrorMessage() << "\n";
		std::cout << "Function: " << gameException->GetFunctionName() << "\n";
		std::cout << "Line #:   " << gameException->GetLineNumber() << "\n";
		std::cout << "\nGame will be stopped.\n";
	}
	else
	{
		std::cout << "Some undefined exception was thrown!\n";
		std::cout << "Message:  " << exception.what() << std::endl;
		std::cout << "\nGame will be stopped.\n";
	}
	Console::PauseApplication();
}

Game& Game::GetInstance()
{
	static Game game;
	return game;
}

Game::Game()
{
	SetApplicationSettings();
	ReadGameDataFromFiles();
	Console::ChangeColorTheme(Console::ColorTheme(currentColorTheme));
	SetScoresOnBestScoresMenu();
}

void Game::SetApplicationSettings()
{
	Console::SetTitle("Console Snake");
	Console::SetFontSettings(FONT_SIZE, FONT_NAME);
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::HideCursor();
	Console::DisableScrollBars();
	Console::DisableMaximizeButton();
	Console::DisableWindowResizing();
}

void Game::HandleInputStartScreen()
{
	// If user wants to switch on main menu immidiately, user will
	// press some key. We need to remove it from input buffer for
	// no doing action in the main menu.
	if (InputManager::UserPressedKey())
	{
		InputManager::PressedKey();

		currentGameWindow = GameWindow::Menu;
	}
}

void Game::HandleInputMenu()
{
	switch (currentMenu)
	{
	case MenuType::MainMenu:
		HandleInputMainMenu();
		break;

	case MenuType::Tutorials:
		HandleInputTutorialsMenu();
		break;

	case MenuType::OptionsMenu:
		HandleInputOptionsMenu();
		break;

	case MenuType::GraphicsMenu:
		HandleInputGraphicsMenu();
		break;

	case MenuType::GameModesMenu:
		HandleInputGameModesMenu();
		break;

	case MenuType::ClassicGameOverMenu:
		HandleInputGameOverMenu();
		break;

	case MenuType::BestScoresMenu:
		HandleInputBestScoresMenu();
		break;

	case MenuType::ConfirmationMenu:
		HandleInputConfirmationMenu();
		break;

	case MenuType::CompanyLevelsMenu:
		HandleInputCompanyLevelsMenu();
		break;

	case MenuType::WinLevelMenu:
		HandleInputWinLevelMenu();
		break;

	case MenuType::CompanyGameOverMenu:
		HandleInputCompanyGameOverMenu();
		break;

	default:
		throw GameException("Incorrect 'currentMenu' value", __func__, __LINE__);
	}
}

void Game::HandleInputGameScene()
{
	Direction userInputDirection = Direction::None;

	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			userInputDirection = Direction::Up;
			break;

		case InputManager::Key::ArrowRight:
			userInputDirection = Direction::Right;
			break;

		case InputManager::Key::ArrowDown:
			userInputDirection = Direction::Down;
			break;

		case InputManager::Key::ArrowLeft:
			userInputDirection = Direction::Left;
			break;

		case InputManager::Key::Escape:
			currentGameWindow = GameWindow::Menu;
			DeallocateGameObjects();
			return;
		}
	}

	if (snake->CanChangeDirection())
		snake->SetHeadDirection(userInputDirection);
}

void Game::UpdateMenu()
{
	switch (currentMenu)
	{
	case MenuType::MainMenu:
		UpdateMainMenu();
		break;

	case MenuType::OptionsMenu:
		UpdateOptionsMenu();
		break;

	case MenuType::GraphicsMenu:
		UpdateGraphicsMenu();
		break;

	case MenuType::GameModesMenu:
		UpdateGameModesMenu();
		break;

	case MenuType::ConfirmationMenu:
		UpdateConfirmationMenu();
		break;

	case MenuType::CompanyLevelsMenu:
		UpdateCompanyLevelsMenu();
		break;

	case MenuType::ClassicGameOverMenu:
	case MenuType::CompanyGameOverMenu:
	case MenuType::Tutorials:
	case MenuType::BestScoresMenu:
	case MenuType::WinLevelMenu:
		// No code
		break;

	default:
		throw GameException("Incorrect 'currentMenu' value", __func__, __LINE__);
	}
}

void Game::UpdateGameScene(double deltaTime)
{
	selectedGameMode == GameMode::Classic ? UpdateGameSceneClassic(deltaTime) : UpdateGameSceneCompany(deltaTime);
}

void Game::RenderStartScreen() const
{
	static size_t showedCharacterIndex = 0;
	static bool companyLogoShowed = false;
	static bool gameLogoShowed = false;

	unsigned animationDelayInMilliseconds = 50;
	unsigned delayBetweenLogos = 2000;

	if (!companyLogoShowed)
	{
		if (showedCharacterIndex < companyLogoContent.length())
		{
			std::cout << companyLogoContent[showedCharacterIndex];

			if (companyLogoContent[showedCharacterIndex] == '\n')
				Console::StopFor(animationDelayInMilliseconds);

			showedCharacterIndex++;
		}
		else
		{
			companyLogoShowed = true;
			Console::StopFor(delayBetweenLogos);
			Console::ClearScreen();

			showedCharacterIndex = 0;
		}
	}
	else if (!gameLogoShowed)
	{
		if (showedCharacterIndex < gameLogoContent.length())
		{
			std::cout << gameLogoContent[showedCharacterIndex];

			if (gameLogoContent[showedCharacterIndex] == '\n')
				Console::StopFor(animationDelayInMilliseconds);

			showedCharacterIndex++;
		}
		else
		{
			gameLogoShowed = true;
			Console::StopFor(delayBetweenLogos);
			Console::ClearScreen();
		}
	}
	else
	{
		currentGameWindow = GameWindow::Menu;
	}
}

void Game::RenderMenu() const
{
	Console::ResetCursorPosition();

	switch (currentMenu)
	{
	case MenuType::MainMenu:
		std::cout << mainMenuContent;
		break;

	case MenuType::Tutorials:
		std::cout << tutorialPagesContents[currentTutorialPageIndex];
		break;

	case MenuType::OptionsMenu:
		std::cout << optionsMenuContent;
		break;

	case MenuType::GraphicsMenu:
		std::cout << graphicsMenuContent;
		break;

	case MenuType::GameModesMenu:
		std::cout << gameModesMenuContent;
		break;

	case MenuType::ClassicGameOverMenu:
		std::cout << classicGameOverMenuContent;
		break;

	case MenuType::CompanyGameOverMenu:
		std::cout << companyGameOverMenuContent;
		break;

	case MenuType::BestScoresMenu:
		std::cout << bestScoresMenuContent;
		break;

	case MenuType::ConfirmationMenu:
		std::cout << confirmationMenuContent;
		break;

	case MenuType::CompanyLevelsMenu:
		std::cout << companyLevelsMenuContent;
		break;

	case MenuType::WinLevelMenu:
		std::cout << winLevelMenuContent;
		break;

	default:
		throw GameException("Incorrect 'currentMenu' value", __func__, __LINE__);
	}
}

void Game::RenderGameScene() const
{
	field->Clear();

	field->Set(*walls);
	field->Set(*apple);
	field->Set(*snake);

	field->Render();
}

void Game::ReadGameDataFromFiles()
{
	// Method 'ReadXXXFromFile' can return 'false'. I want to invoke
	// these methods in 'Game' constructor. If this method would
	// throw exception, there will be problems with Game destructing.
	// So I will handle this problem here in 'try-catch' blocks.

	try
	{
		// --- Read start screen logos ---

		if (!FileManager::ReadTextFromFile(companyLogoFilename, companyLogoContent))
			throw GameException("File " + companyLogoFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(gameLogoFilename, gameLogoContent))
			throw GameException("File " + gameLogoFilename + " could not been opened/created.");

		// --- Read menus ---

		if (!FileManager::ReadTextFromFile(mainMenuFilename, mainMenuContent))
			throw GameException("File " + mainMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(optionsMenuFilename, optionsMenuContent))
			throw GameException("File " + optionsMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(graphicsMenuFilename, graphicsMenuContent))
			throw GameException("File " + graphicsMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(gameModesMenuFilename, gameModesMenuContent))
			throw GameException("File " + gameModesMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(classicGameOverMenuFilename, classicGameOverMenuContent))
			throw GameException("File " + classicGameOverMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(companyGameOverMenuFilename, companyGameOverMenuContent))
			throw GameException("File " + companyGameOverMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(bestScoresMenuFilename, bestScoresMenuContent))
			throw GameException("File " + bestScoresMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(confirmationMenuFilename, confirmationMenuContent))
			throw GameException("File " + confirmationMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(companyLevelsMenuFilename, companyLevelsMenuContent))
			throw GameException("File " + companyLevelsMenuFilename + " could not been opened/created.");

		if (!FileManager::ReadTextFromFile(winLevelMenuFilename, winLevelMenuContent))
			throw GameException("File " + winLevelMenuFilename + " could not been opened/created.");

		// --- Read tutorial pages ---

		for (size_t i = 0; i < TUTORIAL_PAGES_COUNT; i++)
			if (!FileManager::ReadTextFromFile(tutorialPagesNames[i], tutorialPagesContents[i]))
				throw GameException("File " + tutorialPagesNames[i] + " could not been opened/created.");

		// --- Read color theme ---

		if (!FileManager::ReadColorThemeFromFile(colorThemeFilename, currentColorTheme))
			throw GameException("Theme could not been read from " + colorThemeFilename);

		// --- Read score table ---

		if (!FileManager::ReadScoreTableFromFile(bestScoresFilename, bestScoresTable, BEST_SCORES_COUNT))
			throw GameException("Score table could not been read from " + bestScoresFilename);

		// --- Read company levels ---
		for (size_t i = 0; i < COMPANY_LEVELS_COUNT; i++)
			if (!FileManager::ReadTextFromFile(companyLevels[i].name, companyLevels[i].content))
				throw GameException("File " + companyLevels[i].name + " could not been opened/created.");

		// --- Read company progress ---
		if (!FileManager::ReadCompanyProgress(companyProgressFilename, companyLevels, COMPANY_LEVELS_COUNT))
			throw GameException("Company progress could not been read from " + companyProgressFilename);
	}
	catch (const std::exception& error)
	{
		HandleException(error);
	}
}

void Game::HandleInputMainMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			ChangeMenuItemUp(mainMenuSelectedItem, MainMenuItem::StartGame, MainMenuItem::Exit);
			break;

		case InputManager::Key::ArrowDown:
			ChangeMenuItemDown(mainMenuSelectedItem, MainMenuItem::StartGame, MainMenuItem::Exit);
			break;

		case InputManager::Key::Enter:
			switch (mainMenuSelectedItem)
			{
			case MainMenuItem::StartGame:
				currentMenu = MenuType::GameModesMenu;
				break;
			case MainMenuItem::Scores:
				currentMenu = MenuType::BestScoresMenu;
				break;
			case MainMenuItem::Tutorials:
				currentMenu = MenuType::Tutorials;
				break;
			case MainMenuItem::Options:
				currentMenu = MenuType::OptionsMenu;
				break;
			case MainMenuItem::Exit:
				isRunning = false;
				break;
			}
			break;

		case InputManager::Key::Escape:
			isRunning = false;
			break;
		}
	}
}

void Game::HandleInputTutorialsMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowRight:
			if (currentTutorialPageIndex < TUTORIAL_PAGES_COUNT - 1)
				currentTutorialPageIndex++;
			break;

		case InputManager::Key::ArrowLeft:
			if (currentTutorialPageIndex > 0)
				currentTutorialPageIndex--;
			break;

		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputOptionsMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			ChangeMenuItemUp(optionsMenuSelectedItem, OptionsMenuItem::Graphics, OptionsMenuItem::BackToMainMenu);
			break;

		case InputManager::Key::ArrowDown:
			ChangeMenuItemDown(optionsMenuSelectedItem, OptionsMenuItem::Graphics, OptionsMenuItem::BackToMainMenu);
			break;

		case InputManager::Key::Enter:
			switch (optionsMenuSelectedItem)
			{
			case OptionsMenuItem::Graphics:
				currentMenu = MenuType::GraphicsMenu;
				break;
			case OptionsMenuItem::DeleteScores:
				operationToConfirm = OperationToConfirm::DeleteScores;
				currentMenu = MenuType::ConfirmationMenu;
				break;
			case OptionsMenuItem::DeleteSaves:
				operationToConfirm = OperationToConfirm::DeleteCompanyProgress;
				currentMenu = MenuType::ConfirmationMenu;
				break;
			case OptionsMenuItem::BackToMainMenu:
				currentMenu = MenuType::MainMenu;
				break;
			}
			break;

		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputGraphicsMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			ChangeMenuItemUp(graphicsMenuSelectedItem, GraphicsMenuItem::ColorScheme1, GraphicsMenuItem::BackToOptionsMenu);
			break;

		case InputManager::Key::ArrowDown:
			ChangeMenuItemDown(graphicsMenuSelectedItem, GraphicsMenuItem::ColorScheme1, GraphicsMenuItem::BackToOptionsMenu);
			break;

		case InputManager::Key::Enter:
			switch (graphicsMenuSelectedItem)
			{
			case GraphicsMenuItem::ColorScheme1:
				currentColorTheme = ColorTheme::Black_Green;
				Console::ChangeColorTheme(Console::ColorTheme(ColorTheme::Black_Green));
				FileManager::WriteColorThemeInFile(colorThemeFilename, currentColorTheme);
				break;
			case GraphicsMenuItem::ColorScheme2:
				currentColorTheme = ColorTheme::LightAqua_Black;
				Console::ChangeColorTheme(Console::ColorTheme(ColorTheme::LightAqua_Black));
				FileManager::WriteColorThemeInFile(colorThemeFilename, currentColorTheme);
				break;
			case GraphicsMenuItem::ColorScheme3:
				currentColorTheme = ColorTheme::LightYellow_Purple;
				Console::ChangeColorTheme(Console::ColorTheme(ColorTheme::LightYellow_Purple));
				FileManager::WriteColorThemeInFile(colorThemeFilename, currentColorTheme);
				break;
			case GraphicsMenuItem::BackToOptionsMenu:
				currentMenu = MenuType::OptionsMenu;
				break;
			}
			break;

		case InputManager::Key::Escape:
			currentMenu = MenuType::OptionsMenu;
			break;
		}
	}
}

void Game::HandleInputGameModesMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			ChangeMenuItemUp(gameModesMenuSelectedItem, GameModesMenuItem::Classic, GameModesMenuItem::BackToMainMenu);
			break;

		case InputManager::Key::ArrowDown:
			ChangeMenuItemDown(gameModesMenuSelectedItem, GameModesMenuItem::Classic, GameModesMenuItem::BackToMainMenu);
			break;

		case InputManager::Key::Enter:
			switch (gameModesMenuSelectedItem)
			{
			case GameModesMenuItem::Classic:
				currentGameWindow = GameWindow::GameScene;
				selectedGameMode = GameMode::Classic;
				AllocateGameObjects();
				break;
			case GameModesMenuItem::Company:
				currentMenu = MenuType::CompanyLevelsMenu;
				selectedGameMode = GameMode::Company;
				AllocateGameObjects();
				break;
			case GameModesMenuItem::BackToMainMenu:
				currentMenu = MenuType::MainMenu;
				break;
			}
			break;

		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputGameOverMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputBestScoresMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputConfirmationMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			ChangeMenuItemUp(confirmationMenuSelectedItem, ConfirmationMenuItem::Yes, ConfirmationMenuItem::No);
			break;

		case InputManager::Key::ArrowDown:
			ChangeMenuItemDown(confirmationMenuSelectedItem, ConfirmationMenuItem::Yes, ConfirmationMenuItem::No);
			break;

		case InputManager::Key::Enter:
			switch (confirmationMenuSelectedItem)
			{
			case ConfirmationMenuItem::Yes:
				if (operationToConfirm == OperationToConfirm::DeleteScores)
				{
					for (size_t i = 0; i < BEST_SCORES_COUNT; i++)
						bestScoresTable[i].Reset();

					SetScoresOnBestScoresMenu();

					FileManager::WriteScoreTableInFile(bestScoresFilename, bestScoresTable, BEST_SCORES_COUNT);
				}
				else if (operationToConfirm == OperationToConfirm::DeleteCompanyProgress)
				{
					for (size_t i = 1; i < COMPANY_LEVELS_COUNT; i++)
						companyLevels[i].isOpen = false;

					FileManager::WriteCompanyProgressInFile(companyProgressFilename, companyLevels, COMPANY_LEVELS_COUNT);
				}

				currentMenu = MenuType::MainMenu;
				break;

			case ConfirmationMenuItem::No:
				currentMenu = MenuType::MainMenu;
				break;
			}
			break;

		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputCompanyLevelsMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::ArrowUp:
			ChangeMenuItemUp(companyLevelsMenuSelecetedItem, CompanyLevelsMenuItem::Level1, CompanyLevelsMenuItem::BackToMainMenu);
			break;

		case InputManager::Key::ArrowDown:
			ChangeMenuItemDown(companyLevelsMenuSelecetedItem, CompanyLevelsMenuItem::Level1, CompanyLevelsMenuItem::BackToMainMenu);
			break;

		case InputManager::Key::Enter:
			switch (companyLevelsMenuSelecetedItem)
			{
			case CompanyLevelsMenuItem::BackToMainMenu:
				currentMenu = MenuType::MainMenu;
				break;
			default: // Player chose some level
				currentCompanyLevelIndex = static_cast<size_t>(companyLevelsMenuSelecetedItem) - 1;

				if (!companyLevels[currentCompanyLevelIndex].isOpen)
					return;

				AllocateGameObjects();
				playerScore.Reset();

				currentGameWindow = GameWindow::GameScene;
				break;
			}
			break;

		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputWinLevelMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::HandleInputCompanyGameOverMenu()
{
	if (InputManager::UserPressedKey())
	{
		InputManager::Key key = InputManager::PressedKey();

		switch (key)
		{
		case InputManager::Key::Escape:
			currentMenu = MenuType::MainMenu;
			break;
		}
	}
}

void Game::UpdateMainMenu()
{
	// Remove Arrow on selected item.
	if (size_t arrowPosition = mainMenuContent.find("->"); arrowPosition != std::string::npos)
	{
		// Menu items contain this pattern "[  ]".
		// Selected item looks like this pattern "[->]".
		// To remove '-' and '>' characters, we need to
		// change them to ' ' character on selectedItemPosition
		// and selectedItemPosition + 1.
		mainMenuContent[arrowPosition] = ' ';
		mainMenuContent[arrowPosition + 1] = ' ';
	}

	size_t selectedItemPosition;

	switch (mainMenuSelectedItem)
	{
	case MainMenuItem::StartGame:
		selectedItemPosition = mainMenuContent.find("Start Game");
		break;
	case MainMenuItem::Scores:
		selectedItemPosition = mainMenuContent.find("Scores");
		break;
	case MainMenuItem::Tutorials:
		selectedItemPosition = mainMenuContent.find("Tutorials");
		break;
	case MainMenuItem::Options:
		selectedItemPosition = mainMenuContent.find("Options");
		break;
	case MainMenuItem::Exit:
		selectedItemPosition = mainMenuContent.find("Exit");
		break;
	default:
		throw GameException("Incorrect 'mainMenuSelectedItem' value", __func__, __LINE__);
	}

	if (selectedItemPosition == std::string::npos)
		throw GameException("Main menu is incorrect", __func__, __LINE__);

	mainMenuContent[selectedItemPosition - 4] = '-';
	mainMenuContent[selectedItemPosition - 3] = '>';
}

void Game::UpdateOptionsMenu()
{
	// Remove Arrow on selected item.
	if (size_t arrowPosition = optionsMenuContent.find("->"); arrowPosition != std::string::npos)
	{
		// Menu items contain this pattern "[  ]".
		// Selected item looks like this pattern "[->]".
		// To remove '-' and '>' characters, we need to
		// change them to ' ' character on selectedItemPosition
		// and selectedItemPosition + 1.
		optionsMenuContent[arrowPosition] = ' ';
		optionsMenuContent[arrowPosition + 1] = ' ';
	}

	size_t selectedItemPosition;

	switch (optionsMenuSelectedItem)
	{
	case OptionsMenuItem::Graphics:
		selectedItemPosition = optionsMenuContent.find("Graphics");
		break;
	case OptionsMenuItem::DeleteScores:
		selectedItemPosition = optionsMenuContent.find("Delete scores");
		break;
	case OptionsMenuItem::DeleteSaves:
		selectedItemPosition = optionsMenuContent.find("Delete saves");
		break;
	case OptionsMenuItem::BackToMainMenu:
		selectedItemPosition = optionsMenuContent.find("Back to main menu");
		break;
	default:
		throw GameException("Incorrect 'optionsMenuSelectedItem' value", __func__, __LINE__);
	}

	if (selectedItemPosition == std::string::npos)
		throw GameException("Options menu is incorrect", __func__, __LINE__);

	optionsMenuContent[selectedItemPosition - 4] = '-';
	optionsMenuContent[selectedItemPosition - 3] = '>';
}

void Game::UpdateGraphicsMenu()
{
	// Remove Arrow on selected item.
	if (size_t arrowPosition = graphicsMenuContent.find("->"); arrowPosition != std::string::npos)
	{
		// Menu items contain this pattern "[  ]".
		// Selected item looks like this pattern "[->]".
		// To remove '-' and '>' characters, we need to
		// change them to ' ' character on selectedItemPosition
		// and selectedItemPosition + 1.
		graphicsMenuContent[arrowPosition] = ' ';
		graphicsMenuContent[arrowPosition + 1] = ' ';
	}

	// Remove + sign on selected color theme.
	if (size_t signPosition = graphicsMenuContent.find('+'); signPosition != std::string::npos)
		graphicsMenuContent[signPosition] = ' ';

	size_t selectedItemPosition;

	switch (graphicsMenuSelectedItem)
	{
	case GraphicsMenuItem::ColorScheme1:
		selectedItemPosition = graphicsMenuContent.find("Black & Green");
		break;
	case GraphicsMenuItem::ColorScheme2:
		selectedItemPosition = graphicsMenuContent.find("Aqua & Black");
		break;
	case GraphicsMenuItem::ColorScheme3:
		selectedItemPosition = graphicsMenuContent.find("Yellow & Purple");
		break;
	case GraphicsMenuItem::BackToOptionsMenu:
		selectedItemPosition = graphicsMenuContent.find("Back to main menu");
		break;
	default:
		throw GameException("Incorrect 'graphicsMenuSelectedItem' value", __func__, __LINE__);
	}

	if (selectedItemPosition == std::string::npos)
		throw GameException("Graphics menu is incorrect", __func__, __LINE__);

	graphicsMenuContent[selectedItemPosition - 4] = '-';
	graphicsMenuContent[selectedItemPosition - 3] = '>';

	// Set '+' sign to selected color theme.
	size_t selectedColorThemePosition;

	switch (currentColorTheme)
	{
	case ColorTheme::Black_Green:
		selectedColorThemePosition = graphicsMenuContent.find("Black & Green");
		break;
	case ColorTheme::LightAqua_Black:
		selectedColorThemePosition = graphicsMenuContent.find("Aqua & Black");
		break;
	case ColorTheme::LightYellow_Purple:
		selectedColorThemePosition = graphicsMenuContent.find("Yellow & Purple");
		break;
	default:
		throw GameException("Incorrect 'currentColorScheme' value", __func__, __LINE__);
	}

	graphicsMenuContent[selectedColorThemePosition + 17] = '+';

	// Why 17? Look at this row (for example):
	// 
	//       | start here     | plus position here (after 17 characters)
	//       v                v
	// "[  ] Black & Green   { }"
}

void Game::UpdateGameModesMenu()
{
	// Remove Arrow on selected item.
	if (size_t arrowPosition = gameModesMenuContent.find("->"); arrowPosition != std::string::npos)
	{
		// Menu items contain this pattern "[  ]".
		// Selected item looks like this pattern "[->]".
		// To remove '-' and '>' characters, we need to
		// change them to ' ' character on selectedItemPosition
		// and selectedItemPosition + 1.
		gameModesMenuContent[arrowPosition] = ' ';
		gameModesMenuContent[arrowPosition + 1] = ' ';
	}

	size_t selectedItemPosition;

	switch (gameModesMenuSelectedItem)
	{
	case GameModesMenuItem::Classic:
		selectedItemPosition = gameModesMenuContent.find("Classic");
		break;
	case GameModesMenuItem::Company:
		selectedItemPosition = gameModesMenuContent.find("Company");
		break;
	case GameModesMenuItem::BackToMainMenu:
		selectedItemPosition = gameModesMenuContent.find("Back to main menu");
		break;
	default:
		throw GameException("Incorrect 'gameModesMenuSelectedItem' value", __func__, __LINE__);
	}

	if (selectedItemPosition == std::string::npos)
		throw GameException("Game Modes menu is incorrect", __func__, __LINE__);

	gameModesMenuContent[selectedItemPosition - 4] = '-';
	gameModesMenuContent[selectedItemPosition - 3] = '>';
}

void Game::UpdateConfirmationMenu()
{
	// Remove Arrow on selected item.
	if (size_t arrowPosition = confirmationMenuContent.find("->"); arrowPosition != std::string::npos)
	{
		// Menu items contain this pattern "[  ]".
		// Selected item looks like this pattern "[->]".
		// To remove '-' and '>' characters, we need to
		// change them to ' ' character on selectedItemPosition
		// and selectedItemPosition + 1.
		confirmationMenuContent[arrowPosition] = ' ';
		confirmationMenuContent[arrowPosition + 1] = ' ';
	}

	size_t selectedItemPosition;

	switch (confirmationMenuSelectedItem)
	{
	case ConfirmationMenuItem::Yes:
		selectedItemPosition = confirmationMenuContent.find("Yes");
		break;
	case ConfirmationMenuItem::No:
		selectedItemPosition = confirmationMenuContent.find("No");
		break;
	default:
		throw GameException("Incorrect 'confirmationMenuSelectedItem' value", __func__, __LINE__);
	}

	if (selectedItemPosition == std::string::npos)
		throw GameException("Confirmation menu is incorrect", __func__, __LINE__);

	confirmationMenuContent[selectedItemPosition - 4] = '-';
	confirmationMenuContent[selectedItemPosition - 3] = '>';
}

void Game::UpdateCompanyLevelsMenu()
{
	// Remove or add title '(Closed)' from open levels:
	for (size_t i = 0; i < COMPANY_LEVELS_COUNT; i++)
	{
		if (companyLevels[i].isOpen)
		{
			size_t closedTitlePosition = companyLevelsMenuContent.find("Level " + std::to_string(i + 1) + " (Closed)");

			if (closedTitlePosition == std::string::npos)
				continue;

			// Length of "Level N " is 8.
			// Length of "(Closed)" is 8.                                 8 spaces
			companyLevelsMenuContent.replace(closedTitlePosition + 8, 8, "        ");
		}
		else
		{
			size_t closedTitlePosition = companyLevelsMenuContent.find("Level " + std::to_string(i + 1));

			if (closedTitlePosition == std::string::npos)
				continue;

			// Length of "Level N " is 8.
			// Length of "(Closed)" is 8.
			companyLevelsMenuContent.replace(closedTitlePosition + 8, 8, "(Closed)");
		}
	}

	// Remove Arrow on selected item.
	if (size_t arrowPosition = companyLevelsMenuContent.find("->"); arrowPosition != std::string::npos)
	{
		// Menu items contain this pattern "[  ]".
		// Selected item looks like this pattern "[->]".
		// To remove '-' and '>' characters, we need to
		// change them to ' ' character on selectedItemPosition
		// and selectedItemPosition + 1.
		companyLevelsMenuContent[arrowPosition] = ' ';
		companyLevelsMenuContent[arrowPosition + 1] = ' ';
	}

	size_t selectedItemPosition;

	switch (companyLevelsMenuSelecetedItem)
	{
	case CompanyLevelsMenuItem::Level1:
		selectedItemPosition = companyLevelsMenuContent.find("Level 1");
		break;
	case CompanyLevelsMenuItem::Level2:
		selectedItemPosition = companyLevelsMenuContent.find("Level 2");
		break;
	case CompanyLevelsMenuItem::Level3:
		selectedItemPosition = companyLevelsMenuContent.find("Level 3");
		break;
	case CompanyLevelsMenuItem::Level4:
		selectedItemPosition = companyLevelsMenuContent.find("Level 4");
		break;
	case CompanyLevelsMenuItem::Level5:
		selectedItemPosition = companyLevelsMenuContent.find("Level 5");
		break;
	case CompanyLevelsMenuItem::BackToMainMenu:
		selectedItemPosition = companyLevelsMenuContent.find("Back to main menu");
		break;
	default:
		throw GameException("Incorrect 'companyLevelsMenuSelecetedItem' value", __func__, __LINE__);
	}

	if (selectedItemPosition == std::string::npos)
		throw GameException("Company levels menu is incorrect", __func__, __LINE__);

	companyLevelsMenuContent[selectedItemPosition - 4] = '-';
	companyLevelsMenuContent[selectedItemPosition - 3] = '>';
}

void Game::UpdateGameSceneClassic(double deltaTime)
{
	// If snake is dead:
	if (!snake->IsAlive())
	{
		// Update scores:
		CheckScoreBeating();
		SetScoresOnGameOverMenu();

		// Update scores file:
		FileManager::WriteScoreTableInFile(bestScoresFilename, bestScoresTable, BEST_SCORES_COUNT);

		currentGameWindow = GameWindow::Menu;
		currentMenu = MenuType::ClassicGameOverMenu;

		DeallocateGameObjects();
		playerScore.Reset();

		return;
	}

	snake->Move(deltaTime, true); // true - classic mode

	// In classic mode snake never touches bound walls. So we don't need to check this collision.
	if (snake->IsTouchingItself())
	{
		snake->Kill();
	}
	else if (snake->IsTouching(*apple))
	{
		snake->ExpandTail();
		playerScore.AddPoints(1);

		Vector2u appleNewPosition = field->GetRandomEmptyPoint();
		apple->SetPosition(appleNewPosition);
	}
}

void Game::UpdateGameSceneCompany(double deltaTime)
{
	if (!snake->IsAlive())
	{
		currentGameWindow = GameWindow::Menu;
		currentMenu = MenuType::CompanyGameOverMenu;

		DeallocateGameObjects();

		return;
	}

	if (playerScore.Value() >= companyLevels[currentCompanyLevelIndex].requiredApples)
	{
		// Open next level:
		if (currentCompanyLevelIndex < COMPANY_LEVELS_COUNT - 1)
			companyLevels[currentCompanyLevelIndex + 1].isOpen = true;

		FileManager::WriteCompanyProgressInFile(companyProgressFilename, companyLevels, COMPANY_LEVELS_COUNT);

		currentGameWindow = GameWindow::Menu;
		currentMenu = MenuType::WinLevelMenu;

		DeallocateGameObjects();

		return;
	}

	snake->Move(deltaTime, false); // false - company mode

	if (snake->IsTouchingItself() || snake->IsTouching(*walls))
	{
		snake->Kill();
	}
	else if (snake->IsTouching(*apple))
	{
		snake->ExpandTail();
		playerScore.AddPoints(1);

		Vector2u appleNewPosition = field->GetRandomEmptyPoint();
		apple->SetPosition(appleNewPosition);
	}
}

void Game::AllocateGameObjects()
{
	field = std::make_unique<Field>(Vector2u{ WINDOW_WIDTH, WINDOW_HEIGHT });
	walls = std::make_unique<Walls>();

	if (selectedGameMode == GameMode::Classic)
	{
		if (!walls->InitializeFromFile(classicLevelFilename))
		{
			GameException error("File '" + classicLevelFilename + "' couldn't been open", __func__, __LINE__);
			HandleException(error);
		}
	}
	else if (selectedGameMode == GameMode::Company)
	{
		if (!walls->InitializeFromFile(companyLevels[currentCompanyLevelIndex].name))
		{
			GameException error("File '" + classicLevelFilename + "' couldn't been open", __func__, __LINE__);
			HandleException(error);
		}
	}

	field->Set(*walls);

	Vector2u snakeInitialPosition{ field->GetColumns() / 2, field->GetRows() / 2 };
	snake = std::make_unique<Snake>(snakeInitialPosition, Vector2u{ WINDOW_WIDTH, WINDOW_HEIGHT });

	Vector2u appleInitialPosition = field->GetRandomEmptyPoint();
	apple = std::make_unique<Apple>(appleInitialPosition);
}

void Game::DeallocateGameObjects()
{
	field.reset();
	walls.reset();
	snake.reset();
	apple.reset();
}

void Game::SetScoresOnGameOverMenu()
{
	// Set best score:
	if (size_t bestScorePosition = classicGameOverMenuContent.find("BEST"); bestScorePosition != std::string::npos)
	{
		// Length of 'BEST SCORE: [" is 13 characters. We will set score after this length.
		// TOP-1 score is 'bestScores[0]'.

		std::string bestScoreStr = bestScoresTable[0].ToString();
		classicGameOverMenuContent[bestScorePosition + 13] = bestScoreStr[0];
		classicGameOverMenuContent[bestScorePosition + 14] = bestScoreStr[1];
		classicGameOverMenuContent[bestScorePosition + 15] = bestScoreStr[2];
	}

	if (size_t userScorePosition = classicGameOverMenuContent.find("YOUR"); userScorePosition != std::string::npos)
	{
		// Length of 'YOUR SCORE: [" is 13 characters. We will set score after these length.
		// TOP-1 score is 'bestScores[0]'.

		std::string userScoreStr = playerScore.ToString();
		classicGameOverMenuContent[userScorePosition + 13] = userScoreStr[0];
		classicGameOverMenuContent[userScorePosition + 14] = userScoreStr[1];
		classicGameOverMenuContent[userScorePosition + 15] = userScoreStr[2];
	}
}

void Game::CheckScoreBeating()
{
	for (size_t i = 0; i < BEST_SCORES_COUNT; i++)
	{
		if (playerScore > bestScoresTable[i])
		{
			for (size_t j = BEST_SCORES_COUNT - 1; j > i; j--)
				bestScoresTable[j] = bestScoresTable[j - 1];

			bestScoresTable[i] = playerScore;

			SetScoresOnBestScoresMenu();
			return;
		}
	}
}

void Game::SetScoresOnBestScoresMenu()
{
	for (size_t i = 0; i < BEST_SCORES_COUNT; i++)
	{
		size_t scorePosition = bestScoresMenuContent.find(std::to_string(i + 1) + ".");
		std::string scoreString = bestScoresTable[i].ToString();

		bestScoresMenuContent[scorePosition + 3] = scoreString[0];
		bestScoresMenuContent[scorePosition + 4] = scoreString[1];
		bestScoresMenuContent[scorePosition + 5] = scoreString[2];
	}
}
