#include <SDL_mixer.h>
#include <sol.hpp>
#include <iostream>
#include <string>
#include <enet/enet.h>
#include "Serializable.h"
#include "Client.h"
#include "Person.h"
#include "Point.h"

//Screen dimension constants
static constexpr int SCREEN_WIDTH = 680;
static constexpr int SCREEN_HEIGHT = 680;



int main(int argc, char* args[])
{
	//std::cout << "Hello world\n";
	//Person person("Kakashi", 234, 79.4);
	//person.Print();
	//
	//std::vector<char> buff;
	//buff.reserve(person.GetSize());
	//person.Serialize(buff.data());
	//
	//std::cout << " person.GetSize(): " << person.GetSize()
	//	<< " strlen(buff): " << sizeof(buff) << '\n';
	//
	//Person person2;
	//person2.Deserialize(buff.data());
	//
	//std::cout << " after deserializing person 2 is ";
	//person2.Print();
	
	Point pOne(200, 500);
	pOne.Print();
	std::vector<uint8_t> buff;
	buff.reserve(pOne.GetSize());
	pOne.Serialize(buff.data());


	std::cout << "\npoint.GetSize(): " << pOne.GetSize()
		<< " strlen(buff): " << sizeof(buff) << '\n';
	
	Point pTwo;
	pTwo.Deserialize(buff.data());

	std::cout << "\nAfter deserializing point 2 is: " << std::endl;
	pTwo.Print();
	
	//std::cout << "\n print out buffer: ";
	//SerializablePOD<uint8_t>::PrintVector(buff);

	Client NewClient;
	NewClient.Init();
	NewClient.CreateClient();
	NewClient.SetHost();
	NewClient.ConnectPeer();
	NewClient.ConnectServer();
	NewClient.ReceiveComms();
	
	NewClient.SendPacket(pOne);
	NewClient.MsgLoop();


	
	//NewClient.Disconnect(); //END GAME LOOP
	
/*
	//ENET
	if (enet_initialize() != 0) {
		
		return 0;
	}
	std::cout << "ENET INITIALIZED SUCCESSFULLY!\n";

	//SDL and LUA
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName = "Level N\n";

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL TTF
	if (TTF_Init() < 0)
	{
		std::cerr << "SDL TTF could not initialize! TTF_Error: " << TTF_GetError() << "\n";
	}
	//Initialize SDL MIXER
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
	{
		std::cerr << "SDL MIXER could not initialize! Mixer_Error: " << Mix_GetError() << "\n";
	}
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
	}
	else
	{
		//Create new window
		window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
		}
		else
		{
			SDL_Event event;	 
			bool running = true; 

			while (running)
			{
				
				while (SDL_PollEvent(&event))
				{
					running = event.type != SDL_QUIT;
				}

				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);

				//Fill the surface white
				SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x0, 0x0, 0xFF));

				//Update the surface
				SDL_UpdateWindowSurface(window);
			}
		}
	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	*/
	return 0;
}