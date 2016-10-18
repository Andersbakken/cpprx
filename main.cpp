#include <stdio.h>
#include <regex>

static void usage(FILE *f)
{
    fprintf(f, "cpprx [options...] <rx> <haystack>"
            "  Options:\n"
            "  --help|-h          Display help\n");
}

int main(int argc, char **argv)
{
    char *rx = 0;
    char *haystack = 0;
    bool dashdash = false;
    for (int i=1; i<argc; ++i) {
        if (!dashdash && !strcmp(argv[i], "--"))
            dashdash = true;
        if (!dashdash && *argv[i] == '-') {
            if (!strcmp("-h", argv[i]) || !strcmp("--help", argv[i])) {
                usage(stdout);
                return 0;
            }
        } else if (!rx) {
            rx = argv[i];
        } else if (!haystack) {
            haystack = argv[i];
        } else {
            usage(stderr);
            fprintf(stderr, "Too many args\n");
            return 1;
        }
    }

    if (!rx || !haystack) {
        usage(stderr);
        fprintf(stderr, "Not enough args\n");
        return 1;
    }

    std::regex regex(rx);
    std::smatch match;

    const std::string str(haystack);
    if (!std::regex_match(str, match, regex)) // no match
        return 1;

    for (size_t i=0; i<match.size(); ++i) {
        printf("Match[%zu]: %zu \"%s\"\n", i, match[i].first - str.begin(), match[i].str().c_str());
    }
    return 0;
}
