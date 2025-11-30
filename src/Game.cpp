
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

  // Passport Slots
  passport_area.init("../Data/Images/Passport/Slots/PassportSlot.png");
  passport_area.setSlotType(SlotType::PASSPORT);
  passport_area.setAreaPosition(passport_area_unscaled_pos, background_sprite);

  return_area.init("../Data/Images/Passport/Slots/ReturnSlot.png");
  return_area.setSlotType(SlotType::RETURN);
  return_area.setAreaPosition(return_area_unscaled_pos, background_sprite);

  // Load passport
  passport_object = std::make_unique<Passport>(sf::Vector2f(600, 100),
    sf::Vector2f(PASSPORT_WIDTH, (PASSPORT_WIDTH*PASSPORT_HEIGHT_MULTIPLIER)));
  passport_object->setDataManager(&passport_data_manager);

  // Init character
  character_object = std::make_unique<Character>(
    ScaleTools::getScaledPosition(character_unsclaed_pos, background_sprite),
    sf::Vector2f(CHARACTER_WIDTH, (CHARACTER_WIDTH * CHARACTER_HEIGHT_MULTIPLIER)));

  // Passport Stamp
  passport_stamp = std::make_shared<PassportStamp>();

  // Feedback
  feedback.init("../Data/Images/FeedbackEffect.png", 0.5f, 0.5f, 0.1f);

  return true;
}

void Game::update(float dt)
{
  // Handle Gameplay
  if (game_state == GameState::PLAY)
  {
    character_object->loadCharacter(*character_data);

    dragPassport(passport_drag);

    if (passport_stamp_visible)
    {
      sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
      sf::Vector2f mouse_pos_coords = window.mapPixelToCoords(mouse_pos);
      passport_stamp->handleMouseHover(mouse_pos_coords);
    }

    feedback.update(dt);
  }

}

void Game::render()
{
  // Handle Gameplay
  if (game_state == GameState::PLAY) {
    window.draw(background_sprite);
    window.draw(desk_sprite);

    if (passport_object->getPassportStamp() == PassportStampValue::NONE)
    {
      passport_area.draw(window);
    }
    else
    {
      return_area.draw(window);
    }


    character_object->draw(window, *this);
    passport_object->draw(window, *this);

    passport_stamp->draw(window);

    feedback.draw(window);

    if (draw_mouse_coords)
    {
      sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
      sf::Vector2f mouse_pos_coords = window.mapPixelToCoords(mouse_pos);

      sf::RectangleShape rect;
      rect.setFillColor(sf::Color::Yellow);
      rect.setSize({ 12, 12 });
      rect.setPosition(mouse_pos_coords);
      window.draw(rect);

      sf::RectangleShape rect1;
      rect1.setFillColor(sf::Color::Magenta);
      rect1.setSize({ 10, 10 });
      rect1.setPosition(static_cast<sf::Vector2f>(mouse_pos));
      window.draw(rect1);
    }

  }
}

void Game::mouseClicked(sf::Event event)
{
  sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
  sf::Vector2f mouse_pos_coords = window.mapPixelToCoords(mouse_pos);

  std::cout << passport_object->getCanBeDragged() << std::endl;

  if (event.mouseButton.button == sf::Mouse::Left)
  {
    if (passport_object->getPassportBounds().contains(mouse_pos_coords)
      && passport_object->getCanBeDragged())
    {
      passport_drag = passport_object.get();
    }
    if (passport_stamp_visible)
    {
      passport_stamp->onMouseClick();
    }
  }
  else if (event.mouseButton.button == sf::Mouse::Right)
  {
    if (passport_object->getPassportState() == PassportState::OPEN)
    {
      passport_stamp_visible = !passport_stamp->getVisible();
      passport_stamp->showStampUI(passport_stamp_visible, mouse_pos_coords,
        game_view.getSize());
      passport_stamp->setPassport(passport_object.get());

    }

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
      sf::Vector2f pos = {100.f, 100.f};
      passport_object->resetPassport(pos);
      passport_object->initPassport(*character_data);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
      feedback.startFeedback(correct_feedback);
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      feedback.startFeedback(incorrect_feedback);
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

  if (!FontManager::getInstance().loadFont("Passport", "Passport/Passport-Regular.ttf")) {
    std::cerr << "Failed to load Passport font!" << std::endl;
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
  if (!desk_texture.loadFromFile("../Data/Images/Planks/TablePlank.png"))
  {
    std::cout << "Desk texture failed to load!" << std::endl;
    return false;
  }
  desk_sprite.setTexture(desk_texture);
  desk_sprite.setScale(0.5f, 0.5f);
  desk_sprite.setPosition(ScaleTools::getScaledPosition(desk_unscaled_size, background_sprite));

  return true;
}

void Game::dragPassport(Passport* passport)
{
  if (passport != nullptr)
  {
    if (passport_object->getPassportStamp() == PassportStampValue::NONE)
    {
      passport_area.setVisible(true);
    }
    else
    {
      return_area.setVisible(true);
      passport->closePassport();
    }

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    sf::Vector2f mouse_pos_coords = window.mapPixelToCoords(mouse_pos);

    sf::Vector2f drag_pos = sf::Vector2f(
      mouse_pos_coords.x - DRAG_OFFSET,
      mouse_pos_coords.y - DRAG_OFFSET);
    passport->setDragPosition(drag_pos);
  }
  else
  {
    // Passport Handle Area
    if (passport_area.isPassportInArea(passport_object->getPassportPosition())
      && passport_area.getSlotType() == SlotType::PASSPORT
      && passport_object->getPassportStamp() == PassportStampValue::NONE)
    {
      passport_object->setDragPosition(passport_area.getPassportLockPosition());
      passport_object->openPassport();
      passport_object->setCanBeDragged(false);
      passport_area.setVisible(false);
    }

    // Passport Return Area
    //return_area.isPassportInArea(temp_passport->getPassportPosition()
    if (return_area.isPassportInArea(window.mapPixelToCoords(sf::Mouse::getPosition(window)))
      && return_area.getSlotType() == SlotType::RETURN
      && passport_object->getPassportStamp() != PassportStampValue::NONE)
    {
      return_area.setVisible(false);
      passport_object->setCanBeDragged(false);
      passport_object->setVisible(false);
      // createNewCharacter();
    }

  }
}







