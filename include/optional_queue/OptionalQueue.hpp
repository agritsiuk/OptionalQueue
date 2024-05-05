#pragma once

#include <cstdint>
#include <queue>

/**
 * FIFO структура данных, опционально добавляющая l-value элемент в очередь,
 * если добавление не было отменено возвращенным RAII-объектом.
 * Время жизни добавляемого элемента должно переживать RAII-объект, либо вызов метода flush().
 * Андрей Грицюк, Москва 2024.
 *
 * FIFO data structure which optionally adds l-value element into a queue
 * if the addition was not cancelled by the returned RAII object.
 * An element which is being added should outlive an RAII object or flush() method invocation.
 * Andrei Gritsiuk, Moscow 2024.
 */
template <class T>
class OptionalQueue {
   public:
    /**
     * RAII-объект, который позволяет отменить добавление объекта в очередь.
     * A RAII-handle which allows to cancel enqueueing of the last added element.
     */
    class FlushHandle {
       public:
        void cancelEnqueue() { _enqueueCancelled = true; }

        ~FlushHandle() {
            if (_enqueueCancelled) {
                _optionalQueue.cancelFlush();
                return;
            }

            _optionalQueue.flush();
        }

       private:
        friend class OptionalQueue;
        FlushHandle(OptionalQueue& optionalQueue) : _optionalQueue{optionalQueue} {}

       private:
        bool _enqueueCancelled{};
        OptionalQueue& _optionalQueue{};
    };

    OptionalQueue() = default;

    /**
     * Опционально добавляет элемент в очередь.
     * @return RAII-объект, позволяющий отменить добавление элемента в очередь.
     * Optionally adds an element into a queue.
     * @return RAII-object which allows to cancel enqueueing of the last added element.
     */
    [[nodiscard]] FlushHandle push(T& elem) {
        if (_elem) {
            _queue.push(*_elem);
        }

        _elem = &elem;
        return FlushHandle(*this);
    }

    /**
     * Отменяет добавление последнего элемента в очередь.
     * Cancels enqueueing of the last added element.
     */
    void cancelFlush() { _elem = {}; }

    /**
     * Добавляет последний элемент в очередь.
     * Flushes the last added element into a queue.
     */
    void flush() {
        if (_elem) {
            _queue.push(*_elem);
            _elem = {};
        }
    }

    /**
     * Возвращает true, если структура данных пуста.
     * Returns true if data structure is empty.
     */
    bool empty() const { return !(_elem) && _queue.empty(); }

    /**
     * Возвращает первый элемент в структуре данных.
     * Returns top element in the data structure.
     */
    T& top() { return _queue.empty() ? *_elem : _queue.front(); }

    /*
     * Возвращает первый элемент в структуре данных.
     * Returns top element in the data structure.
     */
    const T& top() const { return _queue.empty() ? *_elem : _queue.front(); }

    /**
     * Удаляет первый элемент в структуре данных.
     * Removes top element from the data structure.
     */
    void pop() {
        if (!_queue.empty()) {
            _queue.pop();
        } else {
            _elem = {};
        }
    }

    std::size_t size() const { return _queue.size() + bool(_elem); }

    /**
     * Clears the data structure.
     */
    void clear() {
        _elem = {};
        _queue.clear();
    }

   protected:
    T* _elem{};
    std::queue<T> _queue{};
};