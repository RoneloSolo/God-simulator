#pragma  once

class Engine {
    public:
        Engine(int width, int height, const char* title);
        ~Engine() noexcept;
        bool Close() const;
        void Tick();
    private:
        void Draw();
        void Update();
        void PhysicsUpdate();
};