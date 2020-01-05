//
// Created by yche on 1/5/20.
//

#include <cstdio>
#include <cstdlib>

extern "C"
{
#include "graph.h"
#include "init.h"
}

#include "util/log/log.h"
#include "util/util.h"

void writeToBinFile(graph *g) {
    LONG_T i;

    if (WRITE_TO_FILE) {
        fprintf(stderr, "Writing to file ... ");
        log_info("Out File Path: %s", OUTFILE);
        auto tmp_file_fd = open(OUTFILE, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        size_t file_size = sizeof(int32_t) * 2 * g->m;
        log_info("File Size: %s", FormatWithCommas(file_size).c_str());
        ftruncate(tmp_file_fd, file_size);

        // mmap here.
        auto write_buf = (pair<int32_t, int32_t> *) mmap(nullptr, file_size,
                                                         PROT_READ | PROT_WRITE, MAP_SHARED, tmp_file_fd, 0);
#pragma omp parallel for
        for (i = 0; i < g->m; i++) {
            write_buf[i].first = g->start[i] + 1;
            write_buf[i].second = g->end[i] + 1;
        }
        auto ret = munmap(write_buf, file_size);
        log_info("After Munmap, success code: %d", ret);
        close(tmp_file_fd);
    }
}


int main(int argc, char** argv)
{

    /* data structure for representing the generated edge sets
     * see defs.h */
    graph G;

    /* init.c */
    parseUserInput(argc, argv);

    /* graph.c */
    graphGen(&G);

    /* utils.c */
    writeToBinFile(&G);

    /* Free memory */
    if (STORE_IN_MEMORY) {
        free(G.start);
        free(G.end);
        free(G.w);
    }

    return(0);
}

