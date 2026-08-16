#pragma once
#include <queue>
#include <functional>

namespace AgroResQ
{
namespace Engine
{

class TaskQueue
{
private:
    std::queue<std::function<void()>> tasks;

public:
    TaskQueue() = default;
    ~TaskQueue() = default;

    void enqueue(const std::function<void()>& task);
    void enqueue(std::function<void()>&& task);
    void processAll();
    void processOne();
    size_t size() const;
    bool empty() const;
    void clear();
};

}
}