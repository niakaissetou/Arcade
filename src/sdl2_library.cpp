/*
** EPITECH PROJECT, 2024
** sdl2_lib_create_debut_test
** File description:
** arcade
*/
#include "../Interface.hpp"
#include "../SDL.hpp"

extern "C" {

    void Move_Snake(SDL_Rect *head, int dir)
    {
        switch (dir) {
            case DOWN:
                head->y += 10;
                break;
            case UP:
                head->y -= 10;
                break;
            case LEFT:
                head->x -= 10;
                break;
            case RIGHT:
                head->x += 10;
                break;
        }
    }

    void createWindow(void)
    {
        int i = 0;
        int score = 0;
        bool game_over = false;
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *window = SDL_CreateWindow("SNAKE -----8~ SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        auto render = SDL_CreateRenderer(window, -1, 0);
        SDL_Event event;
        SDL_Rect head{500, 500, 15, 15};
        std::vector<SDL_Rect> body;
        int size = 1;
        std::vector<SDL_Rect> apples;

        int w_width = 0;
        int w_height = 0;
        SDL_GetWindowSize(window, &w_width, &w_height);

        for (; i < 3; i++) {
            int apple_x = rand() % (w_width - 30) + 15;
            int apple_y = rand() % (w_height - 30) + 15;
            SDL_Rect appleRect = {apple_x, apple_y, 15, 15};
            apples.emplace_back(appleRect);
        }
        bool quit = false;
        int dir = 0;
        bool lost = false;
        bool restart = false;
        SDL_Color head_color = {200, 150, 0, 255};
        SDL_Color body_color = {140, 200, 140, 200};

        while (!quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
                if (!lost && event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            dir = UP;
                            break;
                        case SDLK_DOWN:
                            dir = DOWN;
                            break;
                        case SDLK_LEFT:
                            dir = LEFT;
                            break;
                        case SDLK_RIGHT:
                            dir = RIGHT;
                            break;
                        case SDLK_q:
                            quit = true;
                            break;
                        default:
                            break;
                    }
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    restart = true;
                }
                if (head.x <= 0 || head.x + head.w > w_width || head.y <= 0 || head.y + head.h > w_height) {
                    lost = true;
                }
            }
            if (lost && restart || restart) {
                lost = false;
                restart = false;
                game_over = false;
                head = {500, 500, 15, 15};
                body.clear();
                body.push_back(head);
                size = 1;
                apples.clear();
                for (i = 0; i < 3; i++) {
                    int apple_x = rand() % (w_width - 30) + 15;
                    int apple_y = rand() % (w_height - 30) + 15;
                    SDL_Rect appleRect = {apple_x, apple_y, 15, 15};
                    apples.emplace_back(appleRect);
            }
            dir = 0;
            }
            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
            //SDL_RenderClear(render);

            SDL_SetRenderDrawColor(render, 140, 200, 140, 255);
            std::for_each(body.begin(), body.end(), [&](auto &snake_head) {
                SDL_RenderFillRect(render, &snake_head);
            });

            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            std::for_each(apples.begin(), apples.end(), [&](auto &apple) {
                SDL_RenderFillRect(render, &apple);
            });

            if (head.x <= 0 || head.x + head.w > w_width || head.y <= 0 || head.y + head.h > w_height) {
                //int imgFlags = IMG_INIT_PNG;
                if (!game_over) {
                    std::cout << "You Lost! Press space to restart." << std::endl;
                    game_over = true;
                }
                SDL_Surface* looseSurface = IMG_Load("../loose.png");
                if (looseSurface) {
                    SDL_Texture* looseTexture = SDL_CreateTextureFromSurface(render, looseSurface);
                    if (looseTexture) {
                        int img_width = looseSurface->w;
                        int img_height = looseSurface->h;
                        SDL_Rect dstRect = { (w_width - img_width) / 2, (w_height - img_height) / 2, img_width, img_height};
                        SDL_RenderCopy(render, looseTexture, nullptr, nullptr);
                        SDL_DestroyTexture(looseTexture);
                    }
                    SDL_FreeSurface(looseSurface);
                }
            } else {
                Move_Snake(&head, dir);

// Collision avec les pommes
                std::for_each(apples.begin(), apples.end(), [&](auto &apple) {
                    for (auto it = apples.begin(); it != apples.end();) {
                        auto& apple = *it;
                        if (head.x + head.w >= apple.x &&
                            head.x <= apple.x + apple.w &&
                            head.y + head.h >= apple.y &&
                            head.y <= apple.y + apple.h) {
                                it = apples.erase(it);
                                int newApple_x = rand() % (w_width - 10);
                                int newApple_y = rand() % (w_height - 10);
                                SDL_Rect newAppleRect = {newApple_x, newApple_y, 15, 15};
                                apples.push_back(newAppleRect);
                                body.push_back(head);
                                size += 2;
                                score += 10;
                                break;
                        } else {
                            ++it;
                        }
                    }
                });

                // Collision avec le corps du serpent
                // std::for_each(body.begin(), body.end(), [&](SDL_Rect &snake_head) {
                //     if (head.x == snake_head.x && head.y == snake_head.y) {
                //         lost = true;
                //     }
                // });

// nvl pos de la tete
                body.insert(body.begin(), head);


// Corrige la taille de la queue
                while (body.size() > size)
                    body.pop_back();
            }
            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
            SDL_RenderClear(render);

            SDL_SetRenderDrawColor(render, head_color.r, head_color.g, head_color.b, head_color.a);
            SDL_RenderFillRect(render, &head);

            SDL_SetRenderDrawColor(render, body_color.r, body_color.g, body_color.b, body_color.a);
            for (size_t i = 1; i < body.size(); ++i) {
                SDL_RenderFillRect(render, &body[i]);
            }
            // SDL_SetRenderDrawColor(render, 140, 200, 140, 255);
            // std::for_each(body.begin(), body.end(), [&](auto &snake_head) {
            //     SDL_RenderFillRect(render, &snake_head);
            // });

            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            std::for_each(apples.begin(), apples.end(), [&](auto &apple) {
                SDL_RenderFillRect(render, &apple);
            });

            SDL_RenderPresent(render);
            SDL_Delay(60);
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
        }
}
