#pragma once

#include <cinttypes>
#include <cstdlib>

class HookMap {
public:
    static const size_t HOOK_COUNT = 0x400;

    struct Node {
        uintptr_t key;
    };

private:
    Node table[HOOK_COUNT];

public:
    HookMap() : table({ Node { .key = 0 } }) {}
    
    const Node* Get(uintptr_t key) const;
    Node* GetMut(uintptr_t key);
    bool Insert(uintptr_t);
};