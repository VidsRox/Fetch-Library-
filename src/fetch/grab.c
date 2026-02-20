#include "grab.h"
#include "fetch.h"
#include "utils.h"
#include "timer.h"
#include <stdlib.h>

void my_callback(Response* resp, void* context) {
    Request* req = (Request*)context;
    if(resp){
        printf("Async response: %d bytes\n", (int)resp->size);
        free_response(resp);
    } else {
        printf("Async request FAILED\n");
    }
    free(req);  // always free, but after using resp
}

int main() {
    Timer total_timer;
    Request req;
    Response *resp;
    int num_requests = 10;  // Test with 10 requests
    
    printf("========================================\n");
    printf("Sequential Fetch Performance Test\n");
    printf("========================================\n");
    printf("Making %d requests to Google...\n\n", num_requests);

    // Set up request
    req.method = get;
    req.url.protocol = http;
    my_strcopy((char *)req.url.domain, "www.google.com");
    my_strcopy((char *)req.url.file, "/");
    req.contentType[0] = NULL;
    req.cookies = NULL;
    req.headers = NULL;
    req.data = NULL;
    req.size = 0;

    // Start total timer
    timer_start(&total_timer);
    
    // Make multiple requests sequentially
    for (int i = 1; i <= num_requests; i++) {
        Timer request_timer;
        
        printf("Fetching request %d... ", i);
        fflush(stdout);
        
        timer_start(&request_timer);
        resp = fetch_sync(&req);
        double request_time = timer_stop(&request_timer);
        
        if (resp) {
            printf("%d bytes in %.2f ms\n", (int)resp->size, request_time);
            free_response(resp);
        } else {
            printf("FAILED\n");
        }
    }
    
    // Stop total timer
    double total_time = timer_stop(&total_timer);
    
    printf("\n========================================\n");
    printf("Results:\n");
    printf("========================================\n");
    printf("Total requests: %d\n", num_requests);
    printf("Total time:     %.2f ms (%.2f seconds)\n", total_time, total_time/1000.0);
    printf("Avg per request: %.2f ms\n", total_time / num_requests);
    printf("========================================\n");

    printf("Async Fetch Performance Test\n");
    printf("========================================\n");
    printf("Making %d requests to Google...\n\n", num_requests);

    fetch_init(4);//4 workers

    timer_start(&total_timer);

    for(int i = 0; i<num_requests; i++){
        Request* request = malloc(sizeof(Request));
        request->method=req.method;
        request->url.protocol = req.url.protocol;
        my_strcopy((char*)request->url.domain, "www.google.com");
        my_strcopy((char*)request->url.file, "/");
        request->contentType[0] = req.contentType[0];
        request->cookies = req.cookies;
        request->headers=req.headers;
        request->data=req.data;
        request->size=req.size;
        fetch_async(request, my_callback, request);
    }

    fetch_cleanup(); //blocks until all workers finish

    double async_total = timer_stop(&total_timer);

    printf("\nTotal async time: %.2f ms (%.2f seconds)\n", 
       async_total, async_total/1000.0);
    

    return 0;
}