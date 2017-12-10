#include "stdio.h"
#include "../parser/cJSON.h"

int main() {
    const char* my_json_string = "{\n"
            "    \"name\": \"Jack (\\\"Bee\\\") Nimble\",\n"
            "    \"format\": {\n"
            "        \"type\":       \"rect\",\n"
            "        \"width\":      1920,\n"
            "        \"height\":     1080,\n"
            "        \"interlace\":  false,\n"
            "        \"frame rate\": 24\n"
            "    }\n"
            "}";

    cJSON * root = cJSON_Parse(my_json_string);
    cJSON *format = cJSON_GetObjectItemCaseSensitive(root, "format");
    cJSON *framerate_item = cJSON_GetObjectItemCaseSensitive(format, "frame rate");
    int framerate = 0;
    cJSON_SetNumberValue(framerate_item, 140);
    if (cJSON_IsNumber(framerate_item))
    {
        framerate = framerate_item->valueint;
    }
    printf("value of framerate; %d", framerate);

    cJSON_Delete(root);

    return 0;
}

