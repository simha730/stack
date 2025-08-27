typedef struct
{
    int *memory;
    int size;
} Allocator;

Allocator *allocatorCreate(int n)
{
    Allocator *obj = (Allocator *)malloc(sizeof(Allocator));
    if (!obj)
        return NULL;
    obj->memory = (int *)calloc(n, sizeof(int));
    if (!obj->memory)
    {
        free(obj);
        return NULL;
    }
    obj->size = n;
    if (!obj->memory)
        return NULL;
    return obj;
}

int allocatorAllocate(Allocator *obj, int size, int mID)
{
    int count = 0;
    for (int i = 0; i < obj->size; i++)
    {
        if (obj->memory[i] == 0)
        {
            count++;
        }
        else
        {
            count = 0;
        }
        if (count == size)
        {
            int start = i - size + 1, end = start + size;
            for (int j = start; j < end; j++)
            {
                obj->memory[j] = mID;
            }
            return start;
        }
    }
    return -1;
}

int allocatorFreeMemory(Allocator *obj, int mID)
{
    int freed = 0;
    for (int i = 0; i < obj->size; i++)
    {
        if (obj->memory[i] == mID)
        {
            obj->memory[i] = 0;
            freed++;
        }
    }
    return freed;
}

void allocatorFree(Allocator *obj)
{
    free(obj->memory);
    free(obj);
}
