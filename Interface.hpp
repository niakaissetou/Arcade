/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-vaea.seyed-saleh
** File description:
** Interface
*/

#ifndef INTERFACE_HPP_
    #define INTERFACE_HPP_
    #include <utility>
    #include <string>
    #include <vector>
    #include <map>
    #include <SFML/Graphics.hpp>
    #include <memory>


namespace Arcade {
        typedef struct ObjectTexture_t {
        std::string sfml;
        std::string sdl;
        char ncurses;
    } ObjectTexture_t;

    class IObject {
        public:
            virtual ~IObject() = default;
            virtual void setPosition(double x, double y) = 0;
            virtual std::pair<double, double> getPosition() = 0;
            virtual std::string getName() = 0;
            virtual void set_texture() = 0;
            virtual ObjectTexture_t get_texture() = 0;
            virtual std::vector<double> getZone() = 0;
        protected:
        private:
    };
}
namespace Arcade {
        class ILibrary {
        public:
            ILibrary() {};
            virtual ~ILibrary() = default;
            virtual void initializeLib(std::vector<std::shared_ptr<IObject> > ObjectList, std::vector<std::shared_ptr<IObject> > Player) = 0;
            virtual void drawObject(std::vector<std::shared_ptr<IObject> > ObjectList, std::vector<std::shared_ptr<IObject> > Player) = 0;
            virtual std::string handleEvent() = 0;
            virtual void setScore(unsigned int score) = 0;
            virtual void setEvent(std::vector<std::shared_ptr<IObject> > ObjectList, std::vector<std::shared_ptr<IObject> > Player) = 0;
            virtual void displayName(const std::string& name) = 0;
            virtual void createMenu() = 0;
            virtual std::string HandleWindow() = 0;
            virtual void createWindow(std::pair<unsigned int, unsigned int> WindowSize) = 0;
            virtual void SetTextureText( std::vector<std::pair<std::shared_ptr<IObject>, std::string> > _menu) = 0;
            virtual void drawmenu(int state, std::string name) = 0;
            virtual std::string handleMenu(std::string lib, std::string game, std::string key) = 0;

        protected:
        private:
    };
}

namespace Arcade {

template<typename ObjectT, typename PlayerT, typename OldKeyT, typename NewKeyT>

    class IGame {
    public:
        virtual ~IGame() = default;
        virtual std::string getName() = 0;
        virtual void update(OldKeyT OldKey, NewKeyT NewKey, int size) = 0;
        virtual unsigned int getScore() = 0;
        virtual bool isGameOver() = 0;
        virtual void reset() = 0;
        virtual void createObjectList(int size) = 0;
        virtual const ObjectT& getObjectList() const = 0;
        virtual const PlayerT& getPLayerList() const = 0;
        virtual void set_objectList(int size) = 0;
    };
}
#endif