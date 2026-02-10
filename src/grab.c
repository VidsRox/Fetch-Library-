#include "grab.h"
#include "fetch.h"
#include "utils.h"
#include <stdlib.h>


int main() {
    Request req;
    Response *resp;

    //set up request
    req.method = get;
    req.url.protocol = http;
    my_strcopy((char *)req.url.domain, "www.google.com");
    my_strcopy((char *)req.url.file, "/");
    req.contentType[0] = NULL;
    req.cookies = NULL;
    req.headers = NULL;
    req.data = NULL;
    req.size = 0;

    printf("Fetching http://%s%s\n", req.url.domain, req.url.file);

    //Make request
    resp = fetch_sync(&req);

    if(resp){
        printf("\n=== RESPONSE ===\n");
        printf("Status: %d\n", resp->status);
        printf("Content-Type: %s\n", (char *)resp->contentType);
        printf("Body size: %lld bytes\n", resp->size);
        printf("\nFirst 500 chars of the body:\n");

        int i;
        int max = (resp->size < 500) ? resp->size : 500;

        for(i = 0; i < max; i++){
            printf("%c", resp->data[i]);
        }
        printf("\n");

        free_response(resp);
    } else {
        printf("Request failed\n");
    }

    return 0;
}