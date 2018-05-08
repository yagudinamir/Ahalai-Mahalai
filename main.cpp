#include <iostream>

template <bool Cond1, bool Cond2, typename T, int previous>
struct enable_if {
    static constexpr int whence = T::whence;
    static constexpr int how = T::how;
};

template <bool Cond2, typename T, int previous>
struct enable_if<false, Cond2, T, previous> {
    static constexpr int whence = T::curr - 1;
    static constexpr int how = (T::previous xor previous) - (previous xor T::Xor);
};

template <typename T, int previous>
struct enable_if<false, false, T, previous> {
    static constexpr int whence = 0;
    static constexpr int how = 0;
};

template <int current, int prev, int T, int... Args>
class ValueAhalaiMahalai {
public:
    static constexpr int previous = prev;
    static constexpr int curr = current;
    static constexpr int Xor = T xor ValueAhalaiMahalai<curr + 1, previous xor T, Args...>::Xor;
    static constexpr int who = (Xor == 0) + 1;
    static constexpr int whence = enable_if<(ValueAhalaiMahalai<curr + 1, previous xor T, Args...>::whence != 0), (T > (previous xor ValueAhalaiMahalai<curr + 1, previous xor T, Args...>::Xor)), ValueAhalaiMahalai<curr + 1, previous xor T, Args...>, previous>::whence;
    static constexpr int how = enable_if<(ValueAhalaiMahalai<curr + 1, previous xor T, Args...>::whence != 0), (T > (previous xor ValueAhalaiMahalai<curr + 1, previous xor T, Args...>::Xor)), ValueAhalaiMahalai<curr + 1, previous xor T, Args...>, previous>::how;
};

template <int current, int prev, int T>
class ValueAhalaiMahalai<current, prev, T> {
public:
    static constexpr int previous = prev;
    static constexpr int curr = current;
    static constexpr int Xor = T;
    static constexpr int who = (Xor == 0) + 1; //?
    static constexpr int whence = enable_if<false, (T > previous), ValueAhalaiMahalai<curr + 1, previous xor T, 0>, previous>::whence;
    static constexpr int how = enable_if<false, (T > previous), ValueAhalaiMahalai<curr + 1, previous xor T, 0>, previous>::how;
};

template <int current, int prev>
class ValueAhalaiMahalai<current, prev, 0> {
public:
    static constexpr int previous = prev;
    static constexpr int curr = current;
    static constexpr int Xor = 0;
};

template <int... Args>
class AhalaiMahalai {
public:
    static constexpr int who = ValueAhalaiMahalai<1, 0, Args...>::who;
    static constexpr int whence = ValueAhalaiMahalai<1, 0, Args...>::whence;
    static constexpr int how = ValueAhalaiMahalai<1, 0, Args...>::how;
};


int main() {
    std::cout << AhalaiMahalai<10, 16, 10, 16, 14, 15>::who << " " << AhalaiMahalai<10, 16, 10, 16, 14, 15>::whence << " " << AhalaiMahalai<10, 16, 10, 16, 14, 15>::how << "\n";
    std::cout << AhalaiMahalai<10, 16, 10, 13, 14, 13>::who << " " << AhalaiMahalai<10, 16, 10, 13, 14, 13>::whence << " " << AhalaiMahalai<10, 16, 10, 13, 14, 13>::how << "\n";
    std::cout << AhalaiMahalai<10, 16, 99, 10, 16>::who << " " << AhalaiMahalai<10, 16, 99, 10, 16>::whence << " " << AhalaiMahalai<10, 16, 99, 10, 16>::how;
    return 0;
}