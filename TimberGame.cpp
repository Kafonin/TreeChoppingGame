// HelloSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//include important c++ libraries here

#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



using namespace sf;


//function declarations
void updateBranches(int seed);			//function prototype
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
//where is the player/branch?
//left or right
enum class side
{
	LEFT, RIGHT, NONE
};
side branchPositions[NUM_BRANCHES];


int main()
{
	//create video mode object -- represents resolution of player screen
	VideoMode vm(1920, 1080);

	
	
	//create and open window for game. vm object initializes part of the window
	RenderWindow window(vm, "Timber!", Style::Fullscreen);

	
	
	//create texture to hold a graphic on the gpu
	Texture textureBackground;

	
	
	//load a graphic into the texture
	textureBackground.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\background.png");

	
	
	//create a sprite file
	Sprite spriteBackground;

	
	
	//attaCK THE TEXTURE TO THE SPRITE
	spriteBackground.setTexture(textureBackground);

	
	
	//set spritebackgrounmd to cover the screen
	spriteBackground.setPosition(0, 0);

	
	
	//make a tree sprite
	Texture textureTree;					//object instantiated
	textureTree.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\tree.png"); //load the graphic through this path
	Sprite spriteTree;						//object instantiated from the class
	spriteTree.setTexture(textureTree);		//sets the tree graphic
	spriteTree.setPosition(810, 0);			// set the position of the tree graphic

	
											
	//floating bee
	Texture textureBee;
	textureBee.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	
	//is the bee flying?
	bool beeFlying = false;
	
	//bee speed
	float beeSpeed = 0.0f;



	//MKE thrre cloud sprites from 1 texture
	Texture textureCloud;

	//load one texture file
	textureCloud.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\cloud.png");

	//create 3 NEW sprites with the SAME texture file
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;

	//set the cloud objects with the cloud texture file
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	//position of clouds
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);

	//are clouds currently on the screen?
	bool cloud1Flying = false;
	bool cloud2Flying = false;
	bool cloud3Flying = false;

	//cloud speed
	float cloudSpeed1 = 0.0f;
	float cloudSpeed2 = 0.0f;
	float cloudSpeed3 = 0.0f;

	// variables to control time
	Clock clock;


	//Time bar set up -- IMPORTANT -- add AFTER Clock Declaration!!
	RectangleShape timeBar;												//SFML class for drawing rectangles
	float timerBarStartWidth = 400;
	float timerBarHeight = 80;
	timeBar.setSize(Vector2f(timerBarStartWidth, timerBarHeight));		//size of the time bar is set here with the two float var created
	timeBar.setFillColor(Color::Red);									//vector2f is a class which holds two float variables
	timeBar.setPosition((1920 / 2) - timerBarStartWidth / 2, 980);		//first divides 1920 by 2; then divides timerBarStartWidth by 2; then subtracts the latter from the former.
																		//result makes timebar sit horizontall on screen.



	Time gameTimeTotal;													//instantiate the Time class with an object called gametimetotal
	float timeRemaining = 6.0f;											//create float var
	float timerBarWidthPerSecond = timerBarStartWidth / timeRemaining;	//timerBarWidthPerSecond is initialized when timerBarStartWidth is divided by timeRemaining


	// Track whether game is running
	bool paused = true;


	/******************
	DRAWING TEXT IN GAME
	*******************/
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	//set chosen fonts path
	Font font;
	font.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\fonts\\KOMIKAP_.ttf");

	//set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	//assign actual message
	messageText.setString("Press Enter to start the game!");
	scoreText.setString("score = 0");

	//make it really big
	messageText.setString("Score = 0");

	//make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	//choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::Cyan);

	//text position
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);
 



	//Prepare 5 branches
	Texture textureBranch;
	textureBranch.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\branch.png");
	//set texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);		//set position OFF SCREEN
		//set the sprites origin to dead center
		//sp[in it round w/out changing position
		branches[i].setOrigin(220, 20);				//origin = set point ocated when it is drawn. this sprite is drawn in the center.
	}
	

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);



	//prepare he player
	Texture texturePlayer;
	texturePlayer.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	//the player starts on the left
	side playerSide = side::LEFT;

	//prepare teh gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	//prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//line the axe up wiuth the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\graphics\\log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);


	//some other useful log related variables
	bool logActive = false;									//LogActive shows whether it is currently moving or not.
	float logSpeedX = 1000;									//LogSpeedX and logSpeedY will decide how fast the log will move.
	float logSpeedY = -1500;

	//control player input
	bool acceptInput = false;

	//prepare the sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\sound\\chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\sound\\death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	//out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("C:\\Users\\kafon\\source\\repos\\timber3\\sound\\out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);
	

	//****************RUN GAME**********************
	
	while (window.isOpen())
	{
		//handle players input
		Event event;
		while (window.pollEvent(event))							//The pollEvent function puts data into the event object, which describes an operating system event,
		{														//such as a key press, key release, mouse movement, mouse click, game controller action,
			if (event.type == Event::KeyReleased && !paused) {	//or something that happened to the window itself.
				//listen for key presses again
				acceptInput == true;

				//hide axe
				spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))				//fun fact, the while loop, depending on how poerful your poc is, executes 1000's of times p/second.
		{															//and pressing the return key will execute this code, which will be executed well over a 100 times -- restarting the game over 100 times
			paused = false;											//because even the slightest moment when the key is held down it is detected and the related code will execute.

			//reset time & score
			score = 0;
			timeRemaining = 6;

			//make all branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)					//use the for loop to set the tree with no branches
			{
				branchPositions[i] = side::NONE;					//set branch position to side none to be fair, so when game starts the player can get ready
			}

			//make sure gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			//move player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}

		//wrap the player controls to make sure we are accepting input
		if (acceptInput)
		{
			//more code coming next ...
			//first handle accpeting the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				//make sure the player is on the right
				playerSide = side::RIGHT;
				score++;

				//add the amount of time to remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(1200, 720);

				//update branches
				updateBranches(score);

				//set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				//play chop sound
				chop.play();
			}
			//handle the left cursor key

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				//make sure the player is on the left
				playerSide = side::LEFT;
				score++;

				//add the amount of time to remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);

				spritePlayer.setPosition(580, 720);

				//up[date branches
				updateBranches(score);

				//set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}
		}



		/*
		********************************
		update the scene here
		********************************
		*/
		
		if (!paused)
		{

			//SFML framerate solution
			Time deltaTime = clock.restart();

			//subtract from the amount of time remaining
			timeRemaining -= deltaTime.asSeconds();				//subtract time the player has left by however long the previous frame took to execute this code
			//size up the timebar
			timeBar.setSize(Vector2f(timerBarWidthPerSecond *	//adjust time bar. the X value of vector2f is initialized with timebarwidthpersecond multiplied by timeRemaining
				timeRemaining, timerBarHeight));				//produces the correct width relative to how long the player has left. height remains same.
		 

			if (timeRemaining <= 0.0f)							//test whether time has run out on this condition
			{
				//pause the game
				paused = true;									//set pause to true to its the last time the update code is executed

				//change message shown to the player
				messageText.setString("Out of time!!");

				//reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds(); //repeat of the code way above ...
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//play out of time sound
				outOfTime.play();
			}

			//set up the bee to fly
			if (!beeFlying) {
				//how fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200; //generate random int num 

				//altitude of bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500; //generate random int like this
				spriteBee.setPosition(2000, height);
				beeFlying = true;
			}
			else
			{
				//move the bee
				spriteBee.setPosition(													//bee position is changing using this.
					spriteBee.getPosition().x -											//use the getPosition function to get the X coordinate of the bee
					(beeSpeed * deltaTime.asSeconds()),									//add bee speed into delta time as seconds to that coordinate
					spriteBee.getPosition().y);											//use getPosition Y to keep the bee in exactly the same Y coordinate

				//if the bee has reached the right hand side of the screen, do this
				if (spriteBee.getPosition().x < -100) {

					//set up new cloud next frame
					beeFlying = false;
				}
			}


			//set up clouds here
			//clud 1 
			if (!cloud1Flying)
			{
				//speed of cloud
				srand((int)time(0) * 10);
				cloudSpeed1 = (rand() % 200);

				//how high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Flying = true;
			}
			else
			{
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Flying * deltaTime.asSeconds()),
					spriteCloud1.getPosition().y);

				if (spriteCloud1.getPosition().x > 1920) //reached the right edge of screen?
				{
					//set it up for a new cloud
					cloud1Flying = false;
				}
			}



			if (!cloud2Flying)
			{
				//speed of cloud
				srand((int)time(0) * 20);
				cloudSpeed2 = (rand() % 200);

				//how high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud1.setPosition(-200, height);
				cloud2Flying = true;
			}
			else
			{
				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Flying * deltaTime.asSeconds()),
					spriteCloud2.getPosition().y);

				if (spriteCloud2.getPosition().x > 1920) //reached the right edge of screen?
				{
					//set it up for a new cloud
					cloud2Flying = false;
				}
			}


			if (!cloud3Flying)
			{
				//speed of cloud
				srand((int)time(0) * 30);
				cloudSpeed3 = (rand() % 200);

				//how high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Flying = true;
			}
			else
			{
				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Flying * deltaTime.asSeconds()),
					spriteCloud3.getPosition().y);

				if (spriteCloud3.getPosition().x > 1920) //reached the right edge of screen?
				{
					//set it up for a new cloud
					cloud3Flying = false;
				}
			}

			//update scpore text here
			std::stringstream ss;		//instantiate object stringstream as 'ss'
			ss << "Score = " << score;
			scoreText.setString(ss.str());	//displays/sets the string contained in ss to scoreText

			//update branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;					//this means that the 1st branch will have a height of 0, the 2nd = 150, and the 6th of 750.
				if (branchPositions[i] == side::LEFT)
				{
					//move sprite to left side
					branches[i].setPosition(610, height);
					//flip the sprite around the other way
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					//move the sprite to the right side
					branches[i].setPosition(1330, height);
					//set the sprite rotation to normal
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(0);
				}
				else
				{
					//hide branch
					branches[i].setPosition(3000, height);
				}
			}

			//handle flying log
			if (logActive)
			{
				spriteLog.setPosition(
					spriteLog.getPosition().x +
					(logSpeedX * deltaTime.asSeconds()),
					spriteLog.getPosition().y +
					(logSpeedY * deltaTime.asSeconds()));

				//has the log reached teh right hand edge?
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > 2000)
				{
					//set it up to be a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			//has the player been squished by the branch?
			if (branchPositions[5] == playerSide)
			{
				//death
				paused = true;
				acceptInput = false;

				//draw the grave stone
				spriteRIP.setPosition(525, 760);

				//hide the player
				spritePlayer.setPosition(2000, 660);

				//change the text of the message
				messageText.setString("SQUISHED!");

				//center it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f,
					1080 / 2.0f);

				//play the death sound
				death.play();
			}
		} //end if (!paused)

		
		/**********************/
		/*draw scene***********/
		/**********************/
		
		
		
		//clear everything from the last frame
		window.clear();

		
		
		
		//IMPORTANT draw game scene here ... IMPORTANT --> ORDER DRAWN IS IMPORTANT! BACKGROUND -> SPRITE1 -> SPRITE2 -> CHARACTER1. ETC.
		window.draw(spriteBackground);

		
		
		
		//draw the clouds onto the screen here
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);


		//draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		
		//draw bee
		window.draw(spriteBee);


		//draw tree
		window.draw(spriteTree);

		//draw player
		window.draw(spritePlayer);

		//draw the axe
		window.draw(spriteAxe);

		//draw flying log
		window.draw(spriteLog);

		//draw gravestone
		window.draw(spriteRIP);


		//draw score
		window.draw(scoreText);

		//draw timebar
		window.draw(timeBar);


		if (paused)
		{
			//draw the message
			window.draw(messageText);
		}



		//show everything drawn
		window.display();
	}

	return 0;
}

//fUNCTION DEFINITION
void updateBranches(int seed)
{
	//move branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	//spawn a new branch at position 0
	//left, right, or none
	srand((int)time(0) + seed);					//use the int seed var that gets passed in with the func call
												//to guarantee that the random number seed
	int r = (rand() % 5);						//generate a random number between 1 & 4, & store result in var 'r'
	switch (r)									//switch using 'r' as the expression
	{
	case 0:										//The case statements mean that if r is equal to zero,
		branchPositions[0] = side::LEFT;		//then we add a new branch on the left-hand side at top of the tree
		break;
	case 1:										//If r is equal to one, then the branch goes on the right.
		branchPositions[0] = side::RIGHT;
		break;
	default:									//If r is anything else, two, three or four, then the default
		branchPositions[0] = side::NONE;		//ensures that no branch will be added at the top.
		break;
	}
}

