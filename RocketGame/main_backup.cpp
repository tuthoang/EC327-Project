
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Rocketship.hpp"
#include "entity.hpp"
#include "Monsters.hpp"
#include "Missile.hpp"
#include "Powerup.hpp"
#include <string>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Rocketship Game");
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
    sf::Texture textureMonsters1;
    if (!textureMonsters1.loadFromFile(resourcePath() + "monster-lizard.png")) {
        return EXIT_FAILURE;
    }

    sf::Texture textureMonsters2;
    if (!textureMonsters2.loadFromFile(resourcePath() + "alien.png")) {
        return EXIT_FAILURE;
    }
    sf::Texture texturePowerup;
    if(!texturePowerup.loadFromFile(resourcePath()+"powerup.png")){
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
    textHP.setPosition(0,0);
    
    sf::Text textDamage;
    textDamage.setFont(font);
    textDamage.setCharacterSize(25);
    textDamage.setColor(sf::Color::Red);
    vector<sf::Text> textDamageVector;
    
    sf::Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(50);
    textScore.setColor(sf::Color::White);
    textScore.setPosition(window.getSize().x/2, 0);
    
    sf::Text textLevel;
    textLevel.setFont(font);
    textLevel.setCharacterSize(50);
    textLevel.setColor(sf::Color::White);
    textLevel.setPosition(0,50);

    
    sf::Clock missileClock;
    sf::Clock monsterClock;
    sf::Clock damageClock;
    sf::Clock levelClock;
    sf::Clock killClock;
    sf::Clock powerupClock;
    
    //create rocket
    Rocketship rocketship;
    rocketship.sprite.setTexture(textureRocketship);
    
    //create monsters
    Monsters monster;
    monster.sprite.setTexture(textureMonsters1);
    vector<Monsters> monsterVector;

    //create the missiles
    vector<Missile> missileVector;
    vector<Missile> missileVector2;
    vector<Missile> monster_missileVector;
    Missile missiles;
    Missile missiles2;
    Missile monster_missile;
    missiles.sprite.setTexture(textureMissile);
    missiles2.sprite.setTexture(textureMissile);
    monster_missile.sprite.setTexture(textureMissile);
    
    Powerup powerup;
    vector <Powerup> powerupVector;
    powerup.sprite.setTexture(texturePowerup);
    
    int deadCount=0;
    int score = 0;
    int level = 1;
    int monsterCount=0;
    bool doubleshot=true;
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
                window.close();
            }
        }

        // Clear screen
        window.clear();

        int missileIterator=0;
        int missileIterator2=0;
        int monster_missileIterator=0;
        int monsterIterator=0;
        int textureIterator=0;
        int powerupIterator=0;
        int textIterator=0;
        
        //doubleshot is the powerup
        //Spacebar = shoot missiles every 100mS
        if(doubleshot==false){
            if (missileClock.getElapsedTime().asMilliseconds()>100){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    missiles.rect.setPosition(rocketship.rect.getPosition().x+rocketship.rect.getSize().x/2-missiles.rect.getSize().x/2,rocketship.rect.getPosition().y-missiles.rect.getSize().y/2);
                    missileVector.push_back(missiles);
                }
                missileClock.restart();
            }
            //draw the missiles.
            
            for(missileIterator=0; missileIterator<missileVector.size();missileIterator++){
                missileVector[missileIterator].update();
                window.draw(missileVector[missileIterator].sprite);
                if (missileVector[missileIterator].hit==true)
                    missileVector.erase(missileVector.begin()+missileIterator);
            }
        }
        
        if(doubleshot==true){
            if(missileClock.getElapsedTime().asMilliseconds()>100){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    missiles.rect.setPosition(rocketship.rect.getPosition().x+rocketship.rect.getSize().x/3-missiles.rect.getSize().x/2,rocketship.rect.getPosition().y-missiles.rect.getSize().y/2);
                    missileVector.push_back(missiles);
                    missiles2.rect.setPosition(rocketship.rect.getPosition().x+2*rocketship.rect.getSize().x/3-missiles2.rect.getSize().x/2, rocketship.rect.getPosition().y-missiles2.rect.getSize().y/2);
                    missileVector2.push_back(missiles2);
                    
                }
                missileClock.restart();
            }
            for(missileIterator=0; missileIterator<missileVector.size();missileIterator++){
                missileVector[missileIterator].update();
                window.draw(missileVector[missileIterator].sprite);
                if (missileVector[missileIterator].hit==true)
                    missileVector.erase(missileVector.begin()+missileIterator);
                
            }
            for(missileIterator2=0; missileIterator2<missileVector2.size();missileIterator2++){
                missileVector2[missileIterator2].update();
                window.draw(missileVector2[missileIterator2].sprite);
                if (missileVector2[missileIterator2].hit==true)
                    missileVector2.erase(missileVector2.begin()+missileIterator2);
                
            }
        }
        
        //spawn monster every 2 seconds
        if(level==1){
            if(monsterClock.getElapsedTime().asSeconds()>2){
                monster.health=3;
                monster.rect.setPosition(rand()%window.getSize().x+1,0);
                monsterVector.push_back(monster);
                monsterCount++;
                if (monsterCount==3){
                    level=2;
                }
                monsterClock.restart();
                
            }
        }
        else if(level==2){
            if(monsterClock.getElapsedTime().asSeconds()>2){
                textLevel.setColor(sf::Color::Red);
                monster.rect.setSize(sf::Vector2f(46,48)); // may need to change later for collisions. sizes change cause each sprite is differnet size
                monster.sprite.setTextureRect(sf::IntRect(0, 0, 46, 48));         //Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight)
                monster.sprite.setTexture(textureMonsters2);
                monster.health=7;
                monster.rect.setPosition(rand()%window.getSize().x+1,0);
                monsterVector.push_back(monster);
                monsterClock.restart();
            }
        }

    //   cout<< "   " << monsterCount<<endl;
        //draw the monsters
        for(monsterIterator=0;monsterIterator<monsterVector.size();monsterIterator++){
            monsterVector[monsterIterator].update();
            window.draw(monsterVector[monsterIterator].sprite);
            
            //when health is 0, remove the monster entirely from the game
            //maybe add explosion?
            if(monsterVector[monsterIterator].health<=0){
                monsterVector[monsterIterator].dead();
                rocketship.killCount++;
                killClock.restart();
                deadCount++;
                if(deadCount>=20){
                    monsterVector.erase(monsterVector.begin()+monsterIterator);
                    deadCount=0;
                    score++;
                }
            }
            //decrement the rocketship's health, when it collides with the missile
            if(monsterVector[monsterIterator].rect.getGlobalBounds().intersects(rocketship.rect.getGlobalBounds())){
                rocketship.health--;
                monsterVector.erase(monsterVector.begin()+monsterIterator);
            }


        }
        //when missile.rect collides with monster.rect, decrement the health of the monster
        //and delete the missile
        for (missileIterator=0;missileIterator<missileVector.size();missileIterator++){
            for(monsterIterator=0;monsterIterator<monsterVector.size();monsterIterator++){
                if(missileVector[missileIterator].rect.getGlobalBounds().intersects(monsterVector[monsterIterator].rect.getGlobalBounds())){
                    damageClock.restart();
                    monsterVector[monsterIterator].health-=missileVector[missileIterator].damage;
                    textDamage.setString(to_string(missileVector[missileIterator].damage));
                    textDamage.setPosition(monsterVector[monsterIterator].rect.getPosition().x+10,monsterVector[monsterIterator].rect.getPosition().y);
                    textDamageVector.push_back(textDamage);
                    missileVector[missileIterator].hit=true;
                }
            }
        }
        for (missileIterator2=0;missileIterator2<missileVector2.size();missileIterator2++){
            for(monsterIterator=0;monsterIterator<monsterVector.size();monsterIterator++){
                if(missileVector2[missileIterator2].rect.getGlobalBounds().intersects(monsterVector[monsterIterator].rect.getGlobalBounds())){
                    damageClock.restart();
                    monsterVector[monsterIterator].health-=missileVector2[missileIterator2].damage;
                    textDamage.setString(to_string(missileVector2[missileIterator2].damage));
                    textDamage.setPosition(monsterVector[monsterIterator].rect.getPosition().x+10,monsterVector[monsterIterator].rect.getPosition().y);
                    textDamageVector.push_back(textDamage);
                    missileVector2[missileIterator2].hit=true;
                }
            }
        }
        
        //powerup
        if (powerupClock.getElapsedTime().asSeconds()>=20)
        {
            powerupVector.push_back(powerup);
            powerupClock.restart();
        }
        //draw powerup
        for(powerupIterator =0; powerupIterator<powerupVector.size();powerupIterator++){
            powerupVector[powerupIterator].update();
            window.draw(powerupVector[powerupIterator].sprite);
        }
        
        //missle + powerup collision
        
        
        for (missileIterator=0;missileIterator<missileVector.size();missileIterator++){
            for(powerupIterator =0; powerupIterator<powerupVector.size();powerupIterator++){
                if(missileVector[missileIterator].rect.getGlobalBounds().intersects(powerupVector[powerupIterator].rect.getGlobalBounds())){
                    powerupVector.erase(powerupVector.begin()+powerupIterator);
                    missileVector[missileIterator].hit=true;
                    doubleshot=true;
                    powerupClock.restart();
                }
            }
        }
        
        if (doubleshot==true){
            if (powerupClock.getElapsedTime().asSeconds()>=5)
                doubleshot=false;
        }
        //rocketship dies when its health is 0
        //we can move it off the screen to make it "disappear"
        if (rocketship.health<=0){
//            cout<<"Game Over"<<endl;
            rocketship.rect.setPosition(0,0);

        }
        
        rocketship.updateSpeed();
        rocketship.update();
        // Draw the Rocket sprite
        window.draw(rocketship.sprite);
//        window.draw(missiles.sprite);
        
        
        textHP.setString("HP: "+ to_string(rocketship.health));
        textScore.setString("Score: "+ to_string(score));

        window.draw(textHP);
        window.draw(textScore);
        window.draw(textLevel);
        textLevel.setString("Level: " + to_string(level));
        window.draw(textLevel);
        for (textIterator=0;textIterator<textDamageVector.size();textIterator++){
            window.draw(textDamageVector[textIterator]);
            if(damageClock.getElapsedTime().asMilliseconds()>100)
            {
                textDamageVector.erase(textDamageVector.begin()+textIterator);
                damageClock.restart();
            }
        }

        // Update the window
        window.display();
    }
    

    return EXIT_SUCCESS;
}
