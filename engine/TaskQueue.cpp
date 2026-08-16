#include "TaskQueue.h"

namespace AgroResQ
{
namespace Engine
{

void TaskQueue::enqueue(const std::function<void()>& task)
{
    tasks.push(task);
}

void TaskQueue::enqueue(std::function<void()>&& task)
{
    tasks.push(std::move(task));
}

void TaskQueue::processAll()
{
    while (!tasks.empty())
    {
        auto task = std::move(tasks.front());
        tasks.pop();
        task();
    }
}

void TaskQueue::processOne()
{
    if (tasks.empty()) return;
    auto task = std::move(tasks.front());
    tasks.pop();
    task();
}

size_t TaskQueue::size() const
{
    return tasks.size();
}

bool TaskQueue::empty() const
{
    return tasks.empty();
}

void TaskQueue::clear()
{
    while (!tasks.empty())
        tasks.pop();
}

}
}