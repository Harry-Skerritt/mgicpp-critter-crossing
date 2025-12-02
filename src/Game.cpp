
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

bool Game::init()
{

  loadFonts();
  loadData();
  loadBackground();
  loadSprites();

  // Passport Slots
  setupSlots();

  // Load passport
  sf::Vector2f vec2 = ScaleTools::getScaledSize(passport_main_size_unscaled, background_sprite);
  passport_object = std::make_unique<Passport>(sf::Vector2f(600, 100), vec2);
  passport_object->setDataManager(&passport_data_manager);
  passport_object->setVisible(false);

  // Init character
  character_object = std::make_unique<Character>(
    ScaleTools::getScaledPosition(character_unscaled_pos, background_sprite),
    sf::Vector2f(CHARACTER_WIDTH, (CHARACTER_WIDTH * CHARACTER_HEIGHT_MULTIPLIER)));

  // Passport Stamp
  passport_stamp = std::make_shared<PassportStamp>(this);

  // Feedback
  feedback.init("../Data/Images/FeedbackEffect.png", 0.5f, 0.5f, 0.1f);

  // Progress Counter
  progress_counter.init({0, 0}, &background_sprite);

  // Start Game
  createNewRound();

  return true;
}

void Game::update(float dt)
{
  // Handle Menu
  if (game_state == GameState::MENU)
  {

  }
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

    if (progress_counter.isVisible())
      progress_counter.draw(window);

    feedback.draw(window);

    if (debug_mode)
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

  if (debug_mode)
    std::cout << "Passport Can Move?: " << passport_object->getCanBeDragged() << std::endl;

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && debug_mode)
    {
      // Debug choosing a new character on space
      character_data = std::make_shared<CharacterAssetData>(character_creator.ChooseCharacter());
      sf::Vector2f pos = ScaleTools::getScaledPosition(passport_spawn_pos_unscaled, background_sprite);
      passport_object->resetPassport(pos);
      passport_object->initPassport(*character_data);
      makePassportSmall();
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

void Game::setupSlots() {
  passport_area.init("../Data/Images/Passport/Slots/PassportSlot.png");
  passport_area.setSlotType(SlotType::PASSPORT);
  passport_area.setAreaPosition(passport_area_unscaled_pos, background_sprite);

  return_area.init("../Data/Images/Passport/Slots/ReturnSlot.png");
  return_area.setSlotType(SlotType::RETURN);
  return_area.setAreaPosition(return_area_unscaled_pos, background_sprite);
}

void Game::handleDragAreas(Passport* passport) {
  if (!passport->getPassportStamped())
  {
    // Passport isn't stamped so cannot be returned
    passport_area.setVisible(true);

    if (debug_mode)
      std::cout << "Passport has not been stamped" << std::endl;
  }
  else if (passport->getPassportStamped())
  {
    // Passport is stamped so can be returned
    return_area.setVisible(true);

    passport->closePassport();
    makePassportSmall();
    passport_stamp->setPassport(nullptr);

    if (debug_mode)
      std::cout << "Passport has been stamped" << std::endl;
  }
}

sf::Vector2f Game::getDragPosition() {
  sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
  sf::Vector2f mouse_pos_coords = window.mapPixelToCoords(mouse_pos);

  sf::Vector2f drag_pos = sf::Vector2f(
    mouse_pos_coords.x - DRAG_OFFSET,
    mouse_pos_coords.y - DRAG_OFFSET);

  return drag_pos;
}

void Game::handlePassportDropped() {
  // Passport has been dropped
  if (passport_object->getPassportStamped())
  {
    // If stamped then can only be returned
    if (return_area.isPassportInArea(passport_object.get()))
    {
      // Hide and immobilise passport
      passport_object->setCanBeDragged(false);
      passport_object->setVisible(false);
      return_area.setVisible(false);

      validatePassport(passport_object.get());
    }
  }
  else
  {
    // Not stamped - so cannot be returned
    if (passport_area.isPassportInArea(passport_object.get()))
    {
      // Set the passport to be in the area
      passport_object->setDragPosition(passport_area.getPassportLockPosition());

      makePassportBig();
      passport_object->openPassport();
      passport_object->setCanBeDragged(false);
      passport_area.setVisible(false);
    }
  }
}

void Game::validatePassport(Passport *passport) {
  if (passport_data_manager.getPassportMatching())
  {
    // Passport matches
    if (passport->getPassportStamp() == PassportStampValue::APPROVE)
    {
      // Correct
      feedback.startFeedback(correct_feedback);
      rounds_correct++;
    }
    else if (passport->getPassportStamp() == PassportStampValue::REJECT)
    {
      // Incorrect
      feedback.startFeedback(incorrect_feedback);
    }
  }
  else
  {
    // Passport does not match
    if (passport->getPassportStamp() == PassportStampValue::APPROVE)
    {
      // Incorrect
      feedback.startFeedback(incorrect_feedback);
    }
    else if (passport->getPassportStamp() == PassportStampValue::REJECT)
    {
      // Correct
      feedback.startFeedback(correct_feedback);
      rounds_correct++;
    }
  }

  createNewRound();
}

void Game::dragPassport(Passport* passport)
{
  if (passport != nullptr)
  {
    // - Passport is being dragged -

    // Visuals of drag areas
    handleDragAreas(passport);

    // Moving the passport
    passport->setDragPosition(getDragPosition());
  }
  else
  {
    // - Passport isn't being dragged -
    handlePassportDropped();
  }
}

void Game::makePassportBig() {
  passport_object->setSize(ScaleTools::getScaledSize(passport_main_size_unscaled, background_sprite));
  passport_object->setZoom(1.f);
}

void Game::makePassportSmall() {
  passport_object->setSize(ScaleTools::getScaledSize(passport_spawn_size_unscaled, background_sprite));
  passport_object->setZoom(2.f);
}

bool Game::decideIfMatch() const {
    bool match = (static_cast<float>(rand()) / RAND_MAX) < MATCH_PROBABILITY;

    if (debug_mode)
      std::cout << "Match: " << match << std::endl;

    return match;
}

void Game::createNewRound() {
  if (debug_mode)
    std::cout << "Creating new round..." << std::endl;

  // Reset Passport
  sf::Vector2f pos = ScaleTools::getScaledPosition(passport_spawn_pos_unscaled, background_sprite);
  passport_object->resetPassport(pos);
  passport_object->setPassportStamp(PassportStampValue::NONE);
  passport_object->resetPassportStamped();
  makePassportSmall();
  passport_drag = nullptr;

  if (debug_mode)
    std::cout << "Stamp Value: " << passport_object->getPassportStampValue() << std::endl;


  // Choose if matching
  passport_data_manager.setPassportMatching(decideIfMatch());

  // Generate character
  character_data = std::make_shared<CharacterAssetData>(character_creator.ChooseCharacter());

  if (passport_data_manager.getPassportMatching())
  {
    if (debug_mode)
      std::cout << "Passport matching" << std::endl;

    // They match so pass to passport
    passport_character_data = character_data;
  }
  else
  {
    if (debug_mode)
      std::cout << "Passport not matching" << std::endl;

    // Don't match so generate another for passport
    passport_character_data = std::make_shared<CharacterAssetData>(character_creator.ChooseCharacter()); // Todo: Move to a new func to ensure its not the same
  }

  // Send data to passport
  passport_object->initPassport(*passport_character_data);

  // Update Trackers
  progress_counter.updateCount(rounds_correct, rounds_played);
  rounds_played++;

}








