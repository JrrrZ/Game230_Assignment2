/* SFML Includes             *
 * Add to every SFML project */
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <fstream>
#include <string>

// Namespaces
using namespace sf;
using namespace std;

// Prototypes
void setup(RenderWindow& window);
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window);

// Global Variables
Texture tileTexture;
Sprite tileSprite;
int	 textureNum;
Texture tileSet[21];
float tilePosX;
float tilePosY;
int gridPosX;
int gridPosY;
int grid[10][10];
Sprite spriteinGrid[10][10];
Sprite Test;
int spritePosX;
int spritePosY;
int i;
int j;
bool loadFile = false;
string loadReader[10][10];
string temp1;
int temp2;
int m;
int n;


// Main, our applicaiton entry function
int main()
{
	// Create the window for the game
	// All rendering happens here
	RenderWindow window(VideoMode(700, 700), "SFML works!");
	
	setup(window);

	// This is our game loop!
	// All input, logic, and rendering should be handled here
	while (window.isOpen())
	{
		// Check for events from the window
		// E.g., is the window being closed?
		Event event;
		while (window.pollEvent(event))
		{
			handleInput(window, event);
			
			// Space key creates a screenshot
			if (event.key.code == Keyboard::Space) {
				Texture texture;
				texture.create(window.getSize().x, window.getSize().y);
				texture.update(window);
				if (texture.copyToImage().saveToFile("Homework 2 Screenshot.png"))
				{
					cout << "Screenshot saved to Homework 2 Screenshot.png" << endl;
				}
			}

			// S key saves a txt file
			if (event.key.code == Keyboard::S) {
				ofstream myfile("level.txt", ios::out | ios::trunc);
				if (myfile.is_open())
				{
					myfile.clear();
					for (gridPosY = 0; gridPosY < 10; gridPosY++) {
						for (gridPosX = 0; gridPosX < 10; gridPosX++) {
							myfile << grid[gridPosX][gridPosY] << " ";
						}
						myfile << endl;
					}
					cout << "Open a new file!";
					myfile.close();
					cout << "All saved!";
				}
				else cout << "Unable to open file";
			}

			// L key load a txt file
			if (event.key.code == Keyboard::L) {
				ifstream othersfile("level.txt");
				if (othersfile.is_open())
				{
					cout << "\nThe loaded Gird is:\n";
					for (gridPosY = 0; gridPosY < 10; gridPosY++) {
						
						/*cout << temp1 << " is first line" << endl;

						int length = temp1.length();
						int preIndex = -1;
						gridPosX = 0;

						for (int index = 0; index < length; index++) {
							if (temp1[index] == '/n') {
								loadReader[gridPosX][gridPosY] = temp1.substr(preIndex+1, index);
								gridPosX++;
								preIndex = index;
								cout << loadReader[gridPosX][gridPosY];
							}
						}*/
						for (gridPosX = 0; gridPosX < 10; gridPosX++) {
							othersfile >> temp1;
							loadReader[gridPosX][gridPosY] = temp1;
							cout << loadReader[gridPosX][gridPosY];
						}
						cout << endl;
					}
					//temp = 0;
					for (n = 0; n < 10; n++) {
						for (m = 0; m < 10; m++) {
							temp2 = atoi(loadReader[m][n].c_str());
							grid[m][n] = temp2;
							//spriteinGrid[m][n].setTexture(NULL);
							//cout << grid[m][n] << " " << loadReader[m][n] << endl;
							//cout << " ";
							if (grid[m][n] >= 0) {
								spriteinGrid[m][n].setTexture(tileSet[grid[m][n]]);
								spriteinGrid[m][n].setPosition(m * 70, n * 70);
							}
						}
					}


					
					cout << "All loaded!";
					//cout << loadReader[0][0];
				}
				else cout << "Unable to open file";
			}
		}

		update(window);

		render(window);

	}

	// The game has exited normally so send a normal exit status integer back
	return 0;
}

void setup(RenderWindow& window) {
	// Load sprites
	for (textureNum = 0; textureNum < 21; textureNum++) {
		if (tileTexture.loadFromFile("Assets/Platformer/Tileset/Platformer-" + to_string(textureNum) + ".png")) {
			cout << "Platformer-" + to_string(textureNum) + ".png" << endl;
			tileSet[textureNum] = tileTexture;
		}
	}
	textureNum = 0;
	tileSprite.setTexture(tileSet[textureNum]);

	// setup the grid map
	cout << "\nThe Gird is:\n";
	for (gridPosY = 0; gridPosY < 10; gridPosY++) {
		for (gridPosX = 0; gridPosX < 10; gridPosX++) {
			grid[gridPosX][gridPosY] = -1;
			cout << grid[gridPosX][gridPosY];
		}
		cout << endl;
	}
}

void handleInput(RenderWindow& window, Event& e) {
	if (e.type == Event::Closed)
		window.close();

	tilePosX = (Mouse::getPosition(window).x / 70) * 70;
	tilePosY = (Mouse::getPosition(window).y / 70) * 70;
	tileSprite.setPosition(tilePosX, tilePosY);

	if (e.type == Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == Mouse::Left)
		{
			cout << "Yes, you clicked." << endl;
			grid[Mouse::getPosition(window).x / 70][Mouse::getPosition(window).y / 70] = textureNum;
			cout << grid[Mouse::getPosition(window).x / 70][Mouse::getPosition(window).y / 70] << endl;

			cout << "\nThe Gird is:\n";
			for (gridPosY = 0; gridPosY < 10; gridPosY++) {
				for (gridPosX = 0; gridPosX < 10; gridPosX++) {
					cout << grid[gridPosX][gridPosY];
				}
				cout << endl;
			}

			// Place the sprite
			//Test.setTexture(tileSet[textureNum]);
			//Test.setPosition(tilePosX, tilePosY);
			spritePosX = Mouse::getPosition(window).x / 70;
			spritePosY = Mouse::getPosition(window).y / 70;
			cout << "Sprite is at " + to_string(spritePosX) + "," + to_string(spritePosY) << endl;
			spriteinGrid[spritePosX][spritePosY].setTexture(tileSet[textureNum]);
			spriteinGrid[spritePosX][spritePosY].setPosition(tilePosX, tilePosY);
		
		}
	}

	// Change tiles
	if (e.type == Event::KeyReleased)
	{
		if (e.key.code == Keyboard::Up)
		{
			textureNum++;
			textureNum = textureNum % 21;
			cout << textureNum << endl;
			tileSprite.setTexture(tileSet[textureNum]);
		}
		else if (e.key.code == Keyboard::Down)
		{
			if (textureNum > 0) {
				textureNum--;
			}
			else {
				textureNum += 20;
			}
			cout << textureNum << endl;
			tileSprite.setTexture(tileSet[textureNum]);
		}
	}
}

void update(RenderWindow& window) {

}

void render(RenderWindow& window) {
	// This clears the window at the beginning of every frame
	// If we comment this out, it is a very simple way to create a paintbrush effect since the window is never cleared
	window.clear();
	window.setTitle("Mouse Position: (" + to_string(int(Mouse::getPosition(window).x / 70)) + ", " + to_string(int(Mouse::getPosition(window).y / 70)) + ")");

	for (j = 0; j < 10; j++) {
		for (i = 0; i < 10; i++) {
			window.draw(spriteinGrid[i][j]);
		}
	}
	window.draw(tileSprite);

	// Display the window buffer for this frame
	window.display();
}

