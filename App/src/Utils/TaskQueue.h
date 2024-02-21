#pragma once

#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace Gesture {
    class TaskQueue {
    public:

        static TaskQueue* Instance()
        {
            if (!instance)
            {
                instance = new TaskQueue();
            }

            return instance;
        }

        void EnqueueTask(const std::function<void()>& task) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(task);
            m_cond.notify_one();
        }

        bool TryDequeueTask(std::function<void()>& task) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_queue.empty()) {
                return false;
            }
            task = m_queue.front();
            m_queue.pop();
            return true;
        }

    private:
        std::queue<std::function<void()>> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_cond;
        static TaskQueue* instance;
    };
}