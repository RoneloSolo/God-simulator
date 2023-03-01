#pragma  once

class Game{
    public:
        Game(int width, int height, const char* title);
        ~Game() noexcept;
        bool Close() const;
        void Tick();
    private:
        void Draw();
        void Update();
};