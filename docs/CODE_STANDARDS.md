# Code Standards & Best Practices

## Naming Conventions

### Variables & Functions
- Local variables: `camelCase` (e.g., `windowHandle`, `isInitialized`)
- Member variables: `m_camelCase` (e.g., `m_logFile`, `m_mutex`)
- Static variables: `s_camelCase` (e.g., `s_instance`)
- Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_LOG_SIZE`, `DEFAULT_TIMEOUT`)
- Functions: `PascalCase` (e.g., `InitializeApplication`, `LogMessage`)
- Classes: `PascalCase` (e.g., `Logger`, `HWIDGenerator`)

### Files
- Source files: `snake_case.cpp` (e.g., `hwid_generator.cpp`)
- Header files: `snake_case.h` (e.g., `hwid_generator.h`)
- Test files: `test_snake_case.cpp` (e.g., `test_hwid_generator.cpp`)

## Code Organization

### Header Files
```cpp
#pragma once

#include <necessary_headers>
#include "other_headers"

namespace UchihaSpoofer {
namespace SubNamespace {

// Forward declarations
class ForwardDecl;

// Actual declarations
class MyClass { ... };

} // namespace SubNamespace
} // namespace UchihaSpoofer
```

### Implementation Files
```cpp
#include "header.h"
#include <std_includes>

using namespace UchihaSpoofer::SubNamespace;

// Implementation details
```

## Error Handling

### Use Custom Exceptions
```cpp
try {
    if (!condition) {
        throw Core::UchihaException(ErrorCode::SpecificError, "Detailed message");
    }
}
catch (const Core::UchihaException& e) {
    logger.Error("Exception: " + std::string(e.what()));
    // Handle or rethrow
}
catch (const std::exception& e) {
    logger.Critical("Unexpected error: " + std::string(e.what()));
    // Handle
}
```

### Avoid
- Raw pointers (use `std::unique_ptr` or `std::shared_ptr`)
- Global mutable state (use Singleton pattern)
- `goto` statements
- Bare `new`/`delete`

## Thread Safety

### Always Protect Shared Data
```cpp
class ThreadSafeClass {
private:
    std::mutex m_mutex;
    std::vector<Data> m_data;
    
public:
    void AddData(const Data& d) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data.push_back(d);
    }
};
```

## Documentation

### Doxygen Style Comments
```cpp
/**
 * @brief One line description
 * @param param1 Description
 * @return Description
 * @throws UchihaException If something fails
 */
bool DoSomething(int param1);
```

## Performance Guidelines

1. **Avoid unnecessary allocations**
   - Use stack allocation when size is known
   - Reuse objects when possible

2. **Use const references for large objects**
   ```cpp
   void Process(const std::vector<Data>& data);
   ```

3. **Minimize logging in hot paths**
   ```cpp
   if (logger.IsEnabled(LogLevel::Debug)) {
       logger.Debug("Expensive operation...");
   }
   ```

## Code Review Checklist

- [ ] Code follows naming conventions
- [ ] Error handling is comprehensive
- [ ] No memory leaks
- [ ] Thread-safe where needed
- [ ] Documented with comments
- [ ] No hardcoded values (use constants)
- [ ] Efficient algorithms
- [ ] No compiler warnings
