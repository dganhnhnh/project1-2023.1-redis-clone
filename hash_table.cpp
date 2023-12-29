#include <assert.h>
#include <stdlib.h>
#include <cstdint>

struct HNode
{
    HNode *next = NULL;
    uint64_t hcode = 0;
};

struct HTab
{
    HNode **tab = NULL;
    // ??
    size_t mask = 0;
    size_t size = 0;
};

// size of the hashtable is power of two
// ??
static void h_init(HTab *htab, size_t n)
{
    assert(n > 0 && ((n - 1) & n) == 0);
    // cấp phát động, thiết lập bộ nhớ về 0
    htab->tab = (HNode **)calloc(sizeof(HNode *), n);
    htab->mask = n - 1;
    htab->size = 0;
}

static void h_insert(HTab *htab, HNode *node) {
    // index in hash table
    // = hash code of node AND ht mask
    size_t pos = node->hcode & htab->mask;
    // chèn vào đầu danh sách
    HNode *next = htab->tab[pos];
    node->next = next;
    htab->tab[pos] = node;
    htab->size++;
}

static HNode **h_lookup(
    HTab *htab, HNode *key, bool (*cmp)(HNode *, HNode *))
{
    // ht chưa có gì
    if (!htab->tab) {
        return NULL;
    }

    size_t pos = key->hcode & htab->mask;
    // con trỏ trỏ tới đầu list tại index pos
    HNode **from = &htab->tab[pos];
    while (*from) {
        if (cmp(*from, key)) {
            // lưu trữ key value cơ mà, cái này lấy value như nào
            return from;
        }
        from = &(*from)->next;
    }
    return NULL;
}

// remove a node from the chain
static HNode *h_detach(HTab *htab, HNode **from) {
    HNode *node = *from;
    *from = (*from)->next;
    htab->size--;
    return node;
}