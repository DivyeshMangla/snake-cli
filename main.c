#include <stdbool.h>
#include <stdio.h>

#include "Key.h"

int main() {
    while (true) {
        const Key key = read_key();
        printf("Pressed Key = %s\n",   key_type_to_string(key.type));
    }
}
