#include "main.hpp"
#include "application.hpp"
#include "loadressourceexception.hpp"
#include "window.hpp"
#include "rnetwork.hpp"

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

int main()
{
        Window &window = Window::instance();
		window.ShowMouseCursor(false);
        window.Clear(sf::Color(0, 0, 0));
        window.Display();

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
