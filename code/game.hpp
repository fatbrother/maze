#include "context.hpp"
#include "player.hpp"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void render();
    void update();

    void drawMap();
    void saveRoute();
    bool isValidMove(int dir);
    bool isGameOver();

    sf::RenderWindow window;
    std::vector<std::vector<char>> map;
    std::vector<std::vector<int>> route;
    Player player;
    sf::Vector2i lastPos;
};

Game::Game()
{
    // read map from file
    std::ifstream fin("map.txt");
    std::pair<int, int> start;
    int n, m;
    fin >> n >> m;
    map.resize(n);
    for (int i = 0; i < n; i++)
    {
        map[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            fin >> map[i][j];
            if (map[i][j] == START)
                start = std::make_pair(i, j);
        }
    }
    route.resize(n);
    for (int i = 0; i < n; i++)
        route[i].resize(m);

    // set player position
    player.setPos(sf::Vector2i(start.first, start.second));
    lastPos = player.getPos();

    // set window
    window.create(sf::VideoMode(500, 500), "MAZE!");
    window.setFramerateLimit(60);

    // set view to player
    sf::View view;
    view.setCenter(player.getPos().x * GRID_SIZE, player.getPos().y * GRID_SIZE);
    view.setSize(sf::Vector2f(500, 500));
    window.setView(view);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen() && !isGameOver())
    {
        processEvents();
        update();
        render();

        sf::Time lastTime = TIME_PER_FRAME - clock.getElapsedTime();
        if (lastTime > sf::Time::Zero)
            sf::sleep(lastTime);
        clock.restart();
    }
    if (window.isOpen())
    {
        window.close();
        saveRoute();
    }
}

bool Game::isGameOver()
{
    return map[player.getPos().x][player.getPos().y] == END;
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void Game::render()
{
    window.clear();
    drawMap();
    player.draw(window);
    window.display();
}

void Game::update()
{
    int dir = player.move(map);
    player.setPos(lastPos);
    if (!isValidMove(dir))
        return;

    player.setPos(sf::Vector2i(lastPos.x + DIR[dir], lastPos.y + DIR[dir + 1]));
    lastPos = player.getPos();

    // update player position
    route[player.getPos().x][player.getPos().y]++;
    route[player.getPos().x][player.getPos().y] -= route[player.getPos().x][player.getPos().y] > 100;

    // set view to player
    sf::View view;
    view.setCenter(player.getPos().x * GRID_SIZE, player.getPos().y * GRID_SIZE);
    view.setSize(sf::Vector2f(500, 500));
    window.setView(view);
}

void Game::saveRoute()
{
    // save the route as img
    sf::Image img;
    img.create(route.size(), route[0].size());
    for (size_t i = 0; i < route.size(); i++)
    {
        for (size_t j = 0; j < route[i].size(); j++)
        {
            if (map[i][j] == WALL)
                img.setPixel(i, j, sf::Color::Red);
            else if (route[i][j] > 0)
                // set color based on the number of times the player has been on that cell
                img.setPixel(i, j, sf::Color(0, 0, 255 - 255 * route[i][j] / 100));
            else
                img.setPixel(i, j, sf::Color::White);
        }
    }
    img.saveToFile("route.png");
}

bool Game::isValidMove(int dir)
{
    if (dir < 0 || dir > 3)
        return false;

    auto pos = player.getPos();
    pos.x += DIR[dir], pos.y += DIR[dir + 1];
    if (pos.x < 0 || pos.x >= (int)map.size() || pos.y < 0 || pos.y >= (int)map[0].size())
        return false;
    if (map[pos.x][pos.y] == WALL)
        return false;
    return true;
}

void Game::drawMap()
{
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
            rect.setPosition(i * GRID_SIZE, j * GRID_SIZE);
            if (map[i][j] == WALL)
                rect.setFillColor(sf::Color::White);
            else if (map[i][j] == END)
                rect.setFillColor(sf::Color::Red);
            else
                rect.setFillColor(sf::Color::Black);
            window.draw(rect);
        }
    }
}