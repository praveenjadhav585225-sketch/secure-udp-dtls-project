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

    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);

    SSL_connect(ssl);

    SSL_write(ssl, "Hello Secure UDP", 17);

    SSL_free(ssl);
    close(sock);
    SSL_CTX_free(ctx);
}
