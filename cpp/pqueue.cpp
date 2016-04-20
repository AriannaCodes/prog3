// pqueue.cpp

#include "pqueue.h"

Pqueue::Pqueue(unsigned int size)
  : m_end(0),
    m_offset(0)
{
    // initialize the array of edges
    m_array = (uint64_t *)malloc((2 * sizeof(uint64_t)) * (size + 2));
    memset(m_array, 0, 2 * sizeof(uint64_t) * (size + 2));
    // array for holding positions
    m_positions = (unsigned int *)malloc((2 * sizeof(unsigned int)) * (size + 2));
    memset(m_positions, 0, 2 * sizeof(unsigned int) * (size + 2));
}

void Pqueue::insert(uint64_t newItem)
{
    unsigned int pos;

    // insert new edge to the end
    ++m_end;
    m_array[m_end] = newItem;
    m_positions[m_end] = m_end;
    pos = m_end;

    // keep swapping up to keep the order property
    while (pos/2 != 0)
    {
        if (m_array[m_positions[pos]] < m_array[m_positions[pos/2]])
        {
            
        }



        if (m_array[pos] < m_array[pos / 2])
        {
            uint64_t temp = m_array[pos / 2];
            m_array[pos / 2] = m_array[pos];
            m_positions[m_array[pos / 2]] = pos / 2;
            m_array[pos] = temp;
            m_positions[temp] = pos;
            pos = pos / 2;
        }
        else return;
    }
}

Edge Pqueue::removeMin(void)
{
    Edge min = m_array[1];
    m_positions[min.b] = 0;
    unsigned long int pos = 1;
    if (m_end != 1)
    {
        m_array[1] = m_array[m_end];
        m_positions[m_array[1].b] = 1;
    }
    --m_end;
    while (pos < m_end)
    {
        // check if vertex has left child
        if(2 * pos <= m_end)
        {
            // check if vertex has right child
            if(2 * pos +1 <= m_end)
            {
                //check if right child is smaller than left and parent
                if(m_array[2 * pos + 1].w < m_array[2 * pos].w 
                    && m_array[pos].w > m_array[2 * pos + 1].w)
                {
                    Edge temp = m_array[2 * pos + 1];
                    m_array[2 * pos + 1] = m_array[pos];
                    m_positions[m_array[2 * pos + 1].b] = 2 * pos + 1;
                    m_array[pos] = temp;
                    m_positions[m_array[pos].b] = pos;
                    pos = 2 * pos + 1;
                }
                else if (m_array[2 * pos].w < m_array[pos].w)
                {
                    Edge temp = m_array[2 * pos];
                    m_array[2 * pos] = m_array[pos];
                    m_positions[m_array[2 * pos].b] = 2 * pos;
                    m_array[pos] = temp;
                    m_positions[m_array[pos].b] = pos;
                    pos = 2 * pos;
                }
                else return min;
            }
            else if (m_array[2 * pos].w < m_array[pos].w)
            {
                Edge temp = m_array[2 * pos];
                m_array[2 * pos] = m_array[pos];
                m_positions[m_array[2 * pos].b] = 2 * pos;
                m_array[pos] = temp;
                m_positions[m_array[pos].b] = pos;
                pos = 2 * pos;
            }
            else return min;
        }
        else return min;
    }
    return min;
}

void Pqueue::print(void) const
{
    for(unsigned int i = 1; i <= m_end; ++i)
    {
        std::cout << m_array[i].a << " " << m_array[i].b << " " << m_array[i].w << std::endl;
    }
    for (int i = 0; i < 11; ++i)
    {
        std::cout << m_positions[i] << ", ";
    }
}

Pqueue::~Pqueue(void)
{
    free(m_array);
    free(m_positions);
}