
#include "Game.h"

#include "Helpers/ScaleTools/ScaleTools.h"

#include <iostream>

#include "Manager/FontManager/FontManager.h"

Game::Game(sf::RenderWindow& game_window)
  : window(game_window),
    game_view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f))
{
  srand(time(NULL));
  window.setView(game_view);

}

Game::~Game()
{


}

bool Game::init()
{

  loadFonts();
  loadData();
  loadBackground();
  loadSprites();

  // Load passport
  temp_passport = std::make_unique<Passport>(sf::Vector2f(600, 100), sf::Vector2f(PASSPORT_WIDTH, (PASSPORT_WIDTH*PASSPORT_HEIGHT_MULTIPLIER)));
  temp_passport->setDataManager(&passport_data_manager);

  // Init character
  temp_character = std::make_unique<Character>(sf::Vector2f(200, 200), sf::Vector2f(CHARACTER_WIDTH, (CHARACTER_WIDTH * CHARACTER_HEIGHT_MULTIPLIER)));


  return true;
}

void Game::update(float dt)
{
  // Handle Gameplay
  if (game_state == GameState::PLAY) {
    temp_character->loadCharacter(*character_data);

    dragPassport(passport_drag);
  }

}

void Game::render()
{
  // Handle Gameplay
  if (game_state == GameState::PLAY) {
    window.draw(background_sprite);
    window.draw(desk_sprite);
    window.draw(passport_slot_sprite);

    temp_character->draw(window, *this);
    temp_passport->draw(window, *this);
  }
}

void Game::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    sf::Vector2f mouse_pos_pixel = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (temp_passport->getPassportBounds().contains(mouse_pos_pixel))
    {
      passport_drag = temp_passport.get();
    }
  } else if (event.mouseButton.button == sf::Mouse::Right)
  {

  }

}

void Game::mouseReleased(sf::Event event)
{
  passport_drag = nullptr;
}


void Game::keyPressed(sf::Event event)
{

  if (event.type == sf::Event::KeyPressed)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      character_data = std::make_shared<CharacterAssetData>(character_creator.ChooseCharacter());
      temp_passport->initPassport(*character_data);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    {
      temp_passport->openPassport();
    }
  }

}


// View
const sf::View& Game::getDefaultView() {
  return game_view;
}

// --- PRIVATE ---
bool Game::loadBackground() {
  if (!background_texture.loadFromFile("../Data/Images/Background.png")) {
    std::cerr << "Failed to load background texture!" << std::endl;
    return false;
  }

  background_sprite.setTexture(background_texture);
  background_sprite.setScale(0.5f, 0.5f);
  return true;
}

bool Game::loadFonts() {
  if (!FontManager::getInstance().loadFont("Jua", "Jua/Jua-Regular.ttf")) {
    std::cerr << "Failed to load Jua font!" << std::endl;
    return false;
  }

  return true;
}

bool Game::loadData() {
  // Load Characters
  if (!character_creator.LoadCharacterTextures()) {
    std::cerr << "Failed to load character textures!" << std::endl;
    return false;
  }

  // Load Names in passport data manager
  if (!passport_data_manager.loadNameFile("nameList.txt")) {
    std::cerr << "Failed to load passport name data!" << std::endl;
    return false;
  };

  if (!passport_data_manager.loadDistrictFile("districtList.txt")) {
    std::cerr << "Failed to load passport district data!" << std::endl;
    return false;
  };

  return true;
}

bool Game::loadSprites() {
  // Load Desk
  if (!desk_texture.loadFromFile("../Data/Images/Planks/TablePlank.png")) {
    std::cout << "Desk texture failed to load!" << std::endl;
    return false;
  }
  desk_sprite.setTexture(desk_texture);
  desk_sprite.setScale(0.5f, 0.5f);
  desk_sprite.setPosition(ScaleTools::getScaledPosition(desk_unscaled_size, background_sprite));

  if (!passport_slot_texture.loadFromFile("../Data/Images/PassportSlot.png")) {
    std::cout << "Passport slot texture failed to load!" << std::endl;
    return false;
  }
  passport_slot_sprite.setTexture(passport_slot_texture);
  passport_slot_sprite.setScale(0.5f, 0.5f);
  passport_slot_sprite.setPosition(ScaleTools::getScaledPosition(passport_slot_unscaled_size, background_sprite));

  return true;
}

void Game::dragPassport(Passport* passport)
{
  if (passport != nullptr)
  {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos_f = static_cast<sf::Vector2f>(mouse_pos);

    sf::Vector2f drag_pos = sf::Vector2f(mouse_pos_f.x - DRAG_OFFSET, mouse_pos_f.y - DRAG_OFFSET);
    passport->setDragPosition(drag_pos, window.getSize());


  }
}







