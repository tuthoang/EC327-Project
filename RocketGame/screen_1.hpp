#ifndef SCREEN_1_HPP
#define SCREEN_1_HPP

#include "ResourcePath.hpp"
#include <iostream>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



class screen_1 : public cScreen
{
private:
    
public:
    virtual int Run(sf::RenderWindow &App);
};


int screen_1::Run(sf::RenderWindow &window)
{
    // Create the main window
    //sf::RenderWindow window(sf::VideoMode(1000, 800), "Rocketship Game");
    window.setFramerateLimit(60);
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load a sprite to display
    sf::Texture textureRocketship;
    if (!textureRocketship.loadFromFile(resourcePath() + "spritesheetRocket.png")) {
        return EXIT_FAILURE;
    }
    sf::Texture textureMissile;
    if (!textureMissile.loadFromFile(resourcePath() + "Missile.png")) {
        return EXIT_FAILURE;
    }
    sf::Texture textureMonsters;
    if (!textureMonsters.loadFromFile(resourcePath() + "monster-lizard.png")) {
        return EXIT_FAILURE;
    }
    textureMonsters.setSmooth(true);
    sf::Texture textureYoshi;
    if (!textureYoshi.loadFromFile(resourcePath() + "YoshiTransp.png"))
        return EXIT_FAILURE;
    textureYoshi.setSmooth(true);
    
    sf::Texture starMissle;
    if (!starMissle.loadFromFile(resourcePath() + "starSprite.png"))
        return EXIT_FAILURE;
    starMissle.setSmooth(true);
    
    sf::Texture texturePowerup;
    if (!texturePowerup.loadFromFile(resourcePath() + "powerup.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture nyanCatTexture;
    if (!nyanCatTexture.loadFromFile(resourcePath() + "nyan-cat.png")) {
        return EXIT_FAILURE;
    }
    nyanCatTexture.setSmooth(true);
    
    sf::Texture clouds;
    if (!clouds.loadFromFile(resourcePath() + "cloud.png"))
    {
        return EXIT_FAILURE;
    }
    
    sf::Texture spaceTexture;
    if (!spaceTexture.loadFromFile(resourcePath() + "space.jpg"))
    {
        return EXIT_FAILURE;
    }
    
    sf::Texture forestTexture;
    if (!forestTexture.loadFromFile(resourcePath() + "forests.png"))
    {
        return EXIT_FAILURE;
    }
    
    sf::Texture textureBoss;
    if (!textureBoss.loadFromFile(resourcePath() + "boss.jpg")) {
        return EXIT_FAILURE;
    }
    
    sf::Texture textureEnergyBall;
    if (!textureEnergyBall.loadFromFile(resourcePath() + "energy_ball.png")) {
        return EXIT_FAILURE;
    }
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text textHP;
    textHP.setFont(font);
    textHP.setCharacterSize(50);
    textHP.setColor(sf::Color::White);
    textHP.setPosition(0, 0);
    
    sf::Text textDamage;
    textDamage.setFont(font);
    textDamage.setCharacterSize(25);
    textDamage.setColor(sf::Color::Red);
    vector<sf::Text> textDamageVector;
    
    sf::Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(50);
    textScore.setColor(sf::Color::White);
    textScore.setPosition(window.getSize().x / 2, 0);
    
    sf::Text textLevel;
    textLevel.setFont(font);
    textLevel.setCharacterSize(50);
    textLevel.setColor(sf::Color::White);
    textLevel.setPosition(0, 50);
    
    sf::Text textLevelFlash;
    textLevelFlash.setFont(font);
    textLevelFlash.setCharacterSize(200);
    textLevelFlash.setColor(sf::Color::Red);
    textLevelFlash.setPosition(300, 250);
    
    sf::Text textBossDamage;
    textBossDamage.setFont(font);
    textBossDamage.setCharacterSize(50);
    textBossDamage.setColor(sf::Color::Green);
    vector<sf::Text> textBossHealthBarVector;
    
    sf::Text textPowerup;
    textPowerup.setFont(font);
    textPowerup.setCharacterSize(50);
    textPowerup.setColor(sf::Color::Green);
    textPowerup.setString("Doubleshot -> 5s");
    textPowerup.setPosition(0, window.getSize().y / 2);
    vector<sf::Text> textPowerupVector;
    
    //sounds
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(resourcePath() + "shootingSound.wav"))
        return EXIT_FAILURE;
    sf::Sound shooting;
    shooting.setBuffer(buffer);
    
    sf::Music nyanCatSong;
    if (!nyanCatSong.openFromFile("Nyan_Cat.ogg"))
        return EXIT_FAILURE;
    
    sf::Music marioBros;
    if (!marioBros.openFromFile("SuperMarioBros.ogg"))
        return EXIT_FAILURE;
    
    sf::Music dinoMusic;
    if(!dinoMusic.openFromFile(resourcePath()+"epic_dionsaur_piano_song.wav" ))
        return EXIT_FAILURE;
    sf::Music bossBattleMusic;
    if(!bossBattleMusic.openFromFile(resourcePath()+"epic_boss_battle_music.wav"))
        return EXIT_FAILURE;
    sf::Clock countdownClock;
    sf::Clock missileClock;
    sf::Clock monsterClock;
    sf::Clock damageClock;
    sf::Clock levelClock;
    sf::Clock killClock;
    sf::Clock moveDino;
    sf::Clock powerupClock;
    sf::Clock rocketDamage;
    sf::Clock energyBallClock;
    bool step = true;
    bool doubleshot = false;
    
    //create the missiles
    vector<Missile> missileVector;
    vector<Missile> missileVector2;
    vector<Missile> monster_missileVector;
    Missile missiles;
    Missile missiles2;
    Missile star("star");
    Missile monster_missile;
    missiles.sprite.setTexture(textureMissile);
    missiles2.sprite.setTexture(textureMissile);
    monster_missile.sprite.setTexture(textureMissile);
    star.sprite.setTexture(starMissle);
    
    //create the enery ball fired by boss in the middle
    vector<Missile> energyBallMiddleVector;
    Missile energyBallMiddle;
    energyBallMiddle.sprite.setTexture(textureEnergyBall);
    energyBallMiddle.sprite.setTextureRect((sf::IntRect(336, 144, 50, 50)));
    //create the enery ball fired by the boss on the right
    vector<Missile> energyBallRightVector;
    Missile energyBallRight;
    energyBallRight.sprite.setTexture(textureEnergyBall);
    energyBallRight.sprite.setTextureRect((sf::IntRect(336, 144, 50, 50)));
    
    Powerup powerup;
    vector <Powerup> powerupVector;
    powerup.sprite.setTexture(texturePowerup);
    
    //create rocket
    class Rocketship rocketship;
    rocketship.sprite.setTexture(textureRocketship);
    
    //create monsters
    class Monsters yoshi("Yoshi");
    class Monsters nyanCat("nyanCat");
    class Monsters monster;
    
    sf::IntRect rectSourceSprite(28, 230, 23, 49);
    monster.sprite.setTextureRect(rectSourceSprite);
    //---------------------------------------------
    sf::IntRect rectSourceYoshi(86, 40, 23, 49);
    yoshi.sprite.setTextureRect(rectSourceYoshi);
    //---------------------------------------------
    sf::IntRect rectSourceNyan(5, 0, 98, 60);
    nyanCat.sprite.setTextureRect(rectSourceNyan);
    
    nyanCat.sprite.setTexture(nyanCatTexture);
    yoshi.sprite.setTexture(textureYoshi);
    monster.sprite.setTexture(textureMonsters);
    
    vector<Monsters> monsterVector;
    vector<Monsters> bossVector;
    
    // Create Boss
    Monsters boss("boss");
    bossVector.push_back(boss);
    bossVector[0].sprite.setTexture(textureBoss);
    //boss.rect.setSize(sf::Vector2f(175, 135)); // may need to change later for collisions. sizes change cause each sprite is differnet size
    //boss.sprite.setTextureRect(sf::IntRect(360, 600, 175, 135));         //Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight)
    
    //boss.health = 40;
    
    int leftMiddleRightFire = 0; //counter to create shotting pattern for boss
    
    int deadCount = 0;
    int score = 0;
    int level = 1;
    int monsterCount = 0;
    bool play=true;
    
    ////////////////////////////
    if (level != 4)
    {
        bossVector[0].sprite.setPosition(-1000, 0);
    }
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return 0;
            }
        }
        
        // Clear screen
        window.clear();
        
        if (level == 1)
        {
            sf::Sprite space(spaceTexture);
            space.scale(2,1.3);
            
            window.draw(space);
        }
        if (level == 2)
        {
            sf::Sprite forest(forestTexture);
            forest.scale(1.25, 1);
            window.draw(forest);
        }
        if (level == 3) {
            sf::Sprite NyanBackground(clouds);
            NyanBackground.scale(2.5,2.5);
            window.draw(NyanBackground);
        }
        if(level==1 && play==true){
            dinoMusic.play();
            play=false;
        }
        else if(level==4){
            bossBattleMusic.setLoop(true);
        }
        //window.clear(sf::Color::White);
        
        int missileIterator = 0;
        int missileIterator2 = 0;
        int monster_missileIterator = 0;
        int monsterIterator = 0;
        int textureIterator = 0;
        int powerupIterator = 0;
        int textIterator = 0;
        int textPowerupIterator = 0;
        int energyBallMiddleIterator = 0;
        int energyBallRightIterator = 0;
        
        
        //Spacebar = shoot missiles every 100mS
        if (doubleshot == false) {
            if (missileClock.getElapsedTime().asMilliseconds() > 300) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    shooting.stop();
                    shooting.play();
                    if (level == 1 || level == 2 || level == 4)
                    {
                        missiles.rect.setPosition(rocketship.rect.getPosition().x + rocketship.rect.getSize().x / 2 - missiles.rect.getSize().x / 2, rocketship.rect.getPosition().y - missiles.rect.getSize().y / 2);
                        missileVector.push_back(missiles);
                    }
                    else if (level == 3) {
                        star.rect.setPosition(rocketship.rect.getPosition().x + rocketship.rect.getSize().x / 2 - star.rect.getSize().x / 2, rocketship.rect.getPosition().y - star.rect.getSize().y / 2);
                        missileVector.push_back(star);
                    }
                }
                missileClock.restart();
            }
            //draw the missiles.
            
            for (missileIterator = 0; missileIterator < missileVector.size(); missileIterator++) {
                missileVector[missileIterator].update();
                window.draw(missileVector[missileIterator].sprite);
                if (missileVector[missileIterator].hit == true)
                    missileVector.erase(missileVector.begin() + missileIterator);
            }
            
        }
        if (doubleshot == true) {
            if (missileClock.getElapsedTime().asMilliseconds() > 300) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    shooting.stop();
                    shooting.play();
                    missiles.rect.setPosition(rocketship.rect.getPosition().x + rocketship.rect.getSize().x / 3 - missiles.rect.getSize().x / 2, rocketship.rect.getPosition().y - missiles.rect.getSize().y / 2);
                    missileVector.push_back(missiles);
                    missiles2.rect.setPosition(rocketship.rect.getPosition().x + 2 * rocketship.rect.getSize().x / 3 - missiles2.rect.getSize().x / 2, rocketship.rect.getPosition().y - missiles2.rect.getSize().y / 2);
                    missileVector2.push_back(missiles2);
                }
                missileClock.restart();
            }
            for (missileIterator = 0; missileIterator < missileVector.size(); missileIterator++) {
                missileVector[missileIterator].update();
                window.draw(missileVector[missileIterator].sprite);
                if (missileVector[missileIterator].hit == true)
                    missileVector.erase(missileVector.begin() + missileIterator);
                
            }
            for (missileIterator2 = 0; missileIterator2 < missileVector2.size(); missileIterator2++) {
                missileVector2[missileIterator2].update();
                window.draw(missileVector2[missileIterator2].sprite);
                if (missileVector2[missileIterator2].hit == true)
                    missileVector2.erase(missileVector2.begin() + missileIterator2);
                
            }
        }
        
        //draw the energy ball middle.
        for (energyBallMiddleIterator = 0; energyBallMiddleIterator < energyBallMiddleVector.size(); energyBallMiddleIterator++) {
            energyBallMiddleVector[energyBallMiddleIterator].update(0, energyBallMiddleVector[energyBallMiddleIterator].misslespeed);
            window.draw(energyBallMiddleVector[energyBallMiddleIterator].sprite);
            if (energyBallMiddleVector[energyBallMiddleIterator].hit == true)
                energyBallMiddleVector.erase(energyBallMiddleVector.begin() + energyBallMiddleIterator);
        }
        
        //Set energy ball middle rate of firing
        if (energyBallClock.getElapsedTime().asMilliseconds() > 250 && level == 4) {
            energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x / 2, bossVector[0].rect.getPosition().y + energyBallMiddle.rect.getSize().y / 2);
            if (bossVector[0].health < 30 && bossVector[0].health > 20) {
                textBossDamage.setColor(sf::Color::Yellow);
                if (leftMiddleRightFire == 0) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + (-(bossVector[0].rect.getSize().x / 2) / 2), bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 1;
                }
                else if (leftMiddleRightFire == 1) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x + ((bossVector[0].rect.getSize().x / 2) / 2), bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 2;
                }
                else if (leftMiddleRightFire == 2) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x / 2, bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 0;
                }
            }
            
            else if (bossVector[0].health <= 20) {
                textBossDamage.setColor(sf::Color::Red);
                //
                //left
                if (leftMiddleRightFire == 0) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + (-(bossVector[0].rect.getSize().x / 2) / 2), bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 1;
                }
                //right
                else if (leftMiddleRightFire == 1) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x + ((bossVector[0].rect.getSize().x / 2) / 2), bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 2;
                }
                //middle
                else if (leftMiddleRightFire == 2) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x / 2, bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 3;
                }
                else if (leftMiddleRightFire == 3) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + (-(bossVector[0].rect.getSize().x / 2) / 2) + 75, bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 4;
                }
                else if (leftMiddleRightFire == 4) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x / 2, bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 5;
                }
                else if (leftMiddleRightFire == 5) {
                    energyBallMiddle.rect.setPosition(bossVector[0].rect.getPosition().x + bossVector[0].rect.getSize().x + ((bossVector[0].rect.getSize().x / 2) / 2) - 75, bossVector[0].rect.getPosition().y + bossVector[0].rect.getSize().y / 2);
                    leftMiddleRightFire = 0;
                }
                
                
            }
            energyBallMiddleVector.push_back(energyBallMiddle);
            energyBallClock.restart();
        }
        
        //spawn monster every 2 seconds
        if (level == 1) {
            if (monsterClock.getElapsedTime().asSeconds() > 2) {
                monster.rect.setPosition(rand() % window.getSize().x + 1, 0);
                
                monsterVector.push_back(monster);
                monsterCount++;
                monsterClock.restart();
            }
        }
        else if (level == 2) {
            if (monsterClock.getElapsedTime().asSeconds() > 2) {
                yoshi.rect.setPosition(rand() % window.getSize().x + 1, 0);
                monsterVector.push_back(yoshi);
                monsterClock.restart();
            }
        }
        else if (level == 3)
        {
            if (monsterClock.getElapsedTime().asSeconds() > 2) {
                nyanCat.rect.setPosition(0, rand() % (window.getSize().y - 230));
                monsterVector.push_back(nyanCat);
                monsterClock.restart();
            }
        }
        
        //level up
        if (score == 5 && level == 1) {
            level = 2;
            window.clear();
            monsterClock.restart();
            textLevelFlash.setString("Level " + to_string(level));
            window.draw(textLevelFlash);
            window.display();
            while (monsterClock.getElapsedTime().asSeconds() < 2)
            {
                //wait
            }
            window.clear();
            monsterVector.clear();
            missileVector.clear();
            marioBros.play();
            //window.display();
        }
        else if (score >= 20 && level == 2)
        {
            level = 3;
            sf::Color pink{ 255,192,203 };
            marioBros.stop();
            monsterClock.restart();
            window.clear(pink);
            textLevelFlash.setString("Level " + to_string(level));
            window.draw(textLevelFlash);
            window.display();
            while (monsterClock.getElapsedTime().asSeconds() < 2)
            {
                //wait
            }
            missileVector.clear();
            monsterVector.clear();
            textHP.setColor(pink);
            textLevel.setColor(pink);
            textScore.setColor(pink);
            nyanCatSong.play();
            
        }
        else if (score >= 35 && level == 3)
        {
            level = 4;
            window.clear();
            nyanCatSong.stop();
            monsterClock.restart();
            textLevelFlash.setString("Level " + to_string(level));
            window.draw(textLevelFlash);
            window.display();
            while (monsterClock.getElapsedTime().asSeconds() < 2)
            {
                //wait
            }
            window.clear();
            monsterVector.clear();
            missileVector.clear();
            bossBattleMusic.play();
            //window.display();
        }
        
        //   cout<< "   " << monsterCount<<endl;
        textLevelFlash.setString("Level " + to_string(level));
        levelClock.restart();
        
        //move monster
        if (level == 1)
        {
            if (moveDino.getElapsedTime().asMilliseconds() > 60)
            {
                if (rectSourceSprite.left == 428)
                {
                    rectSourceSprite.left = 28;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        if (monsterVector[monsterIterator].health <= 0) {
                            monsterVector[monsterIterator].sprite.setTextureRect(sf::IntRect(413, 420, 50, 22));
                            window.draw(monsterVector[monsterIterator].sprite);
                        }
                        else {
                            monsterVector[monsterIterator].sprite.setTextureRect(rectSourceSprite);
                            window.draw(monsterVector[monsterIterator].sprite);
                        }
                    }
                }
                else
                {
                    rectSourceSprite.left += 80;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        if (monsterVector[monsterIterator].health <= 0) {
                            monsterVector[monsterIterator].sprite.setTextureRect(sf::IntRect(413, 420, 50, 22));
                            window.draw(monsterVector[monsterIterator].sprite);
                        }
                        else {
                            monsterVector[monsterIterator].sprite.setTextureRect(rectSourceSprite);
                            window.draw(monsterVector[monsterIterator].sprite);
                        }
                    }
                }
                moveDino.restart();
            }
        }
        else if (level == 2)
        {
            if (moveDino.getElapsedTime().asMilliseconds() > 70)
            {
                if (rectSourceYoshi.left == 32)
                {
                    step = true;
                    rectSourceYoshi.left = 86;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        monsterVector[monsterIterator].sprite.setTextureRect(rectSourceYoshi);
                        window.draw(monsterVector[monsterIterator].sprite);
                    }
                }
                else if (rectSourceYoshi.left == 140)
                {
                    step = false;
                    rectSourceYoshi.left = 86;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        monsterVector[monsterIterator].sprite.setTextureRect(rectSourceYoshi);
                        window.draw(monsterVector[monsterIterator].sprite);
                    }
                }
                else if (step == true)
                {
                    rectSourceYoshi.left += 27;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        monsterVector[monsterIterator].sprite.setTextureRect(rectSourceYoshi);
                        window.draw(monsterVector[monsterIterator].sprite);
                    }
                }
                else {
                    rectSourceYoshi.left -= 27;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        monsterVector[monsterIterator].sprite.setTextureRect(rectSourceYoshi);
                        window.draw(monsterVector[monsterIterator].sprite);
                    }
                }
                
                moveDino.restart();
            }
        }
        else if (level == 3)
        {
            if (moveDino.getElapsedTime().asMilliseconds() > 60)
            {
                if (rectSourceNyan.left != 495)
                {
                    rectSourceNyan.left += 98;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        monsterVector[monsterIterator].sprite.setTextureRect(rectSourceNyan);
                        window.draw(monsterVector[monsterIterator].sprite);
                    }
                }
                else
                {
                    rectSourceNyan.left = 5;
                    for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
                    {
                        monsterVector[monsterIterator].sprite.setTextureRect(rectSourceNyan);
                        window.draw(monsterVector[monsterIterator].sprite);
                    }
                    
                }
                moveDino.restart();
            }
        }
        else if (level == 4)
        {
            textBossDamage.setString("Boss Health: " + to_string(bossVector[0].health));
            textBossDamage.setPosition(bossVector[0].rect.getPosition().x - 65, bossVector[0].rect.getPosition().y + 135);
            window.draw(textBossDamage);
            
            window.draw(bossVector[0].sprite);
            if (bossVector[0].canMoveRight == true && bossVector[0].canMoveLeft == false) {
                bossVector[0].update(bossVector[0].speed, 0);
                window.draw(bossVector[0].sprite);
                //        window.draw(boss.rect);
            }
            if (bossVector[0].canMoveRight == false && bossVector[0].canMoveLeft == true) {
                bossVector[0].update(-(bossVector[0].speed), 0);
                window.draw(bossVector[0].sprite);
                //       window.draw(boss.rect);
            }
            
            int counter2 = 0;
            if (bossVector[0].rect.getPosition().x > window.getSize().x - 175) {
                bossVector[0].canMoveRight = false;
                bossVector[0].canMoveLeft = true;
            }
            if (bossVector[0].rect.getPosition().x < 0) {
                bossVector[0].canMoveRight = true;
                bossVector[0].canMoveLeft = false;
            }
        }
        
        //draw the monsters
        for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++) {
            if (level == 1 || level == 2) {
                monsterVector[monsterIterator].update();
            }
            else if (level == 3)
                monsterVector[monsterIterator].update(monsterVector[monsterIterator].speed, 0);
            
            window.draw(monsterVector[monsterIterator].sprite);
            
            if (monsterVector[monsterIterator].health <= 0) {
                
                monsterVector[monsterIterator].dead();
                killClock.restart();
                
                deadCount++;
                if (deadCount == 20) {
                    monsterVector.erase(monsterVector.begin() + monsterIterator);
                    deadCount = 0;
                    if (level == 1) {
                        score++;
                    }
                    else if (level == 2)
                    {
                        score += 3;
                    }
                    else if (level == 3)
                        score += 5;
                }
            }
        }
        for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
        {
            if (monsterVector[monsterIterator].rect.getGlobalBounds().intersects(rocketship.rect.getGlobalBounds())) {
                if (rocketship.health > 0) {
                    rocketship.health--;
                }
                else
                    rocketship.health = 0;
                monsterVector.erase(monsterVector.begin() + monsterIterator);
                rocketship.sprite.setColor(sf::Color::Red);
                rocketDamage.restart();
            }
            if (rocketDamage.getElapsedTime().asMilliseconds() > 80)
            {
                rocketship.sprite.setColor(sf::Color::White);
            }
        }
        
        
        //when missile.rect collides with monster.rect, decrement the health of the monster
        //and delete the missile
        for (missileIterator = 0; missileIterator < missileVector.size(); missileIterator++) {
            for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++) {
                if (missileVector[missileIterator].rect.getGlobalBounds().intersects(monsterVector[monsterIterator].rect.getGlobalBounds())) {
                    damageClock.restart();
                    monsterVector[monsterIterator].health -= missileVector[missileIterator].damage;
                    textDamage.setString(to_string(missileVector[missileIterator].damage));
                    textDamage.setPosition(monsterVector[monsterIterator].rect.getPosition().x + 10, monsterVector[monsterIterator].rect.getPosition().y);
                    textDamageVector.push_back(textDamage);
                    missileVector[missileIterator].hit = true;
                }
                if (level == 2)
                {
                    if (monsterVector[monsterIterator].health == 2)
                    {
                        sf::Color lightRed{ 255,102,102 };
                        monsterVector[monsterIterator].sprite.setColor(lightRed);
                    }
                    else if (monsterVector[monsterIterator].health == 1)
                    {
                        monsterVector[monsterIterator].sprite.setColor(sf::Color::Red);
                    }
                }
            }
        }
        for (missileIterator2 = 0; missileIterator2<missileVector2.size(); missileIterator2++) {
            for (monsterIterator = 0; monsterIterator<monsterVector.size(); monsterIterator++) {
                if (missileVector2[missileIterator2].rect.getGlobalBounds().intersects(monsterVector[monsterIterator].rect.getGlobalBounds())) {
                    damageClock.restart();
                    monsterVector[monsterIterator].health -= missileVector2[missileIterator2].damage;
                    textDamage.setString(to_string(missileVector2[missileIterator2].damage));
                    textDamage.setPosition(monsterVector[monsterIterator].rect.getPosition().x + 40, monsterVector[monsterIterator].rect.getPosition().y);
                    textDamageVector.push_back(textDamage);
                    missileVector2[missileIterator2].hit = true;
                }
                if (level == 2)
                {
                    if (monsterVector[monsterIterator].health == 2)
                    {
                        sf::Color lightRed{ 255,102,102 };
                        monsterVector[monsterIterator].sprite.setColor(lightRed);
                    }
                    else if (monsterVector[monsterIterator].health == 1)
                    {
                        monsterVector[monsterIterator].sprite.setColor(sf::Color::Red);
                    }
                }
            }
        }
        
        //when missile.rect collides with boss.rect, decrement the health of the boss
        //and delete the missile
        for (missileIterator = 0; missileIterator < missileVector.size(); missileIterator++) {
            if (missileVector[missileIterator].rect.getGlobalBounds().intersects(bossVector[0].rect.getGlobalBounds())) {
                damageClock.restart();
                
                bossVector[0].health -= missileVector[missileIterator].damage;
                
                textBossDamage.setString("Health: " + to_string(missileVector[missileIterator].damage));
                textBossHealthBarVector.push_back(textBossDamage);
                missileVector[missileIterator].hit = true;
            }
        }
        for (missileIterator2 = 0; missileIterator2 < missileVector2.size(); missileIterator2++) {
            if (missileVector2[missileIterator2].rect.getGlobalBounds().intersects(bossVector[0].rect.getGlobalBounds())) {
                damageClock.restart();
                
                bossVector[0].health -= missileVector[missileIterator].damage;
                
                textBossDamage.setString("Health: " + to_string(missileVector2[missileIterator2].damage));
                textBossHealthBarVector.push_back(textBossDamage);
                missileVector2[missileIterator2].hit = true;
            }
        }
        
        //decrement the rocketship's health, when it's hit with an energy ball middle
        
        for (energyBallMiddleIterator = 0; energyBallMiddleIterator < energyBallMiddleVector.size(); energyBallMiddleIterator++) {
            if (energyBallMiddleVector[energyBallMiddleIterator].rect.getGlobalBounds().intersects(rocketship.rect.getGlobalBounds())) {
                rocketship.health--;
                energyBallMiddleVector.erase(energyBallMiddleVector.begin() + energyBallMiddleIterator);
            }
        }
        
        //decrement the rocketship's health, when it's hit with an energy ball righte
        
        for (energyBallRightIterator = 0; energyBallRightIterator < energyBallRightVector.size(); energyBallRightIterator++) {
            if (energyBallRightVector[energyBallRightIterator].rect.getGlobalBounds().intersects(rocketship.rect.getGlobalBounds())) {
                rocketship.health--;
                energyBallRightVector.erase(energyBallRightVector.begin() + energyBallRightIterator);
            }
        }
        
        
        //powerup
        if (powerupClock.getElapsedTime().asSeconds() >= 20)
        {
            powerupVector.push_back(powerup);
            powerupClock.restart();
        }
        //draw powerup
        for (powerupIterator = 0; powerupIterator < powerupVector.size(); powerupIterator++) {
            powerupVector[powerupIterator].update();
            window.draw(powerupVector[powerupIterator].sprite);
        }
        
        //missle + powerup collision
        
        
        for (missileIterator = 0; missileIterator < missileVector.size(); missileIterator++) {
            for (powerupIterator = 0; powerupIterator < powerupVector.size(); powerupIterator++) {
                if (missileVector[missileIterator].rect.getGlobalBounds().intersects(powerupVector[powerupIterator].rect.getGlobalBounds())) {
                    powerupVector.erase(powerupVector.begin() + powerupIterator);
                    missileVector[missileIterator].hit = true;
                    doubleshot = true;
                    powerupClock.restart();
                }
            }
        }
        
        if (doubleshot == true) {
            if (powerupClock.getElapsedTime().asSeconds() >= 5)
                doubleshot = false;
        }
        if(rocketship.health==2){
            sf::Color lightRed{ 255,102,102 };
            rocketship.sprite.setColor(lightRed);
        }
        if(rocketship.health==1)
            rocketship.sprite.setColor(sf::Color::Red);
        //rocketship dies when its health is 0
        //we can move it off the screen to make it "disappear"
        if (rocketship.health <= 0) {

            return 3;
        }
        
        if (bossVector[0].health <= 0) {
            
            bossVector[0].dead();
            bossVector[0].rect.setPosition(0, 0);
            killClock.restart();
        }
        
        if(rocketship.rect.getPosition().x<=0)
        {
            rocketship.rect.setPosition(0, rocketship.rect.getPosition().y);
        }
        if(rocketship.rect.getPosition().x>=window.getSize().x-75)
        {
            rocketship.rect.setPosition(window.getSize().x-75, rocketship.rect.getPosition().y);
        }
        if(rocketship.rect.getPosition().y<=window.getSize().y/2)
        {
            rocketship.rect.setPosition(rocketship.rect.getPosition().x, window.getSize().y/2);
        }
        if(rocketship.rect.getPosition().y>=window.getSize().y-100)
        {
            rocketship.rect.setPosition(rocketship.rect.getPosition().x, window.getSize().y-100);
        }
        rocketship.updateSpeed();
        
        rocketship.update();
        // Draw the Rocket sprite
        window.draw(rocketship.sprite);
        //        window.draw(missiles.sprite);
        //window.draw(boss.rect);
        
        textHP.setString("HP: " + to_string(rocketship.health));
        textScore.setString("Score: " + to_string(score));
        
        window.draw(textHP);
        window.draw(textScore);
        window.draw(textLevel);
        textLevel.setString("Level: " + to_string(level));
        window.draw(textLevel);
        
        for (textIterator = 0; textIterator < textDamageVector.size(); textIterator++) {
            window.draw(textDamageVector[textIterator]);
            if (damageClock.getElapsedTime().asMilliseconds() > 100)
            {
                textDamageVector.erase(textDamageVector.begin() + textIterator);
                damageClock.restart();
            }
        }
        for (textPowerupIterator = 0; textPowerupIterator < textPowerupVector.size(); textPowerupIterator++) {
            window.draw(textPowerupVector[textPowerupIterator]);
            if (powerupClock.getElapsedTime().asSeconds() > 1)
            {
                textPowerupVector.erase(textPowerupVector.begin() + textPowerupIterator);
                damageClock.restart();
            }
        }
        
        //delete missiles and monsters when they leave screen
        if (level == 1 || level == 2)
        {
            for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
            {
                if (monsterVector[monsterIterator].rect.getPosition().y > window.getSize().y)
                {
                    monsterVector.erase(monsterVector.begin() + monsterIterator);
                    rocketship.health--;
                }
            }
        }
        else if (level == 3)
        {
            for (monsterIterator = 0; monsterIterator < monsterVector.size(); monsterIterator++)
            {
                if (monsterVector[monsterIterator].rect.getPosition().x > window.getSize().x)
                {
                    monsterVector.erase(monsterVector.begin() + monsterIterator);
                    rocketship.health--;
                }
            }
        }
        for (missileIterator = 0; missileIterator < missileVector.size(); missileIterator++)
        {
            if (missileVector[missileIterator].rect.getPosition().y < -100)
            {
                missileVector.erase(missileVector.begin() + missileIterator);
            }
        }
        for (missileIterator2 = 0; missileIterator2 < missileVector2.size(); missileIterator2++)
        {
            if (missileVector2[missileIterator2].rect.getPosition().y < -100)
            {
                missileVector2.erase(missileVector2.begin() + missileIterator2);
            }
        }
        
        if (bossVector[0].health <= 0)
        {
            
            return 4;
        }
        // Update the window
        window.display();
    }
    return -1;
}

#endif
