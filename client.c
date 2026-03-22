#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>

int main() {
    SSL_library_init();

    SSL_CTX *ctx = SSL_CTX_new(DTLS_client_method());

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(4444);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr*)&server, sizeof(server));
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define SERVER_IP "127.0.0.1"
#define PORT 4444

int main() {
    SSL_library_init();
    OpenSSL_add_ssl_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = DTLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);

    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    SSL *ssl = SSL_new(ctx);

    BIO *bio = BIO_new_dgram(sockfd, BIO_NOCLOSE);
    SSL_set_bio(ssl, bio, bio);

    // DTLS handshake
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        printf("Handshake successful!\n");

        char *msg = "Hello Secure UDP (DTLS)";
        SSL_write(ssl, msg, strlen(msg));
    }

    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);

    return 0;
}
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    SSL_connect(ssl);

    SSL_write(ssl, "Hello Secure UDP", 17);

    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);
}
