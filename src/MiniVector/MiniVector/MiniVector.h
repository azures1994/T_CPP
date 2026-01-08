#include <iostream>
#include <memory>       // std::allocator (C++11)
#include <algorithm>    // std::uninitialized_copy (C++11)
#include <stdexcept>    // std::out_of_range (C++11)
#include <utility>      // std::move, std::forward (C++11)
#include <cstddef>      // size_t (C++11)

// 纯C++11兼容的Vector实现
template <typename T>
class MiniVector {
public:
    // C++11 类型别名（替代typedef）
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    // ===== 构造/析构（纯C++11）=====
    MiniVector() noexcept 
        : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
        reserve(4); // 预分配初始容量
    }

    explicit MiniVector(size_type n, const T& val = T()) 
        : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
        resize(n, val);
    }

    // 拷贝构造（C++11兼容）
    MiniVector(const MiniVector& rhs) 
        : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
        reserve(rhs.capacity());
        // C++11: 用uninitialized_copy（仅拷贝，无移动）
        _finish = std::uninitialized_copy(rhs._start, rhs._finish, _start);
    }

    // 移动构造（C++11核心，noexcept）
    MiniVector(MiniVector&& rhs) noexcept 
        : _start(rhs._start), _finish(rhs._finish), _end_of_storage(rhs._end_of_storage) {
        rhs._start = rhs._finish = rhs._end_of_storage = nullptr; // C++11 nullptr
    }

    ~MiniVector() noexcept {
        clear();
        if (_start) {
            _alloc.deallocate(_start, capacity());
        }
    }

    // ===== 赋值运算符（C++11）=====
    MiniVector& operator=(MiniVector rhs) noexcept {
        swap(rhs);
        return *this;
    }

    MiniVector& operator=(MiniVector&& rhs) noexcept {
        if (this != &rhs) {
            clear();
            _alloc.deallocate(_start, capacity());
            _start = rhs._start;
            _finish = rhs._finish;
            _end_of_storage = rhs._end_of_storage;
            rhs._start = rhs._finish = rhs._end_of_storage = nullptr;
        }
        return *this;
    }

    // ===== 核心操作（C++11兼容）=====
    void push_back(const T& val) {
        _emplace_aux();
        _alloc.construct(_finish, val); // 拷贝构造
        ++_finish;
    }

    void push_back(T&& val) {
        _emplace_aux();
        _alloc.construct(_finish, std::move(val)); // C++11 移动构造
        ++_finish;
    }

    // emplace_back：C++11 可变参数+完美转发
    template <typename... Args>
    void emplace_back(Args&&... args) {
        _emplace_aux();
        // C++11 完美转发，原地构造
        _alloc.construct(_finish, std::forward<Args>(args)...);
        ++_finish;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("MiniVector::pop_back: empty container");
        }
        --_finish;
        _alloc.destroy(_finish); // C++11 allocator::destroy
    }

    reference operator[](size_type idx) {
        if (idx >= size()) {
            throw std::out_of_range("MiniVector::operator[]: index out of range");
        }
        return _start[idx];
    }

    const_reference operator[](size_type idx) const {
        if (idx >= size()) {
            throw std::out_of_range("MiniVector::operator[]: index out of range");
        }
        return _start[idx];
    }

    // 扩容：替换std::uninitialized_move（C++11手动实现）
    void reserve(size_type new_cap) {
        if (new_cap <= capacity()) return;

        // 步骤1：分配新内存
        pointer new_start = _alloc.allocate(new_cap);
        pointer new_finish = new_start;

        // 步骤2：手动实现uninitialized_move（C++11兼容）
        pointer old_ptr = _start;
        while (old_ptr != _finish) {
            // 移动构造每个元素到新内存
            _alloc.construct(new_finish, std::move(*old_ptr));
            ++new_finish;
            ++old_ptr;
        }

        // 步骤3：析构旧内存的元素（手动替换std::destroy）
        clear();
        // 步骤4：释放旧内存
        _alloc.deallocate(_start, capacity());

        // 步骤5：更新指针
        _start = new_start;
        _finish = new_finish;
        _end_of_storage = _start + new_cap;
    }

    // resize：替换std::destroy（C++11手动析构）
    void resize(size_type new_size, const T& val = T()) {
        if (new_size < size()) {
            // 手动析构多余元素（替换std::destroy）
            pointer p = _start + new_size;
            while (p != _finish) {
                _alloc.destroy(p);
                ++p;
            }
            _finish = _start + new_size;
        } else if (new_size > size()) {
            reserve(new_size);
            // 构造新元素
            pointer p = _finish;
            while (p != _start + new_size) {
                _alloc.construct(p, val);
                ++p;
            }
            _finish = _start + new_size;
        }
    }

    // clear：手动析构所有元素（替换std::destroy）
    void clear() noexcept {
        pointer p = _start;
        while (p != _finish) {
            _alloc.destroy(p);
            ++p;
        }
        _finish = _start;
    }

    // ===== 状态查询（C++11 noexcept）=====
    size_type size() const noexcept { return _finish - _start; }
    size_type capacity() const noexcept { return _end_of_storage - _start; }
    bool empty() const noexcept { return _start == _finish; }

    // ===== 辅助函数（C++11）=====
    void swap(MiniVector& rhs) noexcept {
        using std::swap;
        swap(_start, rhs._start);
        swap(_finish, rhs._finish);
        swap(_end_of_storage, rhs._end_of_storage);
        swap(_alloc, rhs._alloc);
    }

private:
    // 扩容辅助函数
    void _emplace_aux() {
        if (_finish == _end_of_storage) {
            reserve(capacity() == 0 ? 4 : 2 * capacity());
        }
    }

    std::allocator<T> _alloc;    // C++11 标准分配器
    pointer _start;              // 容器起始地址
    pointer _finish;             // 最后一个有效元素的下一个位置
    pointer _end_of_storage;     // 容量末尾的下一个位置
};

class TestObj {
public:
    int val;
    TestObj(int v = 0) : val(v) {
        std::cout << "TestObj construct: " << val << std::endl;
    }
    TestObj(const TestObj& other) : val(other.val) {
        std::cout << "TestObj copy construct: " << val << std::endl;
    }
    TestObj(TestObj&& other) noexcept : val(other.val) {
        other.val = -1;
        std::cout << "TestObj move construct: " << val << std::endl;
    }
    ~TestObj() {
        std::cout << "TestObj destruct: " << val << std::endl;
    }
};
