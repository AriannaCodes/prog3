// pqueue.h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

class Pqueue
{
    public:
        Pqueue(unsigned int size);
        inline bool empty(void) const;
        void insert(uint64_t newItem);
        uint64_t removeMin(void);
        void print(void) const;
        ~Pqueue(void);
    private:
        uint64_t * m_array;
        unsigned int * m_positions;
        unsigned int m_end;
        unsigned int offset;
};

inline bool Pqueue::empty(void) const
{
    return (m_end < 1);
}