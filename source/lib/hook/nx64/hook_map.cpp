#include "hook_map.hpp"

const HookMap::Node* HookMap::Get(uintptr_t key) const {
    size_t hash = static_cast<size_t>(key) % HOOK_COUNT;
    const Node* out_node = nullptr;
    while (table[hash].key != 0) {
        if (table[hash].key == key) {
            out_node = &table[hash];
            break;
        }
    }

    return out_node;
}

HookMap::Node* HookMap::GetMut(uintptr_t key) {
    size_t hash = static_cast<size_t>(key) % HOOK_COUNT;
    Node* out_node = nullptr;
    while (table[hash].key != 0) {
        if (table[hash].key == key) {
            out_node = &table[hash];
            break;
        }
    }

    return out_node;
}

bool HookMap::Insert(uintptr_t key) {
    size_t hash = static_cast<size_t>(key) % HOOK_COUNT;
    size_t current = hash;
    do {
        if (table[current].key == 0) {
            table[current].key = key;
            return true;
        }
        current = (current + 1) % HOOK_COUNT;
    } while (current != hash);
    return false;
}