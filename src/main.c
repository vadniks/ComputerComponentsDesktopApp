
#include <time.h>
#include <lvgl/lvgl.h>
#include <curl/curl.h>

int main() {
    struct timespec requested = { 0, 1000000 }, remaining = { 0, 0 };

    CURL* curl = curl_easy_init();
    if (!curl) return 1;

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, "https://dummyjson.com/products/1");
    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    lv_init();
    unsigned a = 0;
    while (a < 1000) {
        lv_tick_inc(1);
        a++;
        if (nanosleep(&requested, &remaining) != 0) return 1;
    }
    lv_deinit();
    printf("%c\n", lv_is_initialized() ? 't' : 'f');
    return 0;
}
