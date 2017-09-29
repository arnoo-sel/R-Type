#include "main.hpp"
#include "application.hpp"
#include "loadressourceexception.hpp"
#include "window.hpp"
#include "rnetwork.hpp"
#include "fonts.h"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

int main()
{
        Window &window = Window::instance();
        window.setMouseCursorVisible(false);
        window.clear(sf::Color(0, 0, 0));
        window.display();
        Fonts::initialize();

        Application &app = Application::instance();
        try
        {
				app.globalRessources = app.loadRessources();
        }
        catch(LoadRessourceException *e)
        {
                COUT << e->what() << ENDL;
                getchar();
                return(-1);
        }
		catch (...)
		{
			COUT << "ERROR" << ENDL;
		}
        COUT << "PRESS ENTER TO LAUNCH" << ENDL;
        //getchar();
        app.launch();
		app.quit(app.globalRessources);
		
        return 0;
}
