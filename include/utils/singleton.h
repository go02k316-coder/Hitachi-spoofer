#pragma once

#include <mutex>
#include <memory>

namespace UchihaSpoofer {
namespace Utils {

/**
 * @brief Thread-safe singleton template
 * Usage: class MyClass : public Singleton<MyClass> { ... };
 */
template<typename T>
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;
    
    // Prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    // Prevent moving
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    
public:
    /**
     * @brief Get singleton instance (thread-safe)
     */
    static T& GetInstance() noexcept {
        static T instance;
        return instance;
    }
    
    /**
     * @brief Get unique pointer to singleton
     */
    static std::unique_ptr<T> GetInstancePtr() noexcept {
        return std::make_unique<T>(GetInstance());
    }
};

} // namespace Utils
} // namespace UchihaSpoofer
