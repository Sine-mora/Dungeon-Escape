#include <iostream>
#include <imgui.h>
#include "Renderer/Renderer2D.h"
#include "Renderer/Texture.h"

int main(int agrc, char* args[]){
	std::cout << "Hello world\n";


	auto& rend = K9::Renderer2D::Ref();

	bool m_isRunning = true;
	SDL_Event m_event{};



	if (rend.Init("hello", 400, 600)) {		
		std::cout << "Initialized! \n";
		
		const auto& screensize = rend.GetScreenSize();

		
		
		K9::Texture Text;
		if (!Text.Load("assets/textures/123.jpg")) {
			std::cerr << "Failed loading texture;";
				return 0;
		}

		SDL_Rect destRect = screensize;

		while (m_isRunning)
		{	
			std::cout << "SDL_EVENT! \n";
			// determine if the user still wants to have the window open
			// (this basically checks if the user has pressed 'X')
			m_isRunning = (m_event.type != SDL_QUIT);
			
			while (SDL_PollEvent(&m_event))
			{
				rend.HandleEvent(m_event);

			}
			rend.BeginFrame();
			rend.DrawTexture(Text, destRect);
			rend.BeginImGUIFrame();
			ImGui::ShowDemoWindow(&m_isRunning);
			rend.EndImGUIFrame();
			rend.EndFrame();
		}
		rend.Shutdown();
		
	}




return 0;
}