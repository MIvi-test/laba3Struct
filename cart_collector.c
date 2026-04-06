#include "deq_and_stack.h"
#include "deter.h"

typedef struct OpsCounters
{
    int line_add;
    int line_remove;
    int train_add;
    int train_remove;
} OpsCounters;

static int line_size(const DequeStatic *line)
{
    if (line == NULL || line->head_index == -1)
    {
        return 0;
    }
    return line->tail_index - line->head_index + 1;
}

static int line_free(const DequeStatic *line)
{
    return line->capacity - (line->tail_index - line->head_index + 1);
}

static int line_get_by_offset(const DequeStatic *line, int offset_from_head)
{
    int idx = line->head_index + offset_from_head;
    return line->massive_static_deque[idx];
}

static int line_find_best_side(const DequeStatic *line, int cart_id, int *side, int *blockers)
{
    int sz = line_size(line);
    int from_head = -1;
    int from_tail = -1;

    for (int i = 0; i < sz; i++)
    {
        if (line_get_by_offset(line, i) == cart_id)
        {
            from_head = i;
            break;
        }
    }
    for (int i = 0; i < sz; i++)
    {
        int idx = line->tail_index - i;
        if (line->massive_static_deque[idx] == cart_id)
        {
            from_tail = i;
            break;
        }
    }

    if (from_head < 0 && from_tail < 0)
    {
        return 0;
    }

    if (from_head >= 0 && (from_tail < 0 || from_head <= from_tail))
    {
        *side = 0; // S (head)
        *blockers = from_head;
    }
    else
    {
        *side = 1; // E (tail)
        *blockers = from_tail;
    }
    return 1;
}

static int pick_buffer_line(DequeStatic *lines, int lines_count, int except_line, int need_free)
{
    int best = -1;
    int best_free = -1;
    for (int i = 0; i < lines_count; i++)
    {
        if (i == except_line)
        {
            continue;
        }
        int free_slots = lines[i].capacity - line_size(&lines[i]);
        if (free_slots >= need_free && free_slots > best_free)
        {
            best_free = free_slots;
            best = i;
        }
    }
    return best;
}

static void print_move_line_to_line(int id, int from_idx, int from_side, int to_idx, int to_side, bool verbose)
{
    if (!verbose)
        return;
    printf("%d LINE_%d%c LINE_%d%c\n", id, from_idx + 1, from_side == 0 ? 'S' : 'E',
           to_idx + 1, to_side == 0 ? 'S' : 'E');
}

static void print_move_line_to_train(int id, int from_idx, int from_side, bool verbose)
{
    if (!verbose)
        return;
    printf("%d LINE_%d%c TRAIN\n", id, from_idx + 1, from_side == 0 ? 'S' : 'E');
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <input_file> [--verbose|-v]\n", argv[0]);
        return 1;
    }

    bool verbose = false;
    if (argc >= 3 && (strcmp(argv[2], "--verbose") == 0 || strcmp(argv[2], "-v") == 0))
    {
        verbose = true;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        perror("input file open error");
        return 1;
    }

    int lines_count = 0;
    if (fscanf(f, "%d", &lines_count) != 1 || lines_count <= 0)
    {
        fclose(f);
        printf("Invalid input: lines count\n");
        return 1;
    }

    DequeStatic *lines = (DequeStatic *)malloc(lines_count * sizeof(DequeStatic));
    if (!lines)
    {
        fclose(f);
        return 1;
    }

    for (int i = 0; i < lines_count; i++)
    {
        int capacity = 0, count = 0;
        if (fscanf(f, "%d %d", &capacity, &count) != 2 || capacity <= 0 || count < 0 || count > capacity)
        {
            fclose(f);
            free(lines);
            printf("Invalid input: line %d header\n", i + 1);
            return 1;
        }

        if (!deque_static_init(&lines[i], capacity))
        {
            fclose(f);
            free(lines);
            printf("Memory allocation failed for line %d\n", i + 1);
            return 1;
        }

        for (int k = 0; k < count; k++)
        {
            int id = 0;
            if (fscanf(f, "%d", &id) != 1)
            {
                fclose(f);
                free(lines);
                printf("Invalid input: carts in line %d\n", i + 1);
                return 1;
            }
            if (!deque_static_push_back(&lines[i], id))
            {
                fclose(f);
                free(lines);
                printf("Failed to push cart %d into line %d (capacity exceeded?)\n", id, i + 1);
                return 1;
            }
        }
    }

    int target_count = 0;
    if (fscanf(f, "%d", &target_count) != 1 || target_count < 0)
    {
        fclose(f);
        free(lines);
        printf("Invalid input: target count\n");
        return 1;
    }

    int *targets = (int *)malloc(target_count * sizeof(int));
    if (!targets)
    {
        fclose(f);
        free(lines);
        return 1;
    }

    for (int i = 0; i < target_count; i++)
    {
        if (fscanf(f, "%d", &targets[i]) != 1)
        {
            fclose(f);
            free(targets);
            free(lines);
            printf("Invalid input: target ids\n");
            return 1;
        }
    }
    fclose(f);

    OpsCounters ops = {0, 0, 0, 0};
    StackDynamic train;
    initStack(&train);
    int iter_already[target_count];
    for (int i = 0; i < target_count; i++)
    {
        iter_already[i] = -1;
    }

    for (int iter = 0; iter < target_count; iter++)
    {
        int best_tagret = -1;
        int best_side = -1;
        int best_blockers = -1;
        int from_line = -1;

        
        for (int t = 0; t < target_count; t++)
        {
            int target = targets[t];
            int n = 0;
            for (; n < target_count; n++)
            {
                if (target == iter_already[n])
                    break;
            }
            if (n < target_count)
                continue; 

            for (int i = 0; i < lines_count; i++)
            {
                int side, blockers;
                if (line_find_best_side(&lines[i], target, &side, &blockers))
                {
                    if (best_tagret < 0 || blockers < best_blockers)
                    {
                        best_blockers = blockers;
                        best_side = side;
                        best_tagret = target;
                        from_line = i;
                    }
                }
            }
        }

        if (best_tagret == -1)
        {
            fprintf(stderr, "Error: cannot reach target %d (iteration %d)\n", targets[iter], iter);
            break;
        }

        iter_already[iter] = best_tagret;

        
        if (best_blockers == 0)
        {
            print_move_line_to_train(best_tagret, from_line, best_side, verbose);
            if (best_side == 0)
                popDequeFront(&lines[from_line]);
            else
                popDequeBack(&lines[from_line]);
            ops.line_remove++;
            pushStack(&train, best_tagret);
            ops.train_add++;
            continue;
        }

        while (best_blockers > 0)
        {
            int to_line = -1;
            int best_free = -1;
            for (int l = 0; l < lines_count; l++)
            {
                if (l == from_line)
                    continue;
                int fr = line_free(&lines[l]);
                if (fr > best_free)
                {
                    best_free = fr;
                    to_line = l;
                }
            }

            if (to_line == -1 || best_free == 0)
                break;

            int move = (best_free >= best_blockers) ? best_blockers : best_free;
            best_blockers -= move;

            for (int _ = 0; _ < move; _++)
            {
        
                int value;
                if (best_side == 0)   
                    value = popDequeFront(&lines[from_line]);
                else
                    value = popDequeBack(&lines[from_line]);
                ops.line_remove++;

                
                pushDequeFront(&lines[to_line], value);
                print_move_line_to_line(value, from_line, best_side, to_line, 0, verbose);
                ops.line_add++;
            }
        }

        
        print_move_line_to_train(best_tagret, from_line, best_side, verbose);
        if (best_side == 0)
            popDequeFront(&lines[from_line]);
        else
            popDequeBack(&lines[from_line]);
        ops.line_remove++;
        pushStack(&train, best_tagret);
        ops.train_add++;
    }

    printf("LINE_ADD: %d\n", ops.line_add);
    printf("LINE_REMOVE: %d\n", ops.line_remove);
    printf("TRAIN_ADD: %d\n", ops.train_add);
    printf("TRAIN_REMOVE: %d\n", ops.train_remove);
    printf("TOTAL: %d\n", ops.line_add + ops.line_remove + ops.train_add + ops.train_remove);

    
    for (int i = 0; i < lines_count; i++)
    {
        free(lines[i].massive_static_deque);
        lines[i].massive_static_deque = NULL;
    }
    free(lines);
    free(targets);
    destroyStack(&train);

    return 0;
}